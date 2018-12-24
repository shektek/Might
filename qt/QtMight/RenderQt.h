#ifndef RENDERQT_H
#define RENDERQT_H

#include <QMainWindow>
#include <QImage>
#include "../../Point2D.h"

namespace Ui {
class RenderQt;
}

class RenderQt : public QMainWindow
{
    Q_OBJECT

public:
    explicit RenderQt(QWidget *parent = 0);
    ~RenderQt();

    void DrawGrid(Point2D windowOrigin, Point2D windowEnd, int columns, int rows);

private:
    Ui::RenderQt *ui;
    QImage *gridImage;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // RENDERQT_H
