#include <iostream>
#include <Solver2x2.h>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

int main() {
    auto t1 = Clock::now();

    //load file if existing, creating a new one if not.
    Solver2x2::loadFile("sol.s2c");

    auto t2 = Clock::now();

    std::cout << "Initialization: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms" << std::endl;

    //solve
    std::cout << Solver2x2::solve("RYWOGBOROYWBBYOWYBGRRGGW") << std::endl;

    //deinitialize
    Solver2x2::deinit();

    return 0;
}
