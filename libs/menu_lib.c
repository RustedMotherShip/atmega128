#include "menu_lib.h"
#include "../ttf/rus.h"
#include "../ttf/eng.h"
#include "../ttf/symbols.h"

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
			uint8_t current_first:4;
			uint8_t current_second:4;
			uint8_t current_sens;
			uint8_t current_vers;
			uint8_t current_menu_pos:2;
			 
		};
	};
	
} typedef params_t;

params_t params_value;

void menu_up(void)
{
	params_value.current_menu_pos--;
	if(params_value.current_menu_pos == 3)
		params_value.current_menu_pos = 2;
}
void menu_down(void)
{
	params_value.current_menu_pos++;
	if(params_value.current_menu_pos == 3)
		params_value.current_menu_pos = 0;
}

void menu_ok(void)
{
	if(!params_value.current_state)
		switch(params_value.current_menu_pos)
		{
			case 0:
				menu_set_paragraph(color);
			break;
			case 1:
				menu_set_paragraph(segment);
			break;	
			case 2:
				menu_set_paragraph(settings);
			break;
		}
	else
		params_value.current_state = 0;
}
void value_handler(uint8_t* value)
{
	while(params_value.current_state)
	{
	    switch(check_axis_x())
	    {
	        case left:
	            (*value)--;
	            menu_set_params_value(*value);
	        break;
	        case right:
	            (*value)++;
	            menu_set_params_value(*value);
	        break;
	        default:
	        break;
	    };
	    while(check_axis_x() != zero);
	}
} 
void params_default_conf(void)
{
	params_value.all = 0;

    params_value.current_red = 253;
    params_value.current_green = 254;
    params_value.current_blue = 255;

    params_value.current_first = 0;
    params_value.current_second = 15;

    params_value.current_sens = 10;
    params_value.current_vers = 0xA1;

    params_value.current_menu_pos = 0;
    params_value.current_state = 0;
}

void menu_border(void)
{
	//Верхняя полоса
	ssd1306_buffer_write(0,0,ttf_corner_left_up);
	for(int x = 1;x<15;x++)
		ssd1306_buffer_write(x*8,0,ttf_line_up);
	ssd1306_buffer_write(120,0,ttf_corner_right_up);
	//Левая полоса
	ssd1306_buffer_write(0,8,ttf_line_left);
	ssd1306_buffer_write(0,16,ttf_line_left);
	//Правая полоса
	ssd1306_buffer_write(120,8,ttf_line_right);
	ssd1306_buffer_write(120,16,ttf_line_right);
	//Нижняя полоса
	ssd1306_buffer_write(0,24,ttf_corner_left_down);
	for(int x = 1;x<15;x++)
		ssd1306_buffer_write(x*8,24,ttf_line_down);
	ssd1306_buffer_write(120,24,ttf_corner_right_down);
}

void menu_border_paragraph(uint8_t number_of_letters)
{
	//Верхняя полоса
	ssd1306_buffer_write(6,8,ttf_corner_left_up);
	ssd1306_buffer_write(6,16,ttf_corner_left_down);
	for(int x = 1;x<number_of_letters+1;x++)
		ssd1306_buffer_write(6+x*8,8,ttf_line_up);
	ssd1306_buffer_write(6+number_of_letters*8,8,ttf_corner_right_up);
	ssd1306_buffer_write(12+number_of_letters*8,0,ttf_line_left);
	
	//Нижняя полоса
	ssd1306_buffer_write(6,16,ttf_corner_left_down);
	for(int x = 1;x<number_of_letters+1;x++)
		ssd1306_buffer_write(6+x*8,16,ttf_line_down);
	ssd1306_buffer_write(6+number_of_letters*8,16,ttf_corner_right_down);
	ssd1306_buffer_write(12+number_of_letters*8,24,ttf_line_left);
	
}

