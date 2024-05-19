
/*--------------------------------------------------------------------------
-*- coding: utf-8 -*-                   created on sunday, november 26, 2023

@author: Phuoc Loi Tran (Twilight)
@student code: 2101076 (from C.T.U.T)
@github: Loitranph ( https://github.com/Loitranph )
@discription: Gesture recognition and control project, using python and arduino
@using:
  software:
            python:
                    version: 3.10
                    lib: openCV, mediapipe, pyserial, time, numpy...
            arduino:
                    ide version: 2.2.1
                    lib: Arduino.h, Servo.h
  hardware:
            board Arduino Uno
            ...

-----------------------------------------------------------------------------*/

#include <Servo.h>

Servo Servo1st;
Servo Servo2st;
Servo Servo3st;
Servo Servo4st;
Servo Servo5st;
Servo Servo6st;

// Đặt giới hạn cho phần mã hóa (thử sai nhiều lần)

//Giới hạn trên
int Thum_high = 175;
int Inde_high = 200;
int Midd_high = 210;
int Ring_high = 200;
int Pink_high = 180;
// int Wris_high =  85;

//Giới hạn dưới
int Thum_low = 60;
int Inde_low = 70;
int Midd_low = 60;
int Ring_low = 60;
int Pink_low = 50;
// int Wris_low =  1;

// Đặt góc mở và đóng của các ngón tay
int thuH = 170;   int thuL = 70;
int indH = 180;   int indL = 35;
int midH = 180;   int midL = 20;
int rinH = 180;   int rinL = 45;
int pinH = 180;   int pinL = 40;
// int wriH = 180;   int wriL = 70;

int dl_ti = 0;

void setup()
{

  Serial.begin(9600);  // Khởi tạo cổng serial với tốc độ 9600 bps

  Servo1st.attach(3);
  Servo2st.attach(5);
  Servo3st.attach(6);
  Servo4st.attach(9);
  Servo5st.attach(10);
  Servo6st.attach(11);

}

void loop()
{
    
    String DataSerial = "";

    while (Serial.available() > 0)
    {
      DataSerial = Serial.readStringUntil('/n');
    }
    Serial.println("Received: " + DataSerial);
    DataSerial.trim();

    // Xử lý dữ liệu nhận được (phân tách dữ liệu thành các phần tử)
    int values[7];
    int count = 0;
    char *token = strtok((char *)DataSerial.c_str(), ",");

    while (token != NULL && count < 7)
    {
      values[count] = atoi(token);
      token = strtok(NULL, ",");
      count++;
    }

  // In ra giá trị của các phần tử và chuyễn sang kiểu số nguyên
    for (int i = 1; i < 7; i++)
    {
      Serial.print("Value at index ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(values[i]);
      values[i] = int(values[i]);
    }

  // Điều khiển góc quay theo giá trị nhận được

    // Tính ra tọa độ từ vị trí nhận được
    int Inde_pos = map( values[2] , Inde_low , Inde_high , indL , indH );
    int Midd_pos = map( values[3] , Midd_low , Midd_high , midL , midH );
    int Ring_pos = map( values[4] , Ring_low , Ring_high , rinL , rinH );
    int Pink_pos = map( values[5] , Pink_low , Pink_high , pinL , pinH );
    int Thum_pos;
    // int Wris_pos = map( values[6] , Wris_low , Wris_high , wriL , wriH );
    // Điều khiển
    if (values[6]>35)
    {
      Thum_pos = map( values[1] , Thum_low , Thum_high , thuL , thuH );
      Servo6st.write(180);
    }
    else
    {
      Thum_pos = map( values[1] , Thum_low , Thum_high , thuH , thuL );
      Servo6st.write(90);
    }
    Servo1st.write(Thum_pos);
    Servo2st.write(Inde_pos);
    Servo3st.write(Midd_pos);
    Servo4st.write(Ring_pos);
    Servo5st.write(Pink_pos);
    
    delay(dl_ti);

  if (DataSerial == "")
  {
    Servo1st.write(thuH);
    Servo2st.write(indH);
    Servo3st.write(midH);
    Servo4st.write(rinH);
    Servo5st.write(pinH);
    Servo6st.write(180);
  }
}