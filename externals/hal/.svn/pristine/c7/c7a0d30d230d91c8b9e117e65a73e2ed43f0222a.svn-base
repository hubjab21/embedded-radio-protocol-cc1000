/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_clk.c
 Author:        Lukasz Krzak, Lukasz Duda, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      ATMEL SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       CLK module port for ATMEL SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal.h"
#include <stdlib.h>

// Helper definitions
// Xtal frequency
#ifndef SAM3S_XTAL_FREQ
#define SAM3S_XTAL_FREQ 0
#endif

// Bypassed frequency
#ifndef SAM3S_EXT_FREQ
#define SAM3S_EXT_FREQ 0
#endif

HALRESULT CLK_PORT_Init(ClockController cc);
HALRESULT CLK_PORT_Deinit(ClockController cc);
HALRESULT CLK_PORT_SetClockSource(ClockController cc, int clk, int clk_src, uint32_t freq);
int CLK_PORT_GetClockSource(ClockController cc, int clk);
uint32_t CLK_PORT_GetClockSourceFreq(ClockController cc, int clk_src);
uint32_t CLK_PORT_GetClockFrequency(ClockController cc, int clk);

struct ClockControllerDesc cc_sam3s_desc = {
	.Init = CLK_PORT_Init,
	.Deinit = CLK_PORT_Deinit,
	.SetClockSource = CLK_PORT_SetClockSource,
	.GetClockSource = CLK_PORT_GetClockSource,
	.GetClockSourceFreq = CLK_PORT_GetClockSourceFreq,
	.GetClockFrequency = CLK_PORT_GetClockFrequency
};
// Helper structure
typedef struct{
	uint32_t multip;
	uint32_t divid;
	uint32_t div2;
}data_result;

// Helper functions
uint32_t HAL_Port_Calculate_EmbeddedRC(uint32_t freq);
uint32_t HAL_Port_Calculate_MasterPrescaler(uint32_t freq, uint32_t base_freq);
uint32_t HAL_Port_Calculate_MasterFreq(uint32_t prescaler, uint32_t clock);
data_result HAL_Port_Calculate_PllPrescaler(uint32_t freq, uint32_t base_freq);
void HAL_CLK_FlashPrefetch(uint32_t freq);
ClockController cc_sam3s = &cc_sam3s_desc;

// Helper variables
static uint32_t xck_freq = 0;
static uint32_t slck_freq = 32000;

// Variables for PLLB
static uint32_t multiplerb=1;
static uint32_t dividerb=1;

// Variables for PLLA
static uint32_t multiplera=1;
static uint32_t dividera=1;

// -----------------------------------------------------------------------------
//  CLK_PORT_Init
// -----------------------------------------------------------------------------
HALRESULT CLK_PORT_Init(ClockController cc)
{

	return HALRESULT_OK;

} /* CLK_PORT_Init */


// -----------------------------------------------------------------------------
//  CLK_PORT_Deinit
// -----------------------------------------------------------------------------
HALRESULT CLK_PORT_Deinit(ClockController cc)
{

	return HALRESULT_OK;

} /* CLK_PORT_Init */


