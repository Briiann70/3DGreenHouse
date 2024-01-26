
#include <dht.h>

const int pinLDR = A0;
const int pinRS = A1;
int LEDa = 7;                      //variabel LED
int LEDb = 6;
int LEDc = 5;
int LEDd = 4;
int x=0;
int C1=8;                         //variabel motor stepper
int C2=9;
int C3=10;
int C4=11;
int pin_dht=2;
dht DHT;

int step = 25;                    //Kecepatan putaran Motor Stepper
int delaytime = 2;

void setup() {
  Serial.begin(9600);
  pinMode(pinLDR,INPUT);          //masukan Led
  pinMode(pinRS,INPUT);           //masukan RS
  pinMode(pin_dht,INPUT);
  pinMode(LEDa,OUTPUT);           // keluaran lampu Merah (1) tanda Gelap
  pinMode(LEDb,OUTPUT);           // keluaran lampu Hijau (1) tanda Cerah
  pinMode(LEDc,OUTPUT);           // keluaran lampu Merah (2) tanda Hujan
  pinMode(LEDd,OUTPUT);           // keluaran lampu Hijau (2) tanda Tidak Hujan
  pinMode(C1,OUTPUT);
  pinMode(C2,OUTPUT);
  pinMode(C3,OUTPUT);
  pinMode(C4,OUTPUT);
}

float total;
int dataLDR=0;                    // data LDR dimulai dari 0
int dataRS=0;                     // data RS dimulai dari 0

void loop (){
  //DHT22
  int readData = DHT.read22(pin_dht); // baca Data dari sensor
  float t = DHT.temperature; // Ambil nilai Suhu
  float h = DHT.humidity; // Ambil nilai Kelembaban
  Serial.print("SUHU = ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("    KELEMBABAN = ");
  Serial.print(h);
  //LDR
  dataLDR = analogRead(pinLDR);               // data LDR dibaca dari pin analog LDR
  if(dataLDR>400) {
    digitalWrite(LEDa,HIGH);// lampu merah (1) menyala apabila nilai LDR >400 (Gelap)
    }else{
      digitalWrite(LEDa,LOW); // lampu hijau (1) mati apabila nilai LDR <400 (Cerah)
      }   
    Serial.print("Data LDR = ");                 // tampilan data LDR di monitor
    Serial.println(dataLDR);                     // Nilai dari data LDR yang akan ditampilkan
    if(dataLDR<400) {
      digitalWrite(LEDb,HIGH);  // lampu hijau (1) menyala apabila nilai LDR <400 (Cerah)
      } else {
        digitalWrite(LEDb,LOW);// lampu hijau (1) mati apabila nilai LDR >400 (Gelap)
      }   
  //RAINDROPS 
    dataRS= analogRead(pinRS);                   // data sensor hujan yang dibaca dari pin analog RS
  if(dataRS<900) {digitalWrite(LEDc,HIGH);}   // lampu merah (2) menyala apabila nilai RS <900 (Hujan)
  else            {digitalWrite(LEDc,LOW);}   // lampu merah (2) mati apabila nilai RS >900 (Tidak Hujan)
 Serial.print("Data RS = ");                  // tampilan data RS di monitor
 Serial.println(dataRS);                      // Nilai dari data RS yang akan ditampilkan
  if(dataRS>900) {
    digitalWrite(LEDd,HIGH); // lampu hijau (2) menyala apabila nilai RS >900 (Tidak Hujan)
    }else{
      digitalWrite(LEDd,LOW);
      }   // lampu hijau (2) mati apabila nilai RS <900 (Hujan)
total = (dataRS - (dataLDR+600) - (h+t));
  if (total<-10)
  { if (x==1){
 Serial.print("jemuran keluar");
 for (int i=0; i<2000; i++)
 {mundur(); } x=0;}
}
else if (total>-10)
{ if(x==0) {
 Serial.println("jemuran masuk");
 for (int i=0; i<2000; i++)
 { maju(); } x=1;} 
}

delay(1000);}

void mundur(){
  step4();
  delay(delaytime);
  step3();
  delay(delaytime);
  step2();
  delay(delaytime);
  step1();
  delay(delaytime);
}
void maju(){
  step1();
  delay(delaytime);
  step2();
  delay(delaytime);
  step3();
  delay(delaytime);
  step4();
  delay(delaytime);
}
void step1(){
  digitalWrite(C1,LOW);
  digitalWrite(C2,LOW);
  digitalWrite(C3,HIGH);
  digitalWrite(C4,HIGH);}
void step2(){
  digitalWrite(C1,HIGH);
  digitalWrite(C2,LOW);
  digitalWrite(C3,LOW);
  digitalWrite(C4,HIGH);}
void step3(){
  digitalWrite(C1,HIGH);
  digitalWrite(C2,HIGH);
  digitalWrite(C3,LOW);
  digitalWrite(C4,LOW);}
void step4(){
  digitalWrite(C1,LOW);
  digitalWrite(C2,HIGH);
  digitalWrite(C3,HIGH);
  digitalWrite(C4,LOW);}
