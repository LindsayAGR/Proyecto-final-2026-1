#ifndef NIVEL1_H
#define NIVEL1_H

#include <QGraphicsView>
#include <QKeyEvent>
#include "nivel.h"
#include "jugador.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

class Nivel1 : public QGraphicsView, public Nivel
{
    Q_OBJECT

public:
    explicit Nivel1(QWidget *parent = nullptr);

    void iniciar()          override;
    void actualizar()       override;
    void controlarJugador(QKeyEvent *evento);



protected:
    void keyPressEvent(QKeyEvent *evento)   override;
    void keyReleaseEvent(QKeyEvent *evento) override;

private:
    Jugador *jugador;


    QGraphicsPixmapItem *bgImageFon1, *bgImageFon2;

    QGraphicsScene *escena;
    QTimer *bgTimer;

private slots:
    void gameLoop();
    void moverFondo();
};

#endif // NIVEL1_H
