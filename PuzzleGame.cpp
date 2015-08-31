
#include "PuzzleGame.h"

///
/// \brief PuzzleGame::PuzzleGame
///
///        The default constructor is made innacessible
///        due to the lack of minimum arguments to implement this class
///
PuzzleGame::PuzzleGame() { /* private */ }

///
/// \brief PuzzleGame::PuzzleGame
/// \param size
///
///        This constructor contains the minimum requirements
///        for the implementation of this class
///
PuzzleGame::PuzzleGame(int size)
{
    srand(time(NULL));
    this->size = size;
    pieces = new PuzzlePiece*[getSize()];
    piecesTemplate = new PuzzlePiece*[getSize()];
    createPiecesDataStructure(this->pieces);
    createPiecesDataStructure(this->piecesTemplate);
}

///
/// \brief PuzzleGame::~PuzzleGame
///
/// Default destructor
///
PuzzleGame::~PuzzleGame()
{
    deleteAllPieces();
}

///
/// \brief PuzzleGame::deleteAllPieces
///
///        Deletes all data structures created by this class.
///
void PuzzleGame::deleteAllPieces()
{
    for (int i = 0; i < getSize(); i++)
    {
        delete [] pieces[i];
        delete [] piecesTemplate[i];
    }
    delete [] pieces;
    delete [] piecesTemplate;
}

///
/// \brief PuzzleGame::createPiecesDataStructure
///
/// \param newPieces the pointer to where the data structure will be created
///
void PuzzleGame::createPiecesDataStructure(PuzzlePiece **newPieces)
{
    for(int i = 0; i < getSize(); ++i)
    {
        newPieces[i] = new PuzzlePiece[getSize()];
        for(int j = 0;j < getSize();j++)
        {
            newPieces[i][j].setXy(i,j);
        }
    }
}
///
/// \brief PuzzleGame::copyPiecesToTemplate
///
/// Copies the solution of the game to the template.
///
void PuzzleGame::copyPiecesToTemplate()
{
    for(int i = 0;i < getSize(); i++)
    {
        for(int j = 0;j < getSize(); j++)
        {
            piecesTemplate[i][j].setValue(pieces[i][j].getValue());
        }
    }
}

///
/// \brief PuzzleGame::reloadPieceDataStructure
///
/// Deletes and recreates the data structures containing pieces.
///
void PuzzleGame::reloadPieceDataStructure()
{
    deleteAllPieces();
    pieces = new PuzzlePiece*[getSize()];
    piecesTemplate = new PuzzlePiece*[getSize()];
    createPiecesDataStructure(this->pieces);
    createPiecesDataStructure(this->piecesTemplate);
}

///
/// \brief PuzzleGame::createNewGame
///
/// Will try to create a new game in a recursive manner.
///
/// \param difficulty An integer from 0 to 100.
///                   This is the difficultu percentage of the game.
///
/// \return True if a game could be created
///
bool PuzzleGame::createNewGame(int difficulty)
{
    reloadPieceDataStructure();
    if(solveRandom())
    {
        obfuscatePuzzle((double) getSize() * getSize() / 4 / 100 * difficulty);
        if(isOnlyOneSolutionPossible())
        {
            clearAllUnlockedPieces();
            return true;
        }
    }
    return createNewGame(difficulty);
}

///
/// \brief PuzzleGame::isOnlyOneSolutionPossible
///
/// \return True if only one solution to the puzzle is possible.
///

bool PuzzleGame::isOnlyOneSolutionPossible()
{
    if(solveRecursiveOppositeToTemplate())
    {
        if(isPieceDifferentFromTemplate())
        {
            return true;
        }
    }

    return false;
}

///
/// \brief PuzzleGame::isPieceDifferentFromTemplate
///
/// Verifies if a piece from the differing solution created
/// is different from the initial solution.
///
/// \return It will return 'false' if a piece from the
///

bool PuzzleGame::isPieceDifferentFromTemplate()
{
    for(int i = 0;i < getSize(); i++)
    {
        for(int j = 0;j < getSize(); j++)
        {
            if(piecesTemplate[i][j].getValue() != pieces[i][j].getValue())
            {
                //std::cout << "New solution at " << i << "," << j << std::endl;
                return false;
            }
        }
    }
    return true;
}

