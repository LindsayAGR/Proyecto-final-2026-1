#ifndef NIVEL1_H
#define NIVEL1_H

#include <QGraphicsView>
#include <QKeyEvent>
#include "nivel.h"
#include "jugador.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include "obstaculo.h"
#include <cstdlib>
#include <ctime>
#include <QPushButton>

class Nivel1 : public QGraphicsView, public Nivel
{
    Q_OBJECT


public:
    explicit Nivel1(QWidget *parent = nullptr);

    void iniciar()          override;
    void actualizar()       override;
    void controlarJugador(QKeyEvent *evento);
    bool faseLanzamiento;
    void irNivel2();

protected:
    void keyPressEvent(QKeyEvent *evento)   override;
    void keyReleaseEvent(QKeyEvent *evento) override;

private:
    Jugador *jugador;


    QGraphicsPixmapItem *bgImageFon1, *bgImageFon2;

    QGraphicsScene *escena;
    QTimer *bgTimer, *spawnTimer;

    int contadorSpawn;
    QPushButton *btnReiniciar;

    //vidas
    int vidas;
    int tiempoRestante;
    QTimer *timerCronometro, *timerLanzamiento, *timerTexto;
    QGraphicsTextItem *textoTiempo, *txtVictoria;
    QGraphicsPixmapItem *vida1, *vida2, *vida3, *aro;

    Obstaculo *obstaculos[20];
    int cantObstaculos;

    bool juegoTerminado;
    bool lanzando;

    QPushButton *btnNivel2;



private slots:
    void gameLoop();
    void moverFondo();

    void spawnObstaculo();
    void mostrarGameOver();
    void reiniciar();

    void actualizarCronometro();
    void tiempoAgotado();
    void actualizarVidas();
    void eliminarObstaculo(Obstaculo *obs);

    void nivelCompletado();
    void lanzamientoFallido();
    void actualizarLanzamiento();
    void restarVidaBalon();

signals:
    void pasarNivel2();
};

#endif // NIVEL1_H
