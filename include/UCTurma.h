#ifndef FEUP_AED1_UCTURMA_H
#define FEUP_AED1_UCTURMA_H

#include <string>

class UCTurma {
private:
    std::string cod_uc_;
    std::string cod_turma_;

public:
    UCTurma(const std::string &cod_uc, const std::string &cod_turma);

    std::string getCodUC() const;
    std::string getCodTurma() const;

    bool operator==(const UCTurma &turma) const;
    bool operator!=(const UCTurma &turma) const;
};

#endif //FEUP_AED1_UCTURMA_H
