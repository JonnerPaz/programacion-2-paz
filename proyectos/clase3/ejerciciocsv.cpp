#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Producto {
    int id;
    string codigo;
    string nombre;
    string descripcion;
    int idProveedor;
    float precio;
    int stock;
    string fecharegistro;
};

int main() {

    ifstream archivo("csv_productos.csv");

    Producto* productos = new Producto[60];

    if (!archivo.is_open()) {
        cout << "NO ABRIO EL ARCHIVO";
        delete[] productos;
        return 1;
    }

    string linea;
    int i = 0;
    // Saltar primera linea
    getline(archivo, linea);

    // Leer datos
    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);
        string temp;

        getline(ss, temp, ',');

        getline(ss, productos[i].codigo, ',');

        getline(ss, productos[i].nombre, ',');

        getline(ss, productos[i].descripcion, ',');

        getline(ss, temp, ',');
        productos[i].idProveedor = stoi(temp);

        getline(ss, temp, ',');
        productos[i].precio = stof(temp);

        getline(ss, temp, ',');
        productos[i].stock = stoi(temp);

        getline(ss, productos[i].fecharegistro, ',');

        cout << "ID: " << productos[i].id << " ";
        cout << "COD: " << productos[i].codigo << " ";
        cout << "Nombre: " << productos[i].nombre << " ";
        cout << "Descripción: " << productos[i].descripcion << " ";
        cout << "ID Proveedor: " << productos[i].idProveedor << " ";
        cout << "Precio: " << productos[i].precio << " ";
        cout << "Stock" << productos[i].stock << " ";
        i++;
    };

    return 0;
}
