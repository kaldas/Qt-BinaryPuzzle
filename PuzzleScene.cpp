#include "PuzzleScene.h"

///
/// \brief PuzzleScene::PuzzleScene
/// \param parent
///
/// Default Qt constructor
///
PuzzleScene::PuzzleScene(QObject *parent)
    : QGraphicsScene(parent)
{
    light = true;
}

void PuzzleScene::setPuzzleGame(PuzzleGame *puzzle)
{
    this->puzzle = puzzle;
}

///
/// \brief PuzzleScene::plotBoard
///
///        Draws the binary puzzle board into the scene.
///
void PuzzleScene::plotBoard()
{
    clear();
    for(int i = 0;i < puzzle->getSize();i++)
    {
        for(int j = 0;j < puzzle->getSize();j++)
        {
            PuzzleSceneItem *newItem = new PuzzleSceneItem(puzzle->getPieceByXy(i,j));

            setSceneItemColor(newItem);

            newItem->setPos(25*i,25*j);
            this->addItem(newItem);
        }
    }
}

///
/// \brief PuzzleScene::setSceneItemColor
/// \param item
///
/// Sets the color of a PuzzleSceneItem.
///
void PuzzleScene::setSceneItemColor(PuzzleSceneItem *item)
{
    if(light)
        item->setBrushWhite();
    else
        item->setBrushBlack();
}

///
/// \brief PuzzleScene::resetColorToWhite
///
/// Resets the background color to white.
///
void PuzzleScene::resetColorToWhite()
{
    this->setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));
    light = true;
}

///
/// \brief PuzzleScene::resetColorToBlack
///
/// Resets the background color to black.
///
void PuzzleScene::resetColorToBlack()
{
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    light = false;
}

///
/// \brief PuzzleScene::resetSceneRect
///
/// Resets the scene dimensions
///
void PuzzleScene::resetSceneRect()
{
    this->setSceneRect(0,0,puzzle->getSize()*20,puzzle->getSize()*20);
}
