#include "../include/BSTEstudante.h"

BSTEstudante::BSTEstudante(const Estudante &est) {
    est_ = est;
    left = nullptr;
    right = nullptr;
}

void BSTEstudante::insert(const Estudante &est) {
    if(est == est_) {
        // Pode-se retirar o for pelo primeiro valor da lista getTurmas()
        for(UCTurma turma: est.getTurmas())
            est_.addTurma(turma);
    } else if(est > est_)
        right = insert(right, est);
    else if(est < est_)
        left = insert(left, est);
}

BSTEstudante *BSTEstudante::insert(BSTEstudante *root, const Estudante &est) {
    if(!root)
        return new BSTEstudante(est);

    if(est == root->est_) {
        for(UCTurma turma: est.getTurmas())
            est_.addTurma(turma);
    }
    else if(est > root->est_)
        root->right = insert(root->right, est);
    else if(est < root->est_) {
        root->left = insert(root->left, est);
    }

    return root;
}
