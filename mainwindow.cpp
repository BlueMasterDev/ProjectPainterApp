#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QPen>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , selectedColor(Qt::yellow)
    // , selectedColor_2(Qt::yellow)
{
    ui->setupUi(this);

    customView = new CustomGraphicsView(this);
    scene = new QGraphicsScene(this);
    customView->setScene(scene);

    ui->mainLayout->replaceWidget(ui->graphicsView, customView);

    connect(ui->penColorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    // connect(ui->toolButton_2, &QPushButton::clicked, this, &MainWindow::onColorButton_2Clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(selectedColor, this, "Choose Color");

    if (color.isValid()) {
        selectedColor = color;
        ui->penColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        //dynamic_cast<CustomGraphicsView*>(ui->graphicsView)->setPenColor(color);
        customView->setPenColor(color);
    }
}

// void MainWindow::onColorButton_2Clicked()
// {
//     QColor color = QColorDialog::getColor(selectedColor_2, this, "Choose Color");

//     if (color.isValid()) {
//         selectedColor_2 = color;
//         ui->toolButton_2->setStyleSheet(QString("background-color: %1").arg(color.name()));
//         dynamic_cast<CustomGraphicsView*>(ui->graphicsView)->setPenColor(color);
//     }
// }

void MainWindow::on_penWidthSpinBox_valueChanged(int arg1)
{
    //CustomGraphicsView* customView = dynamic_cast<CustomGraphicsView*>(ui->graphicsView);
    customView->setPenWidth(arg1);
}

void MainWindow::on_penWidthSpinBox_textChanged(const QString &arg1)
{
    //CustomGraphicsView* customView = dynamic_cast<CustomGraphicsView*>(ui->graphicsView);
    customView->setPenWidth(arg1.toInt());
}

