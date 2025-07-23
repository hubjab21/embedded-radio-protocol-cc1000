/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_lis302dl.c
 Author:        ST MCD Application Team, Modyfication for HAL: Łukasz Duda
 Purpose:       HALFRED's Universal port
 Compiler:      %COMPILER%
 Hardware:      Embedded
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       LIS302DL device
--------------------------------------------------------------------------------
 Comments:		MEMS motion sensor
 	 	 	 	3-axis - ± 2g/± 8g smart digital output “piccolo” accelerometer
================================================================================
*/

#include "hal.h"
#include "hal_port_lis302dl.h"

/* Read/Write command */
#define READWRITE_CMD              ((uint8_t)0x80)
/* Multiple byte read/write command */
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)


// -----------------------------------------------------------------------------
//  LIS302DL_Init
// -----------------------------------------------------------------------------
void LIS302DL_Init(IODevice dev, LIS302DL_InitTypeDef *LIS302DL_InitStruct)
{
  uint8_t ctrl = 0x00;

  // Configure MEMS: data rate, power mode, full scale, self test and axes
  ctrl = (uint8_t) (LIS302DL_InitStruct->Output_DataRate | LIS302DL_InitStruct->Power_Mode | \
                    LIS302DL_InitStruct->Full_Scale | LIS302DL_InitStruct->Self_Test | \
                    LIS302DL_InitStruct->Axes_Enable);

  // Write value to MEMS CTRL_REG1 regsister
  LIS302DL_Write(dev, &ctrl, LIS302DL_CTRL_REG1_ADDR, 1);

} /* LIS302DL_Init */

// -----------------------------------------------------------------------------
//  LIS302DL_Deinit
// -----------------------------------------------------------------------------
void LIS302DL_Deinit(IODevice dev)
{

} /* LIS302DL_Deinit */

// -----------------------------------------------------------------------------
//  LIS302DL_InterruptConfig
// -----------------------------------------------------------------------------
void LIS302DL_InterruptConfig(IODevice dev, LIS302DL_InterruptTypeDef *LIS302DL_InterruptStruct)
{
  uint8_t ctrl = 0x00;

  // Configure Interrupts request
  ctrl |= (uint8_t)(LIS302DL_InterruptStruct->InterruptActive_Type | \
		  	  	    LIS302DL_InterruptStruct->InterruptOut_Mode | \
		  	  	    LIS302DL_InterruptStruct->FFWU1_InterruptEnable | \
		  	  	    LIS302DL_InterruptStruct->FFWU2_InterruptEnable);

  // Write value to MEMS CTRL_REG3 register
  LIS302DL_Write(dev, &ctrl, LIS302DL_CTRL_REG3_ADDR, 1);

} /* LIS302DL_InterruptConfig */

// -----------------------------------------------------------------------------
//  LIS302DL_FilterConfig
// -----------------------------------------------------------------------------
void LIS302DL_FilterConfig(IODevice dev, LIS302DL_FilterConfigTypeDef *LIS302DL_FilterConfigStruct)
{
  uint8_t ctrl = 0x00;

  // Read CTRL_REG2 register
  LIS302DL_Read(dev, &ctrl, LIS302DL_CTRL_REG2_ADDR, 1);

  // Clear high pass filter cut-off level, interrupt and data selection bits
  ctrl &= (uint8_t)~(LIS302DL_FILTEREDDATASELECTION_OUTPUTREGISTER | \
                     LIS302DL_HIGHPASSFILTER_LEVEL_3 | \
                     LIS302DL_HIGHPASSFILTERINTERRUPT_1_2);

  // Configure MEMS high pass filter cut-off level, interrupt and data selection bits
  ctrl |= (uint8_t)(LIS302DL_FilterConfigStruct->HighPassFilter_Data_Selection | \
                    LIS302DL_FilterConfigStruct->HighPassFilter_CutOff_Frequency | \
                    LIS302DL_FilterConfigStruct->HighPassFilter_Interrupt);

  // Write value to MEMS CTRL_REG2 register
  LIS302DL_Write(dev, &ctrl, LIS302DL_CTRL_REG2_ADDR, 1);

} /* LIS302DL_FilterConfig */

