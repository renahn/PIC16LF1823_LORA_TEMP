#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DEBUG

//informações da rede WIFI
const char* ssid = "Jiomar";                 //SSID da rede WIFI
const char* password =  "MARIM123";    //senha da rede wifi
 
//informações do broker MQTT - Verifique as informações geradas pelo CloudMQTT
const char* mqttServer = "m11.cloudmqtt.com";   //server
const char* mqttUser = "fagkuzua";              //user
const char* mqttPassword = "wqQvH-bBu4TH";      //password
const int mqttPort = 10077;                     //port
const char* mqttTopicSub ="JUNIOR/TEMP/1";            //tópico que sera assinado
const char* mqttTopicSub2 ="casa/L2";            //tópico que sera assinado
 

WiFiClient espClient;
PubSubClient client(espClient);


void app_mqtt_init(void)
{
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef DEBUG
    Serial.println("Conectando ao WiFi..");
    #endif
  }
  #ifdef DEBUG
  Serial.println("Conectado na rede WiFi");
  #endif
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    #ifdef DEBUG
    Serial.println("Conectando ao Broker MQTT...");
    #endif
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      #ifdef DEBUG
      Serial.println("Conectado");  
      #endif
 
    } else {
      #ifdef DEBUG 
      Serial.print("falha estado  ");
      Serial.print(client.state());
      #endif
      delay(2000);
 
    }
  }
 
  //subscreve no tópico
  client.subscribe(mqttTopicSub);
   client.subscribe(mqttTopicSub2);
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
    if (!client.connected()) return;
    
    client.publish(mqttTopicSub, "TESTE");  
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
