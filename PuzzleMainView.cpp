
#include "PuzzleMainView.h"
#include "ui_PuzzleMainView.h"
#include <ctime>
#include <QPrinter>
#include <QDialog>
#include <QPrintDialog>
PuzzleMainView::PuzzleMainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PuzzleMainView)
{
    ui->setupUi(this);
    this->createGame(6);
    scene->resetColorToWhite();
    scene->plotBoard();
    scene->resetSceneRect();
    setResultText("Welcome to Binary Puzzle");

    ui->comboBoxLevel->addItem("Easy");
    ui->comboBoxLevel->addItem("Medium");
    ui->comboBoxLevel->addItem("Hard");

    //PuzzleBook *book = new PuzzleBook();
    //book->saveNewGame(puzzle);
}

PuzzleMainView::~PuzzleMainView()
{
    delete ui;
    delete scene;
}

void PuzzleMainView::setResultText(std::string message)
{
    ui->labelMessage->setText(QString::fromStdString(message));
}

void PuzzleMainView::setResultTextQs(QString message)
{
    ui->labelMessage->setText(message);
}


void PuzzleMainView::createGame(int size)
{
    puzzle = new PuzzleGame(size);
    scene = new PuzzleScene(this);
    scene->setPuzzleGame(puzzle);
    //scene->setSceneRect(0,0,400,400);
    ui->graphicsView->setScene(scene);
}

void PuzzleMainView::clearGame()
{
    delete scene;
    delete puzzle;
}

void PuzzleMainView::on_buttonSolve_clicked()
{
    setResultText("Solving game...");
    scene->clear();

    if(puzzle->solveRandom())
        setResultText("The board was solved by recursive backtracking.");
    else
        setResultText("The board could not be solved.");

    scene->plotBoard();
}

void PuzzleMainView::on_buttonLight_clicked()
{
    if(ui->buttonLight->text().toStdString() == "Light Off")
    {
        ui->buttonLight->setText(QString::fromStdString("Light On"));
        scene->resetColorToBlack();
    }
    else
    {
        ui->buttonLight->setText(QString::fromStdString("Light Off"));
        scene->resetColorToWhite();
    }
    scene->plotBoard();
}

void PuzzleMainView::on_buttonCheck_clicked()
{
    setResultText(puzzle->checkVictory());
}

int PuzzleMainView::getDifficultyPercentage()
{
    int diff = 0;

    if(ui->comboBoxLevel->currentText() == "Hard")
        diff = 35;
    else if(ui->comboBoxLevel->currentText() == "Medium")
        diff = 45;
    else if(ui->comboBoxLevel->currentText() == "Easy")
        diff = 65;

    return diff;
}

void PuzzleMainView::on_buttonGenerator_clicked()
{
    int size = ui->textSize->text().toInt();

    if((size % 2) != 0 || size == 0)
    {
        setResultText("The size must be a positive even number.");
        return;
    }

    clearGame();
    createGame(size);

    setResultText("Solving game...");
    scene->clear();

    if(puzzle->createNewGame(getDifficultyPercentage()))
    {
        setResultText("The game was created by random recursive backtracking.");
    } else {
        setResultText("The board could not be created.");
    }

    //puzzle->obfuscatePuzzle(10);
    scene->plotBoard();
}

void PuzzleMainView::on_buttonHints_clicked()
{
    puzzle->solveHint();
    scene->clear();
    scene->plotBoard();

    setResultText("You got a hint!");
}

void PuzzleMainView::on_buttonClear_clicked()
{
    QPrinter printer;
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);
        scene->render(&painter);
    }
}
