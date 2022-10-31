#ifndef FEUP_AED1_PEDIDO_H
#define FEUP_AED1_PEDIDO_H

#include "Estudante.h"
#include "UCTurma.h"
/**
 *
 */
class Pedido {
private:
    /**
     *
     */
    Estudante estudante_;
    /**
     *
     */
    UCTurma turma_;
    /**
     * @details 1 -> remover estudante, 2 -> adicionar estudante, (adicionar mais).
     */
    unsigned tipo_;

public:
    //Construtores
    /**
     *
     * @param estudante
     * @param turma
     * @param tipo
     */
    Pedido(const Estudante &estudante, const UCTurma &turma, unsigned tipo);
    /**
     * @details Não é usado o const , para poder adicionar a turma antes de meter no set através da referência do estudante.
     * @return
     */
    Estudante &getEstudante() ;
    /**
     * @return
     */
    UCTurma getTurma() const;
    /**
     * @return
     */
    unsigned getTipo() const;
};

#endif //FEUP_AED1_PEDIDO_H
