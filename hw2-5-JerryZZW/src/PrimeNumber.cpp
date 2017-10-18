#include "PrimeNumber.h"
#include <math.h>

//The method to check if the number is a prime number
bool isPrime(int num ) {
  int count = 0;
  for (int i = 1; i <= num; i++) {
    if ((num % i == 0) && (i != 1 && i != num)) {
      count++;
    }
  }

  return count > 0 ? false : true;
}//end isPrime

//The method to return the nth prime number
int PrimeNumber(int input) {
  int count = 0;

  if (input <= 0) {
    return -1;
  }
  else {
    for (int candidate = 2;; candidate++) {
      if (isPrime(candidate)) {//check if the number is a prime number
        count++;
        if (input == count) {//if the prime number is the nth prime number, return it.
          return candidate;
        }
      }
    }
  }
}//end PrimeNumber

