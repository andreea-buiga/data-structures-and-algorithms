#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that initialises a matrix
    */
    this->number_of_elements = 0;
	this->lines = nrLines;
	this->columns = nrCols;
	this->root = nullptr;
}

int Matrix::nrLines() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that returns the number of lines
    */
	return this->lines;
}

int Matrix::nrColumns() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that the number of columns
    */
    return this->columns;
}

TElem Matrix::element(int i, int j) const {
    /**
     * complexity:
     * BC: Θ(1) - when the element we want to add is a direct child of the root
     * WC: Θ(n) - when the tree is degenerate
     * TC: O(n)
     * function that returns an element from the matrix from a certain line and column
    */
	if((i < 0 || i >= this->lines) || (j < 0 || j >= this->columns))
        throw exception();
    return this->get_bst_element(this->root, i, j);
}

TElem Matrix::modify(int i, int j, TElem e) {
    /**
     * complexity:
     * BC: Θ(1) - when the element we want to add is a direct child of the root
     * WC: Θ(n) - when the tree is degenerate
     * TC: O(n)
     * function that modifies an element from the matrix from a certain line and column
    */
    if((i < 0 || i >= this->lines) || (j < 0 || j >= this->columns))
        throw exception();
    TElem to_return = NULL_TELEM;
    TElem elem = this->element(i, j);
    if(!(e == NULL_TELEM && elem == NULL_TELEM)) {
        if(e == NULL_TELEM) { /// when the element to be added is NULL_TELEM, we remove it from the BST
            TElem old_elem = 0;
            TElem to_remove = 0;
            this->number_of_elements = this->number_of_elements - 1;
            this->root = this->remove_bst_node(this->root, old_elem, to_remove, i, j);
            to_return = old_elem;
        }
        else
            if(elem == NULL_TELEM) {
                this->number_of_elements = this->number_of_elements + 1;
                this->root = this->add_bst_node(this->root, e, i, j);
            }
            else
                to_return = this->modify_bst_node(this->root, e, i, j);
    }
    return to_return;
}

BSTNode *Matrix::add_bst_node(BSTNode *bst_node, TElem e, int i, int j) {
    /**
     * complexity:
     * BC: Θ(1) - when the element we want to add is a direct child of the root
     * WC: Θ(n) - when the tree is degenerate
     * TC: O(n)
     * function that adds a node recursively
    */
    if(bst_node == nullptr) {
        bst_node = new BSTNode;
        bst_node->info = e;
        bst_node->line = i;
        bst_node->column = j;
        bst_node->left = nullptr;
        bst_node->right = nullptr;
    }
    else
        if(i < bst_node->line || (i == bst_node->line && j < bst_node->column))
            bst_node->left = this->add_bst_node(bst_node->left, e, i , j);
        else
            bst_node->right = this->add_bst_node(bst_node->right, e, i, j);
    return bst_node;
}

TElem Matrix::modify_bst_node(BSTNode *bst_node, TElem e, int i, int j) {
    /**
     * complexity:
     * BC: Θ(1)
     * WC: Θ(n)
     * TC: O(n)
     * function that modifies a node recursively
    */
    if(bst_node->line == i && bst_node->column == j) {
        TElem old_elem = bst_node->info;
        bst_node->info = e;
        return old_elem;
    }
    else {
        if(i < bst_node->line || (i == bst_node->line && j < bst_node->column))
            return this->modify_bst_node(bst_node->left, e, i, j);
        else
            return this->modify_bst_node(bst_node->right, e, i, j);
    }
}

TElem Matrix::get_bst_element(BSTNode *bst_node, int i, int j) const {
    /**
     * complexity:
     * BC: Θ(1)
     * WC: Θ(n)
     * TC: O(n)
     * function that gets the element stored in the node recursively
    */
    if(bst_node == nullptr)
        return NULL_TELEM;
    else {
        if(bst_node->line == i && bst_node->column == j)
            return bst_node->info;
        else {
            if (i < bst_node->line || (i == bst_node->line && j < bst_node->column))
                return this->get_bst_element(bst_node->left, i, j);
            else
                return this->get_bst_element(bst_node->right, i, j);
        }
    }
}

BSTNode *Matrix::get_min_node(BSTNode *bst_node) {
    /**
     * complexity:
     * BC: Θ(1)
     * WC: Θ(n)
     * TC: O(n)
     * function that gets the minimum node recursively
    */
    if(bst_node == nullptr)
        return nullptr;
    else {
        if(bst_node->left == nullptr)
            return bst_node;
        else
            return get_min_node(bst_node->left);
    }
}

BSTNode *Matrix::remove_bst_node(BSTNode *bst_node, TElem &old_elm, TElem &to_remove, int i, int j) {
    /**
     * complexity:
     * BC: Θ(1)
     * WC: Θ(n)
     * TC: O(n)
     * function that removes a node recursively
    */
    BSTNode *temp;
    if(bst_node == nullptr)
        return nullptr;
    else
        if(i < bst_node->line || (i == bst_node->line && j < bst_node->column))
            bst_node->left = this->remove_bst_node(bst_node->left, old_elm, to_remove, i, j);
        else
            if(i > bst_node->line || (i == bst_node->line && j > bst_node->column))
                bst_node->right = this->remove_bst_node(bst_node->right, old_elm, to_remove, i, j);
            else
                if(bst_node->left != nullptr && bst_node->right != nullptr) {
                    temp = this->get_min_node(bst_node->right);
                    if(to_remove == 0)
                        old_elm = bst_node->info;
                    bst_node->info = temp->info;
                    bst_node->line = temp->line;
                    bst_node->column = temp->column;
                    to_remove = to_remove + 1;
                    bst_node->right = this->remove_bst_node(bst_node->right, old_elm, to_remove, bst_node->line, bst_node->column);
                }
                else {
                    temp = bst_node;
                    if(to_remove == 0)
                        old_elm = bst_node->info;
                    if(bst_node->left == nullptr)
                        bst_node = bst_node->right;
                    else {
                        if (bst_node->right == nullptr)
                            bst_node = bst_node->left;
                    }
                    delete temp;
                }
    return bst_node;
}

void Matrix::setMainDiagonal(TElem elem) {
    /**
     * complexity:
     * BC: Θ(n * log n) - the none of the elements on the main diagonal are not NULL_TELEM
     *     Θ(1 + 2 + ... + n) = Θ(n(n + 1)/2) = Θ(n^2)
     * WC: Θ(n^3) - when all the elements are not NULL_TELEM for each element on the main diagonal depending on he distance
     *              from the main diagonal
     *     Θ(1 + (n + 2) + ... + n(n - 1) + n) = Θ(n(n + 1)/2 + n^2(n - 1)/2) = Θ((n^3 + n)/2) = Θ(n^3)
     * TC: O(n^3) -
     * function that sets the main diagonal to elem
    */
    if(this->lines != this->columns)
        throw exception();
    int i;
    for(i = 0; i < this->lines; i++)
        this->modify(i, i, elem);
}
