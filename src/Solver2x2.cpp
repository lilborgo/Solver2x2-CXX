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

#include "Solver2x2.h"
#include "Explore.h"
#include "Coords.h"
#include "Tiles.h"

namespace Solver2x2{
    //explore pointer
    static Explore::Scramble* scramble = nullptr;

    //init the solver
    void init(){
        Coords coords;
        Explore explore(coords);

        deinit();
        explore.generate();
        scramble = explore.getScramble();
    }

    //deallocate the scramble solver
    void deinit(){
        if(scramble == nullptr)
            return;

        delete scramble;
        scramble = nullptr;
    }

    //solve the cube
    std::string solve(const std::string& cube){
        Tiles tiles(cube);

        return Solver2x2::Explore::convert(scramble->solve(tiles.getOri(), tiles.getPerm()));
    }
}
