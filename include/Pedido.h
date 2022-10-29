#ifndef FEUP_AED1_PEDIDO_H
#define FEUP_AED1_PEDIDO_H

#include "Estudante.h"
#include "UCTurma.h"

class Pedido {
private:
    Estudante estudante_;
    UCTurma turma_;

    // 1 -> remover estudante, 2 -> adicionar estudante, (adicionar mais)
    unsigned tipo_;

public:
    Pedido(const Estudante &estudante, const UCTurma &turma, unsigned tipo);

    Estudante getEstudante() const;
    UCTurma getTurma() const;
    unsigned getTipo() const;
};

#endif //FEUP_AED1_PEDIDO_H
