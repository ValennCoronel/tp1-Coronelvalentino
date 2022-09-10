#include <iostream>
#include <fstream>
using namespace std;

const int dimNom{8};
const int dimProd{5};

int buscarMayor(int vec[], int dim)
{
    for (int i = 0; i < dim; i++)
    {
        int posicion = 0;
        if (vec[i] > vec[posicion])
        {
            posicion = i;
            return posicion;
        }
    };
}

int main()
{
    /* Abrir el archivo nombres*/
    ifstream leerNombres;
    leerNombres.open("Nombres.txt");
    if (!leerNombres)
    {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    /* Declarar dimensiones y arrays */

    string nombres[dimNom]{};
    string productos[dimProd]{};

    /* Guardar nombres y productos en un array y cerrar archivo*/
    for (int i = 0; i < dimNom && leerNombres >> nombres[i]; ++i)
        ;
    for (int i = 0; i < dimProd && leerNombres >> productos[i]; ++i)
        ;
    leerNombres.close();

    /* Abrir el archivo datos*/
    ifstream leerDatos;
    leerDatos.open("Datos.txt");
    if (!leerDatos)
    {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    /* Declarar dimensiones y arrays de datos */
    double datosPeso[dimNom][dimProd];
    double datosKm[dimNom][dimProd];
    double datosCant[dimProd];
    int cantidadMay[dimNom];
    int codCliente;
    int codProducto;
    float pesoProducto;
    float kmProducto;

    /* Guardar datos en una matriz y cerrar archivo*/
    while (leerDatos >> codCliente >> codProducto >> pesoProducto >> kmProducto)
    {
        datosPeso[codCliente][codProducto] += pesoProducto;
        datosKm[codCliente][codProducto] += kmProducto;
        datosCant[codProducto]++;
    }

    leerNombres.close();

    cout << endl
         << endl
         << "======================PUNTO 1=====================" << endl
         << endl;

    /* PUNTO 1. Emita un listado donde para cada cliente liste los tipos de producto tal que la cantidad total de
    kilos transportados es mayor a 13000. */

    for (int i = 0; i < dimNom; i++)
    {
        for (int j = 0; j < dimProd; j++)
        {
            if (datosPeso[i][j] > 13000)
            {
                cantidadMay[i]++;
                cout << "El cliente: " << nombres[i] << " vendio " << datosPeso[i][j] << "KG de " << productos[j] << endl;
            }
        }
    }
    cout << endl
         << endl
         << "=======================PUNTO 2====================" << endl
         << endl;

    /* PUNTO 2. Para el cliente con mayor cantidad tipos de productos que hayan superado 13000 kg en el punto
    anterior, emita un listado con nombre de tipo de producto y total de kilómetros recorridos,
    ordenado por total de kilómetros en forma ascendente.
    Nota: No alterar el vector de nombres. */
    int prodMayor = 0;
    int posicionMayor = buscarMayor(cantidadMay, dimNom);
    int kmDim = 0;

    for (int i = 0; i < dimProd; i++)
    {
        if (datosPeso[posicionMayor][i] > 13000)
        {

            if (datosKm[posicionMayor][i] > datosKm[posicionMayor][prodMayor])
            {
                int prodMayor = i;
            }
        }
    }

    double kmTotal[dimProd]{};

    for (int i = 0; i < dimProd; i++)
    {
        kmTotal[i] = datosKm[posicionMayor][i];
    }

    // ORDENAR ARRAY

    double auxiliar{};
    string auxiliar2{};
    string prodOrdenados[dimProd]{};

    for (int i = 0; i < dimProd; i++)
    {
        prodOrdenados[i] = productos[i];
    }

    for (int i = 0; i < dimProd; i++)
    {
        for (int j = i + 1; j < dimProd; j++)
        {
            if (kmTotal[i] > kmTotal[j])
            {
                auxiliar = kmTotal[i];   // g 7 en aux
                kmTotal[i] = kmTotal[j]; // 9 3 4 9 6 0
                kmTotal[j] = auxiliar;   // 9 3 4 7 6 0

                auxiliar2 = prodOrdenados[i];
                prodOrdenados[i] = prodOrdenados[j];
                prodOrdenados[j] = auxiliar2;
            }
        }
    }

    cout << "El cliente con mas productos vendidos con mas de 13000 KG es: " << nombres[posicionMayor] << endl;
    cout << "Ventas realizadas: " << endl;

    for (int i = 0; i < dimProd; i++)
    {
            cout << prodOrdenados[i] << " : " << kmTotal[i] << endl;
    }



    cout << endl
         << endl
         << "====================PUNTO 3=======================" << endl
         << endl;
    /*PUNTO 3: Del listado anterior, tome el tipo de producto con mayor cantidad de kilómetros recorridos e
    informe cuantas entregas se hicieron para ese tipo de producto (sin importar para que cliente). */

    cout << "El rubro que mas Km recorrio fue: " << productos[prodMayor] << endl;
    cout << "Este tuvo un total de: " << datosCant[prodMayor] << " entregas realizadas" << endl;

    return 0;
}
