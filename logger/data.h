#ifndef DATA_H
#define DATA_H

#include <due_can.h>

#define SERIAL_COMMUNICATION_FREQUENCY 115200
#define CAN_COMMUNICATION_FREQUENCY CAN_BPS_1000K

void write2SDCallback();
void save2SDCallback();

Task tWrite2SD(20, TASK_FOREVER, &write2SDCallback);
Task tSave2SD(5 * TASK_SECOND, TASK_FOREVER, &save2SDCallback);

Scheduler runner;

const int chipSelect = 87; // SD pin

// CAN data logging
float prec = 0;
float imu_time, imu_general_status, imu_clock_status; // imu
float acc_x, acc_y, acc_z; // imu acc
float gyro_x, gyro_y, gyro_z; // imu gyro
float quaternion_0, quaternion_1, quaternion_2, quaternion_3; // imu quaternions
float roll, pitch, yaw; // imu eulers
float velocity;  // imu velocity
float gps_latitude, gps_longitude; // gps

int i1, i2=100;

unsigned long previousMillis; // Inizializzo variabile per il debouncing
unsigned int interval = 500; // Intervallo di attesa debouncing

String header =
	"imu time,imu general status,imu clock status" // imu
	",acc x,acc y,acc z" // imu acc
	",gyro x,gyro y,gyro z" // imu gyro
	",quaternion 0,quaternion 1,quaternion 2,quaternion 3" // imu quaternions
	",roll,pitch,yaw" // imu eulers
	",velocity" // imu velocity
	",latitude,longitude"; // gps

char fileName[16]; // SDcard uses 8.3 names so 16 bytes is enough NOte room for the '\0' char is needed!
unsigned int nr = 1;
File dataFile; // to save in SD
int message_count = 0;
CAN_FRAME incoming;

bool start = false;

#endif // DATA_H
