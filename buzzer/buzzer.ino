//ライブラリの読み込み
#include "pitches.h"

//メロディーの配列(ドレミファソラシドの順になっている)
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6
};

//ピン
const uint8_t swPin = 4;
const uint8_t buzzerPin = 11;

//delaytime
int delaytime = 1050;

void setup(){

  //確認用にシリアルモニタを用いる
  Serial.begin(9600);

  //ピン設定
  pinMode(swPin,INPUT);
}

void loop(){
  
  //スイッチの状態を得る
  uint8_t swState = digitalRead(swPin);

  //スイッチが押されたら
  while(swState == LOW){

    //間隔が短すぎたらdelaytimeを初期化する。
    if(delaytime <= 10){
      delaytime = 1050;
      break;
    }

    for(size_t i = 0; i < sizeof(melody)/sizeof(melody[0]); i++){
      //memory配列から得た情報でパルス生成
      tone(buzzerPin, melody[i], 200);
      delay(delaytime);
    }

    delay(delaytime);
    Serial.println(String(delaytime));

    delaytime-=10;

    for(size_t i = sizeof(melody)/sizeof(melody[0]); i > 0; i--){
      //memory配列から得た情報でパルス生成
      tone(buzzerPin, melody[i], 200);
      delay(delaytime);
    }
    
  }
}
