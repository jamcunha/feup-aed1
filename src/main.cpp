#include <iostream>
#include "../include/Gestor.h"

int main() {
    Gestor gestor;
    gestor.lerFicheiros();
    gestor.mostrarMenu();
    gestor.processarPedidos();
    gestor.guardarFicheiros();

    return 0;
}
