/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim])
      return true;
    else if (first[curDim] > second[curDim])
      return false;
    else
      return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double currSum = 0;
    double potSum = 0;
    for (int i = 0; i < Dim; i++) {
      currSum += pow((currentBest[i] - target[i]), 2);
      potSum += pow((potential[i] - target[i]), 2);
    }
    if (currSum > potSum)
      return true;
    else if (currSum < potSum)
      return false;
    else
      return potential < currentBest;
}

template <int Dim>
void KDTree<Dim>::quickSort(vector<Point<Dim>>& points, int currDim) {
  if (points.size() < 2)
    return;
  Point<Dim> pivot = points[points.size() - 1];
  int i = -1;
  for (unsigned j = 0; j < points.size() - 1; j++) {
    if (smallerDimVal(points[j], pivot, currDim)) {
      i++;
      Point<Dim> temp = points[i];
      points[i] = points[j];
      points[j] = temp;
    }
  }
  points[points.size() - 1] = points[i + 1];
  points[i + 1] = pivot;
  vector<Point<Dim>> left(points.begin(), points.begin() + i + 1);
  quickSort(left, currDim);
  vector<Point<Dim>> right(points.begin() + i + 2, points.end());
  quickSort(right, currDim);
  for (unsigned j = 0; j < left.size(); j++)
    points[j] = left[j];
  for (unsigned j = 0; j < right.size(); j++)
    points[i + 2 + j] = right[j];
}

template <int Dim>
void KDTree<Dim>::buildTree(KDTreeNode*& subroot, vector<Point<Dim>>& points, int currDim) {
  if (points.size() == 0) {
    subroot = NULL;
    return;
  }
  quickSort(points, currDim);
  int median = (points.size() - 1) / 2;
  subroot = new KDTreeNode(points[median]);
  vector<Point<Dim>> leftPoints(points.begin(), points.begin() + median);
  buildTree(subroot->left, leftPoints, (currDim + 1) % Dim);
  vector<Point<Dim>> rightPoints(points.begin() + median + 1, points.end());
  buildTree(subroot->right, rightPoints, (currDim + 1) % Dim);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    size = newPoints.size();
    buildTree(root, points, 0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* other) {
  KDTreeNode subroot = new KDTreeNode(other->point);
  if (other->left)
    subroot->left = copy(other->left);
  if (other->right)
    subroot->right = copy(other->right);
}

template <int Dim>
void KDTree<Dim>::destroy() {
  if (root) {
    queue<KDTreeNode*> queue;
    queue.push(root);
    while(!queue.empty()) {
      KDTreeNode* curr = queue.front();
      queue.pop();
      if (curr->left)
        queue.push(curr->left);
      if (curr->right)
        queue.push(curr->right);
      delete curr;
    }
  }
  points.clear();
  size = 0;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = copy(other.root);
  points = other.points;
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
    destroy();
    root = copy(rhs.root);
    points = rhs.points;
    size = rhs.size;
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  destroy();
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return find(root, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::find(KDTreeNode* subroot, const Point<Dim>& query, int currDim) const { 
  if (!subroot->left && !subroot->right)
    return subroot->point;
  Point<Dim> currBest;
  double radius = 0;
  if (smallerDimVal(subroot->point, query, currDim)) {
    if (!subroot->right)
      currBest = subroot->point;
    else {
      currBest = find(subroot->right, query, (currDim + 1) % Dim);
      if (shouldReplace(query, currBest, subroot->point)) 
        currBest = subroot->point;
    }
    for (int i = 0; i < Dim; i++)
      radius += pow(currBest[i] - query[i], 2);
    if (radius >= pow(subroot->point[currDim] - query[currDim], 2) && subroot->left) {
      Point<Dim> nextBest = find(subroot->left, query, (currDim + 1) % Dim);
      if (shouldReplace(query, currBest, nextBest)) 
        currBest = nextBest;
    }
  } else {
    if (!subroot->left)
      currBest = subroot->point;
    else {
      currBest = find(subroot->left, query, (currDim + 1) % Dim);
      if (shouldReplace(query, currBest, subroot->point)) 
        currBest = subroot->point;
    }
    for (int i = 0; i < Dim; i++)
      radius += pow(currBest[i] - query[i], 2);
    if (radius >= pow(subroot->point[currDim] - query[currDim], 2) && subroot->right) {
      Point<Dim> nextBest = find(subroot->right, query, (currDim + 1) % Dim);
      if (shouldReplace(query, currBest, nextBest))
        currBest = nextBest;
    }
  }
  return currBest;
}