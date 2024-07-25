#include "customgraphicsview.h"

#include <QMouseEvent>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), drawing(false), penColor(Qt::black), penWidth(5)
{
}

CustomGraphicsView::CustomGraphicsView(QColor defaultPenColor, int defaultpenWidth, QWidget *parent)
    : QGraphicsView(parent), drawing(false), penColor(defaultPenColor), penWidth(defaultpenWidth)
{
    penStyle = Qt::SolidLine;
}

void CustomGraphicsView::setPenColor(const QColor &color)
{
    penColor = color;
}

void CustomGraphicsView::setPenWidth(int width)
{
    penWidth = width;
}

void CustomGraphicsView::setPenStyle(int styleIndex)
{
    penStyle = static_cast<Qt::PenStyle>(styleIndex + 1); // in Qt::PenStyle 0 is no pen so we don't use it
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = mapToScene(event->pos());
    }
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPointF currentPoint = mapToScene(event->pos());
        QPen pen(penColor, penWidth);
        pen.setStyle(penStyle);
        scene()->addLine(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y(), pen);
        lastPoint = currentPoint;
    }
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}
