

// Lembrar de colocar Flash Mode em DIO para o pino 10 funcionar como entrada

void botao_init(void)
{
    pinMode(10,INPUT);
}


void botao_handle(void)
{
    uint8_t counter = 0;
  
    while(!digitalRead(10))
    {
        delay(100);
        counter++;
        Serial.println(counter);
    } 

    if(counter == 0) return;
    else if(counter>0 && counter<20) Serial.println("botao menor que 2 segundos");
    else if(counter>0 && counter<50) Serial.println("botao menor que 5 segundos");
     
}