///
/// \brief PuzzleGame::obfuscatePuzzle
///
/// Obfuscates the puzzle in four individual sections.
///
/// \param quantity a number from 0 to 100
///
void PuzzleGame::obfuscatePuzzle(int quantity)
{
    copyPiecesToTemplate();

    hidePiecesFromTo(0, getSize() / 2, quantity);
    hidePiecesFromTo(0, 0, quantity);
    hidePiecesFromTo(getSize() / 2, getSize() / 2, quantity);
    hidePiecesFromTo(getSize() / 2, 0, quantity);

    clearAllUnlockedPieces();
}

///
/// \brief PuzzleGame::clearAllUnlockedPieces
///
///        Sets all unlocked pieces to empty.
///
void PuzzleGame::clearAllUnlockedPieces()
{
    for(int i = 0;i < getSize(); i++)
    {
        for(int j = 0;j < getSize(); j++)
        {
            if(!pieces[i][j].isLocked())
            {
                pieces[i][j].setValue(2,false);
            }
        }
    }
}

void PuzzleGame::solveHint()
{
    int row,col;

    if(!findNextFreeSpace(row,col))
        return;

    pieces[row][col].setValue(piecesTemplate[row][col].getValue());
}

///
/// \brief PuzzleGame::hidePiecesFromTo
///
/// Hides pieces located in a desired area of the board.
///
/// \param fromX opening location in the grid
/// \param fromY closing location in the grid
/// \param quantity the quantity of pieces that will be obfuscated
///

void PuzzleGame::hidePiecesFromTo(int fromX, int fromY, int quantity)
{
    int limit = getSize() / 2;

    for(int i = 0;i < quantity;i++)
    {
        int x; int y;

        x = rand() % limit + fromX;
        y = rand() % limit + fromY;

        if(pieces[x][y].isLocked())
        {
            i--;
        } else {
            pieces[x][y].lockPiece();
        }
    }
}

///
/// \brief PuzzleGame::setEmptyPiece
///
/// Sets a piece to the empty value.
///
/// \param row
/// \param col
///
void PuzzleGame::setEmptyPiece(int row, int col)
{
    pieces[row][col].setValue(2);
}

///
/// \brief PuzzleGame::getValueByXy
/// \param x
/// \param y
/// \return returns the value of a piece by its location
///
int PuzzleGame::getValueByXy(int x, int y)
{
    return pieces[x][y].getValue();
}

///
/// \brief PuzzleGame::getPieceByXy
/// \param x
/// \param y
/// \return returns a piece by its location in the board
///
PuzzlePiece *PuzzleGame::getPieceByXy(int x, int y)
{
    return &pieces[x][y];
}

///
/// \brief PuzzleGame::getSize
/// \return the size of board of the puzzle
///
int PuzzleGame::getSize()
{
    return this->size;
}

///
/// \brief PuzzleGame::setDefaultPiece
///
///        Sets the default value of a piece.
///
/// \param value
/// \param x
/// \param y
/// \param lock
///
void PuzzleGame::setDefaultPiece(int value, int x, int y, bool lock)
{
    pieces[x][y].setValue(value, lock);
}

///
/// \brief PuzzleGame::solveRecursive
/// \return 'True' if the game can be solved.
///
bool PuzzleGame::solveRecursive()
{
    int row,col;

    if(!findNextFreeSpace(row,col)) // when solveRecursive() has ran successfully until there
        return true;                // are no more free spaces then the game has been solved

    for(int num = 0;num < 2;num++)
    {
        if(isRecursiveMovementValid(&PuzzleGame::solveRecursive,row,col,num))
            return true;
    }

    return false;
}

///
/// \brief PuzzleGame::solveRandom
/// \return 'True' if it can solve the game
///
bool PuzzleGame::solveRandom()
{
    int row,col;

    if(!findNextFreeSpace(row,col))
        return true;

    if(rand() % 2)
    {
        if(isMovementStartingByZeroValid(&PuzzleGame::solveRandom,row, col))
            return true;

    } else {
        if(isMovementStartingByOneValid(&PuzzleGame::solveRandom,row, col))
            return true;
    }

    return false;
}

