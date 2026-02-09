#include <concepts>
#include <format>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

struct Materia {
    int codigo;
    char nombre[40];
    int creditos;
};

struct Estudiante {
    int id;
    char nombre[40];
    float promedio;
    int codigoMateriaPrincipal;
};

struct Escuela {
    Estudiante* estudiantes;
    int cantidadEstudiantes;
    Materia* materias;
    int cantidadMaterias;
};

template <typename T> bool isArrayNull(T* arr) {
    return arr == nullptr;
}

// validation logic for struct properties
template <typename T>
concept Number = std::same_as<T, int> || std::same_as<T, float>;

template <Number T> struct Property {
    T& assignProp;
    string message;
    string errorMessage;
};

template <Number T> void assignProperty(Property<T> property) {
    while (true) {
        cout << property.message;
        cin >> property.assignProp;
        if (cin.fail()) {
            cout << property.errorMessage << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }
}

// Crea la escuela con arreglos dinamicos
void crearEscuela(Escuela& escuela, int cantEst, int cantMat) {
    if (cantEst <= 0 || cantMat <= 0) {
        cout << "La cantidad de estudiantes y materias debe ser mayor a 0." << endl;
        return;
    }

    escuela.estudiantes = new Estudiante[cantEst];
    escuela.materias = new Materia[cantMat];
    escuela.cantidadEstudiantes = cantEst;
    escuela.cantidadMaterias = cantMat;
}

// Llena la lista de estudiantes
void llenarEstudiantes(Escuela& escuela) {
    if (isArrayNull(escuela.estudiantes)) {
        cout << "Error: Puntero nulo" << endl;
        return;
    }

    for (int i = 0; i < escuela.cantidadEstudiantes; i++) {
        assignProperty<int>({.assignProp = escuela.estudiantes[i].id,
                             .message = std::format("Ingresa el id del estudiante #{}: ", i + 1),
                             .errorMessage = "Error: id invalido"});

        cout << std::format("Ingresa el NOMBRE del estudiante #{}: ", i + 1);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(escuela.estudiantes[i].nombre, 40);

        assignProperty<float>(
            {.assignProp = escuela.estudiantes[i].promedio,
             .message = std::format("Ingresa el promedio del estudiante #{}: ", i + 1),
             .errorMessage = "Error: promedio invalido"});

        assignProperty<int>({
            .assignProp = escuela.estudiantes[i].codigoMateriaPrincipal,
            .message = std::format("Ingresa el codigo de la materia principal del estudiante #{}: ",
                                   i + 1),
            .errorMessage = "Error: codigo de materia principal invalido",

        });
    }
}

// Llena la lista de materias
void llenarMaterias(Escuela& escuela) {
    if (isArrayNull(escuela.materias)) {
        cout << "Error: puntero nulo" << endl;
    }

    for (int i = 0; i < escuela.cantidadMaterias; i++) {
        assignProperty<int>(
            {.assignProp = escuela.materias[i].codigo,
             .message = std::format("Ingresa el codigo de la materia #{}: ", i + 1),
             .errorMessage = "Error al ingresar el codigo de la materia: código inválido"});

        cout << std::format("Ingresa el NOMBRE de la materia #{}: ", i + 1);
        cin >> escuela.materias[i].nombre;

        assignProperty<int>(
            {.assignProp = escuela.materias[i].creditos,
             .message =
                 std::format("Ingresa la cantidad de horas crédito de la materia #{}: ", i + 1),
             .errorMessage = "Error al ingresar la cantidad de horas crédito de la materia: "
                             "horas crédito inválidas"});
    }
}

// Muestra la escuela completa
void mostrarEscuela(const Escuela& escuela) {
    cout << "Cantidad de estudiantes: " << escuela.cantidadEstudiantes << endl;
    cout << "Cantidad de materias: " << escuela.cantidadMaterias << endl;
    for (int i = 0; i < escuela.cantidadEstudiantes; i++) {
        cout << "-------------------------------" << endl;
        cout << setw(10) << escuela.estudiantes[i].id << endl;
        cout << setw(10) << escuela.estudiantes[i].nombre << endl;
        cout << setw(10) << escuela.estudiantes[i].promedio << endl;
    }

    for (int i = 0; i < escuela.cantidadMaterias; i++) {
        cout << "-------------------------------" << endl;
        cout << setw(10) << escuela.materias[i].nombre << endl;
        cout << setw(10) << escuela.materias[i].codigo << endl;
        cout << setw(10) << escuela.materias[i].creditos << endl;
    }
}

// Retorna el indice del estudiante con mejor promedio
int buscarMejorPromedio(const Escuela& escuela) {
    if (isArrayNull(escuela.estudiantes)) {
        cout << "Error: Puntero nulo" << endl;
        return -1;
    }

    int max = 0;
    for (int i = 0; i < escuela.cantidadEstudiantes; i++) {
        max = escuela.estudiantes[i].promedio > max ? i : max;
    }
    return max;
}

// Calcula el promedio general de la escuela
float calcularPromedioGeneral(const Escuela& escuela) {
    if (isArrayNull(escuela.estudiantes) || escuela.cantidadEstudiantes <= 0) {
        cout << "No hay estudiantes o puntero nulo";
        return 0.0f;
    }

    int sum = 0;
    for (int i = 0; i < escuela.cantidadEstudiantes; i++) {
        sum += escuela.estudiantes[i].promedio;
    }

    return static_cast<float>(sum) / escuela.cantidadEstudiantes;
}

// Busca un estudiante por id y retorna su indice
int buscarEstudiantePorId(const Escuela& escuela, int id) {
    if (isArrayNull(escuela.estudiantes)) {
        cout << "Argumento inválido";
        return -1;
    }

    for (int i = 0; i < escuela.cantidadEstudiantes; i++) {
        if (!(escuela.estudiantes[i].id == id)) {
            continue;
        }
        return i;
    }

    // No id valid
    return -1;
}

// Libera la memoria de la escuela
void liberarEscuela(Escuela& escuela) {
    delete[] escuela.materias;
    escuela.materias = nullptr;
    delete[] escuela.estudiantes;
    escuela.estudiantes = nullptr;

    escuela.cantidadEstudiantes = 0;
    escuela.cantidadMaterias = 0;
}

// Muestra el menu principal
void mostrarMenu() {
    cout << "\n=== GESTION DE ESTUDIANTES ===" << endl;
    cout << "1. Crear y llenar escuela" << endl;
    cout << "2. Mostrar escuela" << endl;
    cout << "3. Estudiante con mejor promedio" << endl;
    cout << "4. Promedio general" << endl;
    cout << "5. Buscar por id" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    Escuela escuela;
    escuela.estudiantes = nullptr;
    escuela.materias = nullptr;
    escuela.cantidadEstudiantes = 0;
    escuela.cantidadMaterias = 0;

    cout << "=== GESTION DE ESTUDIANTES ===" << endl;
    cout << "Implemente las funciones marcadas con TODO para completar el ejercicio." << endl;

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
        case 1: {
            int cantEst = 0;
            int cantMat = 0;
            cout << "Ingrese la cantidad de estudiantes: ";
            cin >> cantEst;
            cout << "Ingrese la cantidad de materias: ";
            cin >> cantMat;

            liberarEscuela(escuela);
            crearEscuela(escuela, cantEst, cantMat);

            if (escuela.estudiantes != nullptr && escuela.materias != nullptr) {
                llenarMaterias(escuela);
                llenarEstudiantes(escuela);
                cout << "Escuela creada y llenada correctamente." << endl;
            } else {
                cout << "Error al crear la escuela." << endl;
            }
            break;
        }

        case 2: {
            if (escuela.estudiantes != nullptr && escuela.materias != nullptr) {
                mostrarEscuela(escuela);
            } else {
                cout << "No hay escuela creada. Use la opcion 1 primero." << endl;
            }
            break;
        }

        case 3: {
            if (escuela.estudiantes != nullptr && escuela.cantidadEstudiantes > 0) {
                int indice = buscarMejorPromedio(escuela);
                if (indice >= 0) {
                    cout << "Mejor promedio: " << escuela.estudiantes[indice].nombre << " ("
                         << fixed << setprecision(2) << escuela.estudiantes[indice].promedio << ")"
                         << endl;
                } else {
                    cout << "No hay estudiantes en la lista." << endl;
                }
            } else {
                cout << "No hay escuela creada o esta vacia." << endl;
            }
            break;
        }

        case 4: {
            if (escuela.estudiantes != nullptr && escuela.cantidadEstudiantes > 0) {
                float promedio = calcularPromedioGeneral(escuela);
                cout << "Promedio general: " << fixed << setprecision(2) << promedio << endl;
            } else {
                cout << "No hay escuela creada o esta vacia." << endl;
            }
            break;
        }

        case 5: {
            if (escuela.estudiantes != nullptr && escuela.cantidadEstudiantes > 0) {
                int idBuscado;
                cout << "Ingrese el id a buscar: ";
                cin >> idBuscado;
                int indice = buscarEstudiantePorId(escuela, idBuscado);
                if (indice >= 0) {
                    cout << "Encontrado: " << escuela.estudiantes[indice].nombre << " (" << fixed
                         << setprecision(2) << escuela.estudiantes[indice].promedio << ")" << endl;
                } else {
                    cout << "No se encontro un estudiante con ese id." << endl;
                }
            } else {
                cout << "No hay escuela creada o esta vacia." << endl;
            }
            break;
        }

        case 6: {
            cout << "Saliendo del programa..." << endl;
            break;
        }

        default: {
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
        }
        }
    } while (opcion != 6);

    liberarEscuela(escuela);
    cout << "Programa finalizado. Memoria liberada." << endl;
    return 0;
}
