#define Factor 1000000 // factor de conversion s a us
#define tiempo_mimir 5 // tiempo que ESP32 duerme
#define led 14

void setup(){
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  
  // configuracion light sleep
  esp_sleep_enable_timer_wakeup(tiempo_mimir*Factor);
  Serial.println("Configuramos ESP32 para dormir por" + String(tiempo_mimir) + "segundos");
  
}

void loop(){
  digitalWrite(led, LOW);
  esp_light_sleep_start();

  digitalWrite(led,HIGH);
  delay(500);
  
  print_wakeup_reason();
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Inicia por señal RTC_IO (Perifericos del RTC)");
    break;
      
    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("Inicia por señal RTC_CNTL");
    break;

    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Inicia por señal de un timer");
    break;

    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("Inicia por señal en un pin touch");
    break;

    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("Inicia por señal lanzada por ulp");
    break;

    default:
        Serial.printf("EL inicio no es causado por alguna razon conocida: %d\n", wakeup_reason); // %d\n", wakeup_reason
     
      
  }
  
}