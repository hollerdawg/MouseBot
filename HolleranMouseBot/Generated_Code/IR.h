/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : IR.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : LED
**     Version     : Component 01.062, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-10-26, 20:47, # CodeGen: 69
**     Abstract    :
**          This component implements a universal driver for a single LED.
**     Settings    :
**          Component name                                 : IR
**          Turned On with initialization                  : no
**          HW Interface                                   : 
**            On/Off                                       : Enabled
**              Pin                                        : LEDpin
**            PWM                                          : Disabled
**            High Value means ON                          : no
**          Shell                                          : Disabled
**     Contents    :
**         Init       - void IR_Init(void);
**         Deinit     - void IR_Deinit(void);
**         On         - void IR_On(void);
**         Off        - void IR_Off(void);
**         Neg        - void IR_Neg(void);
**         Get        - byte IR_Get(void);
**         Put        - void IR_Put(byte val);
**         SetRatio16 - void IR_SetRatio16(word ratio);
**
**     License   : Open Source (LGPL)
**     Copyright : Erich Styger, 2013, all rights reserved.
**     Web       : www.mcuoneclipse.com
**     This an open source software implementing a driver using Processor Expert.
**     This is a free software and is opened for education, research and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file IR.h
** @version 01.00
** @brief
**          This component implements a universal driver for a single LED.
*/         
/*!
**  @addtogroup IR_module IR module documentation
**  @{
*/         

#ifndef __IR_H
#define __IR_H

/* MODULE IR. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "LEDpin1.h"

#include "Cpu.h"

#define IR_ClrVal()    LEDpin1_ClrVal() /* put the pin on low level */
#define IR_SetVal()    LEDpin1_SetVal() /* put the pin on high level */
#define IR_SetInput()  LEDpin1_SetInput() /* use the pin as input pin */
#define IR_SetOutput() LEDpin1_SetOutput() /* use the pin as output pin */

#define IR_PARSE_COMMAND_ENABLED  0 /* set to 1 if method ParseCommand() is present, 0 otherwise */


#define IR_On() LEDpin1_ClrVal()
/*
** ===================================================================
**     Method      :  IR_On (component LED)
**     Description :
**         This turns the LED on.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define IR_Off() LEDpin1_SetVal()
/*
** ===================================================================
**     Method      :  IR_Off (component LED)
**     Description :
**         This turns the LED off.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define IR_Neg() LEDpin1_NegVal()
/*
** ===================================================================
**     Method      :  IR_Neg (component LED)
**     Description :
**         This negates/toggles the LED
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define IR_Get() (!(LEDpin1_GetVal()))
/*
** ===================================================================
**     Method      :  IR_Get (component LED)
**     Description :
**         This returns logical 1 in case the LED is on, 0 otherwise.
**     Parameters  : None
**     Returns     :
**         ---             - Status of the LED (on or off)
** ===================================================================
*/

#define IR_Init() IR_Off()
/*
** ===================================================================
**     Method      :  IR_Init (component LED)
**     Description :
**         Performs the LED driver initialization.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define IR_Put(val)  ((val) ? IR_On() : IR_Off())
/*
** ===================================================================
**     Method      :  IR_Put (component LED)
**     Description :
**         Turns the LED on or off.
**     Parameters  :
**         NAME            - DESCRIPTION
**         val             - value to define if the LED has to be on or
**                           off.
**     Returns     : Nothing
** ===================================================================
*/

void IR_Deinit(void);
/*
** ===================================================================
**     Method      :  IR_Deinit (component LED)
**     Description :
**         Deinitializes the driver
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void IR_SetRatio16(word ratio);
/*
** ===================================================================
**     Method      :  IR_SetRatio16 (component LED)
**     Description :
**         Method to specify the duty cycle. If using a PWM pin, this
**         means the duty cycle is set. For On/off pins, values smaller
**         0x7FFF means off, while values greater means on.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ratio           - Ratio value, where 0 means 'off' and
**                           0xffff means 'on'
**     Returns     : Nothing
** ===================================================================
*/

/* END IR. */

#endif
/* ifndef __IR_H */
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
