#ifndef __para
#define __para
#include "ST_Include.h"
typedef struct  
{
	u16 Thr;
	u16 Yaw;
	u16 Rol;
	u16 Pit;
}ST_RC_Struct;   //遥控原始值结构体

typedef struct 
{
	float x;
	float y;
	float z;
}xyz_f_t;

typedef struct 
{
	s16 x;
	s16 y;
	s16 z;

}xyz_s16_t; 

typedef union
{
	uint8_t raw_data[64];
	struct
	{
		xyz_f_t Accel;
		xyz_f_t Gyro;
		xyz_f_t Mag;
		xyz_f_t vec_3d_cali;
		uint32_t mpu_flag;
		float Acc_Temperature;
		float Gyro_Temperature;
	}Offset;
}sensor_setup_t; 
extern sensor_setup_t sensor_setup;
#endif

