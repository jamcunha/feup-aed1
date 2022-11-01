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

void Gestor::mostrarMenu() {
    std::cout << "--------------------------------------------------------\n";
    std::cout << "|                         MENU                         |\n";
    std::cout << "|------------------------------------------------------|\n";
    std::cout << "| 1 - Ver Estudantes                                   |\n";
    std::cout << "| 2 - Ver Turmas                                       |\n";
    std::cout << "| 3 - Ver Horario                                      |\n";
    std::cout << "| 4 - Ver UC                                           |\n";
    std::cout << "|                                                      |\n";
    std::cout << "| 0 - Sair                                             |\n";
    std::cout << "--------------------------------------------------------\n";
    int opcao_menu_;
    while(true) {
        std::cout << "\nOpcao (Default 1): ";
        std::cin >> opcao_menu_;
        if(opcao_menu_ <= 4 && opcao_menu_ >= 0)
            break;
        std::cout << "Opcao nao valida, escolha outra opcao.\n";
    }
    switch(opcao_menu_) {
        case 1:
            listarEstudantes();
            break;
        case 2:
            listarTurmas();
            break;
        case 3:
            break;
        default:
            exit(0);
    }
}

void Gestor::listarEstudantes() const {
    bool flag= true;
    while(true){
        std::system("clear");
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                         MENU                         |\n";
        std::cout << "|------------------------------------------------------|\n";
        std::cout << "| 1 - Listar por nome                                  |\n";
        std::cout << "| 2 - Listar por codico estudante                      |\n";
        std::cout << "| 3 - Alunos com mais que n disciplinas                |\n";
        std::cout << "| 4 - Alunos com mais que n disciplinas                |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 9 - Crescente/Decrescente " << "(" << (flag ? "Crescente)  " : "Decrescente)") << "              |\n";
        std::cout << "| 0 - Sair                                             |\n";
        std::cout << "--------------------------------------------------------\n";
        int opcao_menu_ = 1;
        while(true) {
            std::cout << "\nOpcao (Default 1): ";
            std::cin >> opcao_menu_;
            if((opcao_menu_ <= 4 && opcao_menu_ >= 0) || opcao_menu_==9)
                break;
            std::cout << "Opcao nao valida, escolha outra opcao.\n";
        }
        switch(opcao_menu_) {
            case 1: {
            }
                if (!flag) {
                    std::set<Estudante, NomeDecrescente> estudanteslist;
                    for (const auto &i: estudantes_) {
                        estudanteslist.insert(i);
                    }
                    std::cout << "Numero Estudante | Nome";
                    for (const auto &i: estudanteslist)
                        std::cout << i.getCodEstudante() << "\t" << i.getNome() << "\n";
                    break;
                }
                std::cout << "Numero Estudante | Nome";
                for (const auto &estudante: estudantes_)
                    std::cout << estudante.getCodEstudante() << "\t" << estudante.getNome() << "\n";
                break;

            case 2: {
                if (!flag) {
                    std::set<Estudante, CodEstudanteDecrescente> estudanteslist;
                    for (const auto &i: estudantes_) {
                        estudanteslist.insert(i);
                    }
                    std::cout << "Numero Estudante | Nome";
                    for (const auto &i: estudanteslist)
                        std::cout << i.getCodEstudante() << "\t" << i.getNome() << "\n";
                    break;
                }
                std::set<Estudante, CodEstudanteCrescente> estudanteslist;
                for (const auto &i: estudantes_)
                    estudanteslist.insert(i);
                std::cout << "Numero Estudante | Nome";
                for (const auto &i: estudanteslist)
                    std::cout << i.getCodEstudante() << "\t" << i.getNome() << "\n";

                break;
            }
            case 3:{
                int numero_UC;
                while (true) {
                    std::cout << "\nInsira o numero de UC: ";
                    std::cin >> numero_UC;
                    if (numero_UC >= 1)
                        break;
                    std::cout << "Opcao nao valida, escolha outra opcao.\n";
                }
                if (!flag) {
                    std::set<Estudante, NumUcOrdenadoDecrescente> estudanteslist;
                    for (const auto &i: estudantes_)
                        estudanteslist.insert(i);
                    std::cout << "Numero Estudante | Nome | Numero Turmas";
                    auto i = estudanteslist.begin();
                    while (i->getTurmas().size() > numero_UC) {
                        std::cout << i->getCodEstudante() << "\t" << i->getNome() << i->getTurmas().size() << "\n";
                        i++;
                    }
                    break;
                }
                std::set<Estudante, NumUcOrdenadoCrescente> estudanteslist;
                for (const auto &i: estudantes_)
                    estudanteslist.insert(i);
                std::cout << "Numero Estudante | Nome | Numero Turmas";
                for (const auto &i: estudanteslist) {
                    if (i.getTurmas().size() >= numero_UC)
                        std::cout << i.getCodEstudante() << "\t" << i.getNome() << i.getTurmas().size() << "\n";
                }
                break;
            }
            case 4:{
                int numero_UC;
                while (true) {
                    std::cout << "\nInsira o numero de UC: ";
                    std::cin >> numero_UC;
                    if (numero_UC >= 1)
                        break;
                    std::cout << "Opcao nao valida, escolha outra opcao.\n";
                }
                if (!flag) {
                    std::set<Estudante, NumUcOrdenadoDecrescente> estudanteslist;
                    for (const auto &i: estudantes_)
                        estudanteslist.insert(i);
                    std::cout << "Numero Estudante | Nome | Numero Turmas";
                    auto i = estudanteslist.begin();
                    for (const auto &i: estudanteslist) {
                        if (i.getTurmas().size() <= numero_UC)
                            std::cout << i.getCodEstudante() << "\t" << i.getNome() << i.getTurmas().size() << "\n";
                    }
                    break;
                }
                std::set<Estudante, NumUcOrdenadoCrescente> estudanteslist;
                for (const auto &i: estudantes_)
                    estudanteslist.insert(i);
                std::cout << "Numero Estudante | Nome | Numero Turmas";

                auto i = estudanteslist.begin();
                while (i->getTurmas().size() < numero_UC) {
                    std::cout << i->getCodEstudante() << "\t" << i->getNome() << i->getTurmas().size() << "\n";
                    i++;
                }
                break;
            }
            case 9:
                flag = !flag;
                break;
            default:
                exit(0);
        }

    }
}

