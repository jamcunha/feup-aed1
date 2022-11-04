#include "../include/Gestor.h"
#include <iomanip>
#include <cmath>

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

    while(getline(inp_turmas, line)) {
        std::stringstream ss(line);
        std::string cod_uc, cod_turma;

        getline(ss, cod_uc, ',');
        getline(ss, cod_turma, '\r');

        UCTurma turma = UCTurma(cod_uc, cod_turma);
        capacidade_.insert(std::pair<UCTurma, int> (turma, 0));
    }

    while(getline(inp_estudante, line)) {
        std::stringstream ss(line);
        std::string cod_estudante_string, nome, cod_uc, cod_turma;

        getline(ss, cod_estudante_string, ',');
        getline(ss, nome, ',');
        getline(ss, cod_uc, ',');
        getline(ss, cod_turma, '\r');

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

    while(getline(inp_aulas, line)) {
        std::stringstream ss(line);
        std::string cod_turma, cod_uc, dia, inicio_string, duracao_string, tipo;

        getline(ss, cod_turma, ',');
        getline(ss, cod_uc, ',');
        getline(ss, dia, ',');
        getline(ss, inicio_string, ',');
        getline(ss, duracao_string, ',');
        getline(ss, tipo, '\r');

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

void Gestor::listarPedidos(){
    bool sair= false;
    while(!sair) {
        std::system("clear");
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                         MENU                         |\n";
        std::cout << "|------------------------------------------------------|\n";
        std::cout << "| 1 - Remover Estudante                                |\n";
        std::cout << "| 2 - Adicionar Estudante                              |\n";
        std::cout << "| 3 - Alterar Turma                                    |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Sair                                             |\n";
        std::cout << "--------------------------------------------------------\n";
        char opcao_menu;
        while(true) {
            std::cout << "\nOpcao: ";
            std::cin >> opcao_menu;
            if(opcao_menu <= '2' && opcao_menu >= '0')
                break;
            std::cout << "Opcao nao valida, escolha outra opcao.\n";
        }
        std::string nome;
        int cod;
        std::cout<<"Insira o Nome do Estudante: ";
        std::cin>>nome;
        while(true) {
            std::cout << "Insira o Codigo do Estudante (exemplo: 202025232): ";
            std::cin >> cod;
            if(int(std::log10(cod)+1) == 9)
                break;
            std::cout << "Formato do Codigo de Estudante errado. \n\n";
        }
        switch(opcao_menu) {
            case '1':{
                adicionarPedido(1,Estudante(cod,nome));
                break;
            }
            case '2':{
                std::string opcao_turma;
                std::string opcao_uc;
                std::cout << "\nInsira a Disciplina (ex: L.EIC001): ";
                std::cin >> opcao_uc;
                std::transform(opcao_uc.begin(), opcao_uc.end(), opcao_uc.begin(), ::toupper);

                std::cout << "\nInsira a Turma (ex: 1LEIC01) (Insira 0 para ver todas) : ";
                std::cin >> opcao_turma;
                std::transform(opcao_turma.begin(), opcao_turma.end(), opcao_turma.begin(), ::toupper);
                adicionarPedido(2,Estudante(cod,nome),UCTurma(opcao_uc,opcao_turma));
                break;
            }
            case '3':{
                char tecla = 's';
                std::string opcao_turma;
                std::string opcao_uc;
                std::list<UCTurma> lista_turmas;
                while(tecla != 's'){
                    std::cout << "\nInsira a Disciplina (ex: L.EIC001): ";
                    std::cin >> opcao_uc;
                    std::transform(opcao_uc.begin(), opcao_uc.end(), opcao_uc.begin(), ::toupper);

                    std::cout << "\nInsira a Turma (ex: 1LEIC01) (Insira 0 para ver todas) : ";
                    std::cin >> opcao_turma;
                    std::transform(opcao_turma.begin(), opcao_turma.end(), opcao_turma.begin(), ::toupper);
                    lista_turmas.push_back(UCTurma(opcao_uc,opcao_turma));
                    std::cout << "\nPressione s para listar mais: ";
                    std::cin >> tecla;}
                if (lista_turmas.size()!=1){
                    adicionarPedido(4,Estudante(cod,nome),lista_turmas);
                }
                else
                    adicionarPedido(3,Estudante(cod,nome),lista_turmas.front());
                break;
            }
            default:
                sair=true;
        }
        char tecla = 1;
        std::cout << "\nPressione q para voltar ao menu: ";
        while(tecla != 'q')
            std::cin >> tecla;
    }
}
void Gestor::adicionarPedido(unsigned tipo, const Estudante &est, const UCTurma &turma) {
    pedidos_.push(Pedido(est, turma, tipo));
}

void Gestor::adicionarPedido(unsigned tipo, const Estudante &est, const std::list<UCTurma> &turmas) {
    pedidos_.push(Pedido(est, turmas, tipo));
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
            case 3:
                flag = alterarTurma(pedido.getEstudante(), pedido.getTurma());
                if(!flag)
                    arquivo_.push_back(pedido);
                break;
            case 4:
                flag = alterarTurmas(pedido.getEstudante(), pedido.getTurmas());
                if(!flag)
                    arquivo_.push_back(pedido);
                break;
        }
    }
}


