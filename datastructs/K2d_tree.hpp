/**
 *   Purpose: To implement algorithms that are using this class. It is a balanced binary search tree with the 
 *   data on the leaves. 
 * 
 *   @author Chaviaras Michalis
 *   @version 1.1  6/2018
 * 
 */

#ifndef K2D_TREEDEF
#define K2D_TREEDEF

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <stdexcept>   // for exception, runtime_error, out_of_range
#include "../basic/Point2d.hpp"

/**
 *   auxiliary functions that are used for sorting
 */
bool comp_func_by_x(Point2d a, Point2d b) { return a.GetX() < b.GetX(); }
bool comp_func_by_y(Point2d a, Point2d b) { return a.GetY() < b.GetY(); }



class K2d_tree{
	struct Node{
		Node* left;         // points to the left child, otherwise is equal to 0.
		Node* right;        // points to the right child, otherwise is equal to 0.
		int split_coord;    // 1 for x coordinate , 2 for y coordinate, 0 if it is a leaf.
		double split_val;   // contains the split value of the node, if it is a leaf is equal to 0.
		bool is_leaf;       // answer to question if the node is a leaf.
		Point2d data_leaf;  // if the node is a leaf contains the Point2d, otherwise contains the Point2d : (0,0).
	};
private:	
	Node* root;                     // pointer to the root of the tree
	std::vector<Point2d> sort_by_x; // the points of the tree sorted by x
	std::vector<Point2d> sort_by_y; // the points of the tree sorted by y
	unsigned int my_size;           // the number of the leaves for which we constructed the tree
	
	
	/**
	 *  Here is practically the construction of the tree. 
	 *  The parameter constructor call this function after the sorting of the points 
	 *  with respect to x coordinate and y coordinate.
	 *  @returns a node pointer to the root of the tree
	 *  @param split is used to determine whether to split the current set with respect 
	 *  to x or y coordinate, if split is an even number then we split by x coordinate otherwise
	 *  we split by y coordinate.
	 *  @param points_by_x is the current set of the points sorted with respect to x coordinate
	 *  @param points_by_y is the current set of the points sorted with respect to y coordinate
	 *  points_by_x and points_by_y are referred to the same current set but to different sortings.
	 *  If the current set contains one point then we have to make a leaf node.
	 *  Else we have to split the current set and sort the resulted 2 sets with respect to x and y
	 *  coordinate. So the vectors left_by_x, left_by_y, right_by_x, right_by_y keep the 2 set, the left one and
	 *  the right one and the two sortings of them. We can create the last four vectors given the
	 *  points_by_x and points_by_y are sorted. 
	 *  
	 * 
	 */
	Node* BuildTree(int split, std::vector<Point2d> points_by_x, std::vector<Point2d> points_by_y)
	{
		//points_by_x and points_by_y are referred to the same set but to different sorting
		assert(points_by_x.size() == points_by_y.size());
		int siz = points_by_x.size();
		std::vector<Point2d> left_by_x;
		std::vector<Point2d> left_by_y;
		std::vector<Point2d> right_by_x;
		std::vector<Point2d> right_by_y;
		Node* nod = new Node;
		if(points_by_x.size() == 0)
		{
			delete nod;
			return 0;
		}else if(points_by_x.size() == 1)
		{
			nod->left = 0;
			nod->right = 0;
			nod->split_coord = 0;
			nod->split_val = 0;
			nod->is_leaf = true;
			nod->data_leaf = points_by_x[0];
			return nod;
		}else
		{
			if(split%2 == 1)
			{
				//then we split by x coordinate
				
				int index_median = ceil(siz/2.0)-1;
				Point2d split_point = points_by_x[index_median];
				for(int i = 0; i < siz; i++)
				{
					if( i <= index_median )
					{
						left_by_x.push_back(points_by_x[i]);
					}else
					{
						right_by_x.push_back(points_by_x[i]);
					}
					if( points_by_y[i].GetX() <= split_point.GetX() )
					{
						left_by_y.push_back(points_by_y[i]);
					}else
					{
						right_by_y.push_back(points_by_y[i]);
					}
				}
				
				nod->left = BuildTree(split+1,left_by_x,left_by_y);
				nod->right = BuildTree(split+1,right_by_x,right_by_y);
				nod->split_coord = 1;
				nod->split_val = split_point.GetX();
				nod->is_leaf = false;
				return nod;
			}else
			{
				//then we split by y coordinate
				
				int index_median = ceil(siz/2.0)-1;
				Point2d split_point = points_by_y[index_median];
				for(int i = 0; i < siz; i++)
				{
					if( i <= index_median )
					{
						left_by_y.push_back(points_by_y[i]);
					}else
					{
						right_by_y.push_back(points_by_y[i]);
					}
					if( points_by_x[i].GetY() <= split_point.GetY() )
					{
						left_by_x.push_back(points_by_x[i]);
					}else
					{
						right_by_x.push_back(points_by_x[i]);
					}
				}
				
				nod->left = BuildTree(split+1,left_by_x,left_by_y);
				nod->right = BuildTree(split+1,right_by_x,right_by_y);
				nod->split_coord = 2;
				nod->split_val = split_point.GetY();
				nod->is_leaf = false;
				return nod;
			}
		}
	}
	
