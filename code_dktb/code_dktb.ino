#include <Servo.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
int cambien = 5; //Chân cảm biến nối chân số 5 Arduino
int Relay = 3;
int giatri;
boolean canhbaotrom = false;// biến trung gian
Servo myservo_red;
Servo myservo_orange;
Servo myservo_green;
// set chân và tốc độ quạt
int INA = 8;
int INB = 7;
int ENA = 6;
int MAX_SPEED = 255;//từ 0-255
int MIN_SPEED = 0;
void setup() 
{
  Serial.begin(9600);
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Ha_Nhat_Tuong");
  lcd.setCursor(4,1);
  lcd.print("WELCOME");
  pinMode(cambien, INPUT);
  pinMode(Relay, OUTPUT);
  myservo_red.attach(11);
  myservo_orange.attach(10);
  myservo_green.attach(9);
  myservo_red.write(0);
  myservo_orange.write(0);
  myservo_green.write(0);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(ENA,OUTPUT);
}
// hàm stop
void motor_1_Dung() {
  digitalWrite(INA, 0);
  digitalWrite(INB, 0);
}

 // hàm quay thuận KĐH
void motor_1_Tien(int speed) { 
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(INA, 1);
  digitalWrite(INB, 0);
  analogWrite(ENA,speed);
}
void loop() 
{
  if (canhbaotrom) {     
    giatri = digitalRead(cambien);
 
  if (giatri == HIGH){
   digitalWrite(Relay, LOW);
   int alarm1=1;
   Serial.println(alarm1);//truyền tín hiệu dạng digital "1" lên Serial
   delay(30);
  
  }
  else {
    digitalWrite(Relay, HIGH);
    int alarm2=0;
    Serial.println(alarm2);// truyền tín hiệu dạng digital "0" lên Serial
    delay(30);
  } }
 //Đọc giá trị digital từ cảm biến và gán vào biến giatri
 if (Serial.available())
  {
   int  serialValue = Serial.read();// Đọc giá trị từ cổng Serial
   switch (serialValue){
      case 'a':
        canhbaotrom=true;
        break;

      case 'b':
        canhbaotrom=false;
        digitalWrite(Relay , LOW);
        break;
      case 'r':
       
        myservo_red.write(60);
        delay(15000);
        myservo_red.write(0);
        break;
      case '1':
        myservo_red.write(60);
        delay(50);
        break;
      case '0':
        myservo_red.write(0);
        delay(50);
        break;
      case 'o':
        myservo_orange.write(60);
        delay(15000);
        myservo_orange.write(0);
        break;
       case '5':
        myservo_orange.write(60);
        delay(50);
        break;
      case '4':
        myservo_orange.write(0);
        delay(50);
        break;  
      case 'g':
        myservo_green.write(60);
        delay(15000);
        myservo_green.write(0);
        break;
       case '3':
        myservo_green.write(60);
        delay(50);
        break;
      case '2':
        myservo_green.write(0);
        delay(50);
        break;  
       // Mức 0 quạt
       case 'l' :
         motor_1_Dung(); 
         delay(50);
         break;
       //Mức 1 quạt
       case 'm' :
         motor_1_Tien(100);
         delay(50);
         break;
       //Mức 2 quạt
       case 'n': 
         motor_1_Tien(140);
         delay(50);
         break;
       //Mức 3 quạt
       case 'i':
         motor_1_Tien(180);
         delay(50);
         break;
       //Mức 4 quạt
       case 'j':
         motor_1_Tien(220);
         delay(50);
         break;
       //Mức 5 quạt
       case'k':
         motor_1_Tien(MAX_SPEED);
         delay(50);
         break;
       default:
         break;
      }
      }
 delay(200);
  }
