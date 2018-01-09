#ifndef TURUXROBOT_H_INCLUDED
#define TURUXROBOT_H_INCLUDED

#include "Robot.h"
#include <iostream>
#include <stdexcept>
#include <vector>

class Maze;

enum direction {UP, DOWN, RIGHT, LEFT};

class TuruxRobot: public Robot
{
    public:
        TuruxRobot():Robot::Robot() {_id="Turux";} // takes no parameters, 'default constructor'

        // Constructor takes robot's initial location
        // if a pointer to a Maze is not provided, it is NULL (default)
        // note that default arguments are not redeclared.
        // either put them here or in the function prototype (see Robot.h)
        TuruxRobot(int r, int c, const Maze* pMaze): Robot::Robot(r,c,pMaze)
        {_id="Turux";}

        // accesor methods
        // use these to obtain information about attributes of the robot
        int GetRowLocation() const {return _r;}
        int GetColumnLocation() const {return _c;}

        // modifier methods
        // Use these to change attributes of the robot
        void PlaceInMaze(const Maze* pMaze, int r=0, int c=0)
        {
           _pMaze = pMaze;

            //if that is a valid (empty) location in the maze
            // initialise the robot to this location
            if (EnsureValidPosition(r,c))
            {
                _r = r;
                _c = c;
            }
            else
                throw std::invalid_argument("Cannot introduce robot at this location...") ;
        }

        void SetRowLocation(int r) {_r=r;}
        void SetColumnLocation(int c) {_c=c;}

        // methods to move robot
        bool Up() ;
        bool Down() ;
        bool Left() ;
        bool Right() ;

        // Each time this member function is called,
        // the logic inside it should make it move one step towards the
        // end position of the maze. Essentially, for each call of this
        // it should perform one of : Up, Down, Left or Right(). Which direction
        // depends on your logic to exit the maze.
        bool StepTowardsEnd(int& NewR, int& NewC) ;
        bool MinimizeDist(int& NewR, int& NewC);
        void EvasiveAction(const int& i);

    private:
        std::vector<direction> NextMove;
        bool EnsureValidPosition(int r, int c) ; // see Robot.h
        TuruxRobot(const TuruxRobot& r) ; // don't allow robots to be copied, so copy constructor is made private
};

#endif //SUBRROBOT_H_INCLUDED
