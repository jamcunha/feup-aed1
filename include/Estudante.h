#ifndef FEUP_AED1_ESTUDANTE_H
#define FEUP_AED1_ESTUDANTE_H

#include <string>
#include <list>
#include "UCTurma.h"
/**
 * @brief Representa um Estudante.
 */
class Estudante {
private:
    /**
     * @brief Código do estudante.
     */
    int cod_estudante_;
    /**
     * @brief Nome do estudante.
     */
    std::string nome_;
    /**
     * @brief Turma e a Unidade Curricar associada.
     */
    std::list<UCTurma> turmas_;

public:
    //Construtores
    /**
     * Criar um Estudante novo
     * @param cod_estudante Código do estudante
     * @param nome Nome do estudante
     */
    Estudante(int cod_estudante, const std::string &nome);
    //"Getters"
    /**
     * @return Do código do estudante
     */
    int getCodEstudante() const;
    /**
     * @return Do nome do estudante
     */
    std::string getNome() const;
    /**
     * @return Da turma e da unidade curricular associada
     */
    std::list<UCTurma> getTurmas() const;
    //Adicionar
    /**
     * Associa uma turma e UC ao estudante
     * @param turma nova turma do estudante
     */
    void addTurma(const UCTurma &turma);
    UCTurma remTurma(const UCTurma &turma);
    UCTurma remTurma(const std::string &cod_uc);
    //Operadores
    /**
     * Compara a igualdade do nome e do código de estudante
     * @param est estudante2 a comparar
     * @return True se o nome e o código de estudante forem iguais
     * @return False se o nome ou o código de estudante forem diferentes
     */
    bool operator==(const Estudante &est) const;
    /**
     *Compara a desigualdade entre o nome ou o código de estudante
     * @param est estudante2 a comparar
     * @return True  se o nome ou o código de estudante forem diferentes
     * @return False se o nome e o código de estudante forem iguais
     */
    bool operator!=(const Estudante &est) const;
};

#endif //FEUP_AED1_ESTUDANTE_H
