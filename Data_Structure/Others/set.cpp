#include <iostream>
#include <set>

int main() {
    std::set<int> numbers = {5, 3, 1, 4, 2};

    numbers.insert(6);    // Add element to the set
    numbers.erase(3);     // Remove element from the set

    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";  // Access elements using iterators
    }

    return 0;
}