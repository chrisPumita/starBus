#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "time.h"
#include "Bool.h"
#define limpiar() system("cls")


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char mje[20]="";
char nomreUser[30];
char terminal[30] = "FESC Izcalli Edomex";


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
	|------------------------------- PARA EL INICIO DE LA SESION ---------------------|
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


void printLogo(){
	limpiar();
	printf("\t\n");
	printf("\t  _____ _______       _____  ____  _    _  _____         /\\      \n");
	printf("\t / ____|__   __|/\\   |  __ \\|  _ \\| |  | |/ ____|       /  \\      \n");
	printf("\t| (___    | |  /  \\  | |__) | |_) | |  | | (___        /    \\    \n");
	printf("\t \\___ \\   | | / /\\ \\ |  _  /|  _ <| |  | |\\___ \\______/      \\________   \n");
	printf("\t ____) |  | |/ ____ \\| | \\ \\| |_) | |__| |____) |   _| _  |   o _    /     \n");
	printf("\t|_____/   |_/_/    \\_\\_|  \\_\\____/ \\____/|_____/   (_|(/_ ||_||(_)  /     \n");
	printf("\t                                                             _|    /          \n");
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
			printf("\t+-----------------------------------------------------------+\n");
			printf("\t| DESTINOS (1) | VENTA (2) | ADMINISTRACION (3) | SALIR (0) |\n");
			printf("\t+-----------------------------------------------------------+\n");
		break;
		case 2:
			printf("\n");
		break;
	}
}

/*
	|------------------------------- PARA EL INICIO DE LA SESION ---------------------|
*/
void muestraInfo(){
	printLogo();
	muestraTituloMenu(2);

	printLogo();
	muestraTituloMenu(2);
	printf("\n\t\tUSER: %s\tFECHA: ",nomreUser);
	fechaHora();
	printf("\n\t\tTERMINAL: %s\n\n",terminal);
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
				muestraDestinos();
				muestraMenu(1);
				printf("\n\t\tEIJA UNA OPCION: ");
				int opc;
				scanf("%i",&opc);
			break;
			case 2:
				printf("\t\tVENTA\n");
			break;
			case 3:
				printf("\ttADMINISTRACION\n");
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
	printf("___________________________________\n");
	printf("| Puebla Pue. ........ $240.00    |\n");
	printf("| Xalapa Ver. ........ $540.00    |\n");
	printf("| Tlaxcala Tlax. ..... $200.00    |\n");
	printf("| Pachuca Hgo. ....... $300.00    |\n");
	printf("| Matamoros Tam. ..... $1200.00   |\n");
	printf("|_________________________________|\n");
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
