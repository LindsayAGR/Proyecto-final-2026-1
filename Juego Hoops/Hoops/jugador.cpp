#include "jugador.h"

Jugador::Jugador(QPixmap pixmap)
    : QGraphicsPixmapItem(pixmap)
{
    // posicion inicial
    x = 100;
    y = 500;

    // velocidades
    velocidadX = 5;
    velocidadY = 0;

    // estados
    saltando = false;
    tieneBalon = true;

    // gravedad
    gravedad = 0.5;

    // posicion en pantalla
    setPos(x, y);
}

void Jugador::moverIzquierda()
{
    x -= velocidadX;
    setPos(x, y);
}

void Jugador::moverDerecha()
{
    x += velocidadX;
    setPos(x, y);
}

void Jugador::saltar()
{
    if(!saltando)
    {
        velocidadY = -12;
        saltando = true;
    }
}

void Jugador::lanzar()
{

}

void Jugador::actualizar()
{
    // gravedad
    velocidadY += gravedad;

    // mover en Y
    y += velocidadY;

    // piso
    if(y >= 500)
    {
        y = 500;
        velocidadY = 0;
        saltando = false;
    }

    setPos(x, y);
}
