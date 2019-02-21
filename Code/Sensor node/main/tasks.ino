
static uint8_t sys_status = 0; 
static uint8_t sleep_time = 1;  // em segundos

static uint8_t connection = 0;

#define ESP_SUCCESS     0
#define ESP_ERROR       1

void task_handle(void)
{
    sys_status = system_status_get();

    Serial.println(sys_status);
    switch(sys_status)
    {
        case 6:
          if(app_mqtt_init() == ESP_SUCCESS)
          { 
            app_mqtt_send_temp(app_temp_get());
            system_wifi_connection_tries_set(0);
          }
          else
          {
              connection = system_wifi_connection_tries_get();
              connection++;
              if(connection > 5)
              { 
                  connection = 6;
                  sleep_time = 10;       
              }
              system_wifi_connection_tries_set(connection);
          }
          sys_status = 0;
        break;

        default:
          sys_status++;
        break;  
    }

    if(sys_status > 10) sys_status = 0;

    system_status_set(sys_status);
    ESP.deepSleep(sleep_time * 1000000);
}
