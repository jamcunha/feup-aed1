#ifndef FEUP_AED1_TURMAH_H
#define FEUP_AED1_TURMAH_H

#include "UCTurma.h"
#include "Aula.h"

#include <list>

class TurmaH {
private:
    UCTurma turma_;
    std::list<Aula> horario_;

public:
    TurmaH(const UCTurma &turma);

    const UCTurma& getTurma() const;
    std::list<Aula> getHorario() const;

    void addAula(const Aula &aula);

    bool isCompatible(const TurmaH &horario) const;

    bool operator==(const TurmaH &turma) const;
    bool operator!=(const TurmaH &turma) const;
};

#endif //FEUP_AED1_TURMAH_H
