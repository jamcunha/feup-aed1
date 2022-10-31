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
#include "Estudante.h"
#include "TurmaH.h"
#include "OrdenarEstudantes.h"
#include "Pedido.h"

// Capacidade máxima da turma
#define CAP 25


class Gestor {
private:
    std::set<Estudante, NomeCrescente> estudantes_;
    std::vector<TurmaH> horarios_;
    std::queue<Pedido> pedidos_;
    std::map<UCTurma, int> capacidade_;
    std::list<Pedido> arquivo_;

    void removerEstudante(const Estudante &estudante);
    bool adicionarEstudante(Estudante &est, const UCTurma &turma);

public:
    Gestor();
    void lerFicheiros();
    // Adicionado um valor default à turma pois não é necessária para remover estudantes
    void adicionarPedido(unsigned tipo, const Estudante &est, const UCTurma &turma = UCTurma("", ""));
    void processarPedidos();
    void mostrarMenu();
    void listarEstudantes() const;
    void settings() const;
    void listarTurmas() const;


};

#endif //FEUP_AED1_GESTOR_H
