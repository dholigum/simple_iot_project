#include <FirebaseArduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "simpledht11.firebaseio.com"  // Ganti dengan nama firebase lo
#define WIFI_SSID "namawaifulo"                     // Ganti dengan nama WaiFu lo
#define WIFI_PASSWORD "passwordwaifulo"             // Ganti dengan password WaiFu lo
#define DHTPIN 14                                   // Data pin untuk DHT11 ,ingat: pin D5 NodeMCU adalah no. 14
#define DHTTYPE DHT11                               // Pilih tipe DHT, disini gw make DHT11

DHT dht(DHTPIN, DHTTYPE);                           // Deklarasi I/O DHT11, pin sama tipe DHTnya

void setup() {
  Serial.begin(9600);                               // Deklarasi serial monitor
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);            // Konek ke WaiFu lo
  while (WiFi.status() != WL_CONNECTED) {           // Selama WaiFu lo belom konek maka di serial monitor
    delay(500);                                     // akan nampilin "."
    Serial.print(".");
  }
  dht.begin();                                      // Konek ke DHT
  Serial.println ("");
  Serial.println ("WiFi Connected!");               // Tulisan kalo udah konek ke WaiFu
  Firebase.begin(FIREBASE_HOST);                    // Konek ke akun firebase lo
  
}
void loop() {
  float h = dht.readHumidity();                     // Ngambil data kelembaban (%)
  float t = dht.readTemperature();                  // Ngambil data temperature (default: Celcius)
    
  Serial.print("Humidity: ");                       // Nampilin data kelembaban sama temperature ke 
  Serial.print(h);                                  // serial monitor lo
  Serial.print(" %, Temp: ");
  Serial.print(t);
  Serial.println(" Celsius");
  
  Firebase.setFloat("Temperature",t);               // Ngirim data temperature ke firebase lo
  Firebase.setFloat("Humidity",h);                  // Ngirim data kelembaban ke firebase lo
  delay(1000);                                      // Delay waktu tiap pengiriman data ke firebase lo
}
