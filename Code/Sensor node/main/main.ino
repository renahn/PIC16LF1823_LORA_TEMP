/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>


void setup()   
{
  Serial.begin(9600);
  Serial.println("Comecei");

  app_temp_init();
  app_display_init();
  
  //app_display_temperature();
  app_mqtt_init();

  //app_lora_init();
}

int mili = 0;

void loop() 
{
    //app_lora_loop();
    //app_display_init();
    app_mqtt_loop();
    
    if((millis()-mili)>2000)
    {
      mili = millis();
      app_display_temperature(); 
      delay(2000);
      Serial.println("Running");
      //app_display_connection();
    }  
}
