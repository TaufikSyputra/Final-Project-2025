void parseCommand() {
  // baca perintah
  String cmd = Serial.readStringUntil(' ');
  cmd.trim();
  cmd.toLowerCase();

  if (cmd == "setp1kp") { // Contoh: "setp1kp 3.5"
    Kp_1 = Serial.parseFloat();
    PID_pump1.SetTunings(Kp_1, Ki_1, Kd_1);
    Serial.print("Kp1 set to: "); Serial.println(Kp_1);
  }
  else if (cmd == "setp1ki") { // Contoh: "setp1ki 1.2"
    Ki_1 = Serial.parseFloat();
    PID_pump1.SetTunings(Kp_1, Ki_1, Kd_1);
    Serial.print("Ki1 set to: "); Serial.println(Ki_1);
  }
  else if (cmd == "setp1kd") { // Contoh: "setp1kd 0.8"
    Kd_1 = Serial.parseFloat();
    PID_pump1.SetTunings(Kp_1, Ki_1, Kd_1);
    Serial.print("Kd1 set to: "); Serial.println(Kd_1);
  }
    
  // Ulangi untuk Kp_2, Ki_2, Kd_2
  else if (cmd == "setp2kp") {
    Kp_2 = Serial.parseFloat();
    PID_pump2.SetTunings(Kp_2, Ki_2, Kd_2);
    Serial.print("Kp2 set to: "); Serial.println(Kp_2);
  }
  else if(cmd == "setp2ki") {
    Ki_2 = Serial.parseFloat();
    PID_pump2.SetTunings(Kp_2, Ki_2, Kd_2);
    Serial.print("Ki2 set to: "); Serial.println(Ki_2);
  }
  else if (cmd == "setp2kd") { //
    Kd_2 = Serial.parseFloat();
    PID_pump2.SetTunings(Kp_2, Ki_2, Kd_2);
    Serial.print("Kd2 set to: "); Serial.println(Kd_2);
  }
  else{
    Serial.println("perintah tidak dikenali");
  }
  // Tidak ada mode reset atau pengujian yang diperlukan untuk reduksi ini
}