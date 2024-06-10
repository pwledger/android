#include <SoftwareSerial.h>            //라이브러리 추가(기본라이브러리)
#include <TinyGPS.h>                //라이브러리 추가 필요
         
// Arduino에서 GPS와 통신하기 위해 사용할 핀을 정의합니다. 
// 이 경우 GPS 모듈의 TX 핀이 Arduino의 RXPIN(핀 3)에 연결됩니다.
#define RXPIN 2
#define TXPIN 3
//이 값을 GPS의 보드 속도와 동일하게 설정합니다.
#define GPSBAUD 9600
 
// TinyGPS 개체의 인스턴스 생성
TinyGPS gps;
// 위에서 정의한 핀으로 NewSoftSerial 라이브러리 초기화
SoftwareSerial uart_gps(RXPIN, TXPIN);
 
// 여기서 TinyGPS 라이브러리를 사용할 기능의 프로토타입을 선언합니다.
void getgps(TinyGPS &gps);
 
// 설정 기능에서는 두 개의 직렬 포트를 초기화해야 합니다. 
// 터미널 프로그램과 통신하려면 표준 하드웨어 직렬 포트(시리얼())를 초기화해야 합니다. 
void setup()
{
  //통신속도 9600 속도를 더느리게 하면 오류가 날 수 있습니다.
  Serial.begin(9600);    
  //GPS의 보드 속도를 설정합니다.
  uart_gps.begin(GPSBAUD);
  
  Serial.println("");
  Serial.println("WaveShare NEO 6M/7M GPS Module TEST");
  Serial.println("       ...waiting for Data...           ");
  Serial.println("");
}
void loop()
{
  while(uart_gps.available())     // GPS모듈에서 신호가 수신 될 경우
  {
      int c = uart_gps.read();    // 변수에 데이터를 저장
      if(gps.encode(c))              // 새로운 문장이 있다면
      {
        getgps(gps);                 // 데이터를 수집
      }   
  }
}
 
void getgps(TinyGPS &gps)
{
  // 변수정의
  float latitude, longitude;
  // 기능호출
  gps.f_get_position(&latitude, &longitude);
  // 위도(latitude)경도(longitude )출력 가능상태
  Serial.print("Lat/Long: "); 
  Serial.print(latitude,5); 
  Serial.print(", "); 
  Serial.println(longitude,5);
  
  // 날짜랑 시간 데이터도 동일한 포멧입니다.
  int year;
  byte month, day, hour, minute, second, hundredths;
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  Serial.print("Date: "); Serial.print(month, DEC); Serial.print("/"); 
  Serial.print(day, DEC); Serial.print("/"); Serial.print(year);
  Serial.print("  Time: "); Serial.print(hour, DEC); Serial.print(":"); 
  Serial.print(minute, DEC); Serial.print(":"); Serial.print(second, DEC); 
  Serial.print("."); Serial.println(hundredths, DEC);
  
  // 여기서 고도와 코스 값을 직접 인쇄할 수 있습니다
  Serial.print("Altitude (meters): "); Serial.println(gps.f_altitude());  
  Serial.print("Course (degrees): "); Serial.println(gps.f_course()); 
  Serial.print("Speed(kmph): "); Serial.println(gps.f_speed_kmph());
  Serial.println();
  
  // 여기서 문장에 대한 통계를 인쇄할 수 있습니다.
  unsigned long chars;
  unsigned short sentences, failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum);
  //Serial.print("Failed Checksums: ");Serial.print(failed_checksum);
  //Serial.println(); Serial.println();
  delay(1000);
}