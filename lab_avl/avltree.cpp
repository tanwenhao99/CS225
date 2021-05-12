/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp1 = t->right->left;
    t->right->left = t;
    Node* temp2 = t->right;
    t->right = temp1;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = temp2;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp1 = t->left->right;
    t->left->right = t;
    Node* temp2 = t->left;
    t->left = temp1;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = temp2;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL)
        return;
    if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) == 2) {
        if (heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left) == 1)
            rotateLeft(subtree);
        else
            rotateRightLeft(subtree);
    } else if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) == -2) {
        if (heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left) == 1)
            rotateLeftRight(subtree);
        else
            rotateRight(subtree);
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
        return;
    }
    if (subtree->key > key) {
        insert(subtree->left, key, value);
        rebalance(subtree);
    } else if (subtree->key < key) {
        insert(subtree->right, key, value);
        rebalance(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* curr = subtree->left;
            if (curr->right == NULL) {
                curr->right = subtree->right;
                delete subtree;
                subtree = curr;
            } else {
                while (curr->right->right) 
                    curr = curr->right;
                Node* temp = curr->right->left;
                curr->right->left = subtree->left;
                curr->right->right = subtree->right;
                delete subtree;
                subtree = curr->right;
                curr->right = temp;
            }
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left) {
                Node* temp = subtree;
                subtree = subtree->left;
                delete temp;
            } else {
                Node* temp = subtree;
                subtree = subtree->right;
                delete temp;
            }
        }
        // your code here
        rebalance(subtree);
    }
}
