#include "Edge2d.hpp"




Edge2d::Edge2d(const Point2d& p1, const Point2d& p2) :mypoints(2,Point2d(0,0))
{
	mypoints[0] = Point2d(p1);
	mypoints[1] = Point2d(p2);
}


Edge2d::Edge2d(const Edge2d& other_edge) :mypoints(2,Point2d(0,0))
{
	std::vector<Point2d> other_vector(other_edge.GetPoints());
	mypoints[0] = Point2d(other_vector[0]);
	mypoints[1] = Point2d(other_vector[1]);
}



std::vector<Point2d> Edge2d::GetPoints() const
{
	return std::vector<Point2d>(mypoints);
}


bool Edge2d::IsNeighbour(const Edge2d& other_edge)
{
	std::vector<Point2d> other_points(other_edge.GetPoints());
	Point2d p1 = Point2d(other_points[0]);
	Point2d p2 = Point2d(other_points[1]);
	if(this->mypoints[0] == p1 || this->mypoints[0] == p2)
	{
		return true;
	}
	else if(this->mypoints[1] == p1 || this->mypoints[1] == p2)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}




std::ostream& operator<<(std::ostream& output,const Edge2d& z)
{
	output << "{( " << z.mypoints[0].GetX() <<" , " << z.mypoints[0].GetY() <<" ), " << "( " << z.mypoints[1].GetX() <<" , " << z.mypoints[1].GetY() <<" )}";
}