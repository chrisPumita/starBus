#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "Empleados.h"
#include "Corridas.h"
#include "time.h"
#include "Bool.h"

#define limpiar() system("cls")
#define FILE_NAME_EMP "empleados.dat"
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
	************* APARTADO DE EMPLEADOS
 */
void leerEmpleado(FILE * arch, Empleado* reg)
{
	fread(reg,sizeof(Empleado),1,arch);
}

void grabaEmpleado(FILE* arch, Empleado* reg)
{
	fwrite(reg,sizeof(Empleado),1,arch);
}

Empleado creaEmpleado(int id, char nombre[], char user[], char password[], int status)
{
	Empleado x;
	x.id = id;
	strcpy(x.nombre, nombre);
	strcpy(x.user, user);
	strcpy(x.password, password);
	x.status=status;
	return x;
}

Empleado ingresaDatosxConsolaEMP(int indice)
{
	char nombre[30];
	char user[20];
	char password[20];

	printf("\t\tIngrese nombre del empleado: ->");
	scanf("%s",&nombre);

	printf("\t\tIngrese Usuario: ->");
	scanf("%s",&user);	

	printf("\t\tIngrese ingrese password: ->");
	scanf("%s",&password);	

	Empleado x;
	x.id = indice;
	strcpy(x.nombre, nombre);
	strcpy(x.user, user);
	strcpy(x.password, password);
	x.status = 1;
	return x;
}

void DesplegarEmpleados()
{
	if (buscaUltimoEMP() ==0)
	{
		printf("NO HAY REGISTROS AUN\n");
	}
	else{
		FILE* arch;
		Empleado a;

		//Abrimos el archivo para lectura
		arch = fopen(FILE_NAME_EMP, "r+b");
		//La primera leida la hacemos fuera del while
		printf("\t\tID\tUsername\t\Nombre\n");
		leerEmpleado(arch,&a);
		while(!feof(arch))
		{
			printf("\t\t%d ",a.id);
			printf("\t%s",a.user);
			printf("\t%s",a.nombre);
			if (a.status == 1)
				printf("\t\tACTIVO\t");
			else
				printf("\t\tINACTIVO");
			printf("\t\t\n");
			//leemos el sig registro del archivo
	//		fread(&a,sizeof(Empleado),1,arch);
			leerEmpleado(arch,&a);
		}
		fclose(arch);
	}
}


void agregaEmpleado(int indice)
{
	FILE* arch=fopen("empleados.dat","a+b");
	//Ingresa los datos por consola
	Empleado reg = ingresaDatosxConsolaEMP(indice);
	//Posicion del puntero al final del archivo .dat
	fseek(arch,0,SEEK_END);
	fwrite(&reg,sizeof(Empleado),1,arch);
	fclose(arch);
}

 void buscaEmpleadoIndex(int index)
 {
	FILE* arch=fopen(FILE_NAME_EMP,"r+b");
	int n = index;
	//Posiciono el puntero del archivo
	fseek(arch,n*sizeof(Empleado),SEEK_SET);

	//con el puntero posicionado, leo el registro
	Empleado reg;
	fread(&reg,sizeof(Empleado),1,arch);

	//muestro los datos de ese archivo
	printf("Detalles del Empleado:\n");
	printf("ID......: %d\n",reg.id);
	printf("user....: %s\n",reg.user);
	printf("NOMBRE:.: %s\n",reg.nombre);
	printf("STOCK:..: %d\n",reg.status);
	printf("\n");
	fclose(arch);
 }

  int buscaEmpleadoUser(char code[])
 {
	FILE* arch=fopen(FILE_NAME_EMP,"r+b");
	Empleado aux;
	int index = 0;
	// ->>>> BUSCANDO DATO
	// fread(reg,sizeof(Empleado),1,arch);
	while(fread(&aux, sizeof(aux),1,arch)!=0 && strcmp(aux.user,code)!=0)
	{
		index++;
	}
	//printf("altumo %d index%d\n",buscaUltimoEMP(), index );
	//clear();
	fclose(arch);
	if(buscaUltimoEMP()<=index)
		return 0;
	else
	return index;
	// ->> END
 }

 int buscaUltimoEMP(){
 	FILE* arch;
	Empleado a;
	int i;
	//Abrimos el archivo para lectura
	arch = fopen(FILE_NAME_EMP, "r+b");
	leerEmpleado(arch,&a);
	while(!feof(arch)){
		i = a.id;
		//leemos el sig registro del archivo
		leerEmpleado(arch,&a);
	}
	fclose(arch);
	if (i<0)
	{
		i = 0;
	}
	//i++;
	return i;
 }

