/*
*
* Team ID			:		3149
* Author List		:		Samiksha Patil, Kanhaiya Gawade, Trisha Mehar, Ashish Shevale
* File Name			:		Predef.h
* Theme				:		Construct - O - Bot
* Functions			:		void pin_init( void ), void forward( void ), void back( void ), void right( void ), void left(void ),
*							void stop( void ), void f_soft_right( void ), void f_soft_left( void ), void b_soft_right( void ),
*							void b_soft_left( void ), void velocity( int left_motor , int right_motor ), void send_cmd( int command ),
*							void lcd_init( void ), void print_char( int alphabet ), void print_string( char *string ), void lcd_clear( void ),
*							void cursor_xy( int line, int position ),void print_number( int line, unsigned char number1, unsigned char numbr2, unsigned char number3 ),
*							void mid_sensor( void ), void left_sensor( void ), void right_sensor( void ), void sharp_left( void ),
*							void sharp_right( void ),void sensor_cali( void ), void black_line_forward( void ),void forward_node( int node ),
*							void line_follow_distance_forward( unsigned long int distance),void f_right_turn_90( void ),
*							void f_left_turn_90( void ), void b_right_turn_90( void ), void b_left_turn_90( void ), void right_turn_90( void ),
*							void left_turn_90( void ), void right_turn_180( void ), void line_follow_till_wall( void ), void wall_forward( void ),
*							void zig_zag( void ), void white_line_distance(unsigned long int distance ), void white_node( int mode, int house_type, in direction ),
*							void pick( void ), void place( int house_type, int direction ), void buzzer_blink( void ), void buzzer_5( void )
* Global Variables  :		unsigned long int i
*
*/

#define F_CPU 14745600

#include <avr/io.h>
#include <util/delay.h>

// pin initializations

#define M1_CH_A 6 // motor 1 encoder pin A to D6

#define M2_CH_A 6 // motor 2 encoder pin A is connected to E6

#define M1_EN 5 // 7 // motor 1 PWM pin is connected to B7
#define M2_EN 6 // motor 2 PWM pin is connected to B4
#define M1_A1 0 // motor 1 direction control pin 1 is connected to A0
#define M1_A2 1 // motor 1 direction control pin 2 is connected to A1
#define M2_B1 2 // motor 2 direction control pin 1 is connected to A2
#define M2_B2 3 // motor 2 direction control pin 2 is connected to A3

#define PWM_RIGHT 1017 //65535,65360
#define PWM_LEFT  970 // FOR THE BOT TO MOVE IN A STRAIGHT LINE, THE DIFFERENCE IN RIGHT AND LEFT VELOCITIES SHOULD BE 50. ( VALUES :: RIGHT : FFAF, LEFT : FFFF )

#define THRES  20
#define THRES_WHITE 170

#define MAX_WALL_DIST_LEFT 130
#define MAX_WALL_DIST_RIGHT 120
#define WALL_PRESENT 70

#define BUZZER 0 // buzzer is connected to G0

#define lcd_4  4 // D4 of LCD is connected to C4
#define lcd_5  5 // D5 of LCD is connected to C5
#define lcd_6  6 // D6 of LCD is connected to C6
#define lcd_7  7 // D7 of LCD is connected to C7
#define lcd_EN 2 // EN of LCD is connected to C2
#define lcd_RW 1 // RW of LCD is connected to C1
#define lcd_RS 0 // RS of LCD is connected to C0

#define SERVO_1 3 // SERVO 1 IS ARM
#define SERVO_2 5 // SERVO 2 IS GRIPPER

#define sharp1 6 // LEFT  SHARP SENSOR IS CONNECTED TO K0
#define sharp2 7 // RIGHT SHARP SENSOR IS CONNECTED TO K1


unsigned long int i = 0;
void servo_rotate( int servo_number, int new_angle );
/*
* Function Name :: void pin_init( void )
* Input  :: void
* Output :: void
* Logic  :: initializes all input and output ports, timers and adc converter of microcontroller
* Example Call  :: pin_init();
*/
void pin_init( void )
{
	// MOTOR DRIVER DIRECTION CONTROL PIN INITIALIZE

	DDRA = DDRA | (1 << M1_A1)| (1 << M1_A2); // MAKE DIRECTION CONTROL PINS OF MOTOR1 OF DRIVER AS OUTPUT
	DDRA = DDRA | (1 << M2_B1)| (1 << M2_B2); // MAKE DIRECTION CONTROL PINS OF MOTOR2 OF DRIVER AS OUTPUT

	// MOTOR DRIVER PWM CONTROL PIN INITIALIZE

	DDRB = DDRB | (1 << M1_EN) | (1<< M2_EN);// MAKE PWM PINS OF MOTOR DRIVER AS OUTPUT
	
	// BUZZER TRIGGER PIN
	
	DDRG = DDRG | ( 1 << BUZZER );
	PORTG = PORTG | ( 1 << BUZZER );
	
	// SETUP TIMER FOR PWM CONTROL OF MOTORS
	
	TCCR1A = TCCR1A | ( 1 << WGM11 ) | ( 1 << WGM10 ); // WGM13 : 10 = 0011 FOR 10 BIT PHASE CORRECT PWM
	TCCR1A = TCCR1A | ( 1 << COM1A1 )|( 1 << COM1B1 ); // COM1A1 : A0 = 10 , COM1B1 : B0 = 10 FOR NON INVERTING MODE
	TCCR1B = TCCR1B | ( 1 << CS11 ) | ( 1 << CS10 ); // CLK / 8 PRESCALER
	OCR1A = PWM_LEFT; // SET VELOCITY OF LEFT WHEEL
	OCR1B = PWM_RIGHT; // SET VELOCITY OF RIGHT WHEEL
	
	// ADC CONVERTER FOR SENSORS INITIALIZE
	
	DDRF = DDRF & ~( 1 << PF0 ) & ~( 1 << PF1 ) & ~( 1 << PF2 ); // MAKE LINE SENSOR PINS AS INPUT
	DDRK = DDRK & ~( 1 << sharp1 ) & ~( 1 << sharp2 ); // MAKE SHARP SENSOR PINS AS INPUT
	
	PORTF = 0x00;
	PORTK = 0x00;
	
	ADMUX = ADMUX | ( 1 << REFS0 ); // SELECT 5 VOLT VCC AS REFERENCE VOLTAGE
	
	ADCSRA = ADCSRA | ( 1 << ADEN ); // ENABLE THE ADC CONVERTER
	ADCSRA = ADCSRA | ( 1 << ADPS2 ) | ( 1 << ADPS1 ) | ( 1 << ADPS0 ); // SELECT ADC PRESCALE FACTOR OF 128
	
	DIDR0 = 0x00; // DISABLE ALL DIGITAL INPUTS TO THIS PORT
	
	ADMUX = 0x00; // START THE CONVERSION OF SOME DUMMY SENSOR. THIS VALUE WILL BE DISCARDED ANYWAYS AS THE FIRST READING IS BOUND TO HAVE SOME ERRORS
	
	ADCSRA = ADCSRA | ( 1 << ADSC ); // START THE CONVERSION
	
	while( ADCSRA & ( 1 << ADSC ) ); // WAIT FOR THE CONVERSION TO COMPLETE
	
	// SERVO MOTOR INITIALIZE
	
	DDRH = DDRH | ( 1 << SERVO_1 ) | ( 1 << PH5 );
	
	OCR4A = 470; // SET STARTING POSITION OF SERVO 1
	OCR4C = 300; // SET STARTING POSITION OF SERVO 2
	
	TCNT4 = 0; // INITIALIZE TIMER VALUE TO 0
	
	ICR4 = 2499; // SET THE OUTPUT FREQUENCY TO 50 HZ
	
	TCCR4A = ( 1 << WGM41 ) | ( 1 << COM4A1 ) | ( 1 << COM1C1 );
	TCCR4B = ( 1 << WGM42 ) | ( 1 << WGM43 ) | ( 1 << CS40 ) | ( 1 << CS41 ); // TIMER IN FAST PWM, NON INVERTED MODE
	
	

	
}

