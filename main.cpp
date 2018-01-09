#include <fstream>
#include <iostream>
#include "Robot.h"
#include "TuruxRobot.h"
#include "Maze.h"
#include "TuruxMaze.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL)) ;
    int MazeGridSize(11) ; // maze will be MazeGridSize x MazeGridSize
    int NumRobots (3) ; // How many robots in the maze?
    int MaxSteps (1000) ; // How many steps to test before giving up

    Maze::point start(0,0), end(rand()%MazeGridSize, rand()%MazeGridSize) ; // random start and end locations
    TuruxMaze M(MazeGridSize, MazeGridSize, start, end); // Generate a solvable Maze

    vector<Robot*> Rs(NumRobots); // we will create a number of robots, so keep a vector of pointers to robots
    vector<bool> WinningPosition(NumRobots,false) ; // keep track of whether each of the robots is at 'end'
    vector<float> Time(NumRobots,0.0f) ; // keep track of computation time consumed by each robot

    for(int i(0);i<NumRobots; i++)
        Rs[i] = new TuruxRobot(start.r, start.c, &M); // create new robots (dynamically allocate memory on the heap or store)

    // comment out one of the following
    ostream& os(cout) ; // option 1. prints to screen
//    ofstream os("out.txt") ; // option 2. prints to file

    bool Solved(false) ;
    int StepNum(0);
    while(!Solved && StepNum<MaxSteps) // only end if it is solved, or we exceed MaxSteps
    {
        StepNum++ ; // keep track of iterations
        vector<Maze::point> vlocs; // To store locations of each of the robots

        for(int i(0);i<NumRobots; i++)
        {
            Robot& r = *Rs[i] ;
            Maze::point rpt(r.GetRowLocation(), r.GetColumnLocation());
            vlocs.push_back(rpt) ; //  vlocs stores locations of each of the robots
            if (rpt==end) // does any of the positions correspond to the 'end' location?
            {
                Solved=true;
                WinningPosition[i]=true;
            }
        }

        M.UpdateRobotLocs(vlocs) ; //  send locations of each of the robots to maze (for display)

        for(int i(0);i<NumRobots; i++)
        {
            std::clock_t begint = clock();
            Rs[i]->StepTowardsEnd(end.r, end.c) ; // ask each robot to move 1 step
            std::clock_t endt = clock();
            Time[i] += endt-begint;
        }

        os << " ------ Step " << StepNum << " ------" << endl ; // display current positions
        M.Display(os) ;
    }

    os << " Started at " << start.r << " " << start.c << endl ;
    os << " Ended at " << end.r << " " << end.c << endl ;

    // Display robots that reached target position
    for(int i(0);i<NumRobots; i++)
        if (WinningPosition[i]) os << " Congrats! Robot " << i << " " << Rs[i]->GetID() << " solved the maze " << endl ;

    // No robots solved the maze
    if (!Solved)
    {
        cout << ":(" << endl ;
        os << "Unfortunately none of the robots navigated the maze :(" << endl ;
    }
    else
        cout << ":)" << endl ;


    os << endl ;

    // Display total computation time consumed by each of the robots
    for(int i(0);i<NumRobots; i++)
    {
        os << "Computational time consumed by Robot " << i << " " << Rs[i]->GetID() << " = " << Time[i] << " clock ticks "<< endl ;
        delete Rs[i] ;
    }


//
    return -1;
}
