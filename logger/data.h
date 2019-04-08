#ifndef DATA_H
#define DATA_H

#include <due_can.h>

// communication frequencies
#define SERIAL_COMMUNICATION_FREQUENCY 115200
#define CAN_COMMUNICATION_FREQUENCY CAN_BPS_1000K

// Callback methods prototypes
void t1Callback();
void t2Callback();
void t3Callback();
void t5Callback();

Task tRefreshScreen(100, TASK_FOREVER, &t1Callback);
Task tWriteToSD(20, TASK_FOREVER, &t2Callback);
Task tSaveToSD(5 * TASK_SECOND, TASK_FOREVER, &t3Callback);
Task tChangePage(5000, TASK_FOREVER, &t5Callback);

Scheduler runner;

const int chipSelect = 87; // SD pin
int interruptPin = 50; // button 1
int interruptPin2 = 51; // button 2
int interruptPin3 = 53; // button 3

#define BTN1 7
#define BTN2 6
#define BTN3 45
#define BTN4 46

int btn1Status = LOW;
int btn2Status = LOW;
int btn3Status = LOW;
int btn4Status = LOW;

volatile byte state = LOW;

// CAN data logging
float prec = 0;
float throttle, brake, core_temp_vcu, steering; // driver
float press_brake_front, press_brake_rear; // brakes
float imu_time, imu_general_status, imu_clock_status; // imu
float acc_x, acc_y, acc_z; // imu acc
float gyro_x, gyro_y, gyro_z; // imu gyro
float quaternion_0, quaternion_1, quaternion_2, quaternion_3; // imu quaternions
float roll, pitch, yaw; // imu eulers
float velocity;  // imu velocity
float gps_latitude, gps_longitude; // gps
float susp_fr, susp_fl, susp_rr, susp_rl; // suspensions
float temp_oil_1, temp_oil_2, temp_wat_1, temp_wat_2; // temperatures
long act_Val_1[4], act_Val_2[4];
// todo add fl and fr motors
float amk_actual_values1_rl, amk_actual_values2_rl, amk_setpoints_1_rl; // amk
float amk_actual_values1_rr, amk_actual_values2_rr, amk_setpoints_1_rr;

int index_diff_1[4] = {0x283, 0x284, 0x287, 0x288};
int index_diff_2[4] = {0x285, 0x286, 0x289, 0x290};
int index_diff_3[4] = {0x184, 0x185, 0x188, 0x189};
int page = 0;
int i1, i2=100;

unsigned long previousMillis; // Inizializzo variabile per il debouncing
unsigned int interval = 500; // Intervallo di attesa debouncing

String header =
	"time,throttle,brake,steering" // driver
	",press brake front,press brake rear" // brakes
	",imu time,imu general status,imu clock status" // imu
	",acc x,acc y,acc z" // imu acc
	",gyro x,gyro y,gyro z" // imu gyro
	",quaternion 0,quaternion 1,quaternion 2,quaternion 3" // imu quaternions
	",roll,pitch,yaw" // imu eulers
	",velocity" // imu velocity
	",latitude,longitude" // gps
	",susp fr,susp fl,susp rr,susp rl" // suspensions
	",temp oil 1,temp oil 2,temp wat 1,temp wat 2,core temp vcu"
    // ",amk 1 fl,amk 2 fr,amk setpoints fl"
    // ",amk 1 fr,amk 2 fr,amk setpoints fr"
    ",amk 1 rl,amk 2 rr,amk setpoints rl"  // amk
    ",amk 1 rr,amk 2 rr,amk setpoints rr";

char fileName[16]; // SDcard uses 8.3 names so 16 bytes is enough NOte room for the '\0' char is needed!
unsigned int nr = 1;
long totalVoltage;
File dataFile; // to save in SD
int message_count = 0;
CAN_FRAME incoming;

Display display;
// extern unsigned short LogoBLU[0x400];
// extern unsigned short Logo_ED[0x400];

const int analogInPin1 = A0;
const int analogInPin2 = A1;
const int analogInPin3 = A2;

bool start = false;

#endif // DATA_H
