#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "habitaciones.h"
#include "fecha.h"
#include "usuarios.h"

/*
Integrantes:
Roberto Barrero Santoyo
Juan Canul Pasos
Pablo Pech Pech
David Trujillo Vela
*/

int idUsuarioActual = -1;

//IMPRIMIR MENU DE OPCIONES SI O NO
void opcionesSiNo(){
	printf("\n[1] Si");
	printf("\n[2] No");
}

//IMPRIMIR EL TITULO DE CADA MENU CON UN SEPARADOR (FORMATO)
void titulo(char texto[]){
	printf("%s\n", texto);
	int i;
	//IMPRIMIR EL SEPARADOR
	for(i = 0; i < 20; i++){
		printf("-");
	}
	printf("\n");
}

//CERRAR PROGRAMA
void salir(){
	printf("Vuelva pronto :)\n");
	system("PAUSE");
	exit(1);
}

//RESERVAR HABITACIONES
void reservar(){
	system("cls");
	titulo("RESERVAR");
	
	//INICIALIZACION DE VARIABLES
	int cantHuespedes, contador, seleccion, masHabitaciones, habRestantes, dias, i, k, m;
	fecha entrada, salida;
	
	//INGRESAR LAS FECHAS A RESERVAR
	printf("\nIngrese la fecha de entrada.\n\n");
	entrada = nuevaFecha(0);
	printf("\nIngrese la fecha de salida.\n\n");
	salida = nuevaFecha(0);
	
	//VALIDAR QUE LA SALIDA SEA IGUAL O POSTERIOR A LA ENTRADA
	while(calcularDias(entrada, salida) < 0){
		printf("\n\nPor favor, seleccione una fecha de salida válida.\n");
		salida = nuevaFecha(0);
	}
	
	dias = calcularDias(entrada, salida)+1;
	
	//DETERMINAR CUANTAS Y CUALES RESERVACIONES COLISIONAN
	int colisiones = 0;
	int *habitacionesReservadas = NULL;		
	cargarReservaciones(&habitacionesReservadas, entrada, salida, &colisiones);
	int *habitacionesReservadas2 = (int*)habitacionesReservadas;
	
	//DETERMINAR LA CANTIDAD DE HABITACIONES DISPONIBLES EN LAS FECHAS SELECCIONADAS
	habRestantes = 12-colisiones;
	
	//CALCULAR Y GUARDAR LAS HABITACIONES DISPONIBLES EN ESAS FECHAS POR TIPO DE HABITACION
	int cantHabDisp[] = {habDisponibles(0, entrada, salida), habDisponibles(1, entrada, salida), habDisponibles(2, entrada, salida)};
	
	//PEDIR LA CANTIDAD DE HUESPEDES
	printf("\nIngrese la cantidad de huéspedes: ");
	scanf("%d", &cantHuespedes);
	
	//VALIDAR CANTIDAD DE HUESPEDES
	while(cantHuespedes <= 0){
		printf("\nIngrese una cantidad válida de huéspedes: ");
		scanf("%d", &cantHuespedes);
	}
	
	//DETERMINAR SI HAY ESPACIO SUFICIENTE PARA LOS HUESPEDES INGRESADOS
	if(cantHabDisp[0]+cantHabDisp[1]*2+cantHabDisp[2]*4 < cantHuespedes){
		printf("Lo sentimos, no tenemos suficientes habitaciones disponibles en el periodo seleccionado.");
		system("PAUSE");
	} else {
	
	
	//IMPRIMIR LA CANTIDAD DE HABITACIONES DISPONIBLES EN LAS FECHA SELECCIONADAS
	imprimirInfoHabitaciones(cantHabDisp);
	
	//CONTADOR DE HABITACIONES SELECCIONADAS POR TIPO
	int tipoHabSeleccionadas[] = {0, 0, 0};
	
	//PEDIR AL USUARIO SELECCIONAR TIPOS DE HABITACION HASTA QUE PUEDA ALOJAR A LOS HUESPEDES INDICADOS
	contador = cantHuespedes;
	while(contador > 0){
		
		//PEDIR AL USUARIO ELEGIR EL TIPO DE HABITACION
		printf("\nPersonas restantes: %d", contador);//INDICA LA CANTIDAD RESTANTE DE HUESPEDES A ALOJAR
		printf("\nSeleccione el tipo de habitación que desea reservar: ");
		printf("\n[1] Sencilla\n[2] Doble\n[3] Suite\n");
		printf("\n\nSelección: ");
		scanf("%d", &seleccion);
		
		//VALIDAR QUE AUN HAYA HABITACIONES DISPONIBLES DEL TIPO SELECCIONADO
		if(cantHabDisp[seleccion-1] <= 0){
			while(cantHabDisp[seleccion-1] <= 0){
				printf("No quedan mas habitaciones tipo %s disponibles. Seleccione otro tipo", tiposHabitaciones[seleccion-1]);
				printf("\n[1] Sencilla\n[2] Doble\n[3] Suite\n");
				printf("\n\nSelección: ");
				scanf("%d", &seleccion);
			}
		}
		
		
		contador = contador - tiposHabitaciones[seleccion-1].personas;//ACTUALIZAR LA CANTIDAD DE PERSONAS POR ALOJAR
		cantHabDisp[seleccion-1] = cantHabDisp[seleccion-1] - 1;//ACTUALIZAR LA CANTIDAD DE HABITACIONES DISPONIBLES DEL TIPO SELECCIONADO
		tipoHabSeleccionadas[seleccion-1] = tipoHabSeleccionadas[seleccion-1]+1;//ACTUALIZAR LA CANTIDAD DE HABITACIONES RESERVADAS
		habRestantes--;//ACTUALIZAR LA CANTIDAD DE HABITACIONES DISPONIBLES GENERAL
	}       
	//PREGUNTAR SI EL USUARIO QUIERE RESERVAR MAS HABITACIONES DEL MINIMO NECESARIO PARA ALOJAR A LOS HUESPEDES INDICADOS
	if(habRestantes>0){
		printf("¿Desea reservar más habitaciones?");
		opcionesSiNo();
		printf("\n\nSelección: ");
		scanf("%d", &masHabitaciones);
	}
	
	//CONTINUAR SELECCIONANDO TIPOS DE HABITACION HASTA QUE EL USUARIO INDIQUE (O HASTA QUE SE AGOTEN LAS HABITACIONES)
	while(masHabitaciones==1 && habRestantes>0){
		printf("Seleccione el tipo de habitación que desea reservar: ");
		printf("\n[1] Sencilla\n[2] Doble\n[3] Suite\n");
		printf("\n\nSelección: ");
		scanf("%d", &seleccion);
	
		if(cantHabDisp[seleccion-1] <= 0){
			while(cantHabDisp[seleccion-1] <= 0){
				printf("No quedan mas habitaciones tipo %s disponibles. Seleccione otro tipo", tiposHabitaciones[seleccion-1]);
				printf("\n[1] Sencilla\n[2] Doble\n[3] Suite\n");
				printf("\n\nSelección: ");
				scanf("%d", &seleccion);
			}
		}
		contador = contador - tiposHabitaciones[seleccion-1].personas;
		cantHabDisp[seleccion-1] = cantHabDisp[seleccion-1] - 1;
		tipoHabSeleccionadas[seleccion-1] = tipoHabSeleccionadas[seleccion-1]+1;
		printf("%d", cantHabDisp[seleccion-1]);
		habRestantes--;
		
		if(habRestantes>0){
			printf("¿Desea reservar más habitaciones?");
			opcionesSiNo();
			printf("\n\nSelección: ");
			scanf("%d", &masHabitaciones);
		} else {
			printf("No quedan más habitaciones disponibles.");
			masHabitaciones = 0;
		}
	}
	printf("\n");
	
	//IMPRIMIR EL SUBTOTAL Y TOTAL DE LAS HABITACIONES SELECCIONADAS
	titulo("SUBTOTAL");
	float total = 0;
	for(i = 0; i < 3; i++){
		if(tipoHabSeleccionadas[i] > 0){
			printf("\n%s x%d por %d días $%g", tiposHabitaciones[i], tipoHabSeleccionadas[i], dias, tipoHabSeleccionadas[i]*tiposHabitaciones[i].precio*dias);
		}
		total = total + tipoHabSeleccionadas[i]*tiposHabitaciones[i].precio*dias;
	}
	printf("\nTOTAL	$%g\n", total);
	system("PAUSE");
	//GUARDAR EL NUMERO DE HABITACION DE LAS HABITACIONES DISPONIBLES
	int habDisponibles3[12-colisiones];
	int a = 0, tru = 0;
	for(i = 0; i < 12; i++){
		tru = 0;
		for(k = 0; k < colisiones; k++){
			if(habitacionesReservadas2[k] == i){
				tru = 1;
			}
		}
		if(!tru){
			habDisponibles3[a] = i;
			a++;
		}
	}
	printf("\n");
	int reservPrevias = cantidadReservaciones();
	
	//EL USUARIO SELECCIONA EL NUMERO DE HABTIACION QUE DESEE RESERVAR
	if(habRestantes>0){
		int habSeleccionada;
		for(i = 0; i < 3; i++){
			if(cantHabDisp[i] > 0){
				for(k = 0; k < tipoHabSeleccionadas[i]; k++){
					do {
						tru = 0;
						imprimirHabDisponibles(i, entrada, salida);
						printf("\n\nSelección: ");
						fflush(stdin);
						scanf("%d", &habSeleccionada);
						for(m = 0; m < 12-colisiones; m++){
							if(habDisponibles3[m] == habSeleccionada-1 && i == Habitaciones[habSeleccionada-1].tipoHab){
								tru = 1;
								m = 12;
							}
						}
					} while(!tru);
					guardarReservacion(habSeleccionada-1, idUsuarioActual, entrada, salida);
				}
			} else {
				for(k = 0; k < 12-colisiones; k++){
					if(Habitaciones[habDisponibles3[k]].tipoHab == i){
						guardarReservacion(habDisponibles3[k], idUsuarioActual, entrada, salida);
					}
				}
			}
			
		}
	} else {
		for(i = 0; i < 12-colisiones; i++){
			guardarReservacion(habDisponibles3[i], idUsuarioActual, entrada, salida);
		}
	}
	printf("\n");
	
	//IMPRIMIR LAS RESERVACIONES REALIZADAS
	imprimirNReserv(reservPrevias);
	system("PAUSE");
}
}//FIN reservar()

