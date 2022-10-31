#ifndef FEUP_AED1_PEDIDO_H
#define FEUP_AED1_PEDIDO_H

#include "Estudante.h"
#include "UCTurma.h"

class Pedido {
private:
    Estudante estudante_;
    UCTurma turma_;
    // 1 -> remover estudante, 2 -> adicionar estudante, 3 -> alterar turma
    unsigned tipo_;

public:
    Pedido(const Estudante &estudante, const UCTurma &turma, unsigned tipo);

    // O get é suposto ser const mas assim dá return à referencia do estudante para poder adicionar a turma antes de meter no set
    Estudante &getEstudante() ;
    UCTurma getTurma() const;
    unsigned getTipo() const;
};

#endif //FEUP_AED1_PEDIDO_H
