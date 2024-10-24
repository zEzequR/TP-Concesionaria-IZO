#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define MAX_ANIOS 100
#define MAX_PRECIOS 100
#define MAX_NOMBRE 50

float dolar;
float opc1(char *modelo, FILE *fileAnio);
void mostrarPrecios(); 
float menupago(float precio); 
void menuprinc();
float obtenerPrecio(char *modelo);

void menuprinc() {
    int opcion, i;
    FILE *fileAnios = NULL;
    FILE *fileAnios2 = NULL;
    FILE *fileAnios3 = NULL;
    FILE *fileAnios4 = NULL;
    FILE *fileAnios5 = NULL;
    FILE *fileAnios6 = NULL;
    time_t now;
    time(&now);
    printf("-----------------------------------");
    printf("\n CONCESIONARIA ZONA OESTE \n");
    printf("FECHA: %s", ctime(&now));
    printf("\n-----------------------------------");
    do {
    	mostrarPrecios();
    	printf("\n Modelos disponibles de pickups: ");
        printf("\n 1-FORD MAVERICK\n 2-TOYOTA HILUX\n 3-TOYOTA SW4\n 4-NISSAN FRONTIER\n 5-MERCEDES-BENZ XCLASS\n 6-VOLKSWAGEN AMAROK\n 0-Salir\n");
        printf("-----------------------------------\n");
        printf("Por favor, elija una opcion [0-6]: ");
        scanf("%i", &opcion);
        FILE *fileAnios = fopen("anios.txt", "r");
    	FILE *fileAnios2 = fopen("anios2.txt", "r");
    	FILE *fileAnios3 = fopen("anios3.txt", "r");
    	FILE *fileAnios4 = fopen("anios4.txt", "r");
    	FILE *fileAnios5 = fopen("anios4.txt", "r");
    	FILE *fileAnios6 = fopen("anios4.txt", "r");
        switch (opcion) {
        case 0:
            system("cls");
            for (i = 0; i < 10; i++) { 
                printf("Cerrando programa...");
                Sleep(250);
                system("cls");
                Sleep(250); 
            }
            printf("-----------------------------------\n");
            printf("Programa cerrado, presiona una tecla para continuar");
            system("exit");
            break;
        case 1:
            system("cls");
            opc1("FORD MAVERICK", fileAnios);
            fclose(fileAnios);
            break;
        case 2:
            system("cls");
            opc1("TOYOTA HILUX", fileAnios2);
            fclose(fileAnios2);
            break;
        case 3:
            system("cls");
            opc1("TOYOTA SW4", fileAnios3);
            fclose(fileAnios);
            break;
        case 4:
            system("cls");
            opc1("NISSAN FRONTIER", fileAnios4);
            fclose(fileAnios4);
            break;
        case 5:
            system("cls");
            opc1("MERCEDES-BENZ XCLASS", fileAnios5);
            fclose(fileAnios5);
            break;
        case 6:
            system("cls");
            opc1("VOLKSWAGEN AMAROK", fileAnios6);
            fclose(fileAnios6);
            break;
        default:
            printf("No valido, Ingrese nuevamente.\n");
            break;
        }
    } while (opcion != 0);
}

void mostrarPrecios() {
    char modelo[MAX_NOMBRE];
    float precio;
    FILE *filePrecios = fopen("precios.txt", "r");
    printf("\nLista de precios:\n");
    printf("-----------------------------------\n");
    printf("Modelo                      Precio\n");
    printf("-----------------------------------\n");

    while (fscanf(filePrecios, "%[^,], %f\n", modelo, &precio) == 2) {
        printf("%-25s $%.2f\n", modelo, precio);
    }
    printf("-----------------------------------\n");
    fclose(filePrecios);
}

float obtenerPrecio(char *modelo) {
    char nombreModelo[MAX_NOMBRE];
    float precio;
    FILE *filePrecios = fopen("precios.txt", "r");
    
    if (filePrecios == NULL) {
        printf("Error al abrir el archivo de precios.\n");
        return 0;
    }

    while (fscanf(filePrecios, "%[^,], %f\n", nombreModelo, &precio) == 2) {
        if (strcmp(nombreModelo, modelo) == 0) {
            fclose(filePrecios);
            return precio; 
        }
    }
    
    fclose(filePrecios);
    printf("Modelo no encontrado: %s\n", modelo);
    return 0; 
}

