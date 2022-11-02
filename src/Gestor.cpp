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

    for(line; getline(inp_turmas, line);) { //n
        std::stringstream ss(line);
        std::string cod_uc, cod_turma;

        getline(ss, cod_uc, ',');
        getline(ss, cod_turma, ',');

        UCTurma turma = UCTurma(cod_uc, cod_turma);
        capacidade_.insert(std::pair<UCTurma, int> (turma, 0));//log(n)
        //n log(n)
    }

    for(line; getline(inp_estudante, line);) { //n
        std::stringstream ss(line);
        std::string cod_estudante_string, nome, cod_uc, cod_turma;

        getline(ss, cod_estudante_string, ',');
        getline(ss, nome, ',');
        getline(ss, cod_uc, ',');
        getline(ss, cod_turma, ',');

        int cod_estudante = std::stoi(cod_estudante_string);

        Estudante est = Estudante(cod_estudante, nome);
        auto it = estudantes_.find(est);//log(n)
        if(it != estudantes_.end()) {
            auto &temp = const_cast<Estudante &>(*it);

            capacidade_.at(UCTurma(cod_uc, cod_turma))++; // log(n)
            temp.addTurma(UCTurma(cod_uc, cod_turma)); // 1
        } else {
            capacidade_.at(UCTurma(cod_uc, cod_turma))++; //log(n)
            est.addTurma(UCTurma(cod_uc, cod_turma)); // 1

            estudantes_.insert(est); //log(n)
        }
        // n 2 log(n)
    }

    for(line; getline(inp_aulas, line);) { //n
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

        auto it = std::find(horarios_.begin(), horarios_.end(), TurmaH(turma)); //log(n)
        if(it != horarios_.end()) {
            it->addAula(aula); // 1
        } else {
            TurmaH horario = TurmaH(turma);
            horario.addAula(aula); // 1
            horarios_.push_back(horario); //O(1)
        }
    }
}

void Gestor::adicionarPedido(unsigned tipo, const Estudante &est, const UCTurma &turma) {
    pedidos_.push(Pedido(est, turma, tipo)); // 1
}

void Gestor::adicionarPedido(unsigned tipo, const Estudante &est, const std::list<UCTurma> &turmas) {
    pedidos_.push(Pedido(est, turmas, tipo)); // 1
}

void Gestor::processarPedidos() {
    while(!pedidos_.empty()) {
        Pedido pedido = pedidos_.front(); //1
        pedidos_.pop(); // 1

        bool flag;
        switch(pedido.getTipo()) {
            case 1:
                removerEstudante(pedido.getEstudante()); //log(n)
                break;
            case 2:
                flag = adicionarEstudante(pedido.getEstudante(), pedido.getTurma()); // adicionarEstudante
                if(!flag)
                    arquivo_.push_back(pedido); // 1
                break;
            case 3:
                flag = alterarTurma(pedido.getEstudante(), pedido.getTurma()); //
                if(!flag)
                    arquivo_.push_back(pedido); // 1
                break;
            case 4:
                flag = alterarTurmas(pedido.getEstudante(), pedido.getTurmas()); //
                if(!flag)
                    arquivo_.push_back(pedido); // 1
                break;
        }
    }
}

void Gestor::removerEstudante(const Estudante &estudante) { // log(n)
    auto it = estudantes_.find(estudante); //log(n)
    estudantes_.erase(it); //O(1)
}

bool Gestor::adicionarEstudante(Estudante &est, const UCTurma &turma) { //
    // Verificar se a turma possui vaga
    if(capacidade_.at(turma)+1 > CAP)//log(n)
        return false;

    // Verificar se a alteração não provoca desiquilibrio entre turmas
    // Talvez otimizar com o find do std::map [https://cplusplus.com/reference/map/map/find/]
    for(auto it = capacidade_.begin(); it != capacidade_.end(); it++) { // n
        if(it->first.getCodUC() == turma.getCodUC() && abs((capacidade_.at(turma)+1)-it->second) >= 4) {
            return false;
        }
    }

    // Verificar se o horário é compatível
    auto horario = std::find(horarios_.begin(), horarios_.end(), TurmaH(turma)); // n
    for(const UCTurma &i: est.getTurmas()) { //n
        auto hor_i = std::find(horarios_.begin(), horarios_.end(), TurmaH(i)); //n
        if(!hor_i->isCompatible(*horario))
            return false;
    }

    auto it = estudantes_.find(est); //log(n)
    if(it != estudantes_.end()) {
        auto &temp = const_cast<Estudante &>(*it);

        capacidade_.at(turma)++;// log(n)
        temp.addTurma(turma); // 1
    } else {
        capacidade_.at(turma)++;// log(n)
        est.addTurma(turma); // 1

        estudantes_.insert(est);// log(n)
    }
    return true;
}

