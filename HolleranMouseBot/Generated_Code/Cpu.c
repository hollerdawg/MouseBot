/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Cpu.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : MKL25Z128LK4
**     Version     : Component 01.025, Driver 01.04, CPU db: 3.00.000
**     Datasheet   : KL25P80M48SF0RM, Rev.3, Sep 2012
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-11-15, 18:04, # CodeGen: 88
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         SetOperationMode - LDD_TError Cpu_SetOperationMode(LDD_TDriverOperationMode OperationMode,...
**         EnableInt        - void Cpu_EnableInt(void);
**         DisableInt       - void Cpu_DisableInt(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Cpu.c
** @version 01.04
** @brief
**
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */

/* {Default RTOS Adapter} No RTOS includes */
#include "CsIO1.h"
#include "IO1.h"
#include "ADC1.h"
#include "DMA1.h"
#include "TU1.h"
#include "IR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "w.h"
#include "right.h"
#include "PwmLdd1.h"
#include "TU2.h"
#include "left.h"
#include "PwmLdd2.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Events.h"
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Global variables */
volatile uint8_t SR_reg;               /* Current value of the FAULTMASK register */
volatile uint8_t SR_lock = 0x00U;      /* Lock */


/*
** ===================================================================
**     Method      :  Cpu_INT_NMIInterrupt (component MKL25Z128LK4)
**
**     Description :
**         This ISR services the Non Maskable Interrupt interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_NMIInterrupt)
{
  Cpu_OnNMIINT();
}

/*
** ===================================================================
**     Method      :  Cpu_INT_Hard_FaultInterrupt (component MKL25Z128LK4)
**
**     Description :
**         This ISR services the 'hard fault' interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_Hard_FaultInterrupt)
{
  Cpu_OnHardFault();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_Interrupt (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_Interrupt)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  //PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_SetOperationMode (component MKL25Z128LK4)
*/
/*!
**     @brief
**         This method requests to change the component's operation
**         mode (RUN, WAIT, SLEEP, STOP). The target operation mode
**         will be entered immediately. 
**         See [Operation mode settings] for further details of the
**         operation modes mapping to low power modes of the cpu.
**     @param
**         OperationMode   - Requested driver
**                           operation mode
**     @param
**         ModeChangeCallback - Callback to
**                           notify the upper layer once a mode has been
**                           changed. Parameter is ignored, only for
**                           compatibility of API with other components.
**     @param
**         ModeChangeCallbackParamPtr 
**                           - Pointer to callback parameter to notify
**                           the upper layer once a mode has been
**                           changed. Parameter is ignored, only for
**                           compatibility of API with other components.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_PARAM_MODE - Invalid operation mode
*/
/* ===================================================================*/
LDD_TError Cpu_SetOperationMode(LDD_TDriverOperationMode OperationMode, LDD_TCallback ModeChangeCallback, LDD_TCallbackParam *ModeChangeCallbackParamPtr)
{
  (void) ModeChangeCallback;           /* Parameter is not used, suppress unused argument warning */
  (void) ModeChangeCallbackParamPtr;   /* Parameter is not used, suppress unused argument warning */
  switch (OperationMode) {
    case DOM_RUN:
      /* SCB_SCR: SLEEPDEEP=0,SLEEPONEXIT=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(
                  SCB_SCR_SLEEPDEEP_MASK |
                  SCB_SCR_SLEEPONEXIT_MASK
                 );
      if ((MCG_S & MCG_S_CLKST_MASK) != MCG_S_CLKST(3)) { /* If in PBE mode, switch to PEE. PEE to PBE transition was caused by wakeup from low power mode. */
        /* MCG_C1: CLKS=0,IREFS=0 */
        MCG_C1 &= (uint8_t)~(uint8_t)((MCG_C1_CLKS(0x03) | MCG_C1_IREFS_MASK));
        while( (MCG_S & MCG_S_LOCK0_MASK) == 0x00U) { /* Wait for PLL lock */
        }
      }
      break;
    case DOM_WAIT:
      /* SCB_SCR: SLEEPDEEP=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPDEEP_MASK);
      /* SCB_SCR: SLEEPONEXIT=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_MASK);
      PE_WFI();
      break;
    case DOM_SLEEP:
      /* SCB_SCR: SLEEPDEEP=1 */
      SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK;
      /* SMC_STOPCTRL: PSTOPO=0,PORPO=0,??=0,??=0,VLLSM=0 */
      SMC_STOPCTRL = (SMC_STOPCTRL_PSTOPO(0x00) | SMC_STOPCTRL_VLLSM(0x00));
      /* SMC_PMCTRL: STOPM=0 */
      SMC_PMCTRL &= (uint8_t)~(uint8_t)(SMC_PMCTRL_STOPM(0x07));
      (void)(SMC_PMCTRL == 0U);        /* Dummy read of SMC_PMCTRL to ensure the register is written before enterring low power mode */
      /* SCB_SCR: SLEEPONEXIT=0 */
      SCB_SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_MASK);
      PE_WFI();
      break;
    case DOM_STOP:
      break;
    default:
      return ERR_PARAM_MODE;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component MKL25Z128LK4)
*/
/*!
**     @brief
**         Enables all maskable interrupts.
*/
/* ===================================================================*/
void Cpu_EnableInt(void)
{
 __EI();
}

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component MKL25Z128LK4)
*/
/*!
**     @brief
**         Disables all maskable interrupts.
*/
/* ===================================================================*/
void Cpu_DisableInt(void)
{
 __DI();
}


