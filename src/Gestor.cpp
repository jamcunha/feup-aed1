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
        std::cout << "| 1 - Ordenar por nome                                 |\n";
        std::cout << "| 2 - Ordenar por codico estudante                     |\n";
        std::cout << "| 3 - Ordenar                                      |\n";
        std::cout << "| 4 -                                                  |\n";
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
            case 1:
                //set(ordenarNome);
                break;

            case 2:
                //set(ordenarCODUC);
                break;
            case 3:

                break;
            case 9:
                flag = !flag;
                break;
            default:
                exit(0);
        }
        std::cout<< "Numero Estudante | Nome";
        for (auto i = estudantes_.begin(); i!=estudantes_.end() ; i++){
            std::cout<<i->getCodEstudante()<<"\t"<< i->getNome()<<"\n";
        }
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
        std::cout << "| 3 -                                                  |\n";
        std::cout << "| 4 -                                                  |\n";
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

                for (auto i = estudantes_.begin(); i!= estudantes_.end(); i++) {
                    for (auto j = i->getTurmas().begin(); j!=i->getTurmas().end(); j++){
                        std::string code_turma = j->getCodTurma();
                        std::string code_disciplina = j->getCodUC();
                        if (code_turma == opcao_turma && code_disciplina == opcao_disciplina){
                            std::cout<<i->getCodEstudante()<<"\t"<< i->getNome()<<"\n";
                        }
                    }
                }
                break;}
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



