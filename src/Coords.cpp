/**
 * This file precompute the cube coordination.
 */

#include <cstring>
#include <cassert>
#include "Coords.h"

namespace Solver2x2 {

    Coords::Coords() {
        initCOri();
        initCPerm();
    }

    //corner orient

    void Coords::initCOri() {
        uint16_t i;
        int8_t j;
        int8_t cube[N_CORNERS], cube2[N_CORNERS];

        for (i = 0; i < ORI_CASES; i++) {
            invCOri(cube, i);

            for (j = 0; j < N_MOVES; j++) {
                memcpy(cube2, cube, N_CORNERS);
                moveOri(cube2, j);
                cOri[i][j] = comCOri(cube2);
            }
        }
    }

    uint16_t Coords::moveCOri(uint16_t coord, int8_t move) {
        return cOri[coord][move];
    }

    uint16_t Coords::comCOri(const int8_t c[]) {
        int8_t i;
        uint16_t ori = 0;

        for (i = UFR; i < DBL; i++)
            ori = ori*C_STATES+c[i];

        return ori;
    }

    void Coords::invCOri(int8_t c[], uint16_t coord) {
        int8_t i, parity;

        parity = 0;

        for (i = DBL - 1; i >= UFR; i--) {
            parity += coord%C_STATES;
            c[i] = (int8_t)(coord % C_STATES);
            coord /= C_STATES;
        }

        parity %= C_STATES;

        switch (parity) {
            case DEFAULT_C:
                c[DBR] = DEFAULT_C;
                break;
            case C_CLOCKWISE:
                c[DBR] = C_ANTICLOCKWISE;
                break;
            case C_ANTICLOCKWISE:
                c[DBR] = C_CLOCKWISE;
                break;
            default:
                break;
        }

        c[DBL] = 0;
    }

    //corner perm

    void Coords::initCPerm() {
        uint16_t i;
        int8_t j;
        int8_t cube[N_CORNERS], cube2[N_CORNERS];

        for (i = 0; i < PERM_CASES; i++) {
            invCPerm(cube, i);

            for (j = 0; j < N_MOVES; j++) {
                memcpy(cube2, cube, N_CORNERS);
                movePerm(cube2, j);
                cPerm[i][j] = compCPerm(cube2);
            }
        }
    }

    uint16_t Coords::moveCPerm(uint16_t coord, int8_t move){
        return cPerm[coord][move];
    }

    uint16_t Coords::compCPerm(int8_t c[]) {
        int8_t i, j, count;
        uint16_t perm = 0;
        int8_t tmp;

        tmp = c[DBL];
        c[DBL] = c[DBR];

        for (i = DBL; i > UFR; i--) {
            count = 0;

            for (j = (int8_t)(i-1); j >= 0; j--)
                if (c[j] > c[i])
                    count++;

            perm = (perm+count)*i;
        }

        c[DBL] = tmp;

        return perm;
    }

    void Coords::invCPerm(int8_t c[], uint16_t coord) {
        bool explored[N_CORNERS];
        int8_t order[N_CORNERS];
        int8_t i, count;

        for (i = UFR; i <= DBL; i++) {
            explored[i] = false;
            order[i] = (int8_t)(coord%(i+1));
            coord /= (i+1);
        }

        for (i = DBL; i >= UFR; i--) {
            count = DBL;

            while (explored[count])
                count--;

            while (order[i] > 0) {
                order[i]--;

                do{
                    count--;
                }while (explored[count]);
            }

            c[i] = (int8_t)count;
            explored[count] = true;
        }

        c[DBR] = c[DBL];
        c[DBL] = DBL;
    }

    void Coords::test() {
        uint16_t i;
        int8_t j;
        int8_t cube[N_CORNERS];

        for(i = 0; i < ORI_CASES; i++){
            invCOri(cube, i);
            assert(comCOri(cube) == i);
        }

        for(i = 0; i < PERM_CASES; i++){
            invCPerm(cube, i);
            assert(compCPerm(cube) == i);
        }

        for(i = 0; i < ORI_CASES; i++){
            for(j = 0; j < N_MOVES; j++) {
                assert(moveCOri(moveCOri(i, j), invMove(j)) == i);
            }
        }

        for(i = 0; i < PERM_CASES; i++){
            for(j = 0; j < N_MOVES; j++) {
                assert(moveCPerm(moveCPerm(i, j), invMove(j)) == i);
            }
        }
    }
}