#include "main.h"
#include "globaldef.h"
#include "globaltyp.h"
#include "globalval.h"
#include "IMU.H"
#include "LSM6DSM_REG.H"
#include <math.h>
#include "control.h"
#include "gd25q_driver.h"
#include <stdio.h>
#include "user_uart.h"
#include <string.h>
#include "kalman.h"
#include "lora.h"




int32_t lsm6dsm_write_reg(SPI_Type *handle, uint8_t reg, uint8_t *pbuf, uint16_t len)
{
	uint8_t	i;


//	reg |= 0x80;

	GCS_Lo;


	SPIx_ReadWriteByte(handle, reg);
	for(i=0;i<len;i++)
	{
		 SPIx_ReadWriteByte(handle, pbuf[i]);
//		 i++;
	}

	GCS_Hi;
	return 0;
}






int32_t lsm6dsm_read_reg(SPI_Type *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{


	uint8_t i;


	reg |= 0x80;

	GCS_Lo;


	SPIx_ReadWriteByte(handle, reg);
	for(i=0;i<len;i++)
	{
		 *(bufp+i) = SPIx_ReadWriteByte(handle, 0xFF);
	}
	GCS_Hi;
	return 0;
}




void lsm6dsmACCInit(void)
{
//	lsm6dsm_xl_power_mode_set(SPI2, LSM6DSM_XL_NORMAL);
	lsm6dsm_xl_full_scale_set(SPI2, LSM6DSM_4g);
	lsm6dsm_xl_data_rate_set(SPI2, LSM6DSM_XL_ODR_52Hz);
}



void lsm6dsmDRYInit(void)
{

	lsm6dsm_gy_power_mode_set(SPI2, LSM6DSM_GY_HIGH_PERFORMANCE);
	lsm6dsm_gy_full_scale_set(SPI2, LSM6DSM_1000dps);
	lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_1k66Hz);

}




void lsm6dsmHiInit(void)
{
	uint8_t	devid;
	uint8_t rst;

	
	lsm6dsm_int1_route_t  	int1rout;
	lsm6dsm_int2_route_t	int2rout;


	lsm6dsm_device_id_get(&devid);
//INT1 motion detect and wakeup mcu
//int2 Data Ready
	if(devid == 0x6A)
		{


			lsm6dsm_reset_set(SPI2, PROPERTY_ENABLE);

			do 
			{
			  lsm6dsm_reset_get(SPI2, &rst);
			} while (rst);
			FL_DelayMs(200);


//test ok/////////////////////////////////////////////////////////////
//			int2rout.int2_drdy_g = PROPERTY_ENABLE;
//			int1rout.int1_drdy_xl = PROPERTY_ENABLE;


		//	lsm6dsm_xl_power_mode_set(SPI2, LSM6DSM_XL_NORMAL);
			lsm6dsm_xl_full_scale_set(SPI2, LSM6DSM_2g);
			lsm6dsm_xl_data_rate_set(SPI2, LSM6DSM_XL_ODR_52Hz);


//			lsm6dsm_gy_power_mode_set(SPI2, LSM6DSM_GY_HIGH_PERFORMANCE);
			lsm6dsm_gy_power_mode_set(SPI2, LSM6DSM_GY_NORMAL);

			lsm6dsm_gy_full_scale_set(SPI2, LSM6DSM_1000dps);
			lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_208Hz);
//			lsm6dsm_gy_ui_high_pass_set(SPI2, 1);
			FlagStatusSet(&FlagGlobal, Flag_InitDy);
//			FL_DelayMs(70);

			lsm6dsm_pin_int1_route_get(SPI2, &int1rout);
			int1rout.int1_drdy_xl = PROPERTY_ENABLE;
			lsm6dsm_pin_int1_route_set(SPI2, int1rout);
			lsm6dsm_pin_int2_route_get(SPI2, &int2rout);
			int2rout.int2_drdy_g = PROPERTY_ENABLE;
			lsm6dsm_pin_int2_route_set(SPI2, int2rout);
//			lsm6dsm_block_data_update_set(SPI2, PROPERTY_ENABLE);
/////////////////////////////////////////////////////////////////////



//		/* Set XL and Gyro Output Data Rate */
//		lsm6dsm_xl_data_rate_set(SPI2, LSM6DSM_XL_ODR_52Hz);
////		lsm6dsm_xl_data_rate_get(SPI2, &xlrate);
//
//		lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_12Hz5);
//		/* Set 2g full XL scale and 250 dps full Gyro */
//		lsm6dsm_xl_full_scale_set(SPI2, LSM6DSM_2g);
////		lsm6dsm_xl_full_scale_get(SPI2, &fullscal);
//
//		
//		lsm6dsm_gy_full_scale_set(SPI2, LSM6DSM_500dps);
//		/* Set duration for Activity detection to 9.62 ms (= 2 * 1 / ODR_XL) */
//		lsm6dsm_wkup_dur_set(SPI2, 0x02);
//		/* Set duration for Inactivity detection to 4.92 s (= 2 * 512 / ODR_XL) */
//		lsm6dsm_act_sleep_dur_set(SPI2, 0x01);
//		/* Set Activity/Inactivity threshold to 62.5 mg */
//		lsm6dsm_wkup_threshold_set(SPI2, 0x03);
//		/* Inactivity configuration: acc to 12.5 LP, gyro to Power-Down */
//		lsm6dsm_act_mode_set(SPI2, LSM6DSM_XL_12Hz5_GY_PD);
//		/* Enable interrupt generation on Inactivity INT1 pin */
//		lsm6dsm_pin_int1_route_get(SPI2, &int1rout);
//		int1rout.int1_inact_state = PROPERTY_ENABLE;
//		lsm6dsm_pin_int1_route_set(SPI2, int1rout);
//		/* Enable interrupt generation on Dry Ready INT2 pin */
//		lsm6dsm_pin_int2_route_get(SPI2, &int2rout);
//		int2rout.int2_drdy_g = PROPERTY_ENABLE;
//		lsm6dsm_pin_int2_route_set(SPI2, int2rout);

		}
	else
		{
			FlagStatusSet(&FlagErrorStat, Err_IMU_Fail);

		}



}





