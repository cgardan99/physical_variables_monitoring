

#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 4
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
// Pin digital del sensor de vibración
#define vs 5
// Definimos el pin digital donde se conecta el sensor de movimiento
#define MOVSENS 15
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "Totalplay-119C";
const char *pwd = "jamonensalsademiel8";
const char *servidor = "http://ec2-3-19-28-45.us-east-2.compute.amazonaws.com:3050/add";
const char *servidor_mov = "http://ec2-3-19-28-45.us-east-2.compute.amazonaws.com:3050/movimiento";
String payload = "";
int valor;
long measurement;
TaskHandle_t Task1;


void Task1code( void * parameter) {
  for(;;){
      valor = digitalRead(MOVSENS);
      if (valor != HIGH) {
        if(WiFi.status()== WL_CONNECTED){
          HTTPClient http;
          // Your Domain name with URL path or IP address with path
          http.begin(servidor_mov);
          
          // Specify content-type header
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");
         
          int httpResponseCode = http.POST(payload);
         
          Serial.print("Movimiento, Codigo de respuesta: ");
          Serial.println(httpResponseCode);
            
          // Free resources
          http.end();
          payload = "";
        }
        else {
          Serial.println("WiFi Disconnected");
        }
       delay(200);
      }
  }

}

void setup(){
Serial.begin(115200);  
WiFi.begin(ssid, pwd);

while(WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi...");
}

Serial.println("Conectado a la red WiFi");
Serial.println(WiFi.localIP());

// Comenzamos el sensor DHT
  dht.begin();
  //Inicializa Serial a 115200 baudios
 Serial.println("Iniciando ...");

  pinMode(MOVSENS, INPUT);

  xTaskCreatePinnedToCore(
      Task1code, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &Task1,  /* Task handle. */
      1);
}

long vibration(){
  long measurement=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}

 
void loop()
{      
   Serial.println("Censando...");
   delay(50);
   // Leemos la humedad relativa
   float h = dht.readHumidity();
   // Leemos la temperatura en grados centígrados (por defecto)
   float t = dht.readTemperature();
   long v = vibration();
   
   delay(50);
   if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      // Your Domain name with URL path or IP address with path
      http.begin(servidor);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST

      payload.concat("humedad=");
      payload.concat(h);
      payload.concat("&temperatura=");
      payload.concat(t);
      payload.concat("&vibraciones=");
      payload.concat(v);
     
      int httpResponseCode = http.POST(payload);
     
      Serial.print("Codigo de respuesta: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
      payload = "";
    }
    else {
      Serial.println("WiFi Disconnected");
    }
   delay(60000);
}
