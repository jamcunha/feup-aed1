#include "../include/Gestor.h"

Gestor::Gestor() {}

void Gestor::lerFicheiros() {
    std::ifstream inp_estudante("../data/students_classes.csv");

    std::string line;
    getline(inp_estudante, line);
    for(line; getline(inp_estudante, line);) {
        std::stringstream ss(line);
        std::string cod_estudante_string, nome, cod_uc, cod_turma;

        getline(ss, cod_estudante_string, ',');
        getline(ss, nome, ',');
        getline(ss, cod_uc, ',');
        getline(ss, cod_turma, ',');

        int cod_estudante = std::stoi(cod_estudante_string);

        Estudante est = Estudante(cod_estudante, nome);
        auto it = estudantes_.find(est);
        if(it != estudantes_.end()) {
            // não deve ser a melhor coisa mas nao da erros
            Estudante temp = *it;
            estudantes_.erase(it);
            temp.addTurma(UCTurma(cod_uc, cod_turma));
            estudantes_.insert(temp);
        } else {
            est.addTurma(UCTurma(cod_uc, cod_turma));
            estudantes_.insert(est);
        }
    }
}

void Gestor::mostrarMenu() {}