void lsm6dsmActInit(void)
{
	uint8_t	devid;
	uint8_t rst;
//	lsm6dsm_fs_xl_t fullscal;
//	lsm6dsm_odr_xl_t xlrate;
//	lsm6dsm_fs_g_t   fullg;
//	lsm6dsm_inact_en_t  inact;

	
//	uint8_t retdata;
//	uint8_t drdy;
//	int16_t data_raw[3];
//	float val_st_off[3];
//	float val_st_on[3];
//	float test_val[3];
//	uint8_t i,j;


	
	
	lsm6dsm_int1_route_t  	int1rout;
	lsm6dsm_int2_route_t	int2rout;
//	Dev_ctx.handle = SPI2;
//	Dev_ctx.read_reg = platform_read;
//	Dev_ctx.write_reg = platform_write;
//	Dev_ctx.mdelay = FL_DelayMs;


//	int1rout.int1_sign_mot = PROPERTY_ENABLE;
//	int1rout.int1_inact_state = PROPERTY_ENABLE;
//	int2rout.int2_drdy_g = PROPERTY_ENABLE;
//	int1rout.int1_drdy_xl = PROPERTY_ENABLE;

	lsm6dsm_device_id_get(&devid);
//INT1 motion detect and wakeup mcu
//int2 Data Ready
	if(devid == 0x6A)
		{


			lsm6dsm_reset_set(SPI2, PROPERTY_ENABLE);

			do 
			{
			  lsm6dsm_reset_get(SPI2, &rst);
			} while (rst);
			FL_DelayMs(200);


//test ok/////////////////////////////////////////////////////////////
//			int2rout.int2_drdy_g = PROPERTY_ENABLE;
//			int1rout.int1_drdy_xl = PROPERTY_ENABLE;
//
//			lsm6dsm_xl_power_mode_set(SPI2, LSM6DSM_XL_NORMAL);
//			lsm6dsm_xl_full_scale_set(SPI2, LSM6DSM_4g);
//			lsm6dsm_xl_data_rate_set(SPI2, LSM6DSM_XL_ODR_12Hz5);
//			lsm6dsm_gy_power_mode_set(SPI2, LSM6DSM_XL_NORMAL);
//			lsm6dsm_gy_full_scale_set(SPI2, LSM6DSM_500dps);
//			lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_12Hz5);
//			lsm6dsm_pin_int1_route_set(SPI2, int1rout);
//			lsm6dsm_pin_int2_route_set(SPI2, int2rout);
//			lsm6dsm_block_data_update_set(SPI2, PROPERTY_ENABLE);
/////////////////////////////////////////////////////////////////////



		/* Set XL and Gyro Output Data Rate */
//		lsm6dsm_xl_data_rate_set(SPI2, LSM6DSM_XL_ODR_52Hz);
//
////		lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_12Hz5);
//		lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_208Hz);
//
//		/* Set 2g full XL scale and 250 dps full Gyro */
//		lsm6dsm_xl_full_scale_set(SPI2, LSM6DSM_2g);
//


		//	lsm6dsm_xl_power_mode_set(SPI2, LSM6DSM_XL_NORMAL);
			lsm6dsm_xl_full_scale_set(SPI2, LSM6DSM_2g);
			lsm6dsm_xl_data_rate_set(SPI2, LSM6DSM_XL_ODR_52Hz);


//			lsm6dsm_gy_power_mode_set(SPI2, LSM6DSM_GY_HIGH_PERFORMANCE);
			lsm6dsm_gy_power_mode_set(SPI2, LSM6DSM_GY_NORMAL);

			lsm6dsm_gy_full_scale_set(SPI2, LSM6DSM_1000dps);
			lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_208Hz);
//			lsm6dsm_gy_ui_high_pass_set(SPI2, 1);
			FlagStatusSet(&FlagGlobal, Flag_InitDy);
			FL_DelayMs(70);


	
//		lsm6dsm_gy_full_scale_set(SPI2, LSM6DSM_1000dps);
		/* Set duration for Activity detection to 9.62 ms (= 2 * 1 / ODR_XL) */
		lsm6dsm_wkup_dur_set(SPI2, 0x01);
		/* Set duration for Inactivity detection to 4.92 s (= 2 * 512 / ODR_XL) */
		lsm6dsm_act_sleep_dur_set(SPI2, 0x01);
		/* Set Activity/Inactivity threshold to 62.5 mg */
		lsm6dsm_wkup_threshold_set(SPI2, 0x01); //wakeup 1 lsb = FS_XL/2^6
		/* Inactivity configuration: acc to 12.5 LP, gyro to Power-Down */
		lsm6dsm_act_mode_set(SPI2, LSM6DSM_XL_12Hz5_GY_SLEEP);
		/* Enable interrupt generation on Inactivity INT1 pin */
		lsm6dsm_pin_int1_route_get(SPI2, &int1rout);
		int1rout.int1_inact_state = PROPERTY_ENABLE;
		lsm6dsm_pin_int1_route_set(SPI2, int1rout);
		/* Enable interrupt generation on Dry Ready INT2 pin */
		lsm6dsm_pin_int2_route_get(SPI2, &int2rout);
		int2rout.int2_drdy_g = PROPERTY_ENABLE;
		lsm6dsm_pin_int2_route_set(SPI2, int2rout);

		}
	else
		{
			FlagStatusSet(&FlagErrorStat, Err_IMU_Fail);

		}



}



