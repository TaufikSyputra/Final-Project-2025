// Tracking of Magnetic Ball (Position and Orientation)
// Author : Taufik Syahputra

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#define TCA9548A_ADDRESS 0x70 // Alamat I2C default TCA9548A

// Inisialisasi objek sensor HMC5883L
Adafruit_HMC5883_Unified mag1 = Adafruit_HMC5883_Unified(1);
Adafruit_HMC5883_Unified mag2 = Adafruit_HMC5883_Unified(2);
Adafruit_HMC5883_Unified mag3 = Adafruit_HMC5883_Unified(3);
Adafruit_HMC5883_Unified mag4 = Adafruit_HMC5883_Unified(4);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag1.getSensor(&sensor);                                        // hanya sensor 1 karena ketiga sensor identik
  Serial.println("----------------------------------");
  Serial.print("Sensor:       "); Serial.println(sensor.name);
  Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void tcaSelect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCA9548A_ADDRESS);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

void setup(void) {
  Serial.begin(9600);
  Wire.begin();

  // Inisialisasi sensor pada channel 7
  tcaSelect(1);
  if (!mag1.begin()) {
    Serial.println("Tidak dapat menemukan HMC5883L pada channel 7, cek koneksi!");
    while (1);
  }

  // Inisialisasi sensor pada channel 1
  tcaSelect(2);
  if (!mag2.begin()) {
    Serial.println("Tidak dapat menemukan HMC5883L pada channel 1, cek koneksi!");
    while (1);
  }

  // Inisialisasi sensor pada channel 2
  tcaSelect(3);
  if (!mag3.begin()) {
    Serial.println("Tidak dapat menemukan HMC5883L pada channel 2, cek koneksi!");
    while (1);
  }

  // Inisialisasi sensor pada channel 3
  tcaSelect(4);
  if (!mag4.begin()) {
    Serial.println("Tidak dapat menemukan HMC5883L pada channel 3, cek koneksi!");
    while (1);
  }

  // Display informasi tentang sensor
  displaySensorDetails();
}

void loop(void) {
  sensors_event_t event;

  // Membaca sensor pada channel 1
  tcaSelect(1);
  mag1.getEvent(&event);
  float x1 = event.magnetic.x;
  float y1 = event.magnetic.y;
  float z1 = event.magnetic.z;

  // Membaca sensor pada channel 2
  tcaSelect(2);
  mag2.getEvent(&event);
  float x2 = event.magnetic.x;
  float y2 = event.magnetic.y;
  float z2 = event.magnetic.z;

  // Membaca sensor pada channel 3
  tcaSelect(3);
  mag3.getEvent(&event);
  float x3 = event.magnetic.x;
  float y3 = event.magnetic.y;
  float z3 = event.magnetic.z;

  // Membaca sensor pada channel 4
  tcaSelect(4);
  mag4.getEvent(&event);
  float x4 = event.magnetic.x;
  float y4 = event.magnetic.y;
  float z4 = event.magnetic.z;

  // Mengirim data dalam format CSV: x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4
  Serial.print(x1); Serial.print(","); Serial.print(y1); Serial.print(","); Serial.print(z1); Serial.print(",");
  Serial.print(x2); Serial.print(","); Serial.print(y2); Serial.print(","); Serial.print(z2); Serial.print(",");
  Serial.print(x3); Serial.print(","); Serial.print(y3); Serial.print(","); Serial.print(z3); Serial.print(",");
  Serial.print(x4); Serial.print(","); Serial.print(y4); Serial.print(","); Serial.println(z4);

  delay(500); // Tunggu sebelum pembacaan berikutnya
}

void displaySensorData(sensors_event_t event) {
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.println(" uT");
}
// void loop(void) {
//   sensors_event_t event;

//   // Membaca sensor pada channel 1
//   tcaSelect(1);
//   mag1.getEvent(&event);
//   Serial.print("Channel 1 - ");
//   displaySensorData(event);

//   // Membaca sensor pada channel 2
//   tcaSelect(2);
//   mag2.getEvent(&event);
//   Serial.print("Channel 2 - ");
//   displaySensorData(event);

//   // Membaca sensor pada channel 3
//   tcaSelect(3);
//   mag3.getEvent(&event);
//   Serial.print("Channel 3 - ");
//   displaySensorData(event);

//   Serial.println();
//   delay(1000); // Tunggu sebelum pembacaan berikutnya
// }
