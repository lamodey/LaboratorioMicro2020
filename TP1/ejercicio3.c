/*
 * File:   ejercicio 3.C
 * Author: matias
 *
 * Created on 11 de abril de 2020, 16:53
 */

#define _XTAL_FREQ 4000000

#pragma config FOSC = EXTRCIO
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)
#include <xc.h>

void init() 
{
    CMCON = 0b00000111;
    ANSEL = 0;
    TRISIO = 0b11111110; //bit en 1 es input, en 0 es output. Seteo GP0 como OUTPUT y los demás como INPUT.
    GPIO = 0; //clear GPbits.
}

void test()
{
    GP1 = 0;
    __delay_ms(2000);//apagado 2 segundos
    GP1 = 1;
    __delay_ms(1);
    GP1 = 0;
    __delay_ms(5000);//parpadeando 5 segundos
    GP1 = 1;
    __delay_ms(1);
    GP1 = 0;
    __delay_ms(5000);//apagado 5 segundos
}

int wait(){ //devuelve 1 si se debe cambiar el estado
    int entradaanterior = GP1;
    int contador = 0;
    while(contador < 1000){ //el ciclo tardara un segundo salvo que se apriete y se suelte el pulsador
        __delay_ms(1);
        if(entradaanterior == 1 && GP1 == 0){//solte el boton
            return 1;
        }
        entradaanterior = GP1;
        contador++;
    }
    return 0;
}

void alternoled(){ //cambio el valor de la salida(LED))
    if(GP0 == 1){
        GP0 = 0 ;
    }else GP0 = 1 ;
}

void main(){
    init();
    GP0 = 0;
    GP1 = 0;
    int estado = 0;
    while(1){
        switch(estado){
            case 0://inicial(llego aca con el led apagado) 
                if(wait() == 1){
                   estado = 1; 
                }
            break;
            case 1://encendido(llego aca con el led apagado)
                alternoled();
                if(wait() == 1){
                   estado = 2;
                   break;
                }              
            break; 
            case 2://apagado(llego aca con el parpadeo activo)
                GP0 = 0;
                estado = 0;
                break;
        }           
    }
}