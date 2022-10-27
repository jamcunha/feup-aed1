#ifndef FEUP_AED1_GESTOR_H
#define FEUP_AED1_GESTOR_H

#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Estudante.h"
#include "TurmaH.h"

class Gestor {
private:
    std::set<Estudante> estudantes_;
    std::vector<TurmaH> horario_;
    //TODO Pedidos

public:
    Gestor();

    void lerFicheiros();

    void mostrarMenu();
};

#endif //FEUP_AED1_GESTOR_H
