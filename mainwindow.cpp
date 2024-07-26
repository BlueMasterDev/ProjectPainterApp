/**
 * @file mainwindow.cpp
 * @brief Fichier pour la classe MainWindow
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QPen>


/**
 * @brief Constructeur de base de MainWindow
 * @param parent : widget parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , selectedColor(Qt::black)
    // , selectedColor_2(Qt::yellow)
{
    ui->setupUi(this);

    customView = new CustomGraphicsView(selectedColor,ui->penWidthSpinBox->value(), ui->penStyleComboBox->currentIndex(), this);
    scene = new QGraphicsScene(this);
    customView->setScene(scene);

    ui->mainLayout->replaceWidget(ui->graphicsView, customView);
    delete ui->graphicsView;
    ui->graphicsView = nullptr;

    connect(ui->penColorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    // connect(ui->toolButton_2, &QPushButton::clicked, this, &MainWindow::onColorButton_2Clicked);
}

/**
 * @brief Destructeur de base de MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

// -----------------------------------------------------------------------------------------------------------------
// Pen Properties

/**
 * @brief Action qui se déclenche lorsque l'on clique sur la zone de couleur du crayon, permet à l'utilisateur de choisir une couleur.
 */
void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(selectedColor, this, "Choose Color");

    if (color.isValid()) {
        selectedColor = color;
        ui->penColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        customView->setPenColor(color);
    }
}

/**
 * @brief Action qui se déclenche lorsque l'on incrémente ou décrémente le champs contenant la largeur du crayon.
 */
void MainWindow::on_penWidthSpinBox_valueChanged(int arg1)
{
    customView->setPenWidth(arg1);
}

/**
 * @brief Action qui se déclenche lorsque l'on change numériquement au clavier le champs contenant la largeur du crayon.
 */
void MainWindow::on_penWidthSpinBox_textChanged(const QString &arg1)
{
    customView->setPenWidth(arg1.toInt());
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la première couleur par défaut (violet)
 */
void MainWindow::on_colorButton_1_clicked()
{
    customView->setPenColor(QColor(85, 0, 127));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la deuxième couleur par défaut (violet-bleu)
 */
void MainWindow::on_colorButton_2_clicked()
{
    customView->setPenColor(QColor(50, 14, 127));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la troisuème couleur par défaut (bleu)
 */
void MainWindow::on_colorButton_3_clicked()
{
    customView->setPenColor(QColor(0, 0, 255));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la quatrième couleur par défaut (vert)
 */
void MainWindow::on_colorButton_4_clicked()
{
    customView->setPenColor(QColor(0, 255, 0));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la cinquième couleur par défaut (jaune)
 */
void MainWindow::on_colorButton_5_clicked()
{
    customView->setPenColor(QColor(255, 255, 0));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la sixième couleur par défaut (orange)
 */
void MainWindow::on_colorButton_6_clicked()
{
    customView->setPenColor(QColor(255, 85, 0));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la septième couleur par défaut (rouge)
 */
void MainWindow::on_colorButton_7_clicked()
{
    customView->setPenColor(QColor(255, 0, 0));
}

/**
 * @brief Action qui se déclenche lorque l'on change la combo box contenant le style du crayon [Solid, Dashed, Dotted, Dot Dashed]
 */
void MainWindow::on_penStyleComboBox_currentIndexChanged(int index)
{
    customView->setPenStyle(index);
}

// -----------------------------------------------------------------------------------------------------------------

// void MainWindow::onColorButton_2Clicked()
// {
//     QColor color = QColorDialog::getColor(selectedColor_2, this, "Choose Color");

//     if (color.isValid()) {
//         selectedColor_2 = color;
//         ui->toolButton_2->setStyleSheet(QString("background-color: %1").arg(color.name()));
//         dynamic_cast<CustomGraphicsView*>(ui->graphicsView)->setPenColor(color);
//     }
// }
