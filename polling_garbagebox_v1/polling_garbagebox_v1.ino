#define Trig_pin 11 //超音波センサのトリガーピン
#define Echo_pin 10 //超音波センサのエコーピン
#define buzzer_pin 6 //ブザーのピン
#define cds_pin A0 //CDSのピン
#define close_value 200 //ゴミ箱の蓋がしまっているときの基準値

void setup() {
  //シリアルモニタの設定
  Serial.begin(9600);
  
  pinMode(Trig_pin,OUTPUT);
  pinMode(Echo_pin,INPUT);
}

void loop() {
  
    digitalWrite(Trig_pin,LOW);
    delayMicroseconds(10); //10マイクロ秒待つ

    //トリガーのパルスを作成する
    digitalWrite(Trig_pin,HIGH);
    delayMicroseconds(10); //10マイクロ秒待つ
    digitalWrite(Trig_pin,LOW);

    //エコーのハイパルスになっている時間を計測
    float echo_time = pulseIn(Echo_pin,HIGH);

    //分圧したときの電圧(1024階調での値)を取得
    int light = analogRead(cds_pin);
    
    //ハイパルスの時間が0より大きいなら計測できている。かつ周囲が暗いなら(蓋がしまっている状態に近いなら)
    if(echo_time > 0 && light <= close_value){
      float distance = 340 * echo_time / 2 / 1000.0; //距離を計算(音速*ハイパルスの時間/ 2 / 1000 [cmになおして往復分の半分にする])
      if(distance <= 45){
        tone(buzzer_pin,262,200); //ブザーを鳴らす
      }
      Serial.print(distance); //距離表示
      Serial.println("[cm]");
      delay(600); //0.6秒待つ
    }
}
