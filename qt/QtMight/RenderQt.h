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
#include "../../NavigableGrid.h"
#include "../../BattleMap.h"

namespace Ui {
class RenderQt;
}

class RenderQt : public QMainWindow
{
        Q_OBJECT

    public:
        RenderQt(QWidget *parent = 0);
        virtual ~RenderQt();

        void DrawGrid(Point2D windowOrigin, Point2D windowEnd, int columns, int rows);
        void DrawImage(Point2D position, std::string imageLocation);
        void DrawSubmapHighlights(NavigableGrid submap);

    public slots:
        void SetBattleMap(BattleMap map);
        void SetSubmap(NavigableGrid submap);

    private:
        Ui::RenderQt *ui;
        QGraphicsScene scene;
        double _tileWidth;
        double _tileHeight;
        BattleMap _currentMap;
        NavigableGrid _highlights;

        bool _mapReady;
        bool _highlightsReady;

    protected:
        void paintEvent(QPaintEvent *);
};

#endif // RENDERQT_H