void lsm6dsmDeInit(void)
{
	uint8_t	devid;
	
//	lsm6dsm_int1_route_t  	int1rout;
//	lsm6dsm_int2_route_t	int2rout;
//
//	int1rout.int1_sign_mot = PROPERTY_ENABLE;
//	
//	int2rout.int2_drdy_g = PROPERTY_ENABLE;

//	lsm6dsm_device_id_get(&devid);
//INT1 motion detect and wakeup mcu
//int2 Data Ready

	lsm6dsm_reset_set(SPI2, 1);

	FL_DelayMs(10);

	lsm6dsm_xl_data_rate_set(SPI2, LSM6DSM_XL_ODR_OFF);

	lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_OFF);

	
	
//	if(devid == 0x6A)
//		{
//			lsm6dsm_xl_data_rate_set(SPI2, LSM6DSM_XL_ODR_OFF);

//			lsm6dsm_gy_data_rate_set(SPI2, LSM6DSM_GY_ODR_OFF);
//		}
//	else
//		{
//			FlagStatusSet(&FlagErrorStat, Err_IMU_Fail);
//		}



}


void GetAcc(XLRwaTyp *xlraw)
{
	lsm6dsm_acceleration_raw_get(SPI2, (int16_t *)xlraw);
}

void GetGry(GryRwaTyp *grywaw)
{
	lsm6dsm_angular_rate_raw_get(SPI2, (int16_t *)grywaw);
}

