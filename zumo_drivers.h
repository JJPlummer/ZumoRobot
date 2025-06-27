/*
 * zumo_drivers.h
 *
 * Created: 1/16/2023 1:16:18 PM
 *  Author: Doug Summerville
 */ 


#ifndef ZUMO_DRIVERS_H_
#define ZUMO_DRIVERS_H_

#include <stdbool.h>
#include <stdint.h>

void configure_zumo();
_Bool button_a_is_up();
_Bool button_a_is_down();
_Bool button_b_is_up();
_Bool button_b_is_down();
_Bool button_c_is_up();
_Bool button_c_is_down();
uint32_t get_time();
void oled_set_cursor( uint8_t row, uint8_t col);
void oled_clear();
void oled_put_space();
void oled_put_hex(uint8_t hex_digit);
uint32_t get_right_quadrature_counter();
uint32_t get_left_quadrature_counter();

#endif /* ZUMO_DRIVERS_H_ */