	/**
	 *  The below is an auxiliary function for the deletion of all the nodes 
	 *  of the  tree. Starting from the "node" returns all the node that 
	 *  are descendants of the "node" and the "node" itself.
	 *  @returns a vector that contains the "node" and all of its descendants.
	 *  @param node the pointer to the node of the tree that we start to 
	 *  find the descendants
	 */
	std::vector<Node*> getAllNodes(Node* node)
	{
		std::vector<Node*> vec;
		vec.push_back(node);
		if( node->left != 0 )
		{
			std::vector<Node*> vec_left = getAllNodes(node->left);
			for(std::vector<Node*>::iterator it = vec_left.begin(); it != vec_left.end(); it++)
			{
				vec.push_back(*it);
			}
		}
		if( node->right != 0 )
		{
			std::vector<Node*> vec_right = getAllNodes(node->right);
			for(std::vector<Node*>::iterator it = vec_right.begin(); it != vec_right.end(); it++)
			{
				vec.push_back(*it);
			}
		}
		return vec;
	}
	
	
public:
	
	/**
	 *  Purpose : This class created for the accessing of the tree without knowing 
	 *  the implementation details of the class K2d_tree. Provides the ordinary functions
	 *  to get access of the tree data.
	 */
	class tree_iterator{
		private:
			const Node* p;
		public:
			tree_iterator(){p=0;}
			tree_iterator(Node* x){p=x;}
			tree_iterator(const tree_iterator& other_it) {p = other_it.p;}
			
			bool operator==(const tree_iterator& other_it) const {return p == other_it.p ;}
			bool operator!=(const tree_iterator& other_it) const {return p != other_it.p;}
			tree_iterator& operator=(const tree_iterator& other_ch_it){p = other_ch_it.p; return *this;}
			double getSplitValue() const {return p->split_val;}// the median of the set by x or y, it depends on the split_val
			int getSplitCoord() const {return p->split_coord;}//returns 1 for x coordinate and 2 for y coordinate
			bool hasRightChild() const {return p->right != 0;}
			bool hasLeftChild() const {return p->left != 0;}
			bool hasChildren() const {return (p->right != 0) || (p->left != 0);}
			tree_iterator getLeftChild() const {return tree_iterator(p->left);}
			tree_iterator getRightChild() const {return tree_iterator(p->right);}
			void goRightChild() {p = p->right;} 
			void goLeftChild() {p = p->left;}
			bool isInternalNode() const {return !(p->is_leaf);}
			Point2d getLeafPoint() const {return p->data_leaf;}
	};
	
	
	/**
	 *  @returns a vector with all the Point2d data from leaves that are descendants 
	 *  of the node that corresponds to the tree_iterator it_node.
	 *  @param it_node the tree_iterator whose the Point2d of the descendants leaves
	 *  are returned. 
	 */
	static std::vector<Point2d> getAllPoints(tree_iterator it_node)
	{
		std::vector<Point2d> leaves;
		if(!it_node.isInternalNode())
		{
			leaves.push_back(it_node.getLeafPoint());
			return leaves;
		}
		std::vector<Point2d> left = getAllPoints(it_node.getLeftChild());
		std::vector<Point2d> right = getAllPoints(it_node.getRightChild());
		for(std::vector<Point2d>::iterator it = left.begin(); it != left.end(); it++)
		{
			leaves.push_back(*it);
		}
		for(std::vector<Point2d>::iterator it = right.begin(); it != right.end(); it++)
		{
			leaves.push_back(*it);
		}
		return leaves;
	}
	
	
	
