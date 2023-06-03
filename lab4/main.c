#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Lab 4";

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

typedef struct {
    int *outgoingEdges;
    int *outDegree;
    int *inDegree;
} GraphInfo;

int *countDegrees(double **matrix, int n) {
  GraphInfo *graphInfo = (GraphInfo *)malloc(sizeof(GraphInfo));
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

  return graphInfo;
}

void printDegrees (int *matrix, int *symetricMatrix ,int n, int state, int initialY, HDC hdc) {
  GraphInfo *graphInfo = countDegrees(matrix, 11);
  GraphInfo *undirectedGraphInfo = countDegrees(symetricMatrix, 11);
  for (int i = 0; i < n; i++) {
    if (!state) {
      char buffer[256];
      snprintf(buffer, sizeof(buffer), "%d vertex: %d edges ", i + 1, undirectedGraphInfo->outgoingEdges[i]);
      TextOut(hdc, 850, initialY + (i * 20), buffer, strlen(buffer));
    } else {
      char buffer[256];
      snprintf(buffer, sizeof(buffer), "%d vertex: %d edges, %d outgoing , %d ingoing ", i + 1, undirectedGraphInfo->outgoingEdges[i] , graphInfo->outDegree[i], graphInfo->inDegree[i]);
      TextOut(hdc, 850, initialY+ (i * 20), buffer, strlen(buffer));
    }
  }
}


void freeMatrix(double **matrix, int n) {
  for (int i = 0; i < n; ++i) {
    free(matrix[i]);
  }
  free(matrix);
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

void printMatrix(double **matrix, int n, int initialX, int initialY, HDC hdc) {
  for (int i = 0, y = initialY + 30; i < n; i++, y += 15) {
    for (int j = 0, x = initialX; j < n; j++, x += 13) {
      wchar_t buffer[2];
      swprintf(buffer, 2, L"%lf", matrix[i][j]);
      TextOut(hdc, x, y, (LPCSTR) buffer, 1);
    }
    MoveToEx(hdc, initialX, y, NULL);
  }
}

int checkEqualDegrees(int *matrix, int n) {
  int outDegree = 0;
  for (int j = 0; j < n; j++) {
    outDegree += matrix[j];
  }
  for (int i = 1; i < n; i++) {
    int currOutDegree = 0;
    for (int j = 0; j < n; j++) {
      currOutDegree += matrix[i * n + j];
    }
    if (currOutDegree != outDegree) {
      return 0;
    }
  }
  return 1;
}


void printRegularInfo(int *matrix, int n, int initialY, HDC hdc) {
  int isRegular = checkEqualDegrees(matrix, n);

  char buffer[256];
  if (isRegular) {
    snprintf(buffer, sizeof(buffer), "The graph is regular");
  } else {
    snprintf(buffer, sizeof(buffer), "The graph isn't regular");
  }

  TextOut(hdc, 850, initialY, buffer, strlen(buffer));
}

void findIsolatedAndHangingVertices(int **matrix, int n, HDC hdc, int initialY) {
  char buffer[256];
  int isolatedCount = 0;
  int hangingCount = 0;
  int* isolatedVertices = (int*)malloc(n * sizeof(int));
  int* hangingVertices = (int*)malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    int degree;
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == 1) {
        degree++;
      }
    }

    if (degree == 0) {
      isolatedVertices[isolatedCount++] = i + 1;
    } else if (degree == 1) {
      hangingVertices[hangingCount++] = i + 1;
    }
  }

  snprintf(buffer, sizeof(buffer), "Isolated vertices:");
  TextOut(hdc, 1150, initialY, buffer, strlen(buffer));
  initialY += 20;
  if (isolatedCount > 0) {
    for (int i = 0; i < isolatedCount; i++) {
      snprintf(buffer, sizeof(buffer), "%d", isolatedVertices[i]);
      TextOut(hdc, 1150, initialY, buffer, strlen(buffer));
      initialY += 20;
    }
  } else {
    snprintf(buffer, sizeof(buffer), "No isolated vertices");
    TextOut(hdc, 1150, initialY, buffer, strlen(buffer));
    initialY += 20;
  }

  snprintf(buffer, sizeof(buffer), "Hanging vertices:");
  TextOut(hdc, 1150, initialY, buffer, strlen(buffer));
  initialY += 20;
  if (hangingCount > 0) {
    for (int i = 0; i < hangingCount; i++) {
      snprintf(buffer, sizeof(buffer), "%d", hangingVertices[i]);
      TextOut(hdc, 1150, initialY, buffer, strlen(buffer));
      initialY += 20;
    }
  } else {
    snprintf(buffer, sizeof(buffer), "No hanging vertices");
    TextOut(hdc, 1150, initialY, buffer, strlen(buffer));
  }

  free(isolatedVertices);
  free(hangingVertices);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
  WNDCLASS w;
  w.lpszClassName = ProgName;
  w.hInstance = hInstance;
  w.lpfnWndProc = WndProc;
  w.hCursor = LoadCursor(NULL, IDC_ARROW);
  w.hIcon = 0;
  w.lpszMenuName = 0;
  w.hbrBackground = WHITE_BRUSH;
  w.style = CS_HREDRAW | CS_VREDRAW;
  w.cbClsExtra = 0;
  w.cbWndExtra = 0;

  if (!RegisterClass(&w)) {
    return 0;
  }

  HWND hWnd;
  MSG lpMsg;
  hWnd = CreateWindow(
          ProgName,
          "Lab 4. Novykov Ihor",
          WS_OVERLAPPEDWINDOW,
          100,
          100,
          1300,
          700,
          (HWND)NULL,
          (HMENU)NULL,
          (HINSTANCE)hInstance,
          (HINSTANCE)NULL
        );

  ShowWindow(hWnd, nCmdShow);

  while (GetMessage(&lpMsg, hWnd, 0, 0)) {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
  }
  return(lpMsg.wParam);
}

HDC hdc;
PAINTSTRUCT ps;
void arrow(float fi, int px, int py, HDC pHdc) {
  fi = 3.1416 * (180.0 - fi) / 180.0;
  int lx, ly, rx, ry;
  lx = px + 15 * cos(fi + 0.3);
  rx = px + 15 * cos(fi - 0.3);
  ly = py + 15 * sin(fi + 0.3);
  ry = py + 15 * sin(fi - 0.3);
  MoveToEx(hdc, lx, ly, NULL);
  LineTo(hdc, px, py);
  LineTo(hdc, rx, ry);
}

void Line(int node1, int node2, int nx[], int ny[]) {
  MoveToEx(hdc, nx[node1 - 1], ny[node1 - 1], NULL);
  LineTo(hdc, nx[node2 - 1], ny[node2 - 1]);
}

void printUndirectedGraph(char *nn, int nx[], int ny[], double **symmetricMatrix, int n, HDC hdc) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (symmetricMatrix[i][j] == 1) {
        if (i == j) {
          Ellipse(hdc, nx[i] + 30, ny[j] + 50, nx[j] - 30, ny[i]);
        } else if (j == 0 || j == 1) {
          Arc(hdc, nx[1], ny[1] - 40, nx[4], ny[4] + 40, nx[4], ny[4], nx[1], ny[1]);
          Arc(hdc, nx[0], ny[0] - 40, nx[3], ny[3] + 40, nx[3], ny[3], nx[0], ny[0]);
        } else if ((i == 4 && j == 6) || (i == 5 && j == 7)) {
          Arc(hdc, nx[5] + 40, ny[5] - 40, nx[7] - 40, ny[7] + 40, nx[7], ny[7], nx[5] + 40, ny[5] - 40);
          Arc(hdc, nx[4] + 40, ny[4] - 40, nx[6] - 40, ny[6] + 40, nx[6], ny[6], nx[4] + 40, ny[4] - 40);
        } else {
          MoveToEx(hdc, nx[i], ny[i], NULL);
          LineTo(hdc, nx[j], ny[j]);
        }
      }
    }
  }
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
  HWND DIRECTED_BUTTON;
  HWND UNDIRECTED_BUTTON;
  HWND MODIFIED_DIRECTED_BUTTON;
  HWND MODIFIED_UNDIRECTED_BUTTON;
  HWND CONDENSATION_BUTTON;

  const int DIRECTED =  1;
  const int UNDIRECTED = 2;
  const int MODIFIED_DIRECTED = 3;
  const int MODIFIED_UNDIRECTED = 4;
  const int CONDENSATION = 5;
  int buttonState = 1;
  switch (messg) {
    case WM_CREATE:
      DIRECTED_BUTTON = CreateWindow(
              (LPCSTR) "BUTTON",
              (LPCSTR) "Directed",
              WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
              550,
              500,
              130,
              30,
              hWnd,
              (HMENU) DIRECTED,
              (HINSTANCE) GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
              NULL);
      UNDIRECTED_BUTTON = CreateWindow(
              (LPCSTR) "BUTTON",
              (LPCSTR) "Undirected",
              WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
              700,
              500,
              130,
              30,
              hWnd,
              (HMENU) UNDIRECTED,
              (HINSTANCE) GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
              NULL);
      MODIFIED_DIRECTED_BUTTON = CreateWindow(
              (LPCSTR) "BUTTON",
              (LPCSTR) "Upgraded Directed",
              WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
              550,
              550,
              130,
              30,
              hWnd,
              (HMENU) MODIFIED_DIRECTED,
              (HINSTANCE) GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
              NULL);
      MODIFIED_UNDIRECTED_BUTTON = CreateWindow(
              (LPCSTR) "BUTTON",
              (LPCSTR) "Upgraded Undirected",
              WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
              700,
              550,
              130,
              30,
              hWnd,
              (HMENU) MODIFIED_UNDIRECTED,
              (HINSTANCE) GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
              NULL);
      CONDENSATION_BUTTON = CreateWindow(
              (LPCSTR) "BUTTON",
              (LPCSTR) "Condensation",
              WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
              625,
              600,
              130,
              30,
              hWnd,
              (HMENU) CONDENSATION,
              (HINSTANCE) GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
              NULL);
      break;
    case WM_COMMAND:
      switch (LOWORD(wParam)) {
        case DIRECTED:
          buttonState = 1;
          InvalidateRect(hWnd, NULL, FALSE);
          break;

        case UNDIRECTED:
          buttonState = 0;
          InvalidateRect(hWnd, NULL, FALSE);
          break;
        case MODIFIED_DIRECTED:
          buttonState = 2;
          InvalidateRect(hWnd, NULL, FALSE);
          break;
        case MODIFIED_UNDIRECTED:
          buttonState = 3;
          InvalidateRect(hWnd, NULL, FALSE);
          break;
        case CONDENSATION:
          buttonState = 4;
          InvalidateRect(hWnd, NULL, FALSE);
          break;
      }
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      if (buttonState != 4) {
        char* nn[11] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10\0", "11\0"};
        int nx[11] = { 100,200,300, 400, 500, 450, 400, 350, 300, 200, 150 };
        int ny[11] = { 100,100,100, 100, 100, 200, 300, 400, 500, 350, 250 };
        int dx = 20, dy = 20, dtx = 4;
        int i;
        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        SelectObject(hdc, KPen);

        if (buttonState != 2 && buttonState != 3) {
          if (buttonState == 1) {
            Rectangle(hdc, 0, 0, 1300, 700);
            // 1
            arrow(-60, nx[8] - dx * 0.4, ny[8] - dy * 0.9, NULL);
            arrow(-30.0, nx[3] - dx * 0.6, ny[3] - dy * 0.7, NULL);
            Line(1,2, nx, ny);
            Line(1,9,nx, ny);

            // 2
            Ellipse(hdc, nx[1] + 30, ny[1] - 50, nx[1] - 30, ny[1]);
            Line(2,3,nx, ny);
            Arc(hdc, nx[1], ny[1] - 40, nx[4], ny[4] + 40, nx[4], ny[4], nx[1], ny[1]);
            Line(2,6, nx, ny);
            Line(2,7, nx, ny);
            Line(2,8, nx, ny);
            Line(2,9, nx, ny);
            Line(2,10, nx, ny);
            Line(2,11, nx, ny);
            arrow(180,nx[0] + dx,ny[0], NULL);
            arrow(-130,nx[1] + dx,ny[1] - dy * 0.3, NULL);
            arrow(0,nx[2]-dx,ny[2], NULL);
            arrow(-30.0, nx[4] - dx * 0.6, ny[4] - dy * 0.7, NULL);
            arrow(-40.0, nx[6] - dx * 0.6, ny[6] - dy * 0.7, NULL);
            arrow(-60.0, nx[7] - dx * 0.5, ny[7] - dy, NULL);
            arrow(-75, nx[8] - dx * 0.2, ny[8] - dy, NULL);
            arrow(-100, nx[9] - dx * 0.1, ny[9] - dy * 0.9, NULL);
            arrow(-110.0, nx[10] - dx * -0.3, ny[10] - dy * 0.9, NULL);
            // 3
            arrow(180,nx[1] + dx,ny[1], NULL);
            arrow(-90,nx[8],ny[8] - dy, NULL);
            Line(3,8,nx, ny);
            Line(3,9,nx, ny);
            Line(3,10,nx, ny);

            //4
            Arc(hdc, nx[0], ny[0] - 40, nx[3], ny[3] + 40, nx[3], ny[3], nx[0], ny[0]);
            Line(4,5,nx, ny);
            Line(4,6,nx, ny);
            Line(4,7,nx, ny);
            Line(4,8,nx, ny);
            Line(4,9,nx, ny);
            arrow(0,nx[4]-dx,ny[4], NULL);
            arrow(-60.0, nx[5] - dx * 0.4, ny[5] - dy * 0.9, NULL);
            arrow(-90,nx[6],ny[6] - dy, NULL);
            arrow(-100.0, nx[7] - dx * -0.2, ny[7] - dy * 0.9, NULL);

            //5
            Arc(hdc, nx[4] + 40, ny[4] - 40, nx[6] - 40, ny[6] + 40, nx[6], ny[6], nx[4] + 40, ny[4] - 40);
            Line(5,11, nx,ny);
            MoveToEx(hdc, nx[4], ny[4], NULL);
            LineTo(hdc, nx[5] - 60, ny[5]);
            MoveToEx(hdc, nx[5] - 60, ny[5], NULL);
            LineTo(hdc, nx[7], ny[7]);
            MoveToEx(hdc, nx[4], ny[4], NULL);
            LineTo(hdc, nx[6] - 60, ny[6]);
            MoveToEx(hdc, nx[6] - 60, ny[6], NULL);
            LineTo(hdc, nx[8], ny[8]);
            arrow(-150.0, nx[1] - dx * -0.7, ny[1] - dy * 0.8, NULL);
            arrow(180,nx[3] + dx,ny[3], NULL);
            arrow(-220,nx[6] + dx * 0.3,ny[6] - dy * -1.0, NULL);
            arrow(-155.0, nx[10] - dx * -0.8, ny[10] - dy * 0.3, NULL);


            // 6
            Arc(hdc, nx[5] + 40, ny[5] - 40, nx[7] - 40, ny[7] + 40, nx[7], ny[7], nx[5] + 40, ny[5] - 40);
            Line(6,11,nx, ny);
            arrow(150,nx[1] + dx * 0.9,ny[1] - dy * -0.3 , NULL);
            arrow(-220,nx[7] + dx * 0.3,ny[7] - dy * -1.0, NULL);

            // 7
            Line(7,8,nx, ny);
            Line(7,11,nx, ny);
            arrow(-230, nx[1] + dx * 0.8, ny[1] + dy * 0.7, NULL);

            // 8
            arrow(-260, nx[2] + dx * 0.2, ny[2] + dy, NULL);
            arrow(70,nx[6] + dx * -0.5,ny[6] - dy * -0.9, NULL);

            // 9
            Ellipse(hdc, nx[8] + 30, ny[8] + 50, nx[8] - 30, ny[8]);
            arrow(80,nx[3] + dx * -0.2,ny[3] - dy * -0.9, NULL);
            arrow(65,nx[4] + dx * -0.7,ny[4] - dy * -0.8, NULL);
            arrow(50,nx[8] - dx * 0.9,ny[8] + dy * 0.2, NULL);

            // 10
            arrow(65,nx[2] + dx * -0.3,ny[2] - dy * -0.8, NULL);

            // 11
            arrow(0,nx[5]-dx,ny[5] + dy * 0.3, NULL);
            arrow(-10.0,nx[6]-dx,ny[6] - dy * 0.2, NULL);
          } else if (buttonState == 0) {
            Rectangle(hdc, 0, 0, 1300, 700);
            // 1
            Line(1,2, nx, ny);
            Line(1,9,nx, ny);

            // 2
            Ellipse(hdc, nx[1] + 30, ny[1] - 50, nx[1] - 30, ny[1]);
            Line(2,3,nx, ny);
            Arc(hdc, nx[1], ny[1] - 40, nx[4], ny[4] + 40, nx[4], ny[4], nx[1], ny[1]);
            Line(2,6, nx, ny);
            Line(2,7, nx, ny);
            Line(2,8, nx, ny);
            Line(2,9, nx, ny);
            Line(2,10, nx, ny);
            Line(2,11, nx, ny);


            // 3
            Line(3,8,nx, ny);
            Line(3,9,nx, ny);
            Line(3,10,nx, ny);

            //4
            Arc(hdc, nx[0], ny[0] - 40, nx[3], ny[3] + 40, nx[3], ny[3], nx[0], ny[0]);
            Line(4,5,nx, ny);
            Line(4,6,nx, ny);
            Line(4,7,nx, ny);
            Line(4,8,nx, ny);
            Line(4,9,nx, ny);

            //5
            Arc(hdc, nx[4] + 40, ny[4] - 40, nx[6] - 40, ny[6] + 40, nx[6], ny[6], nx[4] + 40, ny[4] - 40);
            Line(5,11, nx,ny);
            MoveToEx(hdc, nx[4], ny[4], NULL);
            LineTo(hdc, nx[5] - 60, ny[5]);
            MoveToEx(hdc, nx[5] - 60, ny[5], NULL);
            LineTo(hdc, nx[7], ny[7]);
            MoveToEx(hdc, nx[4], ny[4], NULL);
            LineTo(hdc, nx[6] - 60, ny[6]);
            MoveToEx(hdc, nx[6] - 60, ny[6], NULL);
            LineTo(hdc, nx[8], ny[8]);

            // 6
            Arc(hdc, nx[5] + 40, ny[5] - 40, nx[7] - 40, ny[7] + 40, nx[7], ny[7], nx[5] + 40, ny[5] - 40);
            Line(6,11,nx, ny);

            // 7
            Line(7,8,nx, ny);
            Line(7,11,nx, ny);

            // 9
            Ellipse(hdc, nx[8] + 30, ny[8] + 50, nx[8] - 30, ny[8]);
          }
          double **T = randm(11);
          double **A = mulmr(T, 1.0 - 0.02 - 0.005 - 0.25, 11);

          TextOut(hdc, 600, 50, (LPCSTR) L"Directed", 18);
          printMatrix(A, 11, 600, 50, hdc);

          double **R = randm(11);
          double **S = symmetricMatrix(mulmr(R, 1.0 - 0.02 - 0.005 - 0.25, 11), 11);

          TextOut(hdc, 600, 260, (LPCSTR) L"Undirected", 20);
          printMatrix(S, 11, 600, 260, hdc);

          GraphInfo *graphInfo = countDegrees(A, 11);
          TextOut(hdc, 850, 50, (LPCSTR) L"Directed degrees", 32);
          printDegrees(A, S, 11, 1, 70 ,hdc);
          printRegularInfo(A, 11, 290, hdc);

          TextOut(hdc, 850, 320, (LPCSTR) L"Undirected degrees", 36);
          printDegrees(A, S, 11, 0, 340 ,hdc);
          printRegularInfo(S, 11, 560, hdc);
          findIsolatedAndHangingVertices(S, 11, hdc, 50);

          free(graphInfo->outgoingEdges);
          free(graphInfo->outDegree);
          free(graphInfo->inDegree);
          free(graphInfo);

          freeMatrix(A, 11);
          freeMatrix(S, 11);
        } else if (buttonState == 2) {
          Rectangle(hdc, 0, 0, 1300, 700);
          double **T = randm(11);
          double **A = mulmr(T, 1.0 - 0.005 - 0.02 - 0.27, 11);

          // 1
          arrow(-60, nx[8] - dx * 0.4, ny[8] - dy * 0.9, NULL);
          arrow(-30.0, nx[3] - dx * 0.6, ny[3] - dy * 0.7, NULL);
          Line(1,2, nx, ny);
          Line(1,9,nx, ny);

          // 2
          Ellipse(hdc, nx[1] + 30, ny[1] - 50, nx[1] - 30, ny[1]);
          Line(2,3,nx, ny);
          Arc(hdc, nx[1], ny[1] - 40, nx[4], ny[4] + 40, nx[4], ny[4], nx[1], ny[1]);
          Line(2,6, nx, ny);
          Line(2,7, nx, ny);
          Line(2,8, nx, ny);
          Line(2,9, nx, ny);
          Line(2,10, nx, ny);
          Line(2,11, nx, ny);
          arrow(180,nx[0] + dx,ny[0], NULL);
          arrow(-130,nx[1] + dx,ny[1] - dy * 0.3, NULL);
          arrow(0,nx[2]-dx,ny[2], NULL);
          arrow(-30.0, nx[4] - dx * 0.6, ny[4] - dy * 0.7, NULL);
          arrow(-40.0, nx[6] - dx * 0.6, ny[6] - dy * 0.7, NULL);
          arrow(-60.0, nx[7] - dx * 0.5, ny[7] - dy, NULL);
          arrow(-75, nx[8] - dx * 0.2, ny[8] - dy, NULL);
          arrow(-100, nx[9] - dx * 0.1, ny[9] - dy * 0.9, NULL);
          arrow(-110.0, nx[10] - dx * -0.3, ny[10] - dy * 0.9, NULL);
          // 3
          arrow(180,nx[1] + dx,ny[1], NULL);
          arrow(-90,nx[8],ny[8] - dy, NULL);
          Line(3,8,nx, ny);
          Line(3,9,nx, ny);
          Line(3,10,nx, ny);

          //4
          Arc(hdc, nx[0], ny[0] - 40, nx[3], ny[3] + 40, nx[3], ny[3], nx[0], ny[0]);
          Line(4,5,nx, ny);
          Line(4,6,nx, ny);
          Line(4,7,nx, ny);
          Line(4,8,nx, ny);
          Line(4,9,nx, ny);
          arrow(0,nx[4]-dx,ny[4], NULL);
          arrow(-60.0, nx[5] - dx * 0.4, ny[5] - dy * 0.9, NULL);
          arrow(-90,nx[6],ny[6] - dy, NULL);
          arrow(-100.0, nx[7] - dx * -0.2, ny[7] - dy * 0.9, NULL);

          //5
          Arc(hdc, nx[4] + 40, ny[4] - 40, nx[6] - 40, ny[6] + 40, nx[6], ny[6], nx[4] + 40, ny[4] - 40);
          Line(5,11, nx,ny);
          MoveToEx(hdc, nx[4], ny[4], NULL);
          LineTo(hdc, nx[5] - 60, ny[5]);
          MoveToEx(hdc, nx[5] - 60, ny[5], NULL);
          LineTo(hdc, nx[7], ny[7]);
          MoveToEx(hdc, nx[4], ny[4], NULL);
          LineTo(hdc, nx[6] - 60, ny[6]);
          MoveToEx(hdc, nx[6] - 60, ny[6], NULL);
          LineTo(hdc, nx[8], ny[8]);
          arrow(-150.0, nx[1] - dx * -0.7, ny[1] - dy * 0.8, NULL);
          arrow(180,nx[3] + dx,ny[3], NULL);
          arrow(-220,nx[6] + dx * 0.3,ny[6] - dy * -1.0, NULL);
          arrow(-155.0, nx[10] - dx * -0.8, ny[10] - dy * 0.3, NULL);


          // 6
          Line(6,11,nx, ny);
          arrow(150,nx[1] + dx * 0.9,ny[1] - dy * -0.3 , NULL);

          // 7
          Line(7,8,nx, ny);
          Line(7,11,nx, ny);
          arrow(-230, nx[1] + dx * 0.8, ny[1] + dy * 0.7, NULL);

          // 8
          arrow(-260, nx[2] + dx * 0.2, ny[2] + dy, NULL);
          arrow(70,nx[6] + dx * -0.5,ny[6] - dy * -0.9, NULL);

          // 9
          Ellipse(hdc, nx[8] + 30, ny[8] + 50, nx[8] - 30, ny[8]);
          arrow(80,nx[3] + dx * -0.2,ny[3] - dy * -0.9, NULL);
          arrow(65,nx[4] + dx * -0.7,ny[4] - dy * -0.8, NULL);
          arrow(50,nx[8] - dx * 0.9,ny[8] + dy * 0.2, NULL);

          // 10
          arrow(65,nx[2] + dx * -0.3,ny[2] - dy * -0.8, NULL);

          // 11
          arrow(0,nx[5]-dx,ny[5] + dy * 0.3, NULL);
          arrow(-10.0,nx[6]-dx,ny[6] - dy * 0.2, NULL);

          TextOut(hdc, 600, 50, (LPCSTR) L"Directed", 18);
          printMatrix(A, 11, 600, 50, hdc);

          GraphInfo *graphInfo = countDegrees(A, 11);
          TextOut(hdc, 850, 50, (LPCSTR) L"Directed degrees", 32);
          printDegrees(A, A, 11, 1, 70 ,hdc);
          printRegularInfo(A, 11, 290, hdc);
        } else if (buttonState == 3) {
          Rectangle(hdc, 0, 0, 1300, 700);
          double **R = randm(11);
          double **S = symmetricMatrix(mulmr(R, 1.0 - 0.005 - 0.02 - 0.27, 11), 11);

          // 1
          Line(1,2, nx, ny);
          Line(1,9,nx, ny);

          // 2
          Ellipse(hdc, nx[1] + 30, ny[1] - 50, nx[1] - 30, ny[1]);
          Line(2,3,nx, ny);
          Arc(hdc, nx[1], ny[1] - 40, nx[4], ny[4] + 40, nx[4], ny[4], nx[1], ny[1]);
          Line(2,6, nx, ny);
          Line(2,7, nx, ny);
          Line(2,8, nx, ny);
          Line(2,9, nx, ny);
          Line(2,10, nx, ny);
          Line(2,11, nx, ny);


          // 3
          Line(3,8,nx, ny);
          Line(3,9,nx, ny);
          Line(3,10,nx, ny);

          //4
          Arc(hdc, nx[0], ny[0] - 40, nx[3], ny[3] + 40, nx[3], ny[3], nx[0], ny[0]);
          Line(4,5,nx, ny);
          Line(4,6,nx, ny);
          Line(4,7,nx, ny);
          Line(4,8,nx, ny);
          Line(4,9,nx, ny);

          //5
          Arc(hdc, nx[4] + 40, ny[4] - 40, nx[6] - 40, ny[6] + 40, nx[6], ny[6], nx[4] + 40, ny[4] - 40);
          Line(5,11, nx,ny);
          MoveToEx(hdc, nx[4], ny[4], NULL);
          LineTo(hdc, nx[5] - 60, ny[5]);
          MoveToEx(hdc, nx[5] - 60, ny[5], NULL);
          LineTo(hdc, nx[7], ny[7]);
          MoveToEx(hdc, nx[4], ny[4], NULL);
          LineTo(hdc, nx[6] - 60, ny[6]);
          MoveToEx(hdc, nx[6] - 60, ny[6], NULL);
          LineTo(hdc, nx[8], ny[8]);

          // 6
          Line(6,11,nx, ny);

          // 7
          Line(7,8,nx, ny);
          Line(7,11,nx, ny);

          // 9
          Ellipse(hdc, nx[8] + 30, ny[8] + 50, nx[8] - 30, ny[8]);

          TextOut(hdc, 600, 50, (LPCSTR) L"Undirected", 20);
          printMatrix(S, 11, 600, 50, hdc);

          GraphInfo *graphInfo = countDegrees(S, 11);
          TextOut(hdc, 850, 50, (LPCSTR) L"Undirected degrees", 32);
          printDegrees(S, S, 11, 0, 70 ,hdc);
          printRegularInfo(S, 11, 290, hdc);
        }
        SelectObject(hdc, BPen);
        for (i = 0; i <= 10; i++) {
          Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
          TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
        }
      } else if (buttonState == 4) {
        Rectangle(hdc, 0, 0, 1300, 700);
        char* nn[5] = {"K1", "K2", "K3", "K4", "K5"};
        int nx[5] = { 100,200,300, 250, 200 };
        int ny[5] = { 100,100,100, 200, 300 };
        int dx = 20, dy = 20, dtx = 4;
        int i;
        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        SelectObject(hdc, KPen);

        int n = 11;
        double **T = randm(n);
        double **A = mulmr(T, 1.0 - 0.01 - 0.04 - 0.3, n);
        double **R = randm(n);
        double **S = symmetricMatrix(mulmr(R, 1.0 - 0.01 - 0.04 - 0.3, n), n);
        double **squaredReachMatrix = squareMatrix(reachMatrix(A, n), n);
        int componentCount;
        int** components = findStronglyConnectedComponents(squaredReachMatrix, n, &componentCount);
        TextOut(hdc, 500, 50, (LPCSTR) L"Condensation", 24);
        printMatrix(buildCondensationMatrix(components, 5), 5, 500, 50, hdc);
        // K1
        Line(1, 2, nx, ny);
        Arc(hdc, nx[0], ny[0] - 40, nx[2], ny[2] + 40, nx[2], ny[2], nx[0], ny[0]);
        Line(1, 4, nx, ny);
        Line(1, 5, nx, ny);
        //K2
        Line(2, 3, nx, ny);
        Line(2, 4, nx, ny);
        Line(2, 5, nx, ny);
        //K3
        Line(3, 4, nx, ny);
        Arc(hdc, nx[2] + 40, ny[2] - 40, nx[4] - 40, ny[4] + 40, nx[4], ny[4], nx[2] + 40, ny[2] - 40);
        //K4
        Line(4, 5, nx, ny);

        SelectObject(hdc, BPen);
        for (i = 0; i <= 4; i++) {
          Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
          TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
        }
      }

      EndPaint(hWnd, &ps);

      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return(DefWindowProc(hWnd, messg, wParam, lParam));
  }
}
