/**
    Purpose: To represent a convex hull of 2d points. It is a list with the vertices of a convex hull of 2d points. I 
    implemented it using a double linked cyclic list in order to read the points in clockwise order and counterclockwise
    order. The iterator I implemented is an iterator that keep the encapsulation and you can't change the list from the 
    iterator. The push(T elem) will add the (elem) into the list and at the right position if it is not interior to the
    current convex hull. So this class provide a unified way to read the points and to add a point keeping in mind that
    this list would represent a convex hul of 2d points, i.e you can't add a point to the list which is not a vertex of
    the convex hull.

    

    @author Chaviaras Michalis
    @version 1.1  2/2018 
*/
#ifndef CH2D_DLCLISTDEF
#define CH2D_DLCLISTDEF
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <stack>
#include "../basic/Point2d.hpp"
#include "../basic/BasicCalcandPred.hpp"
#include "../basic/Orientation.hpp"

using namespace preds;	// For the usage of the preds functions
using namespace basecalc; // for the usage of basecalc

class CH2d_dlclist
{
	struct Node
	{
		Point2d data;
		Node *back;
		Node *front;
	};

  private:
	Node *m_head;
	Node *m_tail;
	unsigned int m_size;
	double m_area;

	/**
	 * calculate the area of a triangle.
	 * Purpose :  It is an auxilliary function to be used in the function notify_area.
	 * Maybe it should be in another class as a static class.
	 * @param p1 A point of the triangle
	 * @param p2 A point of the triangle
	 * @param p3 A point of the triangle 
	 * @returns The area of the triangle consistute of the 3 points
	 */
	double area_of_triangle(const Point2d &p1, const Point2d &p2, const Point2d &p3)
	{
		double A_x = p1.GetX();
		double A_y = p1.GetY();
		double B_x = p2.GetX();
		double B_y = p2.GetY();
		double C_x = p3.GetX();
		double C_y = p3.GetY();
		return std::abs((A_x * (B_y - C_y) + B_x * (C_y - A_y) + C_x * (A_y - B_y)) / 2.0);
	}

	/**
	 * This method notify the area of the convex hull.
	 * Purpose : This method was made because of the time complexity of the notification of 
	 * the area which is O(size of convex hull), thus maybe in future edition we change it 
	 * in public in order to give to the user of this class to decide whether or not to notify 
	 * the area. In this way the user of this class can handle whether or not to pay this 
	 * linear time to notify the area.
	 */
	void notify_area()
	{
		if (m_size == 0 || m_size == 1 || m_size == 2)
		{
			m_area = 0;
		}
		else
		{
			//in order to find the area of the convex hull we will divide it
			//into triangles

			// the below three iterators point to different nodes because
			// there are at least three nodes in the list
			CH2d_dlclist::ch_iterator it_clo_back = ch_iterator(m_head);
			CH2d_dlclist::ch_iterator it_clo_front = it_clo_back + 1;
			CH2d_dlclist::ch_iterator it_cou_clo = it_clo_back - 1;

			// at the below variable we will keep the sum of the areas of
			//every triangle
			double sum = 0;
			sum += area_of_triangle(*it_clo_back, *it_clo_front, *it_cou_clo);

			while (++it_clo_front != it_cou_clo)
			{
				it_clo_back++;
				sum += area_of_triangle(*it_clo_back, *it_clo_front, *it_cou_clo);
			}
			m_area = sum;
		}
	}

  public:
	class ch_iterator
	{
	  private:
		const Node *p;

