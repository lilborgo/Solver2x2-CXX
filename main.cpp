#include <iostream>
#include <Solver2x2.h>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

int main() {
    auto t1 = Clock::now();
    Solver2x2::init();
    auto t2 = Clock::now();

    std::cout << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " ms" << std::endl;

    t1 = Clock::now();
    std::cout << Solver2x2::solve("RYWOGBOROYWBBYOWYBGRRGGW") << std::endl;
    t2 = Clock::now();

    std::cout << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " ms" << std::endl;

    Solver2x2::deinit();

    return 0;
}
