#include "nivel.h"

Nivel::Nivel()
{
    balonX   = 0;
    balonY   = 0;
    gravedad = 9.8;
    balon    = nullptr;
    escena   = nullptr;
    timerJuego = nullptr;
}

Nivel::~Nivel()
{
}

void Nivel::aplicarGravedad(float &velocidadY, float &y)
{
    velocidadY += gravedad;
    y          += velocidadY;
}
