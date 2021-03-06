#ifndef	DEFINE_H
#define	DEFINE_H

#include "types.h"
#include "e2prom.h"
#include "ud_str.h"
#include "commsub.h"


#define ISP_REV 20





#define CRC_YES 1
#define CRC_NO 0

#define BIG	1
#define SMALL 2


#define READ_VARIABLES      3
#define WRITE_VARIABLES     6
#define MULTIPLE_WRITE		16
#define CHECKONLINE			0x19
#define CHECKONLINE_WIHTCOM	 0x18

#define DATABUFLEN			137

#define ORIGINALADDRESSVALUE	100
#define CALIBRATION_OFFSET    128 //allows us to store FLASH_CALIBRATION as an U18_T

// 199 is the highest address we can use when storing variables in the flash memory
#define 	EEP_SERINALNUMBER_WRITE_FLAG	199 
#define 	TOTAL_EE_PARAMETERS		208
 
#define DHCP   1
#define STATIC 0

#define MODBUS 0 
#define TCP_IP 1 

#define BAC_MSTP 2
#define BAC_IP 3


#define WR_DESCRIPTION_SIZE			31
#define AR_DESCRIPTION_SIZE			29
#define ID_SIZE						3
#define AR_TIME_SIZE				46
#define WR_TIME_SIZE			    72
#define SCH_TIME_SIZE				1


#define PRODUCT_CM5		50
#define PRODUCT_MINI_BIG	35
#define PRODUCT_MINI_SMALL	35

typedef struct
{
 	U8_T protocal;
	U8_T serialNum[4];
	U8_T address;
	U8_T product_model;
	U8_T hardRev;
	U8_T baudrate;
	U8_T unit;
	U8_T switch_tstat_val;
	U8_T IspVer;
	U8_T PicVer;
//	U8_T UPDATE_STATUS;
	U8_T  base_addr;
	U8_T  tcp_type;   /* 0 -- DHCP, 1-- STATIC */
	U8_T  ip_addr[4];
	U8_T  mac_addr[6];
	U8_T  	subnet[4];
	U8_T  	getway[4];
	U16_T 	tcp_port;
	U8_T mini_type;
	U8_T  sub_port;
	U8_T zigbee;
}STR_MODBUS;

typedef	union
{
	unsigned int  word;
	unsigned char byte[2];
}UN_RELAY;

typedef	union
	{
		U8_T all[10];
		struct 
		{
			U8_T sec;				/* 0-59	*/
			U8_T min;    		/* 0-59	*/
			U8_T hour;      		/* 0-23	*/
			U8_T day;       		/* 1-31	*/
			U8_T week;  		/* 0-6, 0=Sunday	*/
			U8_T mon;     		/* 0-11	*/
			U8_T year;      		/* 0-99	*/
			U16_T day_of_year; 	/* 0-365	*/
			S8_T is_dst;        /* daylight saving time on / off */		
				
		}Clk;
	}UN_Time;
	 

extern UN_Time RTC;
extern U16_T far input_raw[32];
extern U16_T far output_raw[24];



extern STR_MODBUS far Modbus;

#define BASE_ADDR   0x30 

#define HW_REV	7
#define SW_REV	15
#define PIC_REV 0x01  // pic688


#define CM5_ADDRESS 254
#define PRODUCT_MODEL	50

// define flash address

enum{
	//EEP_IP = 0x19
	EEP_MAC = 0x06,	  // 6 bytes 0x06 - 0x0b
	EEP_IP = 0x19,  // 4 bytes	  0x19 - 0x1c
	EEP_SUBNET = 0x1d, // 4 bytes  0x1d - 0x20
//--- other thing
	EEP_SERIALNUMBER_LOWORD = 0 + USER_BASE_ADDR,             
	EEP_SERIALNUMBER_HIWORD = 2 + USER_BASE_ADDR,
	EEP_FIRMWARE_VERSION_NUMBER_LO = 4 + USER_BASE_ADDR,
	EEP_FIRMWARE_VERSION_NUMBER_HI,
	EEP_ADDRESS						= 6 + USER_BASE_ADDR,
	EEP_PRODUCT_MODEL,
	EEP_HARDWARE_REV,
 	EEP_BAUDRATE,				//	63
	EEP_PIC,
    EEP_ADDRESS_PLUG_N_PLAY ,
	EEP_UNIT,
	EEP_PROTOCAL,
	EEP_TCP_TYPE,
	EEP_MINI_TYPE,

	EEP_DAYLIGHT_ENABLE,   
	EEP_DAYLIGHT_STATUS,
	// registers needed for updating status
	EEP_UPDATE_STATUS = 16 + USER_BASE_ADDR,	


	EEP_SUBADDR1 = 17 + USER_BASE_ADDR,
	EEP_SUBADDR2,
	EEP_SUBADDR3,
	EEP_SUBADDR4,
	EEP_SUBADDR5,
	EEP_SUBADDR6,
	EEP_SUBADDR7,
	EEP_SUBADDR8,

 


