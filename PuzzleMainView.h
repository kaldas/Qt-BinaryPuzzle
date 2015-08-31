#ifndef PUZZLEGAMEVIEW_H
#define PUZZLEGAMEVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include "PuzzleGame.h"
#include "PuzzleScene.h"
#include "PuzzleSceneItem.h"

namespace Ui {
class PuzzleMainView;
}

class PuzzleMainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit PuzzleMainView(QWidget *parent = 0);
    ~PuzzleMainView();

private slots:
    void on_buttonSolve_clicked();

    void on_buttonLight_clicked();

    void on_buttonCheck_clicked();

    void on_buttonGenerator_clicked();

    void on_buttonHints_clicked();

    void on_buttonClear_clicked();

private:
    Ui::PuzzleMainView *ui;
    PuzzleGame *puzzle = NULL;
    PuzzleScene *scene = NULL;
    void clearGame();
    void createGame(int size);
    void setResultText(std::string message);
    int getDifficultyPercentage();
    void setResultTextQs(QString message);
};

#endif // PUZZLEGAMEVIEW_H