void delay_ms( uint16_t time )
{	
	OCR5A = ( int ) ( time * 14 ); // SET THE OUTPUT COMPARE VALUE
	TCCR5B = TCCR5B | ( 1 << CS50 ) | ( 1 << CS52 ) | ( 1 << WGM52 ); // TIMER5 IN CTC MODE WITH CLOCK PRESCALED BY 1024
	while( ( TIFR5 & ( 1 << OCF1A ) ) == 0 ); // WAIT FOR THE TIMER TO OVERFLOW
	TIFR5 = TIFR5 | ( 1 << OCF1A ); // CLEAR THE OUTPUT COMPARE FLAG
}

/*
* Function Name :: inline void forward( void )
* Input  :: void
* Output :: void
* Logic  :: make both the motors run in forward direction using direction control pins
* Example Call  :: forward();
*/
inline void forward( void )
{
	
	PORTA = PORTA | ( (1 << M1_A1) & ~(1 << M1_A2) ); // M1_A1 PIN IS HIGH AND M1_A2 PIN IS LOW
	PORTA = PORTA | ( (1 << M2_B1) & ~(1 << M2_B2) ); // M2_B1 PIN IS HIGH AND M2_B2 PIN IS LOW
}

/*
* Function Name :: inlline void back( void )
* Input  :: void
* Output :: void
* Logic  :: make both motors rn in backward direction using the direction control pins
* Example Call  :: back();
*/
inline void back( void )
{
	PORTA = PORTA | ( (1 << M1_A2) & ~(1 << M1_A1) ); // M1_A1 PIN IS LOW AND M1_A2 PIN IS HIGH
	PORTA = PORTA | ( (1 << M2_B2) & ~(1 << M2_B1) ); // M2_B1 PIN IS LOW AND M2_B2 PIN IS HIGH
	
}

/*
* Function Name :: inline void right( void )
* Input  :: void
* Output :: void 
* Logic  :: make left motor turn forward and right motor turn back 
* Example Call  :: right();
*/
inline void right( void )
{
	PORTA = PORTA | ( (1 << M1_A1) & ~(1 << M1_A2) ); // M1_A1 PIN IS HIGH AND M1_A2 PIN IS LOW
	PORTA = PORTA | ( (1 << M2_B2) & ~(1 << M2_B1) ); // M2_B1 PIN IS LOW AND M2_B2 PIN IS HIGH
}

/*
* Function Name :: inline void left( void )
* Input  :: void
* Output :: void
* Logic  :: make right motor turn forward an left motor turn back
* Example Call  :: left();
*/
inline void left( void )
{
	PORTA = PORTA | ( (1 << M1_A2) & ~(1 << M1_A1) ); // M1_A1 PIN IS LOW AND M1_A2 PIN IS HIGH
	PORTA = PORTA | ( (1 << M2_B1) & ~(1 << M2_B2) ); // M2_B1 PIN IS HIGH AND M2_B2 PIN IS LOW
	
}

/*
* Function Name :: inline void stop( void )
* Input  :: void
* Output :: void
* Logic  :: stop rotating both the motors
* Example Call  :: stop();
*/
inline void stop( void )
{
	PORTA = PORTA & ~(1 << M2_B1) & ~(1 << M2_B2); // M2_A1 PIN IS LOW AND M2_A2 PIN IS LOW
	PORTA = PORTA & ~(1 << M1_A1) & ~(1 << M1_A2); // M1_B1 PIN IS LOW AND M1_B2 PIN IS LOW
	
	
}

/*
* Function Name :: inline void f_soft_right( void )
* Input  :: void
* Output :: void
* Logic  :: rotate left wheel forward and right wheel stationary
* Example Call  :: f_soft_right()
*/
inline void f_soft_right( void )
{
	PORTA = PORTA | ( (1 << M1_A1) & ~(1 << M1_A2) ); // M1_A1 PIN IS HIGH AND M1_A2 PIN IS LOW
	PORTA = PORTA & ( ~(1 << M2_B1) & ~(1 << M2_B2) ); // M2_B1 PIN IS LOW AND M2_B2 PIN IS LOW
}

/*
* Function Name :: inline void f_soft_left( void )
* Input  :: void
* Output :: void
* Logic  :: rotate right wheel forward and left wheel stationary
* Example Call  :: f_soft_left()
*/
inline void f_soft_left( void )
{
	PORTA = PORTA & ( ~(1 << M1_A2) & ~(1 << M1_A1) ); // M1_A1 PIN IS LOW AND M1_A2 PIN IS LOW
	PORTA = PORTA | ( (1 << M2_B1) & ~(1 << M2_B2) ); // M2_B1 PIN IS HIGH AND M2_B2 PIN IS LOW
}

/*
* Function Name :: inline void b_soft_right( void )
* Input  :: void
* Output :: void
* Logic  :: rotate right wheel back and left wheel stationary
* Example Call  :: b_soft_right()
*/
inline void b_soft_right( void )
{
	PORTA = PORTA & ( ~(1 << M1_A2) & ~(1 << M1_A1) ); // M1_A1 PIN IS LOW AND M1_A2 PIN IS LOW
	PORTA = PORTA | ( ~(1 << M2_B1) & (1 << M2_B2) ); // M2_B1 PIN IS LOW AND M2_B2 PIN IS HIGH
}

/*
* Function Name :: inline void b_soft_left( void )
* Input  :: void
* Output :: void
* Logic  :: rotate left wheel back and right wheel stationary
* Example Call  :: b_soft_left()
*/
inline void b_soft_left( void )
{
	PORTA = PORTA | ( ~(1 << M1_A1) & (1 << M1_A2) ); // M2_A1 PIN IS LOW AND M2_A2 PIN IS HIGH
	PORTA = PORTA & ( ~(1 << M2_B2) & ~(1 << M2_B1) ); // M1_B1 PIN IS LOW AND M1_B2 PIN IS LOW
}

/*
* Function Name :: inline void velocity( int left_motor, int right_motor )
* Input  :: left_motor -> velocity of left motor ( between 0 and 1024 )
*			right_motor -> velocity of right motor ( between 0 and 1024 )
* Output :: void
* Logic  :: make left and right wheels rotate with the given velocity
* Example Call  :: velocity( 650, 650 );
*/
inline void velocity( int left_motor, int right_motor )
{
	OCR1A = left_motor; // SET DUTY CYCLE OF LEFT WHEEL USING CTC MODE
	OCR1B = right_motor; // SET DUTY CYCLE OF RIGHT WHEEL USING CTC MODE
}


// LCD DISPLAY FUNCTIONS

