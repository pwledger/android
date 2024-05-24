#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "esp8266firebase-b2b33-default-rtdb.firebaseio.com/" // 주소
#define FIREBASE_AUTH "1J8ghRNzyFzaONbt99xyGsXKUexqaUb9wvRhyhy8"           // 키
#define WIFI_SSID "coding"                                                 //학원 와이파이 이름
#define WIFI_PASSWORD  "coding12345"                                       //학원 비번

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID ,WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(" . ");
    delay(300);
  }
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
int cnt = 0;
void loop() {
  Firebase.setFloat(firebaseData , "/esp8266/count" , cnt++);
  delay(1000);

}
