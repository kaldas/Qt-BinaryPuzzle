#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H

class PuzzlePiece
{
public:
    PuzzlePiece();
    PuzzlePiece(int value);
    int getValue();
    int getX();
    int getY();
    bool isLocked();
    void setValue(int value);
    void setValue(int value, bool lock);
    void lockPiece();
    void setXy(int x, int y);
private:
    int x,y,value;
    bool lock;
};

#endif // PUZZLEPIECE_H