///
/// \brief PuzzleGame::solveRecursiveOppositeToTemplate
/// \return 'true' if it can solve the game
///
bool PuzzleGame::solveRecursiveOppositeToTemplate()
{
    int row,col;

    if(!findNextFreeSpace(row,col))
        return true;

    if(pieces[row][col].getValue() == 0)
    {
        if(isMovementStartingByOneValid(&PuzzleGame::solveRecursiveOppositeToTemplate,row, col))
        {
            return true;
        }
    } else {
        if(isMovementStartingByZeroValid(&PuzzleGame::solveRecursiveOppositeToTemplate,row, col))
        {
            return true;
        }
    }

    return false;
}

///
/// \brief PuzzleGame::isRecursiveMovementValid
/// \param row the desired row where the movement will happen
/// \param col the desired column
/// \param num the value of the movement (either zero or one)
/// \return true if the recursive movement is valid
///
bool PuzzleGame::isRecursiveMovementValid(bool (PuzzleGame::*solver)(), int row, int col, int num)
{
    if(IsMovementLocallyPossible(row,col,num))
    {
        if((*this.*solver)())
            return true;

        setEmptyPiece(row,col);
    }
    return false;
}

///
/// \brief PuzzleGame::isMovementStartingByZeroValid
/// \param row
/// \param col
/// \return true if the movement is valid
///
bool PuzzleGame::isMovementStartingByZeroValid(bool (PuzzleGame::*solver)(), int row, int col)
{
    for(int num = 0;num < 2;num++)
    {
        if(isRecursiveMovementValid(solver,row,col,num))
            return true;
    }
    return false;
}

///
/// \brief PuzzleGame::isMovementStartingByOneValid
/// \param row
/// \param col
/// \return true if the movement is valid
///
bool PuzzleGame::isMovementStartingByOneValid(bool (PuzzleGame::*solver)(), int row, int col)
{
    for(int num = 1;num > -1;num--)
    {
        if(isRecursiveMovementValid(solver, row,col,num))
            return true;
    }
    return false;
}

///
/// \brief PuzzleGame::isRowValid
/// \param row
/// \return true if the row respects the game constraints
///
bool PuzzleGame::isRowValid(int row)
{
    if(isRowComplete(row))
        if(!isRowBalanced(row) || !isRowUnique(row))
            return false;

    return true;
}

///
/// \brief PuzzleGame::isColValid
/// \param col
/// \return true if a column respects the game constraints
///
bool PuzzleGame::isColValid(int col)
{
    if(isColComplete(col))
        if(!isColBalanced(col) || !isColUnique(col))
            return false;

    return true;
}

///
/// \brief PuzzleGame::findNextFreeSpace
/// sets the location of 'row' and 'col' to the location
/// of the next free position in the board from left to right
/// \param row
/// \param col
/// \return true if there is a next free space
///
bool PuzzleGame::findNextFreeSpace(int &row, int &col)
{
    for(row = 0; row < getSize(); row++)
        for(col = 0;col < getSize(); col++)
            if(pieces[row][col].getValue() == 2 && !pieces[row][col].isLocked())
                return true;

    return false;
}

///
/// \brief PuzzleGame::IsMovementLocallyPossible
///        Verifies the feasibility of a movement
/// \param row
/// \param col
/// \param num
/// \return returns true if a movement is feasible within the board
///
bool PuzzleGame::IsMovementLocallyPossible(int row, int col, int num)
{
    if(isHorizontalNeighborGood(row,col,num) && isVerticalNeighborGood(row,col,num))
    {
        pieces[row][col].setValue(num);

        if(isRowValid(row) && isColValid(col))
            return true;

        setEmptyPiece(row,col);
    }
    return false;
}

///
/// \brief PuzzleGame::isNumDifferentFromNeighbor
/// \param row
/// \param col
/// \param num
/// \param target
/// \return true if the value differs from the desired number
///
bool PuzzleGame::isNumDifferentFromNeighbor(int row, int col, int num, int target)
{
    if(target >= 0 && target < getSize())
    {
        if(pieces[row][col].getValue() == num)
        {
            return false;
        }
    }

    return true;
}

