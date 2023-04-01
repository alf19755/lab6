//UNIVERSIDAD DEL VALLE DE GUATEMALA
//IE2023 Programación de Microcontroladores
//Autor:		Mónica Alfaro
//Compilador:	pic-as (v2.36), MPLABX (v6.00)
//
//Programa:	LAB6  (2 CONTADORES CONTROLADOS CON POT POR ADC)	
//
//				
//Dispositivo:	PIC16F887
//Hardware:	LEDs en el puerto D, botones en el puerto B
//
//Creado:	       27 de marzo , 2023
//Última modificación:   27 de marzo , 2023


// Incluir las bibliotecas necesarias
#include <xc.h>
#include <pic16f887.h>
#include <stdint.h>
#include <stdio.h>

//Definir la frecuencia de reloj
#define _XTAL_FREQ 4000000
//Palabras de configuración


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// Variables globales
unsigned int contador = 0; // contador binario
unsigned int valor_pot = 0; // valor del potenciómetro leído por el ADC

// Función para inicializar el ADC
void initADC()
{
    // Configuración del ADC
    ADCON0bits.ADCS = 0b10; // Fosc/32
    ADCON1bits.ADFM = 0; // justificado a la izquierda
    ADCON1bits.VCFG0 = 0; // Vref+ = VDD
    ADCON1bits.VCFG1 = 0; // Vref- = VSS
    
    // Habilitar el ADC
    ADCON0bits.ADON = 1;
}

// Función para leer el valor del potenciómetro a través del ADC

int checkpot()
{
    ADCON0bits.CHS = 0b0000; // canal AN0
    __delay_us(10); // esperar la adquisición de la muestra
    ADCON0bits.GO_DONE = 1; // iniciar la conversión
    while (ADCON0bits.GO_DONE); // esperar hasta que la conversión termine
    return ADRESH; // leer el valor del ADC (solo se necesitan los 8 bits más significativos)
}

// Función para configurar el puerto y los pines
void configurarPuertos()
{
    TRISA = 0b00000001; // RA0 como entrada (potenciómetro)
    TRISB = 0b00000000; // RB0-RB7 como salidas (LEDs)
    ANSEL = 0b00000001; // RA0 como entrada analógica
    ANSELH = 0b00000000; // AN8-AN12 como entradas digitales
    PORTB = 0b00000000; // apagar los LEDs al inicio
}

// Función principal
void main()
{
    configurarPuertos();
    initADC();
    
    while (1)
    {
        valor_pot = checkpot(); // leer el valor del potenciómetro
        contador = (valor_pot * 255) / 1023; // escalar el valor del potenciómetro a un valor de 0-255
        PORTB = contador; // mostrar el valor del contador binario en los LEDs
    }
}