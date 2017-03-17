/** ###################################################################
 **     Filename    : ProcessorExpert.c
 **     Project     : ProcessorExpert
 **     Processor   : MKL25Z128VLK4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2013-01-03, 14:56, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CsIO1.h"
#include "IO1.h"
#include "ADC1.h"
#include "DMA1.h"
#include "TU1.h"
#include "IR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "right.h"
#include "PwmLdd1.h"
#include "TU2.h"
#include "left.h"
#include "PwmLdd2.h"
#include "w.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "my.h"

// size of the channel configuration array
#define ADC_CHANNELS_COUNT 4
// delay time for getting ADC info
#define T 1000
// how many samples are to be taken per average
#define samples 4
// value to determine a sensor "triggered"
#define sens 200
// PWM compare times
#define lFwd 22000-1700
#define rFwd 22000-1300
#define stop 22000-1500
#define lBack 22000-1300
#define rBack 22000-1700
// Turn delay time
#define Twait 700
//number of sensors on robot
#define SensNum 4

// value for CFG2 array selecting MUX A pins or default
#define PIN_A (0) 
// value for CFG2 array selecting MUX B pins
#define PIN_B (ADC_CFG2_MUXSEL_MASK)

// configuration array for channels - channel numbers. Should ends with 0x1F which stops conversion
// seconcd onfiguration array coreesponding to channels selecting A/B pins
// For example: 0 + PIN_A corresponds to the pin ADC0_SE0,   5 + PIN_5 selects the pin ADC0_SE5b
// You can use these arrays to reorder the measurement as you need
//channels 11 and 15 correlate to other ADC channels on arduino shields
const uint8_t ChannelsCfg [ADC_CHANNELS_COUNT + 1] =  {    8,     9,    12,    13,/*    11,    15,*/    0x1F };
const uint8_t ChannelsCfg2[ADC_CHANNELS_COUNT + 1] =  {PIN_A, PIN_A, PIN_B, PIN_A,/* PIN_A, PIN_A,*/    0    };

// buffer for resulting measured values and for calculating average values
uint16_t MeasuredValues[ADC_CHANNELS_COUNT];
uint16_t FirstVals[ADC_CHANNELS_COUNT];
int AllMeasures[ADC_CHANNELS_COUNT];
static int CorrectedVals[ADC_CHANNELS_COUNT];

//used as a "register" to communicate which sensors are triggered
unsigned int sensors = 0x0;

// flag for end of measurement
bool Measured;
bool True = TRUE;
bool False = FALSE;

//Grabs all the ADC Values using the DMA and then sets the ADC values to an array
void getADC(void){
	int x = 0;
	// clear flag  
	Measured = FALSE;	
	// reset DMA0 destination pointer to beginning of the buffer 
	DMA_DAR0 = (uint32_t) &MeasuredValues;
	// reset DMA1 source pointer (MUX switching writes)
	DMA_SAR1 = (uint32_t) &ChannelsCfg2;
	// reset DMA2 source pointer (channel switching and conversion start writes)
	DMA_SAR2 = (uint32_t) &ChannelsCfg;
	// number of total bytes to be transfered from the ADC result register A 
	DMA_DSR_BCR0 = ADC_CHANNELS_COUNT * 2;
	// set number of total bytes to be transfered to the ADC0_CFG2 
	DMA_DSR_BCR1 = ADC_CHANNELS_COUNT + 1;
	// set number of total bytes to be transfered to the ADC0_SC1A.  
	DMA_DSR_BCR2 = ADC_CHANNELS_COUNT + 1;
	// start first DMA1 transfer (selects mux, then fires channel 2 to select channel which starts the conversion)
	DMA_DCR1 |= DMA_DCR_START_MASK;
	// wait till it's all measured
	while (!Measured) {}
	for(x=0; x<ADC_CHANNELS_COUNT; x++){
		MeasuredValues[x] = ~MeasuredValues[x];
	}
}

/*
 * sensors contains a binary representation of the sensors that 
 * are triggered. sensors will then be analyzed by move() and will
 * move the robot according to what sensors are triggered
 * 
 * bit 0 : Rear
 * bit 1 : Left
 * bit 2 : Right
 * bit 3 : Front
 * 
 * This function will determine what actions are to be taken when sensors are triggered,
 * this is done by telling the servos which direction to turn.
 */

