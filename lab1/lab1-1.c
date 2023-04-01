#include <stdio.h>

double Fi(int x, unsigned int i, double cur, double sum) {
  double res;
  if (i == 0) {
    res = x;
    sum += res;
  } else {
    cur = Fi(x, i - 1, cur, sum);
    double factor = (2.0 * i - 1.0) * (2.0 * i - 1.0) * x * x / (2.0 * i * (2.0 * i + 1.0));
    res = cur * factor;
    sum += res;
  }
  res += sum;
  return res;
}

int main() {
  int x = 1, i = 5;
  double sum = 0, cur = 1;
  double arccos = 3.14 / 2 - Fi(x, i, cur, sum);
  printf("The result of arccos(%d) = %f (lab 1-1)", x, arccos);
}