///
/// \brief PuzzleGame::isMovementRespectingLeftNeighbors
/// \param row
/// \param col
/// \param num
/// \return returns true if neighbours to  the left of
///         the desired value are respected.
bool PuzzleGame::isMovementRespectingLeftNeighbors(int row, int col, int num)
{
    if(!isNumDifferentFromNeighbor(row-1,col,num,row-1))
        if(!isNumDifferentFromNeighbor(row-2,col,num,row-2))
            return false;

    return true;
}

///
/// \brief PuzzleGame::isMovementRespectingRightNeighbors
/// \param row
/// \param col
/// \param num
/// \return Returns true if the neighbours the right
///         to the desired value are respected
///
bool PuzzleGame::isMovementRespectingRightNeighbors(int row, int col, int num)
{
    if(!isNumDifferentFromNeighbor(row+1,col,num,row+1))
        if(!isNumDifferentFromNeighbor(row+2,col,num,row+2))
            return false;

    return true;
}

///
/// \brief PuzzleGame::isMovementRespectingUpperNeighbors
/// \param row
/// \param col
/// \param num
/// \return true if the neighbours above the desired value are respected
///
bool PuzzleGame::isMovementRespectingUpperNeighbors(int row, int col, int num)
{
    if(!isNumDifferentFromNeighbor(row,col-1,num,col-1))
        if(!isNumDifferentFromNeighbor(row,col-2,num,col-2))
            return false;

    return true;
}

///
/// \brief PuzzleGame::isMovementRespectingBottomNeighbors
/// \param row
/// \param col
/// \param num
/// \return true if the neighbours in the bottom of the
///         desired value are being respected
///
bool PuzzleGame::isMovementRespectingBottomNeighbors(int row, int col, int num)
{
    if(!isNumDifferentFromNeighbor(row,col+1,num,col+1))
        if(!isNumDifferentFromNeighbor(row,col+2,num,col+2))
            return false;

    return true;
}

///
/// \brief PuzzleGame::isHorizontalNeighborGood
/// \param row
/// \param col
/// \param num the desired value to be verified
/// \return true if the desired value respects horizontal neighbours
///
bool PuzzleGame::isHorizontalNeighborGood(int row, int col, int num)
{
    if(isMovementRespectingLeftNeighbors(row,col,num))
        if(isMovementRespectingRightNeighbors(row,col,num))
            return true;

    return false;
}

///
/// \brief PuzzleGame::isVerticalNeighborGood
/// \param row
/// \param col
/// \param num the desired value to be verified
/// \return true if vertical neighbors are respect
bool PuzzleGame::isVerticalNeighborGood(int row, int col, int num)
{
    if(isMovementRespectingUpperNeighbors(row,col,num))
        if(isMovementRespectingBottomNeighbors(row,col,num))
            return true;

    return false;
}

///
/// \brief PuzzleGame::isNeighbourhoodCorrect
/// \return Returns true if all pieces respect their spacial constraint
///         Otherwise returns false
bool PuzzleGame::isNeighbourhoodCorrect()
{
    for(int i = 0; i < getSize(); i++)
    {
        for(int j = 0; j < getSize(); j++)
        {
            if(!IsMovementLocallyPossible(i,j,pieces[i][j].getValue()))
                return false;
        }
    }
    return true;
}

///
/// \brief PuzzleGame::isColUnique
/// \param y the desired column
/// \return returns true if the desired column is unique (i.e has no duplicates)
///         Otherwise returns false.
bool PuzzleGame::isColUnique(int y)
{
    for(int i = 0; i < getSize(); i++)
    {
        if(i == y)
            continue;

        for(int j = 0;j <= (getSize() - 1);j++)
        {
            if(pieces[j][y].getValue() != pieces[j][i].getValue())
                break;
            if(j == (getSize() - 1))
                return false;
        }
    }
    return true;
}

