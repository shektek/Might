#ifndef RENDERQT_H
#define RENDERQT_H

#include <vector>
#include <QMainWindow>
#include <QPixmap>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../../Point2D.h"

namespace Ui {
class RenderQt;
}

class RenderQt : public QMainWindow
{
    Q_OBJECT

public:
    RenderQt(QWidget *parent = 0);
    ~RenderQt();

    void DrawGrid(Point2D windowOrigin, Point2D windowEnd, int columns, int rows);
    void DrawImage(Point2D position, std::string imageLocation);

private:
    Ui::RenderQt *ui;
    QGraphicsScene scene;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // RENDERQT_H
