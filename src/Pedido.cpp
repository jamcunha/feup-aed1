#include "../include/Pedido.h"

Pedido::Pedido(const Estudante &estudante, const UCTurma &turma, unsigned int tipo): estudante_(estudante), turma_(turma), tipo_(tipo) {}

Estudante Pedido::getEstudante() const {
    return estudante_;
}

UCTurma Pedido::getTurma() const {
    return turma_;
}

unsigned Pedido::getTipo() const {
    return tipo_;
}
