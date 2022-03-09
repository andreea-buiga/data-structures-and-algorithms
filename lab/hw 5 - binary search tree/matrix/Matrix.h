#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

struct BSTNode {
    TElem info;
    int line;
    int column;
    BSTNode* left;
    BSTNode* right;
};



class Matrix {
private:
    BSTNode* root;
	int lines;
	int columns;
    int number_of_elements;

	BSTNode* add_bst_node(BSTNode* bst_node, TElem e, int i, int j);
	TElem modify_bst_node(BSTNode* bst_node, TElem e, int i, int j);
	TElem get_bst_element(BSTNode* bst_node, int i, int j) const;
	BSTNode* remove_bst_node(BSTNode* bst_node, TElem &old_elm, TElem &to_remove, int i, int j);
	BSTNode* get_min_node(BSTNode* bst_node);
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    //sets all the values from the main diagonal to the value elem.
    // throws an exception if it is not a square matrix.
    void setMainDiagonal(TElem elem);

};
