/**
 * @file customgraphicsview.h
 * @brief Fichier pour la classe CustomGraphicsView
 */

#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

/**
 * @class CustomGraphicsView
 * @brief Classe pour la zone de dessin qui est dérivée de la classe QGraphicsView
 */
class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CustomGraphicsView(QWidget *parent = nullptr);
    CustomGraphicsView(QColor defaultPenColor, int defaultPenWidth, int defaultPenStyleIndex, QWidget *parent = nullptr);

    void setPenColor(const QColor &color);
    void setPenWidth(int width);
    void setPenStyle(int styleIndex);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool drawing;
    QPointF lastPoint;
    QPen pen;
};

#endif // CUSTOMGRAPHICSVIEW_H