//MENU DE RESERVACION
void menuReservar(){
	int tipoUsuario, numUsuario, confirmacion = 0;
	if(idUsuarioActual != -1){
		printf("Desea reservar como el usuario %s?", (*buscarUsuarioPorID(idUsuarioActual)).nombre);
		opcionesSiNo();
		printf("\n\nSelección: ");
		scanf("%d", &confirmacion);
	}
	if(confirmacion == 1){
		system("cls");
		reservar();
	} else {
		system("cls");
		titulo("\n\nRESERVAR");
		printf("\nEliga la opción que corresponda: ");
		printf("\n[1]	Usuario existente\n[2]	Nuevo usuario");
		printf("\n\nSelección: ");
		fflush(stdin);
		scanf("%d", &tipoUsuario);
		
		while(tipoUsuario <= 0 || tipoUsuario > 2){
			printf("\n\nSeleccione una opción válida.\n");
			printf("\nEliga la opción que corresponda: ");
			printf("\n[1]	Usuario existente\n[2]	Nuevo usuario");
			printf("\n\nSelección: ");
			fflush(stdin);
			scanf("%d", &tipoUsuario);
		}
	
		switch(tipoUsuario){
		usuario validar;
			case 1:
				validar = *buscarUsuario();
				if(validar.id == -1){
					int volverAIntentar;
    				printf("Usuario no encontrado. ¿Desea volver a intentar?");
    				opcionesSiNo();
    				printf("\n\nSelección: ");
    				scanf("%d", &volverAIntentar);
			    	if(volverAIntentar == 1){
			    		menuReservar();
					}
				} else {
			    	idUsuarioActual = validar.id;
			    	system("PAUSE");
			    	reservar();
				}
				break;
			case 2:
				idUsuarioActual = nuevoUsuario();
				printf("\nUsuario Actual:\n");
				imprimirUsuarioPorID(idUsuarioActual);
				system("PAUSE");
				reservar();
				break;
		}
	}
}

