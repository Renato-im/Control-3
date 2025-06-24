struct cliente{
    char nombre[50];
    int cedula;
};

struct stock{
    char nombre[50];
    int cantidad;
    float precio;
};

struct venta{
    struct cliente clientes;
    struct stock stocks;
    int cantidad;
    float totalVenta;
};

int menu();
void inicializarStock(struct stock stocks[6]);
void gurdarProductos(struct stock stocks[6]);
void imprimirStock(struct stock stocks[6]);
int leerStock(struct stock stocks[6]);
void realizarVenta(struct stock stocks[6], struct venta ventas[6], int *numVentas);
void imprimirVentas(struct venta ventas[6], int numVentas);
void leerCadena(char *cadena, int longitud);
void leerVenta(struct venta *venta);
void leerVentas(struct venta *ventas, int *numVentas);