// -----------------------------------------------------------------------------
//  CLK_PORT_SetClockSource
// -----------------------------------------------------------------------------
HALRESULT CLK_PORT_SetClockSource(ClockController cc, int clk, int clk_src, uint32_t freq)
{
	data_result result;
	uint32_t embedded_rc;
	uint32_t presc;

	// Set good numbers of wait states for flash memory
	HAL_CLK_FlashPrefetch(freq);

	switch (clk) {
	case SAM3S_MAIN_CLOCK:
		// Main clock
		switch (clk_src) {

		case SAM3S_RC_CLOCK_SOURCE:

			// Set internal RC oscillator (4,8 or 12MHz) as main clock
			embedded_rc = HAL_Port_Calculate_EmbeddedRC(freq);

			// Enable embedded RC oscillator at the best frequency

			CKGR_MOR = CKGR_MOR_KEY | CKGR_MOR_MOSCRCEN | embedded_rc ;

			// Wait the RC to stabilize
			while (!(PMC_SR & PMC_SR_MOSCRCS)){
				;
			}
			break;

		case SAM3S_XTAL_CLOCK_SOURCE:


			// Set xtal ( 3-20 MHz) as main clock
			CKGR_MOR = (CKGR_MOR & ~CKGR_MOR_MOSCXTBY) | CKGR_MOR_KEY | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCXTST(SAM3S_MAIN_STARTUP_TIMEOUT);

			// Wait the Xtal to stabilize
			while (!(PMC_SR & PMC_SR_MOSCXTS)) {
				;
			}

			// Confirm xtal as main clock
			CKGR_MOR |= CKGR_MOR_KEY | CKGR_MOR_MOSCSEL;
			break;

		case SAM3S_EXTERNAL_CLOCK_SOURCE:

			// Set external clock by bypassing the main oscillator as main clock
			CKGR_MOR = (CKGR_MOR & ~CKGR_MOR_MOSCXTEN) | CKGR_MOR_KEY | CKGR_MOR_MOSCXTBY | CKGR_MOR_MOSCSEL;

			// Save external clock frequency
			xck_freq = freq;

			break;
		default:
			// other options not possible
			return HALRESULT_ERROR;
			break;
		} // switch (clk_src)

		return HALRESULT_OK;
		break;

	case SAM3S_SLOW_CLOCK:
		// Slow clock
		switch (clk_src) {
		case SAM3S_RC_CLOCK_SOURCE:

			// Set internal RC oscillator as slow clock (SUPC_CR_KEY is the register access key)
			SUPC_CR = SUPC_CR_KEY;
			break;

		case SAM3S_XTAL_CLOCK_SOURCE:

			// set external oscillator as slow clock
			SUPC_CR = SUPC_CR_KEY | SUPC_CR_XTALSEL;
			// wait the Xtal to stabilize
			while (!(SUPC_SR & SUPC_SR_OSCSEL)){
				;
			}
			// WARNNING: Switching SCLK back to RC is only possible by shutting down the VDDIO power supply.

			// Save clock frequency
			slck_freq = freq;
			break;

		case SAM3S_EXTERNAL_CLOCK_SOURCE:

			// Set external clock by bypassing the main oscillator as slow clock
			SUPC_MR |= SUPC_MR_KEY | SUPC_MR_OSCBYPASS;
			SUPC_CR |= SUPC_CR_KEY | SUPC_CR_XTALSEL;
			// WARNNING: Switching SCLK back to RC is only possible by shutting down the VDDIO power supply.

			// Save clock frequency
			slck_freq = freq;
			break;
		default:
			// other options not possible
			return HALRESULT_ERROR;
			break;

		} // switch (clk_src)

		return HALRESULT_OK;

		break;

	case SAM3S_MASTER_CLOCK:
		// master clock

		// disable write protection for PMC registers
		PMC_WPMR = 0x504D4300;

		switch (clk_src) {
		case SAM3S_SLOW_CLOCK_SOURCE:

			// Set slow clock as master clock
			// Calculate right prescaler
			presc = HAL_Port_Calculate_MasterPrescaler(freq, slck_freq);
			//	Turn  on slow clock as master clock
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_CSS_Msk)) | PMC_MCKR_CSS_SLOW_CLK;

			// Wait for active this choose
			while(!(PMC_SR & PMC_SR_MCKRDY)) {
				;
			}
			// Turn on right prescaler
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_PRES_Msk)) | presc;

			// Wait for active this choose
			while(!(PMC_SR & PMC_SR_MCKRDY)) {
				;
			}

			break;

		case SAM3S_MAIN_CLOCK_SOURCE:

			// Set main clock as master clock
			// Calculate the right prescaler
			presc = HAL_Port_Calculate_MasterPrescaler(freq, CLK_PORT_GetClockFrequency(cc_sam3s, SAM3S_MAIN_CLOCK));
			// Turn on main clock as master clock
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_CSS_Msk)) | PMC_MCKR_CSS_MAIN_CLK;

			// Wait for active this choose
			while(!(PMC_SR & PMC_SR_MCKRDY)) {
				;
			}

			// Turn on right prescaler
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_PRES_Msk)) | presc;

			// Wait for active this choose
			while(!(PMC_SR & PMC_SR_MCKRDY)) {
				;
			}

			break;

		case SAM3S_PLLA_CLOCK_SOURCE:

			// Set PLLA source as master clock
			// Get frequency from main clock and calculate Pll Prescaler
			result = HAL_Port_Calculate_PllPrescaler(freq,  CLK_PORT_GetClockFrequency(cc_sam3s, SAM3S_MAIN_CLOCK));
			dividera = result.divid;
			multiplera = result.multip;

			// Select main clock as master clock input
			PMC_MCKR =  (PMC_MCKR & (~PMC_MCKR_CSS_Msk)) | PMC_MCKR_CSS_MAIN_CLK ;

			// Wait for set this setting
			while(!(PMC_SR & PMC_SR_MCKRDY)){
				;
			}

			// Select prescaler as 1
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_PRES_Msk)) | PMC_MCKR_PRES_CLK_1;

			// Wait for set this setting
			while(!(PMC_SR & PMC_SR_MCKRDY)){
				;
			}

			// Disable PLLA
			CKGR_PLLAR = CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(0);

			// Set Pll
			CKGR_PLLAR = CKGR_PLLAR_ONE | CKGR_PLLAR_DIVA(dividera) | CKGR_PLLAR_PLLACOUNT(SAM3S_PLLA_STARTUP_TIMEOUT) | CKGR_PLLAR_MULA(multiplera);

			// Wait for set this setting
			while ((PMC_SR & PMC_SR_LOCKA) == 0){
				;
			}

			// Set master clock prescaler
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_PRES_Msk)) |  (result.div2);

			// Wait for set this setting
			while(!(PMC_SR & PMC_SR_MCKRDY)){
				;
			}


			// Turn on master clock from plla
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_CSS_Msk)) | PMC_MCKR_CSS_PLLA_CLK ;

			//Wait for set this setting
			while(!(PMC_SR & PMC_SR_MCKRDY)){
				;
			}

			break;

		case SAM3S_PLLB_CLOCK_SOURCE:

			// Set PLLB source as master clock
			// Get frequency from main clock and calculate Pll Prescaler
			result = HAL_Port_Calculate_PllPrescaler(freq, CLK_PORT_GetClockFrequency(cc_sam3s, SAM3S_MAIN_CLOCK));
			dividerb=result.divid;
			multiplerb=result.multip;

			// Select main clock as master clock input
			PMC_MCKR =  (PMC_MCKR & (~PMC_MCKR_CSS_Msk)) | PMC_MCKR_CSS_MAIN_CLK;

			// Wait for set this setting
			while(!(PMC_SR & PMC_SR_MCKRDY)){
				;
			}

			// Select prescaler as 1
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_PRES_Msk)) | PMC_MCKR_PRES_CLK_1;

			// Wait for set this setting
			while(!(PMC_SR & PMC_SR_MCKRDY)){
							;
						}
			// Disable PLL
			CKGR_PLLBR = CKGR_PLLBR_MULB(0);

			// Set pll
			CKGR_PLLBR = CKGR_PLLBR_DIVB(dividerb) | CKGR_PLLBR_PLLBCOUNT(SAM3S_PLLB_STARTUP_TIMEOUT) | CKGR_PLLBR_MULB(multiplerb);

			// Wait for set this setting
			while ((PMC_SR & PMC_SR_LOCKB) == 0){
				;
			}

			// Set master clock prescaler
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_PRES_Msk)) | (result.div2);
			//wait for set this setting
			while(!(PMC_SR & PMC_SR_MCKRDY)){
				;
			}
			// Turn on master clock from pllb
			PMC_MCKR = (PMC_MCKR & (~PMC_MCKR_CSS_Msk)) | PMC_MCKR_CSS_PLLB_CLK;

			// Wait for set this setting
			while(!(PMC_SR & PMC_SR_MCKRDY)){
				;
			}

			break;

		default:
			// other options not possible

			return HALRESULT_ERROR;
			break;
	} // switch (clk src)

		return HALRESULT_OK;
		break;

	default:
		// unknown clock
		return HALRESULT_ERROR;
	} // switch (clk)

	return HALRESULT_ERROR;

} /* CLK_PORT_SetClockSource */


