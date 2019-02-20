#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
Adafruit_PCD8544 display = Adafruit_PCD8544(14, 12, 5, 4, 0);

void app_display_init(void)
{
    display.begin();
    display.setContrast(40);
    display.clearDisplay();  

    //pinMode(9, OUTPUT);
    //digitalWrite(9, HIGH);
}


  

void app_display_temperature(void)
{
  static uint16_t temp = 312;

  temp = app_temp_get();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println(" TEMPERATURA");
  display.setCursor(8,15);
  display.setTextSize(4);
  display.setTextColor(BLACK);
  display.println(temp, DEC);
  display.display();
  //delay(2000);

  app_mqtt_send_temp(temp);
}

void app_display_connection(void)
{
    long int rssi = get_rssi();
  
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0,0);
    if(is_wifi_connected()) display.println(" Conectado");
    else display.println("Desconectado");
    display.setCursor(8,15);
    display.setTextSize(4);
    display.setTextColor(BLACK);
    display.println(rssi, DEC);
    display.display();

    app_mqtt_send_temp(10);
}
