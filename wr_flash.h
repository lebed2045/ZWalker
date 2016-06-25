//*****************************************************************************
//
// wr_flash.h - Walking Robot's Flash Memory Manager
//
//*****************************************************************************

#ifndef __WR_FLASH_H__
#define __WR_FLASH_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

void WRFlashInit();
void WRFlashCleanBuffer();
void WRFlashWriteToBuffer(unsigned char*, unsigned long);
void WRFlashReadFromBuffer(unsigned char*, unsigned long);
void WRFlashLoadBuffer(unsigned long);
void WRFlashSaveBuffer(unsigned long);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WR_FLASH_H__
