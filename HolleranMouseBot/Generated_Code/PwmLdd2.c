/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PwmLdd2.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : PWM_LDD
**     Version     : Component 01.013, Driver 01.03, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-11-15, 18:04, # CodeGen: 88
**     Abstract    :
**          This component implements a pulse-width modulation generator
**          that generates signal with variable duty and fixed cycle.
**          This PWM component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
**     Settings    :
**          Component name                                 : PwmLdd2
**          Period device                                  : TPM0_MOD
**          Duty device                                    : TPM0_C1V
**          Output pin                                     : ADC0_SE5b/PTD1/SPI0_SCK/TPM0_CH1
**          Output pin signal                              : 
**          Counter                                        : TPM0_CNT
**          Interrupt service/event                        : Disabled
**          Period                                         : 22 ms
**          Starting pulse width                           : 20500 �s
**          Initial polarity                               : low
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnEnd                                      : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**          Referenced components                          : 
**            Linked component                             : TU2
**     Contents    :
**         Init       - LDD_TDeviceData* PwmLdd2_Init(LDD_TUserData *UserDataPtr);
**         SetRatio16 - LDD_TError PwmLdd2_SetRatio16(LDD_TDeviceData *DeviceDataPtr, uint16_t Ratio);
**         SetDutyUS  - LDD_TError PwmLdd2_SetDutyUS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time);
**         SetDutyMS  - LDD_TError PwmLdd2_SetDutyMS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time);
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
** @file PwmLdd2.c
** @version 01.03
** @brief
**          This component implements a pulse-width modulation generator
**          that generates signal with variable duty and fixed cycle.
**          This PWM component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
*/         
/*!
**  @addtogroup PwmLdd2_module PwmLdd2 module documentation
**  @{
*/         

/* MODULE PwmLdd2. */

#include "PwmLdd2.h"
/* {Default RTOS Adapter} No RTOS includes */

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TDeviceData *LinkedDeviceDataPtr;
  bool EnUser;                         /* Enable/Disable device */
  uint16_t RatioStore;                 /* Ratio of L-level to H-level */
  LDD_TUserData *UserDataPtr;          /* RTOS device data structure */
} PwmLdd2_TDeviceData;

typedef PwmLdd2_TDeviceData *PwmLdd2_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static PwmLdd2_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;

#define CHANNEL 0x01U
/* Internal method prototypes */
static void SetRatio(LDD_TDeviceData *DeviceDataPtr);
/*
** ===================================================================
**     Method      :  PwmLdd2_Init (component PWM_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* PwmLdd2_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  PwmLdd2_TDeviceData *DeviceDataPrv;
  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  DeviceDataPrv->EnUser = TRUE;        /* Set the flag "device enabled" */
  DeviceDataPrv->RatioStore = 0xF03CU; /* Ratio after initialization */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_PwmLdd2_ID,DeviceDataPrv);
  DeviceDataPrv->LinkedDeviceDataPtr = TU2_Init((LDD_TUserData *)NULL);
  if (DeviceDataPrv->LinkedDeviceDataPtr == NULL) { /* Is initialization of TimerUnit unsuccessful? */
    /* Unregistration of the device structure */
    PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_PwmLdd2_ID);
    /* Deallocation of the device structure */
    /* {Default RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated */
    return NULL;                       /* If so, then the PWM initialization is also unsuccessful */
  }
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
}

