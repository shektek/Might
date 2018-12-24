#include <QPainter>
#include "RenderQt.h"
#include "ui_renderqt.h"

RenderQt::RenderQt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RenderQt)
{
    ui->setupUi(this);
}

RenderQt::~RenderQt()
{
    delete ui;
}

void RenderQt::paintEvent(QPaintEvent *)
{
    DrawGrid(Point2D(0, 0), Point2D(size().width(), size().height()), 14, 8);
}

void RenderQt::DrawGrid(Point2D windowOrigin, Point2D windowEnd, int columns, int rows)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(Qt::black, 2));

    double xLength = windowEnd.x - windowOrigin.x;
    double yLength = windowEnd.y - windowOrigin.y;
    double xSpacing = xLength / (double)columns;
    double ySpacing = yLength / (double)rows;

    for(int x = 0; x < columns; x++)
    {
        QPoint begin((windowOrigin.x + xSpacing * x), (windowOrigin.y));
        QPoint final((windowOrigin.x + xSpacing * x), (windowOrigin.y + yLength));

        painter.drawLine(begin, final);
    }

    for(int y = 0; y < rows; y++)
    {
        QPoint begin(windowOrigin.x, (windowOrigin.y + ySpacing * y));
        QPoint final(windowOrigin.x + xLength, (windowOrigin.y + ySpacing * y));

        painter.drawLine(begin, final);
    }

    painter.end();
}
