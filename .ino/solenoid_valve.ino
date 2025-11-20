// Pompa 1
#define ENA 19
#define IN1 18
#define IN2 5

// define pin solenoid
int SolValve[8] = {32, 33, 25, 26, 27, 14, 12, 13};

void setup() {
  Serial.begin(115200);
  // Pompa 1
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set solenoid pin modes, normally closed
  pinMode(SolValve[0], OUTPUT); // exhaust
  pinMode(SolValve[1], OUTPUT); // thumb
  pinMode(SolValve[2], OUTPUT); // index
  pinMode(SolValve[3], OUTPUT); // middle
  pinMode(SolValve[4], OUTPUT); // ring
  pinMode(SolValve[5], OUTPUT); // pinky
  pinMode(SolValve[6], OUTPUT); // pressurise
  pinMode(SolValve[7], OUTPUT); // depressurise

  digitalWrite(SolValve[0], LOW);
  digitalWrite(SolValve[1], LOW);
  digitalWrite(SolValve[2], LOW);
  digitalWrite(SolValve[3], LOW);
  digitalWrite(SolValve[4], LOW);
  digitalWrite(SolValve[5], LOW);
  digitalWrite(SolValve[6], LOW);
  digitalWrite(SolValve[7], LOW);
}

void loop() {
  //Pompa ON
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);

  //solenoid on
  digitalWrite(SolValve[0], HIGH); //hanya solv 1 on
  Serial.println("solvalve 1 ON");
  delay(5000);
  
  digitalWrite(SolValve[0], LOW); //hanya solv 2 on
  digitalWrite(SolValve[1], HIGH);
  Serial.println("solvalve 2 ON");
  delay(5000);

  digitalWrite(SolValve[1], LOW); //hanya solv 3 on
  digitalWrite(SolValve[2], HIGH);
  Serial.println("solvalve 3 ON");
  delay(5000);

  digitalWrite(SolValve[2], LOW); //hanya solv 4 on
  digitalWrite(SolValve[3], HIGH);
  Serial.println("solvalve 4 ON");
  delay(5000);

  digitalWrite(SolValve[3], LOW); //hanya solv 5 on
  digitalWrite(SolValve[4], HIGH);
  Serial.println("solvalve 5 ON");
  delay(5000);

  digitalWrite(SolValve[4], LOW); //hanya solv 6 on
  digitalWrite(SolValve[5], HIGH);
  Serial.println("solvalve 6 ON");
  delay(5000);

  digitalWrite(SolValve[5], LOW); //hanya solv 7 on
  digitalWrite(SolValve[6], HIGH);
  Serial.println("solvalve 7 ON");
  delay(5000);

  digitalWrite(SolValve[6], LOW); //hanya solv 8 on
  digitalWrite(SolValve[7], HIGH);
  Serial.println("solvalve 7 ON");
  delay(5000);
}
