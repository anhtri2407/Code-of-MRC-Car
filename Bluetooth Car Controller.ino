#include <SoftwareSerial.h>
int bluetoothTx = 2; // định nghĩa chân 2 là chân truyền tín hiệu 
int bluetoothRx = 3;// định nghĩa chân 3 là chân nhận tín hiệu
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
   
//định nghĩa chân motor trái
#define enA 6
#define in1 7
#define in2 8

//định nghĩa chân  motor phai
#define enB 5
#define in3 9
#define in4 10


char blue;// là vùng nhớ để so sánh kí tự trả về từ app.
int spd; // giá trị băm xung( tay ga).
void setup() {
   bluetooth.begin(115200);    
   bluetooth.print("$$$");    
   delay(100);    
   bluetooth.println("U,9600,N");    
   bluetooth.begin(9600);
   Serial.begin(9600); 

     
  // định nghĩa chân tín hiệu in & out

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
}

// dieu khien motor trai
void motor_left(int spd, byte dir) 
{ 
   if (dir == 0) // motor trái quay tới
   { 
     digitalWrite(in2, LOW);
     digitalWrite(in1, HIGH);
   }
   else if (dir == 1) // motor trái quay lùi
   {
     digitalWrite(in2, HIGH);
     digitalWrite(in1, LOW);
   }
   else if (dir == 2)// motor trái đứng yên
   {
    digitalWrite(in1, LOW);
    digitalWrite(in2,LOW);
    }
   analogWrite(enA, spd );// băm xung cho motor trái
}

// dieu khien motor phai
void motor_right(int spd, byte dir) 
{ 
   if (dir == 0) // motor phải quay tới 
   { 
     digitalWrite(in4, LOW);
     digitalWrite(in3, HIGH);
   }
   else if (dir == 1)//motor phải quay lùi
   { 
     digitalWrite(in4, HIGH);
     digitalWrite(in3, LOW);
   }
   else if (dir ==2)//motor phải dứng lùi
   {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    }
   analogWrite(enB, spd );
}

void forw () // chay 
{
  Serial.println("motor di thang");
    motor_right(spd , 0);
    motor_left( spd , 0);
}

void back () // chay lui
{
  Serial.println("motor di lui");
    motor_right(spd , 1);
    motor_left( spd , 1);
}

void right () // quay trai
{
  Serial.println("motor cua trai");
    motor_right(spd , 0);
    motor_left( spd , 2);
    
}

void left () // quai phai
{
  Serial.println("motor cua phai");
    motor_left( spd , 0);
    motor_right( spd , 2);
}
void leftforw () // quai phai cham
{
  Serial.println("motor cua phai nhanh");
    motor_left( spd-20 , 0);
    motor_right( spd , 0);
}
void rightforw () // quai phai nhanh
{
  Serial.println("motor cua trai nhanh ");
    motor_left( spd , 0);
    motor_right( spd-20 , 0);
}
void rightback () // quai phai nhanh
{
  Serial.println("motor cua trai nhanh ");
    motor_left( spd , 1);
    motor_right( spd-20 , 1);
}
void leftback () // quai phai nhanh
{
  Serial.println("motor cua trai nhanh ");
    motor_left( spd-20 , 1);
    motor_right( spd , 1);
}
void tack()
{
  motor_left( spd , 2);
  motor_right( spd , 2);
  }



 void robot_android()
 {
 
 if ( bluetooth.available() )
  {
      blue =bluetooth.read();
      Serial.println("gia tri cua blue la   ");
      Serial.println(blue); 
  }
   switch (blue ){

  case('0'):
  spd = 70;
  case('1'):
  spd = 80;
  break;
  case('2'):
  spd = 100;
  break;
  case('3'):
  spd = 110;
  break;
  case('4'):
  spd = 127;
  break;
  case('5'):
  spd = 140;
  break;
  case('6'):
  spd = 160;
  break;
  case('7'):
  spd = 200;
  break;
  case('8'):
  spd = 230;
  break;
  case('9'):
  spd = 255;
  break;
  
  case ('S'):
   tack();
   break;
  case ('F'): 
   forw();
   break;
   case ('B'): 
   back();
   break;
   case ('L'): 
   left();
   break;
   case ('R'): 
   right();
   break;
   case ('H'): 
   leftback();
   break;
   case ('J'): 
   rightback();
   break;
   case ('I'): 
   rightforw();
   break;
   case ('G'): 
   leftforw();
   break;
   }
 }
void loop() {  
 robot_android();
  // put your main code here, to run repeatedly:
}
