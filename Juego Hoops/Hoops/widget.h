#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>
#include "nivel1.h"
#include "nivel2.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void mostrarInicio();
    void iniciarNivel1();
    void iniciarNivel2();



private:
    Ui::Widget *ui;

    QGraphicsScene *sceneInicio;
    QGraphicsPixmapItem *bgInicio;

    QMediaPlayer *musicaInicio;

    QPushButton *btnPlay;


    Nivel1 *nivel1;

    Nivel2 *nivel2;

};

#endif // WIDGET_H
