#ifndef FEUP_AED1_BSTESTUDANTE_H
#define FEUP_AED1_BSTESTUDANTE_H

#include "Estudante.h"

class BSTEstudante {
private:
    Estudante est_;
    BSTEstudante *left, *right;

public:
    BSTEstudante(const Estudante &est);

    void insert(const Estudante &est);
    BSTEstudante *insert(BSTEstudante *root, const Estudante &est);
};

#endif //FEUP_AED1_BSTESTUDANTE_H
