#include "ADS1X15.h" //library untuk ADS115
#include "Wire.h"

//ADS Addressing
ADS1115 ADS0(0x48); // alamat ADS1
ADS1115 ADS1(0x49); // alamat ADS2
float Pressure[5];
float PressureRef;

// Pin solenoid
int SolValve[8] = {32, 33, 25, 26, 27, 14, 12, 13};

// PIN DRIVE L298N
// Pompa 1
#define ENA 19
#define IN1 18
#define IN2 5

//Pompa 2
#define ENB 15
#define IN3 4
#define IN4 2
int pwmValue;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  ADS0.begin();
  ADS1.begin();

  // Set solenoid pin modes
  pinMode(SolValve[0], OUTPUT); // exhaust
  pinMode(SolValve[1], OUTPUT); // thumb
  pinMode(SolValve[2], OUTPUT); // index
  pinMode(SolValve[3], OUTPUT); // middle
  pinMode(SolValve[4], OUTPUT); // ring
  pinMode(SolValve[5], OUTPUT); // pinky
  pinMode(SolValve[6], OUTPUT); // pressurise
  pinMode(SolValve[7], OUTPUT); // depressurise

  // set initial condition of valve
  digitalWrite(SolValve[0], HIGH);
  digitalWrite(SolValve[1], HIGH);
  digitalWrite(SolValve[2], HIGH);
  digitalWrite(SolValve[3], HIGH);
  digitalWrite(SolValve[4], HIGH);
  digitalWrite(SolValve[5], HIGH);
  digitalWrite(SolValve[6], LOW);
  digitalWrite(SolValve[7], LOW);

  // Set L298N pin mode
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 
}

void loop() {
  read_pressure();
  // cek tekanan
  Serial.print(PressureRef); // Pref
  Serial.print(" ");
  Serial.print(Pressure[0]); // pinky
  Serial.print(" ");
  Serial.print(Pressure[1]); // ring
  Serial.print(" ");
  Serial.print(Pressure[2]); // middle
  Serial.print(" ");
  Serial.print(Pressure[3]); // index
  Serial.print(" ");
  Serial.println(Pressure[4]); // tumb

  // Pompa 1 menyala
  // tes tekanan respon posistif
  digitalWrite(SolValve[7], HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);
  delay(150000);

  // setelah 15 detik pompa mati
  digitalWrite(SolValve[7], LOW);
  analogWrite(ENA, 0); 
}

//Serial.print(PressureRef);
  //Serial.print(" ");
  //Serial.print(Pressure[0]);
  //Serial.print(" ");
  //Serial.print(Pressure[1]);
  //Serial.print(" ");
  //Serial.print(Pressure[2]);
  //Serial.print(" ");
  //Serial.println(Pressure[3]);
  //Serial.print(" ");
  //Serial.println(Pressure[4]);

/* Pompa 2 menyala
  analogWrite(ENA, 0);
  digitalWrite(SolValve[6], HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 255);

  //cek tekanan
  Serial.print(PressureRef);
  Serial.print(" ");
  Serial.println(Pressure[3]);
  delay(10000);

  analogWrite(ENB, 0);
  digitalWrite(SolValve[6], LOW);
  */
