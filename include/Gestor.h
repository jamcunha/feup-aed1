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
#include "Pedido.h"
#include "Aula.h"

// Capacidade máxima da turma
#define CAP 25


class Gestor {
private:
    std::set<Estudante, CodEstudanteCrescente> estudantes_;
    std::vector<TurmaH> horarios_;
    std::queue<Pedido> pedidos_;
    std::map<UCTurma, int> capacidade_;
    std::list<Pedido> arquivo_;

    // Ordenação true -> crescente, false -> decrescente
    bool ordenacao_ = true;
    // Filtragem pelo numero de ucs true -> maior que num_ucs, false -> menor que num_ucs
    bool filtro_num_ucs_ = true;
    // Usado para filtro_num_ucs
    unsigned num_ucs_ = 0;

    void removerEstudante(const Estudante &estudante);
    bool adicionarEstudante(Estudante &est, const UCTurma &turma);
    bool alterarTurma(Estudante &est, const UCTurma &turma);
    bool alterarTurmas(Estudante &est, const std::list<UCTurma> &turmas);

public:
    Gestor();
    void lerFicheiros();
    // Adicionado um valor default à turma pois não é necessária para remover estudantes
    void adicionarPedido(unsigned tipo, const Estudante &est, const UCTurma &turma = UCTurma("", ""));
    void adicionarPedido(unsigned tipo, const Estudante &est, const std::list<UCTurma> &turmas);
    void processarPedidos();

    void mostrarMenu();
    void listarEstudantes() const;
    void listarTurmas() const;
    void listarHorario();
    void listarAlocacoes() const;
    void listarPedidos();
    void definicoes();

    void guardarFicheiros();
};

#endif //FEUP_AED1_GESTOR_H
