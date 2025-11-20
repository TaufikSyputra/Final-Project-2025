// Fungsi MAV
int compute_MAV1(int abs_signal1){
  sum1 -= circular_buffer1[data_index1];
  sum1 += abs_signal1;
	circular_buffer1[data_index1] = abs_signal1;
	data_index1 = (data_index1 + 1) % BUFFER_SIZE_MAV;
	return (sum1/BUFFER_SIZE_MAV);
} 

int compute_MAV2(int abs_signal2){
  sum2 -= circular_buffer2[data_index2];
  sum2 += abs_signal2;
	circular_buffer2[data_index2] = abs_signal2;
	data_index2 = (data_index2 + 1) % BUFFER_SIZE_MAV;
	return (sum2/BUFFER_SIZE_MAV);
} 

void EMG_Control(){
  //Serial.println("Mulai");

  if(MAV1 >= treshold_1 && MAV1 > MAV2){
    mode = 1; // Pump 1 ON
    Setpoint1 = SETPOINT_POMPA1;    
  }
  else if(MAV2 >= treshold_2 && MAV2 > MAV1){
    mode = 2; // Pump 2 ON
    Setpoint2 = SETPOINT_POMPA2;
  }
  else{
    mode = 0; // all Pump off
  }
}

