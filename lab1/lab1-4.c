#include <stdio.h>

int main() {
	int x = -1;
	double Fi = 1, sum = 0, formule;
	for (int i = 0; i <= 5; i++) {
		if (i > 0) {
			formule = (2.0 * i - 1.0) * (2.0 * i - 1.0) * x * x / (2.0 * i * (2.0 * i + 1.0));
			Fi *= formule;
		} else {
			Fi = x;
		}
		sum += Fi;
	}
  
	double res = 3.14 / 2 - sum;
  printf("The result of arccos(%d) = %f (lab 1-4)", x, res);
}