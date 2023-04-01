#include <stdio.h>

double sum;

double Fi(int x, double i, double p) {
  double res;
  if (i == 0) {
    res = x;
  } else {
    p = Fi(x, i - 1, p);
    double factor = (2.0 * i - 1.0) * (2.0 * i - 1.0) * x * x / (2.0 * i * (2.0 * i + 1.0));
    res = p * factor;
  }
  sum += res;
  return res;
}

int main() {
  int x = -1, i = 5, p = 1;
  Fi(x, i, p);
  double arccos = 3.14 / 2 - sum;
  printf("The result of arccos(%d) = %f (lab 1-3)", x, arccos);
}