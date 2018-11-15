#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "time.h"
#include "Bool.h"
#define limpiar() system("cls")
#define FILE_NAME_EMP "empleados.dat"

 struct empleado_Type
 {
 	int id;
 	char nombre[20];
 	char user[10];
 	char password[10];
 	int status;
 };
 typedef struct empleado_Type Empleado;


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char mje[20]="";
char nomreUser[30];
char terminal[30] = "FESC Izcalli Edomex";

//declarando las estructuras.
//




int main(int argc, char *argv[]) {
	int success = FALSE;

	do
	{
		limpiar();
		printLogo();
		muestraTituloMenu(1);
		puts(mje);
		int access = verificaUser();
		if (access == TRUE)
		{
			menuPrincipal();
			success = TRUE;
		}
		else{
			printf("\n\tERROR \n");
			strcat(mje, "\t ERROR ");
			success = FALSE;
		}
		
	}
	while(success != TRUE);

	return 0;
}

/*
	|------------------------------- PARA EL INICIO DE LA SES0'ION ---------------------|
*/
int verificaUser(){
	Bool value = FALSE;
	char user[20];
	printf("\n");
	printf("\t\tUSERNAME: ");
	gets(user);
	printf("\t\tPASSWORD: ");
	char pass[20];
    int conta=0;
    int i=0;
    int caracter;
     //Se piden caracteres hasta que se introduca enter
    do
    {
         //Capturamos carácter
    	caracter = getch();
        pass[i]=caracter;
        //Si es un carácter válido y no se ha sobrepasado el límite de 20 caracteres se imprime un asterisco
        if(pass[i]>32 && i<20){
          putchar('*');
          i++;
        }  
    }
    while(caracter!=13);
    
    pass[i]='\0';
    strcat(nomreUser, "Christian Rene Pioquinto Hernandez");
    if(!strcmp(pass, "1234") && !strcmp(user, "chris")){
    	value = TRUE;
    }
    else{
        value =  FALSE;
    }
    return value;
}



void muestraTituloMenu(int type){
	switch(type){
		case 1:
			printf("\n");
			printf("\t\t( I | N | I | C | I | A | R ) \n\t\t ( S | E | S | I | O | N ) \n");
		break;
		case 2:
			printf("\n");
			printf("\t\t\t(B I E N V E N I D O S ) \n\t\t ( M E N U  )  ( P R I N C I P A L ) \n");
		break;
	}
}

void muestraMenu(int type){
	switch(type){
		case 1:
			printf("\n");
			printf("\t+-----------------------------------------------------------------------------+\n");
			printf("\t| DESTINOS (1) | VENTA (2) | ADMINISTRACION (3) | CALCULADORA (4) | SALIR (0) |\n");
			printf("\t+-----------------------------------------------------------------------------+\n");
		break;
		case 2:
			printf("\t+-------------------------------------------------------------------------------------------+\n");
			printf("\t| SELEECIONE DESTINO -> ELIJA ASIENTO -> VERIFICAR IFORMACION -> CONFIRMA VENTA | SALIR (0) |\n");
			printf("\t+-------------------------------------------------------------------------------------------+\n");
		break;
	}
}

void printLogo(){
	limpiar();
	printf("\E[45;33;5m*******************************************************************************************\E[00m\n");
	printf("\t\n");
	printf("\t  _____ _______       _____  ____  _    _  _____    \E[33;36;5m     /\\      \E[00m\n");
	printf("\t / ____|__   __|/\\   |  __ \\|  _ \\| |  | |/ ____|\E[33;36;5m       /  \\      \E[00m\n");
	printf("\t| (___    | |  /  \\  | |__) | |_) | |  | | (___    \E[33;36;5m    /    \\    \E[00m\n");
	printf("\t \\___ \\   | | / /\\ \\ |  _  /|  _ <| |  | |\\___ \\\E[33;36;5m______/      \\________  \E[00m \n");
	printf("\t ____) |  | |/ ____ \\| | \\ \\| |_) | |__| |____) |   _| _  |   o _    \E[33;36;5m/     \E[00m\n");
	printf("\t|_____/   |_/_/    \\_\\_|  \\_\\____/ \\____/|_____/   (_|(/_ ||_||(_)  \E[33;36;5m/     \E[00m\n");
	printf("\t                                                             _|    \E[33;36;5m/          \E[00m\n");
	printf("\E[45;33;5m*******************************************************************************************\E[00m\n");
}
/*
	|------------------------------- PARA EL INICIO DE LA SESION ---------------------|
*/
void muestraInfo(){
	printLogo();
	muestraTituloMenu(2);

	printLogo();
	muestraTituloMenu(2);
	printf("\n\t\tUSER: %s\n\t\tFECHA: ",nomreUser);
	fechaHora();
	printf("\tTERMINAL: %s\n\n",terminal);
}

