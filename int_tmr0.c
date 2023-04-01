//;UNIVERSIDAD DEL VALLE DE GUATEMALA
//;IE2023 Programación de Microcontroladores
//;Autor:		Mónica Alfaro
//;Compilador:	pic-as (v2.36), MPLABX (v6.00)
//;
//;Programa:	PRELAB6 (INT_TMR0 LED)	
//;
//;				
//;Dispositivo:	PIC16F887
//;Hardware:	LEDs en el puerto D, botones en el puerto B
//;
//;Creado:	       19 de febrero , 2023
//;Última modificación:  19 de febrero , 2023


// Incluir las bibliotecas necesarias
#include <xc.h>
#include <stdint.h>

// Definir los pines del LED
#define LED_PIN RC0

// Función para configurar el TMR0
void TMR0_init() {
    T0CS = 0; // Modo temporizador
    PSA = 0; // Habilitar preescalador
    PS2 = 1; // Configurar preescalador a 256
    PS1 = 0;
    PS0 = 0;
    TMR0 = 0; // Reiniciar el contador del TMR0
    TMR0IE = 1; // Habilitar interrupción del TMR0
}

// Función para cambiar el estado del LED
void LED_toggle() {
  LED_PIN ^= 1; // Cambiar el estado del LED
}

// Rutina de interrupción del TMR0
void __interrupt() ISR() {
    if(TMR0IF) { // Verificar si se produjo la interrupción del TMR0
        TMR0IF = 0; // Limpiar la bandera de interrupción
        TMR0 = 0; // Reiniciar el contador del TMR0
        LED_toggle(); // Cambiar el estado del LED
    }
}

// Función principal
void main() {
    TRISC0 = 0; // Configurar el pin del LED como salida
    TMR0_init(); // Configurar el TMR0
    PEIE = 1; // Habilitar interrupciones periféricas
    GIE = 1; // Habilitar interrupciones globales
    while(1) {
        // Hacer algo en el bucle principal si es necesario
    }
}