	/**
	 *  This constructor is the basic constructor. 
	 *  First of all we sort the vector with respect to x and y coordinate.
	 *  If there are points with equal with equal x coordinate or y coordinate 
	 *  then it throws exception because this case is unsupported yet.
	 *  @param points the vector with the points to which the construction of the 
	 *  K2d_tree is based.
	 *  
	 */
	K2d_tree(std::vector<Point2d> points)
	{
		// here must do the sort of points and call the Buildtree 
		std::sort (points.begin(), points.end(), comp_func_by_x);
		sort_by_x = points;
		std::sort (points.begin(), points.end(), comp_func_by_y);
		sort_by_y= points;
		
		my_size = sort_by_x.size();
		
		bool two_same = false;
		int siz = sort_by_x.size();
		for(int i = 0; i < siz-1; i++)
		{
			if( sort_by_x[i].GetX() == sort_by_x[i+1].GetX() )
			{
				two_same = true;
			}
			if( sort_by_y[i].GetY() == sort_by_y[i+1].GetY() )
			{
				two_same = true;
			}
		}
		if( two_same )
		{
			throw std::runtime_error( "The K2d_tree construction is unsupported for sets where exists points \
			that have equal x coordinate or y coordinate\n" );
		}else
		{
			root = BuildTree(1,sort_by_x,sort_by_y);
		}
	}
	
	
	/**
	 *  The destructor is necessary to destruct all the nodes which were constructed
	 *  by using the command "new".
	 */
	~K2d_tree()
	{
		//we have to get all the nodes that were created and delete them
		std::vector<Node*> nodes = getAllNodes(root);
		for(std::vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++)
		{
			delete *it;
		}
	}
	
	
	/**
	 * @returns a tree_iterator which points to the root of the tree
	 */
	tree_iterator begin() const
	{
		assert(root != 0);
		return tree_iterator(root);
	}
	
	
	/**
	 *  This method adding a point to the tree. The function first of all 
	 *  deletes the current whole tree and then adds to the vectors points_by_x and points_by_y
	 *  the new point. After it calls the BuildTree function as the K2d_tree(std::vector<Point2d> points)
	 *  does.
	 *  @param poi the point that will be added to the tree.
	 */
	void addPoint(const Point2d poi) 
	{
		//firtst step we have to destroy all the old nodes
		std::vector<Node*> nodes = getAllNodes(root);
		for(std::vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++)
		{
			delete *it;
		}
		//second step : we have to add to the sort_by_x and sort_by_y the new point 
		std::vector<Point2d>::iterator it = sort_by_x.begin();
		while( it != sort_by_x.end() )
		{
			if( poi.GetX() <= (*it).GetX() )
			{
				sort_by_x.insert(it,poi);
				break;
			}
			it++;
		}
		it = sort_by_y.begin();
		while( it != sort_by_y.end() )
		{
			if( poi.GetY() <= (*it).GetY() )
			{
				sort_by_y.insert(it,poi);
				break;
			}
			it++;
		}
		//the point that was added must increase the size of the tree
		my_size++;
		
		//third step rebuild the tree with the calling of the BuildTree
		root = BuildTree(1,sort_by_x,sort_by_y);
	}
	
	/**
	 * @returns the number of the leaves of the tree 
	 */
	unsigned int size() const
	{
		return my_size;
	}
	
};

	

#endif