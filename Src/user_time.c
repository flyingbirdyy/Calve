#include <string.h>
#include "main.h"
#include "GlobalDef.h"
#include "GlobalTyp.h"
#include "GlobalVal.h"
#include "user_time.h"
#include <time.h>
#include "control.h"



//��ȡRTCAģ���ʱ�䵽 ram
uint8_t RTCA_GetRTCA(FL_RTCA_InitTypeDef *InitStructer)
{
    uint8_t n, i;
    uint8_t Result = 1;

    FL_RTCA_InitTypeDef TempTime1, TempTime2;

    for(n = 0 ; n < 3; n++)
    {
        FL_RTCA_GetTime(RTCA, &TempTime1); //��һ��ʱ��
        FL_RTCA_GetTime(RTCA, &TempTime2); //�ٶ�һ��ʱ��

        for(i = 0; i < 7; i++) //����һ��, ��ʾ��ȡ�ɹ�
        {
            if(((uint32_t *)(&TempTime1))[i] != ((uint32_t *)(&TempTime2))[i]) { break; }
        }

        if(i == 7)
        {
            Result = 0;
            memcpy((uint32_t *)(InitStructer), (uint32_t *)(&TempTime1), 7 * sizeof(uint32_t)); //��ȡ��ȷ������µ�ʱ��
            break;
        }
    }

    return Result;
}

//����ram��ʱ�䵽RTCAģ��
uint8_t RTCA_SetRTCA(FL_RTCA_InitTypeDef *InitStructer)
{
    uint8_t n, i;
    uint8_t Result;
    FL_RTCA_InitTypeDef TempTime1;

    for(n = 0 ; n < 3; n++)
    {
    	FL_CMU_EnableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_RTCA);
        FL_RTCA_ConfigTime(RTCA, InitStructer);
        Result = RTCA_GetRTCA(&TempTime1);    //��ȡȷ�����ý��

        if(Result == 0)
        {
            Result = 1;

            for(i = 0; i < 7; i++) //����һ��, ��ʾ���óɹ�
            {
                if(((uint32_t *)(&TempTime1))[i] != ((uint32_t *)(InitStructer))[i])
                { break; }
            }

            if(i == 7)
            {
                Result = 0;
                break;
            }
        }
    }

    return Result;
}




//��дʱ��
//void RTCA_ReadWrite(void)
//{
//    FL_RTCA_InitTypeDef   inittime;
//    FL_RTCA_InitTypeDef   gettime;
//
//    FL_RTCA_Enable(RTCA);
//    //��ram������д���ʱ��
//    InitTime.year   = 0x20;
//    InitTime.month  = 0x10;
//    InitTime.day    = 0x02;
//    InitTime.week   = 0x04;
//    InitTime.hour   = 0x15;
//    InitTime.minute = 0x00;
//    InitTime.second = 0x00;
//
//    //��ram��ʱ�� д��RTCAģ��
//    RTCA_SetRTCA(&inittime);
//
//    FL_DelayMs(1000); //��ʱ�����Ǳ��롣����ɾ��������Ϊ�˿�RTCA����ʱ �����Ե���1��
//
//    //��RTCAģ���ʱ�� ������ram
//    RTCA_GetRTCA(&gettime);
//}





void SyncTime(void)
{
	FL_RTCA_InitTypeDef   gettime;
	
	RTCA_GetRTCA(&gettime);

	//������
}





//uint16_t calculateDaysDiff(FL_RTCA_InitTypeDef date1, FL_RTCA_InitTypeDef date2) //date2 > date1
//{
//    uint16_t year1 = BcdToHex(date1.year) + 2000;
//    uint16_t month1 = BcdToHex(date1.month);
//    uint16_t day1 = BcdToHex(date1.day);
//    
//    uint16_t year2 = BcdToHex(date2.year) + 2000;
//    uint16_t month2 = BcdToHex(date2.month);;
//    uint16_t day2 = BcdToHex(date2.day);
//
//    uint16_t daysDiff;
//    
//    if ((year1 == year2 && month1 == month2)) {
//        daysDiff = day2 - day1;
//    } else {
//        // �����·��ж�ÿ�����ж�����
//        static const unsigned short daysInMonth[] = {
//            0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
//        
//        int totalDays1 = daysInMonth[month1] + day1;
//        int totalDays2 = daysInMonth[month2] + day2;
//        
//        if (month1 > month2 || (month1 == month2 && day1 >= day2)) {
//            totalDays1 -= totalDays2;
//        } else {
//            totalDays1 += totalDays2;
//        }
//        
//        daysDiff = totalDays1;
//    }
//    
//    return daysDiff;
//}
//



//void WriteAlarm(uint32_t UpdateTime)//UpdateTime: hour
//{
//	FL_RTCA_InitTypeDef tim1;
//	time_t tmp_time;
//	struct tm  tim;
//	struct tm *ptim = &tim;
//
//
//	RTCA_GetRTCA(&tim1);
//
//	ptim->tm_year = BcdToHex(tim1.year) + 100;
//	ptim->tm_mon = BcdToHex(tim1.month) - 1;
//	ptim->tm_mday = BcdToHex(tim1.day);
//	ptim->tm_hour = BcdToHex(tim1.hour);
//	ptim->tm_min = BcdToHex(tim1.minute);
//	ptim->tm_sec = BcdToHex(tim1.second);
//	
//	tmp_time = mktime(ptim);
//	
//	
//	tmp_time += (UpdateTime * 60);
//	ptim = localtime(&tmp_time);
//	tim1.year = HexToBcd(ptim->tm_year-100);
//	tim1.month = HexToBcd(ptim->tm_mon+1);
//	tim1.day = HexToBcd(ptim->tm_mday);
//	tim1.hour = HexToBcd(ptim->tm_hour);
//	tim1.minute = HexToBcd(ptim->tm_min);
//	tim1.second = HexToBcd(ptim->tm_sec);
//	
//	
//	FL_RTCA_WriteHourAlarm(RTCA, tim1.hour);                             //?
//	FL_RTCA_WriteMinuteAlarm(RTCA, tim1.minute);                           //?
//	FL_RTCA_WriteSecondAlarm(RTCA, tim1.second);                           //?
//
//	FL_RTCA_ClearFlag_Alarm(RTCA);                                  //????????
//	FL_RTCA_EnableIT_Alarm(RTCA);                                   //??????
//
//}



