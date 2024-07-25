/**
 * @file graphics_save_load.h
 * @brief Description de la classe graphics_save_load
*/

#ifndef GRAPHICS_SAVE_LOAD_H
#define GRAPHICS_SAVE_LOAD_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>

/**
 * @class Graphics_Save_Load
 * @brief classe qui sauvegarde et charge des fichiers existants
*/

class Graphics_Save_Load
{
public:
    explicit Graphics_Save_Load(QGraphicsView *view);

    bool saveScene(const QString &filePath);

    bool loadScene(const QString &filePath);

    bool addImage(const QString &filePath);

private:
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
};

#endif // GRAPHICS_SAVE_LOAD_H