/*
	************* APARTADO DE CORRIDAS
 */
void leerCorrida(FILE * arch, Corrida* reg)
{
	fread(reg,sizeof(Corrida),1,arch);
}

void grabaCorrida(FILE* arch, Corrida* reg)
{
	fwrite(reg,sizeof(Corrida),1,arch);
}

Corrida creaCorrida(int id, char cdDes[], char edoDes[], int Aocu, int Adis, float costo, int horaS, int minS)
{
	Corrida x;
	x.id = id;
	strcpy(x.cdDes, cdDes);
	strcpy(x.edoDes, edoDes);
	x.Aocu=Aocu;
	x.Adis=Adis;
//	x.asientos=asientos;
	x.costo=costo;
	x.horaS=horaS;
	x.minS=minS;
	return x;
}

Corrida ingresaDatosxConsolaCOR(int indice)
{
 	char cdDes[20];
 	char edoDes[20];
 	int Aocu = 0;
 	int Adis;
 	int asientos;
 	float costo;
 	int horaS;
 	int minS;

	printf("\t\tIngrese Ciudad Destino de la Corrida: ->");
	scanf("%s",&cdDes);

	printf("\t\tIngrese Estado de la Corrida: ->");
	scanf("%s",&edoDes);	

	printf("\t\tIngrese Costo: ->");
	scanf("%f",&costo);	

	printf("\t\tIngrese Hora de Salida [HH]: ->");
	scanf("%d",&horaS);	

	printf("\t\tIngrese Minutos de Salida [MM]: ->");
	scanf("%d",&minS);	

	printf("\t\tCuantos asientos tiene este Autobus: ->");
	scanf("%d",&asientos);	

	Corrida x;
	x.id = indice;
	strcpy(x.cdDes, cdDes);
	strcpy(x.edoDes, edoDes);
	x.Aocu = 0;
	x.Adis = asientos;
	x.asientos = asientos;
	x.costo = costo;
	x.horaS = horaS;
	x.minS = minS;
	int i;
	for (i = 0; i < asientos; i++)
		x.asignacion[i]=0;
	return x;
}

void DesplegarCorridas()
{
	if (buscaUltimoCOR() ==0)
	{
		printf("NO HAY REGISTROS AUN\n");
	}
	else{
		FILE* arch;
		Corrida a;

		//Abrimos el archivo para lectura
		arch = fopen("corrida.dat", "r+b");
		//La primera leida la hacemos fuera del while
		printf("\t\tID\tDestino\t\tDisp\tPrecio\tSalida\n");
		leerCorrida(arch,&a);
		while(!feof(arch))
		{
			printf("\t\t%d ",a.id);
			printf("\t%s",a.cdDes);
			printf(", %s",a.edoDes);
			printf("\t%d",a.Adis);
			printf("/%d",a.Aocu);
			printf("\t$%.2f",a.costo);
			printf("\t%d:%d",a.horaS,a.minS);
			printf("\t\t\n");
			//leemos el sig registro del archivo
	//		fread(&a,sizeof(Corrida),1,arch);
			leerCorrida(arch,&a);
		}
		fclose(arch);
	}
}


