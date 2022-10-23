#include "../include/TurmaH.h"

TurmaH::TurmaH(const UCTurma &turma): turma_(turma) {}

const UCTurma& TurmaH::getTurma() const {
    return turma_;
}