/*
** ===================================================================
**     Method      :  PwmLdd2_SetRatio16 (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets a new duty-cycle ratio. Ratio is expressed
**         as a 16-bit unsigned integer number. 0 - FFFF value is
**         proportional to ratio 0 - 100%. The method is available
**         only if it is not selected list of predefined values in
**         [Starting pulse width] property. 
**         Note: Calculated duty depends on the timer possibilities and
**         on the selected period.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Ratio           - Ratio to set. 0 - 65535 value is
**                           proportional to ratio 0 - 100%
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError PwmLdd2_SetRatio16(LDD_TDeviceData *DeviceDataPtr, uint16_t Ratio)
{
  PwmLdd2_TDeviceData *DeviceDataPrv = (PwmLdd2_TDeviceData *)DeviceDataPtr;

  DeviceDataPrv->RatioStore = Ratio;   /* Store new value of the ratio */
  SetRatio(DeviceDataPtr);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  PwmLdd2_SetDutyUS (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets the new duty value of the output signal.
**         The duty is expressed in microseconds as a 16-bit unsigned
**         integer number. The method is available only if it is not
**         selected list of predefined values in [Starting pulse width]
**         property.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Time            - Duty to set [in microseconds]
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
**                           ERR_MATH - Overflow during evaluation
**                           ERR_PARAM_RANGE - Parameter out of range
*/
/* ===================================================================*/
LDD_TError PwmLdd2_SetDutyUS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time)
{
  PwmLdd2_TDeviceData *DeviceDataPrv = (PwmLdd2_TDeviceData *)DeviceDataPtr;
  LDD_TimerUnit_Tfloat rtval;          /* Result of multiplication */

  /* Time test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Time > 0x5555U) {                /* Is the given value out of range? */
    return ERR_PARAM_RANGE;            /* If yes then error */
  }
  rtval = Time * 3.0F;                 /* Multiply given value and actual clock configuration coefficient */
  if (rtval > 0xFFFFUL) {              /* Is the result greater than 65535 ? */
    DeviceDataPrv->RatioStore = 0xFFFFU; /* If yes then use maximal possible value */
  }
  else {
    DeviceDataPrv->RatioStore = (uint16_t)rtval;
  }
  SetRatio(DeviceDataPtr);             /* Calculate and set up new appropriate values of the duty register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  PwmLdd2_SetDutyMS (component PWM_LDD)
*/
/*!
**     @brief
**         This method sets the new duty value of the output signal.
**         The duty is expressed in milliseconds as a 16-bit unsigned
**         integer number. The method is available only if it is not
**         selected list of predefined values in [Starting pulse width]
**         property.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Time            - Duty to set [in milliseconds]
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
**                           ERR_MATH - Overflow during evaluation
**                           ERR_PARAM_RANGE - Parameter out of range
*/
/* ===================================================================*/
LDD_TError PwmLdd2_SetDutyMS(LDD_TDeviceData *DeviceDataPtr, uint16_t Time)
{
  PwmLdd2_TDeviceData *DeviceDataPrv = (PwmLdd2_TDeviceData *)DeviceDataPtr;
  LDD_TimerUnit_Tfloat rtval;          /* Result of multiplication */

  /* Time test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Time > 0x16U) {                  /* Is the given value out of range? */
    return ERR_PARAM_RANGE;            /* If yes then error */
  }
  rtval = Time * 3000.000000045776F;   /* Multiply given value and actual clock configuration coefficient */
  if (rtval > 0xFFFFUL) {              /* Is the result greater than 65535 ? */
    DeviceDataPrv->RatioStore = 0xFFFFU; /* If yes then use maximal possible value */
  }
  else {
    DeviceDataPrv->RatioStore = (uint16_t)rtval;
  }
  SetRatio(DeviceDataPtr);             /* Calculate and set up new appropriate values of the duty register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SetRatio (component PWM_LDD)
**
**     Description :
**         This method calculates new value of duty compare register from 
**         variable RatioStore.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetRatio(LDD_TDeviceData *DeviceDataPtr)
{
  PwmLdd2_TDeviceData *DeviceDataPrv = (PwmLdd2_TDeviceData*)DeviceDataPtr;
  uint16_t Period;
  uint16_t Duty;

  (void)TU2_GetPeriodTicks(DeviceDataPrv->LinkedDeviceDataPtr, &Period);
  if (Period == 0U) {
    Duty = DeviceDataPrv->RatioStore;
  }
  else {
    Duty = (uint16_t)((((uint32_t)(Period) * DeviceDataPrv->RatioStore) + 0x8000) >> 0x10);
  }
  (void)TU2_SetOffsetTicks(DeviceDataPrv->LinkedDeviceDataPtr, CHANNEL, Duty);
}
/* END PwmLdd2. */

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
