long randNumber;
#include <Wire.h>
const int pingPinA = 9;
const int pingPinB = 7;
const int pingPinC = 13;
const int pingPinD = 11;

unsigned long durationA;
int cm;
unsigned long durationB;
int cm1;
unsigned long durationC;
int cm2;
unsigned long durationD;
int cm3;
void setup() {
  pinMode(pingPinA, OUTPUT);
  pinMode(pingPinB, OUTPUT);
  pinMode(pingPinC, OUTPUT);
  pinMode(pingPinD, OUTPUT);
  Serial.begin(9600);
  Wire.begin(); // join i2c bus

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}
void Motor(char one, char two, char three, char four, char five, char six) {
  Wire.beginTransmission(0x14 / 2);
  Wire.write(0x00 + one); // 1ch
  Wire.write(0x00 + two); // 2ch
  Wire.write(0x00 + three); // 3ch
  Wire.write(0x00 + four); // 4ch
  Wire.write(0x00 + five); // 5ch
  Wire.write(0x00 + six); // 6ch : 0 しかダメ
  Wire.write(0); // ダミー
  Wire.endTransmission();
  delay(2); // このディレーがないと連続稼動せずハングアップ
}

void loop() {
  // print a random number from 10 to 19
  randNumber = random(10, 15);
  Serial.println(randNumber);

  delay(2000);
  /* シリアルを受け取ったとき */
  if (Serial.available() > 0) {
    /* ;まで読み込む */
    String val = Serial.readStringUntil(';');

    if (val == "panda") {
      /* パンダがいたとき */
      Motor( 0, 0, 0, 0, 0, 0);
    }
    else if (val == "panda-no") {
      /*パンダがいないとき*/
      //pingPin
      //ピンをOUTPUTに設定（パルス送信のため）
      pinMode(pingPinA, OUTPUT);
      //LOWパルスを送信
      digitalWrite(pingPinA, LOW);
      delayMicroseconds(2);
      //HIGHパルスを送信
      digitalWrite(pingPinA, HIGH);
      //5uSパルスを送信してPingSensorを起動
      delayMicroseconds(5);
      digitalWrite(pingPinA, LOW);

      //入力パルスを読み取るためにデジタルピンをINPUTに変更（シグナルピンを入力に切り替え）
      pinMode(pingPinA, INPUT);

      //入力パルスの長さを測定
      durationA = pulseIn(pingPinA, HIGH);

      //パルスの長さを半分に分割
      durationA = durationA / 2;
      //cmに変換
      cm = int(durationA / 29);
      Serial.println("");
      Serial.println("前方");
      Serial.print(cm);
      Serial.println("cm");
      //pinPin1
      //ピンをOUTPUTに設定（パルス送信のため）
      pinMode(pingPinB, OUTPUT);
      //LOWパルスを送信
      digitalWrite(pingPinB, LOW);
      delayMicroseconds(2);
      //HIGHパルスを送信
      digitalWrite(pingPinB, HIGH);
      //5uSパルスを送信してPingSensorを起動
      delayMicroseconds(5);
      digitalWrite(pingPinB, LOW);

      //入力パルスを読み取るためにデジタルピンをINPUTに変更（シグナルピンを入力に切り替え）
      pinMode(pingPinB, INPUT);

      //入力パルスの長さを測定
      durationB = pulseIn(pingPinB, HIGH);

      //パルスの長さを半分に分割
      durationB = durationB / 2;
      //cmに変換
      cm1 = int(durationB / 29);
      Serial.println();
      Serial.println("後方");
      Serial.print(cm1);
      Serial.println("cm");


      //pingPin2
      //ピンをOUTPUTに設定（パルス送信のため）
      pinMode(pingPinC, OUTPUT);
      //LOWパルスを送信
      digitalWrite(pingPinC, LOW);
      delayMicroseconds(2);
      //HIGHパルスを送信
      digitalWrite(pingPinC, HIGH);
      //5uSパルスを送信してPingSensorを起動
      delayMicroseconds(5);
      digitalWrite(pingPinC, LOW);

      //入力パルスを読み取るためにデジタルピンをINPUTに変更（シグナルピンを入力に切り替え）
      pinMode(pingPinC, INPUT);

      //入力パルスの長さを測定
      durationC = pulseIn(pingPinC, HIGH);

      //パルスの長さを半分に分割
      durationC = durationC / 2;
      //cmに変換
      cm2 = int(durationC / 29);
      Serial.println();
      Serial.println("右方");
      Serial.print(cm2);
      Serial.println("cm");

      //pingPin3
      //ピンをOUTPUTに設定（パルス送信のため）
      pinMode(pingPinD, OUTPUT);
      //LOWパルスを送信
      digitalWrite(pingPinD, LOW);
      delayMicroseconds(2);
      //HIGHパルスを送信
      digitalWrite(pingPinD, HIGH);
      //5uSパルスを送信してPingSensorを起動
      delayMicroseconds(5);
      digitalWrite(pingPinD, LOW);

      //入力パルスを読み取るためにデジタルピンをINPUTに変更（シグナルピンを入力に切り替え）
      pinMode(pingPinD, INPUT);

      //入力パルスの長さを測定
      durationD = pulseIn(pingPinD, HIGH);

      //パルスの長さを半分に分割
      durationD = durationD / 2;
      cm3 = int(durationD / 29);
      //cmに変換
      Serial.println();
      Serial.println("左方");
      Serial.print(cm3);
      Serial.println("cm");
      Serial.println();
      Serial.println();
      //cmは前方
      //cm1は後方
      //cm2は右方
      //cm3は左方
      //前
      if (cm <= 30 ) {
        Motor(-50, 0, 0, 0, 50, 0);
      }
      //後ろ
      else if (cm1 <= 30 ) {
        Motor(50, 0, 0, 0, -50, 0);
      }
      //右
      else if (cm2 <= 30 ) {
        Motor(0, 0, 50, 0, 0, 50);
      }
      //左
      else if (cm3 <= 30) {
        Motor(0, 0, -50, 0, 0, -50);
      }
      else {
        if (randNumber == 10) {
          Motor(50, 0, 0, 0, -50, 0);
          Serial.print("\t10A\n");
        }
        else if (randNumber == 11) {
          Motor(-50, 0, 0, 0, 50, 0);
          Serial.print("\t11B\n");
        }
        else if (randNumber == 12) {
          Motor(0, 0, 50, 0, 0, 50);
          Serial.print("\t12C\n");
        }
        else if (randNumber == 13) {

          Serial.print("\t13D\n");
        }
        else if (randNumber == 14) {
          Motor(0, 0, -50, 0, 0, -50);
          Serial.print("\t14E\n");
        }
        delay(500);
        /* それ以外だった時 */
      }
    }
  }
}
