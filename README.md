# ゴミ箱 (ゴミ総量お知らせシステム)

Arduino Uno R3 (予定) 割り込みピンは2,3番ピン

超音波センサ: HR-SR04

光センサ: cds 5mm版?

ブザー: パッシブブザー

仮の回路図

![ゴミ箱仮回路](https://github.com/ochiryosuke/Arduino/assets/108120560/27ddeb55-6f2e-4b3f-970d-1d0778c453c5)


回路シュミレーション

https://www.tinkercad.com/things/ewQd3EKqwq2-/editel?sharecode=NqYq7NcnvWMgjdA9b8kittQfPWN3YIP-8VhoYHqJw1Y


プロトタイプのフローチャート(プログラム)
![ゴミ箱流れ図(仮) drawio (1)](https://github.com/ochiryosuke/Arduino/assets/108120560/3a08d309-a8d9-4d47-af9f-730e7f796325)

  *ソースコード(スケッチ)はpolling_garbagebox_v1フォルダ内です*


**シリアルモニタではなく7セグメントLEDに距離[cm]を表示する**

  *ソースコード 7segled_four_distanceフォルダ内です*

**ブザーを使ってシャトルランの音を再現した例**

  *ソースコード buzzerフォルダ内です*
