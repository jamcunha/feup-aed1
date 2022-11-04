#include <iostream>
#include "../include/Gestor.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Gestor gestor;
    gestor.lerFicheiros();
    gestor.mostrarMenu();
    gestor.processarPedidos();
    return 0;
}