void menuPrincipal(){
	int opc;
	do{
	muestraInfo();
	muestraMenu(1);
	printf("\n\t\tEIJA UNA OPCION: ");
	scanf("%i",&opc);
		switch(opc){
			case 1:
				muestraInfo();
				muestraMenu(1);
				muestraDestinos();
				printf("\t\t\t Presiona cualquier numero para regresar \n");
				int opc;
				scanf("%i",&opc);
			break;
			case 2:
				muestraInfo();
				muestraMenu(2);
				muestraDestinos();
				printf("\t\tSELECCIONE DESTINO:  ");
				scanf("%i",&opc);
				muestraInfo();
				muestraMenu(2);
				muestraBus(opc);
				printf("\t\tSELECCIONE ASIENTO:  ");
				scanf("%i",&opc);
				int asiento = verificaAsiento(1,opc);
				muestraInfo();
				muestraMenu(2);
				char nombreUser[30];
				printf("\t\tESCRIBA NOMBRE DEL PASAJERO:  ");
				scanf("%s", &nombreUser);
				printf("\t\tPasajero: %s ASIENTO: %d\n",nombreUser, asiento);
				printf("\t\t PROCEDER A PAGO (Y/N) ");
				char termina[1];
				scanf("%s",&termina[0]);
				if (termina[0] == 'Y' || termina[0] == 'y')
				{
					imprimirTicket();
				}

			break;
			case 3:
				printf("\ttADMINISTRACION\n");
			break;
			case 4:
				system("calc.exe");
			break;
			case 0:
				printLogo();
				printf("\n\n\t\t\tVUELVA PRONTO\n");
				printf("\t\t\tP R O G R A M M E R \n\t\t\t CHRISTIAN RCGS\n");
			break;
		}
	}
	while(opc != 0);
}

void muestraDestinos(){
	printf("\t\t\t\t_____________________________________________________\n");
	printf("\t\t\t\t| ID   DESTINO         ASIENTOS  COSTO     SALIDA   |\n");
	printf("\t\t\t\t| 1    Puebla Pue.       40/40   $240.00    15:40   |\n");
	printf("\t\t\t\t| 2    Xalapa Ver.       35/40   $540.00    03:50   |\n");
	printf("\t\t\t\t| 3    Tlaxcala Tlax.    20/30   $200.00    21:40   |\n");
	printf("\t\t\t\t| 4    Pachuca Hgo.      10/30   $300.00    10:00   |\n");
	printf("\t\t\t\t| 5    Matamoros Tam.    40/40   $1200.00   09:45   |\n");
	printf("\t\t\t\t| 5    Cuernavaca Mor.   01/40   $560.00    14:30   |\n");
	printf("\t\t\t\t|___________________________________________________|\n");
}

/*
	|------------------------------- PARA EL INICIO DE LA SESION ---------------------|
*/

fechaHora(){
	time_t t;
	struct tm *tm;
	char fechayhora[100];

	t=time(NULL);
	tm=localtime(&t);
	strftime(fechayhora, 100, "%d/%m/%Y", tm);
	printf ("%s", fechayhora);
}


void muestraBus(int id){
	//id es el numero del corrida
	int asiento;
	//Consultando la corrida
	printf("\tCORRIDA: FES - DESTINO \t HORA: 15:30 \tDISPONIBLES: 25/32");
	printf("\t\E[37;41;5m[XX]\E[00m -> OCUPADO  \E[37;42;5m[00]\E[00m -> DISPONIBLE\n");

	printf("\t\t\t\t__________________________\n");
	printf("\t\t\t\t| |(O)|                  |\n");	
	printf("\t\t\t\t|                        |\n");	
	printf("\t\t\t\t| [01] [02]    [03] [04] |\n");
	printf("\t\t\t\t| [05] \E[37;41;5m[XX]\E[00m    [07] [08] |\n");
	printf("\t\t\t\t| [09] [10]    [11] [12] |\n");
	printf("\t\t\t\t| [12] [14]    [15] [16] |\n");
	printf("\t\t\t\t| [17] \E[37;41;5m[XX]\E[00m    [19] [20] |\n");
	printf("\t\t\t\t| [21] [22]    [23] [24] |\n");
	printf("\t\t\t\t| [25] [26]    [27] [28] |\n");
	printf("\t\t\t\t| [29] [30]    [31] [32] |\n");
	printf("\t\t\t\t|                        |\n");
	printf("\t\t\t\t| [  W C  ]    [  W C  ] |\n");
	printf("\t\t\t\t|________________________|\n");
}

int verificaAsiento(int id, int asiento){
	//iniciamos el llenado del array de asientos del ID de corrida
	int tam;
	tam = 33;
	int isFree = 0;
	int asientos[] = {0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	//llenado de asientos
	while (isFree !=1){
		if (asientos[asiento-1] != 0)
			isFree = 1;
		else{
			printf("\n\t\t \E[37;41;5mAsiento ocupado\E[00m elija otro: ");
			scanf("%d",&asiento);
			isFree = 0;
		}

	}
	return asiento;
}


int imprimirTicket(int venta){
	printf("TICKETTTT\n");
	system("pause");
	return 1;
}
