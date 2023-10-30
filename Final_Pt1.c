//Name:Aidan Stoner, Marc Santacapita, Shaunessy Reynolds, and Erin Cardino.
//Date:11/6/2023
//Course:ELEC-3371
//Description: This file will contain two functions, one to read the value from our
//             joystick and return someothing in a generic way. The other needs
//             read an analog potentiometer value.
//******************************************************************************
//Global Variables:

//******************************************************************************
//Main Function:
void main() {
//Initialization:
     RCC_APB2ENR |= 1 << 2;  //enables clock for PortA
     RCC_APB2ENR |= 1 << 3;  //enables clock for PortB
     RCC_APB2ENR |= 1 << 4;  //enables clock for PortC
     RCC_APB2ENR |= 1 << 5;  //enables clock for PortD
     RCC_APB2ENR |= 1 << 6;  //enables clock for PortE
     
     GPIOA_CRL = 0x00400000; //Sets PA6 as an input
     GPIOB_CRL = 0x00040000; //sets PB5 as an input
     GPIOB_CRH = 0x00400000; //sets PC13 as an input
     GPIOD_CRL = 0x00004040; //Set PD2 and PD4 as an input *as an FYI we
          //may have to change this later to be wihtin the function as for
          //obj 3 all of portD needs to be an ouput.
     GPIOE_CRH = 0x33333333; //Set PortE/H as an output for LEDS
//******************************************************************************

}