void menu_border_item(uint8_t number_of_letters)
{
	//Боковая полоса
	ssd1306_buffer_write(12+number_of_letters*8,7,ttf_corner_left_down);
	for(int x = 1;x<14-number_of_letters;x++)
		ssd1306_buffer_write(12+number_of_letters*8+x*8,7,ttf_line_down);
	ssd1306_buffer_write(120,7,ttf_corner_right_down);

	//Нижняя полоса
	ssd1306_buffer_write(97,15,ttf_line_left);
	ssd1306_buffer_write(97,17,ttf_corner_left_down);
	ssd1306_buffer_write(104,17,ttf_line_down);
	ssd1306_buffer_write(112,17,ttf_line_down);
	ssd1306_buffer_write(120,17,ttf_line_down);
	
}

void menu_set_params_value(uint8_t number)
{

	uint8_t index = 0;
	static uint8_t *numbers[] = {&ttf_num_0[0],&ttf_num_1[0],&ttf_num_2[0],&ttf_num_3[0],&ttf_num_4[0],&ttf_num_5[0],&ttf_num_6[0],&ttf_num_7[0],&ttf_num_8[0],&ttf_num_9[0]};
	for(int i = 0;i<3;i++)
		ssd1306_buffer_write(117-8*i,15,ttf_void);
	ssd1306_send_buffer();
	do {
        ssd1306_buffer_write(117-8*index,15,numbers[number % 10]); // Получаем последнюю цифру
        number /= 10; // Убираем последнюю цифру
        index++;
    } while (number > 0);
    ssd1306_send_buffer();
}
void menu_switch_paragraph(void)
{
	
	ssd1306_buffer_clean();
				menu_border();
				menu_border_paragraph(4);

				ssd1306_buffer_write(10,12,ttf_rus_8);
		    	ssd1306_buffer_write(18,12,ttf_rus_3);
		    	ssd1306_buffer_write(26,12,ttf_rus_9);
		    	ssd1306_buffer_write(34,12,ttf_rus_20);

		    	ssd1306_buffer_write(48,4,ttf_rus_1);
		    	ssd1306_buffer_write(56,4,ttf_rus_2);
		    	ssd1306_buffer_write(64,4,ttf_rus_3);
		    	ssd1306_buffer_write(72,4,ttf_rus_4);
		    	ssd1306_buffer_write(106,4,ttf_void);

		    	ssd1306_buffer_write(48,12,ttf_rus_6);
		    	ssd1306_buffer_write(56,12,ttf_rus_3);
		    	ssd1306_buffer_write(64,12,ttf_rus_7);
		    	ssd1306_buffer_write(72,12,ttf_rus_8);
		    	ssd1306_buffer_write(80,12,ttf_rus_3);
		    	ssd1306_buffer_write(88,12,ttf_rus_9);
		    	ssd1306_buffer_write(96,12,ttf_rus_4);
		    	ssd1306_buffer_write(106,12,ttf_void);

		    	ssd1306_buffer_write(48,20,ttf_rus_10);
		    	ssd1306_buffer_write(56,20,ttf_rus_11);
		    	ssd1306_buffer_write(64,20,ttf_rus_1);
		    	ssd1306_buffer_write(72,20,ttf_rus_12);
		    	ssd1306_buffer_write(80,20,ttf_rus_12);
		    	ssd1306_buffer_write(106,20,ttf_void);

		    	
	switch(params_value.current_menu_pos)
	{
		case 0:
			ssd1306_buffer_write(114,4,ttf_line_left);
		break;
		case 1:
			ssd1306_buffer_write(114,12,ttf_line_left);	
		break;
		case 2:
			ssd1306_buffer_write(114,20,ttf_line_left);	
		break;
	}
	ssd1306_send_buffer();
	
}