	  public:
		ch_iterator() { p = 0; }
		ch_iterator(Node *x) { p = x; }
		ch_iterator(const ch_iterator &other_it) { p = other_it.p; }
		ch_iterator &operator++()
		{
			p = p->front;
			return *(this);
		}
		ch_iterator operator++(int)
		{
			ch_iterator tmp(*(this));
			operator++();
			return tmp;
		}
		ch_iterator &operator--()
		{
			p = p->back;
			return *(this);
		}
		ch_iterator operator--(int)
		{
			ch_iterator tmp(*(this));
			operator--();
			return tmp;
		}
		bool operator==(const ch_iterator &other_it) const { return p == other_it.p; }
		bool operator!=(const ch_iterator &other_it) const { return p != other_it.p; }
		ch_iterator &operator=(const ch_iterator &other_ch_it)
		{
			p = other_ch_it.p;
			return *this;
		}
		//the returned type below must remain Point2d instead of Point2d& because I don't want to change the data of the list
		// from the iterator
		Point2d operator*() const { return p->data; }
		ch_iterator operator+(const unsigned int num) const
		{
			ch_iterator res;
			res.p = p;
			unsigned int count = 0;
			while (count != num)
			{
				res.p = res.p->front;
				count++;
			}
			return res;
		}

		ch_iterator operator-(const unsigned int num) const
		{
			ch_iterator res;
			res.p = p;
			unsigned int count = 0;
			while (count != num)
			{
				res.p = res.p->back;
				count++;
			}
			return res;
		}
	};

	/**
	 *   Default Constructor
	 * 
	 */
	CH2d_dlclist()
	{
		m_head = 0;
		m_tail = 0;
		m_size = 0;
		m_area = 0;
	}

	/**
	 * Copy Constructor
	 *
	 * @returns other_ch is the Convexhull2d that we make a copy of this.
	 */
	CH2d_dlclist(const CH2d_dlclist &other_ch)
	{
		if (other_ch.m_size > 0)
		{
			CH2d_dlclist::ch_iterator curr_it(other_ch.begin());
			Node *curr = new Node;
			curr->data = *curr_it;
			m_head = curr;
			Node *pre_curr = curr;
			while (++curr_it != other_ch.m_head)
			{
				curr = new Node;
				curr->data = *curr_it;
				pre_curr->front = curr;
				curr->back = pre_curr;
				pre_curr = curr;
			}
			curr->front = m_head;
			m_head->back = curr;
			m_tail = other_ch.m_tail;

			m_size = other_ch.m_size;
			m_area = other_ch.m_area;
		}
		else
		{
			m_head = 0;
			m_tail = 0;
			m_size = 0;
			m_area = 0;
		}
	}

