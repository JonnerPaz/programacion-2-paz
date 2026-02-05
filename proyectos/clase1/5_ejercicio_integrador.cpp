#include <iomanip>
#include <iostream>
#include <locale>
using namespace std;

bool isArrayNull(int* arr) {
    return arr == nullptr;
}

// Función para crear un arreglo dinámico
int* crearArreglo(int size) {
    if (size <= 0) {
        cout << "El tamaño debe ser positivo." << endl;
        return nullptr;
    }

    int* dynamic_arr = new int[size];
    if (dynamic_arr == nullptr) {
        cout << "No se pudo crear el arreglo dinamico." << endl;
        return nullptr;
    }
    return dynamic_arr;
}

// Función para llenar el arreglo con valores del usuario
void llenarArreglo(int* arreglo, int tamanio) {
    if (isArrayNull(arreglo)) {
        cout << "El arreglo debe estar creado." << endl;
        return;
    }

    for (int i = 0; i < tamanio; i++) {
        cout << "Ingrese el elemento " << i + 1 << ": ";
        cin >> arreglo[i];
    }
}

// Función para mostrar todos los elementos del arreglo
void mostrarArreglo(int* arreglo, int tamanio) {
    if (isArrayNull(arreglo)) {
        cout << "El arreglo debe estar creado." << endl;
        return;
    }

    if (tamanio <= 0) {
        cout << "El arreglo esta vacio." << endl;
        return;
    }

    cout << "Contenido del arreglo Arreglo (orden declarado): ";
    for (int i = 0; i < tamanio; i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

// Función para encontrar el número mayor
int encontrarMayor(int* arreglo, int tamanio) {
    if (isArrayNull(arreglo)) {
        cout << "El arreglo debe estar creado." << endl;
        return 0;
    }

    if (tamanio <= 0) {
        cout << "El arreglo esta vacio." << endl;
        return 0;
    }

    int mayor = arreglo[0];
    for (int i = 1; i < tamanio; i++) {
        if (arreglo[i] > mayor) {
            mayor = arreglo[i];
        }
    }

    return mayor;
}

// Función para calcular el promedio
float calcularPromedio(int* arreglo, int tamanio) {
    if (isArrayNull(arreglo)) {
        cout << "El arreglo debe estar creado." << endl;
        return 0.0f;
    }

    if (tamanio <= 0) {
        cout << "El arreglo esta vacio." << endl;
        return 0.0f;
    }

    int sum = 0;
    for (int i = 0; i < tamanio; i++) {
        sum += arreglo[i];
    }

    float promedio = static_cast<float>(sum) / static_cast<float>(tamanio);
    return promedio;
}

// Función para liberar la memoria del arreglo
void liberarArreglo(int*& arreglo) {
    if (!isArrayNull(arreglo)) {
        // deletes the array
        // using delete without [] would delete only the first element
        delete[] arreglo;
        arreglo = nullptr;
        return;
    }
    cout << "Error al liberar el arreglo." << endl;
    cout << "No fue posible liberar ese espacio de memoria." << endl;
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n=== GESTIÓN DE ARREGLOS DINÁMICOS ===" << endl;
    cout << "1. Crear y llenar arreglo" << endl;
    cout << "2. Mostrar arreglo" << endl;
    cout << "3. Encontrar número mayor" << endl;
    cout << "4. Calcular promedio" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main() {
    setlocale(LC_ALL, "spanish");

    // Variables principales
    int* arreglo = nullptr;
    int tamanio = 0;

    cout << "=== GESTIÓN DE ARREGLOS DINÁMICOS ===" << endl;
    cout << "Implemente las funciones marcadas con TODO para completar el ejercicio." << endl;

    int opcion;
    while (opcion != 5) {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
        case 1:
            // Crear y llenar arreglo
            cout << "Ingrese el tamaño del arreglo: ";
            cin >> tamanio;

            arreglo = crearArreglo(tamanio);
            if (isArrayNull(arreglo)) {
                cout << "Error al crear el arreglo." << endl;
                continue;
            }

            llenarArreglo(arreglo, tamanio);
            cout << "Arreglo creado y llenado correctamente." << endl;
            break;

        case 2:
            // Mostrar arreglo
            if (isArrayNull(arreglo) || tamanio <= 0) {
                cout << "No hay arreglo creado. Use la opcion 1 primero." << endl;
                continue;
            }

            mostrarArreglo(arreglo, tamanio);
            break;

        case 3:
            // Encontrar número mayor
            if (isArrayNull(arreglo) || tamanio <= 0) {
                cout << "No hay arreglo creado o está vacío. Use la opcion 1 primero." << endl;
                continue;
            }
            cout << "El número mayor es: " << encontrarMayor(arreglo, tamanio) << endl;
            break;

        case 4:
            // Calcular promedio
            if (isArrayNull(arreglo) || tamanio <= 0) {
                cout << "No hay arreglo creado o está vacío. Use la opcion 1 primero." << endl;
                continue;
                // leaving else here to avoid compiler from complaining
            } else {
                float promedio = calcularPromedio(arreglo, tamanio);
                // std::fixed tells the output to always show decimal places
                // std::setprecision sets the number of decimal places, in this case 2
                cout << "El promedio es: " << fixed << setprecision(2) << promedio << endl;
            }
            break;

        case 5:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }
    }

    // Liberar memoria antes de salir
    liberarArreglo(arreglo);

    cout << "Programa finalizado. Memoria liberada." << endl;
    return 0;
}
