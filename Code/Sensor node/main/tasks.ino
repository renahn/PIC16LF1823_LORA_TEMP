
static uint8_t sys_status = 0; 
static uint8_t sleep_time = 1;  // em segundos



void task_handle(void)
{
    sys_status = system_status_get();

    Serial.println(sys_status);
    switch(sys_status)
    {
        case 6:
          app_mqtt_init();
          app_mqtt_send_temp(app_temp_get());
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
