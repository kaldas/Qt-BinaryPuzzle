#include "PuzzleSceneItem.h"

///
/// \brief PuzzleSceneItem::PuzzleSceneItem
///
/// Default constructor.
/// Establishes a PuzzleSceneItem from a Puzzle Piece.
///
/// \param piece
///
PuzzleSceneItem::PuzzleSceneItem(PuzzlePiece *piece)
{
    this->piece = piece;
    this->setValueFromInt(piece->getValue());
    this->brush = new QBrush(Qt::white);
}

///
/// \brief PuzzleSceneItem::setBrushWhite
///
/// Sets the paint brush color to white.
///
void PuzzleSceneItem::setBrushWhite()
{
    brush->setColor(Qt::white);
    update();
}

///
/// \brief PuzzleSceneItem::setBrushBlack
///
/// Sets the paint brush color to black.
///

void PuzzleSceneItem::setBrushBlack()
{
    brush->setColor(Qt::black);
    update();
}

///
/// \brief PuzzleSceneItem::setValueFromInt
/// \param value An integer value containing a number from 0 to 2
///
/// Set the piece value that will be displayed to player
///

void PuzzleSceneItem::setValueFromInt(int value)
{
    this->piece->setValue(value);
    switch(value)
    {
        case 0:
            this->strValue = "0";
            break;
        case 1:
            this->strValue = "1";
            break;
        default:
            this->strValue = " ";
            break;
    }
}

///
/// \brief PuzzleSceneItem::moveToNextValue
///
/// Moves the piece value to the next value.
///
/// An empty piece becomes a zero.
/// If the value is one then the piece becomes empty.
///
void PuzzleSceneItem::moveToNextValue()
{
    if(piece->isLocked())
        return;

    if(piece->getValue() > 1)
        setValueFromInt(0);
    else
        setValueFromInt(piece->getValue() + 1);
}

///
/// \brief PuzzleSceneItem::paint
///
/// Draws the object in the scene.
///
/// \param painter
/// \param option
/// \param widget
///
void PuzzleSceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    painter->fillRect(rec,brush->color());
    painter->drawRect(rec);
    painter->drawText(10,17,QString::fromStdString(strValue));
}


///
/// \brief PuzzleSceneItem::mousePressEvent
///
/// Captures the event of the player pressing the piece.
///
/// \param event
///
void PuzzleSceneItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    moveToNextValue();
    update();
    QGraphicsItem::mousePressEvent(event);
}

///
/// \brief PuzzleSceneItem::boundingRect
///
/// The size of the piece.
///
/// \return
///

QRectF PuzzleSceneItem::boundingRect() const
{
    return QRectF(0,0,25,25);
}
