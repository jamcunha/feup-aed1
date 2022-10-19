#ifndef FEUP_AED1_ESTUDANTE_H
#define FEUP_AED1_ESTUDANTE_H

#include <string>
#include <list>
#include "UCTurma.h"

class Estudante {
private:
    int _cod_estudante;
    std::string _nome;
    std::list<UCTurma> turmas;

public:
    Estudante(int cod_estudante, std::string nome);
};

#endif //FEUP_AED1_ESTUDANTE_H
