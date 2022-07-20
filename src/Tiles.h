/**
 * This file contains all the necessary to convert
 * a string (the cube) into the coordinates.
 *
 * The cube must be given in this order:
 * U1-U4 R1-R4 F1-F4 D1-D4 L1-L4 B1-B4
 *
 *          U1  U2
 *          U3  U4
 *  L1  L2  F1  F2  R1  R2  B1  B2
 *  L3  L4  F3  F4  R3  R4  B3  B4
 *          D1  D2
 *          D3  D4
 *
 * For example, a solved cube is like this:
 * UUUURRRRFFFFDDDDLLLLBBBB.
 *
 * You can give also directly the colors, for example:
 * YYYYGGGGRRRRWWWWBBBBOOOO.
 */

#ifndef SOLVER2X2_CXX_TILES_H
#define SOLVER2X2_CXX_TILES_H

#include <string>
#include "Coords.h"

/**
 * The total number of tiles in the cube.
 */
#define N_TILES 24

/**
 * The number of tiles per face.
 */
#define N_TILES_FACE 4

/**
 * The number of cube faces.
 */
#define N_FACES 6

namespace Solver2x2{

    /**
     * The order of the tiles in the cube string.
     */
    typedef enum : int8_t{
        U_BL = 0, U_BR = 1, U_FL = 2, U_FR = 3,
        R_FU = 4, R_BU = 5, R_FD = 6, R_BD = 7,
        F_UL = 8, F_UR = 9, F_DL = 10, F_DR = 11,
        D_FL = 12, D_FR = 13, D_BL = 14, D_BR = 15,
        L_BU = 16, L_FU = 17, L_DB = 18, L_DF = 19,
        B_UR = 20, B_UL = 21, B_DR = 22, B_DL = 23
    }Facelets;

    ///The order of the faces.
    constexpr char FACES[] = "RLUDFB";

    ///The faces
    enum Faces: char{
        FRONT = 'f',
        BACK = 'b',
        UP = 'u',
        DOWN = 'd',
        LEFT = 'l',
        RIGHT = 'r'
    };

    /**
     * Types of errors.
     */
    enum Error: int8_t{
        NO_ERROR = 0,
        FEW_TILES = 1,
        ERR_COLOR = 2,
    };

    /**
     * Inverse color string.
     */
    constexpr char INV_COLOR[2][N_FACES+1] = {
            "ywbgro",
            "wygbor"
    };

    /**
     * These are the corners tiles in order.
     * It not follows the order of the tiles.
     */
    constexpr int8_t C_ORDER[N_TILES] = {
            U_FR, R_FU, F_UR,
            U_FL, F_UL, L_FU,
            U_BL, L_BU, B_UL,
            U_BR, B_UR, R_BU,

            D_FR, F_DR, R_FD,
            D_FL, L_DF, F_DL,
            D_BL, B_DL, L_DB,
            D_BR, R_BD, B_DR
    };

    /**
     * The tiles of the corners.
     */
    constexpr char CORNERS[N_CORNERS][4] = {
            "fru",
            "flu",
            "blu",
            "bru",
            "dfr",
            "dfl",
            "bdl",
            "bdr"
    };

    /**
     * Class Tiles
     * This class is used to convert the cube tiles
     * into orientation and permutation.
     */
    class Tiles{
    private:

        ///corner orient
        uint16_t ori;

        ///corner perm
        uint16_t perm;

        ///eventually error.
        Error error;

    public:

        /**
         * Constructor that also convert the tiles into coordinates.
         * The cube must be given in this order:
         * U1-U4 R1-R4 F1-F4 D1-D4 L1-L4 B1-B4
         *
         *          U1  U2
         *          U3  U4
         *  L1  L2  F1  F2  R1  R2  B1  B2
         *  L3  L4  F3  F4  R3  R4  B3  B4
         *          D1  D2
         *          D3  D4
         *
         * For example, a solved cube is like this:
         * UUUURRRRFFFFDDDDLLLLBBBB.
         *
         * You can give also directly the colors, for example:
         * YYYYGGGGRRRRWWWWBBBBOOOO.
         *
         * @param cube      : The cube string to convert.
         */
        explicit Tiles(const std::string& cube);

        /**
         * Get the eventual error.
         *
         * @return      : The error value.
         */
        Error getError() const;

        /**
         * Get corner permutation from the tiles.
         *
         * @return      : The permutation.
         */
        uint16_t getPerm() const;

        /**
         * Get corner orientation from the tiles.
         *
         * @return      : The orientation.
         */
        uint16_t getOri() const;

    private:

        /**
         * Convert the corners tiles into permutation coordinate.
         *
         * @param c     : The corners.
         * @return      : The permutation coordinate.
         */
        static uint16_t toPerm(std::string c[N_CORNERS]);

        /**
         * Convert the corners tiles into orientation coordinate.
         *
         * @param c     : The corners.
         * @return      : The orientation coordinate.
         */
        static uint16_t toOrient(std::string c[N_CORNERS]);

        /**
         * Convert the cube tiles into corners.
         *
         * @param corner    : The array of corner to store them.
         * @param cube      : The cube tiles string.
         */
        static void toCorner(std::string corner[N_CORNERS], const std::string& cube);

        /**
         * Convert color tiles into standard tiles.
         *
         * @param cube      : The cube tiles string.
         * @return          : The new cube with no colors.
         */
        std::string stdTiles(const std::string& cube);
    };
}

#endif //SOLVER2X2_CXX_TILES_H
