//#include <SPI.h>


static int mili;

int value;

void setup()   
{
  Serial.begin(9600);
  Serial.println("Comecei");
 

  //system_init();    // nao tirar
  botao_init();
  botao_handle();
  ESP.deepSleep(1 * 1000000);
  //app_temp_init();
  //app_display_init();
  
  //system_set_first_time(false);

  //task_handle();
  
  //app_display_temperature();
  //app_mqtt_init(); 
}


void loop() 
{    
    //app_lora_loop();
    //app_display_init();
    //app_mqtt_loop();
    
    //if((millis()-mili)>2000)
    //{
      //mili = millis();
      //app_display_temperature(); 
      //delay(2000);
      //Serial.println("Running");
      //app_display_connection();
    //}  
}
