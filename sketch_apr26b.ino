#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3);
int button[]={8,9,10};
int led_pins[]={5,6,7};
boolean lastButton[]={LOW, LOW, LOW};// 이전 눌림 상태를 저장하는 변수
boolean currentButton[]={LOW, LOW, LOW};//현재 버튼 눌림 상태를 저장하는 변수
boolean button_state[3]; //버튼의 on/off여부

void setup() {
  for(int i=0; i<3; i++){ //버튼 입력으로 설정
    pinMode(button[i], INPUT);
    button_state[i]=false;
    pinMode(led_pins[i], OUTPUT);
  }
  Serial.begin(9600); //시리얼 초기화
  BTSerial.begin(9600); //블루투스 초기화
}

void loop() {
  for(int i=0; i<3; i++){
    currentButton[i]=deBounce(lastButton[i], i);//디바운싱 처리된 값을 읽어옴
    if(lastButton[i]==LOW & currentButton[i]==HIGH){
      //버튼을 누름>>상태값 전달
      button_state[i]=!button_state[i];
      digitalWrite(led_pins[i], button_state[i]);
      char message[4]="  \n"; //총 4글자에 신호 저장(3) + 마지막 신호
      message[0]=i+1+'0';
      message[1]=button_state[i]+'0';
      Serial.print(message);
      BTSerial.print(message); //블루투스로 폰에 데이터 전송
    }  
    lastButton[i]=currentButton[i]; //이전 버튼 값을 현재 버튼 값으로 변경
  }
}

//작동할 때가 있고, 작동하지 않을 때에도 있음
//스위치 디바운싱 함수
boolean deBounce(boolean last, int i){ //눌렀을 때 
  boolean current=digitalRead(button[i]);//현재 버튼 상태를 확인
  if(last!=current){
    //이전 버튼 상태와 현재 버튼 상태가 다름
    delay(5);//5ms 동안 기다림 (진동 잡음을 건너뛰기)
    current=digitalRead(button[i]); //현재 버튼 상태 저장
  }
  return current;
}
