#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CustomGraphicsView(QWidget *parent = nullptr);
    CustomGraphicsView(QColor defaultPenColor, int defaultpenWidth, QWidget *parent = nullptr);

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
    QColor penColor;
    int penWidth;
    Qt::PenStyle penStyle;
};

#endif // CUSTOMGRAPHICSVIEW_H
