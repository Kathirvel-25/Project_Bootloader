/*
 * logdata.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef LOGDATA_H_
#define LOGDATA_H_


typedef struct
{
	char longitute[15];
	char latitude[15];
	char ns[2];
	char ew[2];

    float accel_x;
    float accel_y;
    float accel_z;

    float gyro_x;
    float gyro_y;
    float gyro_z;
}logdata_t;


extern logdata_t data_log;

#endif /* LOGDATA_H_ */
