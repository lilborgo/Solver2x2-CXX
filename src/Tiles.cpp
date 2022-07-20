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

#include <algorithm>
#include "Tiles.h"

namespace Solver2x2 {

    //convert tiles into coordinates
    Tiles::Tiles(const std::string &cube) {
        std::string newCube;
        std::string corners[N_CORNERS];

        error = NO_ERROR;

        //check if the number of tiles is correct
        if (cube.length() != N_TILES) {
            error = FEW_TILES;
            return;
        }

        //convert to standard tiles
        newCube = stdTiles(cube);

        if (error != NO_ERROR)
            return;

        //convert to corners
        toCorner(corners, newCube);

        //get coordinates
        perm = toPerm(corners);
        ori = toOrient(corners);
    }

    //eventually error
    Error Tiles::getError() const {
        return error;
    }

    //get permutation
    uint16_t Tiles::getPerm() const {
        return perm;
    }

    //get orientation
    uint16_t Tiles::getOri() const {
        return ori;
    }

    //convert corners into permutation
    uint16_t Tiles::toPerm(std::string *c) {
        std::string cStr[N_CORNERS];
        int8_t corners[N_CORNERS];
        int8_t i, j;

        for (i = 0; i < N_CORNERS; i++) {
            cStr[i] = c[i];
            std::sort(cStr[i].begin(), cStr[i].end());
        }

        for (i = 0; i < N_CORNERS; i++) {
            for (j = 0; j < N_CORNERS; j++) {
                if (cStr[i] == CORNERS[j]) {
                    corners[i] = j;
                    break;
                }
            }
        }

        return Coords::compCPerm(corners);
    }

    //convert corners into orientation
    uint16_t Tiles::toOrient(std::string *c) {
        int8_t corners[N_CORNERS];
        int8_t i, j;

        for (i = 0; i < N_CORNERS; i++) {
            corners[i] = 0;

            for (j = 0; j < C_STATES; j++) {
                if (c[i].at(j) == UP || c[i].at(j) == DOWN) {
                    corners[i] = j;
                    break;
                }
            }
        }

        return Coords::comCOri(corners);
    }

    //convert tiles into corners
    void Tiles::toCorner(std::string *corner, const std::string &cube) {
        int8_t i;

        for (i = 0; i < N_CORNERS; i++)
            corner[i] = "";

        for (i = 0; i < N_TILES; i++)
            corner[i / 3].append(1, (char) std::tolower(cube.at(C_ORDER[i])));
    }

    //convert to standard tiles
    std::string Tiles::stdTiles(const std::string &cube) {
        char faces[N_FACES];
        std::string newCube(cube);
        uint8_t i;

        std::for_each(newCube.begin(), newCube.end(), [](char &c) {
            c = (char) std::tolower(c);
        });

        faces[1] = newCube.at(L_DB);
        faces[3] = newCube.at(D_BL);
        faces[5] = newCube.at(B_DL);

        for (i = 0; i < N_FACES; i++) {
            if (i % 2 == 0)
                faces[i] = INV_COLOR[1][std::string(INV_COLOR[0]).find(faces[i + 1])];

            std::replace(newCube.begin(), newCube.end(), faces[i], FACES[i]);
        }

        for (i = 0; i < N_FACES; i++) {
            if (std::count(newCube.begin(), newCube.end(), FACES[i]) != N_TILES_FACE) {
                error = ERR_COLOR;
                return "";
            }
        }

        return newCube;
    }

}