#include "graphics_save_load.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPainter>

Graphics_Save_Load::Graphics_Save_Load(QGraphicsView *view)
    : graphicsView(view), scene(view->scene())
{
}
/**
 * @param QString &filePath -> chemin du fichier charger
 * @brief Save the drawing area
*/
bool Graphics_Save_Load::saveScene(const QString &filePath)
{
    if (!scene) {
        return false;
    }
/**
 * Déterminer la zone de la scène à capturer
*/
    QRectF sceneRect = scene->sceneRect();
/**
 * Créer une image de la taille de la scène
*/
    QImage image(sceneRect.size().toSize(), QImage::Format_ARGB32);
/**
 * Remplir avec une couleur blanche
*/
    image.fill(Qt::white);
/**
 * Créer un painter pour dessiner la scène dans l'image
*/
    QPainter painter(&image);
    scene->render(&painter);
    painter.end();
/**
 * Sauvegarder l'image dans le fichier spécifié
*/
    return image.save(filePath);
}
/**
 * @param QString &filePath - chemin du fichier à charger
 * @brief load Image
*/
bool Graphics_Save_Load::loadScene(const QString &filePath)
{
    if (!scene) {
        return false;
    }
/**
 * Charger l'image
*/
    QImage image(filePath);
    if (image.isNull()) {
        return false;
    }
/**
 * Effacer la scène actuelle
*/
    scene->clear();
/**
 * Ajouter l'image à la scène
*/
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);

    return true;
}
/**
 * @param QString &filePath chemin du fichier à ajouter
 * @brief Add Image to graphics
*/
bool Graphics_Save_Load::addImage(const QString &filePath)
{
    if (!scene) {
        return false;
    }
/**
 * Charger l'image
*/
    QImage image(filePath);
    if (image.isNull()) {
        return false;
    }
/**
 * Ajouter l'image à la scène
*/
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);

    return true;
}