	EEP_INFO_BYTE,

  	EEP_CALIBRATION , //  = 10 + USER_BASE_ADDR,
	EEP_UPDTE_STATUS ,	
	EEP_BASE_ADDRESS,

	EEP_INPUT1_RANGE,	  // 25							 
	EEP_INPUT2_RANGE,
	EEP_INPUT3_RANGE,
	EEP_INPUT4_RANGE,	
	EEP_INPUT5_RANGE,
	EEP_INPUT6_RANGE,
	EEP_INPUT7_RANGE,
	EEP_INPUT8_RANGE,
	EEP_INPUT9_RANGE,
	EEP_INPUT10_RANGE,

	EEP_INPUT1_FILTER, // 35
	EEP_INPUT2_FILTER,
	EEP_INPUT3_FILTER,
	EEP_INPUT4_FILTER,
	EEP_INPUT5_FILTER,
	EEP_INPUT6_FILTER,
	EEP_INPUT7_FILTER,
	EEP_INPUT8_FILTER,
	EEP_INPUT9_FILTER,
	EEP_INPUT10_FILTER,

	
	EEP_INPUT1_CAL,
	EEP_INPUT2_CAL = EEP_INPUT1_CAL + 2,
	EEP_INPUT3_CAL = EEP_INPUT1_CAL + 4,
	EEP_INPUT4_CAL = EEP_INPUT1_CAL + 6,
	EEP_INPUT5_CAL = EEP_INPUT1_CAL + 8,
	EEP_INPUT6_CAL = EEP_INPUT1_CAL + 10,
	EEP_INPUT7_CAL = EEP_INPUT1_CAL + 12,
	EEP_INPUT8_CAL = EEP_INPUT1_CAL + 14,
	EEP_INPUT9_CAL = EEP_INPUT1_CAL + 16,
	EEP_INPUT10_CAL = EEP_INPUT1_CAL + 18,

	EEP_DI_TYPE1 = EEP_INPUT10_CAL + 2,  // 65
	EEP_DI_TYPE2,
	EEP_DI_TYPE3,
	EEP_DI_TYPE4,
	EEP_DI_TYPE5,
	EEP_DI_TYPE6,
	EEP_DI_TYPE7,
	EEP_DI_TYPE8,

	
	EEP_OUTPUT_LOW,   /* OUTPUT GROUP1 RELAY 1- 8 */
	EEP_OUTPUT_HIGH,   /* K9 and K10 */

	EEP_SWITCH = 146 + USER_BASE_ADDR, 
	EEP_PRIORTITY,

	EEP_DI_ENABLE_LOW,   // Only ON/OFF  170
  	EEP_DI_ENABLE_HIGH,	// Only ON/OFF  171
	EEP_AI_ENABLE_LOW,   
  	EEP_AI_ENABLE_HIGH,
	EEP_DINPUT_AM_LOW,   // 
	EEP_DINPUT_AM_HIGH,   //  
	EEP_OUTPUT_AM_LOW,
	EEP_OUTPUT_AM_HIGH, 
	EEP_AINPUT_AM_LOW,   // 
	EEP_AINPUT_AM_HIGH,   //  


//	EEP_FIRST_TIME,    // whether have tstat address
	EEP_SERIALNUMBER_WRITE_FLAG,

	EEP_DIS_TEMP_NUM,
	EEP_DIS_TEMP_INTERVAL,
	EEP_DIS_TEMP_SEQ_FIRST,
	EEP_DIS_TEMP_SEQ_LAST = EEP_DIS_TEMP_SEQ_FIRST + 9,

	EEP_PORT_LOW,
	EEP_PORT_HIGH,

	EEP_INSTANCE_LOW,
	EEP_INSTANCE_HIGH,
	EEP_STATION_NUM,
	EEP_ZIGBEE_EN,


	MAX_EEP_CONSTRANGE = 208,
};




#define SCHEDUAL_MODBUS_ADDRESS		200

enum {

	MODBUS_SERIALNUMBER_LOWORD = 0,             
	MODBUS_SERIALNUMBER_HIWORD	= 2,
	MODBUS_FIRMWARE_VERSION_NUMBER_LO   	= 4  ,
	MODBUS_FIRMWARE_VERSION_NUMBER_HI,
	MODBUS_ADDRESS					= 6,
	MODBUS_PRODUCT_MODEL,
	MODBUS_HARDWARE_REV,

 	
//	MODBUS_INIT_WR_TIME, 
	MODBUS_PIC = 9,
    MODBUS_ADDRESS_PLUG_N_PLAY= 10,
	MODBUS_TIME_ZONE = 11,	

