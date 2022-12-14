#include "../include/UCTurma.h"

UCTurma::UCTurma(): cod_uc_(""), cod_turma_("") {}
UCTurma::UCTurma(const std::string &cod_uc, const std::string &cod_turma): cod_uc_(cod_uc), cod_turma_(cod_turma) {}

std::string UCTurma::getCodUC() const {
    return cod_uc_;
}

std::string UCTurma::getCodTurma() const {
    return cod_turma_;
}

bool UCTurma::isValid() const {
    return (cod_uc_ != "" && cod_turma_ != "");
}

bool UCTurma::operator==(const UCTurma &turma) const {
    return (cod_uc_ == turma.getCodUC() && cod_turma_ == turma.getCodTurma());
}

bool UCTurma::operator!=(const UCTurma &turma) const {
    return !(cod_uc_ == turma.getCodUC() && cod_turma_ == turma.getCodTurma());
}

bool UCTurma::operator<(const UCTurma &turma) const {
    if(cod_turma_ == turma.getCodTurma()) {
        return cod_uc_ < turma.getCodUC();
    }
    return cod_turma_ < turma.getCodTurma();
}