/*
* Function Name ::  void send_cmd( int CMD )
* Input  :: CMD -> command to be sent to the lcd
* Output :: void
* Logic  :: writes the given command on the data pins of lcd using 4 bit mode
* Example Call  :: lcd_cmd( 0x32 );
*/
void send_cmd(int CMD)
{
	PORTC = (PORTC & 0x0F) | ( CMD & 0xF0); // SEND THE HIGHER 4 BITS OF THE COMMAND TO THE 4 DATA PINS OF LCD
	
	PORTC = PORTC & ~( 1 << lcd_RS); // SELECT COMMAND MODE THROUGH THE REGISTER SELECT PIN OF THE LCD
	PORTC = PORTC & ~( 1 << lcd_RW); // ENABLE WRITE OPERATIONS ON LCD
	
	PORTC = PORTC | ( 1 << lcd_EN); // SEND A HIGH SIGNAL TO LCD
	_delay_us(1);					// WAIT FOR AT LEAST ONE CLOCK CYCLE
	PORTC = PORTC & ~( 1 << lcd_EN);// SEND A LOW PULSE TO LCD
	_delay_us(20);					// THIS HIGH TO LOW PULSE WILL CAUSE THE DATA TO BE LOADED
	
	PORTC = ( PORTC & 0x0F ) | (CMD << 4); // SEND THE HIGHER 4 BITS OF THE COMMAND TO THE 4 DATA PINS OF LCD
	
	PORTC = PORTC | ( 1 << lcd_EN); // SEND A HIGH SIGNAL TO LCD
	_delay_us(1);					// WAIT FOR AT LEAST ONE CLOCK CYCLE
	PORTC = PORTC & ~( 1 << lcd_EN);// SEND A LOW PULSE TO LCD
	_delay_us(20);					// THIS HIGH TO LOW PULSE WILL CAUSE THE DATA TO BE LOADED
	
}

/*
* Function Name ::  void lcd_init( void )
* Input  :: void
* Output :: void
* Logic  :: initializes the lcd in 4 bit 2 line mode
* Example Call  :: lcd_init();
*/
void lcd_init( void )
{
	DDRC = 0xFF; // INITIALIZE ALL PINS OF GHE LCD AS OUTPUT PNS
	PORTC &= ~( 1 << lcd_EN ); // MAKE THE ENABLE PIN OF THE LCD LOW
	_delay_us(200); // WAIT FOR THE VOLTAGE TO DROP
	
	send_cmd(0x33); //
	_delay_us(100);
	
	send_cmd(0x32); //
	_delay_us(100);
	
	send_cmd(0x28); // 4 BIT MODE WITH 2 LINES
	_delay_us(100);
	
	send_cmd(0x0E); // DISPLAY ON CURSOR BLINK
	_delay_us(100);
	
	send_cmd(0x01); // CLEAR DISPLAY
	_delay_us(2000);
	
	send_cmd(0x06); // INCREMENT CURSOR
	_delay_us(100);
	
}

/*
* Function Name ::  void print_char( int alphabet )
* Input  :: alphabet -> character to be printed
* Output :: void
* Logic  :: writes the alphabet on the data pins of the lcd
* Example Call  :: print_char( a );
*/
void print_char( int alphabet)
{
	PORTC =  ( PORTC & 0x0F ) | ( alphabet & 0xF0 ); // MOVE THE HIGHER 4 BITS OF THE DATA TO THE DATA PINS OF LCD
	
	PORTC = PORTC | ( 1 << lcd_RS ); // SELECT DATA MODE THROUGH THE REGISTER SELECT PIN OF LCD
	PORTC = PORTC & ( ~( 1 << lcd_RW ) ); // ENABLE WRITE OPERATIONS ON THE LCD
	
	PORTC = PORTC | ( 1 << lcd_EN); // SEND A HIGH SIGNAL TO LCD
	_delay_us(1);					// WAIT FOR AT LEAST ONE CLOCK CYCLE
	PORTC = PORTC & ~( 1 << lcd_EN);// SEND A LOW PULSE TO LCD
	_delay_us(20);					// THIS HIGH TO LOW PULSE WILL CAUSE THE DATA TO BE LOADED
	
	PORTC = ( PORTC & 0x0F ) | ( alphabet << 4 ); // MOVE THE LOWER 4 BITS OF THE DATA TO THE DATA PINS OF THE LCD
	
	PORTC = PORTC | ( 1 << lcd_EN); // SEND A HIGH SIGNAL TO LCD
	_delay_us(1);					// WAIT FOR AT LEAST ONE CLOCK CYCLE
	PORTC = PORTC & ~( 1 << lcd_EN);// SEND A LOW PULSE TO LCD
	_delay_us(20);					// THIS HIGH TO LOW PULSE WILL CAUSE THE DATA TO BE LOADED
	
}

/*
* Function Name ::  void print_string( char *string )
* Input  :: *string -> address of the string to be printed on lcd
* Output :: void
* Logic  :: sequentially writes all the characters of string on the lcd
* Example Call  :: print_string( "Print This" );
*/
void print_string(char *string)
{
	int i = 0;
	while(string[i] != 0)
	{
		print_char(string[i]); // SEQUENTIALLY PRINT ALL THE ALPHABETS IN THE GIVEN STRING
		_delay_us(100);
		++i;
	}
}

/*
* Function Name ::  void lcd_clear( void )
* Input  :: void
* Output :: void
* Logic  :: sends command for clearing the lcd
* Example Call  :: lcd_clear();
*/
void lcd_clear( void )
{
	send_cmd(0x01);
	_delay_ms(5);
}

/*
* Function Name ::  void cursor_xy( int line, int position )
* Input  :: line -> line number on which to take the cursor to ( 0 or 1 )
*			position -> position fron left to tkae the cursor to
* Output :: void
* Logic  :: takes the cursor to given address using DDRAM
* Example Call  :: cursor_xy( 0, 0 );
*/
void cursor_xy( int line, int position)
{
	send_cmd( ( 0x80 | ( line << 6 ) ) + position ); // CALCULATE AND SET THE DDRAM ADDRESS
	_delay_ms(100);
}

/*
* Function Name ::  void print_number( int line, unsigned int number1, unsigned int number2, unsigned int number3 )
* Input  :: line -> line number on which to print the numbers
*			number1 -> first number to be printed
*			number2 -> second number to be printed
*			number3 -> third number to be printed
* Output :: void
* Logic  :: print the three numbers on the given line
* Example Call  :: print_number( 1, 20, 30, 40 );
*/
void print_number(int line,unsigned int number1, unsigned int number2, unsigned int number3)
{
	int i = 0;
	lcd_clear(); // CLEAR THE DISPLAY
	while(number1) // REPEAT UNTIL THE NUMBER IS NOT EQUAL TO ZERO
	{
		cursor_xy(line, 4 - i);  // TAKE THE CURSOR TO THE NECESSARY POSITION 
		print_char( ( number1 % 10 ) + 48); // PRINT THE ASCII VALUE OF THE LAST DIGIT 
		_delay_us(10); // WAIT FOR THE VALUE TO BE PRINTED
		number1 = number1 / 10;
		++i;
	}
	i = 0;
	while(number2) // REPEAT UNTIL THE NUMBER IS NOT EQUAL TO ZERO
	{
		cursor_xy(line, 9 - i); // TAKE THE VURSOR TO THE REQUIRED POSITION
		print_char( ( number2 % 10 ) + 48); // PRINT THE ASCII VALUE OF THE LAST DIGIT
		_delay_us(10); // WAIT FOR THE VALUE TO BE PRINTED
		number2 = number2 / 10;
		++i;
	}
	i = 0;
	while(number3) // REPEAT UNTIL THE NUMBER IS NOT EQUAL TO ZERO
	{
		cursor_xy(line, 15 - i); // TAKE THE CURSOT TO THE REQUIRED POSITION
		print_char( ( number3 % 10 ) + 48); // PRINT THE ASCII VALUE OF THE LAST DIGIT
		_delay_us(10); // WAIT FOR THE VALUE TO BE PRINTED
		number3 = number3 / 10;
		++i;
	}
	_delay_ms(80);
}

