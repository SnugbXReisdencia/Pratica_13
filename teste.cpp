#include <iostream>
#include <vector>

int main() {
    std::vector<int> myVector(40, -1);

    // Print the vector to verify the initialization
    for (int i = 0; i < myVector.size(); i++) {
        std::cout << myVector[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}