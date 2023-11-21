#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Piece;

class Observer {
 public:
  virtual void notify(Piece &p) = 0;  // p is the Piece that called the notify method

  virtual ~Observer() = default; 
};
#endif