/*** !!! Here you can place your own code using property "User data declarations" on the build options tab. !!! ***/

/*lint -esym(765,__init_hardware) Disable MISRA rule (8.10) checking for symbols (__init_hardware). The function is linked to the EWL library */
/*lint -esym(765,Cpu_Interrupt) Disable MISRA rule (8.10) checking for symbols (Cpu_Interrupt). */
void __init_hardware(void)
{

  /*** !!! Here you can place your own code before PE initialization using property "User code before PE initialization" on the build options tab. !!! ***/

  /*** ### MKL25Z128VLK4 "Cpu" init code ... ***/
  /*** PE initialization code after reset ***/
  SCB_VTOR = (uint32_t)(&__vect_table); /* Set the interrupt vector table position */
  /* Disable the WDOG module */
  /* SIM_COPC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COPT=0,COPCLKS=0,COPW=0 */
  SIM_COPC = SIM_COPC_COPT(0x00);

  /* System clock initialization */
  /* SIM_CLKDIV1: OUTDIV1=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,OUTDIV4=3,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(0x00) | SIM_CLKDIV1_OUTDIV4(0x03)); /* Set the system prescalers to safe value */
  /* SIM_SCGC5: PORTD=1,PORTB=1,PORTA=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK |
               SIM_SCGC5_PORTB_MASK |
               SIM_SCGC5_PORTA_MASK;   /* Enable clock gate for ports to enable pin routing */
  if ((PMC_REGSC & PMC_REGSC_ACKISO_MASK) != 0x0U) {
    /* PMC_REGSC: ACKISO=1 */
    PMC_REGSC |= PMC_REGSC_ACKISO_MASK; /* Release IO pads after wakeup from VLLS mode. */
  }
  /* SIM_CLKDIV1: OUTDIV1=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(0x00) | SIM_CLKDIV1_OUTDIV4(0x01)); /* Update system prescalers */
  /* SIM_SOPT2: PLLFLLSEL=1 */
  SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /* Select PLL as a clock source for various peripherals */
  /* SIM_SOPT1: OSC32KSEL=0 */
  SIM_SOPT1 &= (uint32_t)~(uint32_t)(SIM_SOPT1_OSC32KSEL(0x03)); /* System oscillator drives 32 kHz clock for various peripherals */
  /* SIM_SOPT2: TPMSRC=1 */
  SIM_SOPT2 = (uint32_t)((SIM_SOPT2 & (uint32_t)~(uint32_t)(
               SIM_SOPT2_TPMSRC(0x02)
              )) | (uint32_t)(
               SIM_SOPT2_TPMSRC(0x01)
              ));                      /* Set the TPM clock */
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA_PCR18 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTA_PCR19: ISF=0,MUX=0 */
  PORTA_PCR19 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* MCG_SC: FCRDIV=1 */
  MCG_SC = (uint8_t)((MCG_SC & (uint8_t)~(uint8_t)(
            MCG_SC_FCRDIV(0x06)
           )) | (uint8_t)(
            MCG_SC_FCRDIV(0x01)
           ));
  /* Switch to FBE Mode */
  /* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=1 */
  MCG_C2 = (MCG_C2_RANGE0(0x02) | MCG_C2_EREFS0_MASK | MCG_C2_IRCS_MASK);
  /* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC0_CR = OSC_CR_ERCLKEN_MASK;
  /* MCG_C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG_C1 = (MCG_C1_CLKS(0x02) | MCG_C1_FRDIV(0x03) | MCG_C1_IRCLKEN_MASK);
  /* MCG_C4: DMX32=0,DRST_DRS=0 */
  MCG_C4 &= (uint8_t)~(uint8_t)((MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x03)));
  /* MCG_C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=3 */
  MCG_C5 = MCG_C5_PRDIV0(0x03);
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  MCG_C6 = MCG_C6_VDIV0(0x00);
  while((MCG_S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
  }
  while((MCG_S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
  /* Switch to PBE Mode */
  /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
  MCG_C6 = (MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0x00));
  while((MCG_S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
  while((MCG_S & MCG_S_LOCK0_MASK) == 0x00U) { /* Wait until locked */
  }
  /* Switch to PEE Mode */
  /* MCG_C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG_C1 = (MCG_C1_CLKS(0x00) | MCG_C1_FRDIV(0x03) | MCG_C1_IRCLKEN_MASK);
  while((MCG_S & 0x0CU) != 0x0CU) {    /* Wait until output of the PLL is selected */
  }
  /*** End of PE initialization code after reset ***/

  /*** !!! Here you can place your own code after PE initialization using property "User code after PE initialization" on the build options tab. !!! ***/

}



/*
** ===================================================================
**     Method      :  PE_low_level_init (component MKL25Z128LK4)
**
**     Description :
**         Initializes beans and provides common register initialization. 
**         The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
      /* Initialization of the SIM module */
  /* PORTA_PCR4: ISF=0,MUX=7 */
  PORTA_PCR4 = (uint32_t)((PORTA_PCR4 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK
               )) | (uint32_t)(
                PORT_PCR_MUX(0x07)
               ));
        /* Initialization of the RCM module */
  /* RCM_RPFW: RSTFLTSEL=0 */
  RCM_RPFW &= (uint8_t)~(uint8_t)(RCM_RPFW_RSTFLTSEL(0x1F));
  /* RCM_RPFC: RSTFLTSS=0,RSTFLTSRW=0 */
  RCM_RPFC &= (uint8_t)~(uint8_t)(
               RCM_RPFC_RSTFLTSS_MASK |
               RCM_RPFC_RSTFLTSRW(0x03)
              );
      /* Initialization of the PMC module */
  /* PMC_LVDSC1: LVDACK=1,LVDIE=0,LVDRE=1,LVDV=0 */
  PMC_LVDSC1 = (uint8_t)((PMC_LVDSC1 & (uint8_t)~(uint8_t)(
                PMC_LVDSC1_LVDIE_MASK |
                PMC_LVDSC1_LVDV(0x03)
               )) | (uint8_t)(
                PMC_LVDSC1_LVDACK_MASK |
                PMC_LVDSC1_LVDRE_MASK
               ));
  /* PMC_LVDSC2: LVWACK=1,LVWIE=0,LVWV=0 */
  PMC_LVDSC2 = (uint8_t)((PMC_LVDSC2 & (uint8_t)~(uint8_t)(
                PMC_LVDSC2_LVWIE_MASK |
                PMC_LVDSC2_LVWV(0x03)
               )) | (uint8_t)(
                PMC_LVDSC2_LVWACK_MASK
               ));
  /* PMC_REGSC: BGEN=0,ACKISO=0,BGBE=0 */
  PMC_REGSC &= (uint8_t)~(uint8_t)(
                PMC_REGSC_BGEN_MASK |
                PMC_REGSC_ACKISO_MASK |
                PMC_REGSC_BGBE_MASK
               );
  /* SMC_PMPROT: ??=0,??=0,AVLP=0,??=0,ALLS=0,??=0,AVLLS=0,??=0 */
  SMC_PMPROT = 0x00U;                  /* Setup Power mode protection register */
  /* Common initialization of the CPU registers */
  /* PORTB_PCR0: ISF=0,MUX=0 */
  PORTB_PCR0 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTB_PCR1: ISF=0,MUX=0 */
  PORTB_PCR1 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTB_PCR2: ISF=0,MUX=0 */
  PORTB_PCR2 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTB_PCR3: ISF=0,MUX=0 */
  PORTB_PCR3 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* NVIC_IPR3: PRI_15=0 */
  NVIC_IPR3 &= (uint32_t)~(uint32_t)(NVIC_IP_PRI_15(0xFF));
  /* NVIC_ISER: SETENA|=1 */
  NVIC_ISER |= NVIC_ISER_SETENA(0x01);
  /* NVIC_IPR0: PRI_2=0,PRI_1=0,PRI_0=0 */
  NVIC_IPR0 &= (uint32_t)~(uint32_t)(
                NVIC_IP_PRI_2(0xFF) |
                NVIC_IP_PRI_1(0xFF) |
                NVIC_IP_PRI_0(0xFF)
               );
  /* PORTA_PCR20: ISF=0,MUX=7 */
  PORTA_PCR20 = (uint32_t)((PORTA_PCR20 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* NVIC_IPR1: PRI_6=0 */
  NVIC_IPR1 &= (uint32_t)~(uint32_t)(NVIC_IP_PRI_6(0xFF));
  /* ### Serial_LDD "IO1" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)IO1_Init(NULL);
  /* ### Init_ADC "ADC1" init code ... */
  /* ### Call "ADC1_Init();" init method in a user code, i.e. in the main code */

  /* ### Note:   To enable automatic calling of the "ADC1" init code here,
                 the 'Call Init method' property must be set to 'yes'.
   */
  /* ### Init_DMA "DMA1" init code ... */
  /* ### Call "DMA1_Init();" init method in a user code, i.e. in the main code */

  /* ### Note:   To enable automatic calling of the "DMA1" init code here,
                 the 'Call Init method' property must be set to 'yes'.
   */
  /* ### TimerUnit_LDD "TU1" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)TU1_Init(NULL);
  /* ### BitIO_LDD "BitIoLdd1" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)BitIoLdd1_Init(NULL);
  /* ### LED "IR" init code ... */
  IR_Init(); /* initialize LED driver */
  /* ### PWM_LDD "PwmLdd1" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)PwmLdd1_Init(NULL);
  /* ### PWM_LDD "PwmLdd2" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)PwmLdd2_Init(NULL);
  __EI();
}

/* END Cpu. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
