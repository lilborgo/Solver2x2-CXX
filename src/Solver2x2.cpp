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

#include <fstream>
#include <cassert>
#include "Solver2x2.h"
#include "Explore.h"
#include "Coords.h"
#include "Tiles.h"

namespace Solver2x2{
    //explore pointer
    static Explore::Scramble* scramble = nullptr;

    //init the solver
    void init(){
        deinit();
        scramble = new Explore::Scramble();

        {
            Coords coords;
            Explore explore(coords, scramble);
            explore.generate();
        }
    }

    //deallocate the scramble solver
    void deinit(){
        if(scramble == nullptr)
            return;

        delete scramble;
        scramble = nullptr;
    }

    //write to file
    bool writeFile(const std::string& name){
        std::ofstream file(name);

        if(!file)
            return false;

        if(scramble == nullptr)
            init();

        file.write(reinterpret_cast<char *>(scramble->scrambleArray), sizeof(uint64_t) * CUBE_CASES);
        file.close();

        return true;
    }

    //read the solver from a file
    bool loadFile(const std::string& name){
        std::ifstream file(name);

        if(!file)
            return writeFile(name);

        if(scramble != nullptr)
            deinit();

        scramble = new Explore::Scramble();

        file.read(reinterpret_cast<char *>(scramble->scrambleArray), sizeof(uint64_t) * CUBE_CASES);
        file.close();

        return true;
    }

    //solve the cube
    std::string solve(const std::string& cube){
        Tiles tiles(cube);

        if(tiles.getError() != NO_ERROR)
            return "Error";

        return Solver2x2::Explore::convert(scramble->solve(tiles.getOri(), tiles.getPerm()));
    }

    //random cube
    std::string random(){
        static bool firstTime = true;

        char cube[N_TILES+1] = "YYYYOOOOGGGGWWWWRRRRBBBB";
        std::string cubeStr;

        if(firstTime){
            srand((unsigned)time(nullptr));
            firstTime = false;
        }

        for(int8_t i = 0; i < 20; i++)
            Tiles::moveTiles(cube, rand()%N_MOVES);

        cubeStr = "";
        cubeStr.append(cube);

        return cubeStr;
    }

    //tests all
    void tests(){
        Coords coords;
        std::string cube;

        init();

        Tiles::test();
        testMoves();
        coords.test();

        for(uint16_t i = 0; i < 1000; i++){
            cube = random();
            assert(Solver2x2::fromScramble(Solver2x2::invScramble(Solver2x2::solve(cube))) == cube);
        }

        deinit();
    }

    //inverse scramble
    std::string invScramble(const std::string& s){
        std::string inv;

        inv = "";

        for(int8_t i = s.size()-1; i > 0; i-=3){
            inv += s.at(i-1);

            switch(s.at(i)-'0'){
                case 1:
                    inv += "3 ";
                    break;
                case 2:
                    inv += "2 ";
                    break;
                case 3:
                    inv += "1 ";
                    break;
                default:
                    break;
            }
        }

        inv.erase(inv.length()-1);

        return inv;
    }

    //convert scramble to a cube
    std::string fromScramble(const std::string& s){
        char cube[N_TILES+1] = "YYYYOOOOGGGGWWWWRRRRBBBB";
        std::string cubeStr;
        int8_t move;

        for(int8_t i = 0, size = s.length(); i < size; i+=3){
            switch(s.at(i)){
                case 'F':
                    move = 0;
                    break;
                case 'R':
                    move = 3;
                    break;
                case 'U':
                    move = 6;
                    break;
                default:
                    move = 0;
                    break;
            }

            move += s.at(i+1)-'0'-1;

            Tiles::moveTiles(cube, move);
        }

        cubeStr = "";
        cubeStr.append(cube);

        return cubeStr;
    }
}
