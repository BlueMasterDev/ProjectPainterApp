/**
 * @file mainwindow.h
 * @brief Fichier pour la classe MainWindow
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customgraphicsview.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/**
 * @class MainWindow
 * @brief Classe pour la fenêtre de l'application qui est dérivée de la classe QMainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Pen Properties
    void onColorButtonClicked();
    void on_penWidthSpinBox_valueChanged(int arg1);
    void on_penWidthSpinBox_textChanged(const QString &arg1);
    void on_colorButton_1_clicked();
    void on_colorButton_2_clicked();
    void on_colorButton_3_clicked();
    void on_colorButton_4_clicked();
    void on_colorButton_5_clicked();
    void on_colorButton_6_clicked();
    void on_colorButton_7_clicked();
    void on_penStyleComboBox_currentIndexChanged(int index);

    // void onColorButton_2Clicked();

private:
    Ui::MainWindow *ui;
    CustomGraphicsView *customView;
    QGraphicsScene *scene;
    QColor selectedColor;
    // QColor selectedColor_2;
};

#endif // MAINWINDOW_H