// SENSOR READINGS

/*
* Function Name ::  int mid_sensor ( void )
* Input  :: void
* Output :: reading of middle line sensor
* Logic  :: performs adc conversion for analog reading of middle sensor
* Example Call  :: int mid_sensor_reading = mid_sensor();
*/
int mid_sensor( void )
{
	ADCSRA = ADCSRA & ~( 1 << ADEN ); // DISABLE THE ADC CONVERTER
	ADMUX = 0x21 ;					 // FOR CHANNNEL 1, MUX VAUES SHOULD BE 000
	ADCSRA = ADCSRA | ( 1 << ADEN ); // ENABLE THE ADC CONVERTER
	ADCSRA = ADCSRA | ( 1 << ADSC ); // START CONVERSION
	
	while( ADCSRA & ( 1 << ADSC ) ); // WAIT FOR THE CONVERSION TO COMPLETE
	
	return ADCH;
}

/*
* Function Name ::  int right_sensor( void )
* Input  :: void
* Output :: reading of the right sensor
* Logic  :: performs adc conversion on analog reading of right line sensor
* Example Call  :: int right_sensor_reading = right_sensor();
*/
int right_sensor( void )
{
	ADCSRA = ADCSRA & ~( 1 << ADEN ); // DISABLE THE ADC CONVERTER
	ADMUX = 0x22 ;// FOR CHANNNEL 1, MUX VAUES SHOULD BE 000
	ADCSRA = ADCSRA | ( 1 << ADEN ); // ENABLE THE ADC CONVERTER
	ADCSRA = ADCSRA | ( 1 << ADSC ); // START CONVERSION
	
	while( ADCSRA & ( 1 << ADSC ) ); // WAIT FOR THE CONVERSION TO COMPLETE
	
	return ADCH;
}

/*
* Function Name ::  int left_sensor( void )
* Input  :: void
* Output :: reading of left sensor
* Logic  :: performs adc conversion on analog reading of left sensor
* Example Call  :: int left_sensor_reading = left_sensor();
*/
int left_sensor( void )
{
	ADCSRA = ADCSRA & ~( 1 << ADEN ); // ENABLE THE ADC CONVERTER
	ADMUX = 0x20 ;// FOR CHANNNEL 1, MUX VAUES SHOULD BE 000
	ADCSRA = ADCSRA | ( 1 << ADEN ); // ENABLE THE ADC CONVERTER
	ADCSRA = ADCSRA | ( 1 << ADSC ); // START CONVERSION
	
	while( ADCSRA & ( 1 << ADSC ) ); // WAIT FOR THE CONVERSION TO COMPLETE
	
	return ADCH;
}

/*
* Function Name ::  int sharp_right( void )
* Input  :: void
* Output :: reading of right sharp sensor
* Logic  :: performs analog conversion of reading of right sharp sensor
* Example Call  :: int sharp_right_reading = sharp_right();
*/
int sharp_right( void )
{	
	ADCSRA = ADCSRA & ~( 1 << ADEN ); // ENABLE THE ADC CONVERTER
	ADMUX = 0xE6;
	ADCSRB = ADCSRB | ( 1 << MUX5 ); // MUX VALUES ARE 100000 ( ADC8 )
	ADCSRA = ADCSRA | ( 1 << ADEN ); // ENABLE THE ADC CONVERTER
	ADCSRA = ADCSRA | ( 1 << ADSC ); // START CONVERSION
	
	while( ADCSRA & ( 1 << ADSC ) ); // WAIT FOR THE CONVERSION TO COMPLETE
	
	ADCSRB = ADCSRB & ~( 1 << MUX5 ); // RESET MUX5 AS FUTURE CONVERSIONS MIGHT NOT NEED IT
	ADMUX = 0xE7;
	return ADCH;
}

/*
* Function Name ::  int sharp_left( void )
* Input  :: void
* Output :: reading of left sharp sensor
* Logic  :: performs adc conversion of analog output of left sharp sensor
* Example Call  :: int sharp_left_sensor = sharp_left()
*/
int sharp_left( void )
{
	ADCSRA = ADCSRA & ~( 1 << ADEN ); // DISABLE THE ADC
	ADMUX = 0xE7;
	ADCSRB = ADCSRB | ( 1 << MUX5 ); // MUX VALUES ARE 100001 ( ADC9 )
	ADCSRA = ADCSRA | ( 1 << ADEN ); // ENABLE THE ADC CONVERTER
	ADCSRA = ADCSRA | ( 1 << ADSC ); // START THE CONVERSION
	
	while( ADCSRA & ( 1 << ADSC ) ); // WAIT FOR THE CONVERSION TO COMPLETE
	
	ADCSRB = ADCSRB & ~( 1 << MUX5 ); // RESET MUX5 AS FUTURE CONVERSIONS MIGHT NOT NEED IT	
	ADMUX = 0xE6;
	return ADCH ;
}

/*
* Function Name ::  void sensor_cali( void )
* Input  :: void
* Output :: void
* Logic  :: continously prints all sensor readings on the lcd so that they can be calliberated
* Example Call  :: sensor_cali();
*/
void sensor_cali()
{
	OCR4C = 412;
	lcd_init(); // INITIALIZE THE LCD
	while(1)
	{
		lcd_clear(); // CLEAR THE LCD
		//print_number(0, left_sensor(), mid_sensor(), right_sensor()); // PRINT THE VALUES ALL THREE LINE SENSORS
		print_number(1, sharp_left(), sharp_right(), 0); // PRINT THE VALUES OF BOTH THE SHARP SENSORS
	}
}

// LINE FOLLOWING ALGORITHMS

/*
* Function Name ::  void black_line_follow_forward( void )
* Input  :: void
* Output :: void
* Logic  :: makes the bot follow the black line in forward direction
* Example Call  :: black_line_follow_forward();
*/
void black_line_follow_forward( void )
{
	while(1) // REPEAT THE FOLLOWING INFINITELY
	{
		// IF AT LEAST TWO OR ALL THREE OF THE LINE SENSORS DETECT A BLACK AREA, THEN A NODE HAS BEEN ENCOUNTERED
		if(((left_sensor()>THRES)&&(mid_sensor()>THRES)&&(right_sensor()>THRES)) ||( (left_sensor()<THRES)&&(mid_sensor()>THRES)&&(right_sensor()>THRES))||((left_sensor()>THRES)&&(mid_sensor()>THRES)&&(right_sensor()<THRES))  )
		{
			forward();
			velocity(970,1017); // MOVE THE BOT FORWARD UNTIL THE NODE IS CROSSED
			_delay_ms(60);
			stop();
			break; // BREAK FROM THE INFINITE LOOP
		}
		
		do{
			forward();
			velocity(970,1017);
			
		   }while((left_sensor()<THRES)&&(right_sensor()<THRES)); // MOVE THE BOT FORWARD UNTIL THE RIGHT AND LEFT SENSOR ARE ON WHITE SPACE
		stop();
		
		
		while((left_sensor()>THRES)&&(right_sensor()<THRES)&&(mid_sensor()<THRES)) // IF THE LEFT SENSOR IS ON THE BLACK LINE AND RIGHT AND MIDDLE SENSOR ARE ON THE WHITE AREA, TURN LEFT
		{
			forward();
			velocity(0,1017);
		}
		stop();
		
		
		while((left_sensor()<THRES)&&(right_sensor()>THRES)&&(mid_sensor()<THRES)) // IF THE RIGHT SENSOR IS ON THE BLACK LINE AND THE MIDDLE AND LEFT SENSOR ARE ON WHITE AREA, TURN THE BOT RIGHT
		{
			forward();
			velocity(970,0);
		}
		stop();
		
	}
}

