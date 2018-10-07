/**
 *  Purpose : To implement predicates that we meet in computational geometry
 * 
 *  @author Chaviaras Michalis
 *  @version 1.1  2/2018
 * 
 */


#ifndef PREDDEF
#define PREDDEF

#include<iostream>
#include"../basic/Point2d.hpp"
#include"../basic/Edge2d.hpp"

class Pred{
	
	public:
/**
 * @param p_1 the fir. point 
 * @param p_2 the sec. point
 * @param p_3 the thi. point
 * @returns > 0 if we have an anti clockwise rotation from the vector that starts at point p_2 and ends to p_1 and the vector 
 * starts at point p_2 and ends at point p_3
 * @returns < 0 if we have a clockwise rotation from the vector that starts at point p_2 and ends to p_1 and the vector 
 * starts at point p_2 and ends at point p_3
 * @returns = 0 if the vector starts at p_2 and ends at p1 is collinear with the one that starts at point p_2 and ends at 
 * point p_3 
 */
static double Orient(const Point2d& p_1, const Point2d& p_2, const Point2d& p_3);	
	
	
	
	
/**
 * @param p1_x  x coordinate of the fir. point of the fir. edge 
 * @param p1_y  y coordinate of the fir. point of the fir. edge
 * @param p2_x  x coordinate of the sec. point of the fir. edge
 * @param p2_y  y coordinate of the sec. point of the fir. edge
 * @param p3_x  x coordinate of the fir. point of the sec. edge
 * @param p3_y  y coordinate of the fir. point of the sec. edge 
 * @param p4_x  x coorindate of the sec. point of the sec. edge
 * @param p4_y  y coorindate of the sec. point of the sec. edge
 * @returns true if the edges intersect and false otherwise
*/
static bool Edg_Inters(const double p1_x, const double p1_y, const double p2_x, const double p2_y, const double p3_x, const double p3_y, const double p4_x, const double p4_y);


/**
 * @param p_1 fir. point of the fir. edge
 * @param p_2 sec. point of the fir. edge
 * @param p_3 fir. point of the sec. edge
 * @param p_4 sec. point of the sec. edge
 * @returns true if the edges intersect and false otherwise
 */
static bool Edg_Inters(const Point2d& p_1, const Point2d& p_2, const Point2d& p_3, const Point2d& p_4);


/**
 * @param ed_1 the fir. edge 
 * @param ed_2 the sec. edge
 * @returns true if the edges intersect and false otherwise
 */
static bool Edg_Inters(const Edge2d& ed_1, const Edge2d& ed_2);
	
	
};
	
	
	
#endif
	
	