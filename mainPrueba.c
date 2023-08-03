
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

struct MiEstructura {
    char nombre[50];      
    struct tm* fecha_actual; 
    struct tm* fecha_futura;      
};




void sumarDias(struct tm* fecha, int dias) {
    time_t tiempo = mktime(fecha); 
    tiempo += (dias * 86400);      
    *fecha = *localtime(&tiempo); 
}

void asignarFecha(){
        time_t t_actual = time(NULL);
    struct MiEstructura miObjeto;
    miObjeto.fecha_actual = localtime(&t_actual);
    
    miObjeto.fecha_futura = (struct tm*)malloc(sizeof(struct tm));
    memcpy(miObjeto.fecha_futura, miObjeto.fecha_actual, sizeof(struct tm));
    sumarDias(miObjeto.fecha_futura, 3);
   
     printf("\n FECHA ACTUAL: %i/%i/%i   FECHA FIN: %i/%i/%i\n", miObjeto.fecha_actual->tm_mday, miObjeto.fecha_actual->tm_mon + 1, miObjeto.fecha_actual->tm_year + 1900,  miObjeto.fecha_futura->tm_mday, miObjeto.fecha_futura->tm_mon + 1, miObjeto.fecha_futura->tm_year + 1900);
    free(miObjeto.fecha_futura);
}
int main(){
    asignarFecha();

    return 0;
}



// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>
// #include <locale.h>

// struct MiEstructura {
//     char nombre[50];      
//     struct tm fecha_actual; 
//     struct tm fecha_futura;      
// };

// void sumarDias(struct tm* fecha, int dias) {
//     time_t tiempo = mktime(fecha); 
//     tiempo += (dias * 86400);      
//     *fecha = *localtime(&tiempo); 
// }

// void asignarFecha() {
//     time_t t_actual = time(NULL);
//     struct MiEstructura miObjeto;
    
//     miObjeto.fecha_actual = *localtime(&t_actual);
//     miObjeto.fecha_futura = miObjeto.fecha_actual; // Copiar la fecha actual como punto de partida

//     sumarDias(&miObjeto.fecha_futura, 3); // Sumar 3 días a la fecha futura

//     printf("\n FECHA ACTUAL: %i/%i/%i   FECHA FIN: %i/%i/%i\n", 
//            miObjeto.fecha_actual.tm_mday, miObjeto.fecha_actual.tm_mon + 1, miObjeto.fecha_actual.tm_year + 1900, 
//            miObjeto.fecha_futura.tm_mday, miObjeto.fecha_futura.tm_mon + 1, miObjeto.fecha_futura.tm_year + 1900);
// }

// int main() {
//     asignarFecha();
//     return 0;
// }



// #include <stdio.h>
// #include <stdlib.h>

// typedef struct {
//     int codigo;
//     char nombre[50];
//     float costo;
//     float precio;
// } Producto;

// int main() {
//     int tamanoInicial = 5; // Tamaño inicial del array de productos
//     int numeroProductos = 0; // Contador de productos ingresados
//     Producto* productos = (Producto*)malloc(tamanoInicial * sizeof(Producto));

//     if (productos == NULL) {
//         printf("No se pudo asignar memoria para el array de productos.\n");
//         return 1;
//     }

//     while (1) {
//         printf("Ingrese el codigo del producto (o -1 para terminar): ");
//         int codigo;
//         scanf("%d", &codigo);

//         if (codigo == -1) {
//             break; // Salir del bucle si el usuario ingresa -1
//         }

//         // Verificar si el array de productos está lleno y redimensionarlo si es necesario
//         if (numeroProductos == tamanoInicial) {
//             tamanoInicial *= 2; // Duplicar el tamaño actual
//             Producto* nuevosProductos = (Producto*)realloc(productos, tamanoInicial * sizeof(Producto));

//             if (nuevosProductos == NULL) {
//                 printf("No se pudo redimensionar el array de productos.\n");
//                 break;
//             }

//             productos = nuevosProductos;
//         }
//         productos[numeroProductos].codigo = codigo;
//         numeroProductos++;
        
//     }

//     // Imprimir los datos de los productos almacenados en el array.
//     printf("\nDatos de los productos:\n");
//     for (int i = 0; i < numeroProductos; i++) {
//         printf("Producto %d: Codigo: %d\n", i + 1, productos[i].codigo);
//         // Aquí también puedes imprimir los demás campos del producto.
//     }

//     // Liberar la memoria asignada para el array antes de terminar el programa.
//     free(productos);

//     return 0;
// }
