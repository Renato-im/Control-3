#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    int opc;
    struct stock stocks[6];
    struct venta ventas[100]; // Aumenta el tamaño para más ventas
    int numVentas = 0;
    int numStocks = 6;

    leerVentas(ventas, &numVentas); // Cargar ventas previas al iniciar
    leerStock(stocks); // Cargar stock previo al iniciar

    do{
        opc = menu();
        switch (opc)
        {
        case 1:
            inicializarStock(stocks);
            break;
        case 2:
            if(leerStock(stocks) == 0){
                printf("No hay productos disponobles");
            }else{
                imprimirStock(stocks);
            }
            break;
        case 3:
            realizarVenta(stocks, ventas, &numVentas);
            break;
        case 4:
            if(numVentas == 0){
                printf("No hay ventas registradas.\n");
            } else {
                imprimirVentas(ventas, numVentas);
            }
            break;
        default:
            break;
        }
    }while(opc != 5);

    // Guardar todas las ventas al salir
    FILE *f = fopen("ventas.dat", "wb");
    if(f != NULL) {
        fwrite(ventas, sizeof(struct venta), numVentas, f);
        fclose(f);
    }
    gurdarProductos(stocks); // Guardar el stock actualizado al salir

    return 0;
}
