#include <stdio.h>

double sum;

double Fi(int x, unsigned int i) {
  double res;
  if (i == 0) {
    res = x;
  } else {
    res = (Fi(x, i - 1) * (2.0 * i - 1.0) * (2.0 * i - 1.0) * x * x / (2.0 * i * (2.0 * i + 1.0)));
  }
  sum += res;
  return res;
}

int main() {
  int x = -1, i = 5;
  Fi(x, i);
  double arccos = (3.14 / 2) - sum;
  printf("The result of arccos(%d) = %f (lab 1-2)", x, arccos);
}