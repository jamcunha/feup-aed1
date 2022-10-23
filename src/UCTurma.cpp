#include "../include/UCTurma.h"

UCTurma::UCTurma(int cod_uc, int cod_turma): cod_uc_(cod_uc), cod_turma_(cod_turma) {}

int UCTurma::getCodUC() const {
    return cod_uc_;
}

int UCTurma::getCodTurma() const {
    return cod_turma_;
}
