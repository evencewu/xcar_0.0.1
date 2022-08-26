#include <Servo.h>
Servo my1;
Servo my2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  my1.attach(D1);
  my2.attach(D2);
  my1.write(105);
  my2.write(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
      char i = Serial.read();
      int ser = Serial.parseInt();
      // Serial.parseTint() 会解析出串口内的数字
      switch(i)
      {
        case 'a':
          my1.write(ser);
          Serial.println(ser);
          break;
        case 'b':
          my2.write(ser);
          Serial.println(ser);
          delay(15);
          break;
      }
   }
}
