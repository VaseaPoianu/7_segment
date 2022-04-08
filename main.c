/*
 * 7_segment.c
 *
 * Created: 4/4/2022 11:51:54 AM
 * Author : Vostro
 */ 


#define F_CPU 16000000UL
#define delay 100
#define mini_delay 50


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


static short cnt=0;
static short cnt1=0;
static short cnt2=0;

volatile uint8_t count_flag = 0;

//Digit Map
#define DA 0
#define DB 1
#define DC 2
#define DD 3
#define DE 4
#define DF 5
#define DG 6
#define DP point

//Digit Position
#define D1 4
#define D2 5
#define D3 6
#define D4 7

char digit[10]={
	((1<<DA) | (1<<DB) | (1<<DC) | (1<<DD) | (1<<DE) | (1<<DF)),			//0
	((1<<DB) | (1<<DC)),													//1
	((1<<DA) | (1<<DB) | (1<<DD) | (1<<DE) | (1<<DG)),						//2
	((1<<DA) | (1<<DB) | (1<<DC) | (1<<DD) | (1<<DG)),						//3
	((1<<DB) | (1<<DC) | (1<<DF) | (1<<DG)),								//4
	((1<<DA) | (1<<DC) | (1<<DD) | (1<<DF) | (1<<DG)),						//5
	((1<<DA) | (1<<DC) | (1<<DD) | (1<<DE) | (1<<DF) | (1<<DG)),			//6
	((1<<DA) | (1<<DB) | (1<<DC)),											//7
	((1<<DA) | (1<<DB) | (1<<DC) | (1<<DD) | (1<<DE) | (1<<DF) | (1<<DG)),	//8
	((1<<DA) | (1<<DB) | (1<<DC) | (1<<DD) | (1<<DF) | (1<<DG)),			//9
};


ISR(INT0_vect){
	count_flag = ~count_flag;
}

ISR(INT1_vect){
	cnt = 0;
	count_flag = 0;
	PORTD =( 1<< D4); // DIG 4
	PORTC = ~digit[0];
	_delay_ms(mini_delay);
}

void counting(void){
	if (cnt<=9)
	{
		PORTD =( 1<<D4); // DIG 4
		PORTC = ~digit[cnt%10];
		_delay_ms(mini_delay);
	}
	
	else if ((cnt>9) && (cnt<99))
	{
		PORTD =( 1<<D4); // DIG 4
		PORTC = ~digit[cnt%10];
		_delay_ms(mini_delay);
		
		PORTD =( 1<<D3); // DIG 3
		PORTC = ~digit[cnt/10];	
		_delay_ms(mini_delay);
	}
			
	else if ((cnt>99) && (cnt<999))
	{
		PORTD =( 1<<D4); // DIG 4
		PORTC = ~digit[cnt%10];
		_delay_ms(mini_delay);
				
		cnt1 = cnt/10;
			
		PORTD =( 1<<D3); // DIG 3
		PORTC = ~digit[cnt1%10];
		_delay_ms(mini_delay);
			
		PORTD = (1<<D2); // DIG 2
		PORTC = ~digit[cnt1/10];
		_delay_ms(mini_delay);
	}
			
	else if (cnt>999)
	{
		PORTD = (1<<D4); // DIG 4
		PORTC = ~digit[cnt%10];
		_delay_ms(mini_delay);
				
		cnt1 = cnt/10;
		
		PORTD = (1<<D3); // DIG 3
		PORTC = ~digit[cnt1%10];
		_delay_ms(mini_delay);
				
		cnt2 = cnt1/10;
		
		PORTD = (1<<D2); // DIG 2
		PORTC = ~digit[cnt2%10];
		_delay_ms(mini_delay);
		
		PORTD = (1<<D1); // DIG 1
		PORTC = ~digit[cnt2/10];
		_delay_ms(mini_delay);
	}

}


