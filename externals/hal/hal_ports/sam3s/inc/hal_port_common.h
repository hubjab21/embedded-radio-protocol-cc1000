/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_common.h
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       Common declarations port for ATMEL SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/
#ifndef HAL_PORT_COMMON_H
#define HAL_PORT_COMMON_H

#ifndef AT91SAM3S_H

	#define ID_SUPC   ( 0) /**< \brief Supply Controller (SUPC) */
	#define ID_RSTC   ( 1) /**< \brief Reset Controller (RSTC) */
	#define ID_RTC    ( 2) /**< \brief Real Time Clock (RTC) */
	#define ID_RTT    ( 3) /**< \brief Real Time Timer (RTT) */
	#define ID_WDT    ( 4) /**< \brief Watchdog Timer (WDT) */
	#define ID_PMC    ( 5) /**< \brief Power Management Controller (PMC) */
	#define ID_EFC    ( 6) /**< \brief Enhanced Embedded Flash Controller (EFC) */
	#define ID_UART0  ( 8) /**< \brief UART 0 (UART0) */
	#define ID_UART1  ( 9) /**< \brief UART 1 (UART1) */
	#define ID_SMC    (10) /**< \brief Static Memory Controller (SMC) */
	#define ID_PIOA   (11) /**< \brief Parallel I/O Controller A (PIOA) */
	#define ID_PIOB   (12) /**< \brief Parallel I/O Controller B (PIOB) */
	#define ID_PIOC   (13) /**< \brief Parallel I/O Controller C (PIOC) */
	#define ID_USART0 (14) /**< \brief USART 0 (USART0) */
	#define ID_USART1 (15) /**< \brief USART 1 (USART1) */
	#define ID_HSMCI  (18) /**< \brief Multimedia Card Interface (HSMCI) */
	#define ID_TWI0   (19) /**< \brief Two Wire Interface 0 (TWI0) */
	#define ID_TWI1   (20) /**< \brief Two Wire Interface 1 (TWI1) */
	#define ID_SPI    (21) /**< \brief Serial Peripheral Interface (SPI) */
	#define ID_SSC    (22) /**< \brief Synchronous Serial Controler (SSC) */
	#define ID_TC0    (23) /**< \brief Timer/Counter 0 (TC0) */
	#define ID_TC1    (24) /**< \brief Timer/Counter 1 (TC1) */
	#define ID_TC2    (25) /**< \brief Timer/Counter 2 (TC2) */
	#define ID_TC3    (26) /**< \brief Timer/Counter 3 (TC3) */
	#define ID_TC4    (27) /**< \brief Timer/Counter 4 (TC4) */
	#define ID_TC5    (28) /**< \brief Timer/Counter 5 (TC5) */
	#define ID_ADC    (29) /**< \brief Analog To Digital Converter (ADC) */
	#define ID_DACC   (30) /**< \brief Digital To Analog Converter (DACC) */
	#define ID_PWM    (31) /**< \brief Pulse Width Modulation (PWM) */
	#define ID_CRCCU  (32) /**< \brief CRC Calculation Unit (CRCCU) */
	#define ID_ACC    (33) /**< \brief Analog Comparator (ACC) */
	#define ID_UDP    (34) /**< \brief USB Device Port (UDP) */


	// -----------------------------------------------------------------------------
	//  CLK
	// -----------------------------------------------------------------------------
	#define PMC_SCER   (*(volatile uint32_t*)0x400E0400U) /**< \brief (PMC) System Clock Enable Register */
	#define PMC_SCDR   (*(volatile uint32_t*)0x400E0404U) /**< \brief (PMC) System Clock Disable Register */
	#define PMC_SCSR   (*(volatile uint32_t*)0x400E0408U) /**< \brief (PMC) System Clock Status Register */
	#define PMC_PCER0  (*(volatile uint32_t*)0x400E0410U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
	#define PMC_PCDR0  (*(volatile uint32_t*)0x400E0414U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */
	#define PMC_PCSR0  (*(volatile uint32_t*)0x400E0418U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
	#define CKGR_MOR   (*(volatile uint32_t*)0x400E0420U) /**< \brief (PMC) Main Oscillator Register */
	#define CKGR_MCFR  (*(volatile uint32_t*)0x400E0424U) /**< \brief (PMC) Main Clock Frequency Register */
	#define CKGR_PLLAR (*(volatile uint32_t*)0x400E0428U) /**< \brief (PMC) PLLA Register */
	#define CKGR_PLLBR (*(volatile uint32_t*)0x400E042CU) /**< \brief (PMC) PLLB Register */
	#define PMC_MCKR   (*(volatile uint32_t*)0x400E0430U) /**< \brief (PMC) Master Clock Register */
	#define PMC_USB    (*(volatile uint32_t*)0x400E0438U) /**< \brief (PMC) USB Clock Register */

	#define PMC_IER    (*(volatile uint32_t*)0x400E0460U) /**< \brief (PMC) Interrupt Enable Register */
	#define PMC_IDR    (*(volatile uint32_t*)0x400E0464U) /**< \brief (PMC) Interrupt Disable Register */
	#define PMC_SR     (*(volatile uint32_t*)0x400E0468U) /**< \brief (PMC) Status Register */
	#define PMC_IMR    (*(volatile uint32_t*)0x400E046CU) /**< \brief (PMC) Interrupt Mask Register */
	#define PMC_FSMR   (*(volatile uint32_t*)0x400E0470U) /**< \brief (PMC) Fast Startup Mode Register */
	#define PMC_FSPR   (*(volatile uint32_t*)0x400E0474U) /**< \brief (PMC) Fast Startup Polarity Register */
	#define PMC_FOCR   (*(volatile uint32_t*)0x400E0478U) /**< \brief (PMC) Fault Output Clear Register */
	#define PMC_WPMR   (*(volatile uint32_t*)0x400E04E4U) /**< \brief (PMC) Write Protect Mode Register */
	#define PMC_WPSR   (*(volatile uint32_t*)0x400E04E8U) /**< \brief (PMC) Write Protect Status Register */
	#define PMC_PCER1  (*(volatile uint32_t*)0x400E0500U) /**< \brief (PMC) Peripheral Clock Enable Register 1 */
	#define PMC_PCDR1  (*(volatile uint32_t*)0x400E0504U) /**< \brief (PMC) Peripheral Clock Disable Register 1 */
	#define PMC_PCSR1  (*(volatile uint32_t*)0x400E0508U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
	#define PMC_OCR    (*(volatile uint32_t*)0x400E0510U) /**< \brief (PMC) Oscillator Calibration Register */
	#define EEFC        (*(volatile uint32_t*)0x400E0A00U) /**< \brief (EFC) Enhanced Embedded Flash Controller */

	#define EEFC_FMR_FWS_Pos 8
	#define EEFC_FMR_FWS_Msk (0xfu << EEFC_FMR_FWS_Pos) /**< \brief (EEFC_FMR) Flash Wait State */
	#define EEFC_FMR_FWS(value) ((EEFC_FMR_FWS_Msk & ((value) << EEFC_FMR_FWS_Pos)))

	/* -------- PMC_SCER : (PMC Offset: 0x0000) System Clock Enable Register -------- */
	#define PMC_SCER_UDP (0x1u << 7) /**< \brief (PMC_SCER) USB Device Port Clock Enable */
	#define PMC_SCER_PCK0 (0x1u << 8) /**< \brief (PMC_SCER) Programmable Clock 0 Output Enable */
	#define PMC_SCER_PCK1 (0x1u << 9) /**< \brief (PMC_SCER) Programmable Clock 1 Output Enable */
	#define PMC_SCER_PCK2 (0x1u << 10) /**< \brief (PMC_SCER) Programmable Clock 2 Output Enable */

	/* -------- PMC_SCDR : (PMC Offset: 0x0004) System Clock Disable Register -------- */
	#define PMC_SCDR_UDP (0x1u << 7) /**< \brief (PMC_SCDR) USB Device Port Clock Disable */


	/* -------- PMC_SCSR : (PMC Offset: 0x0008) System Clock Status Register -------- */
	#define PMC_SCSR_UDP (0x1u << 7) /**< \brief (PMC_SCSR) USB Device Port Clock Status */
	#define PMC_SCSR_PCK0 (0x1u << 8) /**< \brief (PMC_SCSR) Programmable Clock 0 Output Status */
	#define PMC_SCSR_PCK1 (0x1u << 9) /**< \brief (PMC_SCSR) Programmable Clock 1 Output Status */
	#define PMC_SCSR_PCK2 (0x1u << 10) /**< \brief (PMC_SCSR) Programmable Clock 2 Output Status */

	/* -------- PMC_PCER0 : (PMC Offset: 0x0010) Peripheral Clock Enable Register 0 -------- */
	#define PMC_PCER0_PID2 (0x1u << 2) /**< \brief (PMC_PCER0) Peripheral Clock 2 Enable */
	#define PMC_PCER0_PID3 (0x1u << 3) /**< \brief (PMC_PCER0) Peripheral Clock 3 Enable */
	#define PMC_PCER0_PID4 (0x1u << 4) /**< \brief (PMC_PCER0) Peripheral Clock 4 Enable */
	#define PMC_PCER0_PID5 (0x1u << 5) /**< \brief (PMC_PCER0) Peripheral Clock 5 Enable */
	#define PMC_PCER0_PID6 (0x1u << 6) /**< \brief (PMC_PCER0) Peripheral Clock 6 Enable */
	#define PMC_PCER0_PID7 (0x1u << 7) /**< \brief (PMC_PCER0) Peripheral Clock 7 Enable */
	#define PMC_PCER0_PID8 (0x1u << 8) /**< \brief (PMC_PCER0) Peripheral Clock 8 Enable */
	#define PMC_PCER0_PID9 (0x1u << 9) /**< \brief (PMC_PCER0) Peripheral Clock 9 Enable */
	#define PMC_PCER0_PID10 (0x1u << 10) /**< \brief (PMC_PCER0) Peripheral Clock 10 Enable */
	#define PMC_PCER0_PID11 (0x1u << 11) /**< \brief (PMC_PCER0) Peripheral Clock 11 Enable */
	#define PMC_PCER0_PID12 (0x1u << 12) /**< \brief (PMC_PCER0) Peripheral Clock 12 Enable */
	#define PMC_PCER0_PID13 (0x1u << 13) /**< \brief (PMC_PCER0) Peripheral Clock 13 Enable */
	#define PMC_PCER0_PID14 (0x1u << 14) /**< \brief (PMC_PCER0) Peripheral Clock 14 Enable */
	#define PMC_PCER0_PID15 (0x1u << 15) /**< \brief (PMC_PCER0) Peripheral Clock 15 Enable */
	#define PMC_PCER0_PID18 (0x1u << 18) /**< \brief (PMC_PCER0) Peripheral Clock 18 Enable */
	#define PMC_PCER0_PID19 (0x1u << 19) /**< \brief (PMC_PCER0) Peripheral Clock 19 Enable */
	#define PMC_PCER0_PID20 (0x1u << 20) /**< \brief (PMC_PCER0) Peripheral Clock 20 Enable */
	#define PMC_PCER0_PID21 (0x1u << 21) /**< \brief (PMC_PCER0) Peripheral Clock 21 Enable */
	#define PMC_PCER0_PID22 (0x1u << 22) /**< \brief (PMC_PCER0) Peripheral Clock 22 Enable */
	#define PMC_PCER0_PID23 (0x1u << 23) /**< \brief (PMC_PCER0) Peripheral Clock 23 Enable */
	#define PMC_PCER0_PID24 (0x1u << 24) /**< \brief (PMC_PCER0) Peripheral Clock 24 Enable */
	#define PMC_PCER0_PID25 (0x1u << 25) /**< \brief (PMC_PCER0) Peripheral Clock 25 Enable */
	#define PMC_PCER0_PID26 (0x1u << 26) /**< \brief (PMC_PCER0) Peripheral Clock 26 Enable */
	#define PMC_PCER0_PID27 (0x1u << 27) /**< \brief (PMC_PCER0) Peripheral Clock 27 Enable */
	#define PMC_PCER0_PID28 (0x1u << 28) /**< \brief (PMC_PCER0) Peripheral Clock 28 Enable */
	#define PMC_PCER0_PID29 (0x1u << 29) /**< \brief (PMC_PCER0) Peripheral Clock 29 Enable */
	#define PMC_PCER0_PID30 (0x1u << 30) /**< \brief (PMC_PCER0) Peripheral Clock 30 Enable */
	#define PMC_PCER0_PID31 (0x1u << 31) /**< \brief (PMC_PCER0) Peripheral Clock 31 Enable */

	/* -------- PMC_PCDR0 : (PMC Offset: 0x0014) Peripheral Clock Disable Register 0 -------- */
	#define PMC_PCDR0_PID2 (0x1u << 2) /**< \brief (PMC_PCDR0) Peripheral Clock 2 Disable */
	#define PMC_PCDR0_PID3 (0x1u << 3) /**< \brief (PMC_PCDR0) Peripheral Clock 3 Disable */
	#define PMC_PCDR0_PID4 (0x1u << 4) /**< \brief (PMC_PCDR0) Peripheral Clock 4 Disable */
	#define PMC_PCDR0_PID5 (0x1u << 5) /**< \brief (PMC_PCDR0) Peripheral Clock 5 Disable */
	#define PMC_PCDR0_PID6 (0x1u << 6) /**< \brief (PMC_PCDR0) Peripheral Clock 6 Disable */
	#define PMC_PCDR0_PID7 (0x1u << 7) /**< \brief (PMC_PCDR0) Peripheral Clock 7 Disable */
	#define PMC_PCDR0_PID8 (0x1u << 8) /**< \brief (PMC_PCDR0) Peripheral Clock 8 Disable */
	#define PMC_PCDR0_PID9 (0x1u << 9) /**< \brief (PMC_PCDR0) Peripheral Clock 9 Disable */
	#define PMC_PCDR0_PID10 (0x1u << 10) /**< \brief (PMC_PCDR0) Peripheral Clock 10 Disable */
	#define PMC_PCDR0_PID11 (0x1u << 11) /**< \brief (PMC_PCDR0) Peripheral Clock 11 Disable */
	#define PMC_PCDR0_PID12 (0x1u << 12) /**< \brief (PMC_PCDR0) Peripheral Clock 12 Disable */
	#define PMC_PCDR0_PID13 (0x1u << 13) /**< \brief (PMC_PCDR0) Peripheral Clock 13 Disable */
	#define PMC_PCDR0_PID14 (0x1u << 14) /**< \brief (PMC_PCDR0) Peripheral Clock 14 Disable */
	#define PMC_PCDR0_PID15 (0x1u << 15) /**< \brief (PMC_PCDR0) Peripheral Clock 15 Disable */
	#define PMC_PCDR0_PID18 (0x1u << 18) /**< \brief (PMC_PCDR0) Peripheral Clock 18 Disable */
	#define PMC_PCDR0_PID19 (0x1u << 19) /**< \brief (PMC_PCDR0) Peripheral Clock 19 Disable */
	#define PMC_PCDR0_PID20 (0x1u << 20) /**< \brief (PMC_PCDR0) Peripheral Clock 20 Disable */
	#define PMC_PCDR0_PID21 (0x1u << 21) /**< \brief (PMC_PCDR0) Peripheral Clock 21 Disable */
	#define PMC_PCDR0_PID22 (0x1u << 22) /**< \brief (PMC_PCDR0) Peripheral Clock 22 Disable */
	#define PMC_PCDR0_PID23 (0x1u << 23) /**< \brief (PMC_PCDR0) Peripheral Clock 23 Disable */
	#define PMC_PCDR0_PID24 (0x1u << 24) /**< \brief (PMC_PCDR0) Peripheral Clock 24 Disable */
	#define PMC_PCDR0_PID25 (0x1u << 25) /**< \brief (PMC_PCDR0) Peripheral Clock 25 Disable */
	#define PMC_PCDR0_PID26 (0x1u << 26) /**< \brief (PMC_PCDR0) Peripheral Clock 26 Disable */
	#define PMC_PCDR0_PID27 (0x1u << 27) /**< \brief (PMC_PCDR0) Peripheral Clock 27 Disable */
	#define PMC_PCDR0_PID28 (0x1u << 28) /**< \brief (PMC_PCDR0) Peripheral Clock 28 Disable */
	#define PMC_PCDR0_PID29 (0x1u << 29) /**< \brief (PMC_PCDR0) Peripheral Clock 29 Disable */
	#define PMC_PCDR0_PID30 (0x1u << 30) /**< \brief (PMC_PCDR0) Peripheral Clock 30 Disable */
	#define PMC_PCDR0_PID31 (0x1u << 31) /**< \brief (PMC_PCDR0) Peripheral Clock 31 Disable */

	/* -------- PMC_PCSR0 : (PMC Offset: 0x0018) Peripheral Clock Status Register 0 -------- */
	#define PMC_PCSR0_PID2 (0x1u << 2) /**< \brief (PMC_PCSR0) Peripheral Clock 2 Status */
	#define PMC_PCSR0_PID3 (0x1u << 3) /**< \brief (PMC_PCSR0) Peripheral Clock 3 Status */
	#define PMC_PCSR0_PID4 (0x1u << 4) /**< \brief (PMC_PCSR0) Peripheral Clock 4 Status */
	#define PMC_PCSR0_PID5 (0x1u << 5) /**< \brief (PMC_PCSR0) Peripheral Clock 5 Status */
	#define PMC_PCSR0_PID6 (0x1u << 6) /**< \brief (PMC_PCSR0) Peripheral Clock 6 Status */
	#define PMC_PCSR0_PID7 (0x1u << 7) /**< \brief (PMC_PCSR0) Peripheral Clock 7 Status */
	#define PMC_PCSR0_PID8 (0x1u << 8) /**< \brief (PMC_PCSR0) Peripheral Clock 8 Status */
	#define PMC_PCSR0_PID9 (0x1u << 9) /**< \brief (PMC_PCSR0) Peripheral Clock 9 Status */
	#define PMC_PCSR0_PID10 (0x1u << 10) /**< \brief (PMC_PCSR0) Peripheral Clock 10 Status */
	#define PMC_PCSR0_PID11 (0x1u << 11) /**< \brief (PMC_PCSR0) Peripheral Clock 11 Status */
	#define PMC_PCSR0_PID12 (0x1u << 12) /**< \brief (PMC_PCSR0) Peripheral Clock 12 Status */
	#define PMC_PCSR0_PID13 (0x1u << 13) /**< \brief (PMC_PCSR0) Peripheral Clock 13 Status */
	#define PMC_PCSR0_PID14 (0x1u << 14) /**< \brief (PMC_PCSR0) Peripheral Clock 14 Status */
	#define PMC_PCSR0_PID15 (0x1u << 15) /**< \brief (PMC_PCSR0) Peripheral Clock 15 Status */
	#define PMC_PCSR0_PID18 (0x1u << 18) /**< \brief (PMC_PCSR0) Peripheral Clock 18 Status */
	#define PMC_PCSR0_PID19 (0x1u << 19) /**< \brief (PMC_PCSR0) Peripheral Clock 19 Status */
	#define PMC_PCSR0_PID20 (0x1u << 20) /**< \brief (PMC_PCSR0) Peripheral Clock 20 Status */
	#define PMC_PCSR0_PID21 (0x1u << 21) /**< \brief (PMC_PCSR0) Peripheral Clock 21 Status */
	#define PMC_PCSR0_PID22 (0x1u << 22) /**< \brief (PMC_PCSR0) Peripheral Clock 22 Status */
	#define PMC_PCSR0_PID23 (0x1u << 23) /**< \brief (PMC_PCSR0) Peripheral Clock 23 Status */
	#define PMC_PCSR0_PID24 (0x1u << 24) /**< \brief (PMC_PCSR0) Peripheral Clock 24 Status */
	#define PMC_PCSR0_PID25 (0x1u << 25) /**< \brief (PMC_PCSR0) Peripheral Clock 25 Status */
	#define PMC_PCSR0_PID26 (0x1u << 26) /**< \brief (PMC_PCSR0) Peripheral Clock 26 Status */
	#define PMC_PCSR0_PID27 (0x1u << 27) /**< \brief (PMC_PCSR0) Peripheral Clock 27 Status */
	#define PMC_PCSR0_PID28 (0x1u << 28) /**< \brief (PMC_PCSR0) Peripheral Clock 28 Status */
	#define PMC_PCSR0_PID29 (0x1u << 29) /**< \brief (PMC_PCSR0) Peripheral Clock 29 Status */
	#define PMC_PCSR0_PID30 (0x1u << 30) /**< \brief (PMC_PCSR0) Peripheral Clock 30 Status */
	#define PMC_PCSR0_PID31 (0x1u << 31) /**< \brief (PMC_PCSR0) Peripheral Clock 31 Status */

	/* -------- CKGR_MOR : (PMC Offset: 0x0020) Main Oscillator Register -------- */
	#define CKGR_MOR_MOSCXTEN (0x1u << 0) /**< \brief (CKGR_MOR) Main Crystal Oscillator Enable */
	#define CKGR_MOR_MOSCXTBY (0x1u << 1) /**< \brief (CKGR_MOR) Main Crystal Oscillator Bypass */
	#define CKGR_MOR_MOSCRCEN (0x1u << 3) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Enable */
	#define CKGR_MOR_MOSCRCF_Pos 4
	#define CKGR_MOR_MOSCRCF_Msk (0x7u << CKGR_MOR_MOSCRCF_Pos) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Frequency Selection */
	#define   CKGR_MOR_MOSCRCF_4_MHz (0x0u << 4) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 4 MHz (default) */
	#define   CKGR_MOR_MOSCRCF_8_MHz (0x1u << 4) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 8 MHz */
	#define   CKGR_MOR_MOSCRCF_12_MHz (0x2u << 4) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 12 MHz */
	#define CKGR_MOR_MOSCXTST_Pos 8
	#define CKGR_MOR_MOSCXTST_Msk (0xffu << CKGR_MOR_MOSCXTST_Pos) /**< \brief (CKGR_MOR) Main Crystal Oscillator Start-up Time */
	#define CKGR_MOR_MOSCXTST(value) ((CKGR_MOR_MOSCXTST_Msk & ((value) << CKGR_MOR_MOSCXTST_Pos)))
	#define CKGR_MOR_KEY (0x37u << 16)
	#define CKGR_MOR_MOSCSEL (0x1u << 24) /**< \brief (CKGR_MOR) Main Oscillator Selection */
	#define CKGR_MOR_CFDEN (0x1u << 25) /**< \brief (CKGR_MOR) Clock Failure Detector Enable */

	/* -------- CKGR_MCFR : (PMC Offset: 0x0024) Main Clock Frequency Register -------- */
	#define CKGR_MCFR_MAINF_Pos 0
	#define CKGR_MCFR_MAINF_Msk (0xffffu << CKGR_MCFR_MAINF_Pos) /**< \brief (CKGR_MCFR) Main Clock Frequency */
	#define CKGR_MCFR_MAINFRDY (0x1u << 16) /**< \brief (CKGR_MCFR) Main Clock Ready */

	/* -------- CKGR_PLLAR : (PMC Offset: 0x0028) PLLA Register -------- */
	#define CKGR_PLLAR_DIVA_Pos 0
	#define CKGR_PLLAR_DIVA_Msk (0xffu << CKGR_PLLAR_DIVA_Pos) /**< \brief (CKGR_PLLAR) Divider */
	#define CKGR_PLLAR_DIVA(value) ((CKGR_PLLAR_DIVA_Msk & ((value) << CKGR_PLLAR_DIVA_Pos)))
	#define CKGR_PLLAR_PLLACOUNT_Pos 8
	#define CKGR_PLLAR_PLLACOUNT_Msk (0x3fu << CKGR_PLLAR_PLLACOUNT_Pos) /**< \brief (CKGR_PLLAR) PLLA Counter */
	#define CKGR_PLLAR_PLLACOUNT(value) ((CKGR_PLLAR_PLLACOUNT_Msk & ((value) << CKGR_PLLAR_PLLACOUNT_Pos)))
	#define CKGR_PLLAR_MULA_Pos 16
	#define CKGR_PLLAR_MULA_Msk (0x7ffu << CKGR_PLLAR_MULA_Pos) /**< \brief (CKGR_PLLAR) PLLA Multiplier */
	#define CKGR_PLLAR_MULA(value) ((CKGR_PLLAR_MULA_Msk & ((value) << CKGR_PLLAR_MULA_Pos)))
	#define CKGR_PLLAR_ONE (0x1u << 29) /**< \brief (CKGR_PLLAR) Must Be Set to 1 */

	/* -------- CKGR_PLLBR : (PMC Offset: 0x002C) PLLB Register -------- */
	#define CKGR_PLLBR_DIVB_Pos 0
	#define CKGR_PLLBR_DIVB_Msk (0xffu << CKGR_PLLBR_DIVB_Pos) /**< \brief (CKGR_PLLBR) Divider */
	#define CKGR_PLLBR_DIVB(value) ((CKGR_PLLBR_DIVB_Msk & ((value) << CKGR_PLLBR_DIVB_Pos)))
	#define CKGR_PLLBR_PLLBCOUNT_Pos 8
	#define CKGR_PLLBR_PLLBCOUNT_Msk (0x3fu << CKGR_PLLBR_PLLBCOUNT_Pos) /**< \brief (CKGR_PLLBR) PLLB Counter */
	#define CKGR_PLLBR_PLLBCOUNT(value) ((CKGR_PLLBR_PLLBCOUNT_Msk & ((value) << CKGR_PLLBR_PLLBCOUNT_Pos)))
	#define CKGR_PLLBR_MULB_Pos 16
	#define CKGR_PLLBR_MULB_Msk (0x7ffu << CKGR_PLLBR_MULB_Pos) /**< \brief (CKGR_PLLBR) PLLB Multiplier */
	#define CKGR_PLLBR_MULB(value) ((CKGR_PLLBR_MULB_Msk & ((value) << CKGR_PLLBR_MULB_Pos)))

	/* -------- PMC_MCKR : (PMC Offset: 0x0030) Master Clock Register -------- */
	#define PMC_MCKR_CSS_Pos 0
	#define PMC_MCKR_CSS_Msk (0x3u << PMC_MCKR_CSS_Pos) /**< \brief (PMC_MCKR) Master Clock Source Selection */
	#define   PMC_MCKR_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_MCKR) Slow Clock is selected */
	#define   PMC_MCKR_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_MCKR) Main Clock is selected */
	#define   PMC_MCKR_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_MCKR) PLLA Clock is selected */
	#define   PMC_MCKR_CSS_PLLB_CLK (0x3u << 0) /**< \brief (PMC_MCKR) PLLB Clock is selected */
	#define PMC_MCKR_PRES_Pos 4
	#define PMC_MCKR_PRES_Msk (0x7u << PMC_MCKR_PRES_Pos) /**< \brief (PMC_MCKR) Processor Clock Prescaler */
	#define   PMC_MCKR_PRES_CLK_1 (0x0u << 4) /**< \brief (PMC_MCKR) Selected clock */
	#define   PMC_MCKR_PRES_CLK_2 (0x1u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 2 */
	#define   PMC_MCKR_PRES_CLK_3 (0x7u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 3 */
	#define   PMC_MCKR_PRES_CLK_4 (0x2u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 4 */
	#define   PMC_MCKR_PRES_CLK_8 (0x3u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 8 */
	#define   PMC_MCKR_PRES_CLK_16 (0x4u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 16 */
	#define   PMC_MCKR_PRES_CLK_32 (0x5u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 32 */
	#define   PMC_MCKR_PRES_CLK_64 (0x6u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 64 */
	#define PMC_MCKR_PLLADIV2 (0x1u << 12) /**< \brief (PMC_MCKR) PLLA Divisor by 2 */
	#define PMC_MCKR_PLLBDIV2 (0x1u << 13) /**< \brief (PMC_MCKR) PLLB Divisor by 2 */

	/* -------- PMC_USB : (PMC Offset: 0x0038) USB Clock Register -------- */
	#define PMC_USB_USBS (0x1u << 0) /**< \brief (PMC_USB) USB Input Clock Selection */
	#define PMC_USB_USBDIV_Pos 8
	#define PMC_USB_USBDIV_Msk (0xfu << PMC_USB_USBDIV_Pos) /**< \brief (PMC_USB) Divider for USB Clock. */
	#define PMC_USB_USBDIV(value) ((PMC_USB_USBDIV_Msk & ((value) << PMC_USB_USBDIV_Pos)))

	/* -------- PMC_PCK[3] : (PMC Offset: 0x0040) Programmable Clock 0 Register -------- */
	#define PMC_PCK_CSS_Pos 0
	#define PMC_PCK_CSS_Msk (0x7u << PMC_PCK_CSS_Pos) /**< \brief (PMC_PCK[3]) Master Clock Source Selection */
	#define   PMC_PCK_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_PCK[3]) Slow Clock is selected */
	#define   PMC_PCK_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_PCK[3]) Main Clock is selected */
	#define   PMC_PCK_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_PCK[3]) PLLA Clock is selected */
	#define   PMC_PCK_CSS_PLLB_CLK (0x3u << 0) /**< \brief (PMC_PCK[3]) PLLB Clock is selected */
	#define   PMC_PCK_CSS_MCK (0x4u << 0) /**< \brief (PMC_PCK[3]) Master Clock is selected */
	#define PMC_PCK_PRES_Pos 4
	#define PMC_PCK_PRES_Msk (0x7u << PMC_PCK_PRES_Pos) /**< \brief (PMC_PCK[3]) Programmable Clock Prescaler */
	#define   PMC_PCK_PRES_CLK_1 (0x0u << 4) /**< \brief (PMC_PCK[3]) Selected clock */
	#define   PMC_PCK_PRES_CLK_2 (0x1u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 2 */
	#define   PMC_PCK_PRES_CLK_4 (0x2u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 4 */
	#define   PMC_PCK_PRES_CLK_8 (0x3u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 8 */
	#define   PMC_PCK_PRES_CLK_16 (0x4u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 16 */
	#define   PMC_PCK_PRES_CLK_32 (0x5u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 32 */
	#define   PMC_PCK_PRES_CLK_64 (0x6u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 64 */

	/* -------- PMC_IER : (PMC Offset: 0x0060) Interrupt Enable Register -------- */
	#define PMC_IER_MOSCXTS (0x1u << 0) /**< \brief (PMC_IER) Main Crystal Oscillator Status Interrupt Enable */
	#define PMC_IER_LOCKA (0x1u << 1) /**< \brief (PMC_IER) PLLA Lock Interrupt Enable */
	#define PMC_IER_LOCKB (0x1u << 2) /**< \brief (PMC_IER) PLLB Lock Interrupt Enable */
	#define PMC_IER_MCKRDY (0x1u << 3) /**< \brief (PMC_IER) Master Clock Ready Interrupt Enable */
	#define PMC_IER_PCKRDY0 (0x1u << 8) /**< \brief (PMC_IER) Programmable Clock Ready 0 Interrupt Enable */
	#define PMC_IER_PCKRDY1 (0x1u << 9) /**< \brief (PMC_IER) Programmable Clock Ready 1 Interrupt Enable */
	#define PMC_IER_PCKRDY2 (0x1u << 10) /**< \brief (PMC_IER) Programmable Clock Ready 2 Interrupt Enable */
	#define PMC_IER_MOSCSELS (0x1u << 16) /**< \brief (PMC_IER) Main Oscillator Selection Status Interrupt Enable */
	#define PMC_IER_MOSCRCS (0x1u << 17) /**< \brief (PMC_IER) Main On-Chip RC Status Interrupt Enable */
	#define PMC_IER_CFDEV (0x1u << 18) /**< \brief (PMC_IER) Clock Failure Detector Event Interrupt Enable */

	/* -------- PMC_IDR : (PMC Offset: 0x0064) Interrupt Disable Register -------- */
	#define PMC_IDR_MOSCXTS (0x1u << 0) /**< \brief (PMC_IDR) Main Crystal Oscillator Status Interrupt Disable */
	#define PMC_IDR_LOCKA (0x1u << 1) /**< \brief (PMC_IDR) PLLA Lock Interrupt Disable */
	#define PMC_IDR_LOCKB (0x1u << 2) /**< \brief (PMC_IDR) PLLB Lock Interrupt Disable */
	#define PMC_IDR_MCKRDY (0x1u << 3) /**< \brief (PMC_IDR) Master Clock Ready Interrupt Disable */
	#define PMC_IDR_PCKRDY0 (0x1u << 8) /**< \brief (PMC_IDR) Programmable Clock Ready 0 Interrupt Disable */
	#define PMC_IDR_PCKRDY1 (0x1u << 9) /**< \brief (PMC_IDR) Programmable Clock Ready 1 Interrupt Disable */
	#define PMC_IDR_PCKRDY2 (0x1u << 10) /**< \brief (PMC_IDR) Programmable Clock Ready 2 Interrupt Disable */
	#define PMC_IDR_MOSCSELS (0x1u << 16) /**< \brief (PMC_IDR) Main Oscillator Selection Status Interrupt Disable */
	#define PMC_IDR_MOSCRCS (0x1u << 17) /**< \brief (PMC_IDR) Main On-Chip RC Status Interrupt Disable */
	#define PMC_IDR_CFDEV (0x1u << 18) /**< \brief (PMC_IDR) Clock Failure Detector Event Interrupt Disable */

	/* -------- PMC_SR : (PMC Offset: 0x0068) Status Register -------- */
	#define PMC_SR_MOSCXTS (0x1u << 0) /**< \brief (PMC_SR) Main XTAL Oscillator Status */
	#define PMC_SR_LOCKA (0x1u << 1) /**< \brief (PMC_SR) PLLA Lock Status */
	#define PMC_SR_LOCKB (0x1u << 2) /**< \brief (PMC_SR) PLLB Lock Status */
	#define PMC_SR_MCKRDY (0x1u << 3) /**< \brief (PMC_SR) Master Clock Status */
	#define PMC_SR_OSCSELS (0x1u << 7) /**< \brief (PMC_SR) Slow Clock Oscillator Selection */
	#define PMC_SR_MOSCSELS (0x1u << 16) /**< \brief (PMC_SR) Main Oscillator Selection Status */
	#define PMC_SR_MOSCRCS (0x1u << 17) /**< \brief (PMC_SR) Main On-Chip RC Oscillator Status */
	#define PMC_SR_CFDEV (0x1u << 18) /**< \brief (PMC_SR) Clock Failure Detector Event */
	#define PMC_SR_CFDS (0x1u << 19) /**< \brief (PMC_SR) Clock Failure Detector Status */
	#define PMC_SR_FOS (0x1u << 20) /**< \brief (PMC_SR) Clock Failure Detector Fault Output Status */

	/* -------- PMC_IMR : (PMC Offset: 0x006C) Interrupt Mask Register -------- */
	#define PMC_IMR_MOSCXTS (0x1u << 0) /**< \brief (PMC_IMR) Main Crystal Oscillator Status Interrupt Mask */
	#define PMC_IMR_LOCKA (0x1u << 1) /**< \brief (PMC_IMR) PLLA Lock Interrupt Mask */
	#define PMC_IMR_LOCKB (0x1u << 2) /**< \brief (PMC_IMR) PLLB Lock Interrupt Mask */
	#define PMC_IMR_MCKRDY (0x1u << 3) /**< \brief (PMC_IMR) Master Clock Ready Interrupt Mask */
	#define PMC_IMR_PCKRDY0 (0x1u << 8) /**< \brief (PMC_IMR) Programmable Clock Ready 0 Interrupt Mask */
	#define PMC_IMR_PCKRDY1 (0x1u << 9) /**< \brief (PMC_IMR) Programmable Clock Ready 1 Interrupt Mask */
	#define PMC_IMR_PCKRDY2 (0x1u << 10) /**< \brief (PMC_IMR) Programmable Clock Ready 2 Interrupt Mask */
	#define PMC_IMR_MOSCSELS (0x1u << 16) /**< \brief (PMC_IMR) Main Oscillator Selection Status Interrupt Mask */
	#define PMC_IMR_MOSCRCS (0x1u << 17) /**< \brief (PMC_IMR) Main On-Chip RC Status Interrupt Mask */
	#define PMC_IMR_CFDEV (0x1u << 18) /**< \brief (PMC_IMR) Clock Failure Detector Event Interrupt Mask */

	/* -------- PMC_FSMR : (PMC Offset: 0x0070) Fast Startup Mode Register -------- */
	#define PMC_FSMR_FSTT0 (0x1u << 0) /**< \brief (PMC_FSMR) Fast Startup Input Enable 0 */
	#define PMC_FSMR_FSTT1 (0x1u << 1) /**< \brief (PMC_FSMR) Fast Startup Input Enable 1 */
	#define PMC_FSMR_FSTT2 (0x1u << 2) /**< \brief (PMC_FSMR) Fast Startup Input Enable 2 */
	#define PMC_FSMR_FSTT3 (0x1u << 3) /**< \brief (PMC_FSMR) Fast Startup Input Enable 3 */
	#define PMC_FSMR_FSTT4 (0x1u << 4) /**< \brief (PMC_FSMR) Fast Startup Input Enable 4 */
	#define PMC_FSMR_FSTT5 (0x1u << 5) /**< \brief (PMC_FSMR) Fast Startup Input Enable 5 */
	#define PMC_FSMR_FSTT6 (0x1u << 6) /**< \brief (PMC_FSMR) Fast Startup Input Enable 6 */
	#define PMC_FSMR_FSTT7 (0x1u << 7) /**< \brief (PMC_FSMR) Fast Startup Input Enable 7 */
	#define PMC_FSMR_FSTT8 (0x1u << 8) /**< \brief (PMC_FSMR) Fast Startup Input Enable 8 */
	#define PMC_FSMR_FSTT9 (0x1u << 9) /**< \brief (PMC_FSMR) Fast Startup Input Enable 9 */
	#define PMC_FSMR_FSTT10 (0x1u << 10) /**< \brief (PMC_FSMR) Fast Startup Input Enable 10 */
	#define PMC_FSMR_FSTT11 (0x1u << 11) /**< \brief (PMC_FSMR) Fast Startup Input Enable 11 */
	#define PMC_FSMR_FSTT12 (0x1u << 12) /**< \brief (PMC_FSMR) Fast Startup Input Enable 12 */
	#define PMC_FSMR_FSTT13 (0x1u << 13) /**< \brief (PMC_FSMR) Fast Startup Input Enable 13 */
	#define PMC_FSMR_FSTT14 (0x1u << 14) /**< \brief (PMC_FSMR) Fast Startup Input Enable 14 */
	#define PMC_FSMR_FSTT15 (0x1u << 15) /**< \brief (PMC_FSMR) Fast Startup Input Enable 15 */
	#define PMC_FSMR_RTTAL (0x1u << 16) /**< \brief (PMC_FSMR) RTT Alarm Enable */
	#define PMC_FSMR_RTCAL (0x1u << 17) /**< \brief (PMC_FSMR) RTC Alarm Enable */
	#define PMC_FSMR_USBAL (0x1u << 18) /**< \brief (PMC_FSMR) USB Alarm Enable */
	#define PMC_FSMR_LPM (0x1u << 20) /**< \brief (PMC_FSMR) Low Power Mode */

	/* -------- PMC_FSPR : (PMC Offset: 0x0074) Fast Startup Polarity Register -------- */
	#define PMC_FSPR_FSTP0 (0x1u << 0) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP1 (0x1u << 1) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP2 (0x1u << 2) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP3 (0x1u << 3) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP4 (0x1u << 4) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP5 (0x1u << 5) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP6 (0x1u << 6) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP7 (0x1u << 7) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP8 (0x1u << 8) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP9 (0x1u << 9) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP10 (0x1u << 10) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP11 (0x1u << 11) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP12 (0x1u << 12) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP13 (0x1u << 13) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP14 (0x1u << 14) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */
	#define PMC_FSPR_FSTP15 (0x1u << 15) /**< \brief (PMC_FSPR) Fast Startup Input Polarityx */

	/* -------- PMC_FOCR : (PMC Offset: 0x0078) Fault Output Clear Register -------- */
	#define PMC_FOCR_FOCLR (0x1u << 0) /**< \brief (PMC_FOCR) Fault Output Clear */

	/* -------- PMC_WPMR : (PMC Offset: 0x00E4) Write Protect Mode Register -------- */
	#define PMC_WPMR_WPEN (0x1u << 0) /**< \brief (PMC_WPMR) Write Protect Enable */
	#define PMC_WPMR_WPKEY_Pos 8
	#define PMC_WPMR_WPKEY_Msk (0xffffffu << PMC_WPMR_WPKEY_Pos) /**< \brief (PMC_WPMR) Write Protect KEY */
	#define PMC_WPMR_WPKEY(value) ((PMC_WPMR_WPKEY_Msk & ((value) << PMC_WPMR_WPKEY_Pos)))

	/* -------- PMC_WPSR : (PMC Offset: 0x00E8) Write Protect Status Register -------- */
	#define PMC_WPSR_WPVS (0x1u << 0) /**< \brief (PMC_WPSR) Write Protect Violation Status */
	#define PMC_WPSR_WPVSRC_Pos 8
	#define PMC_WPSR_WPVSRC_Msk (0xffffu << PMC_WPSR_WPVSRC_Pos) /**< \brief (PMC_WPSR) Write Protect Violation Source */

	/* -------- PMC_PCER1 : (PMC Offset: 0x0100) Peripheral Clock Enable Register 1 -------- */
	#define PMC_PCER1_PID32 (0x1u << 0) /**< \brief (PMC_PCER1) Peripheral Clock 32 Enable */
	#define PMC_PCER1_PID33 (0x1u << 1) /**< \brief (PMC_PCER1) Peripheral Clock 33 Enable */
	#define PMC_PCER1_PID34 (0x1u << 2) /**< \brief (PMC_PCER1) Peripheral Clock 34 Enable */

	/* -------- PMC_PCDR1 : (PMC Offset: 0x0104) Peripheral Clock Disable Register 1 -------- */
	#define PMC_PCDR1_PID32 (0x1u << 0) /**< \brief (PMC_PCDR1) Peripheral Clock 32 Disable */
	#define PMC_PCDR1_PID33 (0x1u << 1) /**< \brief (PMC_PCDR1) Peripheral Clock 33 Disable */
	#define PMC_PCDR1_PID34 (0x1u << 2) /**< \brief (PMC_PCDR1) Peripheral Clock 34 Disable */

	/* -------- PMC_PCSR1 : (PMC Offset: 0x0108) Peripheral Clock Status Register 1 -------- */
	#define PMC_PCSR1_PID32 (0x1u << 0) /**< \brief (PMC_PCSR1) Peripheral Clock 32 Status */
	#define PMC_PCSR1_PID33 (0x1u << 1) /**< \brief (PMC_PCSR1) Peripheral Clock 33 Status */
	#define PMC_PCSR1_PID34 (0x1u << 2) /**< \brief (PMC_PCSR1) Peripheral Clock 34 Status */

	/* -------- PMC_OCR : (PMC Offset: 0x0110) Oscillator Calibration Register -------- */
	#define PMC_OCR_CAL4_Pos 0
	#define PMC_OCR_CAL4_Msk (0x7fu << PMC_OCR_CAL4_Pos) /**< \brief (PMC_OCR) RC Oscillator Calibration bits for 4 Mhz */
	#define PMC_OCR_CAL4(value) ((PMC_OCR_CAL4_Msk & ((value) << PMC_OCR_CAL4_Pos)))
	#define PMC_OCR_SEL4 (0x1u << 7) /**< \brief (PMC_OCR) Selection of RC Oscillator Calibration bits for 4 Mhz */
	#define PMC_OCR_CAL8_Pos 8
	#define PMC_OCR_CAL8_Msk (0x7fu << PMC_OCR_CAL8_Pos) /**< \brief (PMC_OCR) RC Oscillator Calibration bits for 8 Mhz */
	#define PMC_OCR_CAL8(value) ((PMC_OCR_CAL8_Msk & ((value) << PMC_OCR_CAL8_Pos)))
	#define PMC_OCR_SEL8 (0x1u << 15) /**< \brief (PMC_OCR) Selection of RC Oscillator Calibration bits for 8 Mhz */
	#define PMC_OCR_CAL12_Pos 16
	#define PMC_OCR_CAL12_Msk (0x7fu << PMC_OCR_CAL12_Pos) /**< \brief (PMC_OCR) RC Oscillator Calibration bits for 12 Mhz */
	#define PMC_OCR_CAL12(value) ((PMC_OCR_CAL12_Msk & ((value) << PMC_OCR_CAL12_Pos)))
	#define PMC_OCR_SEL12 (0x1u << 23) /**< \brief (PMC_OCR) Selection of RC Oscillator Calibration bits for 12 Mhz */

	// -----------------------------------------------------------------------------
	// UART
	// -----------------------------------------------------------------------------
	#define UART0_CR   (*(volatile uint32_t*)0x400E0600U) /**< \brief (UART0) Control Register */
	#define UART0_MR   (*(volatile uint32_t*)0x400E0604U) /**< \brief (UART0) Mode Register */
	#define UART0_IER  (*(volatile uint32_t*)0x400E0608U) /**< \brief (UART0) Interrupt Enable Register */
	#define UART0_IDR  (*(volatile uint32_t*)0x400E060CU) /**< \brief (UART0) Interrupt Disable Register */
	#define UART0_IMR  (*(volatile uint32_t*)0x400E0610U) /**< \brief (UART0) Interrupt Mask Register */
	#define UART0_SR   (*(volatile uint32_t*)0x400E0614U) /**< \brief (UART0) Status Register */
	#define UART0_RHR  (*(volatile uint32_t*)0x400E0618U) /**< \brief (UART0) Receive Holding Register */
	#define UART0_THR  (*(volatile uint32_t*)0x400E061CU) /**< \brief (UART0) Transmit Holding Register */
	#define UART0_BRGR (*(volatile uint32_t*)0x400E0620U) /**< \brief (UART0) Baud Rate Generator Register */
	#define UART0_RPR  (*(volatile uint32_t*)0x400E0700U) /**< \brief (UART0) Receive Pointer Register */
	#define UART0_RCR  (*(volatile uint32_t*)0x400E0704U) /**< \brief (UART0) Receive Counter Register */
	#define UART0_TPR  (*(volatile uint32_t*)0x400E0708U) /**< \brief (UART0) Transmit Pointer Register */
	#define UART0_TCR  (*(volatile uint32_t*)0x400E070CU) /**< \brief (UART0) Transmit Counter Register */
	#define UART0_RNPR (*(volatile uint32_t*)0x400E0710U) /**< \brief (UART0) Receive Next Pointer Register */
	#define UART0_RNCR (*(volatile uint32_t*)0x400E0714U) /**< \brief (UART0) Receive Next Counter Register */
	#define UART0_TNPR (*(volatile uint32_t*)0x400E0718U) /**< \brief (UART0) Transmit Next Pointer Register */
	#define UART0_TNCR (*(volatile uint32_t*)0x400E071CU) /**< \brief (UART0) Transmit Next Counter Register */
	#define UART0_PTCR (*(volatile uint32_t*)0x400E0720U) /**< \brief (UART0) Transfer Control Register */
	#define UART0_PTSR (*(volatile uint32_t*)0x400E0724U) /**< \brief (UART0) Transfer Status Register */

	#define UART1_CR            (*(volatile uint32_t*)0x400E0800U) /**< \brief (UART1) Control Register */
	#define UART1_MR            (*(volatile uint32_t*)0x400E0804U) /**< \brief (UART1) Mode Register */
	#define UART1_IER           (*(volatile uint32_t*)0x400E0808U) /**< \brief (UART1) Interrupt Enable Register */
	#define UART1_IDR           (*(volatile uint32_t*)0x400E080CU) /**< \brief (UART1) Interrupt Disable Register */
	#define UART1_IMR           (*(volatile uint32_t*)0x400E0810U) /**< \brief (UART1) Interrupt Mask Register */
	#define UART1_SR            (*(volatile uint32_t*)0x400E0814U) /**< \brief (UART1) Status Register */
	#define UART1_RHR           (*(volatile uint32_t*)0x400E0818U) /**< \brief (UART1) Receive Holding Register */
	#define UART1_THR           (*(volatile uint32_t*)0x400E081CU) /**< \brief (UART1) Transmit Holding Register */
	#define UART1_BRGR          (*(volatile uint32_t*)0x400E0820U) /**< \brief (UART1) Baud Rate Generator Register */
	#define UART1_RPR           (*(volatile uint32_t*)0x400E0900U) /**< \brief (UART1) Receive Pointer Register */
	#define UART1_RCR           (*(volatile uint32_t*)0x400E0904U) /**< \brief (UART1) Receive Counter Register */
	#define UART1_TPR           (*(volatile uint32_t*)0x400E0908U) /**< \brief (UART1) Transmit Pointer Register */
	#define UART1_TCR           (*(volatile uint32_t*)0x400E090CU) /**< \brief (UART1) Transmit Counter Register */
	#define UART1_RNPR          (*(volatile uint32_t*)0x400E0910U) /**< \brief (UART1) Receive Next Pointer Register */
	#define UART1_RNCR          (*(volatile uint32_t*)0x400E0914U) /**< \brief (UART1) Receive Next Counter Register */
	#define UART1_TNPR          (*(volatile uint32_t*)0x400E0918U) /**< \brief (UART1) Transmit Next Pointer Register */
	#define UART1_TNCR          (*(volatile uint32_t*)0x400E091CU) /**< \brief (UART1) Transmit Next Counter Register */
	#define UART1_PTCR          (*(volatile uint32_t*)0x400E0920U) /**< \brief (UART1) Transfer Control Register */
	#define UART1_PTSR          (*(volatile uint32_t*)0x400E0924U) /**< \brief (UART1) Transfer Status Register */


	/* -------- UART_CR : (UART Offset: 0x0000) Control Register -------- */
	#define UART_CR_RSTRX (0x1u << 2) /**< \brief (UART_CR) Reset Receiver */
	#define UART_CR_RSTTX (0x1u << 3) /**< \brief (UART_CR) Reset Transmitter */
	#define UART_CR_RXEN (0x1u << 4) /**< \brief (UART_CR) Receiver Enable */
	#define UART_CR_RXDIS (0x1u << 5) /**< \brief (UART_CR) Receiver Disable */
	#define UART_CR_TXEN (0x1u << 6) /**< \brief (UART_CR) Transmitter Enable */
	#define UART_CR_TXDIS (0x1u << 7) /**< \brief (UART_CR) Transmitter Disable */
	#define UART_CR_RSTSTA (0x1u << 8) /**< \brief (UART_CR) Reset Status Bits */

	/* -------- UART_MR : (UART Offset: 0x0004) Mode Register -------- */
	#define UART_MR_PAR_Pos 9
	#define UART_MR_PAR_Msk (0x7u << UART_MR_PAR_Pos) /**< \brief (UART_MR) Parity Type */
	#define   UART_MR_PAR_EVEN (0x0u << 9) /**< \brief (UART_MR) Even parity */
	#define   UART_MR_PAR_ODD (0x1u << 9) /**< \brief (UART_MR) Odd parity */
	#define   UART_MR_PAR_SPACE (0x2u << 9) /**< \brief (UART_MR) Space: parity forced to 0 */
	#define   UART_MR_PAR_MARK (0x3u << 9) /**< \brief (UART_MR) Mark: parity forced to 1 */
	#define   UART_MR_PAR_NO (0x4u << 9) /**< \brief (UART_MR) No parity */
	#define UART_MR_CHMODE_Pos 14
	#define UART_MR_CHMODE_Msk (0x3u << UART_MR_CHMODE_Pos) /**< \brief (UART_MR) Channel Mode */
	#define   UART_MR_CHMODE_NORMAL (0x0u << 14) /**< \brief (UART_MR) Normal Mode */
	#define   UART_MR_CHMODE_AUTOMATIC (0x1u << 14) /**< \brief (UART_MR) Automatic Echo */
	#define   UART_MR_CHMODE_LOCAL_LOOPBACK (0x2u << 14) /**< \brief (UART_MR) Local Loopback */
	#define   UART_MR_CHMODE_REMOTE_LOOPBACK (0x3u << 14) /**< \brief (UART_MR) Remote Loopback */

	/* -------- UART_IER : (UART Offset: 0x0008) Interrupt Enable Register -------- */
	#define UART_IER_RXRDY (0x1u << 0) /**< \brief (UART_IER) Enable RXRDY Interrupt */
	#define UART_IER_TXRDY (0x1u << 1) /**< \brief (UART_IER) Enable TXRDY Interrupt */
	#define UART_IER_ENDRX (0x1u << 3) /**< \brief (UART_IER) Enable End of Receive Transfer Interrupt */
	#define UART_IER_ENDTX (0x1u << 4) /**< \brief (UART_IER) Enable End of Transmit Interrupt */
	#define UART_IER_OVRE (0x1u << 5) /**< \brief (UART_IER) Enable Overrun Error Interrupt */
	#define UART_IER_FRAME (0x1u << 6) /**< \brief (UART_IER) Enable Framing Error Interrupt */
	#define UART_IER_PARE (0x1u << 7) /**< \brief (UART_IER) Enable Parity Error Interrupt */
	#define UART_IER_TXEMPTY (0x1u << 9) /**< \brief (UART_IER) Enable TXEMPTY Interrupt */
	#define UART_IER_TXBUFE (0x1u << 11) /**< \brief (UART_IER) Enable Buffer Empty Interrupt */
	#define UART_IER_RXBUFF (0x1u << 12) /**< \brief (UART_IER) Enable Buffer Full Interrupt */

	/* -------- UART_IDR : (UART Offset: 0x000C) Interrupt Disable Register -------- */
	#define UART_IDR_RXRDY (0x1u << 0) /**< \brief (UART_IDR) Disable RXRDY Interrupt */
	#define UART_IDR_TXRDY (0x1u << 1) /**< \brief (UART_IDR) Disable TXRDY Interrupt */
	#define UART_IDR_ENDRX (0x1u << 3) /**< \brief (UART_IDR) Disable End of Receive Transfer Interrupt */
	#define UART_IDR_ENDTX (0x1u << 4) /**< \brief (UART_IDR) Disable End of Transmit Interrupt */
	#define UART_IDR_OVRE (0x1u << 5) /**< \brief (UART_IDR) Disable Overrun Error Interrupt */
	#define UART_IDR_FRAME (0x1u << 6) /**< \brief (UART_IDR) Disable Framing Error Interrupt */
	#define UART_IDR_PARE (0x1u << 7) /**< \brief (UART_IDR) Disable Parity Error Interrupt */
	#define UART_IDR_TXEMPTY (0x1u << 9) /**< \brief (UART_IDR) Disable TXEMPTY Interrupt */
	#define UART_IDR_TXBUFE (0x1u << 11) /**< \brief (UART_IDR) Disable Buffer Empty Interrupt */
	#define UART_IDR_RXBUFF (0x1u << 12) /**< \brief (UART_IDR) Disable Buffer Full Interrupt */

	/* -------- UART_IMR : (UART Offset: 0x0010) Interrupt Mask Register -------- */
	#define UART_IMR_RXRDY (0x1u << 0) /**< \brief (UART_IMR) Mask RXRDY Interrupt */
	#define UART_IMR_TXRDY (0x1u << 1) /**< \brief (UART_IMR) Disable TXRDY Interrupt */
	#define UART_IMR_ENDRX (0x1u << 3) /**< \brief (UART_IMR) Mask End of Receive Transfer Interrupt */
	#define UART_IMR_ENDTX (0x1u << 4) /**< \brief (UART_IMR) Mask End of Transmit Interrupt */
	#define UART_IMR_OVRE (0x1u << 5) /**< \brief (UART_IMR) Mask Overrun Error Interrupt */
	#define UART_IMR_FRAME (0x1u << 6) /**< \brief (UART_IMR) Mask Framing Error Interrupt */
	#define UART_IMR_PARE (0x1u << 7) /**< \brief (UART_IMR) Mask Parity Error Interrupt */
	#define UART_IMR_TXEMPTY (0x1u << 9) /**< \brief (UART_IMR) Mask TXEMPTY Interrupt */
	#define UART_IMR_TXBUFE (0x1u << 11) /**< \brief (UART_IMR) Mask TXBUFE Interrupt */
	#define UART_IMR_RXBUFF (0x1u << 12) /**< \brief (UART_IMR) Mask RXBUFF Interrupt */

	/* -------- UART_SR : (UART Offset: 0x0014) Status Register -------- */
	#define UART_SR_RXRDY (0x1u << 0) /**< \brief (UART_SR) Receiver Ready */
	#define UART_SR_TXRDY (0x1u << 1) /**< \brief (UART_SR) Transmitter Ready */
	#define UART_SR_ENDRX (0x1u << 3) /**< \brief (UART_SR) End of Receiver Transfer */
	#define UART_SR_ENDTX (0x1u << 4) /**< \brief (UART_SR) End of Transmitter Transfer */
	#define UART_SR_OVRE (0x1u << 5) /**< \brief (UART_SR) Overrun Error */
	#define UART_SR_FRAME (0x1u << 6) /**< \brief (UART_SR) Framing Error */
	#define UART_SR_PARE (0x1u << 7) /**< \brief (UART_SR) Parity Error */
	#define UART_SR_TXEMPTY (0x1u << 9) /**< \brief (UART_SR) Transmitter Empty */
	#define UART_SR_TXBUFE (0x1u << 11) /**< \brief (UART_SR) Transmission Buffer Empty */
	#define UART_SR_RXBUFF (0x1u << 12) /**< \brief (UART_SR) Receive Buffer Full */

	/* -------- UART_RHR : (UART Offset: 0x0018) Receive Holding Register -------- */
	#define UART_RHR_RXCHR_Pos 0
	#define UART_RHR_RXCHR_Msk (0xffu << UART_RHR_RXCHR_Pos) /**< \brief (UART_RHR) Received Character */

	/* -------- UART_THR : (UART Offset: 0x001C) Transmit Holding Register -------- */
	#define UART_THR_TXCHR_Pos 0
	#define UART_THR_TXCHR_Msk (0xffu << UART_THR_TXCHR_Pos) /**< \brief (UART_THR) Character to be Transmitted */
	#define UART_THR_TXCHR(value) ((UART_THR_TXCHR_Msk & ((value) << UART_THR_TXCHR_Pos)))

	/* -------- UART_BRGR : (UART Offset: 0x0020) Baud Rate Generator Register -------- */
	#define UART_BRGR_CD_Pos 0
	#define UART_BRGR_CD_Msk (0xffffu << UART_BRGR_CD_Pos) /**< \brief (UART_BRGR) Clock Divisor */
	#define UART_BRGR_CD(value) ((UART_BRGR_CD_Msk & ((value) << UART_BRGR_CD_Pos)))

	/* -------- UART_RPR : (UART Offset: 0x100) Receive Pointer Register -------- */
	#define UART_RPR_RXPTR_Pos 0
	#define UART_RPR_RXPTR_Msk (0xffffffffu << UART_RPR_RXPTR_Pos) /**< \brief (UART_RPR) Receive Pointer Register */
	#define UART_RPR_RXPTR(value) ((UART_RPR_RXPTR_Msk & ((value) << UART_RPR_RXPTR_Pos)))

	/* -------- UART_RCR : (UART Offset: 0x104) Receive Counter Register -------- */
	#define UART_RCR_RXCTR_Pos 0
	#define UART_RCR_RXCTR_Msk (0xffffu << UART_RCR_RXCTR_Pos) /**< \brief (UART_RCR) Receive Counter Register */
	#define UART_RCR_RXCTR(value) ((UART_RCR_RXCTR_Msk & ((value) << UART_RCR_RXCTR_Pos)))

	/* -------- UART_TPR : (UART Offset: 0x108) Transmit Pointer Register -------- */
	#define UART_TPR_TXPTR_Pos 0
	#define UART_TPR_TXPTR_Msk (0xffffffffu << UART_TPR_TXPTR_Pos) /**< \brief (UART_TPR) Transmit Counter Register */
	#define UART_TPR_TXPTR(value) ((UART_TPR_TXPTR_Msk & ((value) << UART_TPR_TXPTR_Pos)))

	/* -------- UART_TCR : (UART Offset: 0x10C) Transmit Counter Register -------- */
	#define UART_TCR_TXCTR_Pos 0
	#define UART_TCR_TXCTR_Msk (0xffffu << UART_TCR_TXCTR_Pos) /**< \brief (UART_TCR) Transmit Counter Register */
	#define UART_TCR_TXCTR(value) ((UART_TCR_TXCTR_Msk & ((value) << UART_TCR_TXCTR_Pos)))

	/* -------- UART_RNPR : (UART Offset: 0x110) Receive Next Pointer Register -------- */
	#define UART_RNPR_RXNPTR_Pos 0
	#define UART_RNPR_RXNPTR_Msk (0xffffffffu << UART_RNPR_RXNPTR_Pos) /**< \brief (UART_RNPR) Receive Next Pointer */
	#define UART_RNPR_RXNPTR(value) ((UART_RNPR_RXNPTR_Msk & ((value) << UART_RNPR_RXNPTR_Pos)))

	/* -------- UART_RNCR : (UART Offset: 0x114) Receive Next Counter Register -------- */
	#define UART_RNCR_RXNCTR_Pos 0
	#define UART_RNCR_RXNCTR_Msk (0xffffu << UART_RNCR_RXNCTR_Pos) /**< \brief (UART_RNCR) Receive Next Counter */
	#define UART_RNCR_RXNCTR(value) ((UART_RNCR_RXNCTR_Msk & ((value) << UART_RNCR_RXNCTR_Pos)))

	/* -------- UART_TNPR : (UART Offset: 0x118) Transmit Next Pointer Register -------- */
	#define UART_TNPR_TXNPTR_Pos 0
	#define UART_TNPR_TXNPTR_Msk (0xffffffffu << UART_TNPR_TXNPTR_Pos) /**< \brief (UART_TNPR) Transmit Next Pointer */
	#define UART_TNPR_TXNPTR(value) ((UART_TNPR_TXNPTR_Msk & ((value) << UART_TNPR_TXNPTR_Pos)))

	/* -------- UART_TNCR : (UART Offset: 0x11C) Transmit Next Counter Register -------- */
	#define UART_TNCR_TXNCTR_Pos 0
	#define UART_TNCR_TXNCTR_Msk (0xffffu << UART_TNCR_TXNCTR_Pos) /**< \brief (UART_TNCR) Transmit Counter Next */
	#define UART_TNCR_TXNCTR(value) ((UART_TNCR_TXNCTR_Msk & ((value) << UART_TNCR_TXNCTR_Pos)))

	/* -------- UART_PTCR : (UART Offset: 0x120) Transfer Control Register -------- */
	#define UART_PTCR_RXTEN (0x1u << 0) /**< \brief (UART_PTCR) Receiver Transfer Enable */
	#define UART_PTCR_RXTDIS (0x1u << 1) /**< \brief (UART_PTCR) Receiver Transfer Disable */
	#define UART_PTCR_TXTEN (0x1u << 8) /**< \brief (UART_PTCR) Transmitter Transfer Enable */
	#define UART_PTCR_TXTDIS (0x1u << 9) /**< \brief (UART_PTCR) Transmitter Transfer Disable */

	/* -------- UART_PTSR : (UART Offset: 0x124) Transfer Status Register -------- */
	#define UART_PTSR_RXTEN (0x1u << 0) /**< \brief (UART_PTSR) Receiver Transfer Enable */
	#define UART_PTSR_TXTEN (0x1u << 8) /**< \brief (UART_PTSR) Transmitter Transfer Enable */


	// -----------------------------------------------------------------------------
	//  USART
	// -----------------------------------------------------------------------------
	#define USART0_CR   (*(volatile uint32_t*)0x40024000U) /**< \brief (USART0) Control Register */
	#define USART0_MR   (*(volatile uint32_t*)0x40024004U) /**< \brief (USART0) Mode Register */
	#define USART0_IER  (*(volatile uint32_t*)0x40024008U) /**< \brief (USART0) Interrupt Enable Register */
	#define USART0_IDR  (*(volatile uint32_t*)0x4002400CU) /**< \brief (USART0) Interrupt Disable Register */
	#define USART0_IMR  (*(volatile uint32_t*)0x40024010U) /**< \brief (USART0) Interrupt Mask Register */
	#define USART0_CSR  (*(volatile uint32_t*)0x40024014U) /**< \brief (USART0) Channel Status Register */
	#define USART0_RHR  (*(volatile uint32_t*)0x40024018U) /**< \brief (USART0) Receiver Holding Register */
	#define USART0_THR  (*(volatile uint32_t*)0x4002401CU) /**< \brief (USART0) Transmitter Holding Register */
	#define USART0_BRGR (*(volatile uint32_t*)0x40024020U) /**< \brief (USART0) Baud Rate Generator Register */
	#define USART0_RTOR (*(volatile uint32_t*)0x40024024U) /**< \brief (USART0) Receiver Time-out Register */
	#define USART0_TTGR (*(volatile uint32_t*)0x40024028U) /**< \brief (USART0) Transmitter Timeguard Register */
	#define USART0_FIDI (*(volatile uint32_t*)0x40024040U) /**< \brief (USART0) FI DI Ratio Register */
	#define USART0_NER  (*(volatile uint32_t*)0x40024044U) /**< \brief (USART0) Number of Errors Register */
	#define USART0_IF   (*(volatile uint32_t*)0x4002404CU) /**< \brief (USART0) IrDA Filter Register */
	#define USART0_MAN  (*(volatile uint32_t*)0x40024050U) /**< \brief (USART0) Manchester Encoder Decoder Register */
	#define USART0_WPMR (*(volatile uint32_t*)0x400240E4U) /**< \brief (USART0) Write Protect Mode Register */
	#define USART0_WPSR (*(volatile uint32_t*)0x400240E8U) /**< \brief (USART0) Write Protect Status Register */
	#define USART0_VERSION (*(volatile uint32_t*))0x400240FCU) /**< \brief (USART0) Version Register */
	#define USART0_RPR  (*(volatile uint32_t*)0x40024100U) /**< \brief (USART0) Receive Pointer Register */
	#define USART0_RCR  (*(volatile uint32_t*)0x40024104U) /**< \brief (USART0) Receive Counter Register */
	#define USART0_TPR  (*(volatile uint32_t*)0x40024108U) /**< \brief (USART0) Transmit Pointer Register */
	#define USART0_TCR  (*(volatile uint32_t*)0x4002410CU) /**< \brief (USART0) Transmit Counter Register */
	#define USART0_RNPR (*(volatile uint32_t*)0x40024110U) /**< \brief (USART0) Receive Next Pointer Register */
	#define USART0_RNCR (*(volatile uint32_t*)0x40024114U) /**< \brief (USART0) Receive Next Counter Register */
	#define USART0_TNPR (*(volatile uint32_t*)0x40024118U) /**< \brief (USART0) Transmit Next Pointer Register */
	#define USART0_TNCR (*(volatile uint32_t*)0x4002411CU) /**< \brief (USART0) Transmit Next Counter Register */
	#define USART0_PTCR (*(volatile uint32_t*)0x40024120U) /**< \brief (USART0) Transfer Control Register */
	#define USART0_PTSR (*(volatile uint32_t*)0x40024124U) /**< \brief (USART0) Transfer Status Register */


	#define USART1_CR   (*(volatile uint32_t*)0x40028000U) /**< \brief (USART1) Control Register */
	#define USART1_MR   (*(volatile uint32_t*)0x40028004U) /**< \brief (USART1) Mode Register */
	#define USART1_IER  (*(volatile uint32_t*)0x40028008U) /**< \brief (USART1) Interrupt Enable Register */
	#define USART1_IDR  (*(volatile uint32_t*)0x4002800CU) /**< \brief (USART1) Interrupt Disable Register */
	#define USART1_IMR  (*(volatile uint32_t*)0x40028010U) /**< \brief (USART1) Interrupt Mask Register */
	#define USART1_CSR  (*(volatile uint32_t*)0x40028014U) /**< \brief (USART1) Channel Status Register */
	#define USART1_RHR  (*(volatile uint32_t*)0x40028018U) /**< \brief (USART1) Receiver Holding Register */
	#define USART1_THR  (*(volatile uint32_t*)0x4002801CU) /**< \brief (USART1) Transmitter Holding Register */
	#define USART1_BRGR (*(volatile uint32_t*)0x40028020U) /**< \brief (USART1) Baud Rate Generator Register */
	#define USART1_RTOR (*(volatile uint32_t*)0x40028024U) /**< \brief (USART1) Receiver Time-out Register */
	#define USART1_TTGR (*(volatile uint32_t*)0x40028028U) /**< \brief (USART1) Transmitter Timeguard Register */
	#define USART1_FIDI (*(volatile uint32_t*)0x40028040U) /**< \brief (USART1) FI DI Ratio Register */
	#define USART1_NER  (*(volatile uint32_t*)0x40028044U) /**< \brief (USART1) Number of Errors Register */
	#define USART1_IF   (*(volatile uint32_t*)0x4002804CU) /**< \brief (USART1) IrDA Filter Register */
	#define USART1_MAN  (*(volatile uint32_t*)0x40028050U) /**< \brief (USART1) Manchester Encoder Decoder Register */
	#define USART1_WPMR (*(volatile uint32_t*)0x400280E4U) /**< \brief (USART1) Write Protect Mode Register */
	#define USART1_WPSR (*(volatile uint32_t*)0x400280E8U) /**< \brief (USART1) Write Protect Status Register */
	#define USART1_VERSION (*(volatile uint32_t*)0x400280FCU) /**< \brief (USART1) Version Register */
	#define USART1_RPR  (*(volatile uint32_t*)0x40028100U) /**< \brief (USART1) Receive Pointer Register */
	#define USART1_RCR  (*(volatile uint32_t*)0x40028104U) /**< \brief (USART1) Receive Counter Register */
	#define USART1_TPR  (*(volatile uint32_t*)0x40028108U) /**< \brief (USART1) Transmit Pointer Register */
	#define USART1_TCR  (*(volatile uint32_t*)0x4002810CU) /**< \brief (USART1) Transmit Counter Register */
	#define USART1_RNPR (*(volatile uint32_t*)0x40028110U) /**< \brief (USART1) Receive Next Pointer Register */
	#define USART1_RNCR (*(volatile uint32_t*)0x40028114U) /**< \brief (USART1) Receive Next Counter Register */
	#define USART1_TNPR (*(volatile uint32_t*)0x40028118U) /**< \brief (USART1) Transmit Next Pointer Register */
	#define USART1_TNCR (*(volatile uint32_t*)0x4002811CU) /**< \brief (USART1) Transmit Next Counter Register */
	#define USART1_PTCR (*(volatile uint32_t*)0x40028120U) /**< \brief (USART1) Transfer Control Register */
	#define USART1_PTSR (*(volatile uint32_t*)0x40028124U) /**< \brief (USART1) Transfer Status Register */

	/* -------- US_CR : (USART Offset: 0x0000) Control Register -------- */
	#define US_CR_RSTRX (0x1u << 2) /**< \brief (US_CR) Reset Receiver */
	#define US_CR_RSTTX (0x1u << 3) /**< \brief (US_CR) Reset Transmitter */
	#define US_CR_RXEN (0x1u << 4) /**< \brief (US_CR) Receiver Enable */
	#define US_CR_RXDIS (0x1u << 5) /**< \brief (US_CR) Receiver Disable */
	#define US_CR_TXEN (0x1u << 6) /**< \brief (US_CR) Transmitter Enable */
	#define US_CR_TXDIS (0x1u << 7) /**< \brief (US_CR) Transmitter Disable */
	#define US_CR_RSTSTA (0x1u << 8) /**< \brief (US_CR) Reset Status Bits */
	#define US_CR_STTBRK (0x1u << 9) /**< \brief (US_CR) Start Break */
	#define US_CR_STPBRK (0x1u << 10) /**< \brief (US_CR) Stop Break */
	#define US_CR_STTTO (0x1u << 11) /**< \brief (US_CR) Start Time-out */
	#define US_CR_SENDA (0x1u << 12) /**< \brief (US_CR) Send Address */
	#define US_CR_RSTIT (0x1u << 13) /**< \brief (US_CR) Reset Iterations */
	#define US_CR_RSTNACK (0x1u << 14) /**< \brief (US_CR) Reset Non Acknowledge */
	#define US_CR_RETTO (0x1u << 15) /**< \brief (US_CR) Rearm Time-out */
	#define US_CR_DTREN (0x1u << 16) /**< \brief (US_CR) Data Terminal Ready Enable */
	#define US_CR_DTRDIS (0x1u << 17) /**< \brief (US_CR) Data Terminal Ready Disable */
	#define US_CR_RTSEN (0x1u << 18) /**< \brief (US_CR) Request to Send Enable */
	#define US_CR_FCS (0x1u << 18) /**< \brief (US_CR) Force SPI Chip Select */
	#define US_CR_RTSDIS (0x1u << 19) /**< \brief (US_CR) Request to Send Disable */
	#define US_CR_RCS (0x1u << 19) /**< \brief (US_CR) Release SPI Chip Select */

	/* -------- US_MR : (USART Offset: 0x0004) Mode Register -------- */
	#define US_MR_USART_MODE_Pos 0
	#define US_MR_USART_MODE_Msk (0xfu << US_MR_USART_MODE_Pos) /**< \brief (US_MR)  */
	#define   US_MR_USART_MODE_NORMAL (0x0u << 0) /**< \brief (US_MR) Normal mode */
	#define   US_MR_USART_MODE_RS485 (0x1u << 0) /**< \brief (US_MR) RS485 */
	#define   US_MR_USART_MODE_HW_HANDSHAKING (0x2u << 0) /**< \brief (US_MR) Hardware Handshaking */
	#define   US_MR_USART_MODE_MODEM (0x3u << 0) /**< \brief (US_MR) Modem */
	#define   US_MR_USART_MODE_IS07816_T_0 (0x4u << 0) /**< \brief (US_MR) IS07816 Protocol: T = 0 */
	#define   US_MR_USART_MODE_IS07816_T_1 (0x6u << 0) /**< \brief (US_MR) IS07816 Protocol: T = 1 */
	#define   US_MR_USART_MODE_IRDA (0x8u << 0) /**< \brief (US_MR) IrDA */
	#define   US_MR_USART_MODE_SPI_MASTER (0xEu << 0) /**< \brief (US_MR) SPI Master */
	#define   US_MR_USART_MODE_SPI_SLAVE (0xFu << 0) /**< \brief (US_MR) SPI Slave */
	#define US_MR_USCLKS_Pos 4
	#define US_MR_USCLKS_Msk (0x3u << US_MR_USCLKS_Pos) /**< \brief (US_MR) Clock Selection */
	#define   US_MR_USCLKS_MCK (0x0u << 4) /**< \brief (US_MR) Master Clock MCK is selected */
	#define   US_MR_USCLKS_DIV (0x1u << 4) /**< \brief (US_MR) Internal Clock Divided MCK/DIV (DIV=8) is selected */
	#define   US_MR_USCLKS_SCK (0x3u << 4) /**< \brief (US_MR) Serial Clock SLK is selected */
	#define US_MR_CHRL_Pos 6
	#define US_MR_CHRL_Msk (0x3u << US_MR_CHRL_Pos) /**< \brief (US_MR) Character Length. */
	#define   US_MR_CHRL_5_BIT (0x0u << 6) /**< \brief (US_MR) Character length is 5 bits */
	#define   US_MR_CHRL_6_BIT (0x1u << 6) /**< \brief (US_MR) Character length is 6 bits */
	#define   US_MR_CHRL_7_BIT (0x2u << 6) /**< \brief (US_MR) Character length is 7 bits */
	#define   US_MR_CHRL_8_BIT (0x3u << 6) /**< \brief (US_MR) Character length is 8 bits */
	#define US_MR_SYNC (0x1u << 8) /**< \brief (US_MR) Synchronous Mode Select */
	#define US_MR_CPHA (0x1u << 8) /**< \brief (US_MR) SPI Clock Phase */
	#define US_MR_PAR_Pos 9
	#define US_MR_PAR_Msk (0x7u << US_MR_PAR_Pos) /**< \brief (US_MR) Parity Type */
	#define   US_MR_PAR_EVEN (0x0u << 9) /**< \brief (US_MR) Even parity */
	#define   US_MR_PAR_ODD (0x1u << 9) /**< \brief (US_MR) Odd parity */
	#define   US_MR_PAR_SPACE (0x2u << 9) /**< \brief (US_MR) Parity forced to 0 (Space) */
	#define   US_MR_PAR_MARK (0x3u << 9) /**< \brief (US_MR) Parity forced to 1 (Mark) */
	#define   US_MR_PAR_NO (0x4u << 9) /**< \brief (US_MR) No parity */
	#define   US_MR_PAR_MULTIDROP (0x6u << 9) /**< \brief (US_MR) Multidrop mode */
	#define US_MR_NBSTOP_Pos 12
	#define US_MR_NBSTOP_Msk (0x3u << US_MR_NBSTOP_Pos) /**< \brief (US_MR) Number of Stop Bits */
	#define   US_MR_NBSTOP_1_BIT (0x0u << 12) /**< \brief (US_MR) 1 stop bit */
	#define   US_MR_NBSTOP_1_5_BIT (0x1u << 12) /**< \brief (US_MR) 1.5 stop bit (SYNC = 0) or reserved (SYNC = 1) */
	#define   US_MR_NBSTOP_2_BIT (0x2u << 12) /**< \brief (US_MR) 2 stop bits */
	#define US_MR_CHMODE_Pos 14
	#define US_MR_CHMODE_Msk (0x3u << US_MR_CHMODE_Pos) /**< \brief (US_MR) Channel Mode */
	#define   US_MR_CHMODE_NORMAL (0x0u << 14) /**< \brief (US_MR) Normal Mode */
	#define   US_MR_CHMODE_AUTOMATIC (0x1u << 14) /**< \brief (US_MR) Automatic Echo. Receiver input is connected to the TXD pin. */
	#define   US_MR_CHMODE_LOCAL_LOOPBACK (0x2u << 14) /**< \brief (US_MR) Local Loopback. Transmitter output is connected to the Receiver Input. */
	#define   US_MR_CHMODE_REMOTE_LOOPBACK (0x3u << 14) /**< \brief (US_MR) Remote Loopback. RXD pin is internally connected to the TXD pin. */
	#define US_MR_MSBF (0x1u << 16) /**< \brief (US_MR) Bit Order */
	#define US_MR_CPOL (0x1u << 16) /**< \brief (US_MR) SPI Clock Polarity */
	#define US_MR_MODE9 (0x1u << 17) /**< \brief (US_MR) 9-bit Character Length */
	#define US_MR_CLKO (0x1u << 18) /**< \brief (US_MR) Clock Output Select */
	#define US_MR_OVER (0x1u << 19) /**< \brief (US_MR) Oversampling Mode */
	#define US_MR_INACK (0x1u << 20) /**< \brief (US_MR) Inhibit Non Acknowledge */
	#define US_MR_DSNACK (0x1u << 21) /**< \brief (US_MR) Disable Successive NACK */
	#define US_MR_VAR_SYNC (0x1u << 22) /**< \brief (US_MR) Variable Synchronization of Command/Data Sync Start Frame Delimiter */
	#define US_MR_INVDATA (0x1u << 23) /**< \brief (US_MR) INverted Data */
	#define US_MR_MAX_ITERATION_Pos 24
	#define US_MR_MAX_ITERATION_Msk (0x7u << US_MR_MAX_ITERATION_Pos) /**< \brief (US_MR)  */
	#define US_MR_MAX_ITERATION(value) ((US_MR_MAX_ITERATION_Msk & ((value) << US_MR_MAX_ITERATION_Pos)))
	#define US_MR_FILTER (0x1u << 28) /**< \brief (US_MR) Infrared Receive Line Filter */
	#define US_MR_MAN (0x1u << 29) /**< \brief (US_MR) Manchester Encoder/Decoder Enable */
	#define US_MR_MODSYNC (0x1u << 30) /**< \brief (US_MR) Manchester Synchronization Mode */
	#define US_MR_ONEBIT (0x1u << 31) /**< \brief (US_MR) Start Frame Delimiter Selector */

	/* -------- US_IER : (USART Offset: 0x0008) Interrupt Enable Register -------- */
	#define US_IER_RXRDY (0x1u << 0) /**< \brief (US_IER) RXRDY Interrupt Enable */
	#define US_IER_TXRDY (0x1u << 1) /**< \brief (US_IER) TXRDY Interrupt Enable */
	#define US_IER_RXBRK (0x1u << 2) /**< \brief (US_IER) Receiver Break Interrupt Enable */
	#define US_IER_ENDRX (0x1u << 3) /**< \brief (US_IER) End of Receive Transfer Interrupt Enable */
	#define US_IER_ENDTX (0x1u << 4) /**< \brief (US_IER) End of Transmit Interrupt Enable */
	#define US_IER_OVRE (0x1u << 5) /**< \brief (US_IER) Overrun Error Interrupt Enable */
	#define US_IER_FRAME (0x1u << 6) /**< \brief (US_IER) Framing Error Interrupt Enable */
	#define US_IER_PARE (0x1u << 7) /**< \brief (US_IER) Parity Error Interrupt Enable */
	#define US_IER_TIMEOUT (0x1u << 8) /**< \brief (US_IER) Time-out Interrupt Enable */
	#define US_IER_TXEMPTY (0x1u << 9) /**< \brief (US_IER) TXEMPTY Interrupt Enable */
	#define US_IER_ITER (0x1u << 10) /**< \brief (US_IER) Max number of Repetitions Reached */
	#define US_IER_UNRE (0x1u << 10) /**< \brief (US_IER) SPI Underrun Error */
	#define US_IER_TXBUFE (0x1u << 11) /**< \brief (US_IER) Buffer Empty Interrupt Enable */
	#define US_IER_RXBUFF (0x1u << 12) /**< \brief (US_IER) Buffer Full Interrupt Enable */
	#define US_IER_NACK (0x1u << 13) /**< \brief (US_IER) Non AcknowledgeInterrupt Enable */
	#define US_IER_RIIC (0x1u << 16) /**< \brief (US_IER) Ring Indicator Input Change Enable */
	#define US_IER_DSRIC (0x1u << 17) /**< \brief (US_IER) Data Set Ready Input Change Enable */
	#define US_IER_DCDIC (0x1u << 18) /**< \brief (US_IER) Data Carrier Detect Input Change Interrupt Enable */
	#define US_IER_CTSIC (0x1u << 19) /**< \brief (US_IER) Clear to Send Input Change Interrupt Enable */
	#define US_IER_MANE (0x1u << 24) /**< \brief (US_IER) Manchester Error Interrupt Enable */

	/* -------- US_IDR : (USART Offset: 0x000C) Interrupt Disable Register -------- */
	#define US_IDR_RXRDY (0x1u << 0) /**< \brief (US_IDR) RXRDY Interrupt Disable */
	#define US_IDR_TXRDY (0x1u << 1) /**< \brief (US_IDR) TXRDY Interrupt Disable */
	#define US_IDR_RXBRK (0x1u << 2) /**< \brief (US_IDR) Receiver Break Interrupt Disable */
	#define US_IDR_ENDRX (0x1u << 3) /**< \brief (US_IDR) End of Receive Transfer Interrupt Disable */
	#define US_IDR_ENDTX (0x1u << 4) /**< \brief (US_IDR) End of Transmit Interrupt Disable */
	#define US_IDR_OVRE (0x1u << 5) /**< \brief (US_IDR) Overrun Error Interrupt Disable */
	#define US_IDR_FRAME (0x1u << 6) /**< \brief (US_IDR) Framing Error Interrupt Disable */
	#define US_IDR_PARE (0x1u << 7) /**< \brief (US_IDR) Parity Error Interrupt Disable */
	#define US_IDR_TIMEOUT (0x1u << 8) /**< \brief (US_IDR) Time-out Interrupt Disable */
	#define US_IDR_TXEMPTY (0x1u << 9) /**< \brief (US_IDR) TXEMPTY Interrupt Disable */
	#define US_IDR_ITER (0x1u << 10) /**< \brief (US_IDR) Max number of Repetitions Reached Disable */
	#define US_IDR_UNRE (0x1u << 10) /**< \brief (US_IDR) SPI Underrun Error Disable */
	#define US_IDR_TXBUFE (0x1u << 11) /**< \brief (US_IDR) Buffer Empty Interrupt Disable */
	#define US_IDR_RXBUFF (0x1u << 12) /**< \brief (US_IDR) Buffer Full Interrupt Disable */
	#define US_IDR_NACK (0x1u << 13) /**< \brief (US_IDR) Non AcknowledgeInterrupt Disable */
	#define US_IDR_RIIC (0x1u << 16) /**< \brief (US_IDR) Ring Indicator Input Change Disable */
	#define US_IDR_DSRIC (0x1u << 17) /**< \brief (US_IDR) Data Set Ready Input Change Disable */
	#define US_IDR_DCDIC (0x1u << 18) /**< \brief (US_IDR) Data Carrier Detect Input Change Interrupt Disable */
	#define US_IDR_CTSIC (0x1u << 19) /**< \brief (US_IDR) Clear to Send Input Change Interrupt Disable */
	#define US_IDR_MANE (0x1u << 24) /**< \brief (US_IDR) Manchester Error Interrupt Disable */

	/* -------- US_IMR : (USART Offset: 0x0010) Interrupt Mask Register -------- */
	#define US_IMR_RXRDY (0x1u << 0) /**< \brief (US_IMR) RXRDY Interrupt Mask */
	#define US_IMR_TXRDY (0x1u << 1) /**< \brief (US_IMR) TXRDY Interrupt Mask */
	#define US_IMR_RXBRK (0x1u << 2) /**< \brief (US_IMR) Receiver Break Interrupt Mask */
	#define US_IMR_ENDRX (0x1u << 3) /**< \brief (US_IMR) End of Receive Transfer Interrupt Mask */
	#define US_IMR_ENDTX (0x1u << 4) /**< \brief (US_IMR) End of Transmit Interrupt Mask */
	#define US_IMR_OVRE (0x1u << 5) /**< \brief (US_IMR) Overrun Error Interrupt Mask */
	#define US_IMR_FRAME (0x1u << 6) /**< \brief (US_IMR) Framing Error Interrupt Mask */
	#define US_IMR_PARE (0x1u << 7) /**< \brief (US_IMR) Parity Error Interrupt Mask */
	#define US_IMR_TIMEOUT (0x1u << 8) /**< \brief (US_IMR) Time-out Interrupt Mask */
	#define US_IMR_TXEMPTY (0x1u << 9) /**< \brief (US_IMR) TXEMPTY Interrupt Mask */
	#define US_IMR_ITER (0x1u << 10) /**< \brief (US_IMR) Max number of Repetitions Reached Mask */
	#define US_IMR_UNRE (0x1u << 10) /**< \brief (US_IMR) SPI Underrun Error Mask */
	#define US_IMR_TXBUFE (0x1u << 11) /**< \brief (US_IMR) Buffer Empty Interrupt Mask */
	#define US_IMR_RXBUFF (0x1u << 12) /**< \brief (US_IMR) Buffer Full Interrupt Mask */
	#define US_IMR_NACK (0x1u << 13) /**< \brief (US_IMR) Non AcknowledgeInterrupt Mask */
	#define US_IMR_RIIC (0x1u << 16) /**< \brief (US_IMR) Ring Indicator Input Change Mask */
	#define US_IMR_DSRIC (0x1u << 17) /**< \brief (US_IMR) Data Set Ready Input Change Mask */
	#define US_IMR_DCDIC (0x1u << 18) /**< \brief (US_IMR) Data Carrier Detect Input Change Interrupt Mask */
	#define US_IMR_CTSIC (0x1u << 19) /**< \brief (US_IMR) Clear to Send Input Change Interrupt Mask */
	#define US_IMR_MANE (0x1u << 24) /**< \brief (US_IMR) Manchester Error Interrupt Mask */

	/* -------- US_CSR : (USART Offset: 0x0014) Channel Status Register -------- */
	#define US_CSR_RXRDY (0x1u << 0) /**< \brief (US_CSR) Receiver Ready */
	#define US_CSR_TXRDY (0x1u << 1) /**< \brief (US_CSR) Transmitter Ready */
	#define US_CSR_RXBRK (0x1u << 2) /**< \brief (US_CSR) Break Received/End of Break */
	#define US_CSR_ENDRX (0x1u << 3) /**< \brief (US_CSR) End of Receiver Transfer */
	#define US_CSR_ENDTX (0x1u << 4) /**< \brief (US_CSR) End of Transmitter Transfer */
	#define US_CSR_OVRE (0x1u << 5) /**< \brief (US_CSR) Overrun Error */
	#define US_CSR_FRAME (0x1u << 6) /**< \brief (US_CSR) Framing Error */
	#define US_CSR_PARE (0x1u << 7) /**< \brief (US_CSR) Parity Error */
	#define US_CSR_TIMEOUT (0x1u << 8) /**< \brief (US_CSR) Receiver Time-out */
	#define US_CSR_TXEMPTY (0x1u << 9) /**< \brief (US_CSR) Transmitter Empty */
	#define US_CSR_ITER (0x1u << 10) /**< \brief (US_CSR) Max number of Repetitions Reached */
	#define US_CSR_UNRE (0x1u << 10) /**< \brief (US_CSR) SPI Underrun Error */
	#define US_CSR_TXBUFE (0x1u << 11) /**< \brief (US_CSR) Transmission Buffer Empty */
	#define US_CSR_RXBUFF (0x1u << 12) /**< \brief (US_CSR) Reception Buffer Full */
	#define US_CSR_NACK (0x1u << 13) /**< \brief (US_CSR) Non AcknowledgeInterrupt */
	#define US_CSR_RIIC (0x1u << 16) /**< \brief (US_CSR) Ring Indicator Input Change Flag */
	#define US_CSR_DSRIC (0x1u << 17) /**< \brief (US_CSR) Data Set Ready Input Change Flag */
	#define US_CSR_DCDIC (0x1u << 18) /**< \brief (US_CSR) Data Carrier Detect Input Change Flag */
	#define US_CSR_CTSIC (0x1u << 19) /**< \brief (US_CSR) Clear to Send Input Change Flag */
	#define US_CSR_RI (0x1u << 20) /**< \brief (US_CSR) Image of RI Input */
	#define US_CSR_DSR (0x1u << 21) /**< \brief (US_CSR) Image of DSR Input */
	#define US_CSR_DCD (0x1u << 22) /**< \brief (US_CSR) Image of DCD Input */
	#define US_CSR_CTS (0x1u << 23) /**< \brief (US_CSR) Image of CTS Input */
	#define US_CSR_MANERR (0x1u << 24) /**< \brief (US_CSR) Manchester Error */

	/* -------- US_RHR : (USART Offset: 0x0018) Receiver Holding Register -------- */
	#define US_RHR_RXCHR_Pos 0
	#define US_RHR_RXCHR_Msk (0x1ffu << US_RHR_RXCHR_Pos) /**< \brief (US_RHR) Received Character */
	#define US_RHR_RXSYNH (0x1u << 15) /**< \brief (US_RHR) Received Sync */

	/* -------- US_THR : (USART Offset: 0x001C) Transmitter Holding Register -------- */
	#define US_THR_TXCHR_Pos 0
	#define US_THR_TXCHR_Msk (0x1ffu << US_THR_TXCHR_Pos) /**< \brief (US_THR) Character to be Transmitted */
	#define US_THR_TXCHR(value) ((US_THR_TXCHR_Msk & ((value) << US_THR_TXCHR_Pos)))
	#define US_THR_TXSYNH (0x1u << 15) /**< \brief (US_THR) Sync Field to be transmitted */

	/* -------- US_BRGR : (USART Offset: 0x0020) Baud Rate Generator Register -------- */
	#define US_BRGR_CD_Pos 0
	#define US_BRGR_CD_Msk (0xffffu << US_BRGR_CD_Pos) /**< \brief (US_BRGR) Clock Divider */
	#define US_BRGR_CD(value) ((US_BRGR_CD_Msk & ((value) << US_BRGR_CD_Pos)))
	#define US_BRGR_FP_Pos 16
	#define US_BRGR_FP_Msk (0x7u << US_BRGR_FP_Pos) /**< \brief (US_BRGR) Fractional Part */
	#define US_BRGR_FP(value) ((US_BRGR_FP_Msk & ((value) << US_BRGR_FP_Pos)))

	/* -------- US_RTOR : (USART Offset: 0x0024) Receiver Time-out Register -------- */
	#define US_RTOR_TO_Pos 0
	#define US_RTOR_TO_Msk (0xffffu << US_RTOR_TO_Pos) /**< \brief (US_RTOR) Time-out Value */
	#define US_RTOR_TO(value) ((US_RTOR_TO_Msk & ((value) << US_RTOR_TO_Pos)))

	/* -------- US_TTGR : (USART Offset: 0x0028) Transmitter Timeguard Register -------- */
	#define US_TTGR_TG_Pos 0
	#define US_TTGR_TG_Msk (0xffu << US_TTGR_TG_Pos) /**< \brief (US_TTGR) Timeguard Value */
	#define US_TTGR_TG(value) ((US_TTGR_TG_Msk & ((value) << US_TTGR_TG_Pos)))

	/* -------- US_FIDI : (USART Offset: 0x0040) FI DI Ratio Register -------- */
	#define US_FIDI_FI_DI_RATIO_Pos 0
	#define US_FIDI_FI_DI_RATIO_Msk (0x7ffu << US_FIDI_FI_DI_RATIO_Pos) /**< \brief (US_FIDI) FI Over DI Ratio Value */
	#define US_FIDI_FI_DI_RATIO(value) ((US_FIDI_FI_DI_RATIO_Msk & ((value) << US_FIDI_FI_DI_RATIO_Pos)))

	/* -------- US_NER : (USART Offset: 0x0044) Number of Errors Register -------- */
	#define US_NER_NB_ERRORS_Pos 0
	#define US_NER_NB_ERRORS_Msk (0xffu << US_NER_NB_ERRORS_Pos) /**< \brief (US_NER) Number of Errors */

	/* -------- US_IF : (USART Offset: 0x004C) IrDA Filter Register -------- */
	#define US_IF_IRDA_FILTER_Pos 0
	#define US_IF_IRDA_FILTER_Msk (0xffu << US_IF_IRDA_FILTER_Pos) /**< \brief (US_IF) IrDA Filter */
	#define US_IF_IRDA_FILTER(value) ((US_IF_IRDA_FILTER_Msk & ((value) << US_IF_IRDA_FILTER_Pos)))

	/* -------- US_MAN : (USART Offset: 0x0050) Manchester Encoder Decoder Register -------- */
	#define US_MAN_TX_PL_Pos 0
	#define US_MAN_TX_PL_Msk (0xfu << US_MAN_TX_PL_Pos) /**< \brief (US_MAN) Transmitter Preamble Length */
	#define US_MAN_TX_PL(value) ((US_MAN_TX_PL_Msk & ((value) << US_MAN_TX_PL_Pos)))
	#define US_MAN_TX_PP_Pos 8
	#define US_MAN_TX_PP_Msk (0x3u << US_MAN_TX_PP_Pos) /**< \brief (US_MAN) Transmitter Preamble Pattern */
	#define   US_MAN_TX_PP_ALL_ONE (0x0u << 8) /**< \brief (US_MAN) The preamble is composed of '1's */
	#define   US_MAN_TX_PP_ALL_ZERO (0x1u << 8) /**< \brief (US_MAN) The preamble is composed of '0's */
	#define   US_MAN_TX_PP_ZERO_ONE (0x2u << 8) /**< \brief (US_MAN) The preamble is composed of '01's */
	#define   US_MAN_TX_PP_ONE_ZERO (0x3u << 8) /**< \brief (US_MAN) The preamble is composed of '10's */
	#define US_MAN_TX_MPOL (0x1u << 12) /**< \brief (US_MAN) Transmitter Manchester Polarity */
	#define US_MAN_RX_PL_Pos 16
	#define US_MAN_RX_PL_Msk (0xfu << US_MAN_RX_PL_Pos) /**< \brief (US_MAN) Receiver Preamble Length */
	#define US_MAN_RX_PL(value) ((US_MAN_RX_PL_Msk & ((value) << US_MAN_RX_PL_Pos)))
	#define US_MAN_RX_PP_Pos 24
	#define US_MAN_RX_PP_Msk (0x3u << US_MAN_RX_PP_Pos) /**< \brief (US_MAN) Receiver Preamble Pattern detected */
	#define   US_MAN_RX_PP_ALL_ONE (0x0u << 24) /**< \brief (US_MAN) The preamble is composed of '1's */
	#define   US_MAN_RX_PP_ALL_ZERO (0x1u << 24) /**< \brief (US_MAN) The preamble is composed of '0's */
	#define   US_MAN_RX_PP_ZERO_ONE (0x2u << 24) /**< \brief (US_MAN) The preamble is composed of '01's */
	#define   US_MAN_RX_PP_ONE_ZERO (0x3u << 24) /**< \brief (US_MAN) The preamble is composed of '10's */
	#define US_MAN_RX_MPOL (0x1u << 28) /**< \brief (US_MAN) Receiver Manchester Polarity */
	#define US_MAN_STUCKTO1 (0x1u << 29) /**< \brief (US_MAN)  */
	#define US_MAN_DRIFT (0x1u << 30) /**< \brief (US_MAN) Drift compensation */

	/* -------- US_WPMR : (USART Offset: 0xE4) Write Protect Mode Register -------- */
	#define US_WPMR_WPEN (0x1u << 0) /**< \brief (US_WPMR) Write Protect Enable */
	#define US_WPMR_WPKEY_Pos 8
	#define US_WPMR_WPKEY_Msk (0xffffffu << US_WPMR_WPKEY_Pos) /**< \brief (US_WPMR) Write Protect KEY */
	#define US_WPMR_WPKEY(value) ((US_WPMR_WPKEY_Msk & ((value) << US_WPMR_WPKEY_Pos)))

	/* -------- US_WPSR : (USART Offset: 0xE8) Write Protect Status Register -------- */
	#define US_WPSR_WPVS (0x1u << 0) /**< \brief (US_WPSR) Write Protect Violation Status */
	#define US_WPSR_WPVSRC_Pos 8
	#define US_WPSR_WPVSRC_Msk (0xffffu << US_WPSR_WPVSRC_Pos) /**< \brief (US_WPSR) Write Protect Violation Source */

	/* -------- US_VERSION : (USART Offset: 0xFC) Version Register -------- */
	#define US_VERSION_VERSION_Pos 0
	#define US_VERSION_VERSION_Msk (0xfffu << US_VERSION_VERSION_Pos) /**< \brief (US_VERSION)  */
	#define US_VERSION_MFN_Pos 16
	#define US_VERSION_MFN_Msk (0x7u << US_VERSION_MFN_Pos) /**< \brief (US_VERSION)  */

	/* -------- US_RPR : (USART Offset: 0x100) Receive Pointer Register -------- */
	#define US_RPR_RXPTR_Pos 0
	#define US_RPR_RXPTR_Msk (0xffffffffu << US_RPR_RXPTR_Pos) /**< \brief (US_RPR) Receive Pointer Register */
	#define US_RPR_RXPTR(value) ((US_RPR_RXPTR_Msk & ((value) << US_RPR_RXPTR_Pos)))

	/* -------- US_RCR : (USART Offset: 0x104) Receive Counter Register -------- */
	#define US_RCR_RXCTR_Pos 0
	#define US_RCR_RXCTR_Msk (0xffffu << US_RCR_RXCTR_Pos) /**< \brief (US_RCR) Receive Counter Register */
	#define US_RCR_RXCTR(value) ((US_RCR_RXCTR_Msk & ((value) << US_RCR_RXCTR_Pos)))

	/* -------- US_TPR : (USART Offset: 0x108) Transmit Pointer Register -------- */
	#define US_TPR_TXPTR_Pos 0
	#define US_TPR_TXPTR_Msk (0xffffffffu << US_TPR_TXPTR_Pos) /**< \brief (US_TPR) Transmit Counter Register */
	#define US_TPR_TXPTR(value) ((US_TPR_TXPTR_Msk & ((value) << US_TPR_TXPTR_Pos)))

	/* -------- US_TCR : (USART Offset: 0x10C) Transmit Counter Register -------- */
	#define US_TCR_TXCTR_Pos 0
	#define US_TCR_TXCTR_Msk (0xffffu << US_TCR_TXCTR_Pos) /**< \brief (US_TCR) Transmit Counter Register */
	#define US_TCR_TXCTR(value) ((US_TCR_TXCTR_Msk & ((value) << US_TCR_TXCTR_Pos)))

	/* -------- US_RNPR : (USART Offset: 0x110) Receive Next Pointer Register -------- */
	#define US_RNPR_RXNPTR_Pos 0
	#define US_RNPR_RXNPTR_Msk (0xffffffffu << US_RNPR_RXNPTR_Pos) /**< \brief (US_RNPR) Receive Next Pointer */
	#define US_RNPR_RXNPTR(value) ((US_RNPR_RXNPTR_Msk & ((value) << US_RNPR_RXNPTR_Pos)))

	/* -------- US_RNCR : (USART Offset: 0x114) Receive Next Counter Register -------- */
	#define US_RNCR_RXNCTR_Pos 0
	#define US_RNCR_RXNCTR_Msk (0xffffu << US_RNCR_RXNCTR_Pos) /**< \brief (US_RNCR) Receive Next Counter */
	#define US_RNCR_RXNCTR(value) ((US_RNCR_RXNCTR_Msk & ((value) << US_RNCR_RXNCTR_Pos)))

	/* -------- US_TNPR : (USART Offset: 0x118) Transmit Next Pointer Register -------- */
	#define US_TNPR_TXNPTR_Pos 0
	#define US_TNPR_TXNPTR_Msk (0xffffffffu << US_TNPR_TXNPTR_Pos) /**< \brief (US_TNPR) Transmit Next Pointer */
	#define US_TNPR_TXNPTR(value) ((US_TNPR_TXNPTR_Msk & ((value) << US_TNPR_TXNPTR_Pos)))

	/* -------- US_TNCR : (USART Offset: 0x11C) Transmit Next Counter Register -------- */
	#define US_TNCR_TXNCTR_Pos 0
	#define US_TNCR_TXNCTR_Msk (0xffffu << US_TNCR_TXNCTR_Pos) /**< \brief (US_TNCR) Transmit Counter Next */
	#define US_TNCR_TXNCTR(value) ((US_TNCR_TXNCTR_Msk & ((value) << US_TNCR_TXNCTR_Pos)))

	/* -------- US_PTCR : (USART Offset: 0x120) Transfer Control Register -------- */
	#define US_PTCR_RXTEN (0x1u << 0) /**< \brief (US_PTCR) Receiver Transfer Enable */
	#define US_PTCR_RXTDIS (0x1u << 1) /**< \brief (US_PTCR) Receiver Transfer Disable */
	#define US_PTCR_TXTEN (0x1u << 8) /**< \brief (US_PTCR) Transmitter Transfer Enable */
	#define US_PTCR_TXTDIS (0x1u << 9) /**< \brief (US_PTCR) Transmitter Transfer Disable */

	/* -------- US_PTSR : (USART Offset: 0x124) Transfer Status Register -------- */
	#define US_PTSR_RXTEN (0x1u << 0) /**< \brief (US_PTSR) Receiver Transfer Enable */
	#define US_PTSR_TXTEN (0x1u << 8) /**< \brief (US_PTSR) Transmitter Transfer Enable */


	#define USART1	((volatile TGPIO*)0x400E0E00)

	// -----------------------------------------------------------------------------
	//  SPI
	// -----------------------------------------------------------------------------
	#define SPI        (*(volatile uint32_t*)0x40008000U) /**< \brief (SPI       ) Base Address */
	#define PDC_SPI    (*(volatile uint32_t*)0x40008100U) /**< \brief (PDC_SPI   ) Base Address */
	#define SPI_CR     (*(volatile uint32_t*)0x40008000U) /**< \brief (SPI) Control Register */
	#define SPI_MR     (*(volatile uint32_t*)0x40008004U) /**< \brief (SPI) Mode Register */
	#define SPI_RDR    (*(volatile uint32_t*)0x40008008U) /**< \brief (SPI) Receive Data Register */
	#define SPI_TDR    (*(volatile uint32_t*)0x4000800CU) /**< \brief (SPI) Transmit Data Register */
	#define SPI_SR     (*(volatile uint32_t*)0x40008010U) /**< \brief (SPI) Status Register */
	#define SPI_IER    (*(volatile uint32_t*)0x40008014U) /**< \brief (SPI) Interrupt Enable Register */
	#define SPI_IDR    (*(volatile uint32_t*)0x40008018U) /**< \brief (SPI) Interrupt Disable Register */
	#define SPI_IMR    (*(volatile uint32_t*)0x4000801CU) /**< \brief (SPI) Interrupt Mask Register */
	#define SPI_CSR0   (*(volatile uint32_t*)0x40008030U) /**< \brief (SPI) Chip Select Register */
	#define SPI_CSR1   (*(volatile uint32_t*)0x40008034U) /**< \brief (SPI) Chip Select Register */
	#define SPI_CSR2   (*(volatile uint32_t*)0x40008038U) /**< \brief (SPI) Chip Select Register */
	#define SPI_CSR3   (*(volatile uint32_t*)0x4000803CU) /**< \brief (SPI) Chip Select Register */
	#define SPI_WPMR   (*(volatile uint32_t*)0x400080E4U) /**< \brief (SPI) Write Protection Control Register */
	#define SPI_WPS    (*(volatile uint32_t*)0x400080E8U) /**< \brief (SPI) Write Protection Status Register */
	#define SPI_RPR    (*(volatile uint32_t*)0x40008100U) /**< \brief (SPI) Receive Pointer Register */
	#define SPI_RCR    (*(volatile uint32_t*)0x40008104U) /**< \brief (SPI) Receive Counter Register */
	#define SPI_TPR    (*(volatile uint32_t*)0x40008108U) /**< \brief (SPI) Transmit Pointer Register */
	#define SPI_TCR    (*(volatile uint32_t*)0x4000810CU) /**< \brief (SPI) Transmit Counter Register */
	#define SPI_RNPR   (*(volatile uint32_t*)0x40008110U) /**< \brief (SPI) Receive Next Pointer Register */
	#define SPI_RNCR   (*(volatile uint32_t*)0x40008114U) /**< \brief (SPI) Receive Next Counter Register */
	#define SPI_TNPR   (*(volatile uint32_t*)0x40008118U) /**< \brief (SPI) Transmit Next Pointer Register */
	#define SPI_TNCR   (*(volatile uint32_t*)0x4000811CU) /**< \brief (SPI) Transmit Next Counter Register */
	#define SPI_PTCR   (*(volatile uint32_t*)0x40008120U) /**< \brief (SPI) Transfer Control Register */
	#define SPI_PTSR   (*(volatile uint32_t*)0x40008124U) /**< \brief (SPI) Transfer Status Register */

	/* -------- SPI_CR : (SPI Offset: 0x00) Control Register -------- */
	#define SPI_CR_SPIEN (0x1u << 0) /**< \brief (SPI_CR) SPI Enable */
	#define SPI_CR_SPIDIS (0x1u << 1) /**< \brief (SPI_CR) SPI Disable */
	#define SPI_CR_SWRST (0x1u << 7) /**< \brief (SPI_CR) SPI Software Reset */
	#define SPI_CR_LASTXFER (0x1u << 24) /**< \brief (SPI_CR) Last Transfer */

	/* -------- SPI_MR : (SPI Offset: 0x04) Mode Register -------- */
	#define SPI_MR_MSTR (0x1u << 0) /**< \brief (SPI_MR) Master/Slave Mode */
	#define SPI_MR_PS (0x1u << 1) /**< \brief (SPI_MR) Peripheral Select */
	#define SPI_MR_PCSDEC (0x1u << 2) /**< \brief (SPI_MR) Chip Select Decode */
	#define SPI_MR_MODFDIS (0x1u << 4) /**< \brief (SPI_MR) Mode Fault Detection */
	#define SPI_MR_WDRBT (0x1u << 5) /**< \brief (SPI_MR) Wait Data Read Before Transfer */
	#define SPI_MR_LLB (0x1u << 7) /**< \brief (SPI_MR) Local Loopback Enable */
	#define SPI_MR_PCS_Pos 16
	#define SPI_MR_PCS_Msk (0xfu << SPI_MR_PCS_Pos) /**< \brief (SPI_MR) Peripheral Chip Select */
	#define SPI_MR_PCS(value) ((SPI_MR_PCS_Msk & ((value) << SPI_MR_PCS_Pos)))
	#define SPI_MR_DLYBCS_Pos 24
	#define SPI_MR_DLYBCS_Msk (0xffu << SPI_MR_DLYBCS_Pos) /**< \brief (SPI_MR) Delay Between Chip Selects */
	#define SPI_MR_DLYBCS(value) ((SPI_MR_DLYBCS_Msk & ((value) << SPI_MR_DLYBCS_Pos)))

	/* -------- SPI_RDR : (SPI Offset: 0x08) Receive Data Register -------- */
	#define SPI_RDR_RD_Pos 0
	#define SPI_RDR_RD_Msk (0xffffu << SPI_RDR_RD_Pos) /**< \brief (SPI_RDR) Receive Data */
	#define SPI_RDR_PCS_Pos 16
	#define SPI_RDR_PCS_Msk (0xfu << SPI_RDR_PCS_Pos) /**< \brief (SPI_RDR) Peripheral Chip Select */

	/* -------- SPI_TDR : (SPI Offset: 0x0C) Transmit Data Register -------- */
	#define SPI_TDR_TD_Pos 0
	#define SPI_TDR_TD_Msk (0xffffu << SPI_TDR_TD_Pos) /**< \brief (SPI_TDR) Transmit Data */
	#define SPI_TDR_TD(value) ((SPI_TDR_TD_Msk & ((value) << SPI_TDR_TD_Pos)))
	#define SPI_TDR_PCS_Pos 16
	#define SPI_TDR_PCS_Msk (0xfu << SPI_TDR_PCS_Pos) /**< \brief (SPI_TDR) Peripheral Chip Select */
	#define SPI_TDR_PCS(value) ((SPI_TDR_PCS_Msk & ((value) << SPI_TDR_PCS_Pos)))
	#define SPI_TDR_LASTXFER (0x1u << 24) /**< \brief (SPI_TDR) Last Transfer */

	/* -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
	#define SPI_SR_RDRF (0x1u << 0) /**< \brief (SPI_SR) Receive Data Register Full */
	#define SPI_SR_TDRE (0x1u << 1) /**< \brief (SPI_SR) Transmit Data Register Empty */
	#define SPI_SR_MODF (0x1u << 2) /**< \brief (SPI_SR) Mode Fault Error */
	#define SPI_SR_OVRES (0x1u << 3) /**< \brief (SPI_SR) Overrun Error Status */
	#define SPI_SR_ENDRX (0x1u << 4) /**< \brief (SPI_SR) End of RX buffer */
	#define SPI_SR_ENDTX (0x1u << 5) /**< \brief (SPI_SR) End of TX buffer */
	#define SPI_SR_RXBUFF (0x1u << 6) /**< \brief (SPI_SR) RX Buffer Full */
	#define SPI_SR_TXBUFE (0x1u << 7) /**< \brief (SPI_SR) TX Buffer Empty */
	#define SPI_SR_NSSR (0x1u << 8) /**< \brief (SPI_SR) NSS Rising */
	#define SPI_SR_TXEMPTY (0x1u << 9) /**< \brief (SPI_SR) Transmission Registers Empty */
	#define SPI_SR_UNDES (0x1u << 10) /**< \brief (SPI_SR) Underrun Error Status (Slave Mode Only) */
	#define SPI_SR_SPIENS (0x1u << 16) /**< \brief (SPI_SR) SPI Enable Status */

	/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
	#define SPI_IER_RDRF (0x1u << 0) /**< \brief (SPI_IER) Receive Data Register Full Interrupt Enable */
	#define SPI_IER_TDRE (0x1u << 1) /**< \brief (SPI_IER) SPI Transmit Data Register Empty Interrupt Enable */
	#define SPI_IER_MODF (0x1u << 2) /**< \brief (SPI_IER) Mode Fault Error Interrupt Enable */
	#define SPI_IER_OVRES (0x1u << 3) /**< \brief (SPI_IER) Overrun Error Interrupt Enable */
	#define SPI_IER_ENDRX (0x1u << 4) /**< \brief (SPI_IER) End of Receive Buffer Interrupt Enable */
	#define SPI_IER_ENDTX (0x1u << 5) /**< \brief (SPI_IER) End of Transmit Buffer Interrupt Enable */
	#define SPI_IER_RXBUFF (0x1u << 6) /**< \brief (SPI_IER) Receive Buffer Full Interrupt Enable */
	#define SPI_IER_TXBUFE (0x1u << 7) /**< \brief (SPI_IER) Transmit Buffer Empty Interrupt Enable */
	#define SPI_IER_NSSR (0x1u << 8) /**< \brief (SPI_IER) NSS Rising Interrupt Enable */
	#define SPI_IER_TXEMPTY (0x1u << 9) /**< \brief (SPI_IER) Transmission Registers Empty Enable */
	#define SPI_IER_UNDES (0x1u << 10) /**< \brief (SPI_IER) Underrun Error Interrupt Enable */

	/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
	#define SPI_IDR_RDRF (0x1u << 0) /**< \brief (SPI_IDR) Receive Data Register Full Interrupt Disable */
	#define SPI_IDR_TDRE (0x1u << 1) /**< \brief (SPI_IDR) SPI Transmit Data Register Empty Interrupt Disable */
	#define SPI_IDR_MODF (0x1u << 2) /**< \brief (SPI_IDR) Mode Fault Error Interrupt Disable */
	#define SPI_IDR_OVRES (0x1u << 3) /**< \brief (SPI_IDR) Overrun Error Interrupt Disable */
	#define SPI_IDR_ENDRX (0x1u << 4) /**< \brief (SPI_IDR) End of Receive Buffer Interrupt Disable */
	#define SPI_IDR_ENDTX (0x1u << 5) /**< \brief (SPI_IDR) End of Transmit Buffer Interrupt Disable */
	#define SPI_IDR_RXBUFF (0x1u << 6) /**< \brief (SPI_IDR) Receive Buffer Full Interrupt Disable */
	#define SPI_IDR_TXBUFE (0x1u << 7) /**< \brief (SPI_IDR) Transmit Buffer Empty Interrupt Disable */
	#define SPI_IDR_NSSR (0x1u << 8) /**< \brief (SPI_IDR) NSS Rising Interrupt Disable */
	#define SPI_IDR_TXEMPTY (0x1u << 9) /**< \brief (SPI_IDR) Transmission Registers Empty Disable */
	#define SPI_IDR_UNDES (0x1u << 10) /**< \brief (SPI_IDR) Underrun Error Interrupt Disable */

	/* -------- SPI_IMR : (SPI Offset: 0x1C) Interrupt Mask Register -------- */
	#define SPI_IMR_RDRF (0x1u << 0) /**< \brief (SPI_IMR) Receive Data Register Full Interrupt Mask */
	#define SPI_IMR_TDRE (0x1u << 1) /**< \brief (SPI_IMR) SPI Transmit Data Register Empty Interrupt Mask */
	#define SPI_IMR_MODF (0x1u << 2) /**< \brief (SPI_IMR) Mode Fault Error Interrupt Mask */
	#define SPI_IMR_OVRES (0x1u << 3) /**< \brief (SPI_IMR) Overrun Error Interrupt Mask */
	#define SPI_IMR_ENDRX (0x1u << 4) /**< \brief (SPI_IMR) End of Receive Buffer Interrupt Mask */
	#define SPI_IMR_ENDTX (0x1u << 5) /**< \brief (SPI_IMR) End of Transmit Buffer Interrupt Mask */
	#define SPI_IMR_RXBUFF (0x1u << 6) /**< \brief (SPI_IMR) Receive Buffer Full Interrupt Mask */
	#define SPI_IMR_TXBUFE (0x1u << 7) /**< \brief (SPI_IMR) Transmit Buffer Empty Interrupt Mask */
	#define SPI_IMR_NSSR (0x1u << 8) /**< \brief (SPI_IMR) NSS Rising Interrupt Mask */
	#define SPI_IMR_TXEMPTY (0x1u << 9) /**< \brief (SPI_IMR) Transmission Registers Empty Mask */
	#define SPI_IMR_UNDES (0x1u << 10) /**< \brief (SPI_IMR) Underrun Error Interrupt Mask */

	/* -------- SPI_CSR[4] : (SPI Offset: 0x30) Chip Select Register -------- */
	#define SPI_CSR_CPOL (0x1u << 0) /**< \brief (SPI_CSR[4]) Clock Polarity */
	#define SPI_CSR_NCPHA (0x1u << 1) /**< \brief (SPI_CSR[4]) Clock Phase */
	#define SPI_CSR_CSNAAT (0x1u << 2) /**< \brief (SPI_CSR[4]) Chip Select Not Active After Transfer (Ignored if CSAAT = 1) */
	#define SPI_CSR_CSAAT (0x1u << 3) /**< \brief (SPI_CSR[4]) Chip Select Not Active After Transfer (Ignored if CSAAT = 1) */
	#define SPI_CSR_BITS_Pos 4
	#define SPI_CSR_BITS_Msk (0xfu << SPI_CSR_BITS_Pos) /**< \brief (SPI_CSR[4]) Bits Per Transfer */
	#define   SPI_CSR_BITS_8_BIT (0x0u << 4) /**< \brief (SPI_CSR[4]) 8 bits for transfer */
	#define   SPI_CSR_BITS_9_BIT (0x1u << 4) /**< \brief (SPI_CSR[4]) 9 bits for transfer */
	#define   SPI_CSR_BITS_10_BIT (0x2u << 4) /**< \brief (SPI_CSR[4]) 10 bits for transfer */
	#define   SPI_CSR_BITS_11_BIT (0x3u << 4) /**< \brief (SPI_CSR[4]) 11 bits for transfer */
	#define   SPI_CSR_BITS_12_BIT (0x4u << 4) /**< \brief (SPI_CSR[4]) 12 bits for transfer */
	#define   SPI_CSR_BITS_13_BIT (0x5u << 4) /**< \brief (SPI_CSR[4]) 13 bits for transfer */
	#define   SPI_CSR_BITS_14_BIT (0x6u << 4) /**< \brief (SPI_CSR[4]) 14 bits for transfer */
	#define   SPI_CSR_BITS_15_BIT (0x7u << 4) /**< \brief (SPI_CSR[4]) 15 bits for transfer */
	#define   SPI_CSR_BITS_16_BIT (0x8u << 4) /**< \brief (SPI_CSR[4]) 16 bits for transfer */
	#define SPI_CSR_SCBR_Pos 8
	#define SPI_CSR_SCBR_Msk (0xffu << SPI_CSR_SCBR_Pos) /**< \brief (SPI_CSR[4]) Serial Clock Baud Rate */
	#define SPI_CSR_SCBR(value) ((SPI_CSR_SCBR_Msk & ((value) << SPI_CSR_SCBR_Pos)))
	#define SPI_CSR_DLYBS_Pos 16
	#define SPI_CSR_DLYBS_Msk (0xffu << SPI_CSR_DLYBS_Pos) /**< \brief (SPI_CSR[4]) Delay Before SPCK */
	#define SPI_CSR_DLYBS(value) ((SPI_CSR_DLYBS_Msk & ((value) << SPI_CSR_DLYBS_Pos)))
	#define SPI_CSR_DLYBCT_Pos 24
	#define SPI_CSR_DLYBCT_Msk (0xffu << SPI_CSR_DLYBCT_Pos) /**< \brief (SPI_CSR[4]) Delay Between Consecutive Transfers */
	#define SPI_CSR_DLYBCT(value) ((SPI_CSR_DLYBCT_Msk & ((value) << SPI_CSR_DLYBCT_Pos)))

	/* -------- SPI_WPMR : (SPI Offset: 0xE4) Write Protection Control Register -------- */
	#define SPI_WPMR_WPEN (0x1u << 0) /**< \brief (SPI_WPMR) Write Protection Enable */
	#define SPI_WPMR_WPKEY_Pos 8
	#define SPI_WPMR_WPKEY_Msk (0xffffffu << SPI_WPMR_WPKEY_Pos) /**< \brief (SPI_WPMR) Write Protection Key Password */
	#define SPI_WPMR_WPKEY(value) ((SPI_WPMR_WPKEY_Msk & ((value) << SPI_WPMR_WPKEY_Pos)))

	/* -------- SPI_WPSR : (SPI Offset: 0xE8) Write Protection Status Register -------- */
	#define SPI_WPSR_WPVS (0x1u << 0) /**< \brief (SPI_WPSR) Write Protection Violation Status */
	#define SPI_WPSR_WPVS_Pos 0
	#define SPI_WPSR_WPVS_Msk (0x1u << SPI_WPSR_WPVS_Pos) /**< \brief (SPI_WPSR) Write Protection Violation Status */
	#define SPI_WPSR_WPVSRC_Pos 8
	#define SPI_WPSR_WPVSRC_Msk (0xffu << SPI_WPSR_WPVSRC_Pos) /**< \brief (SPI_WPSR) Write Protection Violation Source */

	/* -------- SPI_RPR : (SPI Offset: 0x100) Receive Pointer Register -------- */
	#define SPI_RPR_RXPTR_Pos 0
	#define SPI_RPR_RXPTR_Msk (0xffffffffu << SPI_RPR_RXPTR_Pos) /**< \brief (SPI_RPR) Receive Pointer Register */
	#define SPI_RPR_RXPTR(value) ((SPI_RPR_RXPTR_Msk & ((value) << SPI_RPR_RXPTR_Pos)))

	/* -------- SPI_RCR : (SPI Offset: 0x104) Receive Counter Register -------- */
	#define SPI_RCR_RXCTR_Pos 0
	#define SPI_RCR_RXCTR_Msk (0xffffu << SPI_RCR_RXCTR_Pos) /**< \brief (SPI_RCR) Receive Counter Register */
	#define SPI_RCR_RXCTR(value) ((SPI_RCR_RXCTR_Msk & ((value) << SPI_RCR_RXCTR_Pos)))

	/* -------- SPI_TPR : (SPI Offset: 0x108) Transmit Pointer Register -------- */
	#define SPI_TPR_TXPTR_Pos 0
	#define SPI_TPR_TXPTR_Msk (0xffffffffu << SPI_TPR_TXPTR_Pos) /**< \brief (SPI_TPR) Transmit Counter Register */
	#define SPI_TPR_TXPTR(value) ((SPI_TPR_TXPTR_Msk & ((value) << SPI_TPR_TXPTR_Pos)))

	/* -------- SPI_TCR : (SPI Offset: 0x10C) Transmit Counter Register -------- */
	#define SPI_TCR_TXCTR_Pos 0
	#define SPI_TCR_TXCTR_Msk (0xffffu << SPI_TCR_TXCTR_Pos) /**< \brief (SPI_TCR) Transmit Counter Register */
	#define SPI_TCR_TXCTR(value) ((SPI_TCR_TXCTR_Msk & ((value) << SPI_TCR_TXCTR_Pos)))

	/* -------- SPI_RNPR : (SPI Offset: 0x110) Receive Next Pointer Register -------- */
	#define SPI_RNPR_RXNPTR_Pos 0
	#define SPI_RNPR_RXNPTR_Msk (0xffffffffu << SPI_RNPR_RXNPTR_Pos) /**< \brief (SPI_RNPR) Receive Next Pointer */
	#define SPI_RNPR_RXNPTR(value) ((SPI_RNPR_RXNPTR_Msk & ((value) << SPI_RNPR_RXNPTR_Pos)))

	/* -------- SPI_RNCR : (SPI Offset: 0x114) Receive Next Counter Register -------- */
	#define SPI_RNCR_RXNCTR_Pos 0
	#define SPI_RNCR_RXNCTR_Msk (0xffffu << SPI_RNCR_RXNCTR_Pos) /**< \brief (SPI_RNCR) Receive Next Counter */
	#define SPI_RNCR_RXNCTR(value) ((SPI_RNCR_RXNCTR_Msk & ((value) << SPI_RNCR_RXNCTR_Pos)))

	/* -------- SPI_TNPR : (SPI Offset: 0x118) Transmit Next Pointer Register -------- */
	#define SPI_TNPR_TXNPTR_Pos 0
	#define SPI_TNPR_TXNPTR_Msk (0xffffffffu << SPI_TNPR_TXNPTR_Pos) /**< \brief (SPI_TNPR) Transmit Next Pointer */
	#define SPI_TNPR_TXNPTR(value) ((SPI_TNPR_TXNPTR_Msk & ((value) << SPI_TNPR_TXNPTR_Pos)))

	/* -------- SPI_TNCR : (SPI Offset: 0x11C) Transmit Next Counter Register -------- */
	#define SPI_TNCR_TXNCTR_Pos 0
	#define SPI_TNCR_TXNCTR_Msk (0xffffu << SPI_TNCR_TXNCTR_Pos) /**< \brief (SPI_TNCR) Transmit Counter Next */
	#define SPI_TNCR_TXNCTR(value) ((SPI_TNCR_TXNCTR_Msk & ((value) << SPI_TNCR_TXNCTR_Pos)))

	/* -------- SPI_PTCR : (SPI Offset: 0x120) Transfer Control Register -------- */
	#define SPI_PTCR_RXTEN (0x1u << 0) /**< \brief (SPI_PTCR) Receiver Transfer Enable */
	#define SPI_PTCR_RXTDIS (0x1u << 1) /**< \brief (SPI_PTCR) Receiver Transfer Disable */
	#define SPI_PTCR_TXTEN (0x1u << 8) /**< \brief (SPI_PTCR) Transmitter Transfer Enable */
	#define SPI_PTCR_TXTDIS (0x1u << 9) /**< \brief (SPI_PTCR) Transmitter Transfer Disable */

	/* -------- SPI_PTSR : (SPI Offset: 0x124) Transfer Status Register -------- */
	#define SPI_PTSR_RXTEN (0x1u << 0) /**< \brief (SPI_PTSR) Receiver Transfer Enable */
	#define SPI_PTSR_TXTEN (0x1u << 8) /**< \brief (SPI_PTSR) Transmitter Transfer Enable */

	// -----------------------------------------------------------------------------
	//  TIMERS
	// -----------------------------------------------------------------------------
	#define TC0_CCR0  (*(volatile uint32_t*)0x40010000U) /**< \brief (TC0) Channel Control Register (channel = 0) */
	#define TC0_CMR0  (*(RwReg*)0x40010004U) /**< \brief (TC0) Channel Mode Register (channel = 0) */
	#define TC0_SMMR0 (*(RwReg*)0x40010008U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 0) */
	#define TC0_CV0   (*(RoReg*)0x40010010U) /**< \brief (TC0) Counter Value (channel = 0) */
	#define TC0_RA0   (*(RwReg*)0x40010014U) /**< \brief (TC0) Register A (channel = 0) */
	#define TC0_RB0   (*(RwReg*)0x40010018U) /**< \brief (TC0) Register B (channel = 0) */
	#define TC0_RC0   (*(RwReg*)0x4001001CU) /**< \brief (TC0) Register C (channel = 0) */
	#define TC0_SR0   (*(RoReg*)0x40010020U) /**< \brief (TC0) Status Register (channel = 0) */
	#define TC0_IER0  (*(volatile uint32_t*)0x40010024U) /**< \brief (TC0) Interrupt Enable Register (channel = 0) */
	#define TC0_IDR0  (*(volatile uint32_t*)0x40010028U) /**< \brief (TC0) Interrupt Disable Register (channel = 0) */
	#define TC0_IMR0  (*(RoReg*)0x4001002CU) /**< \brief (TC0) Interrupt Mask Register (channel = 0) */
	#define TC0_CCR1  (*(volatile uint32_t*)0x40010040U) /**< \brief (TC0) Channel Control Register (channel = 1) */
	#define TC0_CMR1  (*(RwReg*)0x40010044U) /**< \brief (TC0) Channel Mode Register (channel = 1) */
	#define TC0_SMMR1 (*(RwReg*)0x40010048U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 1) */
	#define TC0_CV1   (*(RoReg*)0x40010050U) /**< \brief (TC0) Counter Value (channel = 1) */
	#define TC0_RA1   (*(RwReg*)0x40010054U) /**< \brief (TC0) Register A (channel = 1) */
	#define TC0_RB1   (*(RwReg*)0x40010058U) /**< \brief (TC0) Register B (channel = 1) */
	#define TC0_RC1   (*(RwReg*)0x4001005CU) /**< \brief (TC0) Register C (channel = 1) */
	#define TC0_SR1   (*(RoReg*)0x40010060U) /**< \brief (TC0) Status Register (channel = 1) */
	#define TC0_IER1  (*(volatile uint32_t*)0x40010064U) /**< \brief (TC0) Interrupt Enable Register (channel = 1) */
	#define TC0_IDR1  (*(volatile uint32_t*)0x40010068U) /**< \brief (TC0) Interrupt Disable Register (channel = 1) */
	#define TC0_IMR1  (*(RoReg*)0x4001006CU) /**< \brief (TC0) Interrupt Mask Register (channel = 1) */
	#define TC0_CCR2  (*(volatile uint32_t*)0x40010080U) /**< \brief (TC0) Channel Control Register (channel = 2) */
	#define TC0_CMR2  (*(RwReg*)0x40010084U) /**< \brief (TC0) Channel Mode Register (channel = 2) */
	#define TC0_SMMR2 (*(RwReg*)0x40010088U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 2) */
	#define TC0_CV2   (*(RoReg*)0x40010090U) /**< \brief (TC0) Counter Value (channel = 2) */
	#define TC0_RA2   (*(RwReg*)0x40010094U) /**< \brief (TC0) Register A (channel = 2) */
	#define TC0_RB2   (*(RwReg*)0x40010098U) /**< \brief (TC0) Register B (channel = 2) */
	#define TC0_RC2   (*(RwReg*)0x4001009CU) /**< \brief (TC0) Register C (channel = 2) */
	#define TC0_SR2   (*(RoReg*)0x400100A0U) /**< \brief (TC0) Status Register (channel = 2) */
	#define TC0_IER2  (*(volatile uint32_t*)0x400100A4U) /**< \brief (TC0) Interrupt Enable Register (channel = 2) */
	#define TC0_IDR2  (*(volatile uint32_t*)0x400100A8U) /**< \brief (TC0) Interrupt Disable Register (channel = 2) */
	#define TC0_IMR2  (*(RoReg*)0x400100ACU) /**< \brief (TC0) Interrupt Mask Register (channel = 2) */
	#define TC0_BCR   (*(volatile uint32_t*)0x400100C0U) /**< \brief (TC0) Block Control Register */
	#define TC0_BMR   (*(RwReg*)0x400100C4U) /**< \brief (TC0) Block Mode Register */
	#define TC0_QIER  (*(volatile uint32_t*)0x400100C8U) /**< \brief (TC0) QDEC Interrupt Enable Register */
	#define TC0_QIDR  (*(volatile uint32_t*)0x400100CCU) /**< \brief (TC0) QDEC Interrupt Disable Register */
	#define TC0_QIMR  (*(RoReg*)0x400100D0U) /**< \brief (TC0) QDEC Interrupt Mask Register */
	#define TC0_QISR  (*(RoReg*)0x400100D4U) /**< \brief (TC0) QDEC Interrupt Status Register */
	#define TC0_FMR   (*(RwReg*)0x400100D8U) /**< \brief (TC0) Fault Mode Register */
	#define TC0_WPMR  (*(RwReg*)0x400100E4U) /**< \brief (TC0) Write Protect Mode Register */

	#define TC0        ((Tc     *)0x40010000U) /**< \brief (TC0       ) Base Address */

	#define TC1_CCR0  (*(WoReg*)0x40014000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
	#define TC1_CMR0  (*(RwReg*)0x40014004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
	#define TC1_SMMR0 (*(RwReg*)0x40014008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
	#define TC1_CV0   (*(RoReg*)0x40014010U) /**< \brief (TC1) Counter Value (channel = 0) */
	#define TC1_RA0   (*(RwReg*)0x40014014U) /**< \brief (TC1) Register A (channel = 0) */
	#define TC1_RB0   (*(RwReg*)0x40014018U) /**< \brief (TC1) Register B (channel = 0) */
	#define TC1_RC0   (*(RwReg*)0x4001401CU) /**< \brief (TC1) Register C (channel = 0) */
	#define TC1_SR0   (*(RoReg*)0x40014020U) /**< \brief (TC1) Status Register (channel = 0) */
	#define TC1_IER0  (*(WoReg*)0x40014024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
	#define TC1_IDR0  (*(WoReg*)0x40014028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
	#define TC1_IMR0  (*(RoReg*)0x4001402CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
	#define TC1_CCR1  (*(WoReg*)0x40014040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
	#define TC1_CMR1  (*(RwReg*)0x40014044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
	#define TC1_SMMR1 (*(RwReg*)0x40014048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
	#define TC1_CV1   (*(RoReg*)0x40014050U) /**< \brief (TC1) Counter Value (channel = 1) */
	#define TC1_RA1   (*(RwReg*)0x40014054U) /**< \brief (TC1) Register A (channel = 1) */
	#define TC1_RB1   (*(RwReg*)0x40014058U) /**< \brief (TC1) Register B (channel = 1) */
	#define TC1_RC1   (*(RwReg*)0x4001405CU) /**< \brief (TC1) Register C (channel = 1) */
	#define TC1_SR1   (*(RoReg*)0x40014060U) /**< \brief (TC1) Status Register (channel = 1) */
	#define TC1_IER1  (*(WoReg*)0x40014064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
	#define TC1_IDR1  (*(WoReg*)0x40014068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
	#define TC1_IMR1  (*(RoReg*)0x4001406CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
	#define TC1_CCR2  (*(WoReg*)0x40014080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
	#define TC1_CMR2  (*(RwReg*)0x40014084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
	#define TC1_SMMR2 (*(RwReg*)0x40014088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
	#define TC1_CV2   (*(RoReg*)0x40014090U) /**< \brief (TC1) Counter Value (channel = 2) */
	#define TC1_RA2   (*(RwReg*)0x40014094U) /**< \brief (TC1) Register A (channel = 2) */
	#define TC1_RB2   (*(RwReg*)0x40014098U) /**< \brief (TC1) Register B (channel = 2) */
	#define TC1_RC2   (*(RwReg*)0x4001409CU) /**< \brief (TC1) Register C (channel = 2) */
	#define TC1_SR2   (*(RoReg*)0x400140A0U) /**< \brief (TC1) Status Register (channel = 2) */
	#define TC1_IER2  (*(WoReg*)0x400140A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
	#define TC1_IDR2  (*(WoReg*)0x400140A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
	#define TC1_IMR2  (*(RoReg*)0x400140ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
	#define TC1_BCR   (*(WoReg*)0x400140C0U) /**< \brief (TC1) Block Control Register */
	#define TC1_BMR   (*(RwReg*)0x400140C4U) /**< \brief (TC1) Block Mode Register */
	#define TC1_QIER  (*(WoReg*)0x400140C8U) /**< \brief (TC1) QDEC Interrupt Enable Register */
	#define TC1_QIDR  (*(WoReg*)0x400140CCU) /**< \brief (TC1) QDEC Interrupt Disable Register */
	#define TC1_QIMR  (*(RoReg*)0x400140D0U) /**< \brief (TC1) QDEC Interrupt Mask Register */
	#define TC1_QISR  (*(RoReg*)0x400140D4U) /**< \brief (TC1) QDEC Interrupt Status Register */
	#define TC1_FMR   (*(RwReg*)0x400140D8U) /**< \brief (TC1) Fault Mode Register */
	#define TC1_WPMR  (*(RwReg*)0x400140E4U) /**< \brief (TC1) Write Protect Mode Register */

	#define TC_CCR_CLKEN (0x1u << 0) /**< \brief (TC_CCR) Counter Clock Enable Command */
	#define TC_CCR_CLKDIS (0x1u << 1) /**< \brief (TC_CCR) Counter Clock Disable Command */
	#define TC_CCR_SWTRG (0x1u << 2) /**< \brief (TC_CCR) Software Trigger Command */

	/* -------- TC_CMR : (TC Offset: N/A) Channel Mode Register -------- */
	#define TC_CMR_TCCLKS_Pos 0
	#define TC_CMR_TCCLKS_Msk (0x7u << TC_CMR_TCCLKS_Pos) /**< \brief (TC_CMR) Clock Selection */
	#define   TC_CMR_TCCLKS_TIMER_CLOCK1 (0x0u << 0) /**< \brief (TC_CMR) Clock selected: TCLK1 */
	#define   TC_CMR_TCCLKS_TIMER_CLOCK2 (0x1u << 0) /**< \brief (TC_CMR) Clock selected: TCLK2 */
	#define   TC_CMR_TCCLKS_TIMER_CLOCK3 (0x2u << 0) /**< \brief (TC_CMR) Clock selected: TCLK3 */
	#define   TC_CMR_TCCLKS_TIMER_CLOCK4 (0x3u << 0) /**< \brief (TC_CMR) Clock selected: TCLK4 */
	#define   TC_CMR_TCCLKS_TIMER_CLOCK5 (0x4u << 0) /**< \brief (TC_CMR) Clock selected: TCLK5 */
	#define   TC_CMR_TCCLKS_XC0 (0x5u << 0) /**< \brief (TC_CMR) Clock selected: XC0 */
	#define   TC_CMR_TCCLKS_XC1 (0x6u << 0) /**< \brief (TC_CMR) Clock selected: XC1 */
	#define   TC_CMR_TCCLKS_XC2 (0x7u << 0) /**< \brief (TC_CMR) Clock selected: XC2 */
	#define TC_CMR_CLKI (0x1u << 3) /**< \brief (TC_CMR) Clock Invert */
	#define TC_CMR_BURST_Pos 4
	#define TC_CMR_BURST_Msk (0x3u << TC_CMR_BURST_Pos) /**< \brief (TC_CMR) Burst Signal Selection */
	#define   TC_CMR_BURST_NONE (0x0u << 4) /**< \brief (TC_CMR) The clock is not gated by an external signal. */
	#define   TC_CMR_BURST_XC0 (0x1u << 4) /**< \brief (TC_CMR) XC0 is ANDed with the selected clock. */
	#define   TC_CMR_BURST_XC1 (0x2u << 4) /**< \brief (TC_CMR) XC1 is ANDed with the selected clock. */
	#define   TC_CMR_BURST_XC2 (0x3u << 4) /**< \brief (TC_CMR) XC2 is ANDed with the selected clock. */
	#define TC_CMR_LDBSTOP (0x1u << 6) /**< \brief (TC_CMR) Counter Clock Stopped with RB Loading */
	#define TC_CMR_LDBDIS (0x1u << 7) /**< \brief (TC_CMR) Counter Clock Disable with RB Loading */
	#define TC_CMR_ETRGEDG_Pos 8
	#define TC_CMR_ETRGEDG_Msk (0x3u << TC_CMR_ETRGEDG_Pos) /**< \brief (TC_CMR) External Trigger Edge Selection */
	#define   TC_CMR_ETRGEDG_NONE (0x0u << 8) /**< \brief (TC_CMR) The clock is not gated by an external signal. */
	#define   TC_CMR_ETRGEDG_RISING (0x1u << 8) /**< \brief (TC_CMR) Rising edge */
	#define   TC_CMR_ETRGEDG_FALLING (0x2u << 8) /**< \brief (TC_CMR) Falling edge */
	#define   TC_CMR_ETRGEDG_EDGE (0x3u << 8) /**< \brief (TC_CMR) Each edge */
	#define TC_CMR_ABETRG (0x1u << 10) /**< \brief (TC_CMR) TIOA or TIOB External Trigger Selection */
	#define TC_CMR_CPCTRG (0x1u << 14) /**< \brief (TC_CMR) RC Compare Trigger Enable */
	#define TC_CMR_WAVE (0x1u << 15) /**< \brief (TC_CMR) Waveform Mode */
	#define TC_CMR_LDRA_Pos 16
	#define TC_CMR_LDRA_Msk (0x3u << TC_CMR_LDRA_Pos) /**< \brief (TC_CMR) RA Loading Edge Selection */
	#define   TC_CMR_LDRA_NONE (0x0u << 16) /**< \brief (TC_CMR) None */
	#define   TC_CMR_LDRA_RISING (0x1u << 16) /**< \brief (TC_CMR) Rising edge of TIOA */
	#define   TC_CMR_LDRA_FALLING (0x2u << 16) /**< \brief (TC_CMR) Falling edge of TIOA */
	#define   TC_CMR_LDRA_EDGE (0x3u << 16) /**< \brief (TC_CMR) Each edge of TIOA */
	#define TC_CMR_LDRB_Pos 18
	#define TC_CMR_LDRB_Msk (0x3u << TC_CMR_LDRB_Pos) /**< \brief (TC_CMR) RB Loading Edge Selection */
	#define   TC_CMR_LDRB_NONE (0x0u << 18) /**< \brief (TC_CMR) None */
	#define   TC_CMR_LDRB_RISING (0x1u << 18) /**< \brief (TC_CMR) Rising edge of TIOA */
	#define   TC_CMR_LDRB_FALLING (0x2u << 18) /**< \brief (TC_CMR) Falling edge of TIOA */
	#define   TC_CMR_LDRB_EDGE (0x3u << 18) /**< \brief (TC_CMR) Each edge of TIOA */
	#define TC_CMR_CPCSTOP (0x1u << 6) /**< \brief (TC_CMR) Counter Clock Stopped with RC Compare */
	#define TC_CMR_CPCDIS (0x1u << 7) /**< \brief (TC_CMR) Counter Clock Disable with RC Compare */
	#define TC_CMR_EEVTEDG_Pos 8
	#define TC_CMR_EEVTEDG_Msk (0x3u << TC_CMR_EEVTEDG_Pos) /**< \brief (TC_CMR) External Event Edge Selection */
	#define   TC_CMR_EEVTEDG_NONE (0x0u << 8) /**< \brief (TC_CMR) None */
	#define   TC_CMR_EEVTEDG_RISING (0x1u << 8) /**< \brief (TC_CMR) Rising edge */
	#define   TC_CMR_EEVTEDG_FALLING (0x2u << 8) /**< \brief (TC_CMR) Falling edge */
	#define   TC_CMR_EEVTEDG_EDGE (0x3u << 8) /**< \brief (TC_CMR) Each edge */
	#define TC_CMR_EEVT_Pos 10
	#define TC_CMR_EEVT_Msk (0x3u << TC_CMR_EEVT_Pos) /**< \brief (TC_CMR) External Event Selection */
	#define   TC_CMR_EEVT_TIOB (0x0u << 10) /**< \brief (TC_CMR) TIOB */
	#define   TC_CMR_EEVT_XC0 (0x1u << 10) /**< \brief (TC_CMR) XC0 */
	#define   TC_CMR_EEVT_XC1 (0x2u << 10) /**< \brief (TC_CMR) XC1 */
	#define   TC_CMR_EEVT_XC2 (0x3u << 10) /**< \brief (TC_CMR) XC2 */
	#define TC_CMR_ENETRG (0x1u << 12) /**< \brief (TC_CMR) External Event Trigger Enable */
	#define TC_CMR_WAVSEL_Pos 13
	#define TC_CMR_WAVSEL_Msk (0x3u << TC_CMR_WAVSEL_Pos) /**< \brief (TC_CMR) Waveform Selection */
	#define   TC_CMR_WAVSEL_UP (0x0u << 13) /**< \brief (TC_CMR) UP mode without automatic trigger on RC Compare */
	#define   TC_CMR_WAVSEL_UPDOWN (0x1u << 13) /**< \brief (TC_CMR) UPDOWN mode without automatic trigger on RC Compare */
	#define   TC_CMR_WAVSEL_UP_RC (0x2u << 13) /**< \brief (TC_CMR) UP mode with automatic trigger on RC Compare */
	#define   TC_CMR_WAVSEL_UPDOWN_RC (0x3u << 13) /**< \brief (TC_CMR) UPDOWN mode with automatic trigger on RC Compare */
	#define TC_CMR_ACPA_Pos 16
	#define TC_CMR_ACPA_Msk (0x3u << TC_CMR_ACPA_Pos) /**< \brief (TC_CMR) RA Compare Effect on TIOA */
	#define   TC_CMR_ACPA_NONE (0x0u << 16) /**< \brief (TC_CMR) None */
	#define   TC_CMR_ACPA_SET (0x1u << 16) /**< \brief (TC_CMR) Set */
	#define   TC_CMR_ACPA_CLEAR (0x2u << 16) /**< \brief (TC_CMR) Clear */
	#define   TC_CMR_ACPA_TOGGLE (0x3u << 16) /**< \brief (TC_CMR) Toggle */
	#define TC_CMR_ACPC_Pos 18
	#define TC_CMR_ACPC_Msk (0x3u << TC_CMR_ACPC_Pos) /**< \brief (TC_CMR) RC Compare Effect on TIOA */
	#define   TC_CMR_ACPC_NONE (0x0u << 18) /**< \brief (TC_CMR) None */
	#define   TC_CMR_ACPC_SET (0x1u << 18) /**< \brief (TC_CMR) Set */
	#define   TC_CMR_ACPC_CLEAR (0x2u << 18) /**< \brief (TC_CMR) Clear */
	#define   TC_CMR_ACPC_TOGGLE (0x3u << 18) /**< \brief (TC_CMR) Toggle */
	#define TC_CMR_AEEVT_Pos 20
	#define TC_CMR_AEEVT_Msk (0x3u << TC_CMR_AEEVT_Pos) /**< \brief (TC_CMR) External Event Effect on TIOA */
	#define   TC_CMR_AEEVT_NONE (0x0u << 20) /**< \brief (TC_CMR) None */
	#define   TC_CMR_AEEVT_SET (0x1u << 20) /**< \brief (TC_CMR) Set */
	#define   TC_CMR_AEEVT_CLEAR (0x2u << 20) /**< \brief (TC_CMR) Clear */
	#define   TC_CMR_AEEVT_TOGGLE (0x3u << 20) /**< \brief (TC_CMR) Toggle */
	#define TC_CMR_ASWTRG_Pos 22
	#define TC_CMR_ASWTRG_Msk (0x3u << TC_CMR_ASWTRG_Pos) /**< \brief (TC_CMR) Software Trigger Effect on TIOA */
	#define   TC_CMR_ASWTRG_NONE (0x0u << 22) /**< \brief (TC_CMR) None */
	#define   TC_CMR_ASWTRG_SET (0x1u << 22) /**< \brief (TC_CMR) Set */
	#define   TC_CMR_ASWTRG_CLEAR (0x2u << 22) /**< \brief (TC_CMR) Clear */
	#define   TC_CMR_ASWTRG_TOGGLE (0x3u << 22) /**< \brief (TC_CMR) Toggle */
	#define TC_CMR_BCPB_Pos 24
	#define TC_CMR_BCPB_Msk (0x3u << TC_CMR_BCPB_Pos) /**< \brief (TC_CMR) RB Compare Effect on TIOB */
	#define   TC_CMR_BCPB_NONE (0x0u << 24) /**< \brief (TC_CMR) None */
	#define   TC_CMR_BCPB_SET (0x1u << 24) /**< \brief (TC_CMR) Set */
	#define   TC_CMR_BCPB_CLEAR (0x2u << 24) /**< \brief (TC_CMR) Clear */
	#define   TC_CMR_BCPB_TOGGLE (0x3u << 24) /**< \brief (TC_CMR) Toggle */
	#define TC_CMR_BCPC_Pos 26
	#define TC_CMR_BCPC_Msk (0x3u << TC_CMR_BCPC_Pos) /**< \brief (TC_CMR) RC Compare Effect on TIOB */
	#define   TC_CMR_BCPC_NONE (0x0u << 26) /**< \brief (TC_CMR) None */
	#define   TC_CMR_BCPC_SET (0x1u << 26) /**< \brief (TC_CMR) Set */
	#define   TC_CMR_BCPC_CLEAR (0x2u << 26) /**< \brief (TC_CMR) Clear */
	#define   TC_CMR_BCPC_TOGGLE (0x3u << 26) /**< \brief (TC_CMR) Toggle */
	#define TC_CMR_BEEVT_Pos 28
	#define TC_CMR_BEEVT_Msk (0x3u << TC_CMR_BEEVT_Pos) /**< \brief (TC_CMR) External Event Effect on TIOB */
	#define   TC_CMR_BEEVT_NONE (0x0u << 28) /**< \brief (TC_CMR) None */
	#define   TC_CMR_BEEVT_SET (0x1u << 28) /**< \brief (TC_CMR) Set */
	#define   TC_CMR_BEEVT_CLEAR (0x2u << 28) /**< \brief (TC_CMR) Clear */
	#define   TC_CMR_BEEVT_TOGGLE (0x3u << 28) /**< \brief (TC_CMR) Toggle */
	#define TC_CMR_BSWTRG_Pos 30
	#define TC_CMR_BSWTRG_Msk (0x3u << TC_CMR_BSWTRG_Pos) /**< \brief (TC_CMR) Software Trigger Effect on TIOB */
	#define   TC_CMR_BSWTRG_NONE (0x0u << 30) /**< \brief (TC_CMR) None */
	#define   TC_CMR_BSWTRG_SET (0x1u << 30) /**< \brief (TC_CMR) Set */
	#define   TC_CMR_BSWTRG_CLEAR (0x2u << 30) /**< \brief (TC_CMR) Clear */
	#define   TC_CMR_BSWTRG_TOGGLE (0x3u << 30) /**< \brief (TC_CMR) Toggle */

	/* -------- TC_SMMR : (TC Offset: N/A) Stepper Motor Mode Register -------- */
	#define TC_SMMR_GCEN (0x1u << 0) /**< \brief (TC_SMMR) Gray Count Enable */
	#define TC_SMMR_DOWN (0x1u << 1) /**< \brief (TC_SMMR) DOWN Count */

	/* -------- TC_CV : (TC Offset: N/A) Counter Value -------- */
	#define TC_CV_CV_Pos 0
	#define TC_CV_CV_Msk (0xffffffffu << TC_CV_CV_Pos) /**< \brief (TC_CV) Counter Value */

	/* -------- TC_RA : (TC Offset: N/A) Register A -------- */
	#define TC_RA_RA_Pos 0
	#define TC_RA_RA_Msk (0xffffffffu << TC_RA_RA_Pos) /**< \brief (TC_RA) Register A */
	#define TC_RA_RA(value) ((TC_RA_RA_Msk & ((value) << TC_RA_RA_Pos)))

	/* -------- TC_RB : (TC Offset: N/A) Register B -------- */
	#define TC_RB_RB_Pos 0
	#define TC_RB_RB_Msk (0xffffffffu << TC_RB_RB_Pos) /**< \brief (TC_RB) Register B */
	#define TC_RB_RB(value) ((TC_RB_RB_Msk & ((value) << TC_RB_RB_Pos)))

	/* -------- TC_RC : (TC Offset: N/A) Register C -------- */
	#define TC_RC_RC_Pos 0
	#define TC_RC_RC_Msk (0xffffffffu << TC_RC_RC_Pos) /**< \brief (TC_RC) Register C */
	#define TC_RC_RC(value) ((TC_RC_RC_Msk & ((value) << TC_RC_RC_Pos)))

	/* -------- TC_SR : (TC Offset: N/A) Status Register -------- */
	#define TC_SR_COVFS (0x1u << 0) /**< \brief (TC_SR) Counter Overflow Status */
	#define TC_SR_LOVRS (0x1u << 1) /**< \brief (TC_SR) Load Overrun Status */
	#define TC_SR_CPAS (0x1u << 2) /**< \brief (TC_SR) RA Compare Status */
	#define TC_SR_CPBS (0x1u << 3) /**< \brief (TC_SR) RB Compare Status */
	#define TC_SR_CPCS (0x1u << 4) /**< \brief (TC_SR) RC Compare Status */
	#define TC_SR_LDRAS (0x1u << 5) /**< \brief (TC_SR) RA Loading Status */
	#define TC_SR_LDRBS (0x1u << 6) /**< \brief (TC_SR) RB Loading Status */
	#define TC_SR_ETRGS (0x1u << 7) /**< \brief (TC_SR) External Trigger Status */
	#define TC_SR_CLKSTA (0x1u << 16) /**< \brief (TC_SR) Clock Enabling Status */
	#define TC_SR_MTIOA (0x1u << 17) /**< \brief (TC_SR) TIOA Mirror */
	#define TC_SR_MTIOB (0x1u << 18) /**< \brief (TC_SR) TIOB Mirror */

	/* -------- TC_IER : (TC Offset: N/A) Interrupt Enable Register -------- */
	#define TC_IER_COVFS (0x1u << 0) /**< \brief (TC_IER) Counter Overflow */
	#define TC_IER_LOVRS (0x1u << 1) /**< \brief (TC_IER) Load Overrun */
	#define TC_IER_CPAS (0x1u << 2) /**< \brief (TC_IER) RA Compare */
	#define TC_IER_CPBS (0x1u << 3) /**< \brief (TC_IER) RB Compare */
	#define TC_IER_CPCS (0x1u << 4) /**< \brief (TC_IER) RC Compare */
	#define TC_IER_LDRAS (0x1u << 5) /**< \brief (TC_IER) RA Loading */
	#define TC_IER_LDRBS (0x1u << 6) /**< \brief (TC_IER) RB Loading */
	#define TC_IER_ETRGS (0x1u << 7) /**< \brief (TC_IER) External Trigger */

	/* -------- TC_IDR : (TC Offset: N/A) Interrupt Disable Register -------- */
	#define TC_IDR_COVFS (0x1u << 0) /**< \brief (TC_IDR) Counter Overflow */
	#define TC_IDR_LOVRS (0x1u << 1) /**< \brief (TC_IDR) Load Overrun */
	#define TC_IDR_CPAS (0x1u << 2) /**< \brief (TC_IDR) RA Compare */
	#define TC_IDR_CPBS (0x1u << 3) /**< \brief (TC_IDR) RB Compare */
	#define TC_IDR_CPCS (0x1u << 4) /**< \brief (TC_IDR) RC Compare */
	#define TC_IDR_LDRAS (0x1u << 5) /**< \brief (TC_IDR) RA Loading */
	#define TC_IDR_LDRBS (0x1u << 6) /**< \brief (TC_IDR) RB Loading */
	#define TC_IDR_ETRGS (0x1u << 7) /**< \brief (TC_IDR) External Trigger */

	/* -------- TC_IMR : (TC Offset: N/A) Interrupt Mask Register -------- */
	#define TC_IMR_COVFS (0x1u << 0) /**< \brief (TC_IMR) Counter Overflow */
	#define TC_IMR_LOVRS (0x1u << 1) /**< \brief (TC_IMR) Load Overrun */
	#define TC_IMR_CPAS (0x1u << 2) /**< \brief (TC_IMR) RA Compare */
	#define TC_IMR_CPBS (0x1u << 3) /**< \brief (TC_IMR) RB Compare */
	#define TC_IMR_CPCS (0x1u << 4) /**< \brief (TC_IMR) RC Compare */
	#define TC_IMR_LDRAS (0x1u << 5) /**< \brief (TC_IMR) RA Loading */
	#define TC_IMR_LDRBS (0x1u << 6) /**< \brief (TC_IMR) RB Loading */
	#define TC_IMR_ETRGS (0x1u << 7) /**< \brief (TC_IMR) External Trigger */

	/* -------- TC_BCR : (TC Offset: 0xC0) Block Control Register -------- */
	#define TC_BCR_SYNC (0x1u << 0) /**< \brief (TC_BCR) Synchro Command */

	/* -------- TC_BMR : (TC Offset: 0xC4) Block Mode Register -------- */
	#define TC_BMR_TC0XC0S_Pos 0
	#define TC_BMR_TC0XC0S_Msk (0x3u << TC_BMR_TC0XC0S_Pos) /**< \brief (TC_BMR) External Clock Signal 0 Selection */
	#define   TC_BMR_TC0XC0S_TCLK0 (0x0u << 0) /**< \brief (TC_BMR) Signal connected to XC0: TCLK0 */
	#define   TC_BMR_TC0XC0S_TIOA1 (0x2u << 0) /**< \brief (TC_BMR) Signal connected to XC0: TIOA1 */
	#define   TC_BMR_TC0XC0S_TIOA2 (0x3u << 0) /**< \brief (TC_BMR) Signal connected to XC0: TIOA2 */
	#define TC_BMR_TC1XC1S_Pos 2
	#define TC_BMR_TC1XC1S_Msk (0x3u << TC_BMR_TC1XC1S_Pos) /**< \brief (TC_BMR) External Clock Signal 1 Selection */
	#define   TC_BMR_TC1XC1S_TCLK1 (0x0u << 2) /**< \brief (TC_BMR) Signal connected to XC1: TCLK1 */
	#define   TC_BMR_TC1XC1S_TIOA0 (0x2u << 2) /**< \brief (TC_BMR) Signal connected to XC1: TIOA0 */
	#define   TC_BMR_TC1XC1S_TIOA2 (0x3u << 2) /**< \brief (TC_BMR) Signal connected to XC1: TIOA2 */
	#define TC_BMR_TC2XC2S_Pos 4
	#define TC_BMR_TC2XC2S_Msk (0x3u << TC_BMR_TC2XC2S_Pos) /**< \brief (TC_BMR) External Clock Signal 2 Selection */
	#define   TC_BMR_TC2XC2S_TCLK2 (0x0u << 4) /**< \brief (TC_BMR) Signal connected to XC2: TCLK2 */
	#define   TC_BMR_TC2XC2S_TIOA1 (0x2u << 4) /**< \brief (TC_BMR) Signal connected to XC2: TIOA1 */
	#define   TC_BMR_TC2XC2S_TIOA2 (0x3u << 4) /**< \brief (TC_BMR) Signal connected to XC2: TIOA2 */
	#define TC_BMR_QDEN (0x1u << 8) /**< \brief (TC_BMR) Quadrature Decoder ENabled */
	#define TC_BMR_POSEN (0x1u << 9) /**< \brief (TC_BMR) POSition ENabled */
	#define TC_BMR_SPEEDEN (0x1u << 10) /**< \brief (TC_BMR) SPEED ENabled */
	#define TC_BMR_QDTRANS (0x1u << 11) /**< \brief (TC_BMR) Quadrature Decoding TRANSparent */
	#define TC_BMR_EDGPHA (0x1u << 12) /**< \brief (TC_BMR) EDGe on PHA count mode */
	#define TC_BMR_INVA (0x1u << 13) /**< \brief (TC_BMR) INVerted phA */
	#define TC_BMR_INVB (0x1u << 14) /**< \brief (TC_BMR) INVerted phB */
	#define TC_BMR_INVIDX (0x1u << 15) /**< \brief (TC_BMR) INVerted InDeX */
	#define TC_BMR_SWAP (0x1u << 16) /**< \brief (TC_BMR) SWAP PHA and PHB */
	#define TC_BMR_IDXPHB (0x1u << 17) /**< \brief (TC_BMR) InDeX pin is PHB pin */
	#define TC_BMR_FILTER (0x1u << 19) /**< \brief (TC_BMR)  */
	#define TC_BMR_MAXFILT_Pos 20
	#define TC_BMR_MAXFILT_Msk (0x3fu << TC_BMR_MAXFILT_Pos) /**< \brief (TC_BMR) MAXimum FILTer */
	#define TC_BMR_MAXFILT(value) ((TC_BMR_MAXFILT_Msk & ((value) << TC_BMR_MAXFILT_Pos)))

	/* -------- TC_QIER : (TC Offset: 0xC8) QDEC Interrupt Enable Register -------- */
	#define TC_QIER_IDX (0x1u << 0) /**< \brief (TC_QIER) InDeX */
	#define TC_QIER_DIRCHG (0x1u << 1) /**< \brief (TC_QIER) DIRection CHanGe */
	#define TC_QIER_QERR (0x1u << 2) /**< \brief (TC_QIER) Quadrature ERRor */

	/* -------- TC_QIDR : (TC Offset: 0xCC) QDEC Interrupt Disable Register -------- */
	#define TC_QIDR_IDX (0x1u << 0) /**< \brief (TC_QIDR) InDeX */
	#define TC_QIDR_DIRCHG (0x1u << 1) /**< \brief (TC_QIDR) DIRection CHanGe */
	#define TC_QIDR_QERR (0x1u << 2) /**< \brief (TC_QIDR) Quadrature ERRor */

	/* -------- TC_QIMR : (TC Offset: 0xD0) QDEC Interrupt Mask Register -------- */
	#define TC_QIMR_IDX (0x1u << 0) /**< \brief (TC_QIMR) InDeX */
	#define TC_QIMR_DIRCHG (0x1u << 1) /**< \brief (TC_QIMR) DIRection CHanGe */
	#define TC_QIMR_QERR (0x1u << 2) /**< \brief (TC_QIMR) Quadrature ERRor */

	/* -------- TC_QISR : (TC Offset: 0xD4) QDEC Interrupt Status Register -------- */
	#define TC_QISR_IDX (0x1u << 0) /**< \brief (TC_QISR) InDeX */
	#define TC_QISR_DIRCHG (0x1u << 1) /**< \brief (TC_QISR) DIRection CHanGe */
	#define TC_QISR_QERR (0x1u << 2) /**< \brief (TC_QISR) Quadrature ERRor */
	#define TC_QISR_DIR (0x1u << 8) /**< \brief (TC_QISR) Direction */

	/* -------- TC_FMR : (TC Offset: 0xD8) Fault Mode Register -------- */
	#define TC_FMR_ENCF0 (0x1u << 0) /**< \brief (TC_FMR) ENable Compare Fault Channel 0 */
	#define TC_FMR_ENCF1 (0x1u << 1) /**< \brief (TC_FMR) ENable Compare Fault Channel 1 */

	/* -------- TC_WPMR : (TC Offset: 0xE4) Write Protect Mode Register -------- */
	#define TC_WPMR_WPEN (0x1u << 0) /**< \brief (TC_WPMR) Write Protect Enable */
	#define TC_WPMR_WPKEY_Pos 8
	#define TC_WPMR_WPKEY_Msk (0xffffffu << TC_WPMR_WPKEY_Pos) /**< \brief (TC_WPMR) Write Protect KEY */
	#define TC_WPMR_WPKEY(value) ((TC_WPMR_WPKEY_Msk & ((value) << TC_WPMR_WPKEY_Pos)))

	// -----------------------------------------------------------------------------
	// WATCHDOG
	// -----------------------------------------------------------------------------
	#define WDT_MR (*(volatile uint32_t*)0x400E1454)
	#define WDT_CR (*(volatile uint32_t*)0x400E1450)

	#define WDT_MR_WDDIS (0x1u << 15)
	#define WDT_CR_WDRSTT (0x1u << 0)

	#define SUPC_CR (*(volatile uint32_t*)0x400E1410)
	#define SUPC_CR_XTALSEL (0x01u << 3)
	#define SUPC_CR_KEY (0xA5u << 24)

	#define SUPC_SR (*(volatile uint32_t*)0x400E1424)
	#define SUPC_SR_OSCSEL (0x01u << 7)

	#define SUPC_MR (*(volatile uint32_t*)0x400E1418)
	#define SUPC_MR_KEY (0xA5u << 24)
	#define SUPC_MR_OSCBYPASS (0x1u<<20)


