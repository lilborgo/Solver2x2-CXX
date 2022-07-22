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
#include <iostream>
#include <cstring>
#include <cassert>
#include "Tiles.h"

namespace Solver2x2 {

    typedef void (*move_tile_f)(char tiles[]);

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

    //rotate 4 tiles
    static void rotate4(char tiles[], const int8_t idx[]){
        char tmp;

        for(int8_t j = 0; j < 3; j++){

            tmp = tiles[idx[j*4]];

            for(int8_t i = j*4; i < j*4+3; i++)
                tiles[idx[i]] = tiles[idx[i+1]];

            tiles[idx[j*4+3]] = tmp;
        }
    }

    //rotate 2 tiles
    static void rotate2(char tiles[], const int8_t idx[]){
        char tmp;

        for(int8_t i = 0; i < 12; i+=2){
            tmp = tiles[idx[i]];
            tiles[idx[i]] = tiles[idx[i+1]];
            tiles[idx[i+1]] = tmp;
        }
    }

    //tiles F

    static void tilesF1(char tiles[]){
        const int8_t moves[] = {U_FL, L_DF, D_FR, R_FU,
                                U_FR, L_FU, D_FL, R_FD,
                                F_UL, F_DL, F_DR, F_UR};

        rotate4(tiles, moves);
    }

    static void tilesF2(char tiles[]){
        const int8_t moves[] = {U_FR, D_FL, U_FL, D_FR,
                                R_FU, L_DF, L_FU, R_FD,
                                F_UR, F_DL, F_UL, F_DR};

        rotate2(tiles, moves);
    }

    static void tilesF3(char tiles[]){
        const int8_t moves[] = {R_FU, D_FR, L_DF, U_FL,
                                R_FD, D_FL, L_FU, U_FR,
                                F_UR, F_DR, F_DL, F_UL};

        rotate4(tiles, moves);
    }

    //tiles R

    static void tilesR1(char tiles[]){
        const int8_t moves[] = {U_FR, F_DR, D_BR, B_UR,
                                U_BR, F_UR, D_FR, B_DR,
                                R_FU, R_FD, R_BD, R_BU};

        rotate4(tiles, moves);
    }

    static void tilesR2(char tiles[]){
        const int8_t moves[] = {U_FR, D_BR, U_BR, D_FR,
                                F_UR, B_DR, F_DR, B_UR,
                                R_FU, R_BD, R_BU, R_FD};

        rotate2(tiles, moves);
    }

    static void tilesR3(char tiles[]){
        const int8_t moves[] = {B_UR, D_BR, F_DR, U_FR,
                                B_DR, D_FR, F_UR, U_BR,
                                R_BU, R_BD, R_FD, R_FU};

        rotate4(tiles, moves);
    }

    //tiles U

    static void tilesU1(char tiles[]){
        const int8_t moves[] = {F_UR, R_BU, B_UL, L_FU,
                                F_UL, R_FU, B_UR, L_BU,
                                U_FR, U_BR, U_BL, U_FL};

        rotate4(tiles, moves);
    }

    static void tilesU2(char tiles[]){
        const int8_t moves[] = {F_UR, B_UL, F_UL, B_UR,
                                R_FU, L_BU, R_BU, L_FU,
                                U_FL, U_BR, U_FR, U_BL};

        rotate2(tiles, moves);
    }

    static void tilesU3(char tiles[]) {
        const int8_t moves[] = {L_FU, B_UL, R_BU, F_UR,
                                L_BU, B_UR, R_FU, F_UL,
                                U_FL, U_BL, U_BR, U_FR};

        rotate4(tiles, moves);
    }

    const move_tile_f moveTileF[]{
        tilesF1,
        tilesF2,
        tilesF3,
        tilesR1,
        tilesR2,
        tilesR3,
        tilesU1,
        tilesU2,
        tilesU3
    };

    //move tiles char
    void Tiles::moveTiles(char tiles[], int8_t move){
        moveTileF[move](tiles);
    }

    //tests the tiles
    void Tiles::test(){
        const char SOL_CUBE[N_TILES+1] = "YYYYOOOOGGGGWWWWRRRRBBBB";
        char cube[N_TILES+1];

        for(int8_t i = 0; i < N_MOVES; i+=3){
            memcpy(cube, SOL_CUBE, N_TILES);

            moveTiles(cube, i);
            moveTiles(cube, i);
            moveTiles(cube, i+1);
            moveTiles(cube, i+2);
            moveTiles(cube, i+2);
            moveTiles(cube, i+1);

            assert(memcmp(cube, SOL_CUBE, N_TILES) == 0);
        }
    }

}