float opc1(char *modelo,  FILE *fileAnio) {
    int color, anio, anios[MAX_ANIOS], num_anios = 0;
    float precio = obtenerPrecio(modelo);
    
    if (precio == 0) return 0; 

    FILE *fileVentas = fopen("ventas.txt", "a");

    while (fscanf(fileAnio, "%d", &anios[num_anios]) != EOF && num_anios < MAX_ANIOS) {
        num_anios++;
    }
    
    printf("Colores disponibles del Pickup: ");
    do {
        printf("\n 1-ROJO\n 2-BLANCO\n 3-AZUL\n 4-NEGRO\n");
        printf("Elija el color de su preferencia: ");
        scanf("%i", &color);
        switch (color) {
            case 1:
                fprintf(fileVentas, "Modelo: %s, Color: ROJO\n", modelo);
                break;
            case 2:
                fprintf(fileVentas, "Modelo: %s, Color: BLANCO\n", modelo);
                break;
            case 3:
                fprintf(fileVentas, "Modelo: %s, Color: AZUL\n", modelo);
                break;
            case 4:
                fprintf(fileVentas, "Modelo: %s, Color: NEGRO\n", modelo);
                break;
            default:
            	printf("-----------------------------------\n");
                printf("No valido, Ingrese nuevamente.\n");
                continue; 
        }
        
        system("cls");
        
        printf("Seleccione el año del modelo:\n");
        for (int i = 0; i < num_anios; i++) {
            printf("%i. %d\n", i + 1, anios[i]);
        }
        
        int anioSeleccionado;
        printf("Ingrese el numero del anio que desea: ");
        scanf("%d", &anioSeleccionado);
        
        while (anioSeleccionado < 1 || anioSeleccionado > num_anios) {
        	printf("-----------------------------------\n");
        	for (int i = 0; i < num_anios; i++) {
            printf("%i. %d\n", i + 1, anios[i]);
        	}
            printf("Anio no valido. Ingrese una opcion correcta: ");
            scanf("%d", &anioSeleccionado);
        }
        anio = anios[anioSeleccionado - 1];
        fprintf(fileVentas, "Anio: %d\n", anio);
    } while (color > 4 || color < 1);


	float precioFinal = menupago(precio);
    fprintf(fileVentas, "Pago por %s: %.2f\n", (precioFinal == precio * 0.90 ? "Efectivo" : "Transferencia"), precioFinal);
    fprintf(fileVentas, "\n");


    fclose(fileVentas);
    return precio;
}
   
float menupago(float precio) {
    int opcion;
    system("cls");
    FILE *fileVentas = fopen("ventas.txt", "a");
    printf("Metodos de pagos disponibles:");
    do {
        printf("\n1.Efectivo\n2.Transferencia\n");
        printf("Ingrese el metodo de pago a realizar: ");
        scanf("%i", &opcion);
        if (opcion < 1 || opcion > 2) {
        	printf("-----------------------------------\n");
            printf("Ingrese una opcion correcta: ");
        }
    } while (opcion < 1 || opcion > 2);

    float precioFinal = precio;

    switch (opcion) {
        case 1: 
            precioFinal *= 0.90;
            break;
        case 2:
            precioFinal *= 1.05;
            break;
    }
    
    system("cls");
    
	printf("-----------------------------------\n");
    printf("Precio final despues de aplicar el metodo de pago:\nEn USD: $%.2f\nEn ARS: $%.2f\n", precioFinal,precioFinal*dolar);
    return precioFinal;
}

int main() {
    FILE *DOLAR = fopen("DOLAR.txt", "r");
    if (DOLAR == NULL) {
        printf("Error al abrir el archivo DOLAR.txt.\n");
        return 1;
    }
    fscanf(DOLAR, "%f", &dolar);
    fclose(DOLAR);
    menuprinc();
    return 0;
}

