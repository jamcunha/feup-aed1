#ifndef FEUP_AED1_TURMAH_H
#define FEUP_AED1_TURMAH_H

#include "UCTurma.h"
#include "Aula.h"

#include <list>
/**
 * @brief Representa o Horário de cada turma.
 */
class TurmaH {
private:
    /**
     * @brief Turma e a Unidade Curricular associada.
     */
    UCTurma turma_;
    /**
     * @brief Horário associado á turma.
     *
     * @details Guardado em uma lista de Aulas.
     */
    std::list<Aula> horario_;

public:
    //Construtores
    /**
     * Cria um Horário.
     * @param turma Turma e Unidade Curricular.
     */
    TurmaH(const UCTurma &turma);
    //"Getters"
    /**
     * @return Da turma e unidade curricular.
     */
    const UCTurma& getTurma() const;
    /**
     * @return Do horario associado á turma de uma UC.
     */
    std::list<Aula> getHorario() const;
    //Adicionar
    /**
     * Adiciona uma nova aula ao horário.
     * @details Complexidade: O(1).
     * @param aula Nova aula a adicionar.
     */
    void addAula(const Aula &aula);
    /**
     * Verifica se o horário é viável, ou seja, não há aulas sobrepostas do tipo TP OU PL.
     * @details Complexidade: 0(n^2).
     * @param horario Horario associado á turma.
     * @return True-Se o horário for possível.
     * @return False-Se o horário tiver aulas sobrepostas.
     */
    bool isCompatible(const TurmaH &horario) const;
    //Operadores
    /**
     * Compara se a turma1 é igual á turma2.
     * @param turma turma a ser comparada.
     * @return True se forem da mesma turma.
     * @return False se forem de turmas diferentes.
     */
    bool operator==(const TurmaH &turma) const;
    /**
     * Compara se a turma1 é diferente da turma2.
     * @param turma turma a ser comparada.
     * @return True se forem de turmas diferentes.
     * @return False se forem da mesma turma.
     */
    bool operator!=(const TurmaH &turma) const;
};

#endif //FEUP_AED1_TURMAH_H
