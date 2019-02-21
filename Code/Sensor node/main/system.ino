#include <EEPROM.h>

#define FIRST_TIME      187
#define FIRST_TIME_ADDR 0

#define STATUS_ADDR     1

#define WIFI_CONNECT_TRIES_ADDR 2

void system_init(void)
{
    EEPROM.begin(20);
}

void system_set_first_time(bool first_time)
{
    if(first_time)
    {
        EEPROM.write(FIRST_TIME_ADDR, 0);     
        system_status_set(0);
        system_wifi_connection_tries_set(0);
    }
    else EEPROM.write(FIRST_TIME_ADDR, FIRST_TIME);

    EEPROM.commit();  
}

bool is_first_time(void)
{
    uint8_t value = EEPROM.read(FIRST_TIME_ADDR);

    if(value == FIRST_TIME) return false;
    else return true;
}

uint8_t system_status_get(void)
{
    return EEPROM.read(STATUS_ADDR);       
}

void system_status_set(uint8_t value)
{
    EEPROM.write(STATUS_ADDR, value);
    EEPROM.commit();      
}

uint8_t system_wifi_connection_tries_get(void)
{
    return EEPROM.read(WIFI_CONNECT_TRIES_ADDR); 
}

void system_wifi_connection_tries_set(uint8_t value)
{
    EEPROM.write(WIFI_CONNECT_TRIES_ADDR, value);
    EEPROM.commit();
}
