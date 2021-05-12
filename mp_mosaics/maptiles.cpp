/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    if (theTiles.empty() || theSource.getRows() == 0 || theSource.getColumns() == 0)
        return NULL;
    MosaicCanvas* mosaics = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> pts;
    std::map<Point<3>, TileImage*> map;
    for (auto& tile : theTiles) {
        LUVAPixel pixel = tile.getAverageColor();
        Point<3> pt = convertToXYZ(pixel);
        pts.push_back(pt);
        map[pt] = &tile;
    }
    KDTree<3> tree(pts);
    for (int row = 0; row < theSource.getRows(); row++) {
        for (int col = 0; col < theSource.getColumns(); col++) {
            LUVAPixel pixel = theSource.getRegionColor(row, col);
            Point<3> pt = convertToXYZ(pixel);
            pt = tree.findNearestNeighbor(pt);
            TileImage* tile = map[pt];
            mosaics->setTile(row, col, tile);
        }
    }
    return mosaics;
}

