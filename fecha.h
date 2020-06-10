#ifndef FECHAH
#define FECHAH

#include <stdlib.h>
#include <stdio.h>

/*
Integrantes:
Roberto Barrero Santoyo
Juan Canul Pasos
Pablo Pech Pech
David Trujillo Vela
*/

/*DEFINIR TIPO DE VARIABLE FECHA*/
typedef struct FECHA_STRUCT{
	int dia;
	int mes;
	int anio;
} fecha;

void imprimirFecha(fecha x);

fecha nuevaFecha(int pedirAnio);

int calcularDias(fecha a, fecha b);

int fechaEntreFechas(fecha a, fecha b, fecha entrada, fecha salida);

#endif
