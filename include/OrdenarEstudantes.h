#ifndef FEUP_AED1_ORDENARESTUDANTES_H
#define FEUP_AED1_ORDENARESTUDANTES_H

#include "Estudante.h"
#include "Aula.h"

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

struct NumUcOrdenadoCrescente{
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getTurmas().size()<right.getTurmas().size();
    }
};
struct NumUcOrdenadoDecrescente{
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getTurmas().size()>right.getTurmas().size();
    }
};

struct horarioOrdenado {
    bool operator()(const std::pair<Aula,std::string> &left, const std::pair<Aula,std::string> &right) {
        return left.first.getInicio()<right.first.getInicio();
    }
};

#endif //FEUP_AED1_ORDENARESTUDANTES_H
