#ifndef CAN_H
#define CAN_H

#include "data.h"

void bytes2float(unsigned char* bytes, int start, int end, bool reversed, float* x) {
    int count = end - start;
    char buffer[count];
    
    for (int i = 0; i < count; i++) {
        char value = bytes[start + i];
        buffer[i] = value;
    }

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

void logFrame(CAN_FRAME &frame) {
    switch (frame.id) {
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
        default:
            break;
    }
}

#endif // CAN_H
