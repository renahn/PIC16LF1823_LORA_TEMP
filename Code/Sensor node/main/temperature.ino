#include <MAX6675_Thermocouple.h>

#define SCK_PIN 14
#define CS_PIN  2
#define SO_PIN  13

MAX6675_Thermocouple* thermocouple = NULL;

void app_temp_init(void)
{
    thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);
}

uint16_t app_temp_get(void)
{
    double temp = thermocouple->readCelsius();
    
    Serial.print("C = "); 
    Serial.println(temp);

    return temp;
}