/*
* Function Name ::  void forward_node( int node )
* Input  :: node -> number of nodes the bot must follow
* Output :: void
* Logic  :: calls the black_line_follow_forward() function 'node' number of times
* Example Call  :: forward_node( 5 );
*/
void forward_node(int node)
{
	for( int i = 0 ;i < node ; i++ ) // REPEAT THE FOLLOWING FOR THE GIVEN NUMBER OF NODES
	{
		black_line_follow_forward(); // FOLLOW THE BLACK UPTO ONE NODE
		forward(); // MOVE THE BOT FORWARD UNTIL IT HAS CROSSED THE NODE
		velocity(970,1017);
		_delay_ms(60);
		stop(); // STOP THE BOT
	}
}

/*
* Function Name ::  void line_follow_distance_forward( unsigned long int distance )
* Input  :: distance -> distance upto which the bot must follow the line
* Output :: void
* Logic  :: follows the line upto the given distance
* Example Call  :: line_follow_distance_forward( 5000 );
*/
void line_follow_dist_forward( unsigned long int distance )
{
	forward(); // MOVE THE BOT FORWARD
	for ( i = 0; i < distance ; ++i) // REPEAT THE FOLLOWING UPTO THE GIVEN VALUE
	{
		if( left_sensor() < THRES && mid_sensor() > THRES && right_sensor() < THRES ) // IF THE MIDDLE SENSOR IS ON THE BLACK LIEN AND THE OTHER TWO SENSORS ARE WHITE,
			forward(); // MOVE THE BOT FORWARD
		else if( left_sensor() > THRES && mid_sensor() < THRES && right_sensor() < THRES ) // IF THE LEFT SENSOR IS ON THE BLACK LINE AND THE OTHER TWO SENSORS ARE ON WHITE,
			f_soft_left(); // TURN THE BOT LEFT
		else if( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() > THRES ) // IF THE RIGHT SENSOR IS ON THE BLACK LINE AND THE OTHER TWO SENSORS ARE WHITE 
			f_soft_right(); // TURN THE BOT RIGHT
		else
			forward();
	}
	stop(); // STOP THE BOT
	
}

/*
* Function Name ::  void f_right_turn_90( void )
* Input  :: void
* Output :: void
* Logic  :: turn left wheel forward and right wheel stationary and turn 90 degree
* Example Call  :: f_right_turn_90();
*/
void f_right_turn_90()
{
	f_soft_right();
	_delay_ms(100); // START TURNING THE BOT TO THE RIGHT TILL IT HAS CROSSED THE BLACK LINE IT IS ON
		
	while ( (left_sensor() > THRES) || (mid_sensor() > THRES) || (right_sensor() > THRES) ); // KEEP TURNING THE BOT UNTIL ALL THE SENSORS ARE ON THE WHITE AREA
	while ( (left_sensor() > THRES) || (mid_sensor() < THRES) || (right_sensor() > THRES) ); // KEEP TURNING THE BOT UNTIL THE MIDDLE SENSOR IS ON THE BLACK LINE AND THE OTHER TWO ARE ON WHITE
		
	stop(); // STOP THE BOT
		
	f_soft_right();
	_delay_ms(100);
	stop();
	
}

/*
* Function Name ::  void f_left_turn_90( void )
* Input  :: void
* Output :: void
* Logic  :: turn right wheel forward and left wheel stationary and turn 90 degree
* Example Call  :: f_left_turn_90();
*/
void f_left_turn_90()
{
	f_soft_left();
	_delay_ms(100);
	
	while ( (left_sensor() > THRES) || (mid_sensor() > THRES) || (right_sensor() > THRES) );
	while ( (left_sensor() > THRES) || (mid_sensor() < THRES) || (right_sensor() > THRES) );
	
	stop();
	b_soft_right();
	_delay_ms(100);
	stop();
	line_follow_dist_forward(10);
	
}

/*
* Function Name ::  void b_right_turn_90( void )
* Input  :: void
* Output :: void
* Logic  :: turn right wheel bak and left wheel stationary and turn 90 degree
* Example Call  :: f_right_turn_90();
*/
void b_right_turn_90()
{
	for(i = 0; i < 85000; ++i)
	{
		b_soft_right();
	}
	
	while( left_sensor() > THRES || mid_sensor() > THRES || right_sensor() > THRES );
	while( left_sensor() > THRES || mid_sensor() < THRES || right_sensor() > THRES );
	
	stop();
	left();
	_delay_ms(50);
	stop();
	
}

/*
* Function Name ::  void b_left_turn_90( void )
* Input  :: void
* Output :: void
* Logic  :: turn left wheel back and right wheel stationary and trun 90 degree
* Example Call  :: b_left_turn_90();
*/
void b_left_turn_90()
{
		for(i = 0; i < 85000; ++i)
		{
			b_soft_right();
		}
		
		while( left_sensor() > THRES || mid_sensor() > THRES || right_sensor() > THRES );
		while( left_sensor() > THRES || mid_sensor() < THRES || right_sensor() > THRES );
		
		stop();
		left();
		_delay_ms(50);
		stop();

}

/*
* Function Name ::  void right_turn_90( void )
* Input  :: void
* Output :: void
* Logic  :: turn left wheel forward and right wheel back and turn 90 degree
* Example Call  :: f_right_turn_90();
*/
void right_turn_90()
{
	line_follow_dist_forward(100);
	right(); // START TURNING THE BOT RIGHT SO THE IT CROSSES THE LINE UNDERNEATH IT IF ANY
	_delay_ms(250);
	
	while ( (left_sensor() > THRES) || (mid_sensor() > THRES) || (right_sensor() > THRES) ); // ROTATE THE BOT RIGHT UNTIL ALL THE SENSORS ARE ON WHITE AREA
	_delay_ms(50);
	while ( (left_sensor() > THRES) || (mid_sensor() > THRES) || (right_sensor() < THRES) ); // ROTATE THE BOT RIGHT UNTIL THE RIGHT SENSOR IS ON BLACK LINE
	stop();
	left();
	_delay_ms(60);
	stop();
}

/*
* Function Name ::  void left_turn_90( void )
* Input  :: void
* Output :: void
* Logic  :: turn right wheel forward and left wheel back and turn 90 degree
* Example Call  :: left_turn_90();
*/
void left_turn_90()
{
	line_follow_dist_forward(100);
	left(); // START TURNING THE BOT RIGHT SO THE IT CROSSES THE LINE UNDERNEATH IT IF ANY
	_delay_ms(250);
	
	while ( (left_sensor() > THRES) || (mid_sensor() > THRES) || (right_sensor() > THRES) ); // ROTATE THE BOT RIGHT UNTIL ALL THE SENSORS ARE ON WHITE AREA
	_delay_ms(100);
	while ( (left_sensor() < THRES) || (mid_sensor() > THRES) || (right_sensor() > THRES) ); // ROTATE THE BOT RIGHT UNTIL THE RIGHT SENSOR IS ON BLACK LINE
	stop();
	right();
	_delay_ms(60);
	stop(); // STOP THE BOT	
}

