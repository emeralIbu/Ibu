//7_4_19:40
//最終ソースコード

//投函がされていないときの処理
void no_posted(double aa){
 // Serial.println(aa);
  if(aa<20){
 //Serial.write('e');//庫内に物があるとき
    delay(10);
  }else if(aa>=21){
 // Serial.write('f');    //取り出された
   delay(10);
  }
}

const int SENSOR1 = 0; // 赤外線センサが接続されているピン(アナログ)
const int SENSOR2 = 1; // 赤外線センサが接続されているピン(アナログ)
int buffer1[21]; // バッファ
int buffer2[21]; // バッファ
int index1 = 0; // インデックス
int index2 = 0; // インデックス
const int buffer_length1 = 21;
const int buffer_length2 = 21; 
int count=0;
int size_a=0;
int en_posted=0;

void setup() {
 int i,j;
 for (i = 0; i < buffer_length1; i++) {
 buffer1[i] = 0; // バッファ初期化
 }for (j = 0; j< buffer_length2; j++) {
 buffer2[i] = 0; // バッファ初期化
 }
 Serial.begin(9600); // シリアル通信の速度を設定
 }
 void loop() {
 int i,j, v1,v2;
 long sum1,sum2;
 float v_out1,v_out2;
 double d1,d2;
 v1 = analogRead(SENSOR1); // センサの出力値を読み取る
 v2 = analogRead(SENSOR2); // センサの出力値を読み取る
 v_out1 =5.0*v1/1023;
 v_out2 =5.0*v2/1023;
 d1=26.549*pow(v_out1,-1.2091);
 d2=26.549*pow(v_out2,-1.2091);
 
 buffer1[index1] = d1;
 buffer2[index2] = d2;
 index1 = (index1 + 1) % buffer_length1; // バッファ長を超えたら 0 に
 index2 = (index2 + 1) % buffer_length2; // バッファ長を超えたら 0 に

 sum1 = 0;
 sum2 = 0;
 for (i = 0; i < buffer_length1; i++) {
 sum1 += buffer1[i];
 }
 for (j = 0; j < buffer_length2; j++) {
 sum2 += buffer2[j];
 }
 

 d1 = (int) (sum1 / buffer_length1); // バッファ内の全データの平均値を計算
 d2 = (int) (sum2 / buffer_length2); // バッファ内の全データの平均値を計算

Serial.println(d1);
//Serial.println(d2); // シリアル通信で値を送信

if((en_posted < 1) && (d1 < 10)){
  count=count+1 ;
  //Serial.println(count);     
}else if((count >= 40)|| (count > 0) && (d1 >= 10)){         
  en_posted = 1;
  size_a=count;
  count=0;
}

 if(en_posted > 0){
   if((size_a >= 3)&&(size_a < 10)){
     no_posted(d2); // small letter ?
//     Serial.write('a');
     delay(1000);
     en_posted = 0;
     size_a = 0;
   }else if((size_a >= 10)&&(size_a < 20)){
  //   Serial.write('b'); // letter
     delay(1000);
     en_posted = 0;
     size_a = 0;
   }else if((size_a >= 20)&&(size_a < 30)){
     //Serial.write('c'); // flyer
     delay(1000);
    en_posted = 0;
    size_a = 0;
   }else if(size_a >=30){
    //Serial.write('d') ;// full
    delay(1000);
    en_posted = 0;
    size_a = 0;
  }
}else {
  no_posted(d2); // no Enter
}
delay(10);
}
