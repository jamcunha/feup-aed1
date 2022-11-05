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

UCTurma Estudante::remTurma(const UCTurma &turma) {
    for(auto it = turmas_.begin(); it != turmas_.end(); it++) {
        if(*it == turma) {
            UCTurma rem = *it;
            it = turmas_.erase(it);
            return rem;
        }
    }
    return UCTurma();
}

UCTurma Estudante::remTurma(const std::string &cod_uc) {
    for(auto it = turmas_.begin(); it != turmas_.end(); it++) {
        if(it->getCodUC() == cod_uc) {
            UCTurma rem = *it;
            it = turmas_.erase(it);
            return rem;
        }
    }
    return UCTurma();
}

bool Estudante::operator==(const Estudante &est) const {
    return cod_estudante_ == est.getCodEstudante();
}

bool Estudante::operator!=(const Estudante &est) const {
    return !(*this == est);
}
