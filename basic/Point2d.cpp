#include "Point2d.hpp"
#include <iostream>
#include <cmath>


Point2d::Point2d()
{
	myx = 0;
	myy = 0;
}


Point2d::Point2d(const Point2d& otherPoint)
{
	this->myx = otherPoint.GetX();
	this->myy = otherPoint.GetY();
}


Point2d::Point2d(const double x, const double y)
{
	this->myx = x;
	this->myy = y;
}


double Point2d::Distanceof2dPoints(const Point2d p1, const Point2d p2)
{
	return sqrt( pow(p1.GetX()-p2.GetX(),2) + pow(p1.GetY()-p2.GetY(),2) );
}


//double Point2d::GetToleranceOfEquality()
//{
//	return TOL_OF_EQUALITY_OF_POINTS2D;
//}


//void Point2d::SetToleranceOfEquality(double new_tol)
//{
//	assert( new_tol > 0 );
//	TOL_OF_EQUALITY_OF_POINTS2D = new_tol;		
//}


double Point2d::GetX() const
{
	return this->myx;
}


double Point2d::GetY() const
{
	return this->myy;
}


bool Point2d::operator==(const Point2d& other_point) const
{
	if( (this->GetX() == other_point.GetX()) && (this->GetY() == other_point.GetY()) )
	{
		return true;
	}else
	{
		return false;
	}
}



Point2d Point2d::operator+() const
{
	Point2d p1(this->myx, this->myy);
	return p1;
}


Point2d Point2d::operator-() const
{
	Point2d p1(- (this->myx), - (this->myy));
	return p1;
}



Point2d Point2d::operator+(const Point2d& p1) const
{
	Point2d addition_point( myx + p1.myx,myy + p1.myy);
	return addition_point;
}



Point2d Point2d::operator-(const Point2d& p1) const
{
	Point2d subtract_point(myx - p1.myx, myy - p1.myy);
	return subtract_point;
}


Point2d& Point2d::operator=(const Point2d& p)
{
	if( this!= &p )
	{
		myx = p.myx;
		myy = p.myy;
	}
	return *this;
}


std::ostream& operator<<(std::ostream& output, const Point2d& z)
{
	output << "( " << z.GetX() <<" , " << z.GetY() <<" ) ";
}




