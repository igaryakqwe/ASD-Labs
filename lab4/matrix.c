#include "stdio.h"
#include "stdlib.h"

double **randm(int n) {
  srand(2214);
  double **matrix = (double **) malloc(sizeof(double *) * n);
  for (int i = 0; i < n; i++) {
    matrix[i] = (double *) malloc(sizeof(double) * n);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = (double) (rand() * 2.0) / (double) RAND_MAX;
    }
  }
  return matrix;
}

double **mulmr(double **matrix, double coefficient, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] *= coefficient;
      matrix[i][j] = matrix[i][j] < 1 ? 0 : 1;
    }
  }
  return matrix;
}

double **symmetricMatrix(double **matrix, int n) {
  double **symmetrical = (double **) malloc(n * sizeof(double *));
  for (int i = 0; i < n; ++i) {
    symmetrical[i] = (double *) malloc(n * sizeof(double));
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      symmetrical[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (symmetrical[i][j] != symmetrical[j][i]) {
        symmetrical[i][j] = 1;
        symmetrical[j][i] = 1;
      }
    }
  }
  return symmetrical;
}

void printMatrix (double **matrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", (int)matrix[i][j]);
    }
    printf("\n");
  }
}


typedef struct {
    int *outgoingEdges;
    int *outDegree;
    int *inDegree;
} GraphInfo;

void countDegrees(double **matrix, int n, GraphInfo *graphInfo) {
  graphInfo->outgoingEdges = (int *)malloc(sizeof(int) * n);
  graphInfo->outDegree = (int *)malloc(sizeof(int) * n);
  graphInfo->inDegree = (int *)malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    graphInfo->outgoingEdges[i] = 0;
    graphInfo->outDegree[i] = 0;
    graphInfo->inDegree[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == 1) {
        graphInfo->outgoingEdges[i]++;
        graphInfo->outDegree[i]++;
        graphInfo->inDegree[j]++;
      }
    }
  }
}

void printDegrees(double **matrix, double **symmetricMatrix, int n, int state) {
  GraphInfo graphInfo;
  GraphInfo undirectedGraphInfo;

  countDegrees(matrix, n, &graphInfo);
  countDegrees(symmetricMatrix, n, &undirectedGraphInfo);

  for (int i = 0; i < n; i++) {
    if (!state) {
      printf("%d vertex: %d edges\n", i + 1, undirectedGraphInfo.outgoingEdges[i]);
    } else {
      printf("%d vertex: %d edges, %d outgoing, %d ingoing\n", i + 1, undirectedGraphInfo.outgoingEdges[i], graphInfo.outDegree[i], graphInfo.inDegree[i]);
    }
  }
}

double** squareMatrix(double** matrix, int n) {
  double** result = (double**)malloc(sizeof(double*) * n);
  for (int i = 0; i < n; i++) {
    result[i] = (double*)malloc(sizeof(double) * n);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[i][j] = 0.0;
      for (int k = 0; k < n; k++) {
        result[i][j] += matrix[i][k] * matrix[k][j];
      }
    }
  }

  return result;
}

void printPathsOfLengthTwo(double** matrix, int n) {
  printf("Paths of length 2:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] >= 2) {
        for (int k = 0; k < n; k++) {
          if (matrix[j][k] >= 1 && k != i) {
            printf("(%d, %d, %d)\n", i, j, k);
          }
        }
      }
    }
  }
  printf("\n");
}

double** cubeMatrix(double** matrix, int n) {
  double** temp = (double**)malloc(sizeof(double*) * n);
  double** result = (double**)malloc(sizeof(double*) * n);

  for (int i = 0; i < n; i++) {
    temp[i] = (double*)malloc(sizeof(double) * n);
    result[i] = (double*)malloc(sizeof(double) * n);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] = 0.0;
      for (int k = 0; k < n; k++) {
        temp[i][j] += matrix[i][k] * matrix[k][j];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[i][j] = 0.0;
      for (int k = 0; k < n; k++) {
        result[i][j] += temp[i][k] * matrix[k][j];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    free(temp[i]);
  }
  free(temp);

  return result;
}

void printPathsOfLengthThree(double **matrix, int n) {\
  printf("Paths of length 3:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] >= 3) {
        for (int k = 0; k < n; k++) {
          if (matrix[j][k] >= 2 && k != i) {
            for (int l = 0; l < n; l++) {
              if (matrix[k][l] >= 1 && l != i && l != j) {
                printf("(%d, %d, %d, %d)\n", i, j, k, l);
              }
            }
          }
        }
      }
    }
  printf("\n");
  }
}

double** multiplyMatrices(double** A, double** B, int n) {
  int i, j, k;
  double** result = malloc(n * sizeof(double*));
  for (i = 0; i < n; i++) {
    result[i] = malloc(n * sizeof(double));
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      result[i][j] = 0;
      for (k = 0; k < n; k++) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return result;
}

double** sumMatrices(double** matrix, int n, int power) {
  int i, j, k;
  double** result = malloc(n * sizeof(double*));
  for (i = 0; i < n; i++) {
    result[i] = malloc(n * sizeof(double));
    for (j = 0; j < n; j++) {
      result[i][j] = matrix[i][j];
    }
  }

  for (k = 2; k <= power; k++) {
    double** temp = multiplyMatrices(matrix, matrix, n);

    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        result[i][j] += temp[i][j];
      }
    }

    for (i = 0; i < n; i++) {
      free(temp[i]);
    }
    free(temp);
  }

  return result;
}

