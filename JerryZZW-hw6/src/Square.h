#pragma once

#include "Point2D.h"
#include "Rectangle.h"

template<class T>
class Square: public Rectangle<T> {
 public:

  Square(T x, T y, T side);
};

//Parametrized constructor
template<class T>
Square<T>::Square(T x, T y, T side) {
  this->x = x;
  this->y = y;

  if(side <= 0) {//When side <= 0, throw Exception
    throw CustomException(33);
  }
  else {
    this->width = side;
    this->height = side;
  }
}