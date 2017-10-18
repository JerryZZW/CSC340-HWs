#pragma once

#include "Point2D.h"
#include "CustomException.h"

template<class T>
class Rectangle: public Point2D<T> {
 protected:
  T width, height;
 public:

  Rectangle(): width(1), height(1) {}

  Rectangle(T x, T y, T width, T height);

  T getWidth() const;

  T getHeight() const;

  void setWidth(T newWidth);

  void setHeight(T newHeight);

  float area() const;

  float circumference() const;

};

//Parametrized constructor
template<class T>
Rectangle<T>::Rectangle(T x, T y, T width, T height) {
  this->x = x;
  this->y = y;

  if(width <= 0 || height <= 0) {//When width or height <= 0, throw Exception
    throw CustomException(33);
  }
  else {
    this->width = width;
    this->height = height;
  }
}

//Get width
template<class T>
T Rectangle<T>::getWidth() const {
  return width;
}

//Get height
template<class T>
T Rectangle<T>::getHeight() const {
  return height;
}

//Set Width
template<class T>
void Rectangle<T>::setWidth(T newWidth) {
  width = newWidth;
}

//Set Height
template<class T>
void Rectangle<T>::setHeight(T newHeight) {
  height = newHeight;
}

//Calculate the area
template<class T>
float Rectangle<T>::area() const {
  return width * height;
}

//Calculate the circumference
template<class T>
float Rectangle<T>::circumference() const {
  return 2 * (width + height);
}