double **singleMatrix(int n) {
  double** matrix = malloc(n * sizeof(double*));
  int i, j;

  for (i = 0; i < n; i++) {
    matrix[i] = malloc(n * sizeof(double));
    for (j = 0; j < n; j++) {
      if (i == j) {
        matrix[i][j] = 1.0;
      } else {
        matrix[i][j] = 0.0;
      }
    }
  }

  return matrix;
}

double** addMatrices(double** A, double** B, int n) {
  double** result = malloc(n * sizeof(double*));
  int i, j;

  for (i = 0; i < n; i++) {
    result[i] = malloc(n * sizeof(double));
    for (j = 0; j < n; j++) {
      result[i][j] = A[i][j] + B[i][j];
    }
  }

  return result;
}

double **reachMatrix(double **matrix, int n) {
  double **transitMatrix = addMatrices(sumMatrices(matrix, n, n - 1), singleMatrix(n), n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (transitMatrix[i][j] > 0) {
        transitMatrix[i][j] = 1.0;
      } else {
        transitMatrix[i][j] = 0.0;
      }
    }
  }
  return transitMatrix;
}


int** findStronglyConnectedComponents(double** matrix, int n, int* componentCount) {
  int* visited = malloc(n * sizeof(int));
  int* component = malloc(n * sizeof(int));
  *componentCount = 0;

  for (int i = 0; i < n; i++) {
    visited[i] = 0;
    component[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      visited[i] = 1;
      component[i] = (*componentCount);

      for (int j = 0; j < n; j++) {
        if (matrix[i][j] == matrix[j][i] && !visited[j]) {
          visited[j] = 1;
          component[j] = (*componentCount);
        }
      }

      (*componentCount)++;
    }
  }

  int** components = malloc((*componentCount) * sizeof(int*));
  int* componentSizes = calloc((*componentCount), sizeof(int));

  for (int i = 0; i < n; i++) {
    componentSizes[component[i]]++;
  }

  for (int i = 0; i < (*componentCount); i++) {
    components[i] = malloc((componentSizes[i] + 1) * sizeof(int));
    components[i][0] = componentSizes[i];
    int index = 1;
    for (int j = 0; j < n; j++) {
      if (component[j] == i) {
        components[i][index++] = j + 1;
      }
    }
  }

  free(visited);
  free(component);
  free(componentSizes);

  return components;
}




double** transposeMatrix(double** matrix, int n) {
  double** transposedMatrix = malloc(n * sizeof(double*));

  for (int i = 0; i < n; i++) {
    transposedMatrix[i] = malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      transposedMatrix[i][j] = matrix[j][i];
    }
  }

  return transposedMatrix;
}

double** buildCondensationMatrix(int** components, int componentCount) {
  double** condensationMatrix = malloc(componentCount * sizeof(double*));
  for (int i = 0; i < componentCount; i++) {
    condensationMatrix[i] = calloc(componentCount, sizeof(double));
  }

  for (int i = 0; i < componentCount; i++) {
    int componentSize = components[i][0];
    for (int j = 1; j <= componentSize; j++) {
      int vertex = components[i][j];
      for (int k = 0; k < componentCount; k++) {
        if (k != i) {
          condensationMatrix[i][k] = 1.0;
          condensationMatrix[k][i] = 1.0;
        }
      }
    }
  }

  return condensationMatrix;
}



int main() {
  int n = 11;
  double **T = randm(n);
  double **A = mulmr(T, 1.0 - 0.01 - 0.04 - 0.3, n);
  double **R = randm(n);
  double **S = symmetricMatrix(mulmr(R, 1.0 - 0.01 - 0.04 - 0.3, n), n);

  printf("Modified Matrix:\n");
  printMatrix(A, n);
  printDegrees(A, S, 11, 1);

  printf("Square matrix:\n");
  printMatrix(squareMatrix(A, n), n);
  printf("\n");

  printf("Modified Symmetric Matrix:\n");
  printMatrix(S, n);
  printDegrees(A, S, 11, 0);

  printPathsOfLengthTwo(squareMatrix(A, n), n);
  printPathsOfLengthThree(cubeMatrix(A, n), n);

  printf("Reach matrix:\n");
  printMatrix(reachMatrix(A, n), n);
  printf("\n");

  double **squaredReachMatrix = squareMatrix(reachMatrix(A, n), n);
  int componentCount;
  int** components = findStronglyConnectedComponents(squaredReachMatrix, n, &componentCount);

  printf("Strongly connected components:\n");
  for (int i = 0; i < componentCount; i++) {
    printf("Component %d: ", i + 1);
    int componentSize = components[i][0];
    for (int j = 1; j <= componentSize; j++) {
      printf("%d ", components[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  double **strongMatrix = multiplyMatrices(transposeMatrix(reachMatrix(A, n), n), reachMatrix(A, n), n);
  printf("Strong matrix:\n");
  printMatrix(strongMatrix, n);
  printMatrix(buildCondensationMatrix(components, 5), 5);
  return 0;
}