//void GetDryrate0(void)
//{
////	static		float 	xdyrate[IMUDataLength];
////	static		float 	ydyrate[IMUDataLength];
////	static		float 	zdyrate[IMUDataLength];
//	float				xtmpt, ytmpt, ztmpt;
////	static      float   rate[IMUDataLength];
//	static		float	sumx = 0;
//	static		float	sumy = 0;
//	static		float	sumz = 0;
//	static		float	sumrate = 0;
//	float				sumratetemp;
//	
//	static      uint16_t i = 0, j = 0;
//	uint8_t		buf[50];
//	static      bool	flag_xr_over, flag_yr_over, flag_zr_over;
//	static      bool	flag_dry_over;
//	static		float	xLmg;
//	static		float	yLmg;
//	static		float	zLmg;
//	float			mg;
//	static		bool	flag_init;
//	static		uint8_t	accstatic;
//
//	if(flag_init == false)
//		{
//			flag_init = true;
//			lsm6dsmHiInit();
//			FL_DelayMs(200);
//		}
//	
//
//    if(FlagStatusIs(FlagGlobal, Flag_GryReady))
//    	{
//    		FlagStatusClear(&FlagGlobal, Flag_GryReady);
//			GetAcc((XLRwaTyp *)&XYZXLRaw.XLRwa);
////			FL_DelayMs(1);
//			GetGry((GryRwaTyp *)&XYZGyRaw.GryRwa[XYZGyRaw.nextpoint]);
//			if(!FlagStatusIs(FlagGlobal, Flag_InitDy))
//				{
//					XYZGyRaw.nextpoint++;
//					XYZGyRaw.nextpoint %= DryDatalebgth;
//					xLmg = lsm6dsm_from_fs2g_to_mg(XYZXLRaw.XLRwa.xraw);
//					yLmg = lsm6dsm_from_fs2g_to_mg(XYZXLRaw.XLRwa.yraw);
//					zLmg = lsm6dsm_from_fs2g_to_mg(XYZXLRaw.XLRwa.zraw);
//					mg = sqrt(pow(xLmg, 2) + pow(yLmg, 2) + pow(zLmg, 2));
////					TogLED;
//					if(mg < 1100)
//						{
//							accstatic = TRUE;
//						}
//					else
//						{
//							accstatic = FALSE;
//
//						}
//					
//				}
//			else
//				{
//					DyDiscardCnt++;
//					if(DyDiscardCnt == 1)//135)
//						{
//							DyDiscardCnt = 0;
//							FlagStatusClear(&FlagGlobal, Flag_InitDy);
//						}
//				}
//
//    	}
//
//
//
//	if(accstatic == true)
//		{
//			LEDOn;
//			if(XYZGyRaw.startpoint != XYZGyRaw.nextpoint)
//				{
//
////					xdyrate[i] = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].xraw);
////					ydyrate[i] = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].yraw);
////					zdyrate[i] = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].zraw);
//
//					sumx += xtmpt = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].xraw);
//					sumy += ytmpt = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].yraw);
//					sumz += ztmpt = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].zraw);
//
//					i++;
//
//					XYZGyRaw.startpoint++;
//					XYZGyRaw.startpoint %= DryDatalebgth;
////					sumx += xdyrate[i];
////					sumy += ydyrate[i];
////					sumz += zdyrate[i];
////					if(i == IMUDataLength - 1)
//					if(i == IMUDataLength)
//						{
//							
//							sumx /= IMUDataLength;
//							sumy /= IMUDataLength;
//							sumz /= IMUDataLength;
//							if(fabs(xtmpt - sumx)<2)
//								{
//									XYZGyRaw.xrrate0 = sumx;
//									flag_xr_over = true;
//								}
//							if(fabs(ytmpt- sumy)<2)
//								{
//									XYZGyRaw.yrrate0 = sumy;
//									flag_yr_over = true;
//								}
//							if(fabs(ztmpt - sumz)<2)
//								{
//									XYZGyRaw.zrrate0 = sumz;
//									flag_zr_over = true;
//								}
//							sumx = 0;
//							sumy = 0;
//							sumz = 0;
//							i = 0;
//						}
//
//				
//				
//					XYZGyRaw.xrrate = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].xraw) - XYZGyRaw.xrrate0;
//					XYZGyRaw.yrrate = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].yraw) - XYZGyRaw.yrrate0;
//					XYZGyRaw.zrrate = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].zraw) - XYZGyRaw.zrrate0;
////					rate[j] = sqrt(pow(XYZGyRaw.xrrate, 2) + pow(XYZGyRaw.yrrate, 2) + pow(XYZGyRaw.zrrate, 2));
////					XYZGyRaw.rate = rate[j];
//					sumrate += sumratetemp = sqrt(pow(XYZGyRaw.xrrate, 2) + pow(XYZGyRaw.yrrate, 2) + pow(XYZGyRaw.zrrate, 2));
//					j++;
//					
////					sumrate += rate[j];
//					if(j == IMUDataLength)
//						{
//							
//							sumrate /= IMUDataLength;
//				
//							if(fabs(sumratetemp - sumrate)<0.5)
//								{
//									XYZGyRaw.rate0 = sumrate;
////									LEDOn;//debug lysq
//									
//									flag_dry_over = true;
//								}
//							sumrate = 0;
//							j = 0;
//						}
//
//				
//				
//					if(flag_dry_over == true && flag_zr_over == true && flag_yr_over == true && flag_xr_over == true)
//						{
//							flag_dry_over = false;
//							flag_zr_over = false;
//							flag_yr_over = false;
//							flag_xr_over = false;
//							LEDOff;
//							FlagStatusClear(&FlagGlobal, Flag_GetG0);
//							flag_init = false;
//							accstatic = false;
//							lsm6dsmActInit();
//						}
//				
//
//			
//				}
//
//
//
//		}
//		else
//		{
//			i = 0;
//			sumx = 0;
//			sumy = 0;
//			sumz = 0;
//			j = 0;
//			sumrate = 0;
//		}
//
//
//
//}

