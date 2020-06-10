#ifndef HABITACIONESH
#define HABITACIONESH

#include "fecha.h"

/*
Integrantes:
Roberto Barrero Santoyo
Juan Canul Pasos
Pablo Pech Pech
David Trujillo Vela
*/

struct HABITACIONES_STRUCT{
	int numHab;
	int tipoHab;
	int ocupada;
} Habitaciones[12];

struct TIPOSHABITACIONES_STRUCT{ /*TIPOS DE HABITACION DISPONIBLES*/
	char tipoHab[9];
	int personas;
	float precio;
} tiposHabitaciones[];

struct RESERVACIONES_STRUCT{
	int usuarioID;
	int numHab;
	fecha entrada;
	fecha salida;
} reservaciones[];

struct RESERVACIONES_STRUCT  * reservaciones2;

void resetR();

void imprimirHabDisponibles(int x, fecha entrada, fecha salida);

int habDisponibles(int tipo, fecha entrada, fecha salida);

void imprimirInfoHabitaciones();

void guardarReservacion(int hab, int ID, fecha entrada, fecha salida);

void imprimirReservaciones(int numeracion);

void imprimirReservacion();

int cantidadReservaciones();

void cargarReservaciones(int **habitaciones, fecha entrada, fecha salida, int * colisiones);

#endif
