#include "../include/Estudante.h"

Estudante::Estudante(): Estudante(0, "") {}

Estudante::Estudante(int cod_estudante, const std::string &nome): cod_estudante_(cod_estudante), nome_(nome) {}

Estudante::Estudante(const Estudante &est): cod_estudante_(est.getCodEstudante()), nome_(est.getNome()), turmas_(est.getTurmas()) {}

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

bool Estudante::operator<(const Estudante &est) const {
    return est.getNome().compare(nome_) < 0;
}

bool Estudante::operator>(const Estudante &est) const {
    return est.getNome().compare(nome_) > 0;
}

Estudante &Estudante::operator=(const Estudante &est) {
    this->cod_estudante_ = est.getCodEstudante();
    this->nome_ = est.getNome();
    this->turmas_ = est.getTurmas();
    return *this;
}