int main(void){
	DDRA = (1<<5);
	DDRC = 0xFF;
	DDRD = 0xF0;
	
	
	MCUCR = 0x0F;
	GICR = 0xC0;
	sei();
	
// 	PORTD =( 1<< D4); // DIG 4
// 	PORTC = ~digit[0];	// Print 0
	
	while (1){

		/*Afisarea ciclica*/
		

	counting();
	if(count_flag) {
		cnt++;

		if (cnt>9999) cnt=0;
	}
	_delay_ms(5);
	


// 		if (cnt == 0) break;
	
		

		 
// 		if (cnt >= 10) cnt=0;
//  		PORTD = 0xFF;
//  		_delay_ms(delay);


 		/*Afisarea dinamica 1 -> 9999*/
 
// 		static char cnt_unit=0;
// 		static char cnt_decimal=1;
// 		static char cnt_hundred=1;
// 		static char cnt_thousand=1;
//		uint8_t i = 0;
// 
// 		if ((i >= 0) && (i < 10)){
// 			PORTD = 0x08;
// 			PORTC = ~digit[cnt_unit++];
// 			if (cnt_unit >= 10) cnt_unit=0;
// 			_delay_ms(delay);
// 			i++;
//  		}
// 		 
// 		else if ((i >= 10) && (i < 100)){
// 			PORTD = 0x04;
// 			PORTC = ~digit[cnt_decimal];
// 			_delay_ms(delay);
// 			
// 			PORTD = 0x08;
// 			PORTC = ~digit[cnt_unit++];
// 			if (cnt_unit >= 10){
// 				cnt_unit=0;
// 				cnt_decimal++;
// 			}
// 			if (cnt_decimal >= 10) cnt_decimal=0;
// 			_delay_ms(delay);
// 			i++;	
// 		}
// 		
// 		else if ((i >= 100) && (i<1000)) {
// 			PORTD = 0x02;
// 			PORTC = ~digit[cnt_hundred];
// 			_delay_ms(delay);
// 			
// 			PORTD = 0x04;
// 			PORTC = ~digit[cnt_decimal];
// 			if (cnt_decimal >= 10){
// 				cnt_decimal=0;
// 				cnt_hundred++;
// 			}
// 			_delay_ms(delay);
// 			
// 			PORTD = 0x08;
// 			PORTC = ~digit[cnt_unit++];
// 			if (cnt_unit >= 10){
// 				cnt_unit=0;
// 				cnt_decimal++;
// 			}
// 			_delay_ms(delay);
// 			if (cnt_hundred >= 10) cnt_hundred=0;				
// 		}
// 		
// 		else if (i >= 1000){
// 			PORTD = 0x01;
// 			PORTC = ~digit[cnt_thousand];
// 			_delay_ms(delay);
// 						
// 			PORTD = 0x02;
// 			PORTC = ~digit[cnt_hundred];
// 			if (cnt_hundred >= 10){
// 				cnt_hundred = 0;
// 				cnt_thousand++;
// 			}
// 			_delay_ms(delay);
// 			
// 			PORTD = 0x04;
// 			PORTC = ~digit[cnt_decimal];
// 			if (cnt_decimal >= 10){
// 				cnt_decimal=0;
// 				cnt_hundred++;
// 			}
// 			_delay_ms(delay);
// 			
// 			PORTD = 0x08;
// 			PORTC = ~digit[cnt_unit++];
// 			if (cnt_unit >= 10){
// 				cnt_unit=0;
// 				cnt_decimal++;
// 			}
// 			_delay_ms(delay);
// 			
// 			if (cnt_thousand >= 10){
// 				cnt_unit = 0;
// 				cnt_decimal = 0;
// 				cnt_hundred = 0;
// 				cnt_thousand = 0;
// 			}
// 			i++;
// 		}			
		
		/*Afisarea dinamica 1234*/
		
// 		PORTD |= (1<<PD0);
// 		PORTC = ~digit[1];
// 		_delay_ms(delay);
// 		PORTD &= ~(1<<PD0);
// 		
// 		PORTD |= (1<<PD1);
// 		PORTC = ~digit[2];
// 		_delay_ms(delay);
// 		PORTD &= ~(1<<PD1);
// 		
// 		PORTD |= (1<<PD2);
// 		PORTC = ~digit[3];
// 		_delay_ms(delay);
// 		PORTD &= ~(1<<PD2);
// 		
// 		PORTD |= (1<<PD3);
// 		PORTC = ~digit[4];
// 		_delay_ms(delay);
// 		PORTD &= ~(1<<PD3);

		
 		/*Afisare statica 7258*/
		 
// 		//Aprinde 7 x x x
// 		PORTD |= (1<<PC0);
// 		PORTC = ~digit[7];
// 		_delay_ms(delay);
// 		PORTD &= ~(1<<PC0);
// 		_delay_ms(delay);
// 		
// 		//Aprinde x 2 x x
//  	PORTD |= (1<<PC1);
// 		PORTC = ~digit[2];
//  	_delay_ms(delay);
// 		PORTD &= ~(1<<PC1);
// 		_delay_ms(delay);
//  		
// 		//Aprinde x x 5 x
// 	 	PORTD |= (1<<PC2);
// 	 	PORTC = ~digit[5];
// 		_delay_ms(delay);
// 		PORTD &= ~(1<<PC2);
// 		_delay_ms(delay);
// 		
// 		//Aprinde x x x 8
// 		PORTD |= (1<<PC3);
// 		PORTC = ~digit[8];
// 		_delay_ms(delay);
// 		PORTD &= ~(1<<PC3);
// 		_delay_ms(delay);
	}
}