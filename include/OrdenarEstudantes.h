#ifndef FEUP_AED1_ORDENARESTUDANTES_H
#define FEUP_AED1_ORDENARESTUDANTES_H

#include "Estudante.h"

struct NomeCrescente {
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getNome() < right.getNome();
    }
};

struct NomeDecrescente {
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getNome() > right.getNome();
    }
};

struct CodEstudanteCrescente {
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getCodEstudante() < right.getCodEstudante();
    }
};

struct CodEstudanteDecrescente {
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getCodEstudante() > right.getCodEstudante();
    }
};

#endif //FEUP_AED1_ORDENARESTUDANTES_H
