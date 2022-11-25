RTC_DATA_ATTR int contador = 0; //contador se gurada en la memoria
#define Factor 1000000 // factor de conversion s a us
#define tiempo_mimir 5 // tiempo que ESP32 duerme
#define led 14
#define boton 33

void setup(){
  Serial.begin(115200);
  delay(1000);
  pinMode(led,OUTPUT);

  contador++;
  Serial.println("Numero de veces iniciado: " + String(contador));

  print_wakeup_reason();
  
  // configuracion light sleep
  esp_sleep_enable_ext0_wakeup((gpio_num_t)boton,HIGH);
  esp_sleep_enable_timer_wakeup(tiempo_mimir*Factor);
  Serial.println("Configuramos ESP32 para dormir por" + String(tiempo_mimir) + "segundos");

  Serial.println("ESP32 a dormir");
  esp_deep_sleep_start();
  Serial.println("Esta linea no se imprimirá");
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