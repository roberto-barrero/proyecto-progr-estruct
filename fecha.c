#include "fecha.h"

/*
Integrantes:
Roberto Barrero Santoyo
Juan Canul Pasos
Pablo Pech Pech
David Trujillo Vela
*/

//FUNCION PARA IMPRIMIR LA FECHA CON FORMATO XX/XX/XXXX */
void imprimirFecha(fecha x){
	printf("%d/%d/%d", x.dia, x.mes, x.anio);
}

//CANTIDAD DE DIAS CORRESPONDIENTES A CADA MES
int diasMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//CREAR UNA NUEVA FECHA
fecha nuevaFecha(int pedirAnio){
	fecha f;
	
	printf("*Ingrese números únicamente*\n");
	printf ("Día: ");
	fflush(stdin);
	scanf("%d", &f.dia);
	printf ("Mes: ");
	fflush(stdin);
	scanf("%d", &f.mes);
	
	//SOLICITAR O NO EL AÑO
	if(pedirAnio){
		printf ("Año: ");
		fflush(stdin);
		scanf("%d", &f.anio);
	} else {
		f.anio = 2020;
	}
	return f;
}

//CALCULAR LA CANTIDAD DE DÍAS ENTRE DOS FECHAS
int calcularDias(fecha a, fecha b){
	int dias = 0, i;
	
	if(a.mes == b.mes && a.dia > b.dia){
		return -calcularDias(b, a);
	} else if(a.mes > b.mes){
		return -calcularDias(b, a);
	} else{
		if(a.mes != b.mes){
			dias = dias + (diasMes[a.mes-1] - a.dia);
			for(i = 0; i < (b.mes - a.mes)-1; i++){
				dias = dias + diasMes[a.mes+i];
			}
			dias = dias + b.dia;
		} else {
			dias = b.dia - a.dia;
		}
		return dias;
	}
}

//DETERMINAR SI UN PERIODO DE TIEMPO(entrada - salida) SE ENCUENTRA DENTRO DE OTRO (a - b)
int fechaEntreFechas(fecha a, fecha b, fecha entrada, fecha salida){
	if(calcularDias(a, entrada) <= 0){
		if(calcularDias(entrada, salida) < calcularDias(entrada, a)){
			return 0;
		} else {
			return 1;
		}
	} else if(calcularDias(a, entrada) > 0){
		if(calcularDias(entrada, b) >= 0){
			return 1;
		} else {
			return 0;
		}
	}
}
