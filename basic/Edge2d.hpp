/**
    Purpose: To be used to the Computational Geometry Library

    @author Chaviaras Michalis
    @version 1.1  2/2018 
*/

#ifndef EDGE2DDEF
#define EDGE2DDEF

#include <vector>
#include "Point2d.hpp"

class Edge2d
{

  private:
	std::vector<Point2d> m_points;

  public:
	Edge2d(const Edge2d &other_edge);
	Edge2d(const Point2d &p1, const Point2d &p2);

	/**
	 * @returns A vector with the 2d points corresponds to the edge 
	 */
	std::vector<Point2d> GetPoints() const;

	/**
	 * It uses the "equality of points" with the tolerance.
	 * @returns true if other_edge is neighbour to *this 
	 * @param other_edge an edge 
	 */
	bool IsNeighbour(const Edge2d &other_edge);

	/**
	 *  This is the classic operator that allow us to return a stream representation
	 *  of the Edge2d.
	 *  @returns The stream that represents the Edge2d and is of the form "{( , ),( , )} "
	 */
	friend std::ostream &operator<<(std::ostream &output, const Edge2d &z);
};

#endif