//ELIMINAR UNA RESERVACION GUARDADA
void eliminarReservacion(int reservEliminar){
	FILE * archivoEntrada = NULL;
	FILE * archivoSalida = NULL;
	struct RESERVACIONES_STRUCT b;
	
	archivoEntrada = fopen("reservaciones.bin", "rb");
	archivoSalida = fopen("reservaciones2.bin", "wb"); 
    if (archivoEntrada == NULL || archivoSalida == NULL) { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    int contador = 0;  
    // LEER CONTENIDO DEL ARCHIVO HASTA EL FINAL 
    while(fread(&b, sizeof(struct RESERVACIONES_STRUCT), 1, archivoEntrada) && contador < reservEliminar){
    	fwrite(&b, sizeof(struct RESERVACIONES_STRUCT), 1, archivoSalida);
    	contador++;
	}
	contador = reservEliminar+1;	
	fseek(archivoEntrada, contador*sizeof(struct RESERVACIONES_STRUCT), SEEK_SET);
	while(fread(&b, sizeof(struct RESERVACIONES_STRUCT), 1, archivoEntrada)){
    	fwrite(&b, sizeof(struct RESERVACIONES_STRUCT), 1, archivoSalida);
    	contador++;
	}
	fclose(archivoEntrada);
	fclose(archivoSalida);
	if (remove("reservaciones.bin") == 0)
    {
        printf("\nReservación eliminada correctamente.\n");
    } else{
    	perror("No se pudo eliminar el archivo");
	}
	rename("reservaciones2.bin", "reservaciones.bin");
	
	imprimirReservaciones(0);
	system("PAUSE");
}

//EDITAR UNA RESERVACION GUARDADA
void editarReservacion(){
	
	titulo("EDITAR RESERVACIÓN");
	//INICIALIZACION DE VARIABLES
	int cantHuespedes, contador, seleccion, masHabitaciones, habRestantes, dias;
	fecha entrada, salida;
	
	//PEDIR AL USUARIO SELECCIONAR LA RESERVACION A EDITAR
	imprimirReservaciones(1);
	int reservEditar;
	printf("Seleccione el número de la reservacion a editar: ");
	fflush(stdin);
	scanf("%d", &reservEditar);
	reservEditar--;
	int eliminar;
	printf("Desea eliminar la reservación?");
	opcionesSiNo();
	printf("\n\nSelección: ");
	scanf("%d", &eliminar);
	
	if(eliminar==1){
		eliminarReservacion(reservEditar);
	} else {
		
	FILE *outfile; 
	
	outfile = fopen("reservaciones.bin", "r+b"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    }
	//INGRESAR LAS FECHAS A RESERVAR
	printf("\nIngrese la nueva fecha de entrada.\n\n");
	entrada = nuevaFecha(0);
	printf("\nIngrese la nueva fecha de salida.\n\n");
	salida = nuevaFecha(0);
	
	//VALIDAR QUE LAS SALIDA SEA IGUAL O POSTERIOR A LA ENTRADA
	while(calcularDias(entrada, salida) < 0){
		printf("\n\nDesafortunadamente todavía no podemos viajar en el tiempo. Por favor, seleccione una fecha de salida vállida.\n");
		salida = nuevaFecha(0);
	}
	
	//DETERMINAR CUANTAS Y CUALES RESERVACIONES COLISIONAN
	int colisiones = 0;
	int *habitacionesReservadas = NULL;		
	cargarReservaciones(&habitacionesReservadas, entrada, salida, &colisiones);
	int *habitacionesReservadas2 = (int*)habitacionesReservadas;
	
	//DETERMINAR LA CANTIDAD DE HABITACIONES DISPONIBLES EN LAS FECHAS SELECCIONADAS
	habRestantes = 12-colisiones;
	
	//CALCULAR LAS HABITACIONES DISPONIBLES EN ESAS FECHAS POR TIPO DE HABITACION
	int cantHabDisp[] = {habDisponibles(0, entrada, salida), habDisponibles(1, entrada, salida), habDisponibles(2, entrada, salida)};
	int i, k;
	
	//DETERMINAR SI HAY ESPACIO SUFICIENTE PARA LOS HUESPEDES INGRESADOS
	if(habRestantes <= 0){
		printf("Lo sentimos, no tenemos suficientes habitaciones disponibles.");
		system("PAUSE");
		salir();
	}
	
	//IMPRIMIR LA CANTIDAD DE HABITACIONES DISPONIBLES EN LAS FECHA SELECCIONADAS
	imprimirInfoHabitaciones(cantHabDisp);
	
	int habSeleccionada = -1;
	
	//PEDIR AL USUARIO QUE SELECCIONE EL EL TIPO DE HABITACION A RESERVAR
	printf("\nSeleccione el tipo de habitación que desea reservar: ");
	printf("\n[1] Sencilla\n[2] Doble\n[3] Suite\n");
	printf("\n\nSelección: ");
	fflush(stdin);
	scanf("%d", &habSeleccionada);
	
	//VALIDAR QUE HAYA HABITACIONES DISPONIBLES DEL TIPO SELECCIONADO
	if(cantHabDisp[habSeleccionada-1] <= 0 && habSeleccionada != 0){
		while(cantHabDisp[habSeleccionada-1] <= 0){
			printf("No quedan mas habitaciones tipo %s disponibles. Seleccione otro tipo", tiposHabitaciones[habSeleccionada-1]);
			printf("\n[1] Sencilla\n[2] Doble\n[3] Suite\n[0]Cancelar edición\n");
			printf("\n\nSelección: ");
			scanf("%d", &habSeleccionada);
		}
	}
	if(habSeleccionada == 0){
		salir();
	}
	
	//GUARDAR EL NUMERO DE HABITACION DE LAS HABITACIONES DISPONIBLES
	int habDisponibles3[12-colisiones];
	int a = 0, tru = 0;
	for(i = 0; i < 12; i++){
		tru = 0;
		for(k = 0; k < colisiones; k++){
			if(habitacionesReservadas2[k] == i){
				tru = 1;
			}
		}
		if(!tru){
			habDisponibles3[a] = i;
			a++;
		}
	}
	printf("\n");
	
	//EL USUARIO SELECCIONA EL NUMERO DE HABTIACION QUE DESEE RESERVAR

	imprimirHabDisponibles(habSeleccionada-1, entrada, salida);
	printf("\n\nSelección: ");
	fflush(stdin);
	scanf("%d", &habSeleccionada);
	
	struct RESERVACIONES_STRUCT x, anterior;
	
	fseek(outfile, reservEditar*sizeof(struct RESERVACIONES_STRUCT), SEEK_SET);
	fread(&anterior, sizeof(struct RESERVACIONES_STRUCT), 1, outfile);
	
	x.entrada = entrada;
	x.salida = salida;
	x.usuarioID = anterior.usuarioID;
	x.numHab = habSeleccionada-1;
	fseek(outfile, reservEditar*sizeof(struct RESERVACIONES_STRUCT), SEEK_SET);

	fwrite (&x, sizeof(struct RESERVACIONES_STRUCT), 1, outfile); 

	fclose(outfile);
	imprimirReservaciones(0);
	system("PAUSE");
	}		
}

//VERIFICAR LA DISPONIBILIDAD EN UNA FECHA
void disponibilidad(){
	int tipoHab, i, verdad = 0;
	
	printf("Ingrese la fecha de entrada: ");
	fecha entrada = nuevaFecha(0);
	printf("Ingrese la fecha de salida: ");
	fecha salida = nuevaFecha(0);
	
	printf("\nSeleccione la opción que corresponda: ");
	printf("\n[1] Verificar tipo de habitación");
	printf("\n[2] Verificar habitación específica");
	fflush(stdin);
	printf("\n\nOpción: ");
	scanf("%d", &tipoHab);
	
	if(tipoHab == 1){
		/*PRESENTAR LAS OPCIONES AL USUARIO*/
		printf("Seleccione el tipo de habitación que desea: ");
		printf("\n[1]	Sencilla");
		printf("\n[2]	Doble");
		printf("\n[3]	Suite");
		printf("\n[4]	Todas");
		printf("\n\nOpción: ");
		
		fflush(stdin);
		scanf("%d", &tipoHab);
		
		/*VALIDAR QUE LA OPCIÓN ELEGIDA SEA VÁLIDA*/
		while(tipoHab < 1 || tipoHab > 4){
			printf("Opción no válida. Ingese una opción válida.");
			fflush(stdin);
			scanf("%d", &tipoHab);
		}
		
		/*IMPRIMIR LAS HAB DISPONIBLES DEL TIPO SELECCIONADO POR EL USUARIO*/
		if(tipoHab != 4){
			imprimirHabDisponibles(tipoHab-1, entrada, salida);
		} else {
			imprimirHabDisponibles(0, entrada, salida);
			imprimirHabDisponibles(1, entrada, salida);
			imprimirHabDisponibles(2, entrada, salida);
			
		}
	} else {
		printf("\nIngrese el número de habitación a verificar (1-12): ");
		fflush(stdin);
		scanf("%d", &tipoHab);
		
		while(tipoHab < 1 || tipoHab > 12){
			printf("\nIngrese el número de habitación a verificar (1-12): ");
		fflush(stdin);
		scanf("%d", &tipoHab);
		}
		int colisiones;
		int * habitacionesReservadas = NULL;
		cargarReservaciones(&habitacionesReservadas, entrada, salida, &colisiones);
		for(i = 0; i < colisiones; i++){
			if(habitacionesReservadas[i] == tipoHab-1){
				verdad = 1;
			}
		}
		if(verdad){
			printf("\nLa habitación %d no está disponible en el periodo seleccionado.", tipoHab);
		} else {
			printf("\nLa habitación %d está disponible en el periodo seleccionado.", tipoHab);
		}
	}
	printf("\n");
	system("PAUSE");
}

//IMPRIMIR TODAS LAS RESERVACIONES
void imprimirTodasReservaciones(){
	int seleccion;
	
	system("cls");
	titulo("IMPRIMIR RESERVACIONES");
	printf("\nSeleccione la opción que corresponda: ");
	printf("\n[1] Imprimir reservaciónes de un usuario");
	printf("\n[2] Imprimir todas las reservaciones");
	printf("\n\nSelección: ");
	scanf("%d", &seleccion);
	
	while (seleccion < 1 || seleccion > 2){
		printf("\n\nSelección: ");
		scanf("%d", &seleccion);
	}
	
	if(seleccion == 2){
		imprimirReservaciones(0);
	} else {
		int idUsuario, i;
		
		printf("\nIngrese el ID del usuario: ");
		fflush(stdin);
		scanf("%d", &idUsuario);

		FILE * archivo = NULL;
		
		archivo = fopen ("reservaciones.bin", "rb"); 
	    if (archivo == NULL) { 
	        fprintf(stderr, "\nError opening file\n"); 
	        exit (1); 
	    }
	    struct RESERVACIONES_STRUCT b;
	    while(fread(&b, sizeof(struct RESERVACIONES_STRUCT), 1, archivo)){
	    	if(b.usuarioID == idUsuario){
	    		printf("\n");
				imprimirReservacion(b);
			}
		}
		fclose(archivo);
	}
	
	system("PAUSE");
}

//OPCIONES DEL MENU PRINCIPAL
struct OPCIONES_STRUCT{
		int numOpcion;
		char descOpcion[35];
		void (*func)();
	} opciones[] = {
		1, "Reservar habitación", menuReservar,
		2, "Verificar disponibilidad", disponibilidad,
		3, "Imprimir Reservaciones", imprimirTodasReservaciones,
		4, "Imprimir Usuarios", imprimirTodosUsuarios,
		5, "Editar/Eliminar Reservación", editarReservacion,
		6, "Salir", salir
	};

//MENU PRINCIPAL
void menu(){ //IMPRIMIR EL MENU DE OPCIONES
	system("cls");
	int a, seleccion;
	
	
	titulo("INICIO");
	printf("¿En qué le podemos ayudar hoy?\n\n");
	
	//IMPRIMIR LAS OPCIONES QUE SE HAYAN DEFINIDO
	for(a = 0; a < sizeof(opciones)/sizeof(struct OPCIONES_STRUCT); a++){
		printf("[%d]	%s\n", opciones[a].numOpcion, opciones[a].descOpcion);
	}
	fflush(stdin);	
	scanf("%d", &seleccion);
	
	//VERIFICAR QUE LA OPCION INGRESADA SEA VALIDA
	if(seleccion >= 1 && seleccion <=sizeof(opciones)/sizeof(struct OPCIONES_STRUCT)){
		system("cls");
		opciones[seleccion-1].func();
	} else{
		printf("La opción que ingresó no es válida.");
			system("PAUSE");
			menu();
	}
}

main(){
	setlocale(LC_ALL, "Spanish");
	
	//REGRESAR AL MENU HASTA QUE EL USUARIO DECIDA SALIR
	while(1){
		menu();
	}

	system("PAUSE");
	
	return 0;
}
