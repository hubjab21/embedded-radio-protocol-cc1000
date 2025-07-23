/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda
 Purpose:       HALFRED's lis302dl functionality example
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses IO module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

// include the one and only HAL header
#include "hal.h"
#include "hal_port_lis302dl.h"

volatile int _IRQ = 1;

// interrupt handler
void LIS302DL_INT1_Handler(void);

// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void)
{
// -----------------------------------------------------------------------------
//  Low Lewel HAL Init Section
// -----------------------------------------------------------------------------

	// initialize HAL core
	CORE_Init();
	CORE_EnableInterrupts();

	// initialize clock controller
	CC_Init(cc_stm32);

	// setup HSE clock
	CC_SetClockSource(cc_stm32, STM32_HSE_CLOCK, STM32_XTAL_CLOCK_SOURCE, STM32_XTAL_FREQ);
	// setup PLL
	CC_SetClockSource(cc_stm32, STM32_PLL_CLOCK, STM32_HSE_CLOCK_SOURCE, 64000000);
	// setup SYSCLK (At the end)
	CC_SetClockSource(cc_stm32, STM32_SYSCLK_CLOCK, STM32_PLL_CLOCK_SOURCE, 64000000);
	// setup HCLK
	CC_SetClockSource(cc_stm32, STM32_HCLK_CLOCK, STM32_SYSCLK_CLOCK_SOURCE, 64000000);
	// setup PCLK1 max 42MHz
	CC_SetClockSource(cc_stm32, STM32_PCLK1_CLOCK, STM32_HCLK_CLOCK_SOURCE, 32000000);
	// setup PCLK2 max 82MHz
	CC_SetClockSource(cc_stm32, STM32_PCLK2_CLOCK, STM32_HCLK_CLOCK_SOURCE, 32000000);

	HAL_GPIO_Init();

// -----------------------------------------------------------------------------
//  Diagnostic Declaration Section
// -----------------------------------------------------------------------------

	IODEV_Init(IO_DEV);
	IODEV_EnableWrite(IO_DEV);
	IODEV_EnableRead(IO_DEV);

	DIAG_Init();
	DIAG_SetOutputDevice(0, IO_DEV);
    DIAG_ActivateChannel(0);

// -----------------------------------------------------------------------------
//  IO SPI Declaration Section
// -----------------------------------------------------------------------------

    IODEV_Init(IO_SPI);
    IODEV_EnableRead(IO_SPI);
    IODEV_EnableWrite(IO_SPI);

// -----------------------------------------------------------------------------
//  GPIO Configuration Section
// -----------------------------------------------------------------------------

    // chip select pin
    HAL_GPIO_ConfigurePin(LIS302DL_CS, DEFAULT_CONFIG);
    HAL_GPIO_SetPinHigh(LIS302DL_CS);

    // for demo irq
    HAL_GPIO_ConfigurePin(LIS302DL_INT1, DEFAULT_CONFIG);

    // for demo polling
    HAL_GPIO_ConfigurePin(X_AXIS_LOW,  DEFAULT_CONFIG);
    HAL_GPIO_ConfigurePin(X_AXIS_HIGH, DEFAULT_CONFIG);
    HAL_GPIO_ConfigurePin(Y_AXIS_LOW,  DEFAULT_CONFIG);
    HAL_GPIO_ConfigurePin(Y_AXIS_HIGH, DEFAULT_CONFIG);

// -----------------------------------------------------------------------------
//  Who Am I Test Section
// -----------------------------------------------------------------------------

    uint8_t device_id;

    // read WHO_AM_I register
    LIS302DL_GetDeviceInfo(IO_SPI, &device_id);

    // should get 0x3B
    if(0x3B != device_id){
    	DIAG_LogMsg(0, "Cannot connect with LIS302DL device!");
    	while(1);
    }

    DIAG_LogMsg(0, "Successfully connect with LIS302DL device!");
    DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Main Configuration LIS302DL Section
// -----------------------------------------------------------------------------

    // initialize structure
    LIS302DL_InitTypeDef  LIS302DL_InitStruct;

    LIS302DL_InitStruct.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
    LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
    LIS302DL_InitStruct.Axes_Enable = LIS302DL_X_ENABLE | LIS302DL_Y_ENABLE | LIS302DL_Z_ENABLE;
    LIS302DL_InitStruct.Full_Scale = LIS302DL_FULLSCALE_2_3;
    LIS302DL_InitStruct.Self_Test = LIS302DL_SELFTEST_NORMAL;

    // init lis302dl device
    LIS302DL_Init(IO_SPI, &LIS302DL_InitStruct);

// -----------------------------------------------------------------------------
//  Filter Configuration LIS302DL Section
// -----------------------------------------------------------------------------

   // filter config structure
   LIS302DL_FilterConfigTypeDef LIS302DL_FilterStruct;

   // set configuration of Internal High Pass Filter of LIS302DL
   LIS302DL_FilterStruct.HighPassFilter_Data_Selection = LIS302DL_FILTEREDDATASELECTION_OUTPUTREGISTER;
   LIS302DL_FilterStruct.HighPassFilter_CutOff_Frequency = LIS302DL_HIGHPASSFILTER_LEVEL_1;
   LIS302DL_FilterStruct.HighPassFilter_Interrupt = LIS302DL_HIGHPASSFILTERINTERRUPT_1_2;

   // configure high pass filter
   LIS302DL_FilterConfig(IO_SPI, &LIS302DL_FilterStruct);

// -----------------------------------------------------------------------------
//  Click Configuration Interrupt LIS302DL Section
// -----------------------------------------------------------------------------

   // interrupt config structure
   LIS302DL_ClickConfigTypeDef LIS302DL_ClickConfigStruct;

   LIS302DL_ClickConfigStruct.Latch_Request = LIS302DL_INTERRUPTREQUEST_NOTLATCHED;
   LIS302DL_ClickConfigStruct.SingleClick_Axes = LIS302DL_CLICKINTERRUPT_XYZ_DISABLE;
   LIS302DL_ClickConfigStruct.DoubleClick_Axes = LIS302DL_DOUBLECLICKINTERRUPT_XYZ_DISABLE;
   LIS302DL_ClickConfigStruct.Threshold_X = LIS302DL_CLICKTHRESHOLD_3_0g;
   LIS302DL_ClickConfigStruct.Threshold_Y = LIS302DL_CLICKTHRESHOLD_3_5g;
   LIS302DL_ClickConfigStruct.Threshold_Z = LIS302DL_CLICKTHRESHOLD_6_0g;
   LIS302DL_ClickConfigStruct.Time_Limit = 50; /* value form 0 to 255 */
   LIS302DL_ClickConfigStruct.Latency_Time = 50; /* value form 0 to 255 */
   LIS302DL_ClickConfigStruct.Window_Size = 100; /* value form 0 to 255 */

   // configure interrupts
   LIS302DL_ClickConfig(IO_SPI, &LIS302DL_ClickConfigStruct);

   // needed 30ms after configuration !!
   DELAY_MS(30);

// -----------------------------------------------------------------------------
//  Free Fall / Wake Up Interrupt LIS302DL Section
// -----------------------------------------------------------------------------

   // free fall / wake up config structure
   LIS302DL_FFWUTypeDef LIS302DL_FFWUStruct;

   LIS302DL_FFWUStruct.Latch_Request = LIS302DL_INTERRUPTREQUEST_NOTLATCHED;
   LIS302DL_FFWUStruct.Enable_Interrupt = LIS302DL_X_HIGHER_ENABLE | LIS302DL_Y_HIGHER_ENABLE;
   LIS302DL_FFWUStruct.Interrupt_Combination = LIS302DL_INTERRUPT_OR_COMBINATION;
   LIS302DL_FFWUStruct.Reseting_Mode = LIS302DL_COUNTER_RESETTED;
   LIS302DL_FFWUStruct.Threshold_FFWU = 10; /* value form 0 to 127 */
   LIS302DL_FFWUStruct.Duration_Time = 2; /* value form 0 to 255 */

   // configure FFWU1
   LIS302DL_FFWU1Config(IO_SPI, &LIS302DL_FFWUStruct);

// -----------------------------------------------------------------------------
//  Interrupt configuration LIS302DL Section
// -----------------------------------------------------------------------------

  // free fall / wake up config structure
   LIS302DL_InterruptTypeDef LIS302DL_InterruptStruct;

   LIS302DL_InterruptStruct.InterruptActive_Type = LIS302DL_INTERRUPT_ACTIVE_HIGH;
   LIS302DL_InterruptStruct.InterruptOut_Mode = LIS302DL_INTERRUPT_PUSH_PULL;
   LIS302DL_InterruptStruct.FFWU1_InterruptEnable = LIS302DL_SIGNAL_FFWU1;
   LIS302DL_InterruptStruct.FFWU2_InterruptEnable = LIS302DL_SIGNAL_GND;

  // configure interrupts
  LIS302DL_InterruptConfig(IO_SPI, &LIS302DL_InterruptStruct);

// -----------------------------------------------------------------------------
//  Get Position LIS302DL Section
// -----------------------------------------------------------------------------

   LIS302DL_Position position;

   DIAG0_LogNL(0);
   DIAG0_LogMsg(0, "Actual Position: ");
   DIAG0_LogNL(0);

   // get position X,Y,Z
   LIS302DL_GetPosition(IO_SPI, &position);

   DIAG0_LogMsg(0, "X: ");
   DIAG0_LogINT(0, position.X_axis, 10);
   DIAG0_LogNL(0);

   DIAG0_LogMsg(0, "Y: ");
   DIAG0_LogINT(0, position.Y_axis, 10);
   DIAG0_LogNL(0);

   DIAG0_LogMsg(0, "Z: ");
   DIAG0_LogINT(0, position.Z_axis, 10);
   DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Demo IRQ LIS302DL Section
// -----------------------------------------------------------------------------

   // dummy wait
   DELAY_MS(100);

   DIAG0_LogNL(0);
   DIAG0_LogMsg(0, "This demo show some interrupt features of LIS302DL.");
   DIAG0_LogNL(0);
   DIAG0_LogMsg(0, "Try to shake your electronics (like free-fall) !");
   DIAG0_LogNL(0);

   HAL_GPIO_SetEventHandler(LIS302DL_INT1, LIS302DL_INT1_Handler);

   HAL_GPIO_EnableEvent(LIS302DL_INT1, GPIO_TRIGGER_EDGE_RISING);

   while(_IRQ){
	   ;
   }

// -----------------------------------------------------------------------------
//  Demo Polling LIS302DL Section
// -----------------------------------------------------------------------------

   DIAG0_LogNL(0);
   DIAG0_LogMsg(0, "This demo show polling features of LIS302DL.");
   DIAG0_LogNL(0);
   DIAG0_LogMsg(0, "Starting offset is considered.");
   DIAG0_LogNL(0);
   DIAG0_LogMsg(0, "Try to move your electronics!");
   DIAG0_LogNL(0);

   // starting offset
   LIS302DL_Position startOffset;

   // get position X,Y,Z
   LIS302DL_GetPosition(IO_SPI, &startOffset);

   // position state
   LIS302DL_Position temp;

   while(1)
   {
	   LIS302DL_GetPosition(IO_SPI, &temp);

	    HAL_GPIO_SetPinLow(X_AXIS_LOW);
	    HAL_GPIO_SetPinLow(X_AXIS_HIGH);
	    HAL_GPIO_SetPinLow(Y_AXIS_LOW);
	    HAL_GPIO_SetPinLow(Y_AXIS_HIGH);


	   if((temp.X_axis-startOffset.X_axis) > 5){
		   HAL_GPIO_SetPinHigh(X_AXIS_HIGH);
	   }else if((temp.X_axis-startOffset.X_axis) < -5){
		   HAL_GPIO_SetPinHigh(X_AXIS_LOW);
	   }

	   if((temp.Y_axis-startOffset.Y_axis) > 5){
		   HAL_GPIO_SetPinHigh(Y_AXIS_HIGH);
	   }else if((temp.Y_axis-startOffset.Y_axis) < -5){
		   HAL_GPIO_SetPinHigh(Y_AXIS_LOW);
	   }

	   DELAY_MS(100);
   }

// -----------------------------------------------------------------------------
//  Deinitialization HAL Section
// -----------------------------------------------------------------------------

    // deinitialize SPI
    IODEV_Deinit(IO_SPI);

	// deinitialize IODevice
	IODEV_Deinit(IO_DEV);

	// deinitialize HAL core
	CORE_Deinit();
	
	return 0;

} /* main */

void LIS302DL_INT1_Handler(void){

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Interrupt occured!");
	DIAG0_LogNL(0);

	_IRQ = 0;

	HAL_GPIO_DisableEvent(LIS302DL_INT1);

}

/*! \file main.c
    \brief Exemplary application, that uses IOBUS module.

*/