// -----------------------------------------------------------------------------
//  LIS302DL_ClickConfig
// -----------------------------------------------------------------------------
void LIS302DL_ClickConfig(IODevice dev, LIS302DL_ClickConfigTypeDef *LIS302DL_ClickConfigStruct)
{
  uint8_t ctrl = 0x00;

  // Configure latch Interrupt request, click interrupts and double click interrupts
  ctrl = (uint8_t)(LIS302DL_ClickConfigStruct->Latch_Request| \
		  	  	   LIS302DL_ClickConfigStruct->SingleClick_Axes | \
		  	  	   LIS302DL_ClickConfigStruct->DoubleClick_Axes);

  // Write value to MEMS CLICK_CFG register
  LIS302DL_Write(dev, &ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);

  ctrl = (uint8_t)(LIS302DL_ClickConfigStruct->Threshold_X | ((LIS302DL_ClickConfigStruct->Threshold_Y) << 4));

  // Write value to MEMS CLICK_THSY_X register
  LIS302DL_Write(dev, &ctrl, LIS302DL_CLICK_THSY_X_REG_ADDR, 1);

  ctrl = (uint8_t)(LIS302DL_ClickConfigStruct->Threshold_Z);

  // Write value to MEMS CLICK_THSZ register
  LIS302DL_Write(dev, &ctrl, LIS302DL_CLICK_THSZ_REG_ADDR, 1);

  ctrl = (uint8_t)(LIS302DL_ClickConfigStruct->Time_Limit);

  // Write value to MEMS CLICK_TimeLimit register
  LIS302DL_Write(dev, &ctrl, LIS302DL_CLICK_TIMELIMIT_REG_ADDR, 1);

  ctrl = (uint8_t)(LIS302DL_ClickConfigStruct->Time_Limit);

  // Write value to MEMS CLICK_Latency register
  LIS302DL_Write(dev, &ctrl, LIS302DL_CLICK_LATENCY_REG_ADDR, 1);

  ctrl = (uint8_t)(LIS302DL_ClickConfigStruct->Time_Limit);

  // Write value to MEMS CLICK_Window register
  LIS302DL_Write(dev, &ctrl, LIS302DL_CLICK_WINDOW_REG_ADDR, 1);

} /* LIS302DL_ClickConfig */

// -----------------------------------------------------------------------------
//  LIS302DL_FFWU1Config
// -----------------------------------------------------------------------------
void LIS302DL_FFWU1Config(IODevice dev, LIS302DL_FFWUTypeDef *LIS302DL_FFWUTypeStruct)
{
  uint8_t ctrl = 0x00;

  // Configure latch Interrupt request, events enable and type of generate interrupts
  ctrl = (uint8_t)(LIS302DL_FFWUTypeStruct->Latch_Request | \
		  	  	   LIS302DL_FFWUTypeStruct->Interrupt_Combination | \
		  	  	   LIS302DL_FFWUTypeStruct->Enable_Interrupt);

  // Write value to MEMS FFWU1 register
  LIS302DL_Write(dev, &ctrl, LIS302DL_FF_WU_CFG1_REG_ADDR, 1);

  ctrl = (uint8_t)(LIS302DL_FFWUTypeStruct->Reseting_Mode | LIS302DL_FFWUTypeStruct->Threshold_FFWU);

  // Write value to MEMS FFWU1 THS1 register
  LIS302DL_Write(dev, &ctrl, LIS302DL_FF_WU_THS1_REG_ADDR, 1);

  ctrl = (uint8_t)(LIS302DL_FFWUTypeStruct->Duration_Time);

  // Write value to MEMS FFWU1 DURATION register
  LIS302DL_Write(dev, &ctrl, LIS302DL_FF_WU_DURATION1_REG_ADDR, 1);

} /* LIS302DL_FFWU1Config */

// -----------------------------------------------------------------------------
//  LIS302DL_FFWU2Config
// -----------------------------------------------------------------------------
void LIS302DL_FFWU2Config(IODevice dev, LIS302DL_FFWUTypeDef *LIS302DL_FFWUTypeStruct)
{
  uint8_t ctrl = 0x00;

  // Configure latch Interrupt request, events enable and type of generate interrupts
  ctrl = (uint8_t)(LIS302DL_FFWUTypeStruct->Latch_Request | \
		  	  	   LIS302DL_FFWUTypeStruct->Interrupt_Combination | \
		  	  	   LIS302DL_FFWUTypeStruct->Enable_Interrupt);

  // Write value to MEMS FFWU1 register
  LIS302DL_Write(dev, &ctrl, LIS302DL_FF_WU_CFG2_REG_ADDR, 1);

  ctrl = (uint8_t)(LIS302DL_FFWUTypeStruct->Reseting_Mode | LIS302DL_FFWUTypeStruct->Threshold_FFWU);

  // Write value to MEMS FFWU2 THS1 register
  LIS302DL_Write(dev, &ctrl, LIS302DL_FF_WU_THS2_REG_ADDR, 1);

  ctrl = (uint8_t)(LIS302DL_FFWUTypeStruct->Duration_Time);

  // Write value to MEMS FFWU2 DURATION register
  LIS302DL_Write(dev, &ctrl, LIS302DL_FF_WU_DURATION2_REG_ADDR, 1);

} /* LIS302DL_FFWU2Config */