void GetDryrate0(void)
{
//	static		float 	xdyrate[IMUDataLength];
//	static		float 	ydyrate[IMUDataLength];
//	static		float 	zdyrate[IMUDataLength];
	float				xtmpt, ytmpt, ztmpt;
//	static      float   rate[IMUDataLength];
	static		float	sumx = 0;
	static		float	sumy = 0;
	static		float	sumz = 0;
	static		float	sumrate = 0;
	float				sumratetemp;
	
	static      uint16_t i = 0, j = 0;
	uint8_t		buf[50];
	static      bool	flag_xr_over, flag_yr_over, flag_zr_over;
	static      bool	flag_dry_over;
	static		float	xLmg;
	static		float	yLmg;
	static		float	zLmg;
	float			mg;
	static		bool	flag_init;
	static		uint8_t	accstatic;

	if(flag_init == false)
		{
			flag_init = true;
			lsm6dsmHiInit();
			FL_DelayMs(200);
		}
	

    if(FlagStatusIs(FlagGlobal, Flag_GryReady))
    	{
    		FlagStatusClear(&FlagGlobal, Flag_GryReady);
			GetAcc((XLRwaTyp *)&XYZXLRaw.XLRwa);
//			FL_DelayMs(1);
			GetGry((GryRwaTyp *)&XYZGyRaw.GryRwa[XYZGyRaw.nextpoint]);
			if(!FlagStatusIs(FlagGlobal, Flag_InitDy))
				{
					XYZGyRaw.nextpoint++;
					XYZGyRaw.nextpoint %= DryDatalebgth;
					xLmg = lsm6dsm_from_fs2g_to_mg(XYZXLRaw.XLRwa.xraw);
					yLmg = lsm6dsm_from_fs2g_to_mg(XYZXLRaw.XLRwa.yraw);
					zLmg = lsm6dsm_from_fs2g_to_mg(XYZXLRaw.XLRwa.zraw);
					mg = sqrt(pow(xLmg, 2) + pow(yLmg, 2) + pow(zLmg, 2));
//					TogLED;
					if(mg < 1100)
						{
							accstatic = TRUE;
						}
					else
						{
							accstatic = FALSE;

						}
					
				}
			else
				{
					DyDiscardCnt++;
					if(DyDiscardCnt == 1)//135)
						{
							DyDiscardCnt = 0;
							FlagStatusClear(&FlagGlobal, Flag_InitDy);
						}
				}

    	}



	if(accstatic == true)
		{
			LEDOn;
			if(XYZGyRaw.startpoint != XYZGyRaw.nextpoint)
				{

//					xdyrate[i] = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].xraw);
//					ydyrate[i] = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].yraw);
//					zdyrate[i] = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].zraw);

//					sumx += xtmpt = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].xraw);
//					sumy += ytmpt = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].yraw);
//					sumz += ztmpt = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].zraw);

					sumx += xtmpt = XYZGyRaw.GryRwa[XYZGyRaw.startpoint].xraw;
					sumy += ytmpt = XYZGyRaw.GryRwa[XYZGyRaw.startpoint].yraw;
					sumz += ztmpt = XYZGyRaw.GryRwa[XYZGyRaw.startpoint].zraw;




					i++;

					XYZGyRaw.startpoint++;
					XYZGyRaw.startpoint %= DryDatalebgth;
//					sumx += xdyrate[i];
//					sumy += ydyrate[i];
//					sumz += zdyrate[i];
//					if(i == IMUDataLength - 1)
					if(i == IMUDataLength)
						{
							
							sumx /= IMUDataLength;
							sumy /= IMUDataLength;
							sumz /= IMUDataLength;
							if(fabs(xtmpt - sumx)<2)
								{
									XYZGyRaw.xrrate0 = sumx;
									flag_xr_over = true;
								}
							if(fabs(ytmpt- sumy)<2)
								{
									XYZGyRaw.yrrate0 = sumy;
									flag_yr_over = true;
								}
							if(fabs(ztmpt - sumz)<2)
								{
									XYZGyRaw.zrrate0 = sumz;
									flag_zr_over = true;
								}
							sumx = 0;
							sumy = 0;
							sumz = 0;
							i = 0;
						}

				
				
					XYZGyRaw.xrrate = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].xraw) - XYZGyRaw.xrrate0;
					XYZGyRaw.yrrate = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].yraw) - XYZGyRaw.yrrate0;
					XYZGyRaw.zrrate = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].zraw) - XYZGyRaw.zrrate0;
//					rate[j] = sqrt(pow(XYZGyRaw.xrrate, 2) + pow(XYZGyRaw.yrrate, 2) + pow(XYZGyRaw.zrrate, 2));
//					XYZGyRaw.rate = rate[j];
					sumrate += sumratetemp = sqrt(pow(XYZGyRaw.xrrate, 2) + pow(XYZGyRaw.yrrate, 2) + pow(XYZGyRaw.zrrate, 2));
					j++;
					
//					sumrate += rate[j];
					if(j == IMUDataLength)
						{
							
							sumrate /= IMUDataLength;
				
							if(fabs(sumratetemp - sumrate)<0.5)
								{
									XYZGyRaw.rate0 = sumrate;
//									LEDOn;//debug lysq
									
									flag_dry_over = true;
								}
							sumrate = 0;
							j = 0;
						}

				
				
					if(flag_dry_over == true && flag_zr_over == true && flag_yr_over == true && flag_xr_over == true)
						{
							flag_dry_over = false;
							flag_zr_over = false;
							flag_yr_over = false;
							flag_xr_over = false;
							LEDOff;
							FlagStatusClear(&FlagGlobal, Flag_GetG0);
							flag_init = false;
							accstatic = false;
							lsm6dsmActInit();
						}
				

			
				}



		}
		else
		{
			i = 0;
			sumx = 0;
			sumy = 0;
			sumz = 0;
			j = 0;
			sumrate = 0;
		}



}


