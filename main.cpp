#include <Arduino.h>


#define led_pin          2              //GPIO
#define TIME_TO_LedBlink 500            //tempo para blink do LED    [ms]
#define TIME_TO_WAKEUPms 2000           //tempo para o ESP "acordar" [ms]
#define TIME_TO_SLEEPms  5000           //tempo para o ESP "dormir"  [ms]
#define uS_TO_MS_FACTOR  1000           //fator de conversao --> us para ms


//define funcao para inversao do estado do led
#define LED_INVERT digitalWrite(led_pin, !digitalRead(led_pin));  



short int loop_count_led = 0x00;        //variavel auxiliar para inversao do led
short int loop_count_sleep_aux = 0x00;  //variavel auxiliar para contagem do modo deepsleep


void setup(){

  Serial.begin(115200);                        //serial em 115200
  pinMode(led_pin, OUTPUT);                    //configura GPIO como saida
  digitalWrite(led_pin, LOW);                  //inicia com led desligado


  //habilita fonte de wake up a partir de um timer
  // (neste caso esta sendo configurado com 5s)
  esp_sleep_enable_timer_wakeup(TIME_TO_WAKEUPms * uS_TO_MS_FACTOR);


  Serial.println("Iniciando ESP32");           //debug
}

void loop(){

  loop_count_led++;                            //incrementa *teoricamente* 1000x/segundo
  loop_count_sleep_aux++;                      //incrementa *teoricamente* 1000x/segundo

  if(loop_count_led >= TIME_TO_LedBlink){      //caso tenha atingido o tempo determinado...
    loop_count_led = 0x00;                     //reseta contagem
    LED_INVERT;                                //inverte estado do led
  }

  if(loop_count_sleep_aux >= TIME_TO_SLEEPms){ //caso contagem tenha atingido o tempo determinado...
    Serial.println("Entrando em DeepSleep");   //debug
    esp_deep_sleep_start();                    //esp entra em modo deepsleep
                                               //** led para de piscar **
  }

  delay(1);
}



