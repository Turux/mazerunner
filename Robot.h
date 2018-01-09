#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <iostream>
#include <stdexcept>
#include <string>

class Maze;

class Robot
{
    public:
        Robot():_r(0), _c(0), _pMaze(NULL) {}
        Robot(int r, int c, const Maze* pMaze): _r(r), _c(c), _pMaze(pMaze) {}
        // accesor methods
        // use these to obtain information about attributes of the robot
        virtual int GetRowLocation() const = 0 ;
        virtual int GetColumnLocation() const  = 0 ;

        // modifier methods
        // Use these to change attributes of the robot
        virtual void PlaceInMaze(const Maze* pMaze, int r=0, int c=0) = 0 ;

        virtual void SetRowLocation(int r) = 0;
        virtual void SetColumnLocation(int c) = 0 ;

        // methods to move robot
        virtual bool Up() = 0 ;
        virtual bool Down() = 0;
        virtual bool Left() = 0;
        virtual bool Right() = 0;

        std::string GetID() const {return _id;}
        // Each time this member function is called,
        // the logic inside it should make it move one step towards the
        // end position of the maze. Essentially, for each call of this
        // it should perform one of : Up, Down, Left or Right(). Which direction
        // depends on your logic to exit the maze.
        virtual bool StepTowardsEnd(int& NewR, int& NewC) = 0;

    protected:
        int _r, _c; // Robot's location row and column
        const Maze* _pMaze; // Pointer to a const Maze. Robots should not be able to alter the maze
        std::string _id ;

        // EnsureValidPosition returns true if (r,c) is a valid Maze location and it is empty
        // returns false otherwise
        virtual bool EnsureValidPosition(int r, int c) = 0;

};

#endif //ROBOT_H_INCLUDED
