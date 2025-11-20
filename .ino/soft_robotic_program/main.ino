void setup() {
  // Serial connection begin
  Serial.begin(BAUD_RATE);
  Wire.begin(); // start protocol I2C
  ADS0.begin();
  ADS1.begin();

  // start ESP NOW
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  Serial.print("MAC Address Receiver: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init gagal");
    return;
  }
  Serial.println("ESP NOW READY");

  esp_now_register_recv_cb(OnDataRecv);

  // Inisiasi pin L298N
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // set initial condition of Pump (Off)
  // Pompa 1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  // Pompa 2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);

  // Set Solenoid pin modes
  pinMode(SolValve[0], OUTPUT);
  pinMode(SolValve[6], OUTPUT);
  pinMode(SolValve[7], OUTPUT);

  // set initial condition of valve
  digitalWrite(SolValve[0], HIGH);
  digitalWrite(SolValve[6], LOW);
  digitalWrite(SolValve[7], LOW);

  // Initial PID
  PID_pump1.SetMode(AUTOMATIC);
  PID_pump1.SetOutputLimits(179, 255);
  PID_pump2.SetMode(AUTOMATIC);
  PID_pump2.SetOutputLimits(192, 255);
}

void loop() {
  static int readIndex = 0;

  if (availableSamples > 0) {
    // Ambil data dari buffer
    struct_message data = dataBuffer[readIndex];
    readIndex = (readIndex + 1) % BUFFER_SIZE_EMG;

    noInterrupts();
    availableSamples--;
    interrupts();

    // Data EMG
    MAV1 = data.sensor1;
    MAV2 = data.sensor2;
    
    read_pressure();
    EMG_Control();

    // logic to control pump    
    if (mode == 0 ){
      // all pump off
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
      digitalWrite(SolValve[7], LOW);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 0);
      digitalWrite(SolValve[6], LOW);

      // plot MAV and pressure ini middle finger(current pressure) 
      Serial.print(MAV1);
      Serial.print(" ");
      Serial.print(MAV2);
      Serial.print(" ");
      Serial.println(Pressure[2]);
    }
    else if (mode == 1){
      // Pum 1 Pressurise
      Input1 = Pressure[2];
      PID_pump1.Compute();
      digitalWrite(SolValve[7], HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, (int) Output1);

      // Validation of Pump 2 is Off
      digitalWrite(SolValve[6], LOW);
      analogWrite(ENB, 0);

      //plot MAV, setpoint1, Input1
      Serial.print(MAV1);
      Serial.print(" ");
      Serial.print(MAV2);
      Serial.print(" ");
      Serial.print(Setpoint1);
      Serial.print(" ");
      Serial.println(Input1);
    }
    else if(mode == 2) {
      // Pump 2 Depressurise
      Input2 = Pressure[2];
      PID_pump2.Compute();
      digitalWrite(SolValve[6], HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, (int) Output2);

      // validation of pump 1 is off
      digitalWrite(SolValve[7], LOW);
      analogWrite(ENA, 0);

      //plot MAV, setpoint2, Input2
      Serial.print(MAV1);
      Serial.print(" ");
      Serial.print(MAV2);
      Serial.print(" ");
      Serial.print(Setpoint2);
      Serial.print(" ");
      Serial.println(Input2);
    }    
  }
}