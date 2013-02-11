#include "adcHelper.h"
#include "messages.h"
#include "maindefs.h"

void adcInit() {

    TRISA = 0x0F;	// set RA3-RA0 to inputs
    //Configure required pins
    ANCON0bits.PCFG0 = 0;

    //Set voltage reference
    ADCON0bits.VCFG0 = 0;
    ADCON0bits.VCFG1 = 0;

    //Select A/D Input channel
    ADCON0bits.CHS0 = 0;

    //Set acquisition time
    ADCON1bits.ACQT0 = 7;
    ADCON1bits.ACQT1 = 7;
    ADCON1bits.ACQT2 = 7;

    //Set conversion time
    ADCON1bits.ADCS0 = 5;
    ADCON1bits.ADCS1 = 5;

    //Enable ADC module
    ADCON0bits.ADON = 1;

    ADCON0bits.GODONE = 1;
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
}

void adcReadyNextRead() {
    ADCON0bits.GODONE = 1;
}

void adcIntHandler() {

    //ADC output
    unsigned short res  = (short)(ADRESH << 8) | (short)ADRESL;
//    res >>= 6;
    unsigned char reading = res >> 8;
//    res = (float)res * (float)0xFFFF / (float)0x3FF;
//    res = res / 0xFFC0;  //Normalize 10-bit max

//    unsigned short output = res * (float)0xFFFF;

    ToMainLow_sendmsg(sizeof(char), MSG_ADC_DATA, &reading);

    //Clear ADC
    PIR1bits.ADIF = 0;
}