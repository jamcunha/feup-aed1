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
            break;
        case 2:
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
        std::cout << "| 3 - Ordenar por                                      |\n";
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
                break;
            case 2:
                break;
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


