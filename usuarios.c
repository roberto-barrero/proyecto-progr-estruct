#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "fecha.h"

/*
Integrantes:
Roberto Barrero Santoyo
Juan Canul Pasos
Pablo Pech Pech
David Trujillo Vela
*/

//DEFINIR ESTRUCTURA DE USUARIO
typedef struct USUARIO_STRUCT{
	int id;
	char nombre[50];
	char sexo;
	char telefono[11];
	fecha fechaNac;
	int formaPago;
	char correo[50];
} usuario;

//DEFINIR LOS VALORES POR DEFECTO DE UN USUARIO
const usuario USUARIO_DEFAULT = {-1, "DEFAULT", '0', "DEFAULT", {0, 0, 0}, -1, "DEFAULT"};

//DEFINIR METODOS DE PAGO
char metodosPago[3][10] = {"Efectivo", "Tarjeta", "PayPal"};

//REMOVER EL CARACTER '\n' QUE PUEDE SER GUARDADO AL USAR fgets
void removerEnter(char cadena[]){
	if(strchr(cadena, '\n') != NULL){
		*strchr(cadena, '\n') = ' ';
	}
}

//FUNCTION PARA IMPRIMIR LOS DATOS DE UN USUARIO, DADO UN USUARIO
void imprimirUsuario(usuario y){
	printf("\nID: %d", y.id);
	printf("\nNombre: %s", y.nombre);
	printf("\nSexo: %c", y.sexo);
	printf("\nFecha: ");
	imprimirFecha(y.fechaNac);
	printf("\nTeléfono: %s", y.telefono);
	printf("\nCorreo electrónico: %s", y.correo);
	printf("\nForma de pago: %s\n", metodosPago[y.formaPago]);
}

//FUNCION PARA CREAR Y GUARDAR UN NUEVO USUARIO, Y DEVOLVER SU ID
int nuevoUsuario(){ 
	usuario x;
	int confirmar = 0, cambio;
	
	//ABRIR ARCHIVO PARA ESCRIBIR
	FILE *outfile; 
    
	//VERFICAR QUE SE HAYA ABIERTO CORRECTAMENTE  
    outfile = fopen("usuarios.bin", "ab"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    }
    
  	//BUSCAR EL FINAL DEL ARCHIVO
    fseek(outfile, 0L, SEEK_END); 
  
    //CALCULAR EL TAMAÑO DEL ARCHIVO
    long int res = ftell(outfile); 
	
	//ASIGNAR EL SIGUIENTE ID AL NUEVO USUARIO
	x.id = 1000+(res/136);
	
	//PEDIR LOS DATOS DEL USUARIO
	printf("Ingrese su nombre completo: \n");
	fflush(stdin);
	fgets(x.nombre, 50, stdin);
	removerEnter(x.nombre);
	
	printf("Seleccione su sexo ('M' para masculino y 'F' para femenino):\n");
	x.sexo = getchar();
	
	printf("Ingrese su fecha de nacimiento:\n");
	x.fechaNac = nuevaFecha(1);
	
	printf("Ingrese su número de telefono (10 dígitos):\n");
	fflush(stdin);
	fgets(x.telefono, 11, stdin);
	removerEnter(x.telefono);
	
	printf("Ingrese su correo electrónico:\n");
	fflush(stdin);
	fgets(x.correo, 50, stdin);
	removerEnter(x.correo);
	
	printf("Seleccione su método de pago: \n");
	printf("[1]	Efectivo\n[2]	Tarjeta de crédito/debito\n[3]	PayPal");
	printf("\n\nSelección: ");
	fflush(stdin);
	scanf("%d", &x.formaPago);
	x.formaPago = x.formaPago - 1;
	
	//LIMPIAR LA PANTALLA Y PRESENTAR LOS DATOS INGRESADOS
	system("cls");
	
	titulo("CONFIRMAR");
	imprimirUsuario(x);
	
	//PREGUNTAR SI EL USUARIO DESEA HACER CAMBIOS A LOS DATOS
	printf("\n\n¿Desea hacer alguna modificación?");
	opcionesSiNo();
	printf("\n\nSelección: ");
	scanf("%d", &confirmar);
	
	//CICLO PARA REALIZAR TODOS LOS CAMBIOS QUE EL USUARIO DESEE
	 while (!confirmar){
	 	/*IMPRIMIR EL MENU DE CAMBIOS*/
	 	printf("\nSeleccione la opción a modificar: ");
	 	printf("\n\n[1]	Nombre");
	 	printf("\n[2]	Sexo");
	 	printf("\n[3]	Fecha de Nacimiento");
	 	printf("\n[4]	Teléfono");
	 	printf("\n[5]	Correo electrónico");
	 	printf("\n[6]	Forma de Pago");
	 	printf("\n\nSelección: ");
	 	fflush(stdin);
	 	scanf("%d", &cambio);
	 	
	 	//MODIFICAR EL DATO SELECCIONADO
	 	switch(cambio){
	 		case 1:
		 		printf("Ingrese su nombre completo:\n");
				fflush(stdin);
				fgets(x.nombre, 50, stdin);
				removerEnter(x.nombre);
				break;
			case 2:
				printf("Ingrese su sexo ('M' para masculino y 'F' para femenino):\n");
				getchar();
				x.sexo = getchar();
				break;
			case 3:
				printf("Ingrese su fecha de nacimiento:\n");
				x.fechaNac = nuevaFecha(1);
				break;
			case 4:
				printf("Ingrese su número de telefono:\n");
				fflush(stdin);
				fgets(x.telefono, 11, stdin);
				break;
			case 5:
				printf("Ingrese su correo electrónico:\n");
				fflush(stdin);
				gets(x.correo);
				break;
			case 6:
				printf("Seleccione su método de pago: \n");
				printf("[1]	Efectivo\n[2]	Tarjeta de crédito/debito\n[3]	PayPal");
				printf("\n\nSelección: ");
				fflush(stdin);
				scanf("%d", &x.formaPago);
				break;
		 }
		
		//IMPRIMIR DATOS REGISTRADOS
		system("cls");
		titulo("CONFIRMAR");
		imprimirUsuario(x);
		
		//PREGUNTAR SI EL USUARIO DESEA HACER MODIFICACIONES
		printf("\n\n¿Desea hacer alguna modificación?");
		printf("\n\n[0] Si\n[1] No");
		printf("\n\nSelección: ");
		fflush(stdin);
		scanf("%d", &confirmar);
	}
	
//GUARDAR DATOS EN EL ARCHIVO 'usuarios.bin'
      
    //ESCRIBIR DATOS AL ARHCIVO
    fwrite (&x, sizeof(usuario), 1, outfile); 
      
    if(fwrite == 0)  
        printf("error writing file !\n"); 
        
    //CERRAR ARCHIVO
    fclose (outfile);
    
    return x.id;
}//FIN nuevoUsuario()

