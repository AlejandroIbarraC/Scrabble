//
// Created by parallels on 4/1/19.
//

#include "draggablerectitem.h"

DraggableRectItem::DraggableRectItem(QGraphicsItem* parent):
        QGraphicsRectItem(parent), m_dragged(false) {
    setFlags(QGraphicsItem::ItemIsSelectable|
             QGraphicsItem::ItemIsMovable);
}

void DraggableRectItem::setAnchorPoint(const QPointF &anchorPoint) {
    this->anchorPoint = anchorPoint;
}

void DraggableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    m_dragged = true;
    QGraphicsRectItem::mouseMoveEvent(event);
}

void DraggableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(m_dragged){
        QList<QGraphicsItem*> colItems = collidingItems();
        if(colItems.isEmpty())
            this->setPos(anchorPoint);
        else {
            QGraphicsItem* closestItem = colItems.at(0);
            qreal shortestDist = 100000;
                    foreach(QGraphicsItem* item, colItems){
                    QLineF line(item->sceneBoundingRect().center(),
                                this->sceneBoundingRect().center());
                    if(line.length() < shortestDist){
                        shortestDist = line.length();
                        closestItem = item;
                    }
                }
            if (closestItem->acceptDrops() == false) {
                this->setPos(closestItem->scenePos());
            } else {
                this->setPos(anchorPoint);
            }
        }
        m_dragged = false;
    }
    QGraphicsRectItem::mouseReleaseEvent(event);
}
