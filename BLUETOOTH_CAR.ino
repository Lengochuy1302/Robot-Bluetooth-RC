#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;
SoftwareSerial bluetoothSerial(2, 10); // RX, TX

//khai báo chân động cơ
AF_DCMotor MotorPhai(1, MOTOR12_1KHZ);
AF_DCMotor MotorTrai(4, MOTOR34_1KHZ);

char blue;// là vùng nhớ để so sánh kí tự trả về từ app.
int spd = 255; // giá trị băm xung( tay ga).

void setup()
{
  bluetoothSerial.begin(9600);  //Set the baud rate to your Bluetooth module.
  Serial.begin(9600);
   myservo.attach(9);
    myservo.write(20);
  Serial.println("Sẵn sàng");
}

// dieu khien motor phai
void motor_left(int spd, byte dir)
{
  MotorTrai.setSpeed(spd);
  if (dir == 0) // motor trái quay tới
  {
  MotorTrai.run(FORWARD); 
  }
  else if (dir == 1) // motor trái quay lùi
  {
  MotorTrai.run(BACKWARD); 
  }
  else if (dir == 2)// motor trái đứng yên
  {
  MotorTrai.run(RELEASE);
  }
}

// dieu khien motor trai
void motor_right(int spd, byte dir)
{
  MotorPhai.setSpeed(spd);
  if (dir == 0) // motor phải quay tới
  {
  MotorPhai.run(FORWARD); 
  }
  else if (dir == 1)//motor phải quay lùi
  {
  MotorPhai.run(BACKWARD); 
  }
  else if (dir == 2) //motor phải đứng yên
  {
  MotorPhai.run(RELEASE);
  }
}

// cấu trúc điều khiển
void forw () // đi thẳng
{
  Serial.println("motor di thang"); 
  motor_right(spd , 0); 
  motor_left(spd , 0);
}
void back () // chay lui
{
  Serial.println("motor di lui"); 
  motor_right(spd , 1); 
  motor_left(spd , 1);
}
void left () // quay trai
{
  Serial.println("motor cua trai"); 
  motor_right(spd , 0); 
  motor_left(spd , 2);
}
void right () // quai phai
{
  Serial.println("motor cua phai"); 
  motor_left(spd , 0); 
  motor_right(spd , 2);
}
void rightforw () // đi thẳng rẽ trái 
{
  Serial.println("đi thẳng rẽ trái"); 
  motor_left( 110 , 0); 
  motor_right( spd , 0);
}
void leftforw () // đi thẳng rẽ phải
{
  Serial.println("đi thẳng rẽ phải"); 
  motor_left( spd , 0); 
  motor_right( 110 , 0);
}
void rightback () // đi lùi rẽ phải
{
  Serial.println("đi lùi rẽ phải"); 
  motor_left( spd , 1); 
  motor_right( 110 , 1);
}
void leftback () // đi lùi rẽ trái
{
  Serial.println("đi lùi rẽ trái"); 
  motor_left( 110 , 1); 
  motor_right( spd , 1);
}
void tack() // dừng lại
{
  motor_left( spd , 2); 
  motor_right( spd , 2);
}
//void den_tien() {
//  digitalWrite(ledtruoc, HIGH);
//}
//void phat_co() {
//  myservo.write(90); // Điều khiển động cơ quay đến góc 90 độ
//  delay(100);
//}
//void ha_co() {
//  myservo.write(0); // Điều khiển động cơ quay đến góc 0 độ
//  delay(100);
//}
//void coi_lui() {
//  digitalWrite(coilui, HIGH); 
//  delay(3); 
//  digitalWrite(coilui, LOW); 
//  delay(3);
//}
//void den_lui()
//{
//  digitalWrite(ledsau, HIGH);
//}
//void tat_den()
//{
//  digitalWrite(ledsau, LOW); digitalWrite(ledtruoc, LOW);
//}
//void da_dentruoc()
//{
//  digitalWrite(ledtruoc, HIGH); delay(100); digitalWrite(ledtruoc, LOW); delay(1000);
//}
//void da_densau()
//{
//  digitalWrite(ledsau, HIGH); delay(100); digitalWrite(ledsau, LOW); delay(1000);
//}

//Chương trình điều khiển
void robot_android()
{
  if ( bluetoothSerial.available())
  {
    blue = bluetoothSerial.read(); 
    Serial.println(blue);
  }
  switch (blue )
  {
    case ('W'):
 myservo.write(120);
      break;
    case ('w'): 
 myservo.write(20);
      break;
    case ('V'):
//      coi_lui();
      break;
    case ('v'):
//      coi_lui();
      break;
    case ('0'):
      spd = 160;
    case ('1'):
      spd = 170;
      break;
    case ('2'):
      spd = 180;
      break;
    case ('3'):
      spd = 190;
      break;
    case ('4'):
      spd = 200;
      break;
    case ('5'):
      spd = 210;
      break;
    case ('6'):
      spd = 220;
      break;
    case ('7'):
      spd = 230;
      break;
    case ('8'):
      spd = 240;
      break;
    case ('9'):
      spd = 255;
      break;
    case ('S'):
      tack();
//      tat_den();
      break;
    case ('F'):
      forw();
      break;
    case ('B'):
      back();
//      den_lui();
      break;
    case ('L'):
      left();
      break;
    case ('R'):
      right();
      break;
    case ('H'):
      rightback();
//      den_lui();
      break;
    case ('J'):
      leftback();
//      den_lui();
      break;
    case ('I'):
     leftforw();
      break;
    case ('G'):
     rightforw();
      break;
  }
}

void loop() {
  robot_android();
  // put your main code here, to run repeatedly:
}
