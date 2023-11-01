//Name:Aidan Stoner, Marc Santacapita, Shaunessy Reynolds, and Erin Cardino.
//Date:11/6/2023
//Course:ELEC-3371
//Description: This file will contain two functions, one to read the value from our
//             joystick and return someothing in a generic way. The other needs
//             read an analog potentiometer value.
//******************************************************************************
//Global Variables:
int joy = 0;
double pot;
//******************************************************************************
//Function Prototypes:
int joyRead();
int getPot();
int adjustVal();
//******************************************************************************
//Main Function:
void main() {
//Initialization:
     RCC_APB2ENR |= 1 << 2;  //enables clock for PortA
     RCC_APB2ENR |= 1 << 3;  //enables clock for PortB
     RCC_APB2ENR |= 1 << 4;  //enables clock for PortC
     RCC_APB2ENR |= 1 << 5;  //enables clock for PortD
     RCC_APB2ENR |= 1 << 6;  //enables clock for PortE
//******************************************************************************
     for(;;){
          joy = joyRead();
          switch(joy){
               case 0 : //no press
                    GPIOE_ODR = 0;
                    break;
               case 1 : //up turn on PE11 and PE15
                    GPIOE_ODR.B11 = 1;
                    GPIOE_ODR.B15 = 1;
                    break;
               case 2 : //right turn on PE9 and PE10
                    GPIOE_ODR.B9 = 1;
                    GPIOE_ODR.B10 = 1;
                    break;
               case 3 : //down turn on PE8 and PE12
                    GPIOE_ODR.B8 = 1;
                    GPIOE_ODR.B12 = 1;
                    break;
               case 4 : //left turn on PE13 and 14
                    GPIOE_ODR.B13 = 1;
                    GPIOE_ODR.B14 = 1;
                    break;
               case 5 : //click turn on all
                    GPIOE_ODR = 0xFF00;
                    break;
          }
          pot = adjustVal();
          GPIOD_ODR = pot;
     }
}
//Function Definitions:
int joyRead(){
     GPIOA_CRL |= 1 << 26; //Sets PA6 as an input
     GPIOB_CRL |= 1 << 22; //sets PB5 as an input
     GPIOC_CRH |= 1 << 22; //sets PC13 as an input
     GPIOE_CRH = 0x33333333; //Set PortE/H as an output for LEDS
     GPIOD_CRL = 0x40400; //Sets PD2 and PD4 as an input

     
     if(GPIOD_IDR.B4 == 0){
          return 1; //joystick up return a 1
     }else if(GPIOA_IDR.B6 == 0){
          return 2; //joystick right return 2
     }else if(GPIOB_IDR.B5 == 0){
          return 3; //joystick down return 3
     }else if(GPIOD_IDR.B2 == 0){
          return 4; //joystick left return 4
     }else if(GPIOC_IDR.B13 == 0){
          return 5; //joystick clicked return 5
     }else return 0; //nothing pressed return 0
}

int getPot(){
//double m = 99/3830;
//double b = 3731/3830;
//Configure the ADC
     GPIOD_CRL = 0x33333333; //sets GPIOD as an output
     GPIOD_CRH = 0x33333333;
     GPIOC_CRL = 0;
     RCC_APB2ENR |= 1 << 9 ; // Enable ADC1 Clock
     ADC1_SQR1 = (0b0000 << 20); // sets ADC to do 1 conversion
     ADC1_SQR3 = 10; // Select Channel 10 as only one in conversion sequence
     ADC1_SMPR1 = 0b100; // Set sample time on channel 10
     ADC1_CR2 |= (0b111 << 17); // Set software start as external event for regular group conversion
     ADC1_CR2.ADON = 1; // Enable ADC1

//read the value of the ADC
     ADC1_CR2 |= 1 << 20; //enables external trigger conversion mode
     ADC1_CR2 |= 1 << 22; //starts the conversion
     while(ADC1_SR.B1 != 1){} //wait until conversion is done
     //ADCval = ADC1_DR;
     //adjustedADC = ((99/3830) * ADCval) + (3731/3830); //pot goes from 0-3831 we want to display 1-100 so this formula
                               //scales the ADC value to be between 1 and 100
     //return adjustedADC;
     return ADC1_DR;
}

int adjustVal(){
     int ogvalue, value;
     double slope = 0.02584856397;
     double b = 0.974151436;
     ogvalue = getPot();
     value = (slope * ogvalue) + b + 0.5;
     return value;
}