#else

	// -----------------------------------------------------------------------------
	// For BitCloud HAL
	// -----------------------------------------------------------------------------


	// -----------------------------------------------------------------------------
	// GPIO
	// -----------------------------------------------------------------------------
	#define ID_PIOA   (11) /**< \brief Parallel I/O Controller A (PIOA) */
	#define ID_PIOB   (12) /**< \brief Parallel I/O Controller B (PIOB) */
	#define ID_PIOC   (13) /**< \brief Parallel I/O Controller C (PIOC) */


	// -----------------------------------------------------------------------------
	// USART
	// -----------------------------------------------------------------------------
	#define USART0_CR   (*(volatile uint32_t*)0x40024000U) /**< \brief (USART0) Control Register */
	#define USART0_MR   (*(volatile uint32_t*)0x40024004U) /**< \brief (USART0) Mode Register */
	#define USART0_IER  (*(volatile uint32_t*)0x40024008U) /**< \brief (USART0) Interrupt Enable Register */
	#define USART0_IDR  (*(volatile uint32_t*)0x4002400CU) /**< \brief (USART0) Interrupt Disable Register */
	#define USART0_IMR  (*(volatile uint32_t*)0x40024010U) /**< \brief (USART0) Interrupt Mask Register */
	#define USART0_CSR  (*(volatile uint32_t*)0x40024014U) /**< \brief (USART0) Channel Status Register */
	#define USART0_RHR  (*(volatile uint32_t*)0x40024018U) /**< \brief (USART0) Receiver Holding Register */
	#define USART0_THR  (*(volatile uint32_t*)0x4002401CU) /**< \brief (USART0) Transmitter Holding Register */
	#define USART0_BRGR (*(volatile uint32_t*)0x40024020U) /**< \brief (USART0) Baud Rate Generator Register */
	#define USART0_RTOR (*(volatile uint32_t*)0x40024024U) /**< \brief (USART0) Receiver Time-out Register */
	#define USART0_TTGR (*(volatile uint32_t*)0x40024028U) /**< \brief (USART0) Transmitter Timeguard Register */
	#define USART0_FIDI (*(volatile uint32_t*)0x40024040U) /**< \brief (USART0) FI DI Ratio Register */
	#define USART0_NER  (*(volatile uint32_t*)0x40024044U) /**< \brief (USART0) Number of Errors Register */
	#define USART0_IF   (*(volatile uint32_t*)0x4002404CU) /**< \brief (USART0) IrDA Filter Register */
	#define USART0_MAN  (*(volatile uint32_t*)0x40024050U) /**< \brief (USART0) Manchester Encoder Decoder Register */
	#define USART0_WPMR (*(volatile uint32_t*)0x400240E4U) /**< \brief (USART0) Write Protect Mode Register */
	#define USART0_WPSR (*(volatile uint32_t*)0x400240E8U) /**< \brief (USART0) Write Protect Status Register */
	#define USART0_VERSION (*(volatile uint32_t*)0x400240FCU) /**< \brief (USART0) Version Register */
	#define USART0_RPR  (*(volatile uint32_t*)0x40024100U) /**< \brief (USART0) Receive Pointer Register */
	#define USART0_RCR  (*(volatile uint32_t*)0x40024104U) /**< \brief (USART0) Receive Counter Register */
	#define USART0_TPR  (*(volatile uint32_t*)0x40024108U) /**< \brief (USART0) Transmit Pointer Register */
	#define USART0_TCR  (*(volatile uint32_t*)0x4002410CU) /**< \brief (USART0) Transmit Counter Register */
	#define USART0_RNPR (*(volatile uint32_t*)0x40024110U) /**< \brief (USART0) Receive Next Pointer Register */
	#define USART0_RNCR (*(volatile uint32_t*)0x40024114U) /**< \brief (USART0) Receive Next Counter Register */
	#define USART0_TNPR (*(volatile uint32_t*)0x40024118U) /**< \brief (USART0) Transmit Next Pointer Register */
	#define USART0_TNCR (*(volatile uint32_t*)0x4002411CU) /**< \brief (USART0) Transmit Next Counter Register */
	#define USART0_PTCR (*(volatile uint32_t*)0x40024120U) /**< \brief (USART0) Transfer Control Register */
	#define USART0_PTSR (*(volatile uint32_t*)0x40024124U) /**< \brief (USART0) Transfer Status Register */


	#define USART1_CR   (*(volatile uint32_t*)0x40028000U) /**< \brief (USART1) Control Register */
	#define USART1_MR   (*(volatile uint32_t*)0x40028004U) /**< \brief (USART1) Mode Register */
	#define USART1_IER  (*(volatile uint32_t*)0x40028008U) /**< \brief (USART1) Interrupt Enable Register */
	#define USART1_IDR  (*(volatile uint32_t*)0x4002800CU) /**< \brief (USART1) Interrupt Disable Register */
	#define USART1_IMR  (*(volatile uint32_t*)0x40028010U) /**< \brief (USART1) Interrupt Mask Register */
	#define USART1_CSR  (*(volatile uint32_t*)0x40028014U) /**< \brief (USART1) Channel Status Register */
	#define USART1_RHR  (*(volatile uint32_t*)0x40028018U) /**< \brief (USART1) Receiver Holding Register */
	#define USART1_THR  (*(volatile uint32_t*)0x4002801CU) /**< \brief (USART1) Transmitter Holding Register */
	#define USART1_BRGR (*(volatile uint32_t*)0x40028020U) /**< \brief (USART1) Baud Rate Generator Register */
	#define USART1_RTOR (*(volatile uint32_t*)0x40028024U) /**< \brief (USART1) Receiver Time-out Register */
	#define USART1_TTGR (*(volatile uint32_t*)0x40028028U) /**< \brief (USART1) Transmitter Timeguard Register */
	#define USART1_FIDI (*(volatile uint32_t*)0x40028040U) /**< \brief (USART1) FI DI Ratio Register */
	#define USART1_NER  (*(volatile uint32_t*)0x40028044U) /**< \brief (USART1) Number of Errors Register */
	#define USART1_IF   (*(volatile uint32_t*)0x4002804CU) /**< \brief (USART1) IrDA Filter Register */
	#define USART1_MAN  (*(volatile uint32_t*)0x40028050U) /**< \brief (USART1) Manchester Encoder Decoder Register */
	#define USART1_WPMR (*(volatile uint32_t*)0x400280E4U) /**< \brief (USART1) Write Protect Mode Register */
	#define USART1_WPSR (*(volatile uint32_t*)0x400280E8U) /**< \brief (USART1) Write Protect Status Register */
	#define USART1_VERSION (*(volatile uint32_t*)0x400280FCU) /**< \brief (USART1) Version Register */
	#define USART1_RPR  (*(volatile uint32_t*)0x40028100U) /**< \brief (USART1) Receive Pointer Register */
	#define USART1_RCR  (*(volatile uint32_t*)0x40028104U) /**< \brief (USART1) Receive Counter Register */
	#define USART1_TPR  (*(volatile uint32_t*)0x40028108U) /**< \brief (USART1) Transmit Pointer Register */
	#define USART1_TCR  (*(volatile uint32_t*)0x4002810CU) /**< \brief (USART1) Transmit Counter Register */
	#define USART1_RNPR (*(volatile uint32_t*)0x40028110U) /**< \brief (USART1) Receive Next Pointer Register */
	#define USART1_RNCR (*(volatile uint32_t*)0x40028114U) /**< \brief (USART1) Receive Next Counter Register */
	#define USART1_TNPR (*(volatile uint32_t*)0x40028118U) /**< \brief (USART1) Transmit Next Pointer Register */
	#define USART1_TNCR (*(volatile uint32_t*)0x4002811CU) /**< \brief (USART1) Transmit Next Counter Register */
	#define USART1_PTCR (*(volatile uint32_t*)0x40028120U) /**< \brief (USART1) Transfer Control Register */
	#define USART1_PTSR (*(volatile uint32_t*)0x40028124U) /**< \brief (USART1) Transfer Status Register */

	#define US_MR_USCLKS_MCK (0x0u << 4) /**< \brief (US_MR) Master Clock MCK is selected */
	#define US_MR_CHRL_8_BIT (0x3u << 6) /**< \brief (US_MR) Character length is 8 bits */
	#define US_MR_PAR_NO (0x4u << 9) /**< \brief (US_MR) No parity */

	// -----------------------------------------------------------------------------
	// TIMER
	// -----------------------------------------------------------------------------
	#define TC0_CCR0  (*(volatile uint32_t*)0x40010000U) /**< \brief (TC0) Channel Control Register (channel = 0) */
	#define TC0_CMR0  (*(RwReg*)0x40010004U) /**< \brief (TC0) Channel Mode Register (channel = 0) */
	#define TC0_SMMR0 (*(RwReg*)0x40010008U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 0) */
	#define TC0_CV0   (*(RoReg*)0x40010010U) /**< \brief (TC0) Counter Value (channel = 0) */
	#define TC0_RA0   (*(RwReg*)0x40010014U) /**< \brief (TC0) Register A (channel = 0) */
	#define TC0_RB0   (*(RwReg*)0x40010018U) /**< \brief (TC0) Register B (channel = 0) */
	#define TC0_RC0   (*(RwReg*)0x4001001CU) /**< \brief (TC0) Register C (channel = 0) */
	#define TC0_SR0   (*(RoReg*)0x40010020U) /**< \brief (TC0) Status Register (channel = 0) */
	#define TC0_IER0  (*(volatile uint32_t*)0x40010024U) /**< \brief (TC0) Interrupt Enable Register (channel = 0) */
	#define TC0_IDR0  (*(volatile uint32_t*)0x40010028U) /**< \brief (TC0) Interrupt Disable Register (channel = 0) */
	#define TC0_IMR0  (*(RoReg*)0x4001002CU) /**< \brief (TC0) Interrupt Mask Register (channel = 0) */
	#define TC0_CCR1  (*(volatile uint32_t*)0x40010040U) /**< \brief (TC0) Channel Control Register (channel = 1) */
	#define TC0_CMR1  (*(RwReg*)0x40010044U) /**< \brief (TC0) Channel Mode Register (channel = 1) */
	#define TC0_SMMR1 (*(RwReg*)0x40010048U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 1) */
	#define TC0_CV1   (*(RoReg*)0x40010050U) /**< \brief (TC0) Counter Value (channel = 1) */
	#define TC0_RA1   (*(RwReg*)0x40010054U) /**< \brief (TC0) Register A (channel = 1) */
	#define TC0_RB1   (*(RwReg*)0x40010058U) /**< \brief (TC0) Register B (channel = 1) */
	#define TC0_RC1   (*(RwReg*)0x4001005CU) /**< \brief (TC0) Register C (channel = 1) */
	#define TC0_SR1   (*(RoReg*)0x40010060U) /**< \brief (TC0) Status Register (channel = 1) */
	#define TC0_IER1  (*(volatile uint32_t*)0x40010064U) /**< \brief (TC0) Interrupt Enable Register (channel = 1) */
	#define TC0_IDR1  (*(volatile uint32_t*)0x40010068U) /**< \brief (TC0) Interrupt Disable Register (channel = 1) */
	#define TC0_IMR1  (*(RoReg*)0x4001006CU) /**< \brief (TC0) Interrupt Mask Register (channel = 1) */
	#define TC0_CCR2  (*(volatile uint32_t*)0x40010080U) /**< \brief (TC0) Channel Control Register (channel = 2) */
	#define TC0_CMR2  (*(RwReg*)0x40010084U) /**< \brief (TC0) Channel Mode Register (channel = 2) */
	#define TC0_SMMR2 (*(RwReg*)0x40010088U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 2) */
	#define TC0_CV2   (*(RoReg*)0x40010090U) /**< \brief (TC0) Counter Value (channel = 2) */
	#define TC0_RA2   (*(RwReg*)0x40010094U) /**< \brief (TC0) Register A (channel = 2) */
	#define TC0_RB2   (*(RwReg*)0x40010098U) /**< \brief (TC0) Register B (channel = 2) */
	#define TC0_RC2   (*(RwReg*)0x4001009CU) /**< \brief (TC0) Register C (channel = 2) */
	#define TC0_SR2   (*(RoReg*)0x400100A0U) /**< \brief (TC0) Status Register (channel = 2) */
	#define TC0_IER2  (*(volatile uint32_t*)0x400100A4U) /**< \brief (TC0) Interrupt Enable Register (channel = 2) */
	#define TC0_IDR2  (*(volatile uint32_t*)0x400100A8U) /**< \brief (TC0) Interrupt Disable Register (channel = 2) */
	#define TC0_IMR2  (*(RoReg*)0x400100ACU) /**< \brief (TC0) Interrupt Mask Register (channel = 2) */
	#define TC0_BCR   (*(volatile uint32_t*)0x400100C0U) /**< \brief (TC0) Block Control Register */
	#define TC0_BMR   (*(RwReg*)0x400100C4U) /**< \brief (TC0) Block Mode Register */
	#define TC0_QIER  (*(volatile uint32_t*)0x400100C8U) /**< \brief (TC0) QDEC Interrupt Enable Register */
	#define TC0_QIDR  (*(volatile uint32_t*)0x400100CCU) /**< \brief (TC0) QDEC Interrupt Disable Register */
	#define TC0_QIMR  (*(RoReg*)0x400100D0U) /**< \brief (TC0) QDEC Interrupt Mask Register */
	#define TC0_QISR  (*(RoReg*)0x400100D4U) /**< \brief (TC0) QDEC Interrupt Status Register */
	#define TC0_FMR   (*(RwReg*)0x400100D8U) /**< \brief (TC0) Fault Mode Register */
	#define TC0_WPMR  (*(RwReg*)0x400100E4U) /**< \brief (TC0) Write Protect Mode Register */

	#define TC1_CCR0  (*(WoReg*)0x40014000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
	#define TC1_CMR0  (*(RwReg*)0x40014004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
	#define TC1_SMMR0 (*(RwReg*)0x40014008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
	#define TC1_CV0   (*(RoReg*)0x40014010U) /**< \brief (TC1) Counter Value (channel = 0) */
	#define TC1_RA0   (*(RwReg*)0x40014014U) /**< \brief (TC1) Register A (channel = 0) */
	#define TC1_RB0   (*(RwReg*)0x40014018U) /**< \brief (TC1) Register B (channel = 0) */
	#define TC1_RC0   (*(RwReg*)0x4001401CU) /**< \brief (TC1) Register C (channel = 0) */
	#define TC1_SR0   (*(RoReg*)0x40014020U) /**< \brief (TC1) Status Register (channel = 0) */
	#define TC1_IER0  (*(WoReg*)0x40014024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
	#define TC1_IDR0  (*(WoReg*)0x40014028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
	#define TC1_IMR0  (*(RoReg*)0x4001402CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
	#define TC1_CCR1  (*(WoReg*)0x40014040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
	#define TC1_CMR1  (*(RwReg*)0x40014044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
	#define TC1_SMMR1 (*(RwReg*)0x40014048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
	#define TC1_CV1   (*(RoReg*)0x40014050U) /**< \brief (TC1) Counter Value (channel = 1) */
	#define TC1_RA1   (*(RwReg*)0x40014054U) /**< \brief (TC1) Register A (channel = 1) */
	#define TC1_RB1   (*(RwReg*)0x40014058U) /**< \brief (TC1) Register B (channel = 1) */
	#define TC1_RC1   (*(RwReg*)0x4001405CU) /**< \brief (TC1) Register C (channel = 1) */
	#define TC1_SR1   (*(RoReg*)0x40014060U) /**< \brief (TC1) Status Register (channel = 1) */
	#define TC1_IER1  (*(WoReg*)0x40014064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
	#define TC1_IDR1  (*(WoReg*)0x40014068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
	#define TC1_IMR1  (*(RoReg*)0x4001406CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
	#define TC1_CCR2  (*(WoReg*)0x40014080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
	#define TC1_CMR2  (*(RwReg*)0x40014084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
	#define TC1_SMMR2 (*(RwReg*)0x40014088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
	#define TC1_CV2   (*(RoReg*)0x40014090U) /**< \brief (TC1) Counter Value (channel = 2) */
	#define TC1_RA2   (*(RwReg*)0x40014094U) /**< \brief (TC1) Register A (channel = 2) */
	#define TC1_RB2   (*(RwReg*)0x40014098U) /**< \brief (TC1) Register B (channel = 2) */
	#define TC1_RC2   (*(RwReg*)0x4001409CU) /**< \brief (TC1) Register C (channel = 2) */
	#define TC1_SR2   (*(RoReg*)0x400140A0U) /**< \brief (TC1) Status Register (channel = 2) */
	#define TC1_IER2  (*(WoReg*)0x400140A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
	#define TC1_IDR2  (*(WoReg*)0x400140A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
	#define TC1_IMR2  (*(RoReg*)0x400140ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
	#define TC1_BCR   (*(WoReg*)0x400140C0U) /**< \brief (TC1) Block Control Register */
	#define TC1_BMR   (*(RwReg*)0x400140C4U) /**< \brief (TC1) Block Mode Register */
	#define TC1_QIER  (*(WoReg*)0x400140C8U) /**< \brief (TC1) QDEC Interrupt Enable Register */
	#define TC1_QIDR  (*(WoReg*)0x400140CCU) /**< \brief (TC1) QDEC Interrupt Disable Register */
	#define TC1_QIMR  (*(RoReg*)0x400140D0U) /**< \brief (TC1) QDEC Interrupt Mask Register */
	#define TC1_QISR  (*(RoReg*)0x400140D4U) /**< \brief (TC1) QDEC Interrupt Status Register */
	#define TC1_FMR   (*(RwReg*)0x400140D8U) /**< \brief (TC1) Fault Mode Register */
	#define TC1_WPMR  (*(RwReg*)0x400140E4U) /**< \brief (TC1) Write Protect Mode Register */



	#define TC_CCR_CLKEN (0x1u << 0) /**< \brief (TC_CCR) Counter Clock Enable Command */
	#define TC_CCR_CLKDIS (0x1u << 1) /**< \brief (TC_CCR) Counter Clock Disable Command */
	#define TC_CCR_SWTRG (0x1u << 2) /**< \brief (TC_CCR) Software Trigger Command */

	/* -------- TC_CMR : (TC Offset: N/A) Channel Mode Register -------- */
	#define TC_CMR_TCCLKS_TIMER_CLOCK1 (0x0u << 0) /**< \brief (TC_CMR) Clock selected: TCLK1 */
	#define TC_CMR_TCCLKS_TIMER_CLOCK2 (0x1u << 0) /**< \brief (TC_CMR) Clock selected: TCLK2 */
	#define TC_CMR_TCCLKS_TIMER_CLOCK3 (0x2u << 0) /**< \brief (TC_CMR) Clock selected: TCLK3 */
	#define TC_CMR_TCCLKS_TIMER_CLOCK4 (0x3u << 0) /**< \brief (TC_CMR) Clock selected: TCLK4 */
	#define TC_CMR_TCCLKS_TIMER_CLOCK5 (0x4u << 0) /**< \brief (TC_CMR) Clock selected: TCLK5 */
	#define TC_SR_COVFS (0x1u << 0) /**< \brief (TC_SR) Counter Overflow Status */
	#define TC_SR_LOVRS (0x1u << 1) /**< \brief (TC_SR) Load Overrun Status */
	#define TC_SR_CPCS (0x1u << 4) /**< \brief (TC_SR) RC Compare Status */
	#define TC_IER_COVFS (0x1u << 0) /**< \brief (TC_IER) Counter Overflow */
	#define TC_IER_CPCS (0x1u << 4) /**< \brief (TC_IER) RC Compare */
	#define TC_IDR_COVFS (0x1u << 0) /**< \brief (TC_IDR) Counter Overflow */
	#define TC_IDR_LOVRS (0x1u << 1) /**< \brief (TC_IDR) Load Overrun */
	#define TC_IDR_CPCS (0x1u << 4) /**< \brief (TC_IDR) RC Compare */
	#define TC_IMR_COVFS (0x1u << 0) /**< \brief (TC_IMR) Counter Overflow */
	#define TC_IMR_CPCS (0x1u << 4) /**< \brief (TC_IMR) RC Compare */


	// -----------------------------------------------------------------------------
	// CLK
	// -----------------------------------------------------------------------------
	#define PMC_PCER0  (*(volatile uint32_t*)0x400E0410U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
	#define PMC_PCDR0  (*(volatile uint32_t*)0x400E0414U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */

	#define CKGR_MOR   (*(volatile uint32_t*)0x400E0420U) /**< \brief (PMC) Main Oscillator Register */
	#define CKGR_MOR_MOSCRCF_4_MHz (0x0u << 4) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 4 MHz (default) */
	#define CKGR_MOR_MOSCRCF_8_MHz (0x1u << 4) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 8 MHz */
	#define CKGR_MOR_MOSCRCF_12_MHz (0x2u << 4) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 12 MHz */

	#define CKGR_MOR_MOSCXTEN (0x1u << 0) /**< \brief (CKGR_MOR) Main Crystal Oscillator Enable */
	#define CKGR_MOR_MOSCSEL (0x1u << 24) /**< \brief (CKGR_MOR) Main Oscillator Selection */
	#define CKGR_MOR_KEY (0x37u << 16)


	#define PMC_SR     (*(volatile uint32_t*)0x400E0468U) /**< \brief (PMC) Status Register */
	#define PMC_MCKR   (*(volatile uint32_t*)0x400E0430U) /**< \brief (PMC) Master Clock Register */
	#define PMC_WPMR   (*(volatile uint32_t*)0x400E04E4U) /**< \brief (PMC) Write Protect Mode Register */
	#define PMC_SCER   (*(volatile uint32_t*)0x400E0400U) /**< \brief (PMC) System Clock Enable Register */

	//#define PMC_PCK     (*(volatile uint32_t*)0x400E0440U) /**< \brief (PMC) Programmable Clock 0 Register */
	//#define PMC_PCK2    (*(volatile uint32_t*)0x400E0444U) /**< \brief (PMC) Programmable Clock 0 Register */


	#define PMC_SCSR   (*(volatile uint32_t*)0x400E0408U) /**< \brief (PMC) System Clock Status Register */
	#define PMC_SCDR   (*(volatile uint32_t*)0x400E0404U) /**< \brief (PMC) System Clock Disable Register */

	#define PMC_MCKR_CSS_Pos 0
	#define PMC_MCKR_CSS_Msk (0x3u << PMC_MCKR_CSS_Pos) /**< \brief (PMC_MCKR) Master Clock Source Selection */
	#define PMC_SCER_PCK0 (0x1u << 8) /**< \brief (PMC_SCER) Programmable Clock 0 Output Enable */
	#define PMC_SCER_PCK1 (0x1u << 9) /**< \brief (PMC_SCER) Programmable Clock 1 Output Enable */
	#define PMC_SCER_PCK2 (0x1u << 10) /**< \brief (PMC_SCER) Programmable Clock 2 Output Enable */

	#define   PMC_MCKR_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_MCKR) Main Clock is selected */

	#define CKGR_MOR_MOSCRCEN (0x1u << 3) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Enable */


	#define CKGR_MOR_MOSCXTST_Pos 8
	#define CKGR_MOR_MOSCXTST_Msk (0xffu << CKGR_MOR_MOSCXTST_Pos) /**< \brief (CKGR_MOR) Main Crystal Oscillator Start-up Time */
	#define CKGR_MOR_MOSCXTST(value) ((CKGR_MOR_MOSCXTST_Msk & ((value) << CKGR_MOR_MOSCXTST_Pos)))

	#define   PMC_PCK_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_PCK[3]) Slow Clock is selected */
	#define   PMC_PCK_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_PCK[3]) Main Clock is selected */
	#define   PMC_PCK_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_PCK[3]) PLLA Clock is selected */
	#define   PMC_PCK_CSS_PLLB_CLK (0x3u << 0) /**< \brief (PMC_PCK[3]) PLLB Clock is selected */
	#define   PMC_PCK_CSS_MCK (0x4u << 0) /**< \brief (PMC_PCK[3]) Master Clock is selected */

	#define PMC_SCDR_PCK1 (0x1u << 9) /**< \brief (PMC_SCDR) Programmable Clock 1 Output Disable */

	#define   PMC_PCK_PRES_CLK_1 (0x0u << 4) /**< \brief (PMC_PCK[3]) Selected clock */
	#define   PMC_PCK_PRES_CLK_2 (0x1u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 2 */
	#define   PMC_PCK_PRES_CLK_4 (0x2u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 4 */

	#define   PMC_MCKR_PRES_CLK_3 (0x7u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 3 */




	#define SUPC_CR (*(volatile uint32_t*)0x400E1410)
	#define SUPC_CR_XTALSEL (0x01u << 3)
	#define SUPC_CR_KEY (0xA5u << 24)

	#define SUPC_SR (*(volatile uint32_t*)0x400E1424)
	#define SUPC_SR_OSCSEL (0x01u << 7)

	// -----------------------------------------------------------------------------
	// WATCHDOG
	// -----------------------------------------------------------------------------
	#define WDT_MR (*(volatile uint32_t*)0x400E1454)
	#define WDT_CR (*(volatile uint32_t*)0x400E1450)

	#define WDT_MR_WDDIS (0x1u << 15)
	#define WDT_CR_WDRSTT (0x1u << 0)

	#define CKGR_MCFR_MAINFRDY (0x1u << 16) /**< \brief (CKGR_MCFR) Main Clock Ready */
	#define CKGR_MCFR  (*(volatile uint32_t*)0x400E0424U) /**< \brief (PMC) Main Clock Frequency Register */


#endif // AT91SAM3S_H

#endif // HAL_PORT_COMMON_H
