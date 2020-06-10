/*
Integrantes:
Roberto Barrero Santoyo
Juan Canul Pasos
Pablo Pech Pech
David Trujillo Vela
*/

typedef struct USUARIO_STRUCT{
	int id;
	char nombre[50];
	char sexo;
	long telefono;
	fecha fechaNac;
	int formaPago;
	char correo[];
} usuario;

const usuario USUARIO_DEFAULT;

char metodosPago[3][10];

void removerEnter(char cadena[], int a);

void imprimirUsuario(usuario y);

int nuevoUsuario();

void imprimirTodosUsuarios();

usuario * buscarUsuario();

usuario * buscarUsuarioPorID(int id);

void imprimirUsuarioPorID(int id);



