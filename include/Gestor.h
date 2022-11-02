#ifndef FEUP_AED1_GESTOR_H
#define FEUP_AED1_GESTOR_H

#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <map>

#include "Estudante.h"
#include "TurmaH.h"
#include "OrdenarEstudantes.h"

#include "Pedido.h"

// Capacidade máxima da turma
#define CAP 25
/**
 * @brief Cria um Gestor.
 *
 * @details O gestor será usado como classe central usada para acessar as outras classes.
 */
class Gestor {
private:
    /**
     *@brief Guarda uma lista de estudantes por ordem crescente.
     *
     * @details A ordenação é feita com o uso da class OrdenarEstudantes.
     */
    std::set<Estudante, NomeCrescente> estudantes_;
    /**
     *@brief Lista de horários.
     */
    std::vector<TurmaH> horarios_;
    /**
     *@brief Fila de pedidos.
     *
     * @details É usado o "FIFO(first in first out)".
     */
    std::queue<Pedido> pedidos_;
    /**
     *@brief Número de estudantes inscritos por turma.
     */
    std::map<UCTurma, int> capacidade_;
    /**
     *@brief Pedidos arquivados.
     */
    std::list<Pedido> arquivo_;
    /**
     * @brief Remove um estudante de uma turma X. Complexidade: O(log(n)).
     * @param estudante Estudante a remover.
     */
    void removerEstudante(const Estudante &estudante);
    /**
     * @brief Adiciona um estudante a uma turma X. Complexidade: O(log(n)).
     * @param est Estudante a ser adicionado.
     * @param turma Turma e Unidade Curricular associada.
     * @return
     */
    bool adicionarEstudante(Estudante &est, const UCTurma &turma);
    /**
     * @brief Verifica se é possível alterar a turma de um estudante.
     * @details Complexidade: O(2n).
     * @param est Estudante que efetuou o pedido.
     * @param turma Turma a ser alterada.
     * @return True-Se for possível alterar.
     * @return False-Se não for possível alterar.
     */
    bool alterarTurma(Estudante &est, const UCTurma &turma);
    /**
     * @brief Verifica se é possível alterar várias turma no qual um estudante pertence.
     * @details Complexidade: O([2n^2]+n).
     * @param est Estudante que efetuou o pedido.
     * @param turmas Lista de turmas que o estudante frequenta.
     * @return True-Se for possível alterar.
     * @return False-Se não for possível alterar.
     */
    bool alterarTurmas(Estudante &est, const std::list<UCTurma> &turmas);

public:
    //Construtores
    /**
     * @brief Cria um novo gestor.
     */
    Gestor();
    /**
     * @brief Abre os ficheiros para leitura.
     * @details Complexidade: O(3n).
     */
    void lerFicheiros();
    /**
     *
     * @param tipo Tipo de pedido. 1 -> remover estudante, 2 -> adicionar estudante, (adicionar mais).
     * @param est Estudante que efetuou o pedido.
     * @param turma Turma e Unidade Curricular associada ao estudante.
     *
     * @details Adicionado um valor default à turma pois não é necessária para remover estudantes
     */
    void adicionarPedido(unsigned tipo, const Estudante &est, const UCTurma &turma = UCTurma("", ""));
    /**
     * @brief Overloading da função adicionarPedido para poder adicionar um pedido que engloba mais que uma turma.
     * @param tipo Tipo de pedido. 1 -> remover estudante, 2 -> adicionar estudante, (adicionar mais).
     * @param est Estudante que efetuou o pedido.
     * @param turmas Lista turmas associadas ao estudante.
     */
    void adicionarPedido(unsigned tipo, const Estudante &est, const std::list<UCTurma> &turmas);

    /**
    * @brief Resolve todos os pedidos.
    * @details A separação dos pedidos possiveis e impossíveis é feita aqui.
    */
    void processarPedidos();
    /**
     * @brief Abre o menú de opções.
     */
    void mostrarMenu();
};

#endif //FEUP_AED1_GESTOR_H
