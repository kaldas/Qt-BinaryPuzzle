#include "PuzzlePiece.h"

PuzzlePiece::PuzzlePiece()
{
    this->value = 2;
    this->lock = false;
}

PuzzlePiece::PuzzlePiece(int value)
{
    this->value = value;
}

void PuzzlePiece::setValue(int value)
{
    this->value = value;
}

int PuzzlePiece::getValue()
{
    return this->value;
}

bool PuzzlePiece::isLocked()
{
    return this->lock;
}

void PuzzlePiece::lockPiece()
{
    this->lock = true;
}

int PuzzlePiece::getX()
{
    return x;
}

int PuzzlePiece::getY()
{
    return y;
}

void PuzzlePiece::setXy(int x, int y)
{
    this->x = x;
    this->y = y;
}

void PuzzlePiece::setValue(int value, bool lock)
{
    this->value = value;
    this->lock = lock;
}
