#include "TuruxRobot.h"
#include "TuruxMaze.h"
#include <cstdlib>

using namespace std;



bool TuruxRobot::Up()
{
    int test(_r);
    --test;
    if (EnsureValidPosition(test, _c))
    {
        --_r;
        return true;
    }
    else
        return false;
}

bool TuruxRobot::Down()
{
    int test(_r);
    ++test;
    if (EnsureValidPosition(test, _c))
    {
        ++_r;
        return true;
    }
    else
        return false;
}

bool TuruxRobot::Left()
{
    int test(_c);
    --test;
    if (EnsureValidPosition(_r, test))
    {
        --_c;
        return true;
    }
    else
        return false;
}

bool TuruxRobot::Right()
{
    int test(_c);
    ++test;
    if (EnsureValidPosition(_r, test))
    {
        ++_c;
        return true;
    }
    else
        return false;
}

bool TuruxRobot::MinimizeDist(int& NewR, int& NewC)
{
    int R(_r), C(_c);
    if ((_r < NewR) && EnsureValidPosition(++R,C))
        return Down();
    else if ((_r > NewR) && EnsureValidPosition(--R,C))
        return Up();
    else if ((_c < NewC) && EnsureValidPosition(R,++C))
        return Right();
    else if ((_c > NewC) && EnsureValidPosition(R,--C))
        return Left();
}

void TuruxRobot::EvasiveAction(const int& j)
{
    int attempts = j;
    for (int i(0); i<attempts; i++)
    {
        int test= rand()%4;
        int R(_r), C(_c);
        switch (test)
        {
        case 0:
            NextMove.push_back(UP);
            break;
        case 1:
            NextMove.push_back(DOWN);
            break;
        case 2:
            NextMove.push_back(RIGHT);
            break;
        case 3:
            NextMove.push_back(LEFT);
            break;
        }
    }

}

bool TuruxRobot::StepTowardsEnd(int& NewR, int& NewC)
{

    while (!(MinimizeDist(NewR,NewC)))
    {
        TuruxRobot::EvasiveAction(3);

        {
            switch (NextMove.back())
            {
            case UP:
                Up();
                break;
            case DOWN:
                Down();
                break;
            case RIGHT:
                Right();
                break;
            case LEFT:
                Left();
                break;
            }
            NextMove.pop_back();
        }

    }

}

bool TuruxRobot::EnsureValidPosition(int r, int c)
{
    int Rmax = _pMaze->nRows();
    int Cmax = _pMaze->nCols();
    if (r>=0 && r <= Rmax && c>=0 && c<= Cmax)
    {
        return _pMaze->IsEmpty(r,c);
    }
    else
        return false;

}
