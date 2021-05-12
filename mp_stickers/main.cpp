#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image popstars; 
  popstars.readFromFile("popstars.png");
  popstars.scale(2.5);
  Image kda;    
  kda.readFromFile("kda.png");
  kda.scale(0.6);
  Image lol;
  lol.readFromFile("lol.png");
  lol.scale(1);
  Image riot;
  riot.readFromFile("riot.png");
  riot.scale(0.15);
  
  StickerSheet sheet(popstars, 3);
  sheet.addSticker(kda, 670, 750);
  sheet.addSticker(lol, 1748, 1069);
  sheet.addSticker(riot, 1890, 0);
  
  Image picture = sheet.render();
  picture.writeToFile("myImage.png");

  return 0;
}
