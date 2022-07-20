/**
 * This file contains the class Explore.
 * The purpose of this class is to create the
 * main tree of the 2x2 cube. It needs
 * around 150 MB and 3 second.
 */

#include <iostream>
#include <memory>
#include <cstring>
#include "Explore.h"

namespace Solver2x2{

    //the number of cubes you can generate with n moves
    const int32_t Explore::DEPTH_SIZE[MAX_DEPTH];

    //allocate tree and explored
    Explore::Tree::Tree(){
        uint16_t i;
        int32_t j;

        //allocate 1 array that will be split into a matrix
        cubeArray = new CubeNode[CUBE_CASES];
        exploredArray = new bool[CUBE_CASES];

        //split to matrix
        j = 0;
        for(i = 0; i < MAX_DEPTH; i++){
            t[i] = &cubeArray[j];
            j+=DEPTH_SIZE[i];
        }

        for(i = 0; i < ORI_CASES; i++)
            explored[i] = &exploredArray[i*PERM_CASES];

        //clean the memory

        memset(&cubeArray[0], 0, sizeof(CubeNode));
        memset(exploredArray, 0, CUBE_CASES);
    }

    //deallocate arrays
    Explore::Tree::~Tree(){
        delete[] cubeArray;
        delete[] exploredArray;
    }

    //allocate scramble
    Explore::Scramble::Scramble(){
        uint32_t i;

        scrambleArray = new uint64_t[CUBE_CASES];

        for(i = 0; i < ORI_CASES; i++)
            s[i] = &scrambleArray[i*PERM_CASES];

        scrambleArray[0] = 0;
    }

    //deallocate scramble
    Explore::Scramble::~Scramble(){
        delete[] scrambleArray;
    }

    //clone scramble
    Explore::Scramble* Explore::Scramble::clone() const{
        auto* newS = new Scramble();
        memcpy(newS->s[0], scrambleArray, sizeof(uint32_t) * CUBE_CASES);
        return newS;
    }

    //get the solve scramble
    uint64_t Explore::Scramble::solve(uint16_t ori, uint16_t perm){
        return s[ori][perm];
    }

    //set first cube already explored
    Explore::Explore(const Coords &coords) {
        this->coords = coords;
        isExplored(0, 0);
    }

    //set the coordinates
    void Explore::setCoords(const Coords& coords){
        this->coords = coords;
    }

    //generate the whole tree
    void Explore::generate(){
        for(int8_t i = 0; i < MAX_DEPTH; i++)
            expand(i);
    }

    //reallocate tree and explored
    void Explore::clean(){
        tree = Tree();
        scramble = Scramble();
    }

    //solve the cube
    uint64_t Explore::solve(uint16_t ori, uint16_t perm){
        return scramble.s[ori][perm];
    }

    //convert compressed scramble into a string
    std::string Explore::convert(uint64_t scramble){
        typedef union{
            uint8_t m : 4;
            uint64_t scramble;
        }SingleMove;

        const char* strMove;
        char* c_scramble;
        int8_t size;
        std::string res;
        SingleMove single;

        single.scramble = scramble;
        size = (int8_t)single.m;

        if(size == 0)
            return "";

        c_scramble = new char[size * 3];

        for(int8_t i = 0; i < size*3; i+=3){
            single.scramble >>= 4;

            strMove = moveToStr((int8_t)single.m);
            c_scramble[i] = strMove[0];
            c_scramble[i+1] = strMove[1];
            c_scramble[i+2] = ' ';
        }

        c_scramble[size*3-1] = '\0';
        res = c_scramble;
        delete[] c_scramble;

        return res;
    }

    Explore::Scramble* Explore::getScramble() const{
        return this->scramble.clone();
    }

    //compute sons of a particular depth
    int32_t Explore::expand(int8_t depth){
        auto newDepth = (int8_t)(1+depth);
        uint16_t o, p, o2, p2;
        int32_t idx;
        int8_t move;
        uint64_t moves;
        CubeNode* node;

        idx = 0;

        for(int32_t i = 0; i < DEPTH_SIZE[depth]; i++){
            node = &tree.t[depth][i];
            o = node->o;
            p = node->p;
            moves = scramble.s[o][p] >> 4;

            for(move = 0; move < N_MOVES; move++){
                p2 = coords.moveCPerm(p, move);
                o2 = coords.moveCOri(o, move);

                if(!isExplored(o2, p2)){
                    node->s[move] = idx;
                    tree.t[newDepth][idx].o = o2;
                    tree.t[newDepth][idx].p = p2;

                    scramble.s[o2][p2] = (((moves << 4) + invMove(move)) << 4) + depth+1;
                    idx++;
                }
            }
        }

        return idx;
    }

    //check if its already explored
    bool Explore::isExplored(uint16_t o, uint16_t p){
        return tree.explored[o][p] || !(tree.explored[o][p] = true);
    }
}