#include "../include/Gestor.h"

Gestor::Gestor() {}

void Gestor::lerFicheiros() {
    std::ifstream inp_estudante("../data/students_classes.csv");
    std::ifstream inp_aulas("../data/classes.csv");
    std::ifstream inp_turmas("../data/classes_per_uc.csv");

    // Descartar a primeira linha dos ficheiros
    std::string line;
    getline(inp_estudante, line);
    getline(inp_aulas, line);
    getline(inp_turmas, line);

    for(line; getline(inp_turmas, line);) {
        std::stringstream ss(line);
        std::string cod_uc, cod_turma;

        getline(ss, cod_uc, ',');
        getline(ss, cod_turma, ',');

        UCTurma turma = UCTurma(cod_uc, cod_turma);
        capacidade_.insert(std::pair<UCTurma, unsigned> (turma, 0));
    }

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

            capacidade_.at(UCTurma(cod_uc, cod_turma))++;
            temp.addTurma(UCTurma(cod_uc, cod_turma));
        } else {
            capacidade_.at(UCTurma(cod_uc, cod_turma))++;
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

void Gestor::adicionarPedido(unsigned tipo, const Estudante &est, const UCTurma &turma) {
    pedidos_.push(Pedido(est, turma, tipo));
}

void Gestor::processarPedidos() {
    while(!pedidos_.empty()) {
        Pedido pedido = pedidos_.front();
        pedidos_.pop();

        bool flag;
        switch(pedido.getTipo()) {
            case 1:
                removerEstudante(pedido.getEstudante());
                break;
            case 2:
                flag = adicionarEstudante(pedido.getEstudante(), pedido.getTurma());
                if(!flag)
                    arquivo_.push_back(pedido);
                break;
        }
    }
}

void Gestor::removerEstudante(const Estudante &estudante) {
    auto it = estudantes_.find(estudante);
    estudantes_.erase(it);
}

bool Gestor::adicionarEstudante(Estudante &est, const UCTurma &turma) {
    // Verificar se a turma possui vaga
    if(capacidade_.at(turma)+1 > CAP)
        return false;

    // Verificar se a alteração não provoca desiquilibrio entre turmas
    // Talvez otimizar com o find do std::map [https://cplusplus.com/reference/map/map/find/]
    for(auto it = capacidade_.begin(); it != capacidade_.end(); it++) {
        if(it->first.getCodUC() == turma.getCodUC() && abs((capacidade_.at(turma)+1)-it->second) >= 4) {
            return false;
        }
    }

    // Verificar se o horário é compatível
    auto horario = std::find(horarios_.begin(), horarios_.end(), TurmaH(turma));
    for(const UCTurma &i: est.getTurmas()) {
        auto hor_i = std::find(horarios_.begin(), horarios_.end(), TurmaH(i));
        if(!hor_i->isCompatible(*horario))
            return false;
    }

    auto it = estudantes_.find(est);
    if(it != estudantes_.end()) {
        auto &temp = const_cast<Estudante &>(*it);

        capacidade_.at(turma)++;
        temp.addTurma(turma);
    } else {
        capacidade_.at(turma)++;
        est.addTurma(turma);

        estudantes_.insert(est);
    }
    return true;
}

void Gestor::mostrarMenu() {}
