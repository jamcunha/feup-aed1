#ifndef FEUP_AED1_ESTUDANTE_H
#define FEUP_AED1_ESTUDANTE_H

#include <string>
#include <list>
#include "UCTurma.h"

class Estudante {
private:
    int cod_estudante_;
    std::string nome_;
    std::list<UCTurma> turmas_;

public:
    Estudante(int cod_estudante, const std::string &nome);
    int getCodEstudante() const;
    std::string getNome() const;
    std::list<UCTurma> getTurmas() const;

    void addTurma(const UCTurma &turma);

    bool operator==(const Estudante &est) const;
};

#endif //FEUP_AED1_ESTUDANTE_H