/*
* Function Name ::  void right_turn_180( void )
* Input  :: void
* Output :: void
* Logic  :: turn left wheel forward and right wheel stationary and turn 180 degree
* Example Call  :: right_turn_180();
*/
void right_turn_180()
{
	for (i = 0; i < 70000; ++i)
	{
		back(); // TAKE THE BOT A LITTLE BACK
	}
	stop();
	
	velocity(650, 650);
	
	right();
	_delay_ms(200); // START TURNING THE BOT RIGHT FOR SOME TIME UNTIL IT HAS CROSSED THE BLACK LINE
	
	while( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() < THRES ); // KEEP TURNING UNTIL ALL THE SENSORS ARE ON WHITE AREA
	while( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() > THRES ); // KEEP TURNING UNTIL THE RIGHT SENSOR DETECTS THE LINE
	while( left_sensor() < THRES && mid_sensor() > THRES && right_sensor() < THRES ); // KEEP TURNING UNTIL THE MIDDLE SENSOR DETECTS THE BLACK LINE
	
	_delay_ms(200); // WAIT TILL THE BOT HAS CROSSED THIS BLACK LINE
	
	while( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() < THRES ); // KEEP TURNING UNTIL ALL THE SENSORS ARE ON WHITE AREA
	while( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() > THRES ); // KEEP TURNING UNTIL THE RIGHT SENSOR DETECTS THE LINE
	while( left_sensor() < THRES && mid_sensor() > THRES && right_sensor() < THRES ); // KEEP TURNING UNTIL THE MIDDLE SENSOR DETECTS THE BLACK LINE
	
	stop(); // STOP THE BOT
	left();
	_delay_ms(50);
	stop(); // STOP THE BOT
	
	velocity( PWM_LEFT, PWM_RIGHT );
	
}

/*
* Function Name ::  void line_follow_till_wall( void )
* Input  :: void
* Output :: void
* Logic  :: follow the black line until the bot reaches the wall
* Example Call  :: line_follow_till_wall();
*/
void line_follow_till_wall()
{
	forward();
	while( ( sharp_left() < WALL_PRESENT ) || ( sharp_right() < WALL_PRESENT ) )
	{
		if( left_sensor() < THRES && mid_sensor() > THRES && right_sensor() < THRES ) // IF THE MIDDLE SENSOR IS ON THE BLACK LIEN AND THE OTHER TWO SENSORS ARE WHITE,
			forward(); // MOVE THE BOT FORWARD
		else if( left_sensor() > THRES && mid_sensor() < THRES && right_sensor() < THRES ) // IF THE LEFT SENSOR IS ON THE BLACK LINE AND THE OTHER TWO SENSORS ARE ON WHITE,
			f_soft_left(); // TURN THE BOT LEFT
		else if( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() > THRES ) // IF THE RIGHT SENSOR IS ON THE BLACK LINE AND THE OTHER TWO SENSORS ARE WHITE
			f_soft_right(); // TURN THE BOT RIGHT
	}
}

/*
* Function Name ::  void wall_forward( void )
* Input  :: void
* Output :: void
* Logic  :: follows the wall and then the black line upto the node
* Example Call  :: 
*/
void wall_forward()
{
	OCR4C = 412; // PULL IN THE GRIPPER PLATES SO THAT THEY DONT COLLIDE WITH THE WALLS DURING ANY MISALIGNMENT
	servo_rotate(0, 490);
	line_follow_till_wall();
	while(1) // REPEAT THE FOLLOWING INFINITELY
	{

		while( ( sharp_left() > WALL_PRESENT ) && ( sharp_left() < MAX_WALL_DIST_LEFT ) && ( sharp_right() > WALL_PRESENT ) && ( sharp_right() < MAX_WALL_DIST_RIGHT ) ) // IF THE WALL IS AT A SAFE DISTANCE FROM BOTH THE SHARP SENSORS, MOVE FORWARD
		{
			forward(), velocity(PWM_LEFT, PWM_RIGHT);
		}
		stop(); 
		if (sharp_left() > MAX_WALL_DIST_LEFT )
		{
	
			while( sharp_left() > MAX_WALL_DIST_LEFT ) // IF THE RIGHT SHARP SENSOR IS VERY CLOSE TO THE BOT, THEN TURN RIGHT
			{
				f_soft_right(), velocity(730, 0);
			}
			stop();
			
			
		}

		else if ( sharp_right() > MAX_WALL_DIST_RIGHT )
		{
			while( sharp_right() > MAX_WALL_DIST_RIGHT ) // IF THE LEFT SHARP SENSOR IS VERY CLOSE TO THE WALL, THEN TURN LEFT
			{
				f_soft_left(), velocity(0,730);
			}
			stop();
			
		}

		else if( sharp_left() < WALL_PRESENT && sharp_right() < WALL_PRESENT ) // IF THE WALL ARE AT A VERY LARGE DISTANCE FROM THE BOT THEN STOP THE BOT
		{
			break;	
		}
		forward(), velocity(600,600);
	}
	servo_rotate(0, 420); // RAISE THE ARM A LITTLE SO THAT IT DOSENT COLLLIDE WITH ANY HIGH-RISE HOUSES IN FRONT OF IT
	forward();
	_delay_ms(150);
	forward_node(1); // MOVE THE BOT FORWARD BY ONE NODE
	line_follow_dist_forward(80); 
}

/*
* Function Name ::  void zig_zag( void )
* Input  :: void
* Output :: void
* Logic  :: follows the zig-zag path upto the node
* Example Call  :: zig_zag();
*/
void zig_zag()
{
	int prev1 = 0; // 0 = forward, 1 = right, 2 = left
	int prev2 = 0; // 0 = forward, 1 = right, 2 = left
	
	forward();
	while (1)
	{
		if( left_sensor() > THRES && mid_sensor() > THRES && right_sensor() > THRES ) // IF ALL THREE SENSORS DETECT BLACK LINE, NODE IS ENCOUNTERED. BREAK FROM THE LOOP
			break;
			
		if( left_sensor() < THRES && mid_sensor() > THRES && right_sensor() < THRES ) // IF ONLY THE MIDDLE SENSOR DETECTS THE BLACK LINE, THE MOVE THE BOT FORWARD
			forward(),prev2 = prev1, prev1 = 0;
			
		if( left_sensor() > THRES && mid_sensor() < THRES && right_sensor() < THRES ) // IF ONLY THE LEFT SENSOR DETECTS THE BLACK LINE, THEN TURN LEFT
			left(),prev2 = prev1, prev1 = 2;
			
		if( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() > THRES ) // IF ONLY THE RIGHT SENSOR DETECTS THE BLACK LINE, THEN TURN RIGHT
			right(),prev2 = prev1, prev1 = 1;
			
		if( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() < THRES ) // IF NONE OF THE SENSORS DETECT THE BLACK LINE CHECK WHICH SENSORS HAD DETECTED THE LINE PREVIOUSLY
		{
			if( prev1 == 0 && prev2 == 1) // IF THE MID SENSOR HAD DETECTED THE LINE PREVIOUSLY AND THE RIGHT SENSOR BEFORE THAT, THE SEARCH THE LINE TO THE RIGHT
			{
				f_soft_right();
				while( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() < THRES ); // TURN THE BOT TO THE RIGHT UNTIL THE LINE IS FOUND
				stop();
			}
			else if( prev1 == 0 && prev2 == 2) // IF THE MID SENSOR HAD DETECTED THE LINE PREVIOUSLY AND THE LEFT SENSOR BEFORE THAT, THEN SEARCH THE LINE TO THE LEFT
			{
				f_soft_left();
				while( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() < THRES ); // TURN THE BOT LEFT UNTIL THE LINE IS FOUND
				stop();
			}
			else if( prev1 == 1 ) // IF THE RIGHT SENSOR HAD DETECTED THE LINE PREVIOUSLY, THEN SEARCH THE LINE TO THE RIGHT
			{
				f_soft_right();
				while( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() < THRES ); // TURN THE BOT RIGHT UNTIL THE LINE IS FOUND
				stop();
			}
			else if( prev2 == 2 ) // IF THE LEFT SENSOR HAD DETECTED THE LINE PREVIOUSLY, THEN SEARCH THE INE TO THE LEFT
			{
				f_soft_left();
				while( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() < THRES ); // TURN THE BOT LEFT UNTIL THE LINE IS FOUND
				stop();
			}
		}
			
	}
	forward();
	velocity(970,1017); // MOVE THE BOT FORWARD UNTIL THE NODE IS CROSSED
	_delay_ms(60);
	stop();
	forward();
	velocity(970,1017); // MOVE THE BOT FORWARD UNTIL THE NODE IS CROSSED
	_delay_ms(125);
	stop();
}

