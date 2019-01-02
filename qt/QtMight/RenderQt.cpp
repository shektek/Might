#include <QPainter>
#include "RenderQt.h"
#include "ui_renderqt.h"

RenderQt::RenderQt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RenderQt)
{
    ui->setupUi(this);

    //this should be a splash screen to begin with
    QPixmap bkgnd("../../data/images/field.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

RenderQt::~RenderQt()
{
    delete ui;
}

void RenderQt::paintEvent(QPaintEvent *)
{
    DrawGrid(Point2D(0, 0), Point2D(size().width(), size().height()), 14, 8);

    DrawImage(Point2D(20,20), "../../data/images/sword_rightfacing.png");
}

void RenderQt::DrawImage(Point2D position, std::string imageLocation)
{
    QPainter painter(this);
    QPixmap item = QPixmap(imageLocation.c_str());

    painter.drawPixmap(position.x, position.y, 20, 20, item);
}

//todo: make this a texture
void RenderQt::DrawGrid(Point2D windowOrigin, Point2D windowEnd, int columns, int rows)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(Qt::black, 1));

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
