/**
 * VECTOR CUBE MOVER
 * Here there are all the functions able to move the cube represented
 * in the vector form, represented by two arrays:
 * - permutation: representing the corners positions;
 * - orientation: representing the corners directions.
 */

#include <cstring>
#include <cassert>
#include "move.h"

namespace Solver2x2 {

    //function callable for vector moving
    typedef void (*move_func)(int8_t c[]);

    //inverse move
    static const int8_t invMoveArr[N_MOVES] = {
        F3_MOVE,
        F2_MOVE,
        F1_MOVE,
        R3_MOVE,
        R2_MOVE,
        R1_MOVE,
        U3_MOVE,
        U2_MOVE,
        U1_MOVE
    };

    //move to a string
    static const char moveToStrArr[N_MOVES][3]{
            "F1",
            "F2",
            "F3",
            "R1",
            "R2",
            "R3",
            "U1",
            "U2",
            "U3"
    };

    //cube mover functions corner perm

    static void moveF1Perm(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[UFL];
        c[UFL] = c[DFL];
        c[DFL] = c[DFR];
        c[DFR] = tmp;
    }

    static void moveF2Perm(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[DFL];
        c[DFL] = tmp;
        tmp = c[UFL];
        c[UFL] = c[DFR];
        c[DFR] = tmp;
    }

    static void moveF3Perm(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[DFR];
        c[DFR] = c[DFL];
        c[DFL] = c[UFL];
        c[UFL] = tmp;
    }

    static void moveU1Perm(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[UBR];
        c[UBR] = c[UBL];
        c[UBL] = c[UFL];
        c[UFL] = tmp;
    }

    static void moveU2Perm(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[UBL];
        c[UBL] = tmp;
        tmp = c[UFL];
        c[UFL] = c[UBR];
        c[UBR] = tmp;
    }

    static void moveU3Perm(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[UFL];
        c[UFL] = c[UBL];
        c[UBL] = c[UBR];
        c[UBR] = tmp;
    }

    static void moveR1Perm(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[DFR];
        c[DFR] = c[DBR];
        c[DBR] = c[UBR];
        c[UBR] = tmp;
    }

    static void moveR2Perm(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[DBR];
        c[DBR] = tmp;
        tmp = c[UBR];
        c[UBR] = c[DFR];
        c[DFR] = tmp;
    }

    static void moveR3Perm(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[UBR];
        c[UBR] = c[DBR];
        c[DBR] = c[DFR];
        c[DFR] = tmp;
    }

    //cube mover functions Ori

    static void moveF1Ori(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = (int8_t)((c[UFL] + C_CLOCKWISE)%C_STATES);
        c[UFL] = (int8_t)((c[DFL] + C_ANTICLOCKWISE)%C_STATES);
        c[DFL] = (int8_t)((c[DFR] + C_CLOCKWISE)%C_STATES);
        c[DFR] = (int8_t)((tmp + C_ANTICLOCKWISE)%C_STATES);
    }

    static void moveF2Ori(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[DFL];
        c[DFL] = tmp;
        tmp = c[UFL];
        c[UFL] = c[DFR];
        c[DFR] = tmp;
    }

    static void moveF3Ori(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = (int8_t)((c[DFR] + C_CLOCKWISE)%C_STATES);
        c[DFR] = (int8_t)((c[DFL] + C_ANTICLOCKWISE)%C_STATES);
        c[DFL] = (int8_t)((c[UFL] + C_CLOCKWISE)%C_STATES);
        c[UFL] = (int8_t)((tmp + C_ANTICLOCKWISE)%C_STATES);
    }

    static void moveU1Ori(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[UBR];
        c[UBR] = c[UBL];
        c[UBL] = c[UFL];
        c[UFL] = tmp;
    }

    static void moveU2Ori(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[UBL];
        c[UBL] = tmp;
        tmp = c[UFL];
        c[UFL] = c[UBR];
        c[UBR] = tmp;
    }

    static void moveU3Ori(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[UFL];
        c[UFL] = c[UBL];
        c[UBL] = c[UBR];
        c[UBR] = tmp;
    }

    static void moveR1Ori(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = (int8_t)((c[DFR] + C_ANTICLOCKWISE)%C_STATES);
        c[DFR] = (int8_t)((c[DBR] + C_CLOCKWISE)%C_STATES);
        c[DBR] = (int8_t)((c[UBR] + C_ANTICLOCKWISE)%C_STATES);
        c[UBR] = (int8_t)((tmp + C_CLOCKWISE)%C_STATES);
    }

    static void moveR2Ori(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = c[DBR];
        c[DBR] = tmp;
        tmp = c[UBR];
        c[UBR] = c[DFR];
        c[DFR] = tmp;
    }

    static void moveR3Ori(int8_t c[]){
        int8_t tmp;

        tmp = c[UFR];
        c[UFR] = (int8_t)((c[UBR] + C_ANTICLOCKWISE)%C_STATES);
        c[UBR] = (int8_t)((c[DBR] + C_CLOCKWISE)%C_STATES);
        c[DBR] = (int8_t)((c[DFR] + C_ANTICLOCKWISE)%C_STATES);
        c[DFR] = (int8_t)((tmp + C_CLOCKWISE)%C_STATES);
    }

    //useful for not using switch case
    const move_func oriFunc[N_MOVES] = {
            moveF1Ori,
            moveF2Ori,
            moveF3Ori,
            moveR1Ori,
            moveR2Ori,
            moveR3Ori,
            moveU1Ori,
            moveU2Ori,
            moveU3Ori

    };

    //move corner orientation
    void moveOri(int8_t c[], int8_t move){
        oriFunc[move](c);
    }

    //useful for not using switch case
    const move_func permFunc[N_MOVES] = {
            moveF1Perm,
            moveF2Perm,
            moveF3Perm,
            moveR1Perm,
            moveR2Perm,
            moveR3Perm,
            moveU1Perm,
            moveU2Perm,
            moveU3Perm
    };

    //move corner perm;
    void movePerm(int8_t c[], int8_t move){
        permFunc[move](c);
    }

    //move to string
    const char* moveToStr(int8_t move){
        return moveToStrArr[move];
    }

    //inverse move
    int8_t invMove(int8_t move){
        return invMoveArr[move];
    }

    //tests this file
    void testMoves(){
        const int8_t SOLVED_ORI[N_CORNERS] = {0, 0, 0, 0, 0, 0, 0, 0};
        const int8_t SOLVED_PERM[N_CORNERS] = {0, 1, 2, 3, 4, 5, 6, 7};
        int8_t ori[N_CORNERS], perm[N_CORNERS];
        int8_t i, j;

        for(i = 0; i < N_MOVES; i++){
            memcpy(ori, SOLVED_ORI, N_CORNERS);
            memcpy(perm, SOLVED_PERM, N_CORNERS);

            for(j = 0; j < N_MOVES; j++){
                moveOri(ori, j);
                moveOri(ori, invMove(j));

                movePerm(perm, j);
                movePerm(perm, invMove(j));

                assert(memcmp(ori, SOLVED_ORI, N_CORNERS) == 0);
                assert(memcmp(perm, SOLVED_PERM, N_CORNERS) == 0);
            }
        }
     }
}