// -----------------------------------------------------------------------------
//  LIS302DL_GetFFWU1Status
// -----------------------------------------------------------------------------
void LIS302DL_GetFFWU1Status(IODevice dev, uint8_t *status)
{
  // Read FFWU1 Status register
  LIS302DL_Read(dev, status, LIS302DL_FF_WU_SRC1_REG_ADDR, 1);

} /* LIS302DL_GetFFWU1Status */

// -----------------------------------------------------------------------------
//  LIS302DL_GetFFWU2Status
// -----------------------------------------------------------------------------
void LIS302DL_GetFFWU2Status(IODevice dev, uint8_t *status)
{
  // Read FFWU2 Status register
  LIS302DL_Read(dev, status, LIS302DL_FF_WU_SRC2_REG_ADDR, 1);

} /* LIS302DL_GetFFWU2Status */

// -----------------------------------------------------------------------------
//  LIS302DL_GetClickStatus
// -----------------------------------------------------------------------------
void LIS302DL_GetClickStatus(IODevice dev, uint8_t *status)
{
  // Read Click Status register
  LIS302DL_Read(dev, status, LIS302DL_CLICK_SRC_REG_ADDR, 1);

} /* LIS302DL_GetClickStatus */

// -----------------------------------------------------------------------------
//  LIS302DL_GetStatus
// -----------------------------------------------------------------------------
void LIS302DL_GetStatus(IODevice dev, uint8_t *status)
{
  // Read Status register
  LIS302DL_Read(dev, status, LIS302DL_STATUS_REG_ADDR, 1);

} /* LIS302DL_GetStatus */

// -----------------------------------------------------------------------------
//  LIS302DL_GetDeviceInfo
// -----------------------------------------------------------------------------
void LIS302DL_GetDeviceInfo(IODevice dev, uint8_t *device_id)
{
  // Read WHO_AM_I register
  LIS302DL_Read(dev, device_id, LIS302DL_WHO_AM_I_ADDR, 1);

} /* LIS302DL_GetDeviceInfo */

// -----------------------------------------------------------------------------
//  LIS302DL_LowpowerCmd
// -----------------------------------------------------------------------------
void LIS302DL_LowpowerCmd(IODevice dev, uint8_t LowPowerMode)
{
  uint8_t tmpreg;

  // Read CTRL_REG1 register
  LIS302DL_Read(dev, &tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);

  // Set new low power mode configuration
  tmpreg &= (uint8_t)~LIS302DL_LOWPOWERMODE_ACTIVE;
  tmpreg |= LowPowerMode;

  // Write value to MEMS CTRL_REG1 regsister
  LIS302DL_Write(dev, &tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);

} /* LIS302DL_LowpowerCmd */

// -----------------------------------------------------------------------------
//  LIS302DL_DataRateCmd
// -----------------------------------------------------------------------------
void LIS302DL_DataRateCmd(IODevice dev, uint8_t DataRateValue)
{
  uint8_t tmpreg;

  // Read CTRL_REG1 register
  LIS302DL_Read(dev, &tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);

  // Set new Data rate configuration
  tmpreg &= (uint8_t)~LIS302DL_DATARATE_400;
  tmpreg |= DataRateValue;

  // Write value to MEMS CTRL_REG1 regsister
  LIS302DL_Write(dev, &tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);

} /* LIS302DL_DataRateCmd */

// -----------------------------------------------------------------------------
//  LIS302DL_FullScaleCmd
// -----------------------------------------------------------------------------
void LIS302DL_FullScaleCmd(IODevice dev, uint8_t FS_value)
{
  uint8_t tmpreg;

  // Read CTRL_REG1 register
  LIS302DL_Read(dev, &tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);

  // Set new full scale configuration
  tmpreg &= (uint8_t)~LIS302DL_FULLSCALE_9_2;
  tmpreg |= FS_value;

  // Write value to MEMS CTRL_REG1 regsister
  LIS302DL_Write(dev, &tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);

} /* LIS302DL_FullScaleCmd */

