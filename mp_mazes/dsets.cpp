/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++)
        dset.push_back(-1);
}

int DisjointSets::find(int elem) {
    if (dset[elem] < 0)
        return elem;
    else {
        dset[elem] = find(dset[elem]);
        return dset[elem];
    }
}

void DisjointSets::setunion(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    if (size(a) >= size(b)) {
        dset[a] += dset[b];
        dset[b] = a;
    } else {
        dset[b] += dset[a];
        dset[a] = b;
    }
}

int DisjointSets::size(int elem) {
    int a = find(elem);
    return -dset[a];
}