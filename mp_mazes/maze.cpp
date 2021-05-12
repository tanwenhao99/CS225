/* Your code here! */
#include "dsets.h"
#include "maze.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <tuple>

using namespace std;

SquareMaze::SquareMaze() {
    width_ = 0;
    height_ = 0;
}

void SquareMaze::makeMaze(int width, int height) {
    srand(clock());
    DisjointSets dset;
    dset.addelements(width * height);
    width_ = width;
    height_ = height;
    rowWall.clear();
    colWall.clear();
    for (int i = 0; i < width_; i++)
        rowWall.push_back(vector<bool>(height_ + 1, true));
    for (int i = 0; i <= width_; i++)
        colWall.push_back(vector<bool>(height_, true));
    vector< pair<int, int> > grids;
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++)
            grids.push_back(pair<int, int>(x, y));
    }
    while (dset.size(1) != width_ * height_) {
        int x = grids.back().first;
        int y = grids.back().second;
        grids.pop_back();
        vector<int> vec;
        if (x + 1 < width_ && colWall[x + 1][y] && dset.find(y * width_ + x) != dset.find(y * width_ + x + 1)) 
            vec.push_back(0); 
        if (y + 1 < height_ && rowWall[x][y + 1] && dset.find(y * width_ + x) != dset.find((y + 1) * width_ + x)) 
            vec.push_back(1); 
        if (x - 1 >= 0 && colWall[x][y] && dset.find(y * width_ + x) != dset.find(y * width_ + x - 1)) 
            vec.push_back(2); 
        if (y - 1 >= 0 && rowWall[x][y] && dset.find(y * width_ + x) != dset.find((y - 1) * width_ + x)) 
            vec.push_back(3); 
        if (vec.size() == 0)
            continue;
        random_shuffle(vec.begin(), vec.end());
        int k = vec[0];
        if (k == 0) {
            dset.setunion(y * width_ + x, y * width_ + x + 1);
            colWall[x + 1][y] = false;
        } else if (k == 1) {
            dset.setunion(y * width_ + x, (y + 1) * width_ + x);
            rowWall[x][y + 1] = false;
        } else if (k == 2) {
            dset.setunion(y * width_ + x, y * width_ + x - 1);
            colWall[x][y] = false;
        } else {
            dset.setunion(y * width_ + x, (y - 1) * width_ + x);
            rowWall[x][y] = false;
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) 
        return !colWall[x + 1][y];
    else if (dir == 1) 
        return !rowWall[x][y + 1];
    else if (dir == 2) 
        return !colWall[x][y];
    else 
        return !rowWall[x][y];
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir == 0) 
        colWall[x + 1][y] = exists;
    else
        rowWall[x][y + 1] = exists;
}

