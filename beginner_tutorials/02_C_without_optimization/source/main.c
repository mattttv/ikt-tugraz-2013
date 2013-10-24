
#include <stdint.h>


//#define GPIO_FSEL_ADDR			( GPIO_BASE_ADDR + 0x00 )
//#define GPIO_SET_ADDR			( GPIO_BASE_ADDR + 0x1C )
//#define GPIO_CLR_ADDR			( GPIO_BASE_ADDR + 0x28 )

#define GPIO_PIN_LED_ACT	16

#define GPIO_PIN_FKT_INP	0
#define GPIO_PIN_FKT_OUT	1

int main()
{
	//store GPIO - adress
	//////////////////////
	//ldr r0,=0x20200000
	#define GPIO_FSEL_ADDR		0x20200000
	
	//create value for led=output
	//////////////////////
	//mov r1,#1
	//lsl r1,#18
	int32_t led_type_output_value =  GPIO_PIN_FKT_OUT << 18;
	
	//set led as output
	//////////////////////
	//str r1,[r0,#4]
	
	//#define mmio32(x)   (*(volatile uint32_t *)(x))
	//mmio32(GPIO_FSEL_ADDR + 4) = led_output_value;
	//TODO CORRECT?
	(* (volatile uint32_t * ) (GPIO_FSEL_ADDR + 4) ) = led_type_output_value;					

	//create value for led=1
	////////////////////////
	//mov r1,#1
	//lsl r1,#16
	int32_t led_output_value = 1 << 16;
	
	
	while(1) {
		
		//clear led-pin
		////////////////////////
		//str r1,[r0,#40]
	
	(* (volatile uint32_t * ) (GPIO_FSEL_ADDR + 40) ) = led_output_value;					

	
		//// TODO BUSY SLEEP
		int32_t volatile wait = 0;
		int32_t volatile wait2 = 0;
		
		/*
		#define DELAY 20000000
		wait2 = 0;
		for(wait = DELAY; wait != 0; wait--){
			wait2 = wait * wait; //NOP?
			__asm__("NOP");
		}	
		*/
		
		__asm__("mov r2,#0x3F0000\n\t"
			  "wait_first$:\n\t"
			  "sub r2,#1\n\t"
			  "cmp r2,#0\n\t"
			  "bne wait_first$");
	
		////set led-pin (turn off)
		//str r1,[r0,#28]
	(* (volatile uint32_t * ) (GPIO_FSEL_ADDR + 28) ) = led_output_value;	
				
	// tell the compiler not to throw this away by deleting -O2 in the makefile (line 66) 
	__asm__("mov r2,#0x3F0000\n\t"
			  "wait_second$:\n\t"
			  "sub r2,#1\n\t"
			  "cmp r2,#0\n\t"
			  "bne wait_second$");
	
	
	}	
	return 0;
}

