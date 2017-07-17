#include <Arduino.h>
#include <Wire.h>
#include "bmpLUT.h"

/*
Turns on an LED on for one second, then off for one second, repeatedly.
*/

// defines for the commands and corresponding values
#define DISPLAY_OFF 0xAE

#define SET_CONTRAST    0x81

#define CONTRAST    0x7F /// default value

#define SCROLL_OFF  0x2E

#define SET_ADDR_MODE   0x20

#define ADDR_VERTICAL   0x01

#define ADDR_HORIZONTAL	0x00

#define SET_COL_ADDR  0x21 /// used during data display

#define COL_START_ADDR  0x00

#define COL_END_ADDR    0x7F /// 127

#define SET_PAGE_ADDR   0x22

#define PAGE_START_ADDR 0x00

#define PAGE_END_ADDR   0x07 /// 8 pages

#define DISPLAY_START_LINE  0x40 /// line 0

#define SEG_REMAP   0xA0 /// default value

#define SET_MUX 0xA8

#define MUX_RATIO   63

#define SET_COM_SCAN_DIR    0xC0

#define SET_DISPLAY_OFFSET  0xD3

#define DISPLAY_OFFSET  0x00

#define SET_COM_PIN_ASSIGN  0xDA

#define COM_PIN_ASSIGN  0x02

#define SET_CLK_DIV_RATIO   0xD5

#define CLK_DIV_RATIO   0x80

#define SET_PRECHARGE_PERIOD    0xD9

#define PRECHARGE_PERIOD    0x22

#define SET_VCOM    0xDB

#define VCOM    0x20

#define SET_CHARGE_PUMP 0x8D

#define ENABLE_CHARGE_PUMP  0x14

#define DISPLAY_ON	0xAF

#define NORMAL_DISPLAY	0xA6

#define DISPLAY_RAM	0xA4

/******************************************************************************************************************************************************************
* AUTHOR : Sambit Mohapatra
*
* DATE : 11-07-2017
*
* DESCP : Function sends a command to the SSD1306
* 
* ARGS : command - the command to send or the value for a command to be send with a command control byte
*
* RETURN : NONE
*****************************************************************************************************************************************************************/
void commandSSD1306_i2c(uint8_t command)
{
	//
	Wire.beginTransmission(0x3C); // 3C is the slave address for the display
	//
	Wire.write(0x80); /// control byte - command
					  //
	Wire.write(command);
	//
	Wire.endTransmission();
}
//
/**********************************************************************************************************************************************************************************************
* AUTHOR : Sambit Mohapatra
* 
* DATE : 11-07-2017
*
* DESCP : Function sends a data byte to the SSD1306, data byte is written LSB->MSB from top to bottom in a column, each column is 8 bytes (1 byte in each page, 8 pages)
*
* ARGS : data : the data byte
*			col_start_addr = start address for the column from which the data display shall start
*			col_end_addr = column number after which display shall roll over to col_start_addr of next row in page addressing mode
*			page_start_addr = start page number (0-7)
*			page_end_addr = end_page_number (0-7)
*
* RETURN : NONE
************************************************************************************************************************************************************************************************/
void dataSSD1306_i2c(uint8_t data[], uint8_t nbytes, bool wipe=true)
{
	//
	int i;
	//
	for (i = 0; i < nbytes; i++)
	{
		// we write one byte at a time and generate a fresh transaction
		Wire.beginTransmission(0x3C);
		//
		Wire.write(0x40); // control byte - data
		//
		Wire.write(data[i]);
		//
		Wire.endTransmission();
		//
		// produce a wiping effect for text to appear on the display
		if (wipe)
			delayMicroseconds(20000);
	}
	//
	// Put some space between every letter
	Wire.beginTransmission(0x3C);
	Wire.write(0x40);
	Wire.write(0x00);
	Wire.endTransmission();
	//
	Wire.beginTransmission(0x3C);
	Wire.write(0x40);
	Wire.write(0x00);
	Wire.endTransmission();
	//delay(100);
}
//

// function clears the display by writing a 0x00 to every byte
void clearSSD1306()
{
	//
	int i;
	//
	// set the address pointer to the start of the GDDRAM and then write 0s to all bits
	commandSSD1306_i2c(SET_COL_ADDR);
	//
	commandSSD1306_i2c(COL_START_ADDR);
	//
	commandSSD1306_i2c(COL_END_ADDR);
	//
	commandSSD1306_i2c(SET_PAGE_ADDR);
	//
	commandSSD1306_i2c(PAGE_START_ADDR);
	//
	commandSSD1306_i2c(PAGE_END_ADDR);
	//
	for (i = 0; i < 1024; i++)
	{
		//
		Wire.beginTransmission(0x3C);
		//
		Wire.write(0x40); /// control byte - data
						  //				  //
		Wire.write(0x00);
		//
		Wire.endTransmission();
		//
		delayMicroseconds(20000);
		//delay(1);
	}
}
//