void GetGsense(void)
{
	static float		ratexyz;
//	float		xlx, xly,xlz;
	uint8_t		buf[250] = {0};
//	uint8_t     ready;
	double		angletemp;
	static	uint8_t	onemotion;
	static  uint8_t flagact;

	float	tempangle;
	float	GryAvg;
	lsm6dsm_all_sources_t	status;
	
	if(FlagStatusIs(FlagGlobal, Flag_MotionDetect))
	{

		if(onemotion == FALSE)
			{
//				lsm6dsm_gy_sleep_mode_set(SPI2, 0);
				FlagStatusSet(&FlagGlobal, Flag_InitDy);
				onemotion = TRUE;

			}
		


		if(FlagStatusIs(FlagGlobal, Flag_GryReady))
			{
				FlagStatusClear(&FlagGlobal, Flag_GryReady);
				GetAcc((XLRwaTyp *)&XYZXLRaw.XLRwa);
				GetGry((GryRwaTyp *)&XYZGyRaw.GryRwa[XYZGyRaw.nextpoint]);

				GryAvg = sqrt(pow(XYZGyRaw.GryRwa[XYZGyRaw.nextpoint].xraw, 2) + pow(XYZGyRaw.GryRwa[XYZGyRaw.nextpoint].yraw, 2) + pow(XYZGyRaw.GryRwa[XYZGyRaw.nextpoint].zraw, 2));
				if(!FlagStatusIs(FlagGlobal, Flag_InitDy))
					{
						XYZGyRaw.nextpoint++;
						XYZGyRaw.nextpoint %= DryDatalebgth;
//						TogLED;
					}
				else
					{
						DyDiscardCnt++;
						if(DyDiscardCnt == 1)//135)
							{
								DyDiscardCnt = 0;
								FlagStatusClear(&FlagGlobal, Flag_InitDy);
							}
					}
		
			}

		lsm6dsm_all_sources_get(SPI2, &status);

//		if(status.wake_up_src.wu_ia == true)
//			{
//				flagact = true;
//			}
//		else 
			if(status.wake_up_src.sleep_state_ia == true)
			{
				flagact = FALSE;
				onemotion = FALSE;
//				lsm6dsm_gy_sleep_mode_set(SPI2, 1);
				FlagStatusClear(&FlagGlobal, Flag_MotionDetect);
				FlagStatusSet(&FlagGlobal, Flag_WirlessCom);
				LEDOff;
				UpdateData.valvedegree = (int32_t) XYZGyRaw.zangle;
//				ModeSet(NormalMode);
//				memset(buf,0,sizeof(buf));
//				sprintf((char *)buf, "abc:%f,%f,%f,%f, %d\r\n", XYZGyRaw.xangle, XYZGyRaw.yangle, XYZGyRaw.zangle, XYZGyRaw.angle, UpdateData.valvedegree);
//				HAL_UART_TransmitStr(LPUART2, buf, 1000);
			}




//		if(XYZGyRaw.startpoint != XYZGyRaw.nextpoint && flagact == TRUE)
		if(XYZGyRaw.startpoint != XYZGyRaw.nextpoint)
		{

			TogLED;
//			XYZGyRaw.xrrate = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].xraw) - XYZGyRaw.xrrate0;
//
//			XYZGyRaw.yrrate = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].yraw) - XYZGyRaw.yrrate0;
			
//			XYZGyRaw.zrrate = lsm6dsm_from_1000dps_to_dps(XYZGyRaw.GryRwa[XYZGyRaw.startpoint].zraw) - XYZGyRaw.zrrate0;
			
			XYZGyRaw.zrrate = lsm6dsm_from_1000dps_to_dps(GryAvg) - XYZGyRaw.zrrate0;

			XYZGyRaw.startpoint++;
			XYZGyRaw.startpoint %= DryDatalebgth;


//			XYZGyRaw.xangle = getAngle(&DryX, XYZGyRaw.accxangle, XYZGyRaw.xrrate, Dt); // Calculate the angle using a Kalman filter
//			XYZGyRaw.accxangle = XYZGyRaw.xangle;
//
//			XYZGyRaw.yangle = getAngle(&DryY, XYZGyRaw.accyangle, XYZGyRaw.yrrate, Dt); // Calculate the angle using a Kalman filter
//			XYZGyRaw.accyangle = XYZGyRaw.yangle;
//
//			XYZGyRaw.zangle = getAngle(&DryY, XYZGyRaw.acczangle, XYZGyRaw.yrrate, Dt); // Calculate the angle using a Kalman filter
//			XYZGyRaw.acczangle = XYZGyRaw.zangle;


//			XYZGyRaw.xanglenofilter += XYZGyRaw.xrrate * Dt; // Calculate gyro angle without any filter
//			XYZGyRaw.yanglenofilter += XYZGyRaw.yrrate * Dt;
//			XYZGyRaw.zanglenofilter += XYZGyRaw.zrrate * Dt;


//			XYZGyRaw.xangle = CpSysMain*(XYZGyRaw.xangle + XYZGyRaw.xrrate * Dt);// - CpSysMin * XYZGyRaw.xangle; // Calculate gyro angle without any filter
//			XYZGyRaw.yangle = CpSysMain*(XYZGyRaw.yangle + XYZGyRaw.yrrate * Dt);// - CpSysMin * XYZGyRaw.yangle;
//			if(XYZGyRaw.zrrate >= 0)
//				{
				tempangle = XYZGyRaw.zrrate * Dt;
				if(fabs(tempangle) >= 0.003 )
					{
						XYZGyRaw.zangle = CpSysMain*(XYZGyRaw.zangle + tempangle) + CpSysMin * XYZGyRaw.zangle;
					}
				
//			XYZGyRaw.zangle = CpSysMain*(XYZGyRaw.zangle + XYZGyRaw.zrrate * Dt) + CpSysMin * XYZGyRaw.zangle;

//				}
//			else
//				{
//				XYZGyRaw.zangle = CpSysMain*(XYZGyRaw.zangle + XYZGyRaw.zrrate * Dt) + CpSysMin * XYZGyRaw.zangle;
//
//				}


//			XYZGyRaw.xangle += XYZGyRaw.xrrate * Dt;
//
//			XYZGyRaw.yangle += XYZGyRaw.yrrate * Dt;

//			XYZGyRaw.zangle += XYZGyRaw.zrrate * Dt;// - CpSysMin * XYZGyRaw.zangle;

//			angletemp = sqrt(pow(XYZGyRaw.xangle, 2) + pow(XYZGyRaw.yangle, 2) + pow(XYZGyRaw.zangle, 2));
////
////
//			if( XYZGyRaw.zrrate < 0)
//				{
//					angletemp = 0 - angletemp;
//				}
//
//			if(angletemp <= 1 && angletemp >= -1)
//				{
//					angletemp = 0;
//				}
////			
//			XYZGyRaw.angle += angletemp;
//
//			UpdateData.valvedegree = (int32_t) XYZGyRaw.angle;
//			ModeSet(NormalMode);
//			memset(buf,0,sizeof(buf));
//			sprintf((char *)buf, "%f,%f,%f,%f,%f,%f\r\n", XYZGyRaw.xrrate0, XYZGyRaw.yrrate0, XYZGyRaw.zrrate0, XYZGyRaw.xrrate, XYZGyRaw.yrrate, XYZGyRaw.zrrate);
//			HAL_UART_TransmitStr(LPUART2, buf, 1000);

		}






		}

}


