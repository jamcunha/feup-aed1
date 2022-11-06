#include "../include/TurmaH.h"

TurmaH::TurmaH(const UCTurma &turma): turma_(turma) {}

const UCTurma& TurmaH::getTurma() const {
    return turma_;
}

std::list<Aula> TurmaH::getHorario() const {
    return horario_;
}

void TurmaH::addAula(const Aula &aula) {
    horario_.push_back(aula);//O(1)
}

bool TurmaH::isCompatible(const TurmaH &horario) const { // n^2
    for(const Aula &aula : horario.getHorario()) { //n
        if(aula.getTipo() == "T")
            continue;
        for(const Aula &it : horario_) { //n
            if(it.getTipo() == "T")
                continue;
            if(aula.getDia() == it.getDia() && (
                    (aula.getInicio() >= it.getInicio() && aula.getInicio() <= it.getFim() ||
                    (aula.getFim() >= it.getInicio() && aula.getFim() <= it.getFim()))))
                return false;
        }
    }
    return true;
}

bool TurmaH::operator==(const TurmaH &turma) const {
    return (turma_ == turma.getTurma());
}

bool TurmaH::operator!=(const TurmaH &turma) const {
    return !(turma_ == turma.getTurma());
}
