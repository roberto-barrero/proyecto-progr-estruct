#include "fecha.h"
#include "usuarios.h"
#include <stdlib.h>

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
} Habitaciones[12] = {
	1, 0, 1,
	2, 0, 0,
	3, 0, 0,
	4, 0, 1,
	5, 1, 0,
	6, 1, 1,
	7, 1, 0,
	8, 1, 0,
	9, 2, 1,
	10, 2, 1,
	11, 2, 0, 
	12, 2, 0
};

struct TIPOSHABITACIONES_STRUCT { /*TIPOS DE HABITACION DISPONIBLES*/
	char tipoHab[9];
	int personas;
	float precio;
} tiposHabitaciones[] = {
	"Sencilla", 1, 250.25,
	"Doble", 2, 475.50,
	"Suite", 4, 999.99
};

struct RESERVACIONES_STRUCT{
 	int usuarioID;
	int numHab; //INDICE DE LA HAB
	fecha entrada;
	fecha salida;
};

//DETERMINAR LA CANTIDAD DE RESERVACIONES
int cantidadReservaciones(){
	FILE *archivoEntrada = NULL; 
	
	// ABRIR USUARIOS.BIN PARA LEER LOS DATOS GUARDADOS PREVIAMENTE
    archivoEntrada = fopen ("reservaciones.bin", "rb"); 
    if (archivoEntrada == NULL) { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    
    //CALCULAR TAMAÑO DEL ARCHIVO
	fseek(archivoEntrada, 0L, SEEK_END); 
    int res = ftell(archivoEntrada); 
    
    fclose(archivoEntrada);
    
    return res/32;
}

//GUARDAR LAS RESERVACIONES QUE COINCIDEN CON UN PERIODO ESPECIFICADO
void cargarReservaciones(int **habitaciones, fecha entrada, fecha salida, int * colisiones){

	FILE *archivoEntrada = NULL; 
	
    struct RESERVACIONES_STRUCT b;
    
    // ABRIR USUARIOS.BIN PARA LEER LOS DATOS GUARDADOS PREVIAMENTE
    archivoEntrada = fopen ("reservaciones.bin", "rb"); 
    if (archivoEntrada == NULL) { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    
	int contador = 0;
      
    //CALCULAR EL TAMAÑO DEL ARCHIVO

    int res = cantidadReservaciones(); 
    
    
  	//RESERVAR MEMORIA PARA LA CANTIDAD DE RESERVACIONES
  	struct RESERVACIONES_STRUCT  * reservaciones2 = malloc(sizeof(struct RESERVACIONES_STRUCT)*(res));
  	
    // LEER CONTENIDO DEL ARCHIVO HASTA EL FINAL 
    while(fread(&b, sizeof(struct RESERVACIONES_STRUCT), 1, archivoEntrada)){
    	if(fechaEntreFechas(b.entrada, b.salida, entrada, salida) == 1){
    		contador++;
    		(*habitaciones) = (int*)realloc(*habitaciones, contador*sizeof(int));
	    	reservaciones2[contador-1]= b; 
	    	(*habitaciones)[contador-1] = b.numHab;
		}
	}
	*colisiones = contador;
    
    //CERRAR ARCHIVOS
    fclose(archivoEntrada);
}

//IMPRIMIR LAS ULTIMAS N RESERVACIONES
void imprimirNReserv(int inicio){
	FILE * archivoEntrada = NULL;
	int i;
	
	archivoEntrada = fopen("reservaciones.bin", "rb");
	if (archivoEntrada == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit(1); 
    }
	struct RESERVACIONES_STRUCT temp;
	fseek(archivoEntrada, inicio*sizeof(struct RESERVACIONES_STRUCT), SEEK_SET);
	while(fread(&temp, sizeof(struct RESERVACIONES_STRUCT), 1, archivoEntrada)){
		imprimirReservacion(temp);
	}
	printf("\n");
	fclose(archivoEntrada);
}

//GUARDAR RESERVACION EN EL ARCHIVO
void guardarReservacion(int hab, int ID, fecha entrada, fecha salida){
	FILE *outfile; 
	
	struct RESERVACIONES_STRUCT x;
	
	fflush(stdin);
	
	x.usuarioID = ID;
	x.numHab = hab;
	x.entrada = entrada;
	x.salida = salida;
    
    outfile = fopen("reservaciones.bin", "ab"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    }
    
    //ESCRIBIR DATOS AL ARHCIVO
    fwrite (&x, sizeof(struct RESERVACIONES_STRUCT), 1, outfile); 
      
    if(fwrite == 0)  
        printf("error writing file !\n"); 
        
    //CERRAR ARCHIVO
    fclose (outfile);
}

//IMPRIMIR UNA RESERVACION
void imprimirReservacion(struct RESERVACIONES_STRUCT r){
	printf("\Habitacion %d reservada del ", r.numHab+1);
	imprimirFecha(r.entrada);
	printf(" al ");
	imprimirFecha(r.salida);
	printf(" por el usuario %s", buscarUsuarioPorID(r.usuarioID)->nombre);
	printf("\n");
}

//IMPRIMIR TODAS LAS RESERVACIONES
void imprimirReservaciones(int numeracion){
	FILE *archivoEntrada = NULL; 
    struct RESERVACIONES_STRUCT b;
    // ABRIR USUARIOS.BIN PARA LEER LOS DATOS GUARDADOS PREVIAMENTE
    archivoEntrada = fopen ("reservaciones.bin", "rb"); 
    if (archivoEntrada == NULL) { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    int r = 1;
    // LEER CONTENIDO DEL ARCHIVO HASTA EL FINAL 
    if(numeracion){
    	while(fread(&b, sizeof(struct RESERVACIONES_STRUCT), 1, archivoEntrada)){
	    	printf("[%d]	", r);
	    	imprimirReservacion(b);
	    	printf("\n");
	    	r++;
		}
	} else {
		while(fread(&b, sizeof(struct RESERVACIONES_STRUCT), 1, archivoEntrada)){
	    	imprimirReservacion(b);
	    	printf("\n");
		}
	}
    
    
    //CERRAR ARCHIVOS
    fclose(archivoEntrada);
}

//IMPRIMIR LAS HABITACIONES DE UN MISMO TIPO DISPONBLES EN UNA FECHA
void imprimirHabDisponibles(int tipoDeHabitacion, fecha entrada, fecha salida){
	printf("HABITACIONES TIPO %s DISPONIBLES", tiposHabitaciones[tipoDeHabitacion].tipoHab);
	titulo("");
	int i, j, tru;
	
	int * reservaciones = NULL;
	int colisiones;
	cargarReservaciones(&reservaciones, entrada, salida, &colisiones);
	for(i = 0; i < 4; i++){
		tru = 0;
		for(j = 0; j < colisiones; j++){
			if(reservaciones[j] == (tipoDeHabitacion*4)+i){
				tru = 1;
			}
		}
		if(!tru){
			printf("\n- %d", (tipoDeHabitacion*4)+i+1);
		}
	}
	printf("\n");
}

//DETERMINAR LA CANTIDAD DE HABITACIONES DISPONIBLES DE UN MISMO TIPO EN UNA FECHA
int habDisponibles(int tipo, fecha entrada, fecha salida){
	int i, k, tru=0, contador = 0;
	int *reservaciones = NULL;
	int colisiones;
	cargarReservaciones(&reservaciones, entrada, salida, &colisiones);
	
	//VALIDAR LAS HABITACIONES QUE COLISIONAN
	for(i = 0; i < 12; i++){
		//VERIFICAR QUE SEA DEL MISMO TIPO
		if(Habitaciones[i].tipoHab == tipo){
			tru = 0;
			//COMPARAR CON CADA RESERVACION
			for(k = 0; k < colisiones; k++){
				if(i == reservaciones[k]){
					tru = 1;
				}
			}
			if(!tru){
				contador++;
			}
		}
	}
	return contador;
}

//IMPRIMIR LA INFORMACION DE LAS HABITACIONES, INDICANDO LA CANTIDAD DE HAB DISPONIBLES
void imprimirInfoHabitaciones(int habitaciones[3]){
	int i;
	printf("\n|Habitación	|Precio	|Personas	|Disponibles	|");
	printf("\n|%s	|%g	|%d		|%d			|", tiposHabitaciones[0].tipoHab, tiposHabitaciones[0].precio, tiposHabitaciones[0].personas, habitaciones[0]);
	printf("\n|%s		|%g	|%d		|%d			|", tiposHabitaciones[1].tipoHab, tiposHabitaciones[1].precio, tiposHabitaciones[1].personas, habitaciones[1]);
	printf("\n|%s		|%g	|%d		|%d			|", tiposHabitaciones[2].tipoHab, tiposHabitaciones[2].precio, tiposHabitaciones[2].personas, habitaciones[2]);
}
