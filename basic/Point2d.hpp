/**
    Purpose: To be used to the Computational Geometry Library

    @author Chaviaras Michalis
    @version 1.1  2/2018 
*/


#ifndef POINT2DDEF
#define POINT2DDEF

#include <iostream>
#include <cassert>

class Point2d
{
private: 
	//THE USAGE OF THE TOL_OF_EQUALITY_OF_POINTS2D is dubious 
	//static double TOL_OF_EQUALITY_OF_POINTS2D = 1e-9;
	double myx;
	double myy;
public:
	Point2d();
	Point2d(const Point2d& otherPoint);
	Point2d(const double x, const double y);
	
	/**
	 * @returns the x coordinate of the 2d point 
	 */
	double GetX() const;
	
	
	/**
	 * @returns the y coordinate of the 2d point
	 */
	double GetY() const;
	
	
	
	/**
	 * @returns true if two points are distant smaller or equal than TOL_OF_EQUALITY_OF_POINTS2D
	 */
	bool operator==(const Point2d& other_point) const;
	
	
	/**
	 * THE USAGE OF THE TOL_OF_EQUALITY_OF_POINTS2D is dubious therefore and the usage of this 
	 * function
	 * @returns The tolerance of the class. If two points are distant smaller or equal to this number
	 * then they are considered equal
	 */
	//static double GetToleranceOfEquality();
	
	
	/**
	 * THE USAGE OF THE TOL_OF_EQUALITY_OF_POINTS2D is dubious therefore and the usage of this 
	 * function
	 * @param new_tol is the new ToleranceOfEquality
	 */
	//static void SetToleranceOfEquality(double new_tol);
	
	
	
	/**
	 * This member-function overloads the unary (+) operator 
	 * for Point2d
	 * @returns the Point2d corresponds to +(*this)
	 */
	Point2d operator+() const; // unary +
	
	
	
	
	/**
	 * This member-function overloads the unary (-) operator 
	 * for Point2d
	 * @returns the Point2d corresponds to -(*this)
	 */
	Point2d operator-() const; // unary -
	
	
	
	/**
	 *  This member-function overloads the binary (+) operator for Point2d,
	 *  and adds the corresponding coordinates with each other 
	 *  @param p1 the point that will be added to the *(this)
	 *  @returns the result of 
	 */
	Point2d operator+(const Point2d& p1) const; // binary +
	
	
	/**
	 *  This member-function overloads the binary (-) operator for Point2d,
	 *  and subtracts the corresponding coordinates with each other 
	 *  @param p1 the point that will be subtract to the *(this)
	 *  @returns the result of  
	 */
	Point2d operator-(const Point2d& p1) const; // binary -
	
	/**
	 * It is the assignment operator that helps us to assign a "value" of 
	 * Point2d to another Point2d.
	 * @param p the point that the *(this) will be equals to
	 * @returns the reference to the new Point2d after the assignment.
	 */
	Point2d& operator=(const Point2d& p);
	
	
	/**
	 * This friend-function calculate the distance between two points
	 * @returns The distance of 2 Points2d
	 */
	static double Distanceof2dPoints(const Point2d p1, const Point2d p2);
	
	/**
	 *  This is the classic operator that allow us to return a stream representation
	 *  of the Point2d.
	 *  @returns The stream that represents the Point2d and is of the form "( , ) "
	 */
	friend std::ostream& operator<<(std::ostream& output,const Point2d& z);

};


#endif