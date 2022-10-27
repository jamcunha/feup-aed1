#include "../include/Gestor.h"

Gestor::Gestor() {}

void Gestor::lerFicheiros() {
    std::ifstream inp_estudante("../data/students_classes.csv");
    std::ifstream inp_aulas("../data/classes.csv");

    // Descartar a primeira linha dos ficheiros
    std::string line;
    getline(inp_estudante, line);
    getline(inp_aulas, line);

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
            auto &temp = const_cast<Estudante &>(*it);
            temp.addTurma(UCTurma(cod_uc, cod_turma));
        } else {
            est.addTurma(UCTurma(cod_uc, cod_turma));
            estudantes_.insert(est);
        }
    }

    for(line; getline(inp_aulas, line);) {
        std::stringstream ss(line);
        std::string cod_turma, cod_uc, dia, inicio_string, duracao_string, tipo;

        getline(ss, cod_turma, ',');
        getline(ss, cod_uc, ',');
        getline(ss, dia, ',');
        getline(ss, inicio_string, ',');
        getline(ss, duracao_string, ',');
        getline(ss, tipo, ',');

        float inicio = std::stof(inicio_string);
        float duracao = std::stof(duracao_string);

        UCTurma turma = UCTurma(cod_uc, cod_turma);
        Aula aula = Aula(dia, inicio, duracao, tipo);

        auto it = std::find(horarios_.begin(), horarios_.end(), TurmaH(turma));
        if(it != horarios_.end()) {
            it->addAula(aula);
        } else {
            TurmaH horario = TurmaH(turma);
            horario.addAula(aula);
            horarios_.push_back(horario);
        }
    }
}

void Gestor::mostrarMenu() {}
