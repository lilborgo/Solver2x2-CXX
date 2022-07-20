/**
 * This file precompute the cube coordination.
 */

#ifndef CUBESOLVER3X3_CUBECOORD_HPP
#define CUBESOLVER3X3_CUBECOORD_HPP

#include "move.h"

/**
 * This is the cases of the corner orient.
 * In the 3x3 Rubik's cube, the corner orientation can have 3 states:
 * normal state, clockwise, anticlockwise.
 * The corner are 8 but 2 are the result of the other 6.
 * So the number of cases is the result of 3^6 = 2187.
 */
#define ORI_CASES 729

/**
 * This is the cases of the corner perm.
 * In the 3x3 Rubik's cube, the corner permutation is computed by
 * 8! = 40320
 */
#define PERM_CASES 5040

namespace Solver2x2 {

    /**
     * This class is used to handle the coords precomputing.
     * It precompute the orientation and permutation of the
     * 2x2 cube.
     */
    class Coords {

    private:

        /**
         * This is a matrix and is stored all the coordinate cases and coordinates
         * generated moving the cube from them.
         */
        uint16_t cOri[ORI_CASES][N_MOVES]{};

        /**
         * This is a matrix and is stored all the coordinate cases and coordinates
         * generated moving the cube from them.
         */
        uint16_t cPerm[PERM_CASES][N_MOVES]{};

    public:

        /**
         * The constructor generate all the coordinates and
         * store them in the matrix.
         */
        Coords();

        //corner orient

    private:

        /**
         * This function initialize the corner orientation.
         */
        void initCOri();

    public:
        /**
         * This function gets the new corner orient coordinate from an old
         * coordinate and a move.
         * If you apply a move to the cube the orientation of corners change.
         *
         * @param coord             : The old coordinate to move.
         * @param m                 : The move to apply.
         * @return                  : The new coordinate.
         */
        uint16_t moveCOri(uint16_t coord, int8_t move);

        /**
         * This function is used to compute the corner orient coordinate.
         * It converts a number from base 3 to base 10.
         * If converts from base 3 because the states of a corner in the Cube
         * are 3: default cornerOrient, clockwise and anticlockwise,
         *
         * @param cornerOrient      : The array that contains the cornerOrient of corners.
         * @return                  : The coordinate that compute.
         */
        static uint16_t comCOri(const int8_t c[]);

    private:
        /**
         * This function is the opposite of the precedent. It converts a coordinate
         * into the cube.
         *
         * @param c         : The array to store the cube.
         * @param coord     : The coordinate to convert.
         */
        static void invCOri(int8_t c[], uint16_t coord);

        //corner perm

        /**
         * This function initialize the corner permutation.
         */
        void initCPerm();

    public:
        /**
         * This function gets the new corner perm coordinate from an old
         * coordinate and a move.
         * If you apply a move to the cube the permutation of corners change.
         *
         * @param coord     : The old coordinate to move.
         * @param move      : The move to apply.
         * @return          : The new coordinate.
         */
        uint16_t moveCPerm(uint16_t coord, int8_t move);

        /**
         * This function is used to compute the corner perm coordinate.
         *
         * @param c         : The array that contains the order of corners.
         * @return          : The coordinate that compute.
         */
        static uint16_t compCPerm(int8_t c[]);

    private:
        /**
         * This function is the opposite of the precedent. It converts a coordinate
         * into the cube.
         *
         * @param c         : The array to store the cube.
         * @param coord     : The coordinate to convert.
         */
        static void invCPerm(int8_t c[], uint16_t coord);

    public:

        /**
         * Test if the coords generator works correctly.
         */
        void test();
    };
}

#endif //CUBESOLVER3X3_CUBECOORD_HPP
