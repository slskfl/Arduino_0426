#include <SoftwareSerial.h>     //스케치<라이브러리 SoftwareSerial연결(블루투스)
                                
SoftwareSerial BTSerial(2,3);   //[변수만들기] 블루투스 모듈과 교차하여 연결(2-RX,3-TX) 

void setup() {
  Serial.begin(9600); //시리얼 통신 초기화
  BTSerial.begin(9600);
}

void loop() {
  // 블루투스 모듈 ->아두이노 -> 시리얼 모니터 통신 확인
  
  //통신이 잘 되었을 경우
  if(BTSerial.available()){   
      Serial.write(BTSerial.read());
    
  }
  // 시리얼 모니터  ->아두이노 -> 블루투스 모듈
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
}
