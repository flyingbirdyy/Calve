#include "GetSensors.h"
#include <math.h>
#include "GlobalDef.h"
#include "control.h"
#include "GlobalVal.h"
#include "RS485Comm.h"
#include "GetSensors.h"


//void ADC_DMA_Config(uint16_t *buffer, uint32_t length)
//{
//    FL_DMA_ConfigTypeDef DMA_ConfigStruct = {0};
//    DMA_ConfigStruct.memoryAddress = (uint32_t)buffer;                                //配置DMA_RAM地址
//    DMA_ConfigStruct.transmissionCount = length - 1;                                  //配置DMA传输长度
//    (void)FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct, FL_DMA_CHANNEL_0);
//
//}


//void StartADC(uint16_t *adcbuf, uint8_t length)
//{
//	REFOn;
//	ADC_DMA_Config(adcbuf, length);													   //DMA初始化配置
//	
//	FL_ADC_ClearFlag_EndOfConversion(ADC);											   //清标志
//	FL_ADC_Enable(ADC);  
//
//	do
//	{
//		FL_DelayMs(1);
//		timeout++;
//		if(timeout >3000)
//			{
//				statuserr = 1;
//				break;
//			}
//	
//	}
//	while(!FlagStatusIs(FlagGlobal, Flag_DMAComplete));
//	FlagStatusClear(&FlagGlobal, Flag_DMAComplete);
//	REFOff;
//}





static uint8_t GetSingleChannelSample_POLL(uint32_t channel, uint16_t *ADCRdresult)
{
    uint32_t counter = 0;
    uint32_t EOC_Flag;
    uint8_t State;

    FL_CMU_SetADCPrescaler(FL_CMU_ADC_PSC_DIV1);                  //??ADC??????
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_ALL_CHANNEL);      //???????
    FL_ADC_EnableSequencerChannel(ADC, channel);                  //????

    FL_ADC_ClearFlag_EndOfConversion(ADC);                        //???
    FL_ADC_Enable(ADC);                                           //??ADC
    FL_ADC_EnableSWConversion(ADC);                               //????


    do
    {
        EOC_Flag = FL_ADC_IsActiveFlag_EndOfConversion(ADC);
        counter++;
    } while((counter != 0xFFFFFFFFU) && (EOC_Flag == 0U));           //??????

    if(EOC_Flag == 0x01U)
    {
        FL_ADC_ClearFlag_EndOfConversion(ADC);                        //???
        *ADCRdresult = FL_ADC_ReadConversionData(ADC);                 //?????

        FL_ADC_Disable(ADC);                                          //??ADC
        FL_ADC_DisableSequencerChannel(ADC, channel);                 //????
        State = 0;
    }
    else
    {
        State = 1 ;
    }
    return State;
}


void GetRef(uint16_t *databuff)
{
	REFOn;
	FL_DelayMs(10);
	GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH5, databuff+RefRaw);
	REFOff;
}


void GetBatVol(uint16_t *databuff)
{
	float data;
//	BattAdcOn;
//	FL_DelayMs(10);
//	GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH6, databuff+BatRaw);
//	BattAdcOff;
//	UpdateData.StationBatVol = (RefVol*(*(databuff+BatRaw))/(*(databuff+RefRaw)))*2;
//	UpdateData.StationBatVol = Retain_Two_Decimals(UpdateData.StationBatVol);
//	dataf = (RefVol * 4095 / *(databuff+RefRaw) +0.02)*10;
//	UpdateData.ValveBatVal = (uint8_t)((RefVol * 4095 / *(databuff+RefRaw) +0.02)*10);

	data = (RefVol * 4095 / *(databuff+RefRaw) +0.02)*10;
	UpdateData.ValveBatVal = HexToBcd((uint8_t)data);



}


//void GetWaterTemp(uint16_t *databuff)//lysq need to be modified
//{
//	float	r0Vol;

//	float	rt;

//	float a,b,c;
//	GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH1, databuff+TempRaw);
//	r0Vol = RefVol * (*(databuff+TempRaw))/(*(databuff+RefRaw));
//	rt = r0Vol*10000/(SensorVol - r0Vol);
//	UpdateData.WaterTemp = 1/(1/NTC_T0+log(rt/NTC_R0)/NTC_B)-Ka;
////	UpdateData.WaterTemp = Retain_One_Decimals(UpdateData.WaterTemp);
////	float Rt=0;
////	//Rp上拉电阻值
////	float Rp=10000;
////	//T2为25摄氏度，折算为开尔文温度
////	float T2=273.15+25;
////	float Bx=3950;
////	float Ka=273.15;
////	float vol=0;
////	vol=(float)(Get_Adc_Average(ADC_Channel_5,10)*3.3/4096);
////	Rt=(3.3-vol)*10000/vol;
////	temp=1/(1/T2+log(Rt/Rp)/Bx)-Ka+0.5;


//}



//void GetWaterDir(uint16_t *databuff)
//{
//	float presurevol;

//	GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH7, databuff+DirRaw);
//	presurevol = RefVol*(*(databuff+DirRaw))/(*(databuff+RefRaw));
//	UpdateData.WaterDirection = DirLinearCoef*presurevol;

//}



//void GetWaterPresure(uint16_t *databuff)
//{
//	float presurevol;

//	GetSingleChannelSample_POLL(FL_ADC_EXTERNAL_CH0, databuff+PresureRaw);
//	presurevol = RefVol* (*(databuff+PresureRaw))/(*(databuff+RefRaw));

//	UpdateData.WaterPresure = PresureSixPowerCoef*pow(presurevol,6)+PresureFivePowerCoef*pow(presurevol,5)+PresureFourPowerCoef*pow(presurevol,4)+PresureCubeCoef*pow(presurevol,3)+PresureSqurCoef*pow(presurevol,2)+PresureLinearCoef*presurevol+PresureConstant;
////	UpdateData.WaterPresure = Retain_Two_Decimals(UpdateData.WaterPresure);
//}





void ADCDataProcess(uint16_t *databuff)
{
	GetRef(databuff);
	GetBatVol(databuff);
		
}




void GetVoltage(void)
{
	if(FlagStatusIs(FlagGlobal, Flag_GetBatVoltage))
		{
			ADCDataProcess(ADCBuffer);
			FlagStatusClear(&FlagGlobal, Flag_GetBatVoltage);
		}
}



