#ifndef FEUP_AED1_ORDENARESTUDANTES_H
#define FEUP_AED1_ORDENARESTUDANTES_H

#include "Estudante.h"
/**
 * @brief Classe de suporte no ordenamento da lista de estudantes.
 */

/**
 * @brief Ordena alfabéticamente de forma crescente,o nome de dois estudantes.
 */
struct NomeCrescente {
    /**
     * @param left Nome do estudante1.
     * @param right Nome do estudante2.
     * @return True-Se o nome do estudante1 for menor que o nome do estudante2
     * @return False-Se o nome do estudante1 for maior que o nome do estudante2
     */
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getNome() < right.getNome();
    }
};
/**
 * @brief Ordena alfabéticamente de forma decrescente,o nome de dois estudantes.
 */
struct NomeDecrescente {
    /**
     * @param left Nome do estudante1.
     * @param right Nome do estudante2.
     * @return True-Se o nome do estudante1 for maior que o nome do estudante2
     * @return False-Se o nome do estudante1 for menor que o nome do estudante2
     */
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getNome() > right.getNome();
    }
};
/**
 * @brief Ordena numericamente de forma crescente, dois códigos de estudantes.
 */
struct CodEstudanteCrescente {
    /**
     * @param left Código do estudante1.
     * @param right Código do estudante2.
     * @return True-Se o código do estudante1 for menor que o código do estudante2
     * @return False-Se o código do estudante1 for maior que o código do estudante2
     */
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getCodEstudante() < right.getCodEstudante();
    }
};
/**
 * @brief Ordena numericamente de forma decrescente, dois códigos de estudantes.
 */
struct CodEstudanteDecrescente {
    /**
     * @param left Código do estudante1.
     * @param right Código do estudante2.
     * @return True-Se o código do estudante1 for maior que o código do estudante2
     * @return False-Se o código do estudante1 for menor que o código do estudante2
     */
    bool operator()(const Estudante &left, const Estudante &right) {
        return left.getCodEstudante() > right.getCodEstudante();
    }
};

#endif //FEUP_AED1_ORDENARESTUDANTES_H
