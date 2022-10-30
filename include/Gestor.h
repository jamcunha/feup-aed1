#ifndef FEUP_AED1_GESTOR_H
#define FEUP_AED1_GESTOR_H

#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Estudante.h"
#include "TurmaH.h"
#include <algorithm>
#include "OrdenarEstudantes.h"


class Gestor {
private:
    std::set<Estudante, NomeCrescente> estudantes_;
    std::vector<TurmaH> horarios_;
    //TODO Pedidos

public:
    Gestor();
    void lerFicheiros();
    void mostrarMenu();
    void listarEstudantes() const;
    void settings() const;
    void listarTurmas() const;


};

#endif //FEUP_AED1_GESTOR_H
