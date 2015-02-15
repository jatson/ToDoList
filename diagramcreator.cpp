#include "diagramcreator.h"

DiagramCreator::DiagramCreator(QObject *parent) : QObject(parent)
{
    m_scene = new QGraphicsScene(this);
}

DiagramCreator::~DiagramCreator()
{
    delete m_scene;
}

void DiagramCreator::drawDiagram(QList<QSharedPointer<Task> > tasks)
{
#ifdef DEBUG
    qDebug() << "drawDiagram function called...";
#endif

    qDeleteAll(m_scene->items()); // this line will force the diagram re-draw (delete the previos)

    m_scene->setSceneRect(0,0,200,160);

    QFont font("Serif");
    font.setWeight(QFont::Bold);

    QColor bgColor(250, 255, 250);
    QBrush bgBrush(bgColor);
    m_scene->setBackgroundBrush(bgBrush);

    QColor startColor(145, 232, 66);
    QColor endColor(210, 255, 82);

    QLinearGradient linearGradient(QPointF(0, 0), QPointF(200, 0));
    linearGradient.setColorAt(0, startColor);
    linearGradient.setColorAt(0.9, endColor);

    QColor textColor(109, 0, 25);

    QMap<int, QString> bestCat = bestCategories(tasks, 3);
    QMapIterator<int, QString> ji(bestCat);
    ji.toBack();

    float diagramUnit = 200 / ji.peekPrevious().key();

    m_rect1 = m_scene->addRect(0, 0, diagramUnit*ji.peekPrevious().key(), 50, Qt::NoPen, linearGradient);
    m_category1 = m_scene->addText(ji.previous().value(), font);
    m_category1->setPos(10,10);
    m_category1->setDefaultTextColor(textColor);

    m_rect2 = m_scene->addRect(0, 55, diagramUnit*ji.peekPrevious().key(), 50, Qt::NoPen, linearGradient);
    m_category2 = m_scene->addText(ji.previous().value(), font);
    m_category2->setPos(10,65);
    m_category2->setDefaultTextColor(textColor);

    m_rect3 = m_scene->addRect(0, 110, diagramUnit*ji.peekPrevious().key(), 50, Qt::NoPen, linearGradient);
    m_category3 = m_scene->addText(ji.previous().value(), font);
    m_category3->setPos(10,120);
    m_category3->setDefaultTextColor(textColor);
}

QGraphicsScene *DiagramCreator::scene() const
{
    return m_scene;
}

void DiagramCreator::setScene(QGraphicsScene *scene)
{
    m_scene = scene;
}

QMap<int, QString> DiagramCreator::bestCategories(QList<QSharedPointer<Task> > tasks, int num)
{
    QHash<QString, int> categoriesUsage;
    for (int i = 0; i < tasks.size(); ++i)
    {
        QString cat = tasks[i]->category();
        if (categoriesUsage.contains(cat)) categoriesUsage[cat]++;
        else categoriesUsage[cat] = 1;
    }
    QMap<int, QString> categoriesOrdered;
    QHash<QString, int>::const_iterator ci = categoriesUsage.constBegin();
    while(ci != categoriesUsage.constEnd())
    {
        categoriesOrdered.insertMulti(ci.value(), ci.key()); // need to use insertMulti, 'coz for one key can belong more values
        ++ci;
    }

    QMap<int, QString>::iterator it = categoriesOrdered.begin();
    while(categoriesOrdered.size() > num) it = categoriesOrdered.erase(it);
    return categoriesOrdered;
}
