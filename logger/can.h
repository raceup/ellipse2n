#ifndef CAN_H
#define CAN_H

#include "data.h"

/**
 * Takes start:end bytes from list and merges them
 * todo: TEST
*/
void bytes2float(unsigned char* bytes, int start, int end, bool reversed, float* x) {
    int count = end - start;
    char buffer[count];
    
    for (int i = 0; i < count; i++) {
        char value = bytes[start + i];
        buffer[i] = value;
    }

    /*todo: to test before employing!!!
    if (reversed) {
        for (int i = 0; i < count; i++) {
            char tmp = buffer[i];
            buffer[i] = buffer[count - 1 - i];  // swap
            buffer[count - 1 - i] = tmp;
        }
    }*/

    *x = *(float *)&buffer;
}

void byte2float8(CAN_FRAME &frame, float* x, float* x1) {
    char vBuffer[4], vBuffer1[4];
    
    for (int count = 0; count < 4; count++) {
        vBuffer[count] = frame.data.bytes[count];
    }
    for (int count = 4; count < 8; count++) {
        vBuffer1[count - 4] = frame.data.bytes[count];
    }
    
    *x = *(float *)&vBuffer;
    *x1 = *(float *)&vBuffer1;
}

void byte2float4(CAN_FRAME &frame, float* x) {
    char vBuffer[4];
    
    for (int count = 0; count < 4; count++) {
        vBuffer[count] = frame.data.bytes[count];
    }
    
    *x = *(float *)&vBuffer;
}

void byte2int(CAN_FRAME &frame, int* x, int* x1, int* x2, int* x3) {
    char vBuffer[2], vBuffer1[2], vBuffer2[2], vBuffer3[2];
    
    for (int count = 0; count < 2; count++) {
        vBuffer[count] = frame.data.bytes[count];
    }
    for (int count = 2; count < 4; count++) {
        vBuffer1[count-2] = frame.data.bytes[count];
    }
    for (int count = 4; count < 6; count++) {
        vBuffer2[count-4] = frame.data.bytes[count];
    }
    for (int count = 6; count < 8; count++) {
        vBuffer3[count-6] = frame.data.bytes[count];
    }
    
    *x = *(float *)&vBuffer;
    *x1 = *(float *)&vBuffer1;
    *x2 = *(float *)&vBuffer2;
    *x3 = *(float *)&vBuffer3;
}


void parseImuCouple(CAN_FRAME &frame, float* x_0, float* x_1) {
    bytes2float(frame.data.bytes, 0, 4, true, x_0);
    bytes2float(frame.data.bytes, 4, 8, true, x_1);
}


void parseImuTriple(CAN_FRAME &frame, float* x_0, float* x_1, float* x_2) {
    bytes2float(frame.data.bytes, 0, 2, true, x_0);
    bytes2float(frame.data.bytes, 2, 4, true, x_1);
    bytes2float(frame.data.bytes, 4, 6, true, x_2);
}


void parseImuQuaternion(CAN_FRAME &frame, float* x_0, float* x_1, float* x_2, float* x_3) {
    bytes2float(frame.data.bytes, 0, 2, true, x_0);
    bytes2float(frame.data.bytes, 2, 4, true, x_1);
    bytes2float(frame.data.bytes, 4, 6, true, x_2);
    bytes2float(frame.data.bytes, 6, 8, true, x_3);
}

void printFrame(CAN_FRAME &frame) {
    switch (frame.id) {
        case 0x13:
            byte2float8(frame, &throttle, &brake);
            break;
        case 0x14:
            byte2float8(frame, &steering, &core_temp_vcu);
            break;
        case 0x15:
            byte2float8(frame, &press_brake_front, &press_brake_rear);
            break;
        case 0x60:
            byte2float8(frame, &susp_fr, &susp_fl);
            break;
        case 0x61:
            byte2float8(frame, &susp_rr, &susp_rl);
            break;
        case 0x62:
            byte2float8(frame, &temp_oil_1, &temp_oil_2);
            break;
        case 0x63:
            byte2float8(frame, &temp_wat_1, &temp_wat_2);
            break;
        case 0x30:
            totalVoltage = frame.data.bytes[3] + frame.data.bytes[2] * pow(2, 8) + frame.data.bytes[1] * pow(2, 16) + frame.data.bytes[0] * pow(2, 24);
            break;
        case 0x100:
            bytes2float(frame.data.bytes, 0, 4, true, &imu_time);
            bytes2float(frame.data.bytes, 4, 6, true, &imu_general_status);
            bytes2float(frame.data.bytes, 6, 8, true, &imu_clock_status);
            break;
        case 0x121:
            parseImuTriple(frame, &acc_x, &acc_y, &acc_z);
            break;
        case 0x122:
            parseImuTriple(frame, &gyro_x, &gyro_y, &gyro_z);
            break;
        case 0x131:
            parseImuQuaternion(frame, &quaternion_0, &quaternion_1, &quaternion_2, &quaternion_3);
            break;
        case 0x132:
            parseImuTriple(frame, &roll, &pitch, &yaw);
            break;
        case 0x161:
            bytes2float(frame.data.bytes, 0, 4, true, &velocity);
            break;
        case 0x175:
            parseImuCouple(frame, &gps_latitude, &gps_longitude);
            break;
        // aml fl
        case 0x283:
            // bytes2float(frame.data.bytes, 0, 8, false, &amk_actual_values1_fl);
            break;
        case 0x285:
            // bytes2float(frame.data.bytes, 0, 8, false, &amk_actual_values2_fl);
            break;
        case 0x184:
            // bytes2float(frame.data.bytes, 0, 8, false, &amk_setpoints_1_fl);
            break;
        // aml fr
        case 0x284:
            // bytes2float(frame.data.bytes, 0, 8, false, &amk_actual_values1_fr);
            break;
        case 0x286:
            // bytes2float(frame.data.bytes, 0, 8, false, &amk_actual_values2_fr);
            break;
        case 0x185:
            // bytes2float(frame.data.bytes, 0, 8, false, &amk_setpoints_1_fr);
            break;
        // aml rl
        case 0x287:
            bytes2float(frame.data.bytes, 0, 8, false, &amk_actual_values1_rl);
            break;
        case 0x289:
            bytes2float(frame.data.bytes, 0, 8, false, &amk_actual_values2_rl);
            break;
        case 0x188:
            bytes2float(frame.data.bytes, 0, 8, false, &amk_setpoints_1_rl);
            break;
        // aml rr
        case 0x288:
            bytes2float(frame.data.bytes, 0, 8, false, &amk_actual_values1_rl);
            break;
        case 0x290:
            bytes2float(frame.data.bytes, 0, 8, false, &amk_actual_values2_rl);
            break;
        case 0x189:
            bytes2float(frame.data.bytes, 0, 8, false, &amk_setpoints_1_rl);
            break;
        default:
            break;
    }
}

#endif // CAN_H
