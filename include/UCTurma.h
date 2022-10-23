#ifndef FEUP_AED1_UCTURMA_H
#define FEUP_AED1_UCTURMA_H

class UCTurma {
private:
    int cod_uc_;
    int cod_turma_;

public:
    UCTurma(int cod_uc, int cod_turma);

    int getCodUC() const;
    int getCodTurma() const;
};

#endif //FEUP_AED1_UCTURMA_H
