#include <iostream>
#include <vector>

class Point2D {
public:
    int x, y;

    Point2D(int x, int y) : x(x), y(y) {}
};

class Quadrilateral {
public:
    Point2D A, B, C, D;

    Quadrilateral(Point2D A, Point2D B, Point2D C, Point2D D) : A(A), B(B), C(C), D(D) {}
};

void drawQuadrilateral(Quadrilateral quad, std::vector<std::vector<char>>& grid) {
    // Draw the edges of the quadrilateral on the grid
    for (int i = quad.A.x; i < quad.B.x; ++i) grid[quad.A.y][i] = '-';
    for (int i = quad.B.y; i < quad.C.y; ++i) grid[i][quad.B.x] = '|';
    for (int i = quad.C.x; i > quad.D.x; --i) grid[quad.C.y][i] = '-';
    for (int i = quad.D.y; i > quad.A.y; --i) grid[i][quad.D.x] = '|';
}

int main() {
    int width = 100, height = 100;
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));

    // Define the quadrilateral vertices
    Point2D A(10, 10), B(90, 10), C(90, 90), D(10, 90);
    Quadrilateral quad(A, B, C, D);

    drawQuadrilateral(quad, grid);

    // Print the grid
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}
