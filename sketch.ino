    #include <WiFi.h>
    #include <HTTPClient.h>

    long tempoAnterior = 0; 
    long tempoAnterior2 = 0;
    long tempoAnterior3 = 0;
    long tempoAnterior4 = 0;
    long tempo = 1000;  
    long tempo2 = 3000;
    long tempo3= 2000;
    long tempo4= 5000;
    unsigned long ultimoDebounce = 0;
    unsigned long debounceDelay = 200;
    unsigned long ultimoPressionado = 0;

    #define led_azul 9 // Pino utilizado para controle do led azul
    #define led_verde 2 // Pino utilizado para controle do led verda
    #define led_vermelho 40 // Pino utilizado para controle do led vermelho
    #define led_amarelo 9 // Pino utilizado para controle do led azul


    const int botaoPino = 18;  // número do pino do botão


    const int ldrPino = 4;  // número do pino em que o ldr está conectado
    int threshold=600;

    void setup() {
      Serial.begin(9600);
      Serial.print("Conectando-se ao Wi-Fi");
      WiFi.begin("Wokwi-GUEST", "", 6);
      while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
    Serial.println(" Conectado!");

      // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
      pinMode(led_azul,OUTPUT);
      pinMode(led_verde,OUTPUT);
      pinMode(led_vermelho,OUTPUT);
      pinMode(led_amarelo, OUTPUT);

      // Inicialização das entradas
      pinMode(botaoPino, INPUT); //  inicializa o botão como input
      pinMode(ldrPino, INPUT);

      digitalWrite(led_azul, LOW);
      digitalWrite(led_verde, LOW);
      digitalWrite(led_vermelho, LOW);
      digitalWrite(led_amarelo, LOW);

    
  }

      // Verifica estado do botão
      int main () {
      unsigned long tempoAtual = millis();
          int estadoBotao = digitalRead(botaoPino);

          // Controle do botão
          if (estadoBotao == LOW); { // Botão pressionado
              if (tempoAtual - ultimoDebounce > debounceDelay); {
                  ultimoDebounce = tempoAtual;
                  ultimoPressionado = tempoAtual; // Atualiza o tempo da última interação do botão
              }
          }
      }

      int wifi (){
      if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
        HTTPClient http;

        String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

        http.begin(serverPath.c_str());

        int httpRequisicao = http.GET(); // Código do Resultado da Requisição HTTP

        if (httpRequisicao>0) {
          Serial.print("HTTP Response do código: ");
          Serial.println(httpRequisicao);
          String payload = http.getString();
          Serial.println(payload);
          }
        else {
          Serial.print("Erro do código: ");
          Serial.println(httpRequisicao);
          }
          http.end();
        }

      else {
        Serial.println("WiFi desconectado");
      }
    }


    void loop() {
      int estadoBotao = digitalRead(botaoPino);
      int ldrstatus=analogRead(ldrPino);
      Serial.println(ldrstatus);

      if(ldrstatus<=threshold){
        Serial.println("Está escuro, led ligado");
        if (millis() >= tempoAnterior + tempo) {
        tempoAnterior = millis(); 
        digitalWrite(led_amarelo, !digitalRead(led_amarelo));
      }
        Serial.println(ldrstatus);

      }else{
        digitalWrite(led_amarelo, LOW);
        Serial.println("Está claro, led amarelo desligado");
        if (millis() >= tempoAnterior2 + tempo2) {
        tempoAnterior2 = millis(); 
        digitalWrite(led_verde, !digitalRead(led_verde));
        } else {
          digitalWrite(led_verde, LOW);
          if (millis() >= tempoAnterior3 + tempo3) {
          tempoAnterior3 = millis(); 
          digitalWrite(led_amarelo, !digitalRead(led_amarelo));
          } else {
            digitalWrite(led_amarelo, LOW);
            if (millis() >= tempoAnterior4 + tempo4) {
            tempoAnterior4 = millis(); 
            digitalWrite(led_vermelho, !digitalRead(led_vermelho));
          }
                }
        }
      }

      if ((millis() >= tempoAnterior4 + tempo4) && (estadoBotao == LOW)){
      tempoAnterior4 = millis();
      digitalWrite(led_verde, HIGH); 
        digitalWrite(led_amarelo, LOW);
        digitalWrite(led_vermelho, LOW);
      }

      if ((millis() >= tempoAnterior4 + tempo4) && 3*(estadoBotao == LOW)){
        tempoAnterior4 = millis();
      }
    }