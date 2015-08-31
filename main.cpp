
#include "PuzzleMainView.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PuzzleMainView e;
    e.show();
    return a.exec();
}
