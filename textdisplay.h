#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
class Piece;

// TextDisplay is an observer of every piece 

class TextDisplay: public Observer {  // inherits from Observer
  std::vector<std::vector<char>> theDisplay;

 public:
  TextDisplay(int n);

  void notify(Piece &p) override;

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
