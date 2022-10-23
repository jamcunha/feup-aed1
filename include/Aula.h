#ifndef FEUP_AED1_AULA_H
#define FEUP_AED1_AULA_H

#include <string>

class Aula {
private:
    std::string dia_;
    float inicio_;
    float fim_;
    std::string tipo_;

public:
    Aula(const std::string &dia, const float inicio, const float duracao, const std::string &tipo);

    std::string getDia() const;
    float getInicio() const;
    float getFim() const;
    std::string getTipo() const;
};

#endif //FEUP_AED1_AULA_H
