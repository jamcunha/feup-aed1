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

class Gestor {
private:
    std::set<Estudante, NomeCrescente> estudantes_;
    std::vector<TurmaH> horarios_;
    std::queue<Pedido> pedidos_;
    std::map<UCTurma, unsigned> capacidade_;
    std::list<Pedido> arquivo_;

public:
    Gestor();

    void lerFicheiros();
    void adicionarPedido(const Estudante &est, const UCTurma &turma, unsigned tipo);
    void processarPedidos();
    bool removerEstudante(const Estudante &estudante);
    bool adicionarEstudante(const Estudante &est, const UCTurma &turma);
    void mostrarMenu();
};

#endif //FEUP_AED1_GESTOR_H
