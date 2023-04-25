#include <iostream>
#include <fstream>
#include <vector>

enum ObjectType {
    Wall = 0,
    Street = 1,
    Mission = 3
};

class Graph {
public:
    std::vector<std::vector<int>> grid;

    Graph(int width, int height) : grid(height, std::vector<int>(width, 0)) {}

    void setObject(int x, int y, int obj_type) {
        grid[y][x] = obj_type;
    }
};

Graph readGraphFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }

    int height = lines.size();
    int width = lines[0].size();
    Graph graph(width, height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int obj_type = lines[y][x] - '0';
            graph.setObject(x, y, obj_type);
        }
    }

    return graph;
}

int main() {
    const std::string filename = "not_crucial/chatGPT/input7.txt";
    Graph graph = readGraphFromFile(filename);

    // Display the graph
    for (const auto& row : graph.grid) {
        for (int obj_type : row) {
            std::cout << obj_type;
        }
        std::cout << std::endl;
    }

    return 0;
}