bool Gestor::alterarTurma(Estudante &est, const UCTurma &turma) {
    // Verificar se a turma possui vaga
    if(capacidade_.at(turma)+1 > CAP) //log(n)
        return false;

    // Verificar se o estudante existe
    auto it = estudantes_.find(est);//log(n)
    if(it == estudantes_.end())
        return false;

    // Verificar se o estudante está na UC
    auto &temp = const_cast<Estudante &>(*it);
    UCTurma rem_turma = temp.remTurma(turma.getCodUC()); //rem_turma
    if(!rem_turma.isValid())//isvalid
        return false;

    capacidade_.at(rem_turma)--; // log(n)
    // Verificar se a alteração não provoca desiquilibrio entre turmas
    // Talvez otimizar com o find do std::map [https://cplusplus.com/reference/map/map/find/]
    for(auto it = capacidade_.begin(); it != capacidade_.end(); it++) { // n
        if(it->first.getCodUC() == turma.getCodUC() && abs((capacidade_.at(turma)+1)-it->second) >= 4) {
            capacidade_.at(rem_turma)++; // log(n)
            temp.addTurma(rem_turma); // 1
            return false;
        }
    }

    // Verificar se o horário é compatível
    auto horario = std::find(horarios_.begin(), horarios_.end(), TurmaH(turma)); //n
    for(const UCTurma &i: est.getTurmas()) {
        auto hor_i = std::find(horarios_.begin(), horarios_.end(), TurmaH(i)); // n
        if(!hor_i->isCompatible(*horario)) {//iscompatible
            capacidade_.at(rem_turma)++; //log(n)
            temp.addTurma(rem_turma); //1
            return false;
        }
    }

    capacidade_.at(turma)++; // log(n)
    temp.addTurma(turma); // 1

    return true;
}

bool Gestor::alterarTurmas(Estudante &est, const std::list<UCTurma> &turmas) {
    // Verificar se o estudante existe
    auto it = estudantes_.find(est); //log(n)
    if(it == estudantes_.end())
            return false;

    auto &temp = const_cast<Estudante &>(*it);

    // Verificação para cada turma
    for(auto it_turma = turmas.begin(); it_turma != turmas.end(); it_turma++) { // n
        // Verificar se a turma possui vaga
        if(capacidade_.at(*it_turma)+1 > CAP) //log(n)
            return false;

        // Verificar se o estudante está na UC
        UCTurma rem_turma = temp.remTurma(it_turma->getCodUC()); //remturma
        if(!rem_turma.isValid())//isvalid
            return false;

        capacidade_.at(rem_turma)--;
        // Verificar se a alteração não provoca desiquilibrio entre turmas
        // Talvez otimizar com o find do std::map [https://cplusplus.com/reference/map/map/find/]
        for(auto it = capacidade_.begin(); it != capacidade_.end(); it++) { //n
            if(it->first.getCodUC() == it_turma->getCodUC() && abs((capacidade_.at(*it_turma)+1)-it->second) >= 4) {
                capacidade_.at(rem_turma)++; // log(n)
                temp.addTurma(rem_turma); // 1
                return false;
            }
        }

        // Verificar se o horário é compatível
        auto horario = std::find(horarios_.begin(), horarios_.end(), TurmaH(*it_turma)); //n
        for(const UCTurma &i: est.getTurmas()) { // n
            auto hor_i = std::find(horarios_.begin(), horarios_.end(), TurmaH(i)); // n
            if(!hor_i->isCompatible(*horario)) { // n^2
                capacidade_.at(rem_turma)++; // log(n)
                temp.addTurma(rem_turma); // 1
                return false;
            }
        }
    }

    for(auto it_turma = turmas.begin(); it_turma != turmas.end(); it_turma++) { // n
        UCTurma rem_turma = temp.remTurma(it_turma->getCodUC()); //remturma
        capacidade_.at(rem_turma)--; // log(n)
        capacidade_.at(*it_turma)++; // log(n)
        temp.addTurma(*it_turma); // 1
    }

    return true;
}

void Gestor::mostrarMenu() {}
