#include "../include/TurmaH.h"

TurmaH::TurmaH(const UCTurma &turma): turma_(turma) {}

const UCTurma& TurmaH::getTurma() const {
    return turma_;
}

std::list<Aula> TurmaH::getHorario() const {
    return horario_;
}

void TurmaH::addAula(const Aula &aula) {
    horario_.push_back(aula);
}

bool TurmaH::operator==(const TurmaH &turma) const {
    return (turma_ == turma.getTurma());
}

bool TurmaH::operator!=(const TurmaH &turma) const {
    return !(turma_ == turma.getTurma());
}
