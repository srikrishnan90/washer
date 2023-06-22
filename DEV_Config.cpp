/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-12-21
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of theex Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include <DEV_Config.h>
#include <fcntl.h>

/**
 * GPIO
**/
int DEV_RST_PIN;
int DEV_CS_PIN;
int DEV_DRDY_PIN;

/**
 * GPIO read and write
**/
void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{

	digitalWrite(Pin, Value);

}

UBYTE DEV_Digital_Read(UWORD Pin)
{
	UBYTE Read_value = 0;

	Read_value = digitalRead(Pin);



	return Read_value;
}

/**
 * SPI
**/
UBYTE DEV_SPI_WriteByte(uint8_t Value)
{
	UBYTE temp = 0;

	wiringPiSPIDataRW(0, &Value, 1);
	temp = Value;

	return temp;
}

UBYTE DEV_SPI_ReadByte(void)
{
	return DEV_SPI_WriteByte(0x00);
}

/**
 * GPIO Mode
**/
void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{

	if(Mode == 0 || Mode == INPUT) {
		pinMode(Pin, INPUT);
		pullUpDnControl(Pin, PUD_UP);
	} else {
		pinMode(Pin, OUTPUT);
		// Debug (" %d OUT \r\n",Pin);
	}

}

/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms)
{

	delay(xms);

}



void DEV_GPIO_Init(void)
{

    DEV_RST_PIN     = 18;
    DEV_CS_PIN      = 22;
    DEV_DRDY_PIN    = 17;


	DEV_GPIO_Mode(DEV_RST_PIN, 1);
	DEV_GPIO_Mode(DEV_CS_PIN, 1);
	
	DEV_GPIO_Mode(DEV_DRDY_PIN, 0);
	
	DEV_Digital_Write(DEV_CS_PIN, 1);
}

/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_Module_Init(void)
{

	if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
		printf("set wiringPi lib failed	!!! \r\n");
		return 1;
	} else {
		printf("set wiringPi lib success !!! \r\n");
	}


	DEV_GPIO_Init();

	wiringPiSPISetupMode(0, 1000000, 1);

}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_Module_Exit(void)
{

	DEV_Digital_Write(DEV_RST_PIN, 0);
	DEV_Digital_Write(DEV_CS_PIN, 0);

}
