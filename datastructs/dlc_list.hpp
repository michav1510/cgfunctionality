/** 
  * Purpose : This class was initially the CH2d_dlclist but I renamed it in order to maintain 
  *           it as a template class, the CH2d_dlclist became a non template dlc list which
  * 		  contains as data Point2d.
  * 
    @author Chaviaras Michalis
    @version 1.1  4/2018 
*/
#ifndef DLC_LISTDEF
#define DLC_LISTDEF
#include <iostream>
#include <cassert>

template <class T>
class dlc_list
{
	struct Node
	{
		T data;
		Node *back;
		Node *front;
	};

  private:
	Node *m_head;
	unsigned int m_size;
	double m_area;

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
		//the returned type below must remain T instead of T& because I don't want to change the data of the list
		// from the iterator
		T operator*() const { return p->data; }
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

	//default constructor
	dlc_list()
	{
		m_head = 0;
		m_size = 0;
		m_area = 0;
	}

	//copy constructor
	dlc_list(const dlc_list<T> &other_ch)
	{
		if (other_ch.m_size > 0)
		{
			typename dlc_list<T>::ch_iterator curr_it(other_ch.begin());
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

			m_size = other_ch.m_size;
			m_area = other_ch.m_area;
		}
		else
		{
			m_head = 0;
			m_size = 0;
			m_area = 0;
		}
	}

	//destructor
	~dlc_list()
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

	//assignmnent operator
	dlc_list<T> &operator=(const dlc_list<T> &other_ch)
	{
		if (this != &other_ch)
		{
			//firstly we have to delete the list that "this" holds, if "this" is
			//nonotherwise will have a memory leak
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
					std::cout << "Deletion of the node with address : " << tmp << "\n";
					delete tmp;
				}
				std::cout << "Deletion of the node with address : " << last << "\n";
				delete last;
			}
			//the above was the last command of the deletion of the "this" list.

			//now we have the same list as the other_ch
			if (other_ch.m_size > 0)
			{
				// we can't iterate through the iterator we made because with this we can only access the
				// list not to modify. Here we make modification in order the nodes point where we want !!
				typename dlc_list<T>::ch_iterator curr_it(other_ch.begin());
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

				m_size = other_ch.m_size;
				m_area = other_ch.m_area;
			}
			else
			{
				m_head = 0;
				m_size = 0;
				m_area = 0;
			}
		}
		return *this;
	}

	unsigned int size() const
	{
		return m_size;
	}

	/**
	 * @param a The object that will be insert to the m_head of the list.
	 */
	void push(T a)
	{
		Node *tmp = new Node;
		tmp->data = a;
		if (m_size == 0)
		{
			m_head = tmp;
			m_head->front = m_head;
			m_head->back = m_head;
		}
		else
		{
			Node *last = m_head->back;
			last->front = tmp;
			tmp->back = last;
			tmp->front = m_head;
			m_head->back = tmp;
			m_head = tmp;
		}
		m_size++;
	}

	/**
	 * @returns an iterator that points to the m_head of the list.
	 */
	ch_iterator begin() const
	{
		//assert(m_size > 0);
		return ch_iterator(m_head);
	}
};

#endif