void Gestor::removerEstudante(const Estudante &estudante) {
    auto it = estudantes_.find(estudante);
    if(it != estudantes_.end())
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

bool Gestor::alterarTurma(Estudante &est, const UCTurma &turma) {
    // Verificar se a turma possui vaga
    if(capacidade_.at(turma)+1 > CAP)
        return false;

    // Verificar se o estudante existe
    auto it = estudantes_.find(est);
    if(it == estudantes_.end())
        return false;

    // Verificar se o estudante está na UC
    auto &temp = const_cast<Estudante &>(*it);
    UCTurma rem_turma = temp.remTurma(turma.getCodUC());
    if(!rem_turma.isValid())
        return false;

    capacidade_.at(rem_turma)--;
    // Verificar se a alteração não provoca desiquilibrio entre turmas
    // Talvez otimizar com o find do std::map [https://cplusplus.com/reference/map/map/find/]
    for(auto it = capacidade_.begin(); it != capacidade_.end(); it++) {
        if(it->first.getCodUC() == turma.getCodUC() && abs((capacidade_.at(turma)+1)-it->second) >= 4) {
            capacidade_.at(rem_turma)++;
            temp.addTurma(rem_turma);
            return false;
        }
    }

    // Verificar se o horário é compatível
    auto horario = std::find(horarios_.begin(), horarios_.end(), TurmaH(turma));
    for(const UCTurma &i: est.getTurmas()) {
        auto hor_i = std::find(horarios_.begin(), horarios_.end(), TurmaH(i));
        if(!hor_i->isCompatible(*horario)) {
            capacidade_.at(rem_turma)++;
            temp.addTurma(rem_turma);
            return false;
        }
    }

    capacidade_.at(turma)++;
    temp.addTurma(turma);

    return true;
}

bool Gestor::alterarTurmas(Estudante &est, const std::list<UCTurma> &turmas) {
    // Verificar se o estudante existe
    auto it = estudantes_.find(est);
    if(it == estudantes_.end())
            return false;

    auto &temp = const_cast<Estudante &>(*it);

    // Verificação para cada turma
    for(auto it_turma = turmas.begin(); it_turma != turmas.end(); it_turma++) {
        // Verificar se a turma possui vaga
        if(capacidade_.at(*it_turma)+1 > CAP)
            return false;

        // Verificar se o estudante está na UC
        UCTurma rem_turma = temp.remTurma(it_turma->getCodUC());
        if(!rem_turma.isValid())
            return false;

        capacidade_.at(rem_turma)--;
        // Verificar se a alteração não provoca desiquilibrio entre turmas
        // Talvez otimizar com o find do std::map [https://cplusplus.com/reference/map/map/find/]
        for(auto it = capacidade_.begin(); it != capacidade_.end(); it++) {
            if(it->first.getCodUC() == it_turma->getCodUC() && abs((capacidade_.at(*it_turma)+1)-it->second) >= 4) {
                capacidade_.at(rem_turma)++;
                temp.addTurma(rem_turma);
                return false;
            }
        }

        // Verificar se o horário é compatível
        auto horario = std::find(horarios_.begin(), horarios_.end(), TurmaH(*it_turma));
        for(const UCTurma &i: est.getTurmas()) {
            auto hor_i = std::find(horarios_.begin(), horarios_.end(), TurmaH(i));
            if(!hor_i->isCompatible(*horario)) {
                capacidade_.at(rem_turma)++;
                temp.addTurma(rem_turma);
                return false;
            }
        }
    }

    for(auto it_turma = turmas.begin(); it_turma != turmas.end(); it_turma++) {
        UCTurma rem_turma = temp.remTurma(it_turma->getCodUC());
        capacidade_.at(rem_turma)--;

        capacidade_.at(*it_turma)++;
        temp.addTurma(*it_turma);
    }

    return true;
}

void Gestor::mostrarMenu() {
    while(true) {
        std::system("clear");
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                         MENU                         |\n";
        std::cout << "|------------------------------------------------------|\n";
        std::cout << "| 1 - Ver Estudantes                                   |\n";
        std::cout << "| 2 - Ver Turmas                                       |\n";
        std::cout << "| 3 - Ver Horario                                      |\n";
        std::cout << "| 4 - Ver Alocacoes                                    |\n";
        std::cout << "| 5 - Ver Pedidos                                      |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 9 - Definicoes                                       |\n";
        std::cout << "| 0 - Sair                                             |\n";
        std::cout << "--------------------------------------------------------\n";
        char opcao_menu;
        while(true) {
            std::cout << "\nOpcao: ";
            std::cin >> opcao_menu;
            if(opcao_menu <= '5' && opcao_menu >= '0' || opcao_menu == '9')
                break;
            std::cout << "Opcao nao valida, escolha outra opcao.\n";
        }
        switch(opcao_menu) {
            case '1':
                listarEstudantes();
                break;
            case '2':
                listarTurmas();
                break;
            case '3':
                listarHorario();
                break;
            case '4':
                listarAlocacoes();
                break;
            case '5':
                listarPedidos();
                break;
            case '9':
                definicoes();
                break;
            default:
                std::system("clear");
                exit(0);
        }
    }
}

void Gestor::listarEstudantes() const {
    bool sair = false;
    while(!sair) {
        std::system("clear");
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                         MENU                         |\n";
        std::cout << "|------------------------------------------------------|\n";
        std::cout << "| 1 - Listar por nome                                  |\n";
        std::cout << "| 2 - Listar por codico estudante                      |\n";
        std::cout << "| 3 - Listar por numero de UCs                         |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Voltar ao menu principal                         |\n";
        std::cout << "--------------------------------------------------------\n";
        char opcao_menu;
        while(true) {
            std::cout << "\nOpcao: ";
            std::cin >> opcao_menu;
            if(opcao_menu <= '3' && opcao_menu >= '0')
                break;
            std::cout << "Opcao nao valida, escolha outra opcao.\n";
        }
        std::system("clear");
        switch(opcao_menu) {
            case '1':
                if (!ordenacao_) {
                    std::set<Estudante, NomeDecrescente> estudantes(estudantes_.begin(), estudantes_.end());
                    std::cout << "Numero Estudante | Nome                       | Numero de UCs\n";
                    std::cout << "-------------------------------------------------------------\n";
                    for (const auto &i: estudantes)
                        if((filtro_num_ucs_ && i.getTurmas().size() > num_ucs_) || (!filtro_num_ucs_ && i.getTurmas().size() < num_ucs_))
                            std::cout << i.getCodEstudante() << "\t | " << i.getNome() << std::setfill(' ') << std::setw(29-i.getNome().size()) << "| " << i.getTurmas().size() << "\n";
                } else {
                    std::set<Estudante, NomeCrescente> estudantes(estudantes_.begin(), estudantes_.end());
                    std::cout << "Numero Estudante | Nome                       | Numero de UCs\n";
                    std::cout << "-------------------------------------------------------------\n";
                    for (const auto &i: estudantes)
                        if((filtro_num_ucs_ && i.getTurmas().size() > num_ucs_) || (!filtro_num_ucs_ && i.getTurmas().size() < num_ucs_))
                            std::cout << i.getCodEstudante() << "\t | " << i.getNome() << std::setfill(' ') << std::setw(29-i.getNome().size()) << "| " << i.getTurmas().size() << "\n";
                }
                break;

            case '2':
                if (!ordenacao_) {
                    std::set<Estudante, CodEstudanteDecrescente> estudantes(estudantes_.begin(), estudantes_.end());
                    std::cout << "Numero Estudante | Nome                       | Numero de UCs\n";
                    std::cout << "-------------------------------------------------------------\n";
                    for (const auto &i: estudantes)
                        if((filtro_num_ucs_ && i.getTurmas().size() > num_ucs_) || (!filtro_num_ucs_ && i.getTurmas().size() < num_ucs_))
                            std::cout << i.getCodEstudante() << "\t | " << i.getNome() << std::setfill(' ') << std::setw(29-i.getNome().size()) << "| " << i.getTurmas().size() << "\n";
                } else {
                    std::cout << "Numero Estudante | Nome                       | Numero de UCs\n";
                    std::cout << "-------------------------------------------------------------\n";
                    for (const auto &i: estudantes_)
                        if((filtro_num_ucs_ && i.getTurmas().size() > num_ucs_) || (!filtro_num_ucs_ && i.getTurmas().size() < num_ucs_))
                            std::cout << i.getCodEstudante() << "\t | " << i.getNome() << std::setfill(' ') << std::setw(29-i.getNome().size()) << "| " << i.getTurmas().size() << "\n";
                }
                break;
            case '3':
                if (!ordenacao_) {
                    std::set<Estudante, NumUcDecrescente> estudantes(estudantes_.begin(), estudantes_.end());
                    std::cout << "Numero Estudante | Nome                       | Numero de UCs\n";
                    std::cout << "-------------------------------------------------------------\n";
                    for (const auto &i: estudantes)
                        if((filtro_num_ucs_ && i.getTurmas().size() > num_ucs_) || (!filtro_num_ucs_ && i.getTurmas().size() < num_ucs_))
                            std::cout << i.getCodEstudante() << "\t | " << i.getNome() << std::setfill(' ') << std::setw(29-i.getNome().size()) << "| " << i.getTurmas().size() << "\n";
                } else {
                    std::set<Estudante, NumUcCrescente> estudantes(estudantes_.begin(), estudantes_.end());
                    std::cout << "Numero Estudante | Nome                       | Numero de UCs\n";
                    std::cout << "-------------------------------------------------------------\n";
                    for (const auto &i: estudantes)
                        if((filtro_num_ucs_ && i.getTurmas().size() > num_ucs_) || (!filtro_num_ucs_ && i.getTurmas().size() < num_ucs_))
                            std::cout << i.getCodEstudante() << "\t | " << i.getNome() << std::setfill(' ') << std::setw(29-i.getNome().size()) << "| " << i.getTurmas().size() << "\n";
                }
                break;
            default:
                sair = true;
        }

        char tecla = 1;
        if(opcao_menu != '0') {
            std::cout << "\nPressione q para voltar ao menu: ";
            while(tecla != 'q')
                std::cin >> tecla;
        }
    }
}

void Gestor::listarTurmas() const {
    bool sair = false;
    while(!sair) {
        std::system("clear");
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                         MENU                         |\n";
        std::cout << "|------------------------------------------------------|\n";
        std::cout << "| 1 - Ver Estudantes por Ano                           |\n";
        std::cout << "| 2 - Ver Estudantes por Disciplina                    |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Voltar ao menu principal                         |\n";
        std::cout << "--------------------------------------------------------\n";
        char opcao_menu = 1;
        while(true) {
            std::cout << "\nOpcao: ";
            std::cin >> opcao_menu;
            if(opcao_menu <= '2' && opcao_menu >= '0')
                break;
            std::cout << "Opcao nao valida, escolha outra opcao.\n";
        }
        switch(opcao_menu) {
            case '1':
                int opcao_ano;
                while(true) {
                    std::cout << "Insira o Ano: ";
                    std::cin >> opcao_ano;
                    if(opcao_ano <= 3 && opcao_ano >= 1)
                        break;
                    std::cout << "Opcao nao valida, escolha outra opcao.\n";
                }

                std::system("clear");
                std::cout << "Estudantes do " << opcao_ano << "º Ano\n\n";
                for (auto it = estudantes_.begin(); it!= estudantes_.end(); it++) {
                    for (auto &j: it->getTurmas()){
                        int code = (int)(j.getCodTurma()[0]) - '0';
                        if (code == opcao_ano) {
                            std::cout << it->getCodEstudante() << "\t" << it->getNome() << "\n";
                            break;
                        }
                    }
                }
                break;
            case '2': {
                std::string opcao_turma;
                std::string opcao_uc;
                std::cout << "\nInsira a Disciplina (ex: L.EIC001): ";
                std::cin >> opcao_uc;
                std::transform(opcao_uc.begin(), opcao_uc.end(), opcao_uc.begin(), ::toupper);

                std::cout << "\nInsira a Turma (ex: 1LEIC01) (Insira 0 para ver todas) : ";
                std::cin >> opcao_turma;
                std::transform(opcao_turma.begin(), opcao_turma.end(), opcao_turma.begin(), ::toupper);

                std::cout << '\n';
                if(opcao_turma=="0"){
                    for(auto it = estudantes_.begin(); it != estudantes_.end(); it++) {
                        for(auto &j: it->getTurmas()) {
                            if (j.getCodUC() == opcao_uc)
                                std::cout << it->getCodEstudante() << "\t" << it->getNome() <<"\n";
                        }
                    }
                } else {
                    for(auto it = estudantes_.begin(); it != estudantes_.end(); it++) {
                        for(auto &j: it->getTurmas()){
                            if(j == UCTurma(opcao_uc, opcao_turma)){
                                std::cout << it->getCodEstudante() << "\t" << it->getNome() <<"\n";
                            }
                        }
                    }
                }
                break;
            }
            default:
                sair = true;
        }

        char tecla = 1;
        if(opcao_menu != '0') {
            std::cout << "\nPressione q para voltar ao menu: ";
            while(tecla != 'q')
                std::cin >> tecla;
        }
    }
}

struct horarioOrdenado {
    bool operator()(const std::pair<Aula,std::string> &left, const std::pair<Aula,std::string> &right) {
        return left.first.getInicio() < right.first.getInicio();
    }
};

void listagemHorario(std::list<std::pair<Aula,std::string>> &dia_semana){
    dia_semana.sort(horarioOrdenado());
    std::cout << dia_semana.begin()->first.getDia() << ":\n\n";
    for (const std::pair<Aula,std::string> &i : dia_semana){
        std::cout << i.second << " - " << "Horas: " << i.first.getInicio() << " - " << i.first.getFim() << '\t' << i.first.getTipo() << "\n";
    }
}

void Gestor::listarHorario(){
    int numero_estudante;
    while(true) {
        while(true) {
            std::cout << "Insira o Codigo do Estudante (exemplo: 202025232): ";
            std::cin >> numero_estudante;
            if(int(std::log10(numero_estudante)+1) == 9)
                break;
            std::cout << "Formato do Codigo de Estudante errado. \n\n";
        }
        std::list<std::pair<Aula,std::string>> segunda,terca,quarta,quinta,sexta;
        auto it = estudantes_.find(Estudante(numero_estudante,""));
        if (it != estudantes_.end()){
            std::cout<<"\nHorario "<<it->getNome()<<"\n";
            for (const UCTurma &i : it->getTurmas()){
                auto hor_i = std::find(horarios_.begin(), horarios_.end(), TurmaH(i));
                std::list<Aula> horario = hor_i->getHorario();
                for (const Aula &j : horario){
                    switch(j.getDia()[0]) {
                        case 'M':
                            segunda.push_back(std::make_pair(j,i.getCodUC()));
                            break;
                        case 'T':
                            if (j.getDia() == "Tuesday"){
                                terca.push_back(std::make_pair(j,i.getCodUC()));
                                break;
                            }
                            quinta.push_back(std::make_pair(j,i.getCodUC()));
                            break;
                        case 'W':
                            quarta.push_back(std::make_pair(j,i.getCodUC()));
                            break;
                        case 'F':
                            sexta.push_back(std::make_pair(j,i.getCodUC()));
                            break;
                    }

                }
            }
            if(!segunda.empty()) {
                std::cout << '\n';
                listagemHorario(segunda);
            }
            if(!terca.empty()) {
                std::cout << '\n';
                listagemHorario(terca);
            }
            if(!quarta.empty()) {
                std::cout << '\n';
                listagemHorario(quarta);
            }
            if(!quinta.empty()) {
                std::cout << '\n';
                listagemHorario(quinta);
            }
            if(!sexta.empty()) {
                std::cout << '\n';
                listagemHorario(sexta);
            }
            break;
        }
        else
            std::cout << "Estudante não encontrado.\n";
        break;
    }

    char tecla = 1;
    std::cout << "\nPressione q para voltar ao menu: ";
    while(tecla != 'q')
        std::cin >> tecla;
}

void Gestor::definicoes() {
    bool sair = false;
    while(!sair) {
        std::system("clear");
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                         DEFINICOES                   |\n";
        std::cout << "|------------------------------------------------------|\n";
        std::cout << "| 1 - Ordenacao Crescente/Decrescente [" << (ordenacao_ ? "Crescente]  ": "Decrescente]") << "    |\n";
        std::cout << "| 2 - Filtrar pelo numero de UCs [" << (filtro_num_ucs_ ? "Maior]" : "Menor]") << "               |\n";
        std::cout << "| 3 - Numero de UCs para filtrar [" << std::setfill('0') << std::setw(2) << num_ucs_ << "]                  |\n" ;
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Voltar ao menu principal                         |\n";
        std::cout << "--------------------------------------------------------\n";

        char opcao_menu;
        while(true) {
            std::cout << "\nOpcao: ";
            std::cin >> opcao_menu;
            if(opcao_menu <= '3' && opcao_menu >= '0')
                break;
            std::cout << "Opcao nao valida, escolha outra opcao.\n";
        }
        
        switch(opcao_menu) {
            case '1':
                ordenacao_ = !ordenacao_;
                break;
            case '2':
                filtro_num_ucs_ = !filtro_num_ucs_;
                break;
            case '3':
                while(true) {
                    std::cout << "\nNumero de UCs: ";
                    std::cin >> num_ucs_;
                    if(num_ucs_ < 100 && num_ucs_ >= 0)
                        break;
                    num_ucs_ = 0;
                    std::cout << "Numero de UCs nao valido, insira um numero entre 0 e 99\n";
                }
                break;
            default:
                sair = true;
        }
    }
}

void Gestor::listarAlocacoes() const {
    bool sair= false;
    while(!sair) {
        std::system("clear");
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                         MENU                         |\n";
        std::cout << "|------------------------------------------------------|\n";
        std::cout << "| 1 - Alocacoes por ano                                |\n";
        std::cout << "| 2 - Alocacoes por turma                              |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Voltar ao menu principal                         |\n";
        std::cout << "--------------------------------------------------------\n";
        char opcao_menu;
        while(true) {
            std::cout << "\nOpcao: ";
            std::cin >> opcao_menu;
            if(opcao_menu <= '2' && opcao_menu >= '0')
                break;
            std::cout << "Opcao nao valida, escolha outra opcao.\n";
        }
        switch(opcao_menu) {
            case '1':{
                int count1=0, count2=0, count3=0;
                bool flag1,flag2,flag3;
                for (const auto &estudante : estudantes_) {
                    flag1=flag2=flag3= false;
                    for (const auto & j : estudante.getTurmas()){
                        int code = (int)(j.getCodTurma()[0]) - '0';
                        switch (code){
                            case 1:
                                if (!flag1){
                                    count1+=1;
                                    flag1=true;}
                                break;
                            case 2:
                                if (!flag2){
                                    count2+=1;
                                    flag2=true;}
                                break;
                            case 3:
                                if (!flag3){
                                    count3+=1;
                                    flag3=true;}
                                break;
                        }
                    }
                }
                std::cout<<"1º Ano: "<<count1<<" alunos\n";
                std::cout<<"2º Ano: "<<count2<<" alunos\n";
                std::cout<<"3º Ano: "<<count3<<" alunos\n";
                break;
            }
            case '2': {
                std::string opcao_turma;
                std::string opcao_uc;
                std::cout << "\nInsira a Disciplina (ex: L.EIC001): ";
                std::cin >> opcao_uc;
                std::transform(opcao_uc.begin(), opcao_uc.end(), opcao_uc.begin(), ::toupper);
                std::cout << "\nInsira a Turma (ex: 1LEIC01) (Insira 0 para ver todas) : ";
                std::cin >> opcao_turma;
                std::transform(opcao_turma.begin(), opcao_turma.end(), opcao_turma.begin(), ::toupper);
                std::cout << '\n';
                if(opcao_turma=="0") {
                    int capacidade_turma=0;
                    for(auto it = capacidade_.begin(); it != capacidade_.end(); it++) {
                        if(it->first.getCodUC() == opcao_uc)
                            capacidade_turma+=it->second;
                    }
                    std::cout<<opcao_uc<<": "<<capacidade_turma<<" alunos\n";
                }
                else {
                    std::cout<<opcao_uc<<" - "<< opcao_turma<<": "<<capacidade_.at(UCTurma(opcao_uc,opcao_turma))<<" alunos\n";
                }
                break;
            }
            default:
                sair=true;
        }
        if(opcao_menu != '0') {
            char tecla = 1;
            std::cout << "\nPressione q para voltar ao menu: ";
            while(tecla != 'q')
                std::cin >> tecla;
        }
    }
}


bool checkFileExists(std::string path) {
    std::ifstream file(path);
    return file.good();
}

void Gestor::guardarFicheiros() {
    // Guardar arquivo no ficheiro
    bool existe = checkFileExists("../data/arquivo.csv");
    std::ofstream out_arquivo("../data/arquivo.csv", std::ios::app);
    if(!existe)
        out_arquivo << "Tipo,CodEstudante,Nome,CodUc,CodTurma\n";
    for(Pedido &pedido: arquivo_) {
        for(UCTurma &turma: pedido.getTurmas()) {
            out_arquivo << pedido.getTipo() << ',';
            out_arquivo << pedido.getEstudante().getCodEstudante() << ',' << pedido.getEstudante().getNome() << ',';
            out_arquivo << turma.getCodUC() << ',' << turma.getCodTurma() << '\n';
        }
    }

    // Rescrever o ficheiro dos estudantes
    std::ofstream out_estudantes("../data/students_classes.csv");
    out_estudantes << "StudentCode,StudentName,UcCode,ClassCode\n";

    for(auto it = estudantes_.begin(); it != estudantes_.end(); it++) {
        for(auto &turma: it->getTurmas()) {
            out_estudantes << it->getCodEstudante() << ',' << it->getNome() << ',';
            out_estudantes << turma.getCodUC() << ',' << turma.getCodTurma() << '\n';
        }
    }
}