//FUNCION PARA IMPRIMIR TODOS LOS USUARIOS
imprimirTodosUsuarios(){

FILE *archivoEntrada = NULL; 
    usuario b;
    // ABRIR 'usuarios.bin' PARA LEER LOS DATOS GUARDADOS PREVIAMENTE
    archivoEntrada = fopen ("usuarios.bin", "rb"); 
    if (archivoEntrada == NULL) { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
      
    // LEER CONTENIDO DEL ARCHIVO HASTA EL FINAL 
    while(fread(&b, sizeof(usuario), 1, archivoEntrada)){
    	imprimirUsuario(b);
    	printf("\n");
	}
    
    //CERRAR ARCHIVOS
    fclose(archivoEntrada); 
    system("PAUSE");
}//FIN imprimirTodosUsuarios()

//FUNCION PARA BUSCAR UN USUARIO PREVIAMENTE REGISTRADO
usuario * buscarUsuario(){
	int opcion, id;
	char correo[50];
	
	//IMPRIMIR MENU DE OPCIONES
	printf("\nSeleccione como desea ingresar: ");
	fflush(stdin);
	printf("\n[1] ID\n[2] Correo electrónico");
	printf("\n\nSelección: ");
	scanf("%d", &opcion);
	
	//VERIFICAR SELECCION
	while(opcion < 1 || opcion > 2){
		printf("\nSeleccione como desea ingresar: ");
		fflush(stdin);
		printf("\n[1] ID\n[2] Correo electrónico");
		printf("\n\nSelección: ");
		scanf("%d", &opcion);
	}
	
	FILE *archivoEntrada = NULL; 
    usuario temp, b;
    b = USUARIO_DEFAULT;
    
    // ABRIR 'usuarios.bin' PARA LEER LOS DATOS GUARDADOS PREVIAMENTE
    archivoEntrada = fopen ("usuarios.bin", "rb"); 
    if (archivoEntrada == NULL) { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    
    //BUSCAR USUARIO DEPENDIENDO DE LA SELECCION
	switch(opcion){
		case 1:
			printf("\nIngrese el ID del usuario: ");
			scanf("%d", &id);
			while(fread(&temp, sizeof(usuario), 1, archivoEntrada)){
				if(temp.id == id){
					b = temp;
					break;
				}
			}
			break;
		case 2:
			printf("\nIngrese el correo electrónico: ");
			fflush(stdin);
			fgets(correo, 50, stdin);
			removerEnter(correo);
			while(fread(&temp, sizeof(usuario), 1, archivoEntrada)){
				if(strcmp(correo, temp.correo)==0){
					b = temp;
					break;
				}
			}
	}
	
	//VERIFICAR QUE SE HAYA ENCONTRADO UN USUARIO
	if(b.id != -1){
	printf("\nUSUARIO ENCONTRADO:\n");    
    imprimirUsuario(b);
	} 
    //CERRAR ARCHIVOS
    fclose(archivoEntrada);
    
    return &b;
	
}//FIN buscarUsuario()

//FUNCION PARA BUSCAR UN USUARIO POR ID
usuario* buscarUsuarioPorID(int id){

	FILE *archivoEntrada = NULL; 
    usuario temp, b;
    b = USUARIO_DEFAULT;
    
    // ABRIR USUARIOS.BIN PARA LEER LOS DATOS GUARDADOS PREVIAMENTE
    archivoEntrada = fopen ("usuarios.bin", "rb"); 
    if (archivoEntrada == NULL) { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    
	while(fread(&temp, sizeof(usuario), 1, archivoEntrada)){
		if(temp.id == id){
			b = temp;
			break;
		}
	}  
    
    //CERRAR ARCHIVOS
    fclose(archivoEntrada);
    return &b;
}

//FUNCION PARA IMPRIMIR UN USUARIO POR ID
void imprimirUsuarioPorID(int id){
	FILE *archivoEntrada = NULL; 
    usuario temp, b;
    b = USUARIO_DEFAULT;
    // ABRIR USUARIOS.BIN PARA LEER LOS DATOS GUARDADOS PREVIAMENTE
    archivoEntrada = fopen ("usuarios.bin", "rb"); 
    if (archivoEntrada == NULL) { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
      
    // LEER CONTENIDO DEL ARCHIVO HASTA EL FINAL 
    while(fread(&temp, sizeof(usuario), 1, archivoEntrada)){
		if(temp.id == id){
			b = temp;
			break;
		}
	}
    
    imprimirUsuario(b);
    //CERRAR ARCHIVOS
    fclose(archivoEntrada);
}

