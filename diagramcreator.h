#ifndef DIAGRAMCREATOR_H
#define DIAGRAMCREATOR_H

#include <QObject>
#include <QGraphicsScene>       /* The QGraphicsScene class provides a surface for managing a large number of 2D graphical items. */
#include <QGraphicsTextItem>    /* The QGraphicsTextItem class provides a text item that you can add to a QGraphicsScene to display formatted text. */
#include <QGraphicsRectItem>    /* The QGraphicsRectItem class provides a rectangle item that you can add to a QGraphicsScene. */

#include "task.h"
#include "defines.h"

class DiagramCreator : public QObject
{
    Q_OBJECT
private:
    QGraphicsScene *m_scene;
    QMap<int, QString> bestCategories(QList<QSharedPointer<Task> > tasks, int num);

    QGraphicsRectItem *m_rect1;
    QGraphicsRectItem *m_rect2;
    QGraphicsRectItem *m_rect3;
    QGraphicsTextItem *m_category1;
    QGraphicsTextItem *m_category2;
    QGraphicsTextItem *m_category3;

public:
    explicit DiagramCreator(QObject *parent = 0);
    ~DiagramCreator();

    void drawDiagram(QList<QSharedPointer<Task> > tasks);

    QGraphicsScene *scene() const;
    void setScene(QGraphicsScene *scene);

signals:

public slots:
};

#endif // DIAGRAMCREATOR_H
