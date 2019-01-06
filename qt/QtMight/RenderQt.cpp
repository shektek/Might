#include <QPainter>
#include "RenderQt.h"
#include "ui_renderqt.h"

RenderQt::RenderQt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RenderQt)
{
    ui->setupUi(this);

    //_currentMap = nullptr;
    //_highlights = nullptr;
    _mapReady = false;
    _highlightsReady = false;

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

void RenderQt::SetBattleMap(BattleMap map)
{
    //blind map change for now...
    _currentMap = map;
    _mapReady = true;
    //this->repaint();
}

void RenderQt::SetSubmap(NavigableGrid submap)
{
    _highlights = submap;
    _highlightsReady = true;
    //this->repaint();
}

void RenderQt::paintEvent(QPaintEvent *)
{
    if(_mapReady)
    {
        DrawGrid(Point2D(0, 0), Point2D(size().width(), size().height()), 14, 8);

        DrawImage(Point2D(20,20), "../../data/images/sword_rightfacing.png");
    }

    if(_highlightsReady)
    {
        DrawSubmapHighlights(_highlights);
    }
}

void RenderQt::DrawImage(Point2D position, std::string imageLocation)
{
    QPainter painter(this);
    QPixmap item = QPixmap(imageLocation.c_str());

    painter.drawPixmap(position.x, position.y, 20, 20, item);
    painter.end();
}

void RenderQt::DrawGrid(Point2D windowOrigin, Point2D windowEnd, int columns, int rows)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(Qt::black, 1));

    double xLength = windowEnd.x - windowOrigin.x;
    double yLength = windowEnd.y - windowOrigin.y;
    double xSpacing = xLength / (double)columns;
    double ySpacing = yLength / (double)rows;

    //awkward but this needs to resize the battlemaps tiles after getting the above
    //TODO: it might be worth investigating whether there's a better way than doing this
    if(_tileWidth != xSpacing || _tileHeight != ySpacing)
    {
        _tileWidth = xSpacing;
        _tileHeight = ySpacing;
        _currentMap.RescaleTiles(xSpacing, ySpacing);
    }

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

void RenderQt::DrawSubmapHighlights(NavigableGrid submap)
{
//    if(submap != nullptr)
    {
        QPainter painter(this);
        painter.setPen(QPen(Qt::blue, 1));

        for(int yi = 0; yi < submap.GetWidth(); yi++)
        {
            for(int xi = 0; xi < submap.GetHeight(); xi++)
            {
                TileFloodNode *tile = submap.GetTile(xi, yi);

                //get the position and size
                if(tile != nullptr)
                {
                    Point2D pos = tile->tile->GlobalBottomLeft();
                    short width = tile->tile->GetWidth();
                    short height = tile->tile->GetHeight();

                    painter.drawRect(pos.x, pos.y, width, height);
                }
            }
        }

        painter.end();
    }
}
