#include "customgraphicsview.h"

#include <QMouseEvent>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), drawing(false), currentShape(None), currentItem(nullptr)
{
    pen.setColor(Qt::black);
    pen.setWidth(5);
}

CustomGraphicsView::CustomGraphicsView(QColor defaultPenColor, int defaultPenWidth, int defaultPenStyleIndex, QWidget *parent)
    : QGraphicsView(parent), drawing(false), currentShape(None), currentItem(nullptr)
{
    pen.setColor(defaultPenColor);
    pen.setWidth(defaultPenWidth);
    pen.setStyle(static_cast<Qt::PenStyle>(defaultPenStyleIndex + 1)); // in Qt::PenStyle 0 is no pen so we don't use it
    pen.setDashOffset(qreal(defaultPenWidth));
}

void CustomGraphicsView::setPenColor(const QColor &color)
{
    pen.setColor(color);
}

void CustomGraphicsView::setPenWidth(int width)
{
    pen.setWidth(width);
    pen.setDashOffset(qreal(width));
}

void CustomGraphicsView::setPenStyle(int styleIndex)
{
    pen.setStyle(static_cast<Qt::PenStyle>(styleIndex + 1)); // in Qt::PenStyle 0 is no pen so we don't use it
}

void CustomGraphicsView::setDrawShape(DrawShape shape)
{
    currentShape = shape;
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = mapToScene(event->pos());

        switch (currentShape) {
        case Rectangle:
            currentItem = scene()->addRect(QRectF(lastPoint, lastPoint), pen);
            break;
        case Ellipse:
            currentItem = scene()->addEllipse(QRectF(lastPoint, lastPoint), pen);
            break;
        default:
            break;
        }
    }
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPointF currentPoint = mapToScene(event->pos());

        switch (currentShape) {
        case Pen:
            scene()->addLine(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y(), pen);
            lastPoint = currentPoint;
            break;
        case Rectangle:
            if (QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem*>(currentItem)) {
                rect->setRect(QRectF(lastPoint, currentPoint).normalized());
            }
            break;
        case Ellipse:
            if (QGraphicsEllipseItem *ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(currentItem)) {
                ellipse->setRect(QRectF(lastPoint, currentPoint).normalized());
            }
            break;
        default:
            break;
        }
    }
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        currentItem = nullptr;
    }
}