// -----------------------------------------------------------------------------
//  CLK_PORT_GetClockSource
// -----------------------------------------------------------------------------
int CLK_PORT_GetClockSource(ClockController cc, int clk)
{
	switch ((CORE_PORT_Clock)clk) {

	case SAM3S_MAIN_CLOCK:

		if((CKGR_MOR & CKGR_MOR_MOSCXTBY)){
			// Bypass is selected
			return SAM3S_EXTERNAL_CLOCK_SOURCE;
		} else if((CKGR_MOR & CKGR_MOR_MOSCXTEN)){
			return SAM3S_XTAL_CLOCK_SOURCE;
		}else{
			return SAM3S_RC_CLOCK_SOURCE;
		}


		break;

	case SAM3S_SLOW_CLOCK:

		// Check if the embedded RC oscillator is selected
		 if(SUPC_MR & SUPC_MR_OSCBYPASS){

			// Bypass is selected
			return SAM3S_EXTERNAL_CLOCK_SOURCE;

		 }else if ((SUPC_SR & SUPC_SR_OSCSEL)) {
			 // Crystal Oscillator is selected
			return SAM3S_XTAL_CLOCK_SOURCE;

		}else{

			// The embedded 32kHz RC oscillator is selected
			return SAM3S_RC_CLOCK_SOURCE;
		}
	break;

	case SAM3S_MASTER_CLOCK:

		switch(PMC_MCKR & 0x03u){
		case 0:

			// Slow Clock is selected
			return SAM3S_SLOW_CLOCK_SOURCE;
			break;
		case 1:

			// Main Clock is selected
			return SAM3S_MAIN_CLOCK_SOURCE;
			break;
		case 2:

			// PLLA Clock is selected
			return SAM3S_PLLA_CLOCK_SOURCE;
			break;
		case 3:

			// PLLB Clock is selected
			return SAM3S_PLLB_CLOCK_SOURCE;
			break;
		default:

			// No other options are possible
			return SAM3S_UNKNOWN_CLOCK_SOURCE;
			break;
		} // switch(PMC_MCKR & 0x03u)
		break;
		default:
			// Unknown clock was requested
			break;
	} // Switch (clk)

	// By default return a value meaning that clock source is unknown
	return SAM3S_UNKNOWN_CLOCK_SOURCE;

} /* CLK_PORT_GetClockSource */


