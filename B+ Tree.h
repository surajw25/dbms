#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
//#include <filesystem>
using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
    /*
		Generally size of the this node should be equal to the block size. Which will limit the number of disk access and increase the accesssing time.
		Intermediate nodes only hold the Tree pointers which is of considerably small size(so they can hold more Tree pointers) and only Leaf nodes hold
		the data pointer directly to the disc.

		IMPORTANT := All the data has to be present in the leaf node
	*/
   public:
    bool isLeaf;
    vector<int> keys;
    Node* ptr2next;      
    union ptr {                  
        vector<Node*> ptr2Tree;  
        vector<FILE*> dataPtr;   
        ptr(); 
        ~ptr();
    } ptr2TreeOrData;

    friend class BPTree;  
   public:
    Node();
};






class BPTree {
    /*
		::For Root Node :=
			The root node has, at least two tree pointers
		::For Internal Nodes:=
			1. ceil(maxIntChildLimit/2)     <=  #of children <= maxIntChildLimit
			2. ceil(maxIntChildLimit/2)-1  <=  #of keys     <= maxIntChildLimit -1
		::For Leaf Nodes :=
			1. ceil(maxLeafNodeLimit/2)   <=  #of keys     <= maxLeafNodeLimit -1
	*/
   private:
    int maxIntChildLimit;                                  
    int maxLeafNodeLimit;                                  
    Node* root;                                             
    void insertInternal(int x, Node** cursor, Node** child); 
    Node** findParent(Node* cursor, Node* child);
    Node* firstLeftNode(Node* cursor);

   public:
    BPTree();
    BPTree(int degreeInternal, int degreeLeaf);
    Node* getRoot();
    int getMaxIntChildLimit();
    int getMaxLeafNodeLimit();
    void setRoot(Node *);
    void display(Node* cursor);
    void seqDisplay(Node* cursor);
    void search(int key);
    void insert(int key, FILE* filePtr);
    void removeKey(int key);
    void removeInternal(int x, Node* cursor, Node* child);
};

#endif