///
/// \brief PuzzleGame::isRowUnique
/// \param x the desired row
/// \return Returns true if the desired row is unique
///         Otherwise returns false
bool PuzzleGame::isRowUnique(int x)
{
    for(int i = 0; i < getSize(); i++)
    {
        if(i == x)
            continue;

        for(int j = 0; j < getSize(); j++)
        {
            if(pieces[x][j].getValue() != pieces[i][j].getValue())
                break;
            if(j == (getSize() - 1))
                return false;
        }
    }
    return true;
}

///
/// \brief PuzzleGame::isColComplete
/// \param y the desired column to be verified
/// \return returns true if the column is complete (i.e has no free spaces)
///         Otherwise returns false.
///
bool PuzzleGame::isColComplete(int y)
{
    for(int j = 0; j < getSize(); j++)
    {
        if(pieces[j][y].getValue() == 2)
            return false;
    }
    return true;
}

///
/// \brief PuzzleGame::isRowComplete
/// \param x the desired row to be verified
/// \return Returns true if a row is complete (i.e has no empty spaces)
///         Otherwise returns false
bool PuzzleGame::isRowComplete(int x)
{
    for(int j = 0; j < getSize(); j++)
    {
        if(pieces[x][j].getValue() == 2)
            return false;
    }
    return true;
}

///
/// \brief PuzzleGame::isRowBalanced
/// \param x the desired row to be verified
/// \return Returns true if the row has the same number of zeros and ones
///         Otherwise returns false
///
bool PuzzleGame::isRowBalanced(int x)
{
    int colCount = 0;
    for(int j = 0; j < getSize(); j++)
    {
        int value = pieces[x][j].getValue();

        if(value == 2)
            return false;

        colCount += value;
    }
    return (colCount == (size / 2));
}

///
/// \brief PuzzleGame::isColBalanced
/// \param y desired column to verify if its balanced
/// \return returns true if the column is balanced
///         Otherwise it returns false.
bool PuzzleGame::isColBalanced(int y)
{
    int rowCount = 0;
    for(int j = 0; j < getSize(); j++)
    {
        int value = pieces[j][y].getValue();

        if(value == 2)
            return false;

        rowCount += value;
    }
    return (rowCount == (size / 2));
}

///
/// \brief PuzzleGame::isVerticallyBalanced
/// \return Returns true if all columns have the same number of zeros and ones
///         Otherwise returns false
bool PuzzleGame::isVerticallyBalanced()
{
    for(int i = 0;i < getSize();i++)
    {
        if(!isColBalanced(i))
            return false;
    }
    return true;
}

///
/// \brief PuzzleGame::isHorizontallyBalanced
/// \return Returns true if all rows have the same number of zeros and ones
///         Otherwise returns false
///
bool PuzzleGame::isHorizontallyBalanced()
{
    for(int i = 0;i < getSize();i++)
    {
        if(!isRowBalanced(i))
            return false;
    }
    return true;
}

///
/// \brief PuzzleGame::isVerticallyDuplicate
/// \return Returns true if there are no duplicated columns
///         otherwise it returns false.
///
bool PuzzleGame::isVerticallyDuplicate()
{
    for(int i = 0; i < getSize(); i++)
    {
        if(!isColUnique(i))
            return false;
    }
    return true;
}

///
/// \brief PuzzleGame::isHorizontallyDuplicate
///
/// \return Returns true if there are no duplicate rows,
///         otherwise returns false.
///
bool PuzzleGame::isHorizontallyDuplicate()
{
    for(int i = 0; i < getSize(); i++)
    {
        if(!isRowUnique(i))
            return false;
    }
    return true;
}

///
/// \brief PuzzleGame::checkVictory
///        Verifies if the game has been successfully solved.
/// \return Returns a string explaining if
///
std::string PuzzleGame::checkVictory()
{
    std::string result;

    if(!isNeighbourhoodCorrect())
        result = "Unfortunately, you did not solve the board correctly.";

    else if(!isVerticallyBalanced())
        result = "Unfortunately, an asymmetric row was found.";

    else if(!isHorizontallyBalanced())
        result = "Unfortunately, an asymmetric column was found.";

    else if(!isHorizontallyDuplicate())
        result = "Unfortunately, a duplicate row was found.";

    else if(!isVerticallyDuplicate())
        result = "Unfortunately, a duplicate column was found.";

    else
        result = "Congratulations! You won the game.";

    return result;
}
