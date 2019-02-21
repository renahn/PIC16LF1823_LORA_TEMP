#include <ESP8266WiFi.h>
#include <PubSubClient.h>


//informações da rede WIFI
const char* ssid = "Jiomar";                 //SSID da rede WIFI
const char* password =  "MARIM123";    //senha da rede wifi
 
//informações do broker MQTT - Verifique as informações geradas pelo CloudMQTT
const char* mqttServer = "m11.cloudmqtt.com";   //server
const char* mqttUser = "fagkuzua";              //user
const char* mqttPassword = "wqQvH-bBu4TH";      //password
const int mqttPort = 10077;                     //port
const char* mqttTopicSub ="JUNIOR/TEMP/1";            //tópico que sera assinado
 

WiFiClient espClient;
PubSubClient client(espClient);

#define WIFI_CONNECT_TIMEOUT 15*1000 // 15 segundos
static int milli;

uint8_t app_mqtt_init(void)
{
  WiFi.begin(ssid, password);

  milli = millis();

  // Tenta conectar ao wifi
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.println("Conectando ao WiFi..");
  
    if((millis() - milli) > WIFI_CONNECT_TIMEOUT)
    {
        Serial.println("TIMEOUT coneccao com WIFI");
        return 1; 
    }
  }
  Serial.println("Conectado na rede WiFi");

  // Conecta ao servidor MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while(!client.connected()) 
  {
    Serial.println("Conectando ao Broker MQTT...");
    if(client.connect("ESP8266Client", mqttUser, mqttPassword )) Serial.println("Conectado");  
    else 
    {
      Serial.print("falha estado  ");
      Serial.print(client.state());
      return 1;
    }
  }
 
  //subscreve no tópico
  client.subscribe(mqttTopicSub);

  return 0;
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  //armazena msg recebida em uma sring
  payload[length] = '\0';
  String strMSG = String((char*)payload);
 
  #ifdef DEBUG
  Serial.print("Mensagem chegou do tópico: ");
  Serial.println(topic);
  Serial.print("Mensagem:");
  Serial.print(strMSG);
  Serial.println();
  Serial.println("-----------------------");
  #endif
}
 
//função pra reconectar ao servido MQTT
void reconect() {
  //Enquanto estiver desconectado
  while (!client.connected()) {
    #ifdef DEBUG
    Serial.print("Tentando conectar ao servidor MQTT");
    #endif
     
    bool conectado = strlen(mqttUser) > 0 ?
                     client.connect("ESP8266Client", mqttUser, mqttPassword) :
                     client.connect("ESP8266Client");
 
    if(conectado) {
      #ifdef DEBUG
      Serial.println("Conectado!");
      #endif
      //subscreve no tópico
      client.subscribe(mqttTopicSub, 1); //nivel de qualidade: QoS 1
    } else {
      #ifdef DEBUG
      Serial.println("Falha durante a conexão.Code: ");
      Serial.println( String(client.state()).c_str());
      Serial.println("Tentando novamente em 10 s");
      #endif
      //Aguarda 10 segundos 
      delay(10000);
    }
  }
}

void app_mqtt_loop(void)
{
  if (!client.connected()) {
    reconect();
  }
  client.loop(); 
}

void app_mqtt_send_temp(double temp)
{
    if (!client.connected()) reconect();

    int num = (int)temp;
    char cstr[16];
    itoa(num, cstr, 10);
    
    client.publish(mqttTopicSub, cstr);  
    client.loop();
    delay(2000); 
}

bool is_wifi_connected(void)
{
  if(WiFi.status() == WL_CONNECTED) return true;
  else return false; 
}

long int get_rssi(void)
{
    if(is_wifi_connected()) return WiFi.RSSI();
    else return 0;
}