// function does all the required initialisation for the display to work properly
void initSSD1306_i2c()
{
	//
	//Wire.beginTransmission(0x3C);
	//
	commandSSD1306_i2c(DISPLAY_OFF);
	//
	commandSSD1306_i2c(SET_CONTRAST);
	//
	commandSSD1306_i2c(CONTRAST);
	//
	commandSSD1306_i2c(SCROLL_OFF);
	//
	commandSSD1306_i2c(SET_ADDR_MODE);
	//
	//commandSSD1306_i2c(ADDR_VERTICAL);
	//
	commandSSD1306_i2c(ADDR_HORIZONTAL);
	//
	commandSSD1306_i2c(DISPLAY_START_LINE);
	//
	commandSSD1306_i2c(SEG_REMAP);
	//
	commandSSD1306_i2c(SET_MUX);
	//
	commandSSD1306_i2c(MUX_RATIO);
	//
	commandSSD1306_i2c(SET_COM_SCAN_DIR);
	//
	commandSSD1306_i2c(SET_DISPLAY_OFFSET);
	//
	commandSSD1306_i2c(DISPLAY_OFFSET);
	//
	commandSSD1306_i2c(SET_COM_PIN_ASSIGN);
	//
	commandSSD1306_i2c(COM_PIN_ASSIGN);
	//
	commandSSD1306_i2c(SET_CLK_DIV_RATIO);
	//
	commandSSD1306_i2c(CLK_DIV_RATIO);
	//
	commandSSD1306_i2c(SET_PRECHARGE_PERIOD);
	//
	commandSSD1306_i2c(PRECHARGE_PERIOD);
	//
	commandSSD1306_i2c(SET_VCOM);
	//
	commandSSD1306_i2c(VCOM);
	//
	commandSSD1306_i2c(SET_CHARGE_PUMP);
	//
	commandSSD1306_i2c(ENABLE_CHARGE_PUMP);
	//
	commandSSD1306_i2c(NORMAL_DISPLAY);
	//
	commandSSD1306_i2c(DISPLAY_RAM);
	//
	commandSSD1306_i2c(DISPLAY_ON);
	//
	//Wire.endTransmission();

}
//
/********************************************************************************************************************************
* AUTHOR : Sambit Mohapatra
*
* DATE : 17/07/2017
*
* DESCP : Function takes a floating point number and converts into string to be written to the display
*
*********************************************************************************************************************************/

void ssd_WriteNum(float number, uint8_t col_pos, uint8_t page_pos)
{
	//
	char strNum[10]; // the number will be 10 characters wide at max
	//
	memset(strNum, 0, sizeof(strNum)); // clear the buffer before storing anything
	//
	sprintf(strNum, "%.2f", number); // convert to string with 2 characters after decimal
	//
	ssd_WriteString(strNum, col_pos, page_pos);
}
//


/****************************************************************************************************************************

* AUTHOR : Sambit Mohapatra

*

* DATE : 12/07/2017

*

* DESCP : Function writes a string to the SSD1306 display by first getting the corresponding byte stream for each character

*           of the passed string and then using the ssd_Data() function to write those bytes to the display

*****************************************************************************************************************************/

void ssd_WriteString(char str[], uint8_t col_pos, uint8_t page_pos)