// -----------------------------------------------------------------------------
//  CLK_PORT_GetClockSourceFreq
// -----------------------------------------------------------------------------
uint32_t CLK_PORT_GetClockSourceFreq(ClockController cc, int clk_src)
{
	switch ((CORE_PORT_ClockSource)clk_src) {

	case SAM3S_RC_CLOCK_SOURCE:

		switch ((CKGR_MOR & CKGR_MOR_MOSCRCF_Msk) >> 4) {
		case 0:
			return 4000000;
			break;
		case 1:
			return 8000000;
			break;
		case 2:
			return 12000000;
			break;
		default:
			// Other values may indicate hardware error
			break;
		} // Switch ((CKGR_MOR & CKGR_MOR_MOSCRCF_Msk) >> 4)
		break;

		case SAM3S_XTAL_CLOCK_SOURCE:

			return SAM3S_XTAL_FREQ;
			break;

		case SAM3S_SLOW_CLOCK_SOURCE:

			return slck_freq;
			break;

		case SAM3S_MAIN_CLOCK_SOURCE:

			return CLK_PORT_GetClockFrequency(cc_sam3s, SAM3S_MAIN_CLOCK);
			break;

		default:
			// Unknown clock
			break;
	} // Switch (clk_src)

	// By default return 0
	return 0;

} /* CLK_PORT_GetClockSourceFreq */

