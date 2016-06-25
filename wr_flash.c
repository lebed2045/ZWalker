#include "wr_flash.h"

#include "inc/lm3s811.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/sysctl.h"
#include "driverlib/flash.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define FLASH_SAVE_START	0xf800	//last two pages in flash
#define FLASH_PAGE_SIZE		0x400	//1Kb

unsigned char cBuffer[FLASH_PAGE_SIZE];
unsigned long posBuffer;

//
// flush
//
void WRFlashCleanBuffer()
{
	posBuffer = 0;
	memset( cBuffer, 0, sizeof( cBuffer ) );
}

//
// printf
//
void WRFlashWriteToBuffer(unsigned char* buff, unsigned long size)
{
	memcpy( cBuffer+posBuffer, buff, size );
	posBuffer += size;	
}

//
// scanf
//
void WRFlashReadFromBuffer(unsigned char* buff, unsigned long size)
{
	memcpy( buff, cBuffer+posBuffer, size );	
	posBuffer += size;	
}

//
// fscanf
//
void WRFlashLoadBuffer(unsigned long page)
{
   	unsigned long flash_start = FLASH_SAVE_START + page*FLASH_PAGE_SIZE;

	memcpy( cBuffer, (void*)flash_start, FLASH_PAGE_SIZE );	
}

//
// fprintf
// 
void WRFlashSaveBuffer(unsigned long page)
{
  	unsigned long flash_start = FLASH_SAVE_START + page*FLASH_PAGE_SIZE;
	
	FlashErase(flash_start); 
	
  	FlashProgram( (unsigned long*)cBuffer, flash_start, FLASH_PAGE_SIZE);			
}

void WRFlashInit()
{
	//
	// Set the uSec value to number of clock cycles per mks
	//
	FlashUsecSet(SysCtlClockGet()/1000000);   
}
