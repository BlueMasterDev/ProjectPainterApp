#include "customgraphicsview.h"

#include <QMouseEvent>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), drawing(false)
{
    pen.setColor(Qt::black);
    pen.setWidth(5);
}

CustomGraphicsView::CustomGraphicsView(QColor defaultPenColor, int defaultPenWidth, int defaultPenStyleIndex, QWidget *parent)
    : QGraphicsView(parent), drawing(false)
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

// -----------------------------------------------------------------------------------------------------------------
// Drag and Drop properties

/**
 * @brief Drag Enter Event
 * @param QDragEnterEvent *event - évènement de QDragEnterEvent
*/
void CustomGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
/**
 * L'évènement du DragEnter est acceptée et doit être exécutée
*/
    event->accept();
    event->acceptProposedAction();
}

/**
 * @brief Drag Leave Event
 * @param QDragLeaveEvent *event - évènement de la classe QDragLeaveEvent
*/
void CustomGraphicsView::dragLeaveEvent(QDragLeaveEvent *event)
{
/**
 * L'évènement du DragLeave est acceptée et doit être exécutée
*/
    event->accept();
}

/**
 * @brief Drag Move Event
 * @param QDragMoveEvent *event - évènement de la classe QDragMoveEvent
*/
void CustomGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
/**
 * L'évènement du DragMove est acceptée et doit être exécutée
*/
    event->accept();
    event->acceptProposedAction();
}

/**
 * @brief Drop Event
 * @param QDropEvent *event - évènement de la classe QDropEvent
*/
void CustomGraphicsView::dropEvent(QDropEvent *event)
{
    if (event->source() == this) return;
/**
 * Utilisation de l'item drag et conversion de la position du curseur à la position de la scène
*/
    QListWidget *list = qobject_cast<QListWidget*>(event->source());
    QString text = list->currentItem()->text();
    QPointF position = mapToScene(event->position().toPoint());

/**
 * Ajout des différentes formes ou dessins selon le texte contenu dans l'item
*/
    if (text == "Learn")
    {
        QPixmap pixmap(":/images/images/quick.png");
        if (!pixmap.isNull()) {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            item->setPos(position);
            scene()->addItem(item);
            item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        }
    }
    else if (text == "Rectangle")
    {
        QGraphicsItem *item = nullptr;
        item = scene()->addRect(position.x(), position.y(), 100, 50, pen, QBrush(Qt::blue));
        item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        scene()->addItem(item);
    }
    else if (text == "Ellipse")
    {
        QGraphicsItem *item = nullptr;
        item = scene()->addEllipse(position.x(), position.y(), 100, 50, pen, QBrush(Qt::blue));
        item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        scene()->addItem(item);
    }
    else if (text == "Star")
    {
        QGraphicsItem *item = nullptr;
        QPolygonF star;
        star << QPointF(0, 40) << QPointF(20, 40) << QPointF(30, 0)
             << QPointF(40, 40) << QPointF(60, 40) << QPointF(45, 60)
             << QPointF(50, 100) << QPointF(30, 75) << QPointF(10, 100)
             << QPointF(15, 60) << QPointF(0, 40);
        item = scene()->addPolygon(star, pen, QBrush(Qt::yellow));
        item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        item->setPos(position);
        scene()->addItem(item);
    }

    event->acceptProposedAction();
}