void agregaCorrida(int indice)
{
	FILE* arch=fopen("corrida.dat","a+b");
	//Ingresa los datos por consola
	Corrida reg = ingresaDatosxConsolaCOR(indice);
	//Posicion del puntero al final del archivo .dat
	fseek(arch,0,SEEK_END);
	fwrite(&reg,sizeof(Corrida),1,arch);
	fclose(arch);
}

 void buscaCorridaIndex(int index)
 {
	FILE* arch=fopen("corrida.dat","r+b");
	int n = index-1;
	//Posiciono el puntero del archivo
	fseek(arch,n*sizeof(Corrida),SEEK_SET);

	//con el puntero posicionado, leo el registro
	Corrida reg;
	fread(&reg,sizeof(Corrida),1,arch);

	//muestro los datos de ese archivo
	printf("\t\tD E T A L L E S :\n");
	printf("\t\t\tID: %d ",reg.id);
	printf("Destino: %s, ",reg.cdDes);
	printf("%s \n",reg.edoDes);
	printf("\t\t\tDISPONIBILIDAD: %d/",reg.Adis);
	printf("%d ",reg.Aocu);
	printf("PRECIO: $%.2f ",reg.costo);
	printf(" SALIDA: %d:%d\n",reg.horaS,reg.minS);
	printf("\n");

	int i,j,val, cont = 1;

 	printf("\t\E[37;41;5m[XX]\E[00m -> OCUPADO  \E[37;42;5m[00]\E[00m -> DISPONIBLE\n");
	printf("\t\t\t\t____________________________________\n");
	printf("\t\t\t\t|  |(O)|                           |\n");	
	printf("\t\t\t\t|                                  |\n");	
	for (i = 0; i < reg.asientos; i=i+4){
			printf("\t\t\t\t|");
		for (j = 0; j < 4; j++)
		{
			if (reg.asignacion[cont-1] == 0) //LIBRE
				if (cont<10)
					printf("  \E[37;42;5m[0%d]\E[00m  ",cont);
				else
					printf("  \E[37;42;5m[%d]\E[00m  ",cont);
			else
				if (cont<=reg.asientos) //OCUPADO
					printf("  \E[37;41;5m[XX]\E[00m  ");
			cont ++;
		}
		printf("  |\n");
	}
	printf("\t\t\t\t|                                  |\n");
	printf("\t\t\t\t| [  W C  ]              [  W C  ] |\n");
	printf("\t\t\t\t|__________________________________|\n");

//	for (i = 0; i < reg.asientos; i++)
//		printf("%d-%d, ",i,reg.asignacion[i]);
	fclose(arch);
 }

  int buscaCorrida(int idBusqueda)
 {
	FILE* arch=fopen("corrida.dat","r+b");
	Corrida aux;
	int index = 0;
	// ->>>> BUSCANDO DATO
	// fread(reg,sizeof(Empleado),1,arch);
	while(fread(&aux, sizeof(aux),1,arch)!=0 && aux.id,idBusqueda!=0)
	{
		index++;
	}
	//printf("altumo %d index%d\n",buscaUltimoEMP(), index );
	//clear();
	fclose(arch);
	if(buscaUltimoCOR()<=index)
		return 0;
	else
		return index;
	// ->> END
 }

   int buscaAsiento(int idCorrida, int idAsiento)
 {
 	FILE* arch=fopen("corrida.dat","r+b");
	int n = idCorrida-1;
	//Posiciono el puntero del archivo
	fseek(arch,n*sizeof(Corrida),SEEK_SET);

	//con el puntero posicionado, leo el registro
	Corrida reg;
	fread(&reg,sizeof(Corrida),1,arch);

	if (reg.asignacion[idAsiento-1] == 1) //OCUPADO
		return 0;
	else
		return 1;
	fclose(arch);
 }

 int buscaUltimoCOR(){
 	FILE* arch;
	Corrida a;
	int i;
	//Abrimos el archivo para lectura
	arch = fopen("corrida.dat", "r+b");
	leerCorrida(arch,&a);
	while(!feof(arch)){
		i = a.id;
		//leemos el sig registro del archivo
		leerCorrida(arch,&a);
	}
	fclose(arch);
	if (i<0)
	{
		i = 0;
	}
	//i++;
	return i;
 }

 void updateBus(int index, int lugar){
	FILE* fp =fopen("corrida.dat","r+b");
	int n = index-1;
	Corrida reg;
	reg.asignacion[lugar-1] = 1;
	
	//Posicion del indentificaro de posicion
	fseek(fp,n*sizeof(Corrida),SEEK_SET);

	//Grabo el registro reescribiendo
	fwrite(&reg.asignacion,sizeof(Corrida),1,fp);
	fclose(fp); 	
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
		case 3:
			printf("\n");
			printf("\t\t\t(B I E N V E N I D O S ) \n\t\t ( M E N U  )  ( V E N T A ) \n");
		case 4:
			printf("\n");
			printf("\t\t\t(B I E N V E N I D O S ) \n\t\t ( M E N U  )  ( A D M I N I S T R A C I O N ) \n");
		break;
		case 5:
			printf("\n");
			printf("\t\t\t(B I E N V E N I D O S ) \n\t\t ( M E N U  )  ( C O N S U L T A ) \n");
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
			printf("\t+------------------------------------------------------------------------------------------+\n");
			printf("\t| SELECIONE DESTINO -> ELIJA ASIENTO -> VERIFICAR IFORMACION -> CONFIRMA VENTA | SALIR (0) |\n");
			printf("\t+------------------------------------------------------------------------------------------+\n");
		break;
		case 3:
			printf("\t+-----------------------+------------------+----------------------+-------------------+-----------+\n");
			printf("\t| AGREGAR CORRIDAS  [1] | VER CORRIDAS [2] | AGREGAR EMPLEADO [3] | VER EMPLEADOS [4] | SALIR [0] |\n");
			printf("\t+-----------------------+------------------+----------------------+-------------------+-----------+\n");
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
	printf("\n\t\tUSER: %s\n\t\tFECHA: ",nomreUser);
	fechaHora();
	printf("\tTERMINAL: %s\n\n",terminal);
}

