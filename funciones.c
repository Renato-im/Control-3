/*Sintomas del problema:
- Una empresa de venta de repuestos de vehiculos no puede llevar un correcto control de su stock ni de sus ventas.
Por lo cual busca la ayuda de un ingebiero en software para solucionar su problema.*/

/*Problema identificado> La empresa no lleva un registro actualizado de su stock, ventas y clientes*/

#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu(){
    int opc;
    printf("____________________________\nMENU\n");
    printf("Seleccione una opcion\n");
    printf("1. Inicializar stock\n");
    printf("2. Imprimir stock\n");
    printf("3. Realizar venta\n");
    printf("4. Imprimir ventas\n");
    printf("5. Salir\n");
    printf("____________________________\n");
    printf(">> ");
    scanf("%d", &opc);
    return opc;
}

void leerCadena(char *cadena, int longitud) {
    fgets(cadena, longitud, stdin);
    cadena[strcspn(cadena, "\n")] = '\0'; // Eliminar el salto de línea
}

void inicializarStock(struct stock stocks[6]){
    strcpy(stocks[0].nombre, "luces");
    stocks[0].cantidad = 100;
    stocks[0].precio = 10.50;
    strcpy(stocks[1].nombre, "baterias");
    stocks[1].cantidad = 50;
    stocks[1].precio = 75.00;
    strcpy(stocks[2].nombre, "Filtro de aceite");
    stocks[2].cantidad = 30;
    stocks[2].precio = 15.00;
    strcpy(stocks[3].nombre, "Filtro de aire");
    stocks[3].cantidad = 20;
    stocks[3].precio = 20.00;
    strcpy(stocks[4].nombre, "Parachoques");
    stocks[4].cantidad = 40;
    stocks[4].precio = 25.00;
    strcpy(stocks[5].nombre, "Neumaticos");
    stocks[5].cantidad = 10;
    stocks[5].precio = 100.00;
    gurdarProductos(stocks);
}

void gurdarProductos(struct stock stocks[6]){
    FILE *f;
    f = fopen("stock.dat", "wb+");
    fwrite(stocks, sizeof(struct stock), 6, f);
    fclose(f);
}

void imprimirStock(struct stock stocks[6]){
    printf("Stock disponible:\n");
    printf("#\tNombre\tCantidad\tPrecio\n");
    for(int i = 0; i < 6; i++){
        printf("%d.-\t%s\t%d\t%.2f\n",i, stocks[i].nombre, stocks[i].cantidad, stocks[i].precio);
    }
}

int leerStock(struct stock stocks[6]){
    FILE *f;
    f = fopen("stock.dat", "rb");
    if(f == NULL){
        printf("No existe el archivo.\n");
        return 0;
    }
    fread(stocks, sizeof(struct stock), 6, f);
    fclose(f);
    return 1;
}

// Prototipo para evitar advertencia de declaración implícita
void guardarVentas (struct venta *ventas, int numVentas);
void leerVentas (struct venta *ventas, int *numVentas);

void realizarVenta (struct stock stocks[6], struct venta ventas[6], int *numVentas) {
    struct venta nuevaVenta;
    int numProducts;
    printf("Ingrese el nombre del cliente: ");
    getchar(); // Limpiar buffer
    leerCadena(nuevaVenta.clientes.nombre, 50);
    printf("Ingrese la cedula del cliente: ");
    scanf("%d", &nuevaVenta.clientes.cedula);
    printf("Ingrese el numero de productos a vender (max 6): ");
    scanf("%d", &numProducts);
    if(numProducts > 6) {
        printf("Numero de productos excede el limite.\n");
        return;
    }

    nuevaVenta.cantidad = numProducts;
    nuevaVenta.totalVenta = 0.0;
    printf("Seleccione un producto:\n");
    imprimirStock(stocks);

    int opclist;
    for (int i = 0; i < numProducts; i++)
    {
        printf("Seleccione el numero de producto (0-5): ");
        scanf("%d", &opclist);
        if(opclist < 0 || opclist > 5) {
            printf("Producto invalido.\n");
            i--; // Repetir este ciclo
            continue;
        }
        // Copiar datos del producto seleccionado a la venta
        nuevaVenta.stocks = stocks[opclist]; // Solo guarda el último producto
        nuevaVenta.totalVenta += stocks[opclist].precio;
    }
    // Guardar la venta en el arreglo de ventas
    ventas[*numVentas] = nuevaVenta;
    (*numVentas)++;
    guardarVentas(&ventas[*numVentas-1], 1); // Guardar solo la venta recién realizada
    printf("Venta realizada con exito\n");
}

void guardarVentas (struct venta *ventas, int numVentas) {
    FILE *f;
    f = fopen("ventas.dat", "ab+");
    if(f == NULL) {
        printf("Error al abrir el archivo de ventas.\n");
        return;
    }
    fwrite(ventas, sizeof(struct venta), numVentas, f);
    fclose(f);
}

void leerVentas (struct venta *ventas, int *numVentas) {
    FILE *f;
    f = fopen("ventas.dat", "rb+");
    if(f == NULL) {
        printf("No existe el archivo de ventas.\n");
        return;
    }
    *numVentas = fread(ventas, sizeof(struct venta), 6, f);
    fclose(f);
}

void imprimirVentas(struct venta *ventas, int numVentas) {
    if(numVentas == 0) {
        printf("No hay ventas registradas.\n");
        return;
    }

    printf("Ventas realizadas:\n");
    printf("Cliente\t\tCedula\t\tProducto\t\tCantidad\t\tTotal\n");
    for(int i = 0; i < numVentas; i++) {
        printf("%s\t\t%d\t\t%s\t\t%d\t\t%.2f\n", ventas[i].clientes.nombre, ventas[i].clientes.cedula, ventas[i].stocks.nombre, ventas[i].cantidad, ventas[i].totalVenta);
    }
}