void menu_set_item_menu(uint8_t item)
{
	switch(item)
	{
		case red:
			menu_border_item(color);

			ssd1306_buffer_write(15+color*8,4,ttf_rus_13);
			ssd1306_buffer_write(15+color*8+8,4,ttf_rus_14);
			ssd1306_buffer_write(15+color*8+16,4,ttf_rus_5);
			ssd1306_buffer_write(15+color*8+24,4,ttf_rus_6);
			ssd1306_buffer_write(15+color*8+32,4,ttf_rus_9);
			ssd1306_buffer_write(15+color*8+40,4,ttf_rus_15);
			ssd1306_buffer_write(15+color*8+48,4,ttf_rus_16);

			menu_set_params_value(params_value.current_red);
		break;
		case green:
			menu_border_item(color);
			
			ssd1306_buffer_write(15+color*8,4,ttf_rus_17);
			ssd1306_buffer_write(15+color*8+8,4,ttf_rus_3);
			ssd1306_buffer_write(15+color*8+16,4,ttf_rus_18);
			ssd1306_buffer_write(15+color*8+24,4,ttf_rus_3);
			ssd1306_buffer_write(15+color*8+32,4,ttf_rus_9);
			ssd1306_buffer_write(15+color*8+40,4,ttf_rus_15);
			ssd1306_buffer_write(15+color*8+48,4,ttf_rus_16);

		break;
		case blue:
			menu_border_item(color);
			
			ssd1306_buffer_write(15+color*8,4,ttf_rus_6);
			ssd1306_buffer_write(15+color*8+8,4,ttf_rus_12);
			ssd1306_buffer_write(15+color*8+16,4,ttf_rus_9);
			ssd1306_buffer_write(15+color*8+24,4,ttf_rus_12);
			ssd1306_buffer_write(15+color*8+32,4,ttf_rus_16);

		break;
		case first:
			menu_border_item(segment);
			
			// ssd1306_buffer_write(15+segment*8,4,ttf_eng_f);
			// ssd1306_buffer_write(15+segment*8+8,4,ttf_eng_i);
			// ssd1306_buffer_write(15+segment*8+16,4,ttf_eng_r);
			// ssd1306_buffer_write(15+segment*8+24,4,ttf_eng_s);
			// ssd1306_buffer_write(15+segment*8+32,4,ttf_eng_t);

			menu_set_params_value(params_value.current_first);
		break;
		case second:
			menu_border_item(segment);
			
			// ssd1306_buffer_write(15+segment*8,4,ttf_eng_s);
			// ssd1306_buffer_write(15+segment*8+8,4,ttf_eng_e);
			// ssd1306_buffer_write(15+segment*8+16,4,ttf_eng_c);
			// ssd1306_buffer_write(15+segment*8+24,4,ttf_eng_o);
			// ssd1306_buffer_write(15+segment*8+32,4,ttf_eng_n);
			// ssd1306_buffer_write(15+segment*8+40,4,ttf_eng_d);

			menu_set_params_value(params_value.current_second);
		break;
		case sens:
			menu_border_item(settings);
			
			// ssd1306_buffer_write(15+settings*8,4,ttf_eng_s);
			// ssd1306_buffer_write(15+settings*8+8,4,ttf_eng_e);
			// ssd1306_buffer_write(15+settings*8+16,4,ttf_eng_n);
			// ssd1306_buffer_write(15+settings*8+24,4,ttf_eng_s);

			menu_set_params_value(params_value.current_sens);
		break;
		case vers:
			menu_border_item(settings);
			
			// ssd1306_buffer_write(15+settings*8,4,ttf_eng_v);
			// ssd1306_buffer_write(15+settings*8+8,4,ttf_eng_e);
			// ssd1306_buffer_write(15+settings*8+16,4,ttf_eng_r);
			// ssd1306_buffer_write(15+settings*8+24,4,ttf_eng_s);

			menu_set_params_value(params_value.current_vers);
		break;
	}
	
}


