#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
class Piece;

// TextDisplay is an observer of every piece 

class TextDisplay: public Observer {  // inherits from Observer
  std::vector<std::vector<char>> theDisplay;
  
  const int boardSize = 8;

 public:
  TextDisplay();

  void notify(Piece &p, int oldRow, int oldCol) override;
  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
