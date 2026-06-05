#ifndef NIVEL2_H
#define NIVEL2_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include "nivel.h"
#include "jugador.h"

class Nivel2 : public QGraphicsView, public Nivel
{
    Q_OBJECT

public:
    explicit Nivel2(QWidget *parent = nullptr);

    void iniciar();
    void actualizar();
    void controlarJugador(QKeyEvent *evento);
    void cambiarJugador();
    void pasarBalon();
    void lanzarBalon();
    void robarBalon();
    void moverIA();
    void verificarPunto();

protected:
    void keyPressEvent(QKeyEvent *evento);
    void keyReleaseEvent(QKeyEvent *evento);

private:
    Jugador *equipo[3];
    Jugador *rival[3];
    Jugador *actual;
    int puntaje;
    float gravedad;

    QGraphicsScene      *escenaN2;
    QGraphicsPixmapItem *fondoN2;
    QTimer              *timerJuegoN2;
    QTimer              *timerIA;

    int aroDerX = 1320, aroDerY = 460;   // aro azules
    int aroIzqX = 255,  aroIzqY = 450;   // aro rojos

    bool modoNivel2;

    int puntajeRival;
    QGraphicsTextItem *textoMarcador;

private slots:
    void gameLoop();
    void moverIASlot();

    void resetearJugadores();

};

#endif // NIVEL2_H
