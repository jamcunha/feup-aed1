#include "../include/Estudante.h"

Estudante::Estudante(int cod_estudante, const std::string &nome): cod_estudante_(cod_estudante), nome_(nome) {}

int Estudante::getCodEstudante() const {
    return cod_estudante_;
}

std::string Estudante::getNome() const {
    return nome_;
}

std::list<UCTurma> Estudante::getTurmas() const {
    return turmas_;
}

void Estudante::addTurma(const UCTurma &turma) {
    turmas_.push_back(turma);
}

bool Estudante::operator==(const Estudante &est) const {
    return (nome_ == est.getNome() && cod_estudante_ == est.getCodEstudante());
}

bool Estudante::operator!=(const Estudante &est) const {
    return !(*this == est);
}
