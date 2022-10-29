#ifndef FEUP_AED1_UCTURMA_H
#define FEUP_AED1_UCTURMA_H

#include <string>
/**
 * @brief Representa uma turma associada a uma Unidade Curricular
 */
class UCTurma {
private:
    /**
     *@brief Código da Unidade Curricular
     */
    std::string cod_uc_;
    /**
     *@brief Código da Turma
     */
    std::string cod_turma_;

public:
    //Construtores
    /**
     *Cria uma associação entre a turma e a unidade curricular
     * @param cod_uc Unidade Curricular
     * @param cod_turma Turma
     */
    UCTurma(const std::string &cod_uc, const std::string &cod_turma);
    //"Getters"
    /**
     * @return Da Unidade Curricular
     */
    std::string getCodUC() const;
    /**
     * @return Da Turma
     */
    std::string getCodTurma() const;
    //Operadores
    /**
     * @param turma turma e unidade curricular a ser comparda
     * @return True se ambas turmas e UC forem iguais
     * @return False se tiverem turma ou UC diferente
     */
    bool operator==(const UCTurma &turma) const;
    /**
     * @param turma turma e unidade curricular a ser comparda
     * @return True se tiverem turma ou UC diferente
     * @return False se ambas turmas e UC forem iguais
     */
    bool operator!=(const UCTurma &turma) const;
};

#endif //FEUP_AED1_UCTURMA_H
