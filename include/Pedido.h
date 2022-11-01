#ifndef FEUP_AED1_PEDIDO_H
#define FEUP_AED1_PEDIDO_H

#include "Estudante.h"
#include "UCTurma.h"
/**
 * @brief Representa um Pedido
 */
class Pedido {
private:
    /**
     * @brief Estudante que efetuou o pedido.
     */
    Estudante estudante_;
    /**
     * @brief Lista de turmas associadas ao estudante.
     */
    std::list<UCTurma> turmas_;
    // 1 -> remover estudante, 2 -> adicionar estudante, 3 -> alterar turma

    unsigned tipo_;

public:
    //Construtores
     /**
      * @brief Cria um novo pedido.
      * @param estudante Estudante que efetuou o pedido.
      * @param turma Turma e UC associada ao estudante.
      * @param tipo Tipo de pedido (1 -> remover estudante, 2 -> adicionar estudante, 3 -> alterar turma).
      */
    Pedido(const Estudante &estudante, const UCTurma &turma, unsigned tipo);
    /**
     * @brief Overloading da função Pedido, para poder efetuar um pedido que engloba mais que uma turma.
     * @param estudante Estudante que efetuou o pedido.
     * @param turmas Lista de Turmas e UC em que o estudante frequenta.
     * @param tipo Tipo de pedido (1 -> remover estudante, 2 -> adicionar estudante, 3 -> alterar turma).
     */
    Pedido(const Estudante &estudante, const std::list<UCTurma> &turmas, unsigned tipo);
    /**
     * @details Não é usado o const, com o return da referência do estudante é possivel adicionar a turma antes de meter no set.
     * @return Referência do Estudante que fez o pedido.
     */
    Estudante &getEstudante() ;
    /**
     * @return
     */
    UCTurma getTurma() const;
    std::list<UCTurma> getTurmas() const;
    unsigned getTipo() const;
};

#endif //FEUP_AED1_PEDIDO_H
