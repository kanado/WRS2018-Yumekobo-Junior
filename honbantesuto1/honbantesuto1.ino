#include <MsTimer2.h>
#include<Wire.h>
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


void Motor(char one, char twe, char three, char four, char five, char six) {
  Wire.beginTransmission(0x14 / 2);
  Wire.write(0x00 + one); //1ch
  Wire.write(0x00 + twe); //2ch
  Wire.write(0x00 + three); //3ch
  Wire.write(0x00 + four); //4ch
  Wire.write(0x00 + five); //5ch
  Wire.write(0x00 + six); //6ch
  Wire.write(0);//ダミー
  Wire.endTransmission();
  delay(2);
}
void setup() {
  pinMode(pingPinA, OUTPUT);
  pinMode(pingPinB, OUTPUT);
  pinMode(pingPinC, OUTPUT);
  pinMode(pingPinD, OUTPUT);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
/*Timerのプログラム*/
MsTimer2::set(50,front);
MsTimer2::set(50,back);
MsTimer2::set(50,right);
MsTimer2::set(50,left);
MsTimer2::start();
}

void front() {
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
}
void back(){ 
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
}
void right(){
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
}
void left(){

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
}
  //cmは前方
  //cm1は後方
  //cm2は右方
  //cm3は左方

void loop(){

  if (cm <= 20) {
    Motor(50, 0, 50, 0, 50, -50);
    delay(600);
    Motor( 0, 0, 0, 0, 0, 0);
    Serial.println("左折");
  }
  else
  {
    Serial.println("前進");
    Motor( 60, 0, 0, 0, -50, 0);
  }
  delay(100);
}
