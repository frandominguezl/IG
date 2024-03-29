#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"


class LuzDireccional : public Luz
{
    protected:
    float alpha;
    float beta;

    public:
    const float PI = 3.14159265;
    LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
    void variarAnguloAlpha(float incremento) override;
    void variarAnguloBeta(float incremento) override;
    void calcularPosiciones();
};

#endif