vector<int> SquareMaze::solveMaze() {
    vector< vector<int>> grids;
    for (int x = 0; x < width_; x++)
        grids.push_back(vector<int>(height_, -1));
    queue< tuple<int, int, int> > bfs;
    if (canTravel(0, 0, 0)) {
        bfs.push(tuple<int, int, int>(1, 0, 0));
        grids[1][0] = 0;
    }
    if (canTravel(0, 0, 1)) {
        bfs.push(tuple<int, int, int>(0, 1, 1));
        grids[0][1] = 1;
    }
    while (!bfs.empty()) {
        auto block = bfs.front();
        bfs.pop();
        int x = get<0>(block);
        int y = get<1>(block);
        int dir = get<2>(block);
        if (dir == 0) {
            if (canTravel(x, y, 0)) {
                bfs.push(tuple<int, int, int>(x+1, y, 0));
                grids[x+1][y] = 0;
            }
            if (canTravel(x, y, 1)) {
                bfs.push(tuple<int, int, int>(x, y+1, 1));
                grids[x][y+1] = 1;
            }
            if (canTravel(x, y, 3)) {
                bfs.push(tuple<int, int, int>(x, y-1, 3));
                grids[x][y-1] = 3;
            }
        } else if (dir == 1) {
            if (canTravel(x, y, 0)) {
                bfs.push(tuple<int, int, int>(x+1, y, 0));
                grids[x+1][y] = 0;
            }
            if (canTravel(x, y, 1)) {
                bfs.push(tuple<int, int, int>(x, y+1, 1));
                grids[x][y+1] = 1;
            }
            if (canTravel(x, y, 2)) {
                bfs.push(tuple<int, int, int>(x-1, y, 2));
                grids[x-1][y] = 2;
            }
        } else if (dir == 2) {
            if (canTravel(x, y, 1)) {
                bfs.push(tuple<int, int, int>(x, y+1, 1));
                grids[x][y+1] = 1;
            }
            if (canTravel(x, y, 2)) {
                bfs.push(tuple<int, int, int>(x-1, y, 2));
                grids[x-1][y] = 2;
            }
            if (canTravel(x, y, 3)) {
                bfs.push(tuple<int, int, int>(x, y-1, 3));
                grids[x][y-1] = 3;
            }
        } else {
            if (canTravel(x, y, 0)) {
                bfs.push(tuple<int, int, int>(x+1, y, 0));
                grids[x+1][y] = 0;
            }
            if (canTravel(x, y, 2)) {
                bfs.push(tuple<int, int, int>(x-1, y, 2));
                grids[x-1][y] = 2;
            }
            if (canTravel(x, y, 3)) {
                bfs.push(tuple<int, int, int>(x, y-1, 3));
                grids[x][y-1] = 3;
            }
        }
    }
    int index = -1;
    int max = 0;
    for (int n = 0; n < width_; n++) {
        int x = n;
        int y = height_ - 1;
        int count = 0;
        while (x != 0 || y != 0) {
            int dir = grids[x][y];
            if (dir == 0)
                x--;
            else if (dir == 1)
                y--;
            else if (dir == 2)
                x++;
            else
                y++;
            count++;
        }
        if (count > max) {
            index = n;
            max = count;
        }
    }
    vector<int> path(max, -1);
    int x = index;
    int y = height_ - 1;
    for (int i = max - 1; i >= 0; i--) {
        int dir = grids[x][y];
        path[i] = dir;
        if (dir == 0)
            x--;
        else if (dir == 1)
            y--;
        else if (dir == 2)
            x++;
        else
            y++;
    }
    return path;
}

PNG* SquareMaze::drawMaze() const {
    PNG* png = new PNG(width_ * 10 + 1, height_ * 10 + 1);
    for (unsigned x = 10; x < png->width(); x++) 
        png->getPixel(x, 0).l = 0;
    for (unsigned y = 0; y < png->height(); y++) 
        png->getPixel(0, y).l = 0;
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            if (colWall[x + 1][y]) {
                for (int k = 0; k <= 10; k++)
                    png->getPixel((x + 1) * 10, y * 10 + k).l = 0;
            }
            if (rowWall[x][y + 1]) {
                for (int k = 0; k <= 10; k++)
                    png->getPixel(x * 10 + k, (y + 1) * 10).l = 0;
            }
        }
    }
    return png;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* png = drawMaze();
    vector<int> path = solveMaze();
    int x = 5; int y = 5;
    for (auto& it : path) {
        if (it == 0) {
            for (int k = 0; k <= 10; k++) {
                png->getPixel(x + k, y).s = 1;
                png->getPixel(x + k, y).l = 0.5;
            }
            x += 10;
        } else if (it == 1) {
            for (int k = 0; k <= 10; k++) {
                png->getPixel(x, y + k).s = 1;
                png->getPixel(x, y + k).l = 0.5;
            }
            y += 10;
        } else if (it == 2) {
            for (int k = 0; k <= 10; k++) {
                png->getPixel(x - k, y).s = 1;
                png->getPixel(x - k, y).l = 0.5;
            }
            x -= 10;
        } else {
            for (int k = 0; k <= 10; k++) {
                png->getPixel(x, y - k).s = 1;
                png->getPixel(x, y - k).l = 0.5;
            }
            y -= 10;
        }
    }
    x /= 10; y /= 10;
    for (int k = 1; k <= 9; k++) 
        png->getPixel(x * 10 + k, (y + 1) * 10).l = 1;
    return png;
}