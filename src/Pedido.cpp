#include "../include/Pedido.h"

Pedido::Pedido(const Estudante &estudante, const UCTurma &turma, unsigned tipo): estudante_(estudante), tipo_(tipo) {
    turmas_.push_back(turma);
}

Pedido::Pedido(const Estudante &estudante, const std::list<UCTurma> &turmas, unsigned tipo): estudante_(estudante), tipo_(tipo) {
    for(auto it = turmas.begin(); it != turmas.end(); it++) {
        turmas_.push_back(*it);
    }
}

Estudante &Pedido::getEstudante() {
    return estudante_;
}

UCTurma Pedido::getTurma() const {
    return *turmas_.begin();
}

std::list<UCTurma> Pedido::getTurmas() const {
    return turmas_;
}

unsigned Pedido::getTipo() const {
    return tipo_;
}