	/**
	 * 
	 * Purpose : To implement basic algorithm or algorithms for the creation of a convex hull 
	 * in the plane(2d).
	 * @param points The set of points of which we will build the convex hull(2d)
	 * @param algorithm The algorithm we will use to construct the convex hull(2d) 
	 * 
	 */
	CH2d_dlclist(const std::vector<Point2d> &points, std::string algorithm = "Jarvis")
	{
		int size_of_vec = points.size();
		if (size_of_vec == 0)
		{
			m_head = 0;
			m_tail = 0;
			m_size = 0;
			m_area = 0;
		}
		else if (size_of_vec == 1)
		{
			m_head = new Node;
			m_head->data = points[0];
			m_head->front = m_head;
			m_head->back = m_head;
			m_tail = m_head;
			m_size = 1;
			m_area = 0;
		}
		else if (size_of_vec == 2)
		{
			if (points[0] == points[1])
			{
				m_head = new Node;
				m_head->data = points[0];
				m_head->front = m_head;
				m_head->back = m_head;
				m_tail = m_head;
				m_size = 1;
				m_area = 0;
			}
			else if (points[0].GetX() == points[1].GetX())
			{
				m_head = new Node;
				m_tail = new Node;
				if (points[0].GetY() < points[1].GetY())
				{
					m_head->data = points[0];
					m_tail->data = points[1];
				}
				else if (points[0].GetY() > points[1].GetY())
				{
					m_head->data = points[1];
					m_tail->data = points[0];
				}
				m_head->front = m_tail;
				m_tail->back = m_head;
				m_tail->front = m_head;
				m_head->back = m_tail;
				m_size = 2;
				m_area = 0;
			}
			else
			{
				m_head = new Node;
				m_tail = new Node;
				if (points[0].GetX() < points[1].GetX())
				{
					m_head->data = points[0];
					m_tail->data = points[1];
				}
				else
				{
					m_head->data = points[1];
					m_tail->data = points[0];
				}
				m_head->front = m_tail;
				m_tail->back = m_head;
				m_tail->front = m_head;
				m_head->back = m_tail;
				m_size = 2;
				m_area = 0;
			}
		}
		else
		{
			if (algorithm.compare("Jarvis") == 0)
			{
				//firstly we have to find the point with the minimum x  i.e the one we get from
				// GetX() from Point2d class

				int pos_m_head = 0; //we will find the position of the m_head and this is the initialization
				int pos_m_tail = 0; //we will find the position of the m_tail and this is the initialization
				for (int i = 1; i < size_of_vec; i++)
				{
					if ((points[i].GetX() <= points[pos_m_head].GetX()) && (points[i].GetY() <= points[pos_m_head].GetY()) ||
						points[i].GetX() < points[pos_m_head].GetX())
					{
						pos_m_head = i;
					}

					if ((points[i].GetX() >= points[pos_m_tail].GetX()) && (points[i].GetY() <= points[pos_m_tail].GetY()) ||
						points[i].GetX() > points[pos_m_tail].GetX())
					{
						pos_m_tail = i;
					}
				} // now we have the position of the m_head for sure the "points[pos_m_head]" wil be, certainly,
				// the first point of the convex hull(2d).We have also the position of the m_tail for sure the
				//"points[pos_m_tail]" wil be, certainly, a point of the convex hull(2d).

				m_head = new Node;
				m_head->data = points[pos_m_head];
				m_size = 1;
				Node *last_node = m_head;	 //we have to hold also the last node added to the list
				int last_ch_pos = pos_m_head; // the position of the last point added to the convex
				//hull (2d).
				int pos_next_cand = (pos_m_head + 1) % size_of_vec; // with this we can guarantee
				//that we start from a "random" candidate different than the pos_m_head
				while (pos_next_cand != pos_m_head)
				{
					pos_next_cand = (last_ch_pos + 1) % size_of_vec; // we change the pos_next_cand
					//after the while because we don't want to the end of the while because
					//at the start of the while we remain the pos_next_cand to be checked.
					// the last_ch_pos changes in every iteration so there is no problem with this
					// assignment.

					for (int i = 0; i < size_of_vec; i++)
					{
						if (i != last_ch_pos && i != pos_next_cand && last_ch_pos != pos_next_cand)
						{
							//doesn't have a sense to  check the angle if one of the points is the
							//same with another
							if (getOrientation(points[pos_next_cand], points[last_ch_pos], points[i]) == Orientation::Count_Clockwise ||
								(getOrientation(points[pos_next_cand], points[last_ch_pos], points[i]) == Orientation::No_Orientation &&
								 Distanceof2dPoints(points[last_ch_pos], points[pos_next_cand]) <
									 Distanceof2dPoints(points[last_ch_pos], points[i])))
							{
								//the best point will change if there is one with better angle, or a collinear
								//point which is more distant from the last point added than the best point is distant
								//from the last point added.
								pos_next_cand = i;
							}
						}
					}
					//with the finish of the for we have the new point of the convex hull in the pos_next_cand
					if (pos_next_cand != pos_m_head)
					{
						//below we insert the point to the dlc list
						Node *tmp = new Node;
						tmp->data = points[pos_next_cand];
						last_node->front = tmp;
						tmp->back = last_node;
						if (pos_next_cand == pos_m_tail)
						{
							m_tail = tmp;
						}
						//below we have to update the indexes and the pointers to node
						last_node = tmp;
						last_ch_pos = pos_next_cand;
						m_size++;
						//becareful don't updathe pos_next_cand because it is checked in the
						//condition of the while
					}
					else //if the next point of the ch(2d) is the m_head then
					{	//we don't have to allocate memory it is already allocated
						last_node->front = m_head;
						m_head->back = last_node;
					}
				}
			}
			notify_area();
		}
	};

