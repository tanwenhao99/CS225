/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) {
    if (subRoot != NULL) {
        mirror(subRoot->left);
        mirror(subRoot->right);
        Node* temp = subRoot->left;
        subRoot->left = subRoot->right;
        subRoot->right = temp;
    }
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    if (root == NULL)
        return true;
    std::stack<Node*> stack;
    Node* curr = root;
    stack.push(curr);
    while (curr->left != NULL) {
        stack.push(curr->left);
        curr = curr->left;
    }
    T val = curr->elem;
    while (!stack.empty()) {
        curr = stack.top();
        stack.pop();
        if (val > curr->elem)
            return false;
        else
            val = curr->elem;
        if (curr->right != NULL) {
            stack.push(curr->right);
            Node * temp = curr->right;
            while (temp->left != NULL) {
                stack.push(temp->left);
                temp = temp->left;
            }
        }
    }

    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursive(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(const Node* subRoot) const {
    if (subRoot == NULL)
        return true;
    if (isOrderedRecursive(subRoot->left) && isOrderedRecursive(subRoot->right)) {
        Node * lNode = subRoot->left;
        Node * rNode = subRoot->right;
        if (lNode != NULL) {
            while (lNode->right != NULL)
                lNode = lNode->right;
            if (lNode->elem > subRoot->elem)
                return false;
        }
        if (rNode != NULL) {
            while (rNode->left != NULL)
                rNode = rNode->left;
            if (rNode->elem < subRoot->elem)
                return false;
        }
    } else
        return false;
    return true;
}