	MODBUS_BAUDRATE,	 
//	MODBUS_DAYLIGHT_ENABLE,
//	MODBUS_DAYLIGHT_STATUS,
//	MODBUS_RESET_FLASH,	
	MODBUS_ISP_VER = 14,

// registers needed for updating status
	MODBUS_UPDATE_STATUS = 16,	
	MODBUS_UNIT =17,



//------------------ FOR SUB TSTAT ------------------------------
	// 193 - 203

	MODBUS_TOTAL_NO ,  // NUMBER OF ZONES
	MODBUS_TOTAL_HEAT, //		NUMBER OF ZONES CALLING FOR HEAT
	MODBUS_TOTAL_COOL, //		NUMBER OF ZONES CALLING FOR COOLING	

//	MODBUS_TEST = 180,
	MODBUS_REFRESH_STATUS, // 196  


//  add ethernet register
	MODBUS_DEMO_ENABLE = 31,
	MODBUS_PROTOCAL = 32,
	MODBUS_RESET_PARAMETER = 33,
	MODBUS_MINI_TYPE,
	MODBUS_INSTANCE,
	MODBUS_STATION_NUM,
	MODBUS_SUB_PORT,
	MODBUS_ZIGBEE_EN,
	MODBUS_CLEAR_SCAN_DB = 39,

	MODBUS_ENABLE_WRITE_MAC = 93,

	/* 100 ~ 133 */
   	MODBUS_MAC_1 = 100,
	MODBUS_MAC_2,
	MODBUS_MAC_3,
	MODBUS_MAC_4,
	MODBUS_MAC_5,
	MODBUS_MAC_6,

	MODBUS_TCP_TYPE = 106,	  // DHCP OR STATIC

	MODBUS_IP_1,	  // IP have 4 bytes
	MODBUS_IP_2,
	MODBUS_IP_3,
	MODBUS_IP_4,

	MODBUS_SUBNET_1,	  // subnet have 4 bytes
	MODBUS_SUBNET_2,
	MODBUS_SUBNET_3,
	MODBUS_SUBNET_4,

	MODBUS_GETWAY_1,	  // getway have 4 bytes
	MODBUS_GETWAY_2,
	MODBUS_GETWAY_3,
	MODBUS_GETWAY_4,

	MODBUS_TCPSERVER,		// no used
	MODBUS_TCP_LISTEN_PORT,	

	MODBUS_TIMER_ADDRESS = SCHEDUAL_MODBUS_ADDRESS, // 200
	/*
	120 TO 133 reserved
		
	*/
	
	MODBUS_SUBADDR_FIRST = 300 ,	// 193
	MODBUS_SUBADDR_LAST = 400 , // 200

	MODBUS_TEST = 7000,
	MODBUS_TEST_50 = 7049,


	MODBUS_OUT_NUM = 8000,
	MODBUS_IN_NUM = 8001,
	MODBUS_VAR_NUM = 8002,
	MODBUS_CON_NUM = 8003,
	MODBUS_WR_NUM = 8004,
	MODBUS_AR_NUM = 8005,
	MODBUS_PRG_NUM = 8006,
	MODBUS_TBL_NUM = 8007,
	MODBUS_TZ_NUM = 8008,
	MODBUS_AMON_NUM = 8009,
	MODBUS_GRP_NUM = 8010,
	MODBUS_ARRAY_NUM = 8011,
	MODBUS_ALARM_NUM = 8012,
	MODBUS_UNIT_NUM = 8013,
	MODBUS_USER_NAME_NUM = 8014,
	MODBUS_ALARM_SET_NUM = 8015,
	MOSBUS_SUB_NO,

	MODBUS_OUTPUT_FIRST = 8020,      // Input 1, register 100
	MODBUS_OUTPUT_LAST = MODBUS_OUTPUT_FIRST + MAX_OUTS * sizeof(Str_out_point),
	
	MODBUS_INPUT_FIRST,
	MODBUS_INPUT_LAST = MODBUS_INPUT_FIRST + MAX_INS * sizeof(Str_in_point),

	MODBUS_WR_FIRST, 
	MODBUS_WR_LAST = MODBUS_WR_FIRST + MAX_WR * sizeof(Str_weekly_routine_point),

	MODBUS_AR_FIRST, 
	MODBUS_AR_LAST = MODBUS_AR_FIRST + MAX_AR * sizeof(Str_annual_routine_point),

	MODBUS_WR_TIME_FIRST, 
	MODBUS_WR_TIME_LAST = MODBUS_WR_TIME_FIRST + MAX_WR * MAX_SCHEDULES_PER_WEEK,

	MODBUS_AR_TIME_FIRST, 
	MODBUS_AR_TIME_LAST = MODBUS_AR_TIME_FIRST + MAX_AR * AR_DATES_SIZE,

	MODBUS_SUB_INFO_FIRST = 10800,
	MODBUS_SUB_INFO_LAST = MODBUS_SUB_INFO_FIRST + SUB_NO * 20,
}; 




#endif
