/**
    Purpose: To develop functions about Computational Geometry 

    @author Chaviaras Michalis
    @version 1.1  2/2018 
*/


#include "CompGeomLibrary.hpp"
#include <algorithm>



/**
 * This function is an auxilliary function to provide a comparator function to other functions.
 * This function is a comparator function for two points. It can be used for a sorting algorithm
 * to sort the points by its x coordinates and more specific by increasing order. 
 * @returns The returned bool has the meaning to determine for a non-trivial comparison which 
 * members must be compared (here we chose the x coordinates of the points)and what order do we 
 * want, i.e we want decreasing order (>) or increasing order (<) 
 * @param p1 is the first point that would be used for the comparison
 * @param p2 is the second point that would be used for the comparison.
 */ 
bool comp_points_by_x(const Point2d& p1, const Point2d& p2) { return p1.GetX() < p2.GetX(); } 

/**
 * This function is an auxilliary function to provide a comparator function to the other functions
 * This function is a comparatator function for two edges. It gets two edges and it finds for every edge
 * the point with the smallest x-coordinate which is located after the sorting of the vector of points 
 * at the first position. Then it compares the two edges using their points with the smallest x coordinate.
 * These two points with the smallest x coordinate are compared using their x coordinate. 
 * @returns there is no meaning to the returned result, but the < to the end set if the function 
 * that call it as comparator function sorts the result by increasing or decreasing order. The 
 * members participating to the last operator (<) are the x coordinates of the firsts points of the 
 * vectors. These members are the points with the minimum x coordinate between the points of 
 * the edge.  
 * @param e_1 is the first edge of the comparator function
 * @param e_2 is the second edge of the comparator function
 */
bool comp_edges_by_min_x(const Edge2d& e_1, const Edge2d& e_2) { 
	std::vector<Point2d> e_1_points = e_1.GetPoints(); 
	std::vector<Point2d> e_2_points = e_2.GetPoints();    
	std::sort(e_1_points.begin(),e_1_points.end(),comp_points_by_x);
	std::sort(e_2_points.begin(),e_2_points.end(),comp_points_by_x);
	return e_1_points[0].GetX() < e_2_points[0].GetX();
}

	

	
	
	
std::list<Point2d> CompGeomLibrary::Compose_ch2d(const std::list< Edge2d > list_of_edges)
{
	// the list we would return, with the vertices of the convex hull in clock wise order
	std::list<Point2d> conv_hull;
	
	// the list_of_edges is const so I take a copy of this and I pro
	std::list<Point2d> new_list_of_edges(list_of_edges);
	new_list_of_edges.sort(comp_edges_by_min_x);
      
//at this level I have sorted the input list by the rule I wanted to
}





