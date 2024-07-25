#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customgraphicsview.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onColorButtonClicked();
    // void onColorButton_2Clicked();

private:
    Ui::MainWindow *ui;
    CustomGraphicsView *customView;
    QGraphicsScene *scene;
    QColor selectedColor;
    // QColor selectedColor_2;
};

#endif // MAINWINDOW_H
