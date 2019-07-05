/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to read 10bit ADC value from channel 0 and send it on UART.

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
    Copyright (C) 2012  ExploreEmbedded

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


Errors and omissions should be reported to codelibraries@exploreembedded.com
**************************************************************************************************/
#include "adc.h"
#include "rtc.h"
#include "uart.h"
#include "common.h"
#include "ili9341.h"
#include <stdio.h>
#include <util/delay.h>

float Vin=5.0;     // [V]
float Rt=10000;    // Resistor t [ohm]
float R0=10000;    // value of rct in T0 [ohm]
float T0=298.15;   // use T0 in Kelvin [K]
float Vout=0.0;    // Vout in A0
float Rout=0.0;    // Rout in A0
float T1=273.15;      // [K] in datasheet 0º C
float T2=373.15;      // [K] in datasheet 100° C
float RT1=35563;   // [ohms]  resistence in T1
float RT2=549;    // [ohms]   resistence in T2
float beta=0.0;    // initial parameters [K]
float Rinf=0.0;    // initial parameters [ohm]
float TempK=0.0;   // variable output
float TempC=0.0;   // variable output
char buffer0[200],buffer1[200],buffer2[100],buffer3[100],buffer4[100];

int main() 
{
	    DDRA=(1<<DDA5) | (1<<DDA6)| (1<<DDA7);
	    PORTA=(0<<PA5) | (1<<PA6)| (0<<PA7);
    int adcValue;
	rtc_t rtc;
	
	ILI9341_Init();
	RTC_Init();	
    ADC_Init();       /* Initialize the ADC module */
    UART_Init(9600);  /* Initialize UART at 9600 baud rate */

rtc.hour = 0x10; //  10:40:20 am
rtc.min =  0x40;
rtc.sec =  0x00;

rtc.date = 0x29; //1st Jan 2016
rtc.month = 0x06;
rtc.year = 0x19;
rtc.weekDay = 6; // Friday: 5th day of week considering monday as first day.

  RTC_SetDateTime(&rtc);  //  10:40:20 am, 1st Jan 2016

beta=(log(RT1/RT2))/((1/T1)-(1/T2));
Rinf=R0*exp(-beta/T0);

ILI9341_string("Time:", 0, 0, 2, COLOR_YELLOW);
ILI9341_string("Date:", 0, 30, 2, COLOR_YELLOW);
ILI9341_string("ADC value:", 0, 60, 2, COLOR_YELLOW);
ILI9341_string("Temperature:", 0, 90, 2, COLOR_YELLOW);

    while(1)
    {
        adcValue = ADC_GetAdcValue(1); // Read the ADC value of channel zero
		Vout=Vin*(adcValue/1024.0); // calc for ntc
		Rout=(Rt*Vout/(Vin-Vout));

		TempK=(beta/log(Rout/Rinf)); // calc for temperature
		TempC=TempK-273.15;
       
		sprintf(buffer1,"Temperature: %.2f C \n\r",TempC);
		sprintf(buffer0,"%2x:%2x:%2x",(uint16_t)rtc.hour,(uint16_t)rtc.min,(uint16_t)rtc.sec);
		sprintf(buffer2,"%x/%2x/20%2x",(uint16_t)rtc.date,(uint16_t)rtc.month,(uint16_t)rtc.year);
		sprintf(buffer3,"%4d",adcValue);
		sprintf(buffer4,"%.2f C",TempC);
		RTC_GetDateTime(&rtc);
		UART_Printf("\n\rTime:%2x:%2x:%2x  \nDate:%x/%2x/20%2x\n\r",(uint16_t)rtc.hour,(uint16_t)rtc.min,(uint16_t)rtc.sec,(uint16_t)rtc.date,(uint16_t)rtc.month,(uint16_t)rtc.year);
		UART_Printf("ADC0 Value:%4d \n\r",adcValue);     // Send the value on UART
		UART_Printf(buffer1); 
		
		
		ILI9341_string(buffer0, 80, 0, 2, COLOR_YELLOW);
		ILI9341_string(buffer2, 80, 30, 2, COLOR_YELLOW);
		ILI9341_string(buffer3, 110, 60, 2, COLOR_YELLOW);
		ILI9341_string(buffer4, 145, 90, 2, COLOR_YELLOW);
		_delay_ms(500);
		ILI9341_string(buffer0, 80, 0, 2, COLOR_BLACK);
		ILI9341_string(buffer2, 80, 30, 2, COLOR_BLACK);
		ILI9341_string(buffer3, 110, 60, 2, COLOR_BLACK);
		ILI9341_string(buffer4, 145, 90, 2, COLOR_BLACK);
    }
    return (0);
}

