/**
 * VECTOR CUBE MOVER
 * Here there are all the functions able to move the cube represented
 * in the vector form, represented by two arrays:
 * - permutation: representing the corners positions;
 * - orientation: representing the corners directions.
 */

#ifndef SOLVER2X2_CXX_MOVE_H
#define SOLVER2X2_CXX_MOVE_H

#include <cstdint>

namespace Solver2x2 {
    /**
     * Number of corners.
     */
    #define N_CORNERS 8

    /**
     * Number of moves
     */
    #define N_MOVES 9

    /**
     * This is the number assigned to a corner in the correct orientation.
     */
    #define DEFAULT_C 0

    /**
     * This is the value that a 0 orientation would acquire after a clockwise
     * rotation.
     */
    #define C_CLOCKWISE 1

    /**
     * This is the value that a 0 orientation would acquire after a anticlockwise
     * rotation.
     */
    #define C_ANTICLOCKWISE 2

    /**
     * This is the number of states that a corner can have:
     * default orientation, clockwise and anticlockwise.
     */
    #define C_STATES 3

    /**
     * This enum contains all the available moves performable on a 2x2 cube.
     */
    enum Move : int8_t {
        F1_MOVE = 0,
        F2_MOVE = 1,
        F3_MOVE = 2,
        R1_MOVE = 3,
        R2_MOVE = 4,
        R3_MOVE = 5,
        U1_MOVE = 6,
        U2_MOVE = 7,
        U3_MOVE = 8,
        NO_MOVE = 9,
    };

    /**
     * These are the names of the cube corners.
     */
    enum Corner : int8_t {
        UFR = 0,
        UFL = 1,
        UBL = 2,
        UBR = 3,
        DFR = 4,
        DFL = 5,
        DBL = 6,
        DBR = 7
    };

    /**
     * This function is used to move the corner orientation.
     * If I apply a move in the cube, the corner orient changes.
     * So this function change the corner orientation from an old orientation
     * and a move to apply.
     *
     * @param c     : The array that contains the orientation of corners.
     * @param m     : The move to apply.
     */
    void moveOri(int8_t c[], int8_t m);

    /**
     * This is used to move the corner permutation.
     * If I apply a move in the cube, the corner permutation changes.
     * So this function change the corner permutation from an old permutation
     * and a move to apply.
     *
     * @param c     : The array that contains the permutation of corners.
     * @param m     : The move to apply.
     */
    void movePerm(int8_t c[], int8_t m);


    /**
     * Convert a move to a string.
     *
     * @param move  : The move to convert.
     * @return      : The move in string.
     */
    const char* moveToStr(int8_t move);

    /**
     * Return the inverse move.
     *
     * @param move  : The move to convert.
     * @return      : The inverse move.
     */
    int8_t invMove(int8_t move);

    /**
     * Test the move functions.
     */
    void testMoves();
}

#endif //SOLVER2X2_CXX_MOVE_H