	/**
	 *   Destructor 
	 */
	~CH2d_dlclist()
	{
		if (m_head != 0)
		{
			Node *curr;
			Node *last;
			curr = m_head;
			last = m_head->back;
			while (curr != last)
			{
				Node *tmp = curr;
				curr = curr->front;
				//you should uncomment the below if you are running tests
				//std::cout << "deletion : " << tmp->data <<  ", with address : " << tmp << "\n";
				delete tmp;
			}
			//you should uncomment the below if you are running tests
			//std::cout << "deletion : " << last->data << ", with address : " << last << "\n";
			delete last;
		}
	}

	/**
	 *    Assignment Operator
	 *    @param other_ch the other CH2d_dlclist of which the "this" list will 
	 *    be a copy of.
	 *    @returns a refernce of a CH2d_dlclist that is a copy of "other_ch"
	 */
	CH2d_dlclist &operator=(const CH2d_dlclist &other_ch)
	{
		if (this != &other_ch)
		{
			//firstly we have to delete the list that "this" holds, otherwise we
			//will have a memory leak
			if (m_head != 0)
			{
				Node *curr;
				Node *last;
				curr = m_head;
				last = m_head->back;
				while (curr->front != last)
				{
					Node *tmp = curr;
					curr = curr->front;
					//std::cout << "Deletion of the node with address : " << tmp << "\n";
					delete tmp;
				}
				//std::cout << "Deletion of the node with address : " << last << "\n";
				delete last;
			}
			//the above was the last command of the deletion of "this" list.

			if (other_ch.m_size > 0)
			{
				//we are iterating the "other_ch" through the iterator we made for safety, we don't want
				//to handle directly the list from pointers to Node. Even if the "other_ch" is const
				CH2d_dlclist::ch_iterator curr_it(other_ch.begin());
				Node *curr = new Node;
				curr->data = *curr_it;
				m_head = curr;
				Node *pre_curr = curr;
				while (++curr_it != other_ch.m_head)
				{
					curr = new Node;
					curr->data = *curr_it;
					pre_curr->front = curr;
					curr->back = pre_curr;
					pre_curr = curr;
				}
				curr->front = m_head;
				m_head->back = curr;

				m_tail = other_ch.m_tail;
				m_size = other_ch.m_size;
				m_area = other_ch.m_area;
			}
			else
			{
				m_head = 0;
				m_tail = 0;
				m_size = 0;
				m_area = 0;
			}
		}
		return *this;
	}

