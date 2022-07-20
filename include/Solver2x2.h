/**
 * This is the main file for the Solver for 2x2 cubes.
 * Here you can initialize the solver, deinitialize and
 * solve the cube.
 * The cube must be given in a string in the following order:
 *
 * U1-U4 R1-R4 F1-F4 D1-D4 L1-L4 B1-B4
 *
 *          U1  U2
 *          U3  U4
 *  L1  L2  F1  F2  R1  R2  B1  B2
 *  L3  L4  F3  F4  R3  R4  B3  B4
 *          D1  D2
 *          D3  D4
 *
 *  You can give directly the color of the cube.
 */

#ifndef SOLVER2X2_CXX_SOLVER2X2_H
#define SOLVER2X2_CXX_SOLVER2X2_H

#include <string>

namespace Solver2x2 {

    /**
     * This is the initializer for the solver. It takes around 3 seconds for
     * a i5 processor. It also needs around 150 MB, but after the initialization
     * part of the memory will be deallocated automatically. It will remain 15 MB
     * used.
     */
    void init();

    /**
     * This is used to deallocate the solver.
     */
    void deinit();

    /**
     * Solve the cube.
     *
     * * The cube must be given in a string in the following order:
     *
     * U1-U4 R1-R4 F1-F4 D1-D4 L1-L4 B1-B4
     *
     *          U1  U2
     *          U3  U4
     *  L1  L2  F1  F2  R1  R2  B1  B2
     *  L3  L4  F3  F4  R3  R4  B3  B4
     *          D1  D2
     *          D3  D4
     *
 *  You can give directly the color of the cube.
     *
     * @param cube          : The cube string.
     * @return              : The string with the solving scramble.
     */
    std::string solve(const std::string& cube);
}

#endif //SOLVER2X2_CXX_SOLVER2X2_H
