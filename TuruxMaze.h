#ifndef TURUXMAZE_H_INCLUDED
#define TURUXMAZE_H_INCLUDED

#include "Maze.h"
#include <iostream>
#include <vector>

using std::vector ;
using std::ostream;

class Robot ;

class TuruxMaze: public Maze
{
    public:
        TuruxMaze() {}
        TuruxMaze(int nr, int nc, const point& start, const point& end): Maze::Maze(nr,nc,start,end)  // create a Maze with nr rows and nc columns
        {
            GenerateMaze(nr,nc,start,end) ;
        }

        //regenerate a maze with new size nr, nc
        // if no arguments are given, then use existing size
        void Regenerate(int nr, int nc, const point& start, const point& end) ;
		void Regenerate() ;

        // Get info about maze
        int nRows() const ; // # rows
        int nCols() const ; // # cols
        bool IsEmpty(int i, int j) const ;

        void UpdateRobotLocs(const vector<point>& vp) ;

        std::ostream&  Display(std::ostream& os) const ;
		
	//int FindIndex(vector < point > v, point e) const;
		

    private:

        //overridden with my own version of GenerateMaze
        void GenerateMaze(int nr, int nc, const point& start, const point& end) ;

        // Do not want to allow mazes to be copied hence private copy constructor
        TuruxMaze(const TuruxMaze& m);
		
		
};

#endif // TuruxMaze
