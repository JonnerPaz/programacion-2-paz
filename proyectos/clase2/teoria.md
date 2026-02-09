# Clase 2: Memoria dinámica
## Stack vs heap
1. Stack:
    - 1MB (winslop)
    - 8MB (Linux god and MACOS)
    - stack overflow (nos jodimos, nos quedamos sin espacio)
    - Más rápida
2. Heap:
    - Memoria ram mucho más accesible
    - Más lenta, pero grandísima
3. Exception:
    - Error de ejecución.
    - try-catch para Exception handling

`````````cpp
try {
    // something bad happened
} catch (bad_alloc &e) {
    std::cout << "Metí la pata" << std::endl;
}
`````````

## Proyecto de la materia

El proyecto va a ser una especie de inventario de compras y ventas de productos.

Posibles clases:
- productos
- Proveedores
- Transacción (compra/venta)

Memory leak: No libero memoria y se me llenó el rancho. No puedo almacenar más vacas.