/*
* Function Name ::  void white_line_distance( void )
* Input  :: distance -> the distance to be travelled
* Output :: void
* Logic  :: follows the white line for the given distance
* Example Call  :: white_line_distance( 5000 );
*/
void white_line_distance( unsigned long int distance )
{
	for (i = 0; i < distance ; ++i) // 
	{
			 if( left_sensor() > THRES && mid_sensor() < THRES && right_sensor() > THRES ) // IF MIDDLE SENSOR IS ON THE BLACK LINE THEN MOVE FORWARD
			forward();
		else if( left_sensor() < THRES && mid_sensor() > THRES && right_sensor() > THRES ) // IF LEFT SENSOR IS ON THE BLACK LINE THEN TURN LEFT
			f_soft_left();
		else if( left_sensor() > THRES && mid_sensor() > THRES && right_sensor() < THRES ) // IF RIGHT SENSOR IS ON THE BLACK LINE THEN TURN RIGHT
			f_soft_right();
		else // IF NEIGHTER CONDITION IS SATISFIED, THEN MOVE FORWARD
			forward();
		
	}
	
	stop();
	back(); // MOVE THE BOT BACK TO COUNTER INERTIA
	_delay_ms(50);
	stop();
	
}

/*
* Function Name ::  void white_node( int mode, int house_type, int direction )
* Input  :: mode -> whether the bot is moving towards the house or away from it ( mode = 0 :: towards house, mode = 1 :: away from house )
*			house_type -> whether the house is high rise or low rise ( house_type = 0 :: low rise, house_type = 1 :: high rise )
*			direction -> whether to turn right or left for placing ( direction = 0 :: left turn , direction = 1 :: right turn )
* Output :: void
* Logic  :: follows the white line from white node to black node or vice-versa
* Example Call  :: white_node( 0, 1, 1 );
*/
void white_node( int mode , int house_type, int direction )
{
	if( mode == 0 ) // IF THE BOT IS MOVING TOWARDS THE HOUSE, THEN
	{
		forward();
		while( 1 ) // FOLLOW THE BLACK LINE UNTIL THE WHITE LINE
		{
			if( left_sensor() < THRES && mid_sensor() > THRES && right_sensor() < THRES ) // IF THE MIDDLE SENSOR IS ON THE WHITE LINE THEN MOVE FORWARD
				forward();
			if( left_sensor() > THRES && mid_sensor() < THRES && right_sensor() < THRES ) // IF THE LEFT SENSOR IS ON THE BLACK LINE, THEN TURN LEFT
				f_soft_left();
			if( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() > THRES ) // IF THE RIGHT SENSOR IS ON THE BLACK LINE, THEN TURN RIGHT
				f_soft_right();
			
			if( left_sensor() > THRES_WHITE && mid_sensor() < THRES_WHITE && right_sensor() > THRES_WHITE ) // IF THE MIDDLE SENSOR IS ON THE WHITE LINE, THEN BREAK
				break;
			if( left_sensor() < THRES_WHITE && mid_sensor() > THRES_WHITE && right_sensor() > THRES_WHITE ) // IF THE LEFT SENSOR IS ON THE WHITE LINE, THEN BREAK
				break;
			if( left_sensor() > THRES_WHITE && mid_sensor() > THRES_WHITE && right_sensor() < THRES_WHITE ) // IF THE RIGHT SENSOR IS ON THE WHITE LINE, THEN BREAK
				break;
		}
		while(1) // FOLLOW THE WHITE LINE TO THE NODE
		{
			if( left_sensor() > THRES_WHITE && mid_sensor() < THRES_WHITE && right_sensor() > THRES_WHITE ) // IF THE MIDDLE SENSOR IS ON THE WHITE LINE, THEN MOVE FORWARD
				forward(), velocity( PWM_LEFT, PWM_RIGHT );
			if( left_sensor() < THRES_WHITE && mid_sensor() > THRES_WHITE && right_sensor() > THRES_WHITE ) // IF THE LEFT SENSOR IS ON THE WHITE LINE, THEN TURN LEFT
				f_soft_left();
			if( left_sensor() > THRES_WHITE && mid_sensor() > THRES_WHITE && right_sensor() < THRES_WHITE ) // IF THE RIGHT SENSOR IS ON THE WHITE LINE, THEN TRN RIGHT
				f_soft_right();
			
			if( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() < THRES ) // IF ALL THE SENSORS ARE ON THE WHITE NODE, THEN BREAK
				break;
			if( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() > THRES ) // IF LEFT AND MIDDLE SENSORS ARE ON WHITE NODE, THEN BREAK
				break;
			if( left_sensor() > THRES && mid_sensor() < THRES && right_sensor() < THRES ) // IF RIGHT AND MIDDLE SENSORS ARE ON WHITE LINE, THEN BREAK
				break;
		}
		stop(); // STOP THE BOT
		white_line_distance(340); // MOVE THE BOT FORWARD BY SOME DISTANCE UNTIL THE BOT IS ABOVE THE NODE
		
		if(house_type == 0) // IF HOUSE IS LOW RISE
		OCR4A = 450, _delay_ms(600); // THEN LOWER THE ARM
		else				// ELSE IF HOUSE IS HIGH RISE
		OCR4A = 400, _delay_ms(200); // THEN LOWER THE ARM
		
		if( direction == 0 ) // IF THE HOUSE IS ON THE LEFT, THEN TURN LEFT
			left();
		else  // ELSE IF THE HOUSE IS ON THE RIGHT, THEN TURN RIGHT
			right();
		_delay_ms(430); // KEEP TURNING UNTIL THE BOT HAS CROSSED INTO BLACK REGION
		while( left_sensor() < THRES || mid_sensor() < THRES || right_sensor() < THRES ); // WAIT UNTIL ALL SENSORS ARE ON BLACK
		while( left_sensor() < THRES || mid_sensor() > THRES || right_sensor() < THRES ); // WAIT UNTIL THE MIDDLE SENSOR IS ON THE BLACK LINE
		
		stop(); // STOP THE BOT
		
		if( direction == 0 ) // TURN THE BOT IN THE OPPOSITE DIRECTION TO COUNTER INERTIA
			right();
		else
			left();
		_delay_ms(120);
		stop();
		
		OCR4C = 300; // RELAESE THE GRIPPER
		_delay_ms(600);
		
		OCR4A = 350; // RAISE THE ARM
		_delay_ms(280);
		
	}
	
	else
	{
		
		if( direction == 0 ) // IF THE HOUSE WAS ON THE RIGHT, THEN TURN THE BOT LEFT
			left();
		else // ELSE TURN THE BOT RIGHT
			right();
		_delay_ms(450); // WAIT UNTIL THE BOT CROSSES INTO THE BLACK REGION
		
		while( left_sensor() < THRES || mid_sensor() < THRES || right_sensor() < THRES ); // WAIT FOR ALL THE SENSORS TO CROSS INTO THE BLACK REGION
		while( left_sensor() < THRES || mid_sensor() > THRES || right_sensor() < THRES ); // WAIT UNTIL THE MIDDLE SENSOR DETECTS THE BLACK LINE
		
		stop();
		
		if( direction == 0 ) // ROTATE THE BOT IN THE OPPOSITE DIRECTION IT WAS ROTATING BEFORE TO COUNTER INERTIA
			right();
		else
			left();
		_delay_ms(100);
		stop();
		
		servo_rotate(0, 420);
		
		forward();
		while (1) // FOLLOW THE WHITE LINE UPTO THE BLACK LINE
		{
			if( left_sensor() > THRES_WHITE && mid_sensor() < THRES_WHITE && right_sensor() > THRES_WHITE ) // IF THE MIDDLE SENSOR IS ON THE WHITE LINE, THEN 
				forward();
			if( left_sensor() < THRES_WHITE && mid_sensor() > THRES_WHITE && right_sensor() > THRES_WHITE ) // IF THE LEFTVSENSOR IS ON THE WHITE LINE THEN TURN LEFT
				f_soft_left();
			if( left_sensor() > THRES_WHITE && mid_sensor() > THRES_WHITE && right_sensor() < THRES_WHITE ) // IF THE RIGHT SENSOR IS ON THE WHITE LINE, THEN TURN RIGHT
				f_soft_right();
				
			if( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() < THRES ) // IF ALL THE SENSOR DETECT WHITE LINE THEN BREAK
				break;
			if( left_sensor() < THRES && mid_sensor() > THRES && right_sensor() < THRES ) // IF THE MIDDLE SENSOR DETECTS THE BLACK LINE, THEN BREAK
				break;
			if( left_sensor() > THRES && mid_sensor() < THRES && right_sensor() < THRES ) // IF THE LEFT SENSOR DETECTS THE BLACK LINE, THEN TURN LEFT
				break;
			if( left_sensor() < THRES && mid_sensor() < THRES && right_sensor() > THRES ) // IF THE RIGHT SENSOR DETECTS THE BLACK LINE, THE TURN RIGHT
				break;
		}
		stop();
		back(); // MOVE THE BOT BACK FOR SOME TIME TO COUNTER THE INERTIA
		_delay_ms(50);
		stop();
		forward_node(1); // FOLLOW THE REMAINING WHITE LINE UPTO THE NODE
		back();
		_delay_ms(100); // MOVE THE BOT A LITTLE BACK TO COUNTER INERTIA
		stop();
		
	}
}