void move(){
		switch(sensors){
		case 0x0	:	//sensors detect nothing, no movement
			right_SetDutyUS(stop);
			left_SetDutyUS(stop);
			break;
		case 0x1	:	//something in the rear, move forward
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lFwd);
			break;
		case 0x2	:	//something to the left, turn right
			right_SetDutyUS(rBack);
			left_SetDutyUS(lFwd);
			break;
		case 0x3	:	//something left and rear, turn right, then forward
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lFwd);
			w_Waitms(Twait);
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lFwd);
			break;
		case 0x4	:	//something to the right, turn left
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lBack);
			break;
		case 0x5	:	//something to the right and rear, turn left, then forward
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lBack);
			w_Waitms(Twait);
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lFwd);
			break;
		case 0x6	:	//something right and left, move forward
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lFwd);
			break;
		case 0x7	:	//something right, left, and rear, move forward
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lFwd);
			break;
		case 0x8	:	//something in front, move backward
			right_SetDutyUS(rBack);
			left_SetDutyUS(lBack);
			break;
		case 0x9	:	//something front and back, zero turn right, then forward
			right_SetDutyUS(rBack);
			left_SetDutyUS(lFwd);
			w_Waitms(Twait/2);
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lFwd);
			break;
		case 0xA	:	//something front and left, turn left, then backward
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lBack);
			w_Waitms(Twait);
			right_SetDutyUS(rBack);
			left_SetDutyUS(lBack);
			break;
		case 0xB	:	//something left, front, and back, zero turn right, then forward
			right_SetDutyUS(rBack);
			left_SetDutyUS(lFwd);
			w_Waitms(Twait);
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lFwd);
			break;
		case 0xC	:	//something front and right, turn right, then backward
			right_SetDutyUS(rBack);
			left_SetDutyUS(lFwd);
			w_Waitms(Twait/2);
			right_SetDutyUS(rBack);
			left_SetDutyUS(lBack);
			break;
		case 0xD	:	//something front, right, and rear, zero turn left, then foward
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lBack);
			w_Waitms(Twait);
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lFwd);
			break;
		case 0xE	:	//something foward, left, and right, move backward
			right_SetDutyUS(rBack);
			left_SetDutyUS(lBack);
			break;
		case 0xF	:	//sensors detect everything!! spin in a circle until clear.
			right_SetDutyUS(rFwd);
			left_SetDutyUS(lBack);
			break;
		default		:
			right_SetDutyUS(stop);
			left_SetDutyUS(stop);
		}
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void){
	/*lint -restore Enable MISRA rule (6.3) checking. */
	/* Write your local variable definition here */
	int i = 0;
	int n = 0;
	int movWait = 0;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	printf ("Hello!\r\n");

	// reset flag 
	Measured = FALSE;
	
	// Initialize ADC now
	ADC1_Init();
	// Initialize DMA now  
	DMA1_Init();
	IR_Init();
	IR_Put(1);
	// loop forever  
	while (TRUE) {
		for(i = 0; i<ADC_CHANNELS_COUNT; i++){
				AllMeasures[i] = 0;
		}
		for (i=0; i<samples; i++){
			//Turn LEDs off
			IR_Put(1);
			w_Waitus(T);
			getADC();


			for(n = 0; n<ADC_CHANNELS_COUNT; n++){
				FirstVals[n] = MeasuredValues[n];
			}

			//Turn LEDs on
			IR_Put(0);
			w_Waitus(T);
			getADC();

			for(n = 0; n<ADC_CHANNELS_COUNT; n++){
				AllMeasures[n] += MeasuredValues[n]-FirstVals[n];
			}
		}
		
		for(n = 0; n<ADC_CHANNELS_COUNT; n++){
			CorrectedVals[n] = AllMeasures[n]/samples;
			if(CorrectedVals[n] < 0)
				CorrectedVals[n] = 0;
		}
		
		// the code below enables the robot kl25z to talk to the
		// user through the virtual terminal connected the the SDA Debugger.
		// this will output the corrected, averaged samples.
		// WARNING: it is advised not to used printf in embedded projects.
		// this is because it takes up a lot of memory.
		
//		printf("corrected");
//		for(i = 0; i<ADC_CHANNELS_COUNT; i++){
//			printf ("%7u", (int) CorrectedVals[i]);
//		}
//		printf("\n");
		
		/*
		 * sensors contains a binary representation of the sensors that 
		 * are triggered. sensors will then be analyzed by move() and will
		 * move the robot according to what sensors are triggered
		 * 
		 * bit 0 : Rear
		 * bit 1 : Left
		 * bit 2 : Right
		 * bit 3 : Front
		 * 
		 */
		for(i=0; i<SensNum; i++){
			if(CorrectedVals[i]>sens){
				switch(i){
				case 0	:
					sensors |= 0x1;
					break;
				case 1	:
					sensors |= 0x2;
					break;
				case 2	:
					sensors |= 0x4;
					break;
				case 3	:
					sensors |= 0x8;
					break;
				}
			}
			else
				switch(i){
				case 0	:
					sensors &= ~0x1;
					break;
				case 1	:
					sensors &= ~0x2;
					break;
				case 2	:
					sensors &= ~0x4;
					break;
				case 3	:
					sensors &= ~0x8;
					break;
				}
		}
		
		// Make the movements a bit less jittery by adding a delay
		// to changing the direction of rotation to the servos.
		movWait += 1;
		if(movWait >= 10){
			movWait = 0;
			move();

//			This commented code is used for calibration of servos.
//			right_SetDutyUS(stop);
//			left_SetDutyUS(stop);
			
		}
	}
		/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
	}
