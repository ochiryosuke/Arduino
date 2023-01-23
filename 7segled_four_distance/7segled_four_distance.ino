//シフトレジスタにつながっているデジタルピン
const int RCLK = 11; //ST_CP
const int SRCLK = 9; //SH_CP
const int DS = 12; //SER

//超音波センサのピン
const int TrigPin=4;
const int EchoPin=3;

float Echotime = 0.0f;//echoピンがHIGHになった時間を格納用
float d=0.0f;//距離

//7セグの桁選択のデジタルピン
const int dig1 = 8;
const int dig2 = 7;
const int dig3 = 6;
const int dig4 = 13;

//配列の大きさ
const int a_size=12;

//ダイナミック点灯用待ち時間変数
const int delaytime=2;

int data1 = 0;
int data2 = 0;
float data3 = 0;
float data4 = 0;

//光らせるパターンのbyte
//Bの8bitは各bit 7セグのa b c e d e f g DPに対応

byte temp_array[a_size] = {
  B11111100,//0
  B01100000,//1
  B11011010,//2
  B11110010,//3
  B01100110,//4
  B10110110,//5
  B10111110,//6
  B11100100,//7
  B11111110,//8
  B11100110,//9
  B00000001,//小数点
  B00000000 //消灯
};

void shiftdata(int x)
{
  digitalWrite(RCLK, LOW);//送信中のRCLKをLowにする
  shiftOut(DS, SRCLK, LSBFIRST, temp_array[x]);//シフト演算を使って点灯するLEDを選択
  digitalWrite(RCLK, HIGH);//送信終了後RCLKをHighにする
}

void setup() {
  Serial.begin(9600);
  
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);

  //シフトレジスタ
  pinMode(RCLK,OUTPUT);
  pinMode(DS,OUTPUT);
  pinMode(SRCLK,OUTPUT);

  pinMode(dig1,OUTPUT);
  pinMode(dig2,OUTPUT);
  pinMode(dig3,OUTPUT);
  pinMode(dig4,OUTPUT);

  //HIGHで桁選択しない状態
  digitalWrite(dig1,HIGH);
  digitalWrite(dig2,HIGH);
  digitalWrite(dig3,HIGH);
  digitalWrite(dig4,HIGH);
}

void loop() {
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(10);

  //計測のためにトリガ信号生成
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);

  //echoピンのHIGHになってる時間を得る
  Echotime = pulseIn(EchoPin,HIGH);

  //時間が0よりも大きいとき
    if(Echotime > 0){

      //距離[m]=音速(340) * EchoがHIGHレベルの時間 / 2(往復分なので割る) 
      d = 340 * Echotime / 2;
      
      d /= 10000; 
      Serial.print("距離:");
      Serial.println(d);

      //Serial.print("echotime");
      //Serial.print(Echotime);
      //Serial.println("マイクロ秒");
    }
    delay(delaytime);

  //整数部分が二桁なら
  if(10.00 <= d && d <= 99.99){
    data1 = d / 10;
    delay(delaytime);
    
    digitalWrite(dig1,LOW);
    digitalWrite(dig2,HIGH);
    digitalWrite(dig3,HIGH);
    digitalWrite(dig4,HIGH);
 
    shiftdata(data1);
    delay(delaytime);
    shiftdata(11);
     
    data2 = fmod(d,10);
    delay(delaytime);
  
    digitalWrite(dig1,HIGH);
    digitalWrite(dig2,LOW);
    digitalWrite(dig3,HIGH);
    digitalWrite(dig4,HIGH);

    bitSet(temp_array[data2],0);//DPのビットを立てる
    shiftdata(data2);
    delay(delaytime);
    bitClear(temp_array[data2],0);//DPのビットを下ろす
    shiftdata(11);
  
    data3 = d - float(data1 * 10 + data2);
    data3 *= 10;
    delay(delaytime);
    
    digitalWrite(dig1,HIGH);
    digitalWrite(dig2,HIGH);
    digitalWrite(dig3,LOW);
    digitalWrite(dig4,HIGH);

    shiftdata(data3);
    delay(delaytime);
    shiftdata(11);

    data4 = data3*10 - int(data3*10);
    data4 *= 10;
    delay(delaytime);

    digitalWrite(dig1,HIGH);
    digitalWrite(dig2,HIGH);
    digitalWrite(dig3,HIGH);
    digitalWrite(dig4,LOW);

    shiftdata(data4);
    delay(delaytime);
    shiftdata(11);    
  }else if(2.0 <= d && d < 10.00){//整数部分が一桁のとき
    
    data1 = 0;
    delay(delaytime);
    
    digitalWrite(dig1,LOW);
    digitalWrite(dig2,HIGH);
    digitalWrite(dig3,HIGH);
    digitalWrite(dig4,HIGH);
 
    shiftdata(data1);
    delay(delaytime);
    shiftdata(11);

    data2 = int(d);
    delay(delaytime);
    
    digitalWrite(dig1,HIGH);
    digitalWrite(dig2,LOW);
    digitalWrite(dig3,HIGH);
    digitalWrite(dig4,HIGH);

    bitSet(temp_array[data2],0);//DPのビットを立てる
    shiftdata(data2);
    bitClear(temp_array[data2],0);//DPのビットを下ろす
    delay(delaytime);
    shiftdata(11);


    data3 = d - data2;
    data3 *= 10;
    delay(delaytime);
    
    digitalWrite(dig1,HIGH);
    digitalWrite(dig2,HIGH);
    digitalWrite(dig3,LOW);
    digitalWrite(dig4,HIGH);
 
    shiftdata(data3);
    delay(delaytime);
    shiftdata(11);

    data4 = (data2 + data3) - d;
    delay(delaytime);
    
    digitalWrite(dig1,HIGH);
    digitalWrite(dig2,HIGH);
    digitalWrite(dig3,HIGH);
    digitalWrite(dig4,LOW);
 
    shiftdata(data4);
    delay(delaytime);
    shiftdata(11);
  }
}
