/**
    Purpose: To algorithms about Computational Geometry 

    @author Chaviaras Michalis
    @version 1.1  2/2018 
*/



#ifndef COMPGEOMLIBRARY
#define COMPGEOMLIBRARY

#include <list>
#include <vector>
#include "Point2d.hpp"
#include "Edge2d.hpp"
#include "CH2d_dlclist.hpp"

class CompGeomLibrary
{

public:

/**   
  @param list_of_edges The unsorted list of the edges of 2d the convex hull 
  @returns A list that contains the vertices of a 2d convex hull in a clockwise order
  @throws exception if there are colinear edges
*/
static std::list<Point2d> Compose_ch2d(const std::list<Edge2d> list_of_edges);
	

/**
 * The following function will search inside the convex hull "ch" which points from the 
 * vector "points" lies inside the "ch".
 *  
 */
std::vector<Point2d> PointsThatFoundInTheCHfromtheVector(CH2d_dlclist ch, std::vector<Point2d> points );	


};










#endif