{
	//
	uint8_t i;
	//
	// for pages 4-7
	if (page_pos > 3)
	{
		commandSSD1306_i2c(0xD3);
		//
		commandSSD1306_i2c(0x31);
	}
	//
	commandSSD1306_i2c(SET_COL_ADDR);
	//
	commandSSD1306_i2c(col_pos);
	//
	commandSSD1306_i2c(COL_END_ADDR);
	//
	commandSSD1306_i2c(SET_PAGE_ADDR);
	//
	commandSSD1306_i2c(page_pos);
	//
	commandSSD1306_i2c(PAGE_END_ADDR);
	// get every character
	for (i = 0; i < strlen(str); i++)
	{
		
		switch (str[i])
		{
		case 'A':
			dataSSD1306_i2c(A, 15); // we have found 'A', so send its byte stream and number of byte
			break;
			//
		case 'B':
			dataSSD1306_i2c(B, 6);
			//
			break;
			//
		case 'C':
			dataSSD1306_i2c(C, 6);
			//
			break;
			//
		case 'D':
			dataSSD1306_i2c(D, 7);
			//
			break;
			//
		case 'E':
			dataSSD1306_i2c(E, 6);
			//
			break;
			//
		case 'F':
			dataSSD1306_i2c(F, 7);
			//
			break;
			//
		case 'G':
			dataSSD1306_i2c(G, 6);
			//
			break;
			//
		case 'H':
			dataSSD1306_i2c(H, 7);
			//
			break;
			//
		case 'I':
			dataSSD1306_i2c(I, 7);
			//
			break;
			//
		case 'J':
			dataSSD1306_i2c(J, 7);

			break;
			//
		case 'K':
			dataSSD1306_i2c(K, 6);
			//
			break;
			//
		case 'L':
			dataSSD1306_i2c(L, 7);
			//
			break;
			//
		case 'M':

			dataSSD1306_i2c(M, 9);

			//

			break;

			//

		case 'N':

			dataSSD1306_i2c(N, 8);

			//

			break;

			//

		case 'O':

			dataSSD1306_i2c(O, 9);

			//

			break;

			//

		case 'P':

			dataSSD1306_i2c(P, 6);

			//

			break;

			//

		case 'Q':

			dataSSD1306_i2c(Q, 9);

			//

			break;



		case 'R':

			dataSSD1306_i2c(R, 5);

			//

			break;

			//

		case 'S':

			dataSSD1306_i2c(S, 7);

			//

			break;

			//

		case 'T':

			dataSSD1306_i2c(T, 7);

			//

			break;

			//

		case 'U':

			dataSSD1306_i2c(U, 9);

			//

			break;

			//

		case 'V':

			dataSSD1306_i2c(V, 15);

			//

			break;

			//

		case 'W':

			dataSSD1306_i2c(W, 11);

			//

			break;

			//

		case 'X':

			dataSSD1306_i2c(X, 8);

			//

			break;

			//

		case 'Y':

			dataSSD1306_i2c(Y, 9);
			//
			break;
			//
		case 'Z':
			dataSSD1306_i2c(Z, 8);
			//
			break;
			//
		case '0':
			dataSSD1306_i2c(N0, 4);
			//
			break;
			//
		case '1':
			dataSSD1306_i2c(N1, 3);
			//
			break;
			//
		case '2':
			dataSSD1306_i2c(N2, 4);
			//
			break;
		case '3':
			dataSSD1306_i2c(N3, 3);
			//
			break;
		case '5':
			dataSSD1306_i2c(N5, 4);
			//
			break;
		case '4':
			dataSSD1306_i2c(N4, 4);
			//
			break;
		case '6':
			dataSSD1306_i2c(N6, 4);
			//
			break;
		case '7':
			dataSSD1306_i2c(N7, 4);
			//
			break;
		case '8':
			dataSSD1306_i2c(N8, 4);
			//
			break;
		case '9':
			dataSSD1306_i2c(N9, 4);
			//
			break;
			//
			case '\'':
				dataSSD1306_i2c(deg, 1);
				//
				break;
				//
			case '%':
				dataSSD1306_i2c(per, 5);
				//
				break;
				//
		default:
			dataSSD1306_i2c(cls, 4);
			break;
		}

	}

}

// genaral arduino setup function
void setup()
{
	Serial.begin(9600);

	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
	pinMode(13, OUTPUT);
	//
	/// OLED init sequence for 128*32 bit I2C
	Wire.begin(); /// join I2C as a master
				  //
	initSSD1306_i2c();
	//Wire.beginTransmission(0x3c); /// slave address of OLED
	//
	clearSSD1306();
	//
	//ssd_WriteString("HELLO RAGA", 0, 0);
	//
	//ssd_WriteString("HUMIDITY", 5, 0);
	//
	//ssd_WriteString("70%", 100, 0);
	//clearSSD1306();
	
}

void loop()
{
	Serial.println(sizeof(uint8_t));

	//dataSSD1306_i2c(0xFF);
	//
	ssd_WriteString("HUMIDITY", 5, 0);
	//
	//ssd_WriteString("70%", 100, 0);
	//
	ssd_WriteNum(70.0, 100, 0);
	//
	delay(500);              // wait for a second
	digitalWrite(13, HIGH);
	
	//clearSSD1306();
	//dataSSD1306_i2c(0x00);
	// set the LED on
	delay(500);              // wait for a second
	digitalWrite(13, LOW);    // set the LED off
}


