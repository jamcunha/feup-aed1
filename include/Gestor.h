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

class Gestor {
private:
    std::set<Estudante> estudantes_;
    std::vector<TurmaH> horario_;
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
