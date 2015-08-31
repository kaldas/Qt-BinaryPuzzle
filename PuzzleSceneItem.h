#ifndef PUZZLESCENEITEM_H
#define PUZZLESCENEITEM_H

#include "PuzzlePiece.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsItem>

class PuzzleSceneItem : public QGraphicsItem
{
public:
    PuzzleSceneItem(PuzzlePiece *piece);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setBrushWhite();
    void setBrushBlack();
signals:
    void pieceValueChanged(int x, int y, int value);
private:
    std::string strValue;
    QBrush *brush;
    int value;
    bool isLocked;
    PuzzlePiece *piece;
    void setValueString(int i);
    void setValueFromInt(int value);
    void moveToNextValue();
};

#endif // PUZZLESCENEITEM_H