void listagemhorario(std::list<std::pair<Aula,std::string>> dia_semana){
    dia_semana.sort(horarioOrdenado());
    std::cout<<dia_semana.begin()->first.getDia()<<":";
    for (const std::pair<Aula,std::string> &i : dia_semana){
        std::cout<<i.second<<"-"<<i.first.getTipo()<<" Horas: "<<i.first.getInicio()<<"-"<<i.first.getFim()<<"\n";
    }
}



void Gestor::listarHorario() const {
    int numero_estudante;
    while(true) {
        std::cout << "Insira o Código do Estudante (exemplo: 202025232): ";
        std::cin >> numero_estudante;
        std::list<std::pair<Aula,std::string>> segunda,terca,quarta,quinta,sexta;
        bool flag;
        for (auto estudante_horario: estudantes_){
            if (estudante_horario.getCodEstudante()==numero_estudante){
                flag= false;
                for (const UCTurma &i : estudante_horario.getTurmas()){
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
                listagemhorario(segunda);
                listagemhorario(terca);
                listagemhorario(quarta);
                listagemhorario(quinta);
                listagemhorario(sexta);

            }

        }
        if (flag)
            std::cout << "Opcao nao valida, escolha outra opcao.\n";

    }
}

void Gestor::listarTurmas() const {
    bool flag= true;
    while(true){
        std::system("clear");
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                         MENU                         |\n";
        std::cout << "|------------------------------------------------------|\n";
        std::cout << "| 1 - Ver Estudantes por Ano                           |\n";
        std::cout << "| 2 - Ver Estudantes por Disciplina                    |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 9 - Crescente/Decrescente " << "(" << (flag ? "Crescente  " : "Decrescente") << "              |\n";
        std::cout << "| 0 - Sair                                             |\n";
        std::cout << "--------------------------------------------------------\n";
        int opcao_menu_ = 1;
        while(true) {
            std::cout << "\nOpcao (Default 1): ";
            std::cin >> opcao_menu_;
            if((opcao_menu_ <= 4 && opcao_menu_ >= 0) || opcao_menu_==9)
                break;
            std::cout << "Opcao nao valida, escolha outra opcao.\n";
        }
        switch(opcao_menu_) {
            case 1:{
                int opcao_ano;
                while(true) {
                    std::cout << "Insira o Ano: ";
                    std::cin >> opcao_ano;
                    if(opcao_ano <= 3 && opcao_ano >= 1)
                        break;
                    std::cout << "Opcao nao valida, escolha outra opcao.\n";
                }
                for (auto i = estudantes_.begin(); i!= estudantes_.end(); i++) {
                    for (auto j = i->getTurmas().begin(); j!=i->getTurmas().end(); j++){
                        int code = (int)(j->getCodTurma()[0]);
                        if (code == opcao_ano){
                            std::cout<<i->getCodEstudante()<<"\t"<< i->getNome()<<"\n";

                        }
                    }
                }
                break;
            }
            case 2:{
                //passar para função?
                std::string opcao_turma;
                std::string opcao_disciplina;
                std::set<std::string> listar_disciplinas {"L.EIC001","L.EIC002", "L.EIC003", "L.EIC004", "L.EIC005", "L.EIC011", "L.EIC012", "L.EIC013", "L.EIC014", "L.EIC015", "L.EIC021", "L.EIC022", "L.EIC023", "L.EIC024", "L.EIC025", "UP001"};
                std::set<std::string> listar_turmas {"1LEIC01", "1LEIC02", "1LEIC03", "1LEIC04", "1LEIC05", "1LEIC06", "1LEIC07", "1LEIC08", "1LEIC09", "1LEIC10", "1LEIC11", "1LEIC12", "1LEIC13", "1LEIC14","1LEIC15", "1LEIC16","2LEIC01", "2LEIC02", "2LEIC03", "2LEIC04", "2LEIC05", "2LEIC06", "2LEIC07", "2LEIC08", "2LEIC09", "2LEIC10", "2LEIC11", "2LEIC12", "2LEIC13", "2LEIC14", "2LEIC15", "2LEIC16","3LEIC01", "3LEIC02", "3LEIC03", "3LEIC04", "3LEIC05", "3LEIC06", "3LEIC07", "3LEIC08", "3LEIC09", "3LEIC10", "3LEIC11", "3LEIC12" , "3LEIC13", "3LEIC14", "3LEIC15", "3LEIC16"};
                while (true){
                    for (std::string i : listar_disciplinas){
                        std::cout<<i;
                    }
                    std::cout << "Insira a Disciplina: ";
                    std::cin >> opcao_disciplina;
                    auto it = listar_disciplinas.find(opcao_disciplina);
                    if(it != listar_disciplinas.end())
                        break;
                    std::cout << "Opcao nao valida, escolha outra opcao.\n";
                }
                while(true) {
                    for (std::string i : listar_turmas){
                        std::cout<<i;
                    }
                    std::cout << "Insira a Turma (Insira 0 para ver todas) : ";
                    std::cin >> opcao_turma;
                    std::transform(opcao_turma.begin(), opcao_turma.end(), opcao_turma.begin(), ::toupper);
                    auto it = listar_turmas.find(opcao_turma);
                    if(opcao_turma=="0" || it != listar_turmas.end())
                        break;
                    std::cout << "Opcao nao valida, escolha outra opcao.\n";}
                if (opcao_turma=="0"){
                    for (auto i = estudantes_.begin(); i!= estudantes_.end(); i++) {
                        for (auto j = i->getTurmas().begin(); j!=i->getTurmas().end(); j++){
                            std::string code_disciplina = j->getCodUC();
                            if (code_disciplina == opcao_disciplina){
                                std::cout<<i->getCodEstudante()<<"\t"<< i->getNome()<<"\n";

                            }
                        }
                    }
                    break;
                }
                for (auto i = estudantes_.begin(); i!= estudantes_.end(); i++) {
                    for (auto j = i->getTurmas().begin(); j!=i->getTurmas().end(); j++){
                        std::string code_turma = j->getCodTurma();
                        std::string code_disciplina = j->getCodUC();
                        if (code_turma == opcao_turma && code_disciplina == opcao_disciplina){
                            std::cout<<i->getCodEstudante()<<"\t"<< i->getNome()<<"\n";
                        }
                    }
                }
                break;
            }
            case 3:
                break;
            case 9:
                flag = !flag;
                break;
            default:
                exit(0);
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

