#include "Edge2d.hpp"

Edge2d::Edge2d(const Point2d &p1, const Point2d &p2) : m_points(2, Point2d(0, 0))
{
	m_points[0] = Point2d(p1);
	m_points[1] = Point2d(p2);
}

Edge2d::Edge2d(const Edge2d &other_edge) : m_points(2, Point2d(0, 0))
{
	std::vector<Point2d> other_vector(other_edge.GetPoints());
	m_points[0] = Point2d(other_vector[0]);
	m_points[1] = Point2d(other_vector[1]);
}

std::vector<Point2d> Edge2d::GetPoints() const
{
	return std::vector<Point2d>(m_points);
}

bool Edge2d::IsNeighbour(const Edge2d &other_edge)
{
	std::vector<Point2d> other_points(other_edge.GetPoints());
	Point2d p1 = Point2d(other_points[0]);
	Point2d p2 = Point2d(other_points[1]);
	if (this->m_points[0] == p1 || this->m_points[0] == p2)
	{
		return true;
	}
	else if (this->m_points[1] == p1 || this->m_points[1] == p2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::ostream &operator<<(std::ostream &output, const Edge2d &z)
{
	output << "{( " << z.m_points[0].GetX() << " , " << z.m_points[0].GetY() << " ), "
		   << "( " << z.m_points[1].GetX() << " , " << z.m_points[1].GetY() << " )}";
}