// -----------------------------------------------------------------------------
//  CLK_PORT_GetClockFrequency
// -----------------------------------------------------------------------------
uint32_t CLK_PORT_GetClockFrequency(ClockController cc, int clk)
{

	switch ((CORE_PORT_Clock)clk) {

	case SAM3S_MAIN_CLOCK:
		// Main clock
		if((CKGR_MOR & CKGR_MOR_MOSCXTBY)){
			// Bypass - main clock
			return SAM3S_EXT_FREQ;
		}else if((CKGR_MOR & CKGR_MOR_MOSCXTEN)){

			// Xtal -main clock
			return SAM3S_XTAL_FREQ;
		}else{
			// Embedded RC oscillator
			uint32_t embedded_rc_selection = ((CKGR_MOR & CKGR_MOR_MOSCRCF_Msk) >> 4);

			if(embedded_rc_selection == 0){
				embedded_rc_selection = 4000000;
			}else if(embedded_rc_selection == 1){
				embedded_rc_selection = 8000000;
			}else{
				embedded_rc_selection = 12000000;
			}

			return embedded_rc_selection;
		}
		break;

	case SAM3S_SLOW_CLOCK:
		// Slow clock
		return slck_freq;
		break;

	case SAM3S_MASTER_CLOCK:

		if((PMC_MCKR & PMC_MCKR_CSS_Msk) == PMC_MCKR_CSS_MAIN_CLK){

			//  Master CLK <- Main CLK
			uint32_t prescaler_pmc = ((PMC_MCKR & PMC_MCKR_PRES_Msk) >> 4);

			if((CKGR_MOR & CKGR_MOR_MOSCXTBY)){

				//  Master CLK <- Main CLK <- Bypass
				return HAL_Port_Calculate_MasterFreq(prescaler_pmc, SAM3S_EXT_FREQ);
			}else if(!(CKGR_MOR & CKGR_MOR_MOSCXTEN)) {

				//  Master CLK <- Main CLK <- Embedded RC
				uint32_t embedded_rc_selection = ((CKGR_MOR & CKGR_MOR_MOSCRCF_Msk) >> 4);

				if(embedded_rc_selection == 0){
					embedded_rc_selection = 4000000;
				}else if(embedded_rc_selection == 1){
					embedded_rc_selection = 8000000;
				}else{
					embedded_rc_selection = 12000000;
				}
				return HAL_Port_Calculate_MasterFreq(prescaler_pmc, embedded_rc_selection);

			}else{

				//  Master CLK <- Main CLK <- Xtal
				uint32_t xtal_freq = SAM3S_XTAL_FREQ;
				return HAL_Port_Calculate_MasterFreq(prescaler_pmc, xtal_freq);


			}
		}else if((PMC_MCKR & PMC_MCKR_CSS_Msk) == PMC_MCKR_CSS_SLOW_CLK){

			//  Master CLK <- Slow clock
			uint32_t prescaler_pmc = ((PMC_MCKR & PMC_MCKR_PRES_Msk) >> 4);
			if(SUPC_MR & SUPC_MR_OSCBYPASS){

				//  Master CLK <- Slow clock <- Bypass
				return HAL_Port_Calculate_MasterFreq(prescaler_pmc, slck_freq);

			}else if(PMC_SR & PMC_SR_OSCSELS){

				//  Master CLK <- Slow clock <- 32kHz crystal
				return HAL_Port_Calculate_MasterFreq(prescaler_pmc, 32768);

			}else{

				//  Master CLK <- Slow clock <- embedded RC oscillator
				return HAL_Port_Calculate_MasterFreq(prescaler_pmc, 32000);
			}
		}else if((PMC_MCKR & PMC_MCKR_CSS_Msk) == PMC_MCKR_CSS_PLLA_CLK){
			//  Master CLK <- PLL A
			uint32_t prescaler_pmc = ((PMC_MCKR & PMC_MCKR_PRES_Msk) >> 4);


			if((CKGR_MOR & CKGR_MOR_MOSCXTBY)){

				//  Master CLK <- PLL A <- Main Clk <- Bypass
				uint32_t ext_freq=0;

				ext_freq=SAM3S_EXT_FREQ;
				if(PMC_MCKR & PMC_MCKR_PLLADIV2){
					ext_freq/=2;
				}
				ext_freq=ext_freq*(multiplera+1)/dividera;
				return HAL_Port_Calculate_MasterFreq(prescaler_pmc, ext_freq);

			}else if(CKGR_MOR & CKGR_MOR_MOSCXTEN){

				//  Master CLK <- PLL A <- Main Clk <- Xtal
				uint32_t xtal_freq=0;
				xtal_freq=SAM3S_XTAL_FREQ;
				if(PMC_MCKR & PMC_MCKR_PLLADIV2){
					xtal_freq/=2;
				}
				xtal_freq=xtal_freq*(multiplera+1)/dividera;

				return HAL_Port_Calculate_MasterFreq(prescaler_pmc, xtal_freq);
			}else{
				//  Master CLK <- PLL A <- Main Clk <- embedded RC oscillator
				uint32_t embedded_rc_selection = ((CKGR_MOR & CKGR_MOR_MOSCRCF_Msk) >> 4);
				if(embedded_rc_selection == 0){
					embedded_rc_selection = 4000000;
				}else if(embedded_rc_selection == 1){
					embedded_rc_selection = 8000000;
				}else{
					embedded_rc_selection = 12000000;
				}
				if(PMC_MCKR & PMC_MCKR_PLLADIV2){
					embedded_rc_selection/=2;
				}
				embedded_rc_selection=embedded_rc_selection*(multiplera+1)/dividera;

				return HAL_Port_Calculate_MasterFreq(prescaler_pmc, embedded_rc_selection);
			}


		}else if((PMC_MCKR & PMC_MCKR_CSS_Msk) == PMC_MCKR_CSS_PLLB_CLK){

			//  Master CLK <- PLL B
			uint32_t prescaler_pmc = ((PMC_MCKR & PMC_MCKR_PRES_Msk) >> 4);

			if((CKGR_MOR & CKGR_MOR_MOSCXTBY)){

			//  Master CLK <- PLL B <- Main Clk <- Bypass
			uint32_t ext_freq=0;

			ext_freq=SAM3S_EXT_FREQ;
			if(PMC_MCKR & PMC_MCKR_PLLBDIV2){
				ext_freq/=2;
			}
			ext_freq=ext_freq*(multiplerb+1)/dividerb;
			return HAL_Port_Calculate_MasterFreq(prescaler_pmc, ext_freq);
		}else if(CKGR_MOR & CKGR_MOR_MOSCXTEN){

			//  Master CLK <- PLL B <- Main Clk <- Xtal
			uint32_t xtal_freq=0;
			xtal_freq=SAM3S_XTAL_FREQ;
			if(PMC_MCKR & PMC_MCKR_PLLBDIV2){
				xtal_freq/=2;
			}
			xtal_freq=xtal_freq*(multiplerb+1)/dividerb;

			return HAL_Port_Calculate_MasterFreq(prescaler_pmc, xtal_freq);
		} else {

			//  Master CLK <- PLL B <- Main Clk <- Embedded RC oscillator
			uint32_t embedded_rc_selection = ((CKGR_MOR & CKGR_MOR_MOSCRCF_Msk) >> 4);
			if(embedded_rc_selection == 0){
				embedded_rc_selection = 4000000;
			}else if(embedded_rc_selection == 1){
				embedded_rc_selection = 8000000;
			}else{
				embedded_rc_selection = 12000000;
			}

			if(PMC_MCKR & PMC_MCKR_PLLBDIV2){
				embedded_rc_selection/=2;
			}
			embedded_rc_selection=embedded_rc_selection*(multiplerb+1)/dividerb;

			return HAL_Port_Calculate_MasterFreq(prescaler_pmc, embedded_rc_selection);
			}
		}
		break;

	default:
		// unknown clock

		return 0;
	} // switch (clk)

	return 0;

} /* CLK_PORT_GetClockFrequency */


