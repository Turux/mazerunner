#include "TuruxMaze.h"
#include <cstdlib>

using namespace std;

int TuruxMaze::nRows() const
{
	return _mat.size();
}

int TuruxMaze::nCols() const
{
	return _mat[0].size();
}

bool TuruxMaze::IsEmpty(int i, int j) const
{
	point check(i,j);
	
	if (check == _st || check == _end)
		return true;
	else if (_mat[i][j])
		return false;
	else 
		return true;
}

void TuruxMaze::GenerateMaze(int nr, int nc, const point& start, const point& end)
{
	_mat.resize( nr , vector<bool>( nc , 0 ) );
	for (int i=0; i<nr; i++)
		for (int j=0; j<nc; j++)
			if (bool t=rand() % 2)			
			_mat[i][j]=rand() % 2;
			else _mat[i][j]=t;
	_st = start;
	_end = end;
}

void TuruxMaze::Regenerate(int nr, int nc, const point& start, const point& end)
{
	_mat.clear();
	GenerateMaze(nr,nc,start,end);
}

void TuruxMaze::Regenerate()
{
	int nr = nRows();
	int nc = nCols();
	_mat.clear();
	GenerateMaze(nr,nc,_st,_end);
}

void TuruxMaze::UpdateRobotLocs(const vector<point>& vp)
{
	_robotLocs = vp;
}
template <typename T>
int FindIndex( vector < T >& v, T& e)
{
    for (int i=0; i<v.size(); i++)
	{
		if (v[i] == e)
		return i;
	}
	return -1;
}

std::ostream&  TuruxMaze::Display(std::ostream& os) const
{
	int nr = nRows();
	int nc = nCols();
		
	for (int i=0; i < nr; i++)
	{
		
		os << endl;
		for (int j=0; j < nc; j++)
		{
			point now(i,j);
			vector<point> loc = _robotLocs;
			
			int k= FindIndex(loc,now);
			if (k != -1)
			{
				os << k << k;
			}
			else if (now == _st) os << "..";
			else if (now == _end) os << "XX";
			else
			{
				switch(_mat[i][j])
				{
					case 0: os << "  "; break;
					case 1: os << "##"; break;
				}
			}
			
		}

	}
	os << endl;
	return os;
}
