#ifndef FEUP_AED1_AULA_H
#define FEUP_AED1_AULA_H

#include <string>
/**
 * @brief Representa uma aula.
 */
class Aula{
    /**
     * @note Todas as aulas são retiradas do ficheiro schedule.zip.
     */
private:
    /**
     * @brief Dia da semana em que a aula é lecionada.
     */
    std::string dia_;
    /**
     * @brief Inicio da aula, guardado em float (10,30 -> 10h:30m).
     */
    float inicio_;
    /**
     * @brief Fim da aula, guardado em float (11,30 -> 11h:30m).
     */
    float fim_;
    /**
     * @brief Tipo de aula.
     */
    std::string tipo_;

public:
    //Construtores
    /**
     * Cria uma aula.
     * @param dia Dia da semana em que a aula é lecionada
     * @param inicio Inicio da aula
     * @param duracao Fim da aula
     * @param tipo Tipo de aula
     */
    Aula(const std::string &dia, const float inicio, const float duracao, const std::string &tipo);
    //"Getters"
    /**
     * @return Dia da semana em que a aula ocorre
     */
    std::string getDia() const;
    /**
     * @return Horas em que a aula começa, num float
     */
    float getInicio() const;
    /**
     * @return Horas em que a aula acaba, num float
     */
    float getFim() const;
    /**
     * @return Tipo de aula
     */
    std::string getTipo() const;
};

#endif //FEUP_AED1_AULA_H