// SERVO ANGULAR MOTION


/*
* Function Name ::  void pick( void )
* Input  :: void
* Output :: void
* Logic  :: lowers the arm and picks the CM
* Example Call  :: pick()
*/
void pick( void )
{
	right();
	_delay_ms(45);
	stop();
	
	OCR4A = 550; // LOWER THE ARM
	_delay_ms(280);
	
	left();
	delay_ms(60);
	stop();
	
	OCR4C = 413; // GRIP THE BOX
	_delay_ms(350);
	
	servo_rotate(0, 385);
	_delay_ms(300);
}

/*
* Function Name ::  void place( int house_type, int direction )
* Input  :: house_type -> whether the house is high rise or low rise ( house_type = 0 :: low rise, house_type = 1 :: high rise )
*			direction -> whether to turn right or left to pick the box (  direction = 0 :: left turn, direction = 1 :: right turn, directio = 2 :: forward )
* Output :: void
* Logic  :: turn the bot in the given direction and place the CM in the house
* Example Call  :: place( 0, 1 );
*/
void place( int house_type ,int direction )
{
		
	if( house_type == 0 )
		line_follow_dist_forward(70);
	
	if( direction == 0 )
		left_turn_90(); // TAKE A 90 DEGREE TURN LEFT
	else if( direction == 1 )
		right_turn_90(); // TAKE A 90 DEGREE TURN RIGHT
	
	if( direction == 0 )
		line_follow_dist_forward(180); // IF THE CM IS TO BE PLACED FROM THE LEFT THEN MOVE THE BOT FORWARD A LITTLE FIRST
	else if( direction == 1 )
		line_follow_dist_forward(150); // IF THE CM IS TO BE PLACED FROM THE RIGHT THEN MOVE THE BOT FORWARD A LITTLE FIRST
	else
		line_follow_dist_forward(325); // IF THE CM IS TO BE PLACED FROM THE FRONT THEN MOVE THE BOT FORWARD VERY LITTLE

	if(house_type == 0) // HOUSE IS LOW RISE
		servo_rotate(0, 510); // LOWER THE ARM
	else				// HOUSE IS HIGH RISE
		servo_rotate(0, 413); // LOWER THE ARM
	
	
	OCR4C = 300; // RELAESE THE GRIPPER
	_delay_ms(200);
	
	servo_rotate(0, 375); // RAISE THE ARM
	_delay_ms(200);
}

void servo_rotate( int servo_number, int new_angle )
{
	if( servo_number == 0 )
	{
		int curr_angle = OCR4A;
		if( curr_angle < new_angle )
		{
			while( curr_angle < new_angle )
			{
				OCR4A = curr_angle ;
				_delay_ms(30);
				curr_angle = curr_angle + 10;
			}
			OCR4A = curr_angle;
			_delay_ms(30);
			OCR4A = curr_angle - 10;
			_delay_ms(30);
		}
		else
		{
			while( curr_angle > new_angle )
			{
				OCR4A = curr_angle;
				_delay_ms(30);
				curr_angle = curr_angle - 10;
		}
			OCR4A = curr_angle;
			_delay_ms(30);
			OCR4A = curr_angle - 10;
			_delay_ms(30);
		}
	}
	else
	{
		int curr_angle = OCR4C;
		if( curr_angle < new_angle )
		{
			while( curr_angle < new_angle )
			{
				OCR4C = curr_angle ;
				_delay_ms(30);
				curr_angle = curr_angle + 10;
			}
		}
		else
		{
			while( curr_angle > new_angle )
			{
				OCR4C = curr_angle;
				_delay_ms(30);
				curr_angle = curr_angle - 10;
			}
		}
	}
}


// BUZZER

/*
* Function Name ::  void buzzer_blink( void )
* Input  :: void
* Output :: void
* Logic  :: turn the buzzer on for 100 millis and then turn it off, useful for debugging
* Example Call  :: buzzer_blink();
*/
void buzzer_blink( void )
{
	PORTG = PORTG & ~( 1 << BUZZER ); // TURN THE BUZZER ON
	_delay_ms(100);					  // WAIT FOR 100 MILISECOND
	PORTG = PORTG | ( 1 << BUZZER );  // TURN THE BUZZER OFF
	
}

/*
* Function Name ::  void buzzer_5( void )
* Input  :: void
* Output :: void
* Logic  :: turn the bot on for 5 seconds to signal the end of task
* Example Call  :: buzzer_5();
*/
void buzzer_5( void )
{
	PORTG = PORTG & ~( 1 << BUZZER ); // TURN THE BUZZER ON
	_delay_ms(5000);				  // WAIT FOR 5 SECONDS
	PORTG = PORTG | ( 1 << BUZZER );  // TURN THE BUZZER OFF
	
}
