#ifndef MENU_LIB_H
#define MENU_LIB_H

#include <stdint.h>

#include "../libs/ssd1306_lib.h"
#include "../libs/joystick_lib.h"

#include <util/delay.h>

//static uint8_t *word_menu[] = {&ttf_eng_m[0],&ttf_eng_e[0],&ttf_eng_n[0],&ttf_eng_u[0]};

#define menu 0
#define color 4
#define segment 7
#define settings 5

#define red 1
#define green 2
#define blue 3

#define first 4
#define second 5

#define sens 6
#define vers 7

struct params_
{
	union
	{
		uint8_t all;
		struct {
			uint8_t current_state;
			uint8_t current_value;

			uint8_t current_red;
			uint8_t current_green;
			uint8_t current_blue;
			uint8_t current_first;
			uint8_t current_second;
			uint8_t current_sens;
			uint8_t current_vers;
			uint8_t current_menu_pos:2;
			 
		};
	};
	
}; typedef struct params_ params_t;

void menu_set_item_menu(uint8_t item);
void menu_set_paragraph(uint8_t paragraph);
void menu_set_params_value(uint8_t number);
void params_default_conf(void);
void menu_switch_paragraph(void);
void menu_ok(void);
void menu_up(void);
void menu_down(void);
void menu_right(uint8_t* value);
void menu_left(uint8_t* value);
void menu_handler(void);

void menu_set_params_state(void);
#endif