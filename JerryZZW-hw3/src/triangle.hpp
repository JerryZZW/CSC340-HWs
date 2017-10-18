#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include "triangle_Interface.hpp"


using namespace std;

template<class T>
class Triangle: public triangleInterface<T> {

 private :
  T side1, side2, side3;

 public :


  //TODO: Implement ALL methods that are in triangle_interface.hpp

  Triangle();

  Triangle(T side1, T side2, T side3);

  /** Sets or modifies the sides of this triangle. Ensures that the new sides form a triangle. */
  void setSides(T newSide1, T newSide2, T newSide3) override;

  /** Gets the three sides of this triangle.
   * @return A vector containing the values of the sides. */
  std::vector<T> getSides() const override;

  /** Computes the area of this triangle. @return This triangle's area. */
  T getArea() const override;

  /** Computes the perimeter of this triangle. @return This triangle's perimeter. */
  //TODO define the perimeter function(look at the interfe)
  T getPerimeter() const override;

  /** @return True if this triangle is a right triangle. */
  bool isRightTriangle() const override;

  /** @return True if this triangle is an equilateral triangle. */
  //TODO define the Equilateral... function(look at the interfe)
  bool isEquilateral() const override;

  /** @return True if this triangle is an isosceles triangle. */
  bool isIsosceles() const override;

};

//Default constructor
template<class T>
Triangle<T>::Triangle() {
  //TODO
  //set the default values
  side1 = 3;
  side2 = 4;
  side3 = 5;

}

//Parametrized constructor
template<class T>
Triangle<T>::Triangle(T side1, T side2, T side3) {
  //TODO
  //Set the values of the sides when the user input form a triangle
  if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1) {
    this->side1 = side1;
    this->side2 = side2;
    this->side3 = side3;
  }
  else {//When inputs don't form a triangle, set the values of sides to 0
    this->side1 = 0;
    this->side2 = 0;
    this->side3 = 0;
  }
}

/** Set the values of all sides */
template<class T>
void Triangle<T>::setSides(T newSide1, T newSide2, T newSide3) {
  //TODO
  //Set the values of the sides when the user input form a triangle
  if (newSide1 + newSide2 > newSide3 && newSide1 + newSide3 > newSide2 && newSide2 + newSide3 > newSide1) {
    side1 = newSide1;
    side2 = newSide2;
    side3 = newSide3;
  }
  else {//When inputs don't form a triangle, set the values of sides to 0
    side1 = 0;
    side2 = 0;
    side3 = 0;
  }
}

/** Gets the three sides of this triangle.
 * @return A vector containing the values of the sides. */
template<class T>
std::vector<T> Triangle<T>::getSides() const {
  //TODO
  vector<T> sides = {side1,side2,side3};
  return sides;
}

/** Computes the area of this triangle. @return This triangle's area. */
template<class T>
T Triangle<T>::getArea() const {
  //TODO
  double p = (side1 + side2 + side3)/2.0;
  T area = std::sqrt(p*(p-side1)*(p-side2)*(p-side3));
  return area;
}

/** Computes the perimeter of this triangle. @return This triangle's perimeter. */
template<class T>
T Triangle<T>::getPerimeter() const {
  //TODO
  return side1 + side2 + side3;
}

//TODO declare+implement the missing method isRightTriangle()
/** @return True if this triangle is an right triangle. */
template<class T>
bool Triangle<T>::isRightTriangle() const {
  if (side1 > side2 && side1 > side3) {
    if (side1*side1 == side2*side2 + side3*side3) {
      return true;
    }
    else {
      return false;
    }
  }
  else if (side2 > side1 && side2 > side3) {
    if (side2*side2 == side1*side1 + side3*side3) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if (side3*side3 == side1*side1 + side2*side2) {
      return true;
    }
    else {
      return false;
    }
  }
}

/** @return True if this triangle is an equilateral triangle. */
template<class T>
bool Triangle<T>::isEquilateral() const {
  //TODO
  if (side1 == side2 && side2 == side3) {
    return true;
  }
  else {
    return false;
  }
}

//TODO declare+implement the missing method isIsosceles()
/** @return True if this triangle is an isosceles triangle. */
template<class T>
bool Triangle<T>::isIsosceles() const {
  if(side1 == side2) {
    return true;
  }
  else if (side1 == side3) {
    return true;
  }
  else if (side2 == side3) {
    return true;
  }
  else {
    return false;
  }
}