	/**
	* This function will push a point to the dlc list if it is not in the
	* convex hull(2d), otherwise it will not be added. The complexity of 
	* the addition of the point to a list, if the list size is >= 3, is
	* O(n). Because it runs the upper hull and the lower hull to check 
	* if there are not anti clockwise turns in the convex hull(2d). 
	* Purpose : to add a point if it is not interval to the convex hull(2d) 
	* @param qrypoint Is the point that maybe added to the list.
	* @returns -1 if the point wasn't added to the list, 1 if the point
	* was added to the list.
	*/
	int push(const Point2d &qrypoint)
	{
		if (m_size == 0)
		{
			m_head = new Node;
			m_head->data = qrypoint;
			m_head->front = m_head;
			m_head->back = m_head;
			m_tail = m_head;
			m_size++;
			m_area = 0;
			return 1;
		}
		else if (m_size == 1)
		{
			Node *current_nod;
			current_nod = m_head;

			//the current point of the list is represented by the m_head
			if (!(qrypoint == current_nod->data)) //if the points are not equal
			{
				Node *new_elem = new Node; // if we construct the new point Node and it will not be added we will have
				// a memory leak, so I declare and initialize the node inside the if
				new_elem->data = qrypoint;

				if (qrypoint.GetX() < current_nod->data.GetX())
				{
					m_head = new_elem;
					m_tail = current_nod;
				}
				else if (qrypoint.GetX() > current_nod->data.GetX())
				{
					m_head = current_nod;
					m_tail = new_elem;
				}
				else //if the two points are on the same vertical position
				{
					if (current_nod->data.GetY() > qrypoint.GetY())
					{
						m_head = new_elem;
						m_tail = current_nod;
					}
					else if (current_nod->data.GetY() < qrypoint.GetY())
					{
						m_head = current_nod;
						m_tail = new_elem;
					}
				}
				m_head->front = m_tail;
				m_head->back = m_tail;
				m_tail->back = m_head;
				m_tail->front = m_head;
				m_size++;
				m_area = 0;
				return 1;
			}
			else
			{
				return -1;
			}
		}
		else if (m_size == 2)
		{
			if (m_head->data == qrypoint || m_tail->data == qrypoint)
			{
				//if the query point is equal with one of the current points
				return -1;
			}
			else if (getOrientation(qrypoint, m_head->data, m_tail->data) == Orientation::No_Orientation &&
					 (qrypoint.GetX() >= m_head->data.GetX() && qrypoint.GetX() <= m_tail->data.GetX()) &&
					 ((qrypoint.GetY() >= m_head->data.GetY() && qrypoint.GetY() <= m_tail->data.GetY()) ||
					  (qrypoint.GetY() >= m_tail->data.GetY()) && qrypoint.GetY() <= m_head->data.GetY()))
			{
				// if the query point is collinear with the other two and the query point is between the m_head
				// and the m_tail then it will not be added to the list
				return -1;
			}
			else if (getOrientation(qrypoint, m_head->data, m_tail->data) == Orientation::No_Orientation)
			{
				// the new element is collinear but it will be added to the list
				Node *new_elem = new Node;
				new_elem->data = qrypoint;
				if (m_head->data.GetX() == m_tail->data.GetX())
				{
					// if the m_head and the m_tail lie on the same vertical line
					//then we check the y coordinates
					if (qrypoint.GetY() < m_head->data.GetY())
					{
						// the new element must substitute the m_head and the (old) m_head must be deleted
						delete m_head; //the old m_head must be deleted
						m_head = new_elem;
					}
					else
					{
						//std::cout << "(DEBUGGING) : deleting " << m_tail->data  << "\n";
						// the new element must substitute the m_tail and the (old) m_head must be deleted
						delete m_tail; // the old m_tail must be deleted
						m_tail = new_elem;
					}
				}
				else if (qrypoint.GetX() < m_head->data.GetX())
				{
					//std::cout << "(DEBUGGING) : deleting " << m_head->data  << "\n";
					// the new element must substitute the m_head and the (old) m_head must be deleted
					delete m_head; //the old m_head must be deleted
					m_head = new_elem;
				}
				else
				{
					//std::cout << "(DEBUGGING) : deleting " << m_tail->data  << "\n";
					// the new element must substitute the m_tail and the (old) m_head must be deleted
					delete m_tail; // the old m_tail must be deleted
					m_tail = new_elem;
				}
				m_head->front = m_tail;
				m_tail->back = m_head;
				m_tail->front = m_head;
				m_head->back = m_tail;
				//becareful we added a new element but we deleted also so there is no change in
				//the size, nor change to the area because is zero again;
				return 1;
			}
			else
			{
				// in this case the query point has a "random" position and it will be added to the list
				Node *new_elem = new Node;
				new_elem->data = qrypoint;
				if (qrypoint.GetX() < m_head->data.GetX() ||
					(qrypoint.GetX() == m_head->data.GetX() && qrypoint.GetY() < m_head->data.GetY()))
				{
					// then the m_head must be substituted by the query point
					Node *old_m_head = m_head;
					m_head = new_elem;
					if (getOrientation(qrypoint, old_m_head->data, m_tail->data) == Orientation::Clockwise)
					{
						// the front of the new m_head is the m_tail,
						m_head->front = m_tail;
						m_tail->back = m_head;
						m_tail->front = old_m_head;
						old_m_head->back = m_tail;
						old_m_head->front = m_head;
						m_head->back = old_m_head;
						if (old_m_head->data.GetX() == m_tail->data.GetX())
						{
							//if the old m_head lie on the same vertical
							// line with the m_tail then the m_tail also must change
							m_tail = old_m_head;
						}
					}
					else
					{
						// the front of the new m_head is the old m_head
						m_head->front = old_m_head;
						old_m_head->back = m_head;
						old_m_head->front = m_tail;
						m_tail->back = old_m_head;
						m_tail->front = m_head;
						m_head->back = m_tail;
					}
				}
				else if (qrypoint.GetX() > m_tail->data.GetX() ||
						 (qrypoint.GetX() == m_tail->data.GetX() && qrypoint.GetY() < m_tail->data.GetY()))
				{
					// the the m_tail must be substituted
					Node *old_m_tail = m_tail;
					m_tail = new_elem;
					if (getOrientation(m_head->data, old_m_tail->data, qrypoint) == Orientation::Clockwise)
					{
						// then the front of the m_head is the new m_tail
						m_head->front = m_tail;
						m_tail->back = m_head;
						m_tail->front = old_m_tail;
						old_m_tail->back = m_tail;
						old_m_tail->front = m_head;
						m_head->back = old_m_tail;
					}
					else
					{
						// the front of the m_head is the old m_tail
						m_head->front = old_m_tail;
						old_m_tail->back = m_head;
						old_m_tail->front = m_tail;
						m_tail->back = old_m_tail;
						m_tail->front = m_head;
						m_head->back = m_tail;
					}
				}
				else
				{
					// then the nor the m_head nor the m_tail must be substituted
					if (getOrientation(m_tail->data, m_head->data, qrypoint) == Orientation::Count_Clockwise)
					{
						m_head->front = new_elem;
						new_elem->back = m_head;
						new_elem->front = m_tail;
						m_tail->back = new_elem;
						m_tail->front = m_head;
						m_head->back = m_tail;
					}
					else
					{
						m_head->front = m_tail;
						m_tail->back = m_head;
						m_tail->front = new_elem;
						new_elem->back = m_tail;
						new_elem->front = m_head;
						m_head->back = new_elem;
					}
				}
				m_size++;
				notify_area();
				return 1;
			}
		}
		else //in this case we have an at least 3 points current convex hull(2d)
		{
			//becareful you can't avoid the first stage which is the necessity to add
			//the point to the list and the later loop will delete it if needed. The
			//reason is you can't know how many points front or back you have to delete
			//if the query point will be added to the list.

			Node *query_nod = new Node; //it is helpfull to create the node of the query point
			query_nod->data = qrypoint; //because it is very helpfull in the deletion later.

			bool quer_po_added = false; // it is very usefull to see if the query point added
			//to the list, if it is not added you haven't to run the last while which deletes
			// the unnecessary points.

			//the case where the query point is equal with one of the points of the convex hull(2d)
			//is checked in the else of this if-else-if...-else statement
			if (qrypoint.GetX() <= m_head->data.GetX() && qrypoint.GetY() < m_head->data.GetY() ||
				qrypoint.GetX() < m_head->data.GetX() && qrypoint.GetY() >= m_head->data.GetY())
			{
				//this is the case where the query point becomes m_head

				Node *new_m_head = query_nod; //the query point is new m_head
				Node *bef = m_head->back;
				Node *aft = m_head->front;

				if (getOrientation(bef->data, new_m_head->data, m_head->data) == Orientation::Count_Clockwise)
				{
					bef->front = new_m_head;
					new_m_head->back = bef;
					new_m_head->front = m_head;
					m_head->back = new_m_head;
				}
				else
				{
					m_head->front = new_m_head;
					new_m_head->back = m_head;
					new_m_head->front = aft;
					aft->back = new_m_head;
				}

				quer_po_added = true;
				m_size++;
				m_head = new_m_head;
				//now we the new point is inserted to the list and the later loop
				//will delete some points if it is needed
			}
			else if ((qrypoint.GetX() > m_tail->data.GetX() && qrypoint.GetY() >= m_tail->data.GetY()) ||
					 (qrypoint.GetX() >= m_tail->data.GetX() && qrypoint.GetY() < m_tail->data.GetY()))
			{
				//this is the case where the query point becomes m_tail

				Node *new_m_tail = query_nod; //the query point is new m_tail
				Node *bef = m_tail->back;
				Node *aft = m_tail->front;

				if (getOrientation(bef->data, new_m_tail->data, m_tail->data) == Orientation::Count_Clockwise)
				{
					bef->front = new_m_tail;
					new_m_tail->back = bef;
					new_m_tail->front = m_tail;
					m_tail->back = new_m_tail;
				}
				else
				{
					m_tail->front = new_m_tail;
					new_m_tail->back = m_tail;
					new_m_tail->front = aft;
					aft->back = new_m_tail;
				}

				quer_po_added = true;
				m_size++;
				m_tail = new_m_tail;
				//now the new point is inserted to the list and the later loop
				//will delete some points if it is needed
			}
			else
			{
				//the query point lies above or below the convex hull(2d)
				Node *prev = m_head;
				Node *after = m_head->front;
				while (prev != m_tail)
				{
					// upper hull iteration
					if (qrypoint == prev->data || qrypoint == after->data)
					{
						// this is the case where the query point is equal to one point of the
						// current convex hull
						delete query_nod; //we must delete the query point that we allocated
						return -1;
					}
					if (prev->data.GetX() != after->data.GetX() &&
						qrypoint.GetX() >= prev->data.GetX() && qrypoint.GetX() <= after->data.GetX())
					{
						//if after and prev are on the same vertical line then we don't want to add the
						//query point here because it will be added to the next iteration
						if (getOrientation(prev->data, qrypoint, after->data) == Orientation::Count_Clockwise)
						{
							//the second condition after || is for the case that the previous and the after
							//are at the same x coordinate, and we have three collinear points
							//(with the query point) and the query point is not between the other two points,
							// thus it should be added to the list because it is surely in the convex hull(2d)
							prev->front = query_nod;
							query_nod->back = prev;
							query_nod->front = after;
							after->back = query_nod;
							quer_po_added = true;
							m_size++; //the size must be increased. at the later stage may also be decreased.
							break;	//if we find the position of the query point in the list then we must stop
						}
					}
					prev = prev->front;
					after = after->front;
				}
				prev = m_tail;
				after = m_tail->front;
				while (prev != m_head && !quer_po_added)
				{
					// lower hull iteration
					if (qrypoint == prev->data || qrypoint == after->data)
					{
						// this is the case where the query point is equal to one point of the
						// current convex hull
						delete query_nod; //we must delete the query point that we allocated
						return -1;
					}
					if (prev->data.GetX() != after->data.GetX() &&
						qrypoint.GetX() >= after->data.GetX() && qrypoint.GetX() <= prev->data.GetX())
					{
						if (getOrientation(prev->data, qrypoint, after->data) == Orientation::Count_Clockwise)
						{
							//the second condition after || is for the case that we have three collinear points
							// and the query point is not between the other two points, thus it should be added
							// to the list because it is surely in the convex hull(2d)
							prev->front = query_nod;
							query_nod->back = prev;
							query_nod->front = after;
							after->back = query_nod;
							quer_po_added = true;
							m_size++; //the size must be increased. at the later stage may also be decreased.
							break;	//if we find the position of the query point in the list the we must stop
						}
					}
					prev = prev->front;
					after = after->front;
				}
			}
			//at this stage we have added the query point to the list but maybe will deleted and also
			//some other points maybe will deleted, the m_head and the m_tail points to the right nodes
			if (!quer_po_added)
			{
				//if the query point have not been added to the list then we don't have
				//to proceed any further because there is no change in the list.
				delete query_nod;
				return -1;
			}

			std::stack<Node *> del; // all the points from the list that will be deleted
			//now is the time to delete all the unnecessary points

			//the below upper hull and lower hull iteration is from the "Andrew's algorithm" or "monotone chain"
			//the upper hull iteration to remove unnecessary points

			//upper hull iteration starts
			std::vector<Node *> upp;
			upp.push_back(m_head);
			upp.push_back(m_head->front);
			Node *curr = m_head->front;
			while (curr != m_tail)
			{
				curr = curr->front;
				upp.push_back(curr);
				int siz = upp.size();
				while (siz > 2 && getOrientation(upp[siz - 3]->data, upp[siz - 2]->data, upp[siz - 1]->data) != Orientation::Count_Clockwise)
				{
					//while the last three do not make a counter clockwise turn delete the middle

					//std::cout << "(DEBUGGING) : " << upp[siz-3]->data << " " << upp[siz-2]->data << " " << upp[siz-1]->data << "\n";
					upp[siz - 3]->front = upp[siz - 1];
					upp[siz - 1]->back = upp[siz - 3];
					del.push(upp[siz - 2]);
					upp.erase(upp.end() - 2);
					siz = upp.size();
				}
			}

			//lower hull iteration starts
			std::vector<Node *> low;
			low.push_back(m_tail);
			low.push_back(m_tail->front);
			curr = m_tail->front;
			while (curr != m_head)
			{
				curr = curr->front;
				low.push_back(curr);
				int siz = low.size();
				while (siz > 2 && getOrientation(low[siz - 3]->data, low[siz - 2]->data, low[siz - 1]->data) != Orientation::Count_Clockwise)
				{
					//while the last three do not make a counter clockwise turn delete the middle

					//std::cout << "(DEBUGGING) : " << low[siz-3]->data << " " << low[siz-2]->data << " " << low[siz-1]->data << "\n";
					low[siz - 3]->front = low[siz - 1];
					low[siz - 1]->back = low[siz - 3];
					del.push(low[siz - 2]);
					low.erase(low.end() - 2);
					siz = low.size();
				}
			}
			//at this point we have disconnected the unnecessary points and we inserted them to the del
			//stack , so we have to free the pointers of this points and to reduce the size and to
			//notify the area. of course we have to check if the query point deleted from the list
			//thus we have the below flag
			bool flag = false;
			while (!del.empty())
			{
				if (query_nod == del.top())
				{
					std::cout << "(DEBUGGING) : case 60\n";
					flag = true;
				}
				//DEBUGGING code starts
				if (del.top() != query_nod)
				{
					//std::cout << "(DEBUGGING) : deleting " << del.top()->data  << "\n";
				}
				//DEBUGGING code ends
				delete del.top();
				del.pop();
				m_size--;
			}
			notify_area();
			if (flag)
			{
				std::cout << "(DEBUGGING) : case 62\n";
				return -1;
			}
			else
			{
				return 1;
			}
		}
	}

	/**
	 * @returns the number of the points consistute the convex hull
	 */
	unsigned int size() const
	{
		return m_size;
	}

	/**
	* @returns the point with the minimum x and the minimum y
	*/
	ch_iterator begin() const
	{
		assert(m_size > 0);
		return ch_iterator(m_head);
	}

	/**
	 * @returns the point with the maximum x, and the minimum y
	 */
	ch_iterator end() const
	{
		assert(m_size > 0);
		return ch_iterator(m_tail);
	}

	/**
	 * @returns the area of the convex hull(2d)
	 */
	double area() const
	{
		return m_area;
	}
};

#endif