//void GetGsense0(void)
//{
//	float		xsum = 0, ysum = 0, zsum = 0;
//	float		xdsum = 0, ydsum = 0, zdsum = 0;
//
//	static      uint8_t i = 0, j = 0;
//	static		float 	xLmg[200];
//	static		float 	yLmg[200];
//	static		float 	zLmg[200];
//	static		float 	xdyrate[200];
//	static		float 	ydyrate[200];
//	static		float 	zdyrate[200];
//
//	static          float		a,b,c;
//	static		bool    flag_get_dry;
//
//	if(FlagStatusIs(FlagGlobal, Flag_MotionDetect))
//		{
//			FlagStatusClear(&FlagGlobal, Flag_MotionDetect);
//			GetAcc(&XYZXLRaw);
//			xLmg[i] = lsm6dsm_from_fs4g_to_mg(XYZXLRaw.xraw);
//			yLmg[i] = lsm6dsm_from_fs4g_to_mg(XYZXLRaw.yraw);
//			zLmg[i] = lsm6dsm_from_fs4g_to_mg(XYZXLRaw.zraw);
//			if(i>0)
//				{
//					a = fabs(xLmg[i] - xLmg[i-1]);
//					b = fabs(yLmg[i] - yLmg[i-1]);
//					c = fabs(zLmg[i] - zLmg[i-1]);
//					if(fabs(xLmg[i] - xLmg[i-1])<10 &&
//					   fabs(yLmg[i] - yLmg[i-1])<10 &&
//					   fabs(zLmg[i] - zLmg[i-1])<10)//判断是否平稳
//						{
//							xsum += xLmg[i-1];
//							ysum += yLmg[i-1];
//							zsum += zLmg[i-1];
//							if(i == 199)
//								{
//									XYZXLRaw.xmg0 = (xsum + xLmg[i])/200;
//									XYZXLRaw.ymg0 = (ysum + yLmg[i])/200;
//									XYZXLRaw.zmg0 = (zsum + zLmg[i])/200;
//									flag_get_dry = true;
//								}
//							
//						}
//					   else
//					   	{
//							i = 0;
//							j = 0;
//							xsum = 0;
//							ysum = 0;
//							zsum = 0;
//							xdsum = 0;
//							ydsum = 0;
//							zdsum = 0;
//
//					   	}
//				}
//			if(i == 199)
//				{
//					i = 0;
//					xsum = 0;
//					ysum = 0;
//					zsum = 0;
//				}
//			else
//				{
//					i++;
//				}
//			
//		}
//
//	if(FlagStatusIs(FlagGlobal, Flag_GryReady))
//		{
//			FlagStatusClear(&FlagGlobal, Flag_GryReady);
//			GetGry(&XYZGyRaw);
//			xdyrate[j] = lsm6dsm_from_500dps_to_dps(XYZGyRaw.xraw);
//			ydyrate[j] = lsm6dsm_from_500dps_to_dps(XYZGyRaw.yraw);
//			zdyrate[j] = lsm6dsm_from_500dps_to_dps(XYZGyRaw.zraw);
//			xdsum += xdyrate[j];
//			ydsum += ydyrate[j];
//			zdsum += zdyrate[j];
//			if(j == 199)
//				{
//					if(flag_get_dry == true)
//						{
//							flag_get_dry = false;
//							XYZGyRaw.xrrate0 = xdsum/200;
//							XYZGyRaw.yrrate0 = ydsum/200;
//							XYZGyRaw.zrrate0 = zdsum/200;
//							i = 0;
//							xsum = 0;
//							ysum = 0;
//							zsum = 0;
//							FlagStatusClear(&FlagGlobal, Flag_GetG0);
//						}
//					j = 0;
//					xdsum = 0;
//					ydsum = 0;
//					zdsum = 0;
//
//				}
//			else
//				{
//					j++;
//				}
//
//              }
//}


