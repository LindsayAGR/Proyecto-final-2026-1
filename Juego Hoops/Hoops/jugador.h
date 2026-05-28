#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>

class Jugador : public QGraphicsPixmapItem
{
private:

    // posicion
    float x;
    float y;

    // velocidades
    float velocidadX;
    float velocidadY;

    // estados
    bool saltando;
    bool tieneBalon;

    // gravedad
    float gravedad;

public:

    // constructor
    Jugador(QPixmap pixmap);

    // movimiento
    void moverIzquierda();
    void moverDerecha();

    // acciones
    void saltar();
    void lanzar();

    // actualizar fisicas
    void actualizar();

};

#endif // JUGADOR_H
