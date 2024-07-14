#include "erdos-gallai.hpp"

int main() {
    int n;
    std::cin >> n;
    std::vector<int> seq(n);
    for (int i = 0; i < n; i++) std::cin >> seq[i];

    std::sort(seq.begin(), seq.end(), std::greater<int>());

    if (CheckErdosGallai(seq)) {
        std::cout << "Yes" << std::endl;
        auto mat = StructGraph(seq);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << mat[i][j] << (j < n - 1 ? " ": "\n");
            }
        }
    } else {
        std::cout << "No" << std::endl;
    }
}