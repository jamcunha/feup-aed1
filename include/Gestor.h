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
     *@brief Lista de horários
     */
    std::vector<TurmaH> horarios_;
    /**
     *@brief Fila de pedidos
     *
     * @details É usado o "FIFO(first in first out)".
     */
    std::queue<Pedido> pedidos_;
    /**
     *@brief Número de estudantes inscritos numa turma.
     */
    std::map<UCTurma, int> capacidade_;
    /**
     *@brief
     */
    std::list<Pedido> arquivo_;
    /**
     *
     * @param estudante
     */
    void removerEstudante(const Estudante &estudante);
    /**
     *
     * @param est
     * @param turma
     * @return
     */
    bool adicionarEstudante(Estudante &est, const UCTurma &turma);

public:
    //Construtores
    /**
     *
     */
    Gestor();
    /**
     *
     */
    void lerFicheiros();
    /**
     *
     * @param tipo
     * @param est
     * @param turma
     *
     * @details Adicionado um valor default à turma pois não é necessária para remover estudantes
     */
    void adicionarPedido(unsigned tipo, const Estudante &est, const UCTurma &turma = UCTurma("", ""));
    /**
     *
     */
    void processarPedidos();
    /**
     *
     */
    void mostrarMenu();
};

#endif //FEUP_AED1_GESTOR_H
