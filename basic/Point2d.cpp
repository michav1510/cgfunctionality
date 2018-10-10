#include "Point2d.hpp"
#include <iostream>
#include <cmath>

Point2d::Point2d()
{
	m_x = 0;
	m_y = 0;
}

Point2d::Point2d(const Point2d &otherPoint)
{
	this->m_x = otherPoint.GetX();
	this->m_y = otherPoint.GetY();
}

Point2d::Point2d(const double x, const double y)
{
	this->m_x = x;
	this->m_y = y;
}

double Point2d::GetX() const
{
	return this->m_x;
}

double Point2d::GetY() const
{
	return this->m_y;
}

bool Point2d::operator==(const Point2d &other_point) const
{
	if ((this->GetX() == other_point.GetX()) && (this->GetY() == other_point.GetY()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Point2d Point2d::operator+() const
{
	Point2d p1(this->m_x, this->m_y);
	return p1;
}

Point2d Point2d::operator-() const
{
	Point2d p1(-(this->m_x), -(this->m_y));
	return p1;
}

Point2d Point2d::operator+(const Point2d &p1) const
{
	Point2d addition_point(m_x + p1.m_x, m_y + p1.m_y);
	return addition_point;
}

Point2d Point2d::operator-(const Point2d &p1) const
{
	Point2d subtract_point(m_x - p1.m_x, m_y - p1.m_y);
	return subtract_point;
}

Point2d &Point2d::operator=(const Point2d &p)
{
	if (this != &p)
	{
		m_x = p.m_x;
		m_y = p.m_y;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &output, const Point2d &z)
{
	output << "( " << z.GetX() << " , " << z.GetY() << " ) ";
}