// -----------------------------------------------------------------------------
//  Helper functions
// -----------------------------------------------------------------------------


/* HAL_Port_Calculate_EmbeddedRC
 *
 *  Find the best Embedded RC value
 *
 *  \param freq Clock target frequency
 *  \return RC value
 */
uint32_t HAL_Port_Calculate_EmbeddedRC(uint32_t freq){

	uint32_t embedded;
	int32_t err, cmp;

	embedded = CKGR_MOR_MOSCRCF_4_MHz;

	// error for 4MHz RC oscillator
	err = labs(4000000 - freq);

	// error for 8MHz RC oscillator
	cmp = labs(8000000 - freq);
	if (cmp < err) {
		embedded = CKGR_MOR_MOSCRCF_8_MHz;
		err = cmp;
	}

	// error for 12MHz RC oscillator
	cmp = labs(12000000 - freq);
	if (cmp < err) {
		embedded = CKGR_MOR_MOSCRCF_12_MHz;
		err = cmp;
	}

	return embedded;
} /*HAL_Port_Calculate_EmbeddedRC*/


/* HAL_Port_Calculate_MasterPrescaler
 *
 *  Find the best Master Clock Prescaler
 *
 *  \param base_freq Clock Source frequency
 *  \param freq Clock target frequency
 *  \return prescaler
 */
uint32_t HAL_Port_Calculate_MasterPrescaler(uint32_t freq, uint32_t base_freq){

	uint32_t presc;
	int32_t err, cmp;

	presc = PMC_MCKR_PRES_CLK_1;

	err = labs((base_freq) - freq);

	cmp = labs((base_freq)/(2) - freq);
	if (cmp < err) {
		presc = PMC_MCKR_PRES_CLK_2;
		err = cmp;
	}

	cmp = labs((base_freq)/(3) - freq);
	if (cmp < err) {
		presc = PMC_MCKR_PRES_CLK_3;
		err = cmp;
	}

	cmp = labs((base_freq)/(4) - freq);
	if (cmp < err) {
		presc = PMC_MCKR_PRES_CLK_4;
		err = cmp;
	}

	cmp = labs((base_freq)/(8) - freq);
	if (cmp < err) {
		presc = PMC_MCKR_PRES_CLK_8;
		err = cmp;
	}

	cmp = labs((base_freq)/(16) - freq);
	if (cmp < err) {
		presc = PMC_MCKR_PRES_CLK_16;
		err = cmp;
	}

	cmp = labs((base_freq)/(32) - freq);
	if (cmp < err) {
		presc = PMC_MCKR_PRES_CLK_32;
		err = cmp;
	}

	cmp = labs((base_freq)/(64) - freq);
	if (cmp < err) {
		presc = PMC_MCKR_PRES_CLK_64;
		err = cmp;
	}

	return presc;
} /*HAL_Port_Calculate_MasterPrescaler*/


/* HAL_Port_Calculate_MasterFreq
 *
 *  Calculate right value of frequency
 *
 *  \param clock Clock Source frequency
 *  \param prescaler Prescaler of this clock
 *  \return right value of frequency
 */
uint32_t HAL_Port_Calculate_MasterFreq(uint32_t prescaler, uint32_t clock)
{
	if(prescaler == 0){
		return (clock)/(1);
	}else if(prescaler == 1){
		return (clock)/(2);
	}else if(prescaler == 2){
		return (clock)/(4);
	}else if(prescaler == 3){
		return (clock)/(8);
	}else if(prescaler == 4){
		return (clock)/(16);
	}else if(prescaler == 5){
		return (clock)/(32);
	}else if(prescaler == 6){
		return (clock)/(64);
	}else if(prescaler== 7){
		return (clock)/(3);
	}
	return 0; //error
} /* HAL_Port_Calculate_MasterFreq*/


/* HAL_Port_Calculate_PllPrescaler
 *
 *  Find the best Pll Clock Prescaler
 *
 *  \param base_freq Clock Source frequency
 *  \param freq Clock target frequency
 *  \return prescaler - multiplier, divider in pll and divider by 2 in master clock
 */
data_result HAL_Port_Calculate_PllPrescaler(uint32_t freq, uint32_t base_freq){
	data_result result;
	int d=0;
	int m=0;
	int err=0;
	int cmp=0;

	if(freq>64000000) {
		freq=64000000;
	}
	if(base_freq<3500000 || base_freq>20000000){//20Mhz>=clk_in>=3.5Mhz
		result.divid=0;
		result.multip=0;
		result.div2=(0x0u << 4);
		return result ;
	}

	err = labs((base_freq) - freq);
	if(err==0){
		result.divid=2;
		result.multip=1;
		result.div2=(0x0u << 4);
		return result ;
	}


	if(freq>=60000000){
		for(m=1;m<=36;m++){
			for(d=1;d<=255;d++){
				cmp= labs((base_freq*(m+1)/(2*d)) - freq);
				if(cmp<err){
					err=cmp;
					result.divid=d;
					result.multip=m;
					result.div2=(0x1u << 4);
				}
			}
		}

	}else{
		for(m=1;m<=36;m++){
			for(d=1;d<=255;d++){
				cmp= labs((base_freq*(m+1)/d) - freq);
				if(cmp<err){
					err=cmp;
					result.divid=d;
					result.multip=m;
					result.div2=(0x0u << 4);
				}
			}
		}
	}
	return result;
}

/* HAL_CLK_FlashPrefetch
 *
 *\param freq Clock frequency
 *  Set good numbers of wait states for flash memory
 */
void HAL_CLK_FlashPrefetch(uint32_t freq)
{
	if(freq<17000000){
		EEFC=((EEFC & (~EEFC_FMR_FWS_Msk))| EEFC_FMR_FWS(0));
	}else if(freq<30000000){
		EEFC=((EEFC & (~EEFC_FMR_FWS_Msk))| EEFC_FMR_FWS(1));
	}else if(freq<54000000){
		EEFC=((EEFC & (~EEFC_FMR_FWS_Msk))| EEFC_FMR_FWS(2));
	}else{
		EEFC=((EEFC & (~EEFC_FMR_FWS_Msk))| EEFC_FMR_FWS(3));
	}

} /* HAL_CLK_FlashPrefetch */