void menuPrincipal(){
	int opc;
	do{
	muestraInfo();
	muestraTituloMenu(2);
	muestraMenu(1);
	printf("\n\t\tEIJA UNA OPCION: ");
	scanf("%i",&opc);
		switch(opc){
			case 1:
				muestraInfo();
				muestraTituloMenu(5);
				muestraMenu(1);

				//muestraDestinos();
				DesplegarCorridas();
				printf("\t\tPARA VER ASIENTOS ESCRIBA EL ID DE LA CORRIDA\t\tEscriba 0 para salir\n\t\t\tID->");
				scanf("%d",&opc);
				if (opc!=0)
				{
					muestraBus(opc);
				}
				system("pause");
				opc = 99;
			break;
			case 2:
				muestraInfo();
				muestraTituloMenu(3);
				muestraMenu(2);
				//muestraDestinos();
				DesplegarCorridas();
				printf("\t\tSELECCIONE DESTINO:  ");
				scanf("%i",&opc);
				muestraInfo();
				muestraMenu(2);
				int bus = muestraBus(opc);
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
					//updateBus(bus,asiento); AUN NO DISPONIBLE
					printf("\t\tAUTOBUSES STARBUS SA DE CV\n");
					FILE* arch=fopen("corrida.dat","r+b");
					int n = bus-1;
					//Posiciono el puntero del archivo
					fseek(arch,n*sizeof(Corrida),SEEK_SET);

					//con el puntero posicionado, leo el registro
					Corrida reg;
					fread(&reg,sizeof(Corrida),1,arch);

					//muestro los datos de ese archivo
					printf("\t\tD E T A L L E S :\n");
					printf("\tPasajero: %s \n",nombreUser);
					printf("\t\t\tID: %d ",reg.id);
					printf("\tDestino: %s, ",reg.cdDes);
					printf("%s \n",reg.edoDes);
					printf("\tPRECIO: $%.2f ",reg.costo);
					printf("\tSALIDA: %d:%d\n",reg.horaS,reg.minS);
					printf("\tAsiento: %d \n",asiento);
					printf("\n");
					fclose(arch);

					system("pause");
				}
				opc = 99;
			break;
			case 3:
				muestraInfo();
				muestraTituloMenu(4);
				muestraMenu(3);
				printf("\t\tElija una opcion ");
				scanf("%d",&opc);
				while(opc!=0){
					if (opc == 1)
					{
						/* Selijio agregar destino AUN NO DISPONIBLE*/
						//DesplegarCorridas();
						printf("\t\tAgregando nuevo destino...\n");
						agregaCorrida(buscaUltimoCOR()+1);
						//agregaCorrida(1);
						printf("Se ha Agregado una corrida\n");
						system("pause");
					}
					else if (opc == 2)
					{
						/*Desplegando un todos los destinos*/
						DesplegarCorridas();
						system("pause");
					}
					else if (opc == 3)
					{
						/* Eligio agregar usuarios */
						DesplegarEmpleados();
						printf("\t\tAgregando nuevo empleado...\n");
						agregaEmpleado(buscaUltimoEMP()+1);
						printf("Se ha Agregado un usuario\n");
						system("pause");
					}
					else if (opc == 4)
					{
						DesplegarEmpleados();
						system("pause");
					}

					limpiar();
					muestraInfo();
					muestraMenu(3);
					printf("\t\tElija una opcion ");
					scanf("%d",&opc);
				}
				opc = 99;
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


int muestraBus(int id){
	//id es el numero del corrida
	int ultimo = buscaUltimoCOR()-1;
	if (ultimo <=id-1){
		while(ultimo<id-1){
			//El ciclo se produce cuando se esta ingresando un ID no valido
			muestraInfo();
			muestraMenu(2);
			DesplegarCorridas();
			printf("\nEl id No es valido, escrbiba otro ->");
			scanf("%d",&id-1);
		}
	}
	//Hasta aqui ya tebemos ID valido
	buscaCorridaIndex(id); //Mostramos info de la corrida
	return id;
}

int verificaAsiento(int id, int asiento){
	//iniciamos el llenado del array de asientos del ID de corrida
	int  isFree = buscaAsiento(id, asiento);
	//llenado de asientos
	while (isFree == 0){ //MIentras el asiento este ocupado
		printf("\n\t\t \E[37;41;5mAsiento ocupado\E[00m elija otro: ");
		scanf("%d",&asiento);
		isFree = buscaAsiento(id, asiento);
	}
	return asiento;
}


#if 0
int main()
{
nuevaVenta();
	return 0;
	
}
#endif