// -----------------------------------------------------------------------------
//  LIS302DL_RebootCmd
// -----------------------------------------------------------------------------
void LIS302DL_RebootCmd(IODevice dev)
{
  uint8_t tmpreg;
  // Read CTRL_REG2 register
  LIS302DL_Read(dev, &tmpreg, LIS302DL_CTRL_REG2_ADDR, 1);

  // Enable or Disable the reboot memory
  tmpreg |= LIS302DL_BOOT_REBOOTMEMORY;

  // Write value to MEMS CTRL_REG2 regsister
  LIS302DL_Write(dev, &tmpreg, LIS302DL_CTRL_REG2_ADDR, 1);

} /* LIS302DL_RebootCmd */

// -----------------------------------------------------------------------------
//  LIS302DL_GetPosition
// -----------------------------------------------------------------------------
void LIS302DL_GetPosition(IODevice dev, LIS302DL_Position *pos)
{
  uint8_t tmpreg[5];

  // Read X,Y,Z register in one time
  LIS302DL_Read(dev, tmpreg, LIS302DL_OUT_X_ADDR, 5);

  if(NULL != pos){
	  pos->X_axis = tmpreg[0];
  	  pos->Y_axis = tmpreg[2];
  	  pos->Z_axis = tmpreg[4];
   }

} /* LIS302DL_GetPosition */

// -----------------------------------------------------------------------------
//  LIS302DL_ReadACC
// -----------------------------------------------------------------------------
void LIS302DL_ReadACC(IODevice dev, int32_t* out)
{
  uint8_t buffer[6];
  uint8_t crtl, i = 0x00;

  LIS302DL_Read(dev, &crtl, LIS302DL_CTRL_REG1_ADDR, 1);
  LIS302DL_Read(dev, buffer, LIS302DL_OUT_X_ADDR, 6);

  switch(crtl & 0x20)
    {
    // FS bit = 0 ==> Sensitivity typical value = 18milligals/digit
    case 0x00:
      for(i=0; i<0x03; i++)
      {
        *out =(int32_t)(LIS302DL_SENSITIVITY_2_3G *  (int8_t)buffer[2*i]);
        out++;
      }
      break;
    // FS bit = 1 ==> Sensitivity typical value = 72milligals/digit
    case 0x20:
      for(i=0; i<0x03; i++)
      {
        *out =(int32_t)(LIS302DL_SENSITIVITY_9_2G * (int8_t)buffer[2*i]);
        out++;
      }
      break;
    default:
      break;
    }

 } /* LIS302DL_ReadACC */

// -----------------------------------------------------------------------------
//  LIS302DL_Write
// -----------------------------------------------------------------------------
void LIS302DL_Write(IODevice dev, uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
  // Configure the MS bit:
  //     - When 0, the address will remain unchanged in multiple read/write commands.
  //     - When 1, the address will be auto incremented in multiple read/write commands.
  if(NumByteToWrite > 0x01)
  {
    WriteAddr |= (uint8_t)MULTIPLEBYTE_CMD;
  }
  // Set chip select Low at the start of the transmission
  LIS302DL_RELEASE_CS();

  // Send the Address of the indexed register

  IODEV_Write(dev, &WriteAddr, 1, 0);

  // Send the data that will be written into the device (MSB First)
  IODEV_Write(dev, pBuffer, NumByteToWrite, 0);

  // Set chip select High at the end of the transmission
  LIS302DL_ASSERT_CS();

} /* LIS302DL_Write */

// -----------------------------------------------------------------------------
//  LIS302DL_Read
// -----------------------------------------------------------------------------
void LIS302DL_Read(IODevice dev, uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{
  if(NumByteToRead > 0x01)
  {
    ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
  }
  else
  {
    ReadAddr |= (uint8_t)READWRITE_CMD;
  }
  // Set chip select Low at the start of the transmission
  LIS302DL_RELEASE_CS();

  // Send the Address of the indexed register
  IODEV_Write(dev, &ReadAddr, 1, 0);

  // Receive the data that will be read from the device (MSB First)
  IODEV_Read(dev, pBuffer, NumByteToRead, 0);

  // Set chip select High at the end of the transmission
  LIS302DL_ASSERT_CS();

} /* LIS302DL_Read */