//void Yijielvbo(float angle_m, float gyro_m)//采集后计算的角度和角加速度
//{
//     angle1 = K1 * angle_m+ (1-K1) * (angle1 + gyro_m * dt);
//}









//void Erjielvbo(float angle_m,float gyro_m)//采集后计算的角度和角加速度
//{
//    x1=(angle_m-angle2)*(1-K2)*(1-K2);
//    y1=y1+x1*dt;
//    x2=y1+2*(1-K2)*(angle_m-angle2)+gyro_m;
//    angle2=angle2+ x2*dt;
//}



//卡尔曼滤波
//void Kalman_Filter(float angle_m, float gyro_m)//angleAx 和 gyroGy
//{
//angle+=(gyro_m-q_bias) * dt;
//angle_err = angle_m - angle;
//Pdot[0]=Q_angle - P[0][1] - P[1][0];
//Pdot[1]=- P[1][1];
//Pdot[2]=- P[1][1];
//Pdot[3]=Q_gyro;
//P[0][0] += Pdot[0] * dt;
//P[0][1] += Pdot[1] * dt;
//P[1][0] += Pdot[2] * dt;
//P[1][1] += Pdot[3] * dt;
//PCt_0 = C_0 * P[0][0];
//PCt_1 = C_0 * P[1][0];
//E = R_angle + C_0 * PCt_0;
//K_0 = PCt_0 / E;
//K_1 = PCt_1 / E;
//t_0 = PCt_0;
//t_1 = C_0 * P[0][1];
//P[0][0] -= K_0 * t_0;
//P[0][1] -= K_0 * t_1;
//P[1][0] -= K_1 * t_0;
//P[1][1] -= K_1 * t_1;
//angle += K_0 * angle_err; //最优角度
//q_bias += K_1 * angle_err;
//angle_dot = gyro_m-q_bias;//最优角速度
//}


//void getangle()
//{
//    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);//读取原始6个数据
//    angleAx=atan2(ax,az)*180/PI;//计算与x轴夹角
//    gyroGy=-gy/131.00;//计算角速度
//    Yijielvbo(angleAx,gyroGy);//一阶滤波
//    Erjielvbo(angleAx,gyroGy);//二阶滤波
//    Kalman_Filter(angleAx,gyroGy);   //卡尔曼滤波
//}





// The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds
//float GetAngle(float newAngle, float newRate, float dt) 
//{
//    // KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
//    // Modified by Kristian Lauszus
//    // See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it
//
//    // Discrete Kalman filter time update equations - Time Update ("Predict")
//    // Update xhat - Project the state ahead
//    /* Step 1 */
//	float rate;
//    rate = newRate - bias;
//    angle += dt * rate;
//
//    // Update estimation error covariance - Project the error covariance ahead
//    /* Step 2 */
//    P[0][0] += dt * (dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
//    P[0][1] -= dt * P[1][1];
//    P[1][0] -= dt * P[1][1];
//    P[1][1] += Q_bias * dt;
//
//    // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
//    // Calculate Kalman gain - Compute the Kalman gain
//    /* Step 4 */
//    float S = P[0][0] + R_measure; // Estimate error
//    /* Step 5 */
//    float K[2]; // Kalman gain - This is a 2x1 vector
//    K[0] = P[0][0] / S;
//    K[1] = P[1][0] / S;
//
//    // Calculate angle and bias - Update estimate with measurement zk (newAngle)
//    /* Step 3 */
//    float y = newAngle - angle; // Angle difference
//    /* Step 6 */
//    angle += K[0] * y;
//    bias += K[1] * y;
//
//    // Calculate estimation error covariance - Update the error covariance
//    /* Step 7 */
//    float P00_temp = P[0][0];
//    float P01_temp = P[0][1];
//
//    P[0][0] -= K[0] * P00_temp;
//    P[0][1] -= K[0] * P01_temp;
//    P[1][0] -= K[1] * P00_temp;
//    P[1][1] -= K[1] * P01_temp;
//
//    return angle;
//};


