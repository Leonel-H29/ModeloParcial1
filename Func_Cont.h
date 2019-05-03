#ifndef LISTA_H_
#define LISTA_H_
#include <stdio.h>
#include <stdlib.h>


int cantidad_cont();
int opcion_menu();
void final();
char seguir_prom();
void Pausa();
int Num_contacto();


void Pausa(){
	printf("--Presione cualquier tecla para continuar\n");
	getch();
}

int cantidad_cont(){
	int num;

	printf("--Ingrese la cantidad de contactos: ");
	scanf("%d", &num);
	fflush(stdin);

	return num;
}

int Num_contacto(){
	int num;

	printf("--Ingrese el n° del contacto: ");
	scanf("%d", &num);
	fflush(stdin);

	while(num < 1500000000){
		printf("**Numero de telefono no valido\n--Ingrese el n° del contacto: ");
		scanf("%d", &num);
	    fflush(stdin);
	}
	return num;
}

int opcion_menu(){
	int num;
	printf("1) Buscar contactos\n");
	printf("2) Agregar contactos\n");
	printf("3) Eliminar contactos\n");
	printf("Ingrese aqui: ");
	scanf("%d", &num);
	fflush(stdin);

	while(num==0 || num > 3){
		printf("**Opcion incorrecta**\nIngrese una opcion valida\n--Ingrese la cantidad de contactos: ");
		printf("1) Agregar contactos\n");
	    printf("2) Eliminar contactos\n");
	    printf("Ingrese aqui: ");
	    scanf("%d", &num);
	    fflush(stdin);
	}
	return num;
}

void final(){
	exit(0);
}

char seguir_prom(){
	char letra;
	printf("--Desea continuar? (S/N):  ");
	letra = getchar();
	fflush(stdin);
	while(letra !='S' && letra !='s' && letra !='N' && letra !='n'){
		printf("**Opcion incorrecta**\nIngrese una opcion valida\n--Desea continuar? (S/N): ");
		letra = getchar();
	    fflush(stdin);
	}
	return letra;
}

#endif