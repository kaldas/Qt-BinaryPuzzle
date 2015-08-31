#ifndef PUZZLESCENE_H
#define PUZZLESCENE_H

#include<QGraphicsScene>
#include "PuzzleGame.h"
#include "PuzzleSceneItem.h"

class PuzzleScene : public QGraphicsScene
{
public:
    PuzzleScene();
    PuzzleScene(QObject *parent);
    void plotBoard();
    void setPuzzleGame(PuzzleGame *puzzle);
    void setLight(bool light);
    void resetSceneRect();
    void resetColorToWhite();
    void resetColorToBlack();
private:
    PuzzleGame *puzzle;
    bool light;
    void setSceneItemColor(PuzzleSceneItem *item);
};

#endif // PUZZLESCENE_H
