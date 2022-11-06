#ifndef FEUP_AED1_GESTOR_H
#define FEUP_AED1_GESTOR_H

#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <iomanip>

#include "Estudante.h"
#include "TurmaH.h"
#include "OrdenarEstudantes.h"
#include "Aula.h"

#include "Pedido.h"
/**
 * @brief Cria um Gestor.
 *
 * @details O gestor será usado como classe central usada para acessar as outras classes.
 */
class Gestor {
private:
    /**
     * @brief Guarda uma lista de estudantes por ordem crescente.
     *
     * @details A ordenação é feita com o uso da class OrdenarEstudantes.
     */
    std::set<Estudante, NomeCrescente> estudantes_;
    /**
     *@brief Lista de horários.
     */
    std::vector<TurmaH> horarios_;
    /**
     * @brief Fila de pedidos.
     *
     * @details É usado o "FIFO(first in first out)".
     */
    std::queue<Pedido> pedidos_;
    /**
     * @brief Número de estudantes inscritos por turma.
     */
    std::map<UCTurma, int> capacidade_;
    /**
     * @brief Pedidos arquivados.
     */
    std::list<Pedido> arquivo_;
    /**
     * @brief Determina se a ordenação é crescente ou decrescente
     * @details Ordenação=true -> crescente | Ordenação=false -> decrescente.
     */
    bool ordenacao_ = true;
    /**
     * @brief Determina o tipo de filtragem pelo numero de ucs.
     * @details True -> maior que num_ucs | false -> menor que num_ucs.
     */
    bool filtro_num_ucs_ = true;
    /**
     * @brief Usado como filtro.
     * @details num_ucs_=5 -> Vai listar todos os estudantes com mais de 5 ucs,caso filtro_num_ucs_=true.
     * @details Ou lista todos os estudantes com menos de 5 ucs, se filtro_num_ucs=false.
     */
    unsigned num_ucs_ = 0;
    /**
     * @brief Limite de estudantes inscritos numa turma.
     */
    unsigned cap_ = 25;
    /**
     * @brief Remove um estudante de uma turma X.
     * @details Complexidade: O(log(n)).
     * @param estudante Estudante a remover.
     */
    void removerEstudante(const Estudante &estudante);
    /**
     * @brief Adiciona um estudante a uma turma X.
     * @deetails Complexidade: O(n).
     * @param est Estudante a ser adicionado.
     * @param turma Turma e Unidade Curricular associada.
     * @return
     */
    bool adicionarEstudante(Estudante &est, const UCTurma &turma);
    /**
     * @brief Verifica se é possível alterar a turma de um estudante.
     * @details Complexidade: O(n).
     * @param est Estudante que efetuou o pedido.
     * @param turma Turma a ser alterada.
     * @return True-Se for possível alterar.
     * @return False-Se não for possível alterar.
     */
    bool alterarTurma(Estudante &est, const UCTurma &turma);
    /**
     * @brief Verifica se é possível alterar várias turma no qual um estudante pertence.
     * @details Complexidade: O(n^2).
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
     * @details Complexidade: O(n(log(n)).
     */
    void lerFicheiros();
    /**
     * @bief Adiciona um pedido á fila de pedidos.
     * @param tipo Tipo de pedido. 1 -> remover estudante, 2 -> adicionar estudante, 3->alterar turma, 4->alterar conjunto de turmas.
     * @param est Estudante que efetuou o pedido.
     * @param turma Turma e Unidade Curricular associada ao estudante.
     *
     * @details Adicionado um valor default à turma pois não é necessária para remover estudantes
     * @details Complexidade: O(1).
     */
    void adicionarPedido(unsigned tipo, const Estudante &est, const UCTurma &turma = UCTurma("", ""));
    /**
     * @brief Overloading da função adicionarPedido para poder adicionar um pedido que engloba mais que uma turma.
     * @param tipo Tipo de pedido. 1 -> remover estudante, 2 -> adicionar estudante, 3->alterar turma, 4->alterar conjunto de turmas.
     * @param est Estudante que efetuou o pedido.
     * @param turmas Lista turmas associadas ao estudante.
     * @details Complexidade: O(1).
     */
    void adicionarPedido(unsigned tipo, const Estudante &est, const std::list<UCTurma> &turmas);
    /**
     * @brief Abre o menú que contem a listagem de estudantes.
     * @details Complexidade: O(n).
     */
    void listarEstudantes() const;
    /**
     * @brief Abre o menú que contem a listagem de turmas.
     * @details Complexidade: O(n^2).
     */
    void listarTurmas() const;
    /**
     * @brief Abre o menú que contem a listagem de horários.
     * @details Complexidade: O(n^3).
     */
    void listarHorario();
    /**
     * @brief Abre o menú que contem a listagem de alucacoes.
     * @details Complexidade: O(n^2).
     */
    void listarAlocacoes() const;
    /**
     * @brief Abre o menú que contem a criação de novos pedidos.
     * @details Complexidade: O(n).
     */
    void listarPedidos();
    /**
     * @brief Abre as definições.
     */
    void definicoes();
    /**
    * @brief Resolve todos os pedidos.
    * @details A separação dos pedidos possiveis e impossíveis é feita aqui.
    * @details Complexidade: O(n^2).
    */
    void processarPedidos();
    /**
     * @brief Abre o menú de opções.
     */
    void mostrarMenu();
    /**
     * @brief Guarda os ficheiros depois de alterados.
     * @details Complexidade: O(n^2).
     */
    void guardarFicheiros();
};

#endif //FEUP_AED1_GESTOR_H
