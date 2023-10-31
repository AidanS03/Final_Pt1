//Name:Aidan Stoner, Marc Santacapita, Shaunessy Reynolds, and Erin Cardino.
//Date:11/6/2023
//Course:ELEC-3371
//Description: This file will contain two functions, one to read the value from our
//             joystick and return someothing in a generic way. The other needs
//             read an analog potentiometer value.
//******************************************************************************
//Global Variables:

//******************************************************************************
//Function Prototypes:
int joyRead();
//******************************************************************************
//Main Function:
void main() {
//Initialization:
     RCC_APB2ENR |= 1 << 2;  //enables clock for PortA
     RCC_APB2ENR |= 1 << 3;  //enables clock for PortB
     RCC_APB2ENR |= 1 << 4;  //enables clock for PortC
     RCC_APB2ENR |= 1 << 5;  //enables clock for PortD
     RCC_APB2ENR |= 1 << 6;  //enables clock for PortE
     
     GPIOA_CRL = 0x44444444; //Sets PortA/L as an input
     GPIOB_CRL = 0x44444444; //sets PortB/L as an input
     GPIOC_CRH = 0x44444444; //sets PortC/H as an input
     GPIOD_CRL = 0x44444444; //Sets PortD/L as an input *as an FYI we
          //may have to change this later to be wihtin the function as for
          //obj 3 all of portD needs to be an ouput.
     GPIOE_CRH = 0x33333333; //Set PortE/H as an output for LEDS
//******************************************************************************
     for(;;){
          switch(joyRead()){
               case 0 : //no press
                    GPIOE_ODR = 0;
               case 1 : //up turn on PE11 and PE15
                    GPIOE_ODR.B11 = 1;
                    GPIOE_ODR.B15 = 1;
               case 2 : //right turn on PE9 and PE10
                    GPIOE_ODR.B9 = 1;
                    GPIOE_ODR.B10 = 1;
               case 3 : //down turn on PE8 and PE12
                    GPIOE_ODR.B8 = 1;
                    GPIOE_ODR.B12 = 1;
               case 4 : //left turn on PE13 and 14
                    GPIOE_ODR.B13 = 1;
                    GPIOE_ODR.B14 = 1;
               case 5 : //click turn on all
                    GPIOE_ODR =
          }
     }
}
//Function Definitions:
int joyRead(){
     if(GPIOD_IDR.B4 == 1){
          return 1; //joystick up return a 1
     }else if(GPIOA_IDR.B4 == 1){
          return 2; //joystick right return 2
     }else if(GPIOB_IDR.B5 == 1){
          return 3; //joystick down return 3
     }else if(GPIOD_IDR.B2 == 1){
          return 4; //joystick left return 4
     }else if(GPIOC_IDR.B13 == 1){
          return 5; //joystick clicked return 5
     }else return 0; //nothing pressed return 0
}