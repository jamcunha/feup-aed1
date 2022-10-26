#ifndef FEUP_AED1_GESTOR_H
#define FEUP_AED1_GESTOR_H

#include <set>
#include <vector>

#include "Estudante.h"
#include "TurmaH.h"

class Gestor {
private:
    std::set<Estudante> estudantes_;
    std::vector<TurmaH> turmas_;
    //TODO Pedidos

public:
    Gestor();
    void mostrarMenu();
};

#endif //FEUP_AED1_GESTOR_H
