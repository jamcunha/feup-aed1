#ifndef FEUP_AED1_GESTOR_H
#define FEUP_AED1_GESTOR_H

#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "Estudante.h"
#include "TurmaH.h"
#include "OrdenarEstudantes.h"
/**
 * @brief Cria um Gestor
 *
 * @details O gestor será utilizado para 
 */
class Gestor {
private:
    std::set<Estudante, NomeCrescente> estudantes_;
    std::vector<TurmaH> horarios_;
    //TODO Pedidos

public:
    Gestor();

    void lerFicheiros();

    void mostrarMenu();
};

#endif //FEUP_AED1_GESTOR_H
