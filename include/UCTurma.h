#ifndef FEUP_AED1_UCTURMA_H
#define FEUP_AED1_UCTURMA_H

class UCTurma {
private:
    int _cod_uc;
    int _cod_turma;

public:
    UCTurma(int cod_uc, int cod_turma);

    int getCodUC() const;
    int getCodTurma() const;
};

#endif //FEUP_AED1_UCTURMA_H
