#include "../include/UCTurma.h"

UCTurma::UCTurma(int cod_uc, int cod_turma): _cod_uc(cod_uc), _cod_turma(cod_turma) {}

int UCTurma::getCodUC() const {
    return _cod_uc;
}

int UCTurma::getCodTurma() const {
    return _cod_turma;
}