void menu_set_paragraph(uint8_t paragraph)
{
	ssd1306_buffer_clean();
	menu_border();
	switch(paragraph)
	{
		case menu:
			
			menu_border_paragraph(4);

			ssd1306_buffer_write(10,12,ttf_rus_8);
	    	ssd1306_buffer_write(18,12,ttf_rus_3);
	    	ssd1306_buffer_write(26,12,ttf_rus_9);
	    	ssd1306_buffer_write(34,12,ttf_rus_20);

	    	ssd1306_buffer_write(48,4,ttf_rus_1);
	    	ssd1306_buffer_write(56,4,ttf_rus_2);
	    	ssd1306_buffer_write(64,4,ttf_rus_3);
	    	ssd1306_buffer_write(72,4,ttf_rus_4);
	    	ssd1306_buffer_write(114,4,ttf_line_left);

	    	ssd1306_buffer_write(48,12,ttf_rus_6);
	    	ssd1306_buffer_write(56,12,ttf_rus_3);
	    	ssd1306_buffer_write(64,12,ttf_rus_7);
	    	ssd1306_buffer_write(72,12,ttf_rus_8);
	    	ssd1306_buffer_write(80,12,ttf_rus_3);
	    	ssd1306_buffer_write(88,12,ttf_rus_9);
	    	ssd1306_buffer_write(96,12,ttf_rus_4);
	    	ssd1306_buffer_write(106,12,ttf_void);

	    	ssd1306_buffer_write(48,20,ttf_rus_10);
	    	ssd1306_buffer_write(56,20,ttf_rus_11);
	    	ssd1306_buffer_write(64,20,ttf_rus_1);
	    	ssd1306_buffer_write(72,20,ttf_rus_12);
	    	ssd1306_buffer_write(80,20,ttf_rus_12);
	    	ssd1306_buffer_write(106,20,ttf_void);
	    	params_value.current_state = 0;
	    	ssd1306_send_buffer();
		break;
		case color:
			menu_border_paragraph(color);
			ssd1306_buffer_write(10,12,ttf_rus_1);
	    	ssd1306_buffer_write(18,12,ttf_rus_2);
	    	ssd1306_buffer_write(26,12,ttf_rus_3);
	    	ssd1306_buffer_write(34,12,ttf_rus_4);

	    	params_value.current_state = red;
	    	menu_set_item_menu(red);
	    	menu_set_params_value(params_value.current_red);
			value_handler(&params_value.current_red);

			params_value.current_state = green;
	    	menu_set_item_menu(green);
	    	menu_set_params_value(params_value.current_green);
			value_handler(&params_value.current_green);

			params_value.current_state = blue;
	    	menu_set_item_menu(blue);
	    	menu_set_params_value(params_value.current_blue);
			value_handler(&params_value.current_blue);
	    	
	    	menu_set_paragraph(menu);
		break;
		case segment:
			menu_border_paragraph(segment);
			ssd1306_buffer_write(10,12,ttf_rus_6);
	    	ssd1306_buffer_write(18,12,ttf_rus_3);
	    	ssd1306_buffer_write(26,12,ttf_rus_7);
	    	ssd1306_buffer_write(34,12,ttf_rus_8);
	    	ssd1306_buffer_write(42,12,ttf_rus_3);
	    	ssd1306_buffer_write(50,12,ttf_rus_9);
	    	ssd1306_buffer_write(58,12,ttf_rus_4);

	    	//params_value.current_paragraph = segment;
	    	//params_value.current_item = first;

		break;
		case settings:
			menu_border_paragraph(settings);
	    	ssd1306_buffer_write(10,12,ttf_rus_10);
	    	ssd1306_buffer_write(18,12,ttf_rus_11);
	    	ssd1306_buffer_write(26,12,ttf_rus_1);
	    	ssd1306_buffer_write(34,12,ttf_rus_12);
	    	ssd1306_buffer_write(42,12,ttf_rus_12);

	    	//params_value.current_paragraph = settings;
	    	//params_value.current_item = sens;
		break;
	}
}