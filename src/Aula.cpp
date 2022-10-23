#include "../include/Aula.h"

Aula::Aula(const std::string &dia, const float inicio, const float duracao, const std::string &tipo): dia_(dia), inicio_(inicio), tipo_(tipo) {
    fim_ = inicio + duracao;
}

std::string Aula::getDia() const {
    return dia_;
}

float Aula::getInicio() const {
    return inicio_;
}

float Aula::getFim() const {
    return fim_;
}

std::string Aula::getTipo() const {
    return tipo_;
}
