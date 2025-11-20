#include "ADS1X15.h"
#include "Wire.h"
#include "PID_v1.h"
#include "esp_now.h"
#include "WiFi.h"

#define BAUD_RATE 115200
#define BUFFER_SIZE_EMG 2 // ukuran buffer data masuk
#define BUFFER_SIZE_MAV 250 // ukuran window untuk perhitungan MAV

// Struktur data dari transmitter
typedef struct struct_message {
  float sensor1;
  float sensor2;
} struct_message;

// Buffer data dari transmitter
struct_message dataBuffer[BUFFER_SIZE_EMG];
volatile int writeIndex = 0;
volatile int availableSamples = 0;

// Variabel EMG
int circular_buffer1[BUFFER_SIZE_MAV] = {0};
int circular_buffer2[BUFFER_SIZE_MAV] = {0};
int data_index1, data_index2, sum1, sum2;
int MAV1, MAV2;
float treshold_1 = 11;
float treshold_2 = 9;

// Callback saat data diterima
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  if (availableSamples < BUFFER_SIZE_EMG) {
    memcpy(&dataBuffer[writeIndex], incomingData, sizeof(struct_message));
    writeIndex = (writeIndex + 1) % BUFFER_SIZE_EMG;
    availableSamples++;
  }
}

//ADS addressing
ADS1115 ADS0(0x48);
ADS1115 ADS1(0x49);

// variable Pressure from sensor MPX5700AP
float Pressure[5];
float PressureRef;

// PIN DRIVE L298N
// Pump 1
int ENA = 19; // PWM (0-225)
int IN1 = 18; 
int IN2 = 5;

// Pump 2
int ENB = 15; // pwm
int IN3 = 4;
int IN4 = 2; 

// Pin Solenoid Valve
int SolValve[8] = {32, 33, 25, 26, 27, 14, 12, 13};

// PID variable
//Define Variables we'll be connecting to
double Input1, Output1, Setpoint1; // pressure positive
double Input2, Output2, Setpoint2; // pressure negative

// PID for Pum 1
//Specify the links and initial tuning parameters
double Kp_1=4.5, Ki_1=3, Kd_1=1;
PID PID_pump1(&Input1, &Output1, &Setpoint1, Kp_1, Ki_1, Kd_1, DIRECT);

// PID for Pum 2
//Specify the links and initial tuning parameters
double Kp_2=10, Ki_2=11, Kd_2=2;
PID PID_pump2(&Input2, &Output2, &Setpoint2, Kp_2, Ki_2, Kd_2, REVERSE);

// Konstanta setpoint
const float SETPOINT_POMPA1 = 36; // kPa
const float SETPOINT_POMPA2 = -45.0; // kPa

// mode operasi
int mode = 0;

// deklarasi fungsi
float compute_MAV1(float abs_signal1);
float compute_MAV2(float abs_signal2);

// status pompa
// bool isPump1Active = false;
// bool isPump2Active = false;

