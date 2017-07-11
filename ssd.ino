#include <Arduino.h>
#include <Wire.h>

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
void dataSSD1306_i2c(uint8_t data[], uint8_t col_start_addr=COL_START_ADDR, uint8_t col_end_addr=COL_END_ADDR, uint8_t page_start_addr=PAGE_START_ADDR, uint8_t page_end_addr=PAGE_END_ADDR)
{
	//
	commandSSD1306_i2c(SET_COL_ADDR);
	//
	commandSSD1306_i2c(col_start_addr);
	//
	commandSSD1306_i2c(col_end_addr);
	//
	commandSSD1306_i2c(SET_PAGE_ADDR);
	//
	commandSSD1306_i2c(page_start_addr);
	//
	commandSSD1306_i2c(page_end_addr);
	//
	Wire.beginTransmission(0x3C);
	//
	Wire.write(0x40); /// control byte - data
	//				  //
	Wire.write(0xC0);
	//
	//Wire.endTransmission();
	//


	Wire.write(0x40); /// control byte - data
					  //				  //
	Wire.write(0x30);
	//
	//Wire.endTransmission();

	Wire.write(0x40); /// control byte - data
					  //				  //
	Wire.write(0x1C);
	//
	//Wire.endTransmission();

	Wire.write(0x40); /// control byte - data
					  //				  //
	Wire.write(0x13);
	//
	Wire.write(0x40); /// control byte - data
					  //				  //
	Wire.write(0x1C);
	//
	Wire.write(0x40); /// control byte - data
					  //				  //
	Wire.write(0x30);
	//
	Wire.write(0x40); /// control byte - data
					  //				  //
	Wire.write(0xC0);

	Wire.endTransmission();
	//delay(100);
}
//

void clearSSD1306()
{
	//
	int i;
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
		delay(1);
	}
}
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
	uint8_t data[3] = { 0xC0, 0xFF, 0xA0 };
	dataSSD1306_i2c(data);
	/// display OFF
	//commandSSD1306_i2c()
	//Wire.endTransmission();

}

void loop()
{
	Serial.println(sizeof(uint8_t));

	//dataSSD1306_i2c(0xFF);
	delay(500);              // wait for a second
	digitalWrite(13, HIGH);
	//dataSSD1306_i2c(0x00);
	// set the LED on
	delay(500);              // wait for a second
	digitalWrite(13, LOW);    // set the LED off
}


