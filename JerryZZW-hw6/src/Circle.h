#pragma once

#include "Point2D.h"
#include "CustomException.h"

template<class T>
class Circle: public Point2D<T> {
 protected:
  T radius;
 public:

  Circle(): radius(1) {}

  Circle(T x, T y, T radius);

  T getRadius() const;

  void setRadius(T newRadius);

  float area() const;

  float circumference() const;

};

//Parametrized constructor
template<class T>
Circle<T>::Circle(T x, T y, T radius) {
  this->x = x;
  this->y = y;

  if(radius <= 0) {//When radius <= 0, throw Exception
    throw CustomException(22);
  }
  else {
    this->radius = radius;
  }
}

//Get radius
template<class T>
T Circle<T>::getRadius() const {
  return radius;
}

//Set radius
template<class T>
void Circle<T>::setRadius(T newRadius) {
  radius = newRadius;
}

//Calculate the area
template<class T>
float Circle<T>::area() const {
  return 3.14 * radius * radius;
}

//Calculate the circumference
template<class T>
float Circle<T>::circumference() const {
  return 2 * 3.14 * radius;
}