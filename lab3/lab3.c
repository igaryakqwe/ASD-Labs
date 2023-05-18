#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Lab 3";

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

double **mulmr(double **matrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] *= 1.0 - 0.02 - 0.005 - 0.25;
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

void freeMatrix(double **matrix, int n) {
  for (int i = 0; i < n; ++i) {
    free(matrix[i]);
  }
  free(matrix);
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
          "Lab 3. Novykov Ihor",
          WS_OVERLAPPEDWINDOW,
          100,
          100,
          900,
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
  HWND DIRECTED_BUTTON;
  HWND UNDIRECTED_BUTTON;
  const int DIRECTED =  1;
  const int UNDIRECTED = 2;
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
      }
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      char* nn[11] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10\0", "11\0"};
      int nx[11] = { 100,200,300, 400, 500, 450, 400, 350, 300, 200, 150 };
      int ny[11] = { 100,100,100, 100, 100, 200, 300, 400, 500, 350, 250 };
      int dx = 20, dy = 20, dtx = 4;
      int i;
      HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
      HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
      SelectObject(hdc, KPen);
      if (buttonState) {
        Rectangle(hdc, 0, 0, 900, 700);
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
      } else {
        Rectangle(hdc, 0, 0, 900, 700);
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

      SelectObject(hdc, BPen);
      for (i = 0; i <= 10; i++) {
        Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
      }

      double **T = randm(11);
      double **A = mulmr( T, 11);

      TextOut(hdc, 600, 50, (LPCSTR) L"Directed", 18);
      printMatrix(A, 11, 600, 50, hdc);

      double **R = randm(11);
      double **S = symmetricMatrix(mulmr(R, 11), 11);

      TextOut(hdc, 600, 260, (LPCSTR) L"Undirected", 28);
      printMatrix(S, 11, 600, 260, hdc);

      EndPaint(hWnd, &ps);

      freeMatrix(A, 11);
      freeMatrix(S, 11);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return(DefWindowProc(hWnd, messg, wParam, lParam));
  }
}