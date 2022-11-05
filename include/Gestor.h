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
    // Ordenação true -> crescente, false -> decrescente
    bool ordenacao_ = true;
    // Filtragem pelo numero de ucs true -> maior que num_ucs, false -> menor que num_ucs
    bool filtro_num_ucs_ = true;
    // Usado para filtro_num_ucs
    unsigned num_ucs_ = 0;
    // Capacidade máxima da turma
    unsigned cap_ = 25;
/**
     * @brief Remove um estudante de uma turma X. Complexidade: O(n).
     * @param estudante Estudante a remover.
     */
    void removerEstudante(const Estudante &estudante);
    /**
     * @brief Adiciona um estudante a uma turma X. Complexidade: O(n).
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
     * @details Complexidade: O(n).
     */
    void lerFicheiros();
    /**
     *
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
    void mostrarMenu();
    void listarEstudantes() const;
    void listarTurmas() const;
    void listarHorario();
    void listarAlocacoes() const;
    void listarPedidos();
    void definicoes();
    /**
    * @brief Resolve todos os pedidos.
    * @details A separação dos pedidos possiveis e impossíveis é feita aqui.
    * @details Complexidade: O(n).
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
 /*
  * Depois do merge cm o menu

   bool ordenação
/*
@brief Determina se a ordenação é crescente ou decrescente
@details Ordenação=true -> crescente | Ordenação=false -> decrescente.
/*

bool filtro_num_ucs_
/**
@brief Determina o tipo de filtragem pelo numero de ucs
@details True -> maior que num_ucs | false -> menor que num_ucs.
/*

unsigned num_ucs
/**
@brief Usado como filtro.
@details num_ucs_=5 -> Vai listar todos os estudantes com mais de 5 ucs,caso filtro_num_ucs_=true.
@details Ou lista todos os estudantes com menos de 5 ucs, se filtro_num_ucs=false.
/*

listarestudantes()
/**
@brief Abre o menú que contem a listagem de estudantes.
@details Complexidade: O(n).
/*

listarturmas()
/**
 @brief Abre o menú que contem a listagem de turmas.
@details Complexidade: O(n^2).
/*

listarhorario()
/**
 @brief Abre o menú que contem a listagem de horários.
@details Complexidade: O(n^3).
/*

listarAlocações()
/**
 @brief Abre o menú que contem a listagem de alucacoes.
@details Complexidade: O(n^2).
/*

listarPedidos()
/**
  @brief Abre o menú que contem a criação de novos pedidos.
@details Complexidade: O(n).
/*

definições()
/**
@brief Abre as definições.
@details Complexidade: O(1).
/*


/*
 * @brief Ordena numericamente de forma crescente, a capacidade de duas turmas diferentes.
 */
 /*
 struct NumUcCrescente{
/**
     * @param left Capacidade da turma 1.
     * @param right Capacidade da turma 2.
     * @return True-Se a capacidade da turma 1 for menor que a capacidade da turma 2.
     * @return False-Se a capacidade da turma 1 for maior que a capacidade da turma 2.

     bool operator()(const Estudante &left, const Estudante &right) {
         return (left.getTurmas().size()<=right.getTurmas().size());
     }
 };
/*
 * @brief Ordena numericamente de forma decrescente, a capacidade de duas turmas diferentes.
*/
/*
struct NumUcDecrescente{
    * @param left Capacidade da turma 1.
    * @param right Capacidade da turma 2.
    * @return True-Se a capacidade da turma 1 for maior que a capacidade da turma 2.
    * @return False-Se a capacidade da turma 1 for menor que a capacidade da turma 2.

    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getTurmas().size()>=right.getTurmas().size();
    }
};


*/