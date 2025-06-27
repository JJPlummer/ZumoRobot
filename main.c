// Binghamton University, EECE 287 Sophomore Design
// Final Project #
// Instructor: Meghana Jain

//Group: 
//Student Names: 

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h> 
#include "zumo_drivers.h"


#define LEFT_MOTOR_LOCATION 6
#define LEFT_MOTOR_DIRECTION 2 
#define RIGHT_MOTOR_LOCATION 5
#define RIGHT_MOTOR_DIRECTION 1

#define PWM_TOP 255 
#define INCREMENT 5

bool direction = false;

void configure_Left_Motor()
{
	DDRB &= ~(1<<LEFT_MOTOR_LOCATION);
	DDRB |= (1<<LEFT_MOTOR_DIRECTION);
}	
void configure_Right_Motor()
{
	DDRB &= ~(1<<RIGHT_MOTOR_LOCATION);
	DDRB |= (1<<RIGHT_MOTOR_DIRECTION);
}	
void Left_Motor_On()
{
	DDRB |= (1<<LEFT_MOTOR_LOCATION);
}
void Right_Motor_On()
{
	DDRB |= (1<<RIGHT_MOTOR_LOCATION);
}
void BOTH_Motors_On()
{
	Right_Motor_On();
	Left_Motor_On();
}
void Left_Motor_Forward()
{
	PORTB &= ~(1<<LEFT_MOTOR_DIRECTION);
}
void Right_Motor_Forward()
{
	PORTB &= ~(1<<RIGHT_MOTOR_DIRECTION);
}
void BOTH_Motors_Forward()
{
	Left_Motor_Forward();
	Right_Motor_Forward();
}
void Left_Motor_Reverse()
{
	PORTB |= (1<<LEFT_MOTOR_DIRECTION);

}
void Right_Motor_Reverse()
{
	PORTB |= (1<<RIGHT_MOTOR_DIRECTION);
}
void BOTH_Motors_Reverse()
{
	Left_Motor_Reverse();
	Right_Motor_Reverse();
}
void change_direction()
{
	direction = !direction;
	if(!direction){
		BOTH_Motors_Forward();
	}else{
		Left_Motor_Reverse();
		Right_Motor_Reverse();
	}
}
void Left_Motor_Off()
{
	DDRB &= ~(1<<LEFT_MOTOR_LOCATION);
}
void Right_Motor_Off()
{
	DDRB &= ~(1<<RIGHT_MOTOR_LOCATION);
}
void BOTH_Motors_Off()
{
	
	Left_Motor_Off();
	Right_Motor_Off();
}
void turn_Right()
{
	BOTH_Motors_On();
	Left_Motor_Forward();
	Right_Motor_Reverse();
	
}
void turn_Left()
{
	BOTH_Motors_On();
	Right_Motor_Forward();
	Left_Motor_Reverse();
	
}
void set_speed(uint8_t speed)
{
	OCR1A = speed;
	OCR1B = speed;
}
void display(uint8_t row, uint8_t col, uint8_t val)
{
		oled_clear();
		oled_set_cursor(row,col);
		oled_put_hex(val & 0x0F);
}
int main(){
	uint8_t speed = 40;
	uint32_t quad_start;
	uint32_t quad_current;
	configure_zumo();
	configure_Left_Motor();
	configure_Right_Motor();
	oled_clear();
	unsigned int x_counter=0; //Input for x axis 0-60 
	unsigned int y_counter=0; //Input for y axis 0-60 
	bool is_A_button_pressed = false;
	bool is_B_button_pressed = false;
	bool is_C_button_pressed = false;
	bool runloop = true;

	
	while(runloop){//First loop for inputing location and starting the run
		set_speed(speed);
		if(button_a_is_down() && !is_A_button_pressed){  	 	 	
			is_A_button_pressed = true;
 	 	} else if(button_a_is_up() && is_A_button_pressed){
			is_A_button_pressed = false;
			x_counter++;
		}	
		if(button_b_is_down() && !is_B_button_pressed){  	 	 	
			is_B_button_pressed = true;
 	 	} else if(button_b_is_up() && is_B_button_pressed){
			is_B_button_pressed = false;
			y_counter++;
		}
		if(button_c_is_down() && !is_C_button_pressed){  	 	 	
			is_C_button_pressed = true;
 	 	} else if(button_c_is_up() && is_C_button_pressed){
			runloop = false;
		}
		if(x_counter>60) x_counter=0;
		if(y_counter>60) y_counter=0;
		oled_set_cursor(1,1);//X on oled screen
		oled_put_hex(x_counter>>4);
		oled_put_hex(x_counter);
		
		oled_set_cursor(2,2); //Y on oled Screen
		oled_put_hex(y_counter>>4);
		oled_put_hex(y_counter);
	}//End of first loop where we get the x and y location and display them on the oled
	int X_inch =  abs((x_counter-30)*200);//Arbratrary value for distance found through trial and error
	int Y_inch =  abs((y_counter-30)*200);
	runloop = true;
	quad_start=get_left_quadrature_counter();//Get quadrature values
	quad_current=get_left_quadrature_counter();
	if(x_counter<30)//Check condition of the x input and decides direction
	{
		BOTH_Motors_Reverse();
	}
	else
	{
		BOTH_Motors_Forward();
	}
	while(runloop)//Moving in along the x axis
	{
		quad_current = get_left_quadrature_counter();//Constantly updating
		set_speed(40);
		BOTH_Motors_On();
		if(X_inch<=(quad_current-quad_start))//Uses value from early and difference between quadrature values then shuts off and goes to next phase
		{
			BOTH_Motors_Off();
			runloop = false;
		}
	}
	int distance_turned = 660;//Turn 90 degrees found through trial and error
	runloop = true;
	quad_start = get_left_quadrature_counter();//works the same as last phase but for turning
	quad_current = get_left_quadrature_counter();
	turn_Left();
	while(runloop)//Turning
	{
		quad_current = get_left_quadrature_counter();
		set_speed(40);
		BOTH_Motors_On();
		if(distance_turned<=(quad_current-quad_start))
		{
			BOTH_Motors_Off();
			runloop = false;
		}
	}
	runloop = true;
	quad_start=get_left_quadrature_counter();//Get quadrature values
	quad_current=get_left_quadrature_counter();
	BOTH_Motors_Forward();
	if(y_counter<30)//Checks y input and decides what direction to go in
	{
		BOTH_Motors_Reverse();
	}
	else
	{
		BOTH_Motors_Forward();
	}
	while(runloop)//Moving in along the y axis
	{
		quad_current = get_left_quadrature_counter();
		set_speed(40);
		BOTH_Motors_On();
		if(Y_inch<=(quad_current-quad_start))
		{
			BOTH_Motors_Off();
			runloop = false;
		}
	}
	return 0;
}
	
	