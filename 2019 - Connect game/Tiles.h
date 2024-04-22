#ifndef TILES_H
#define TILES_H

#include<ctime>
#include<cstdlib>
#include<iostream>
#include<vector>

const std::string chr=" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!&#$()?><[]{}\\/-=~";

class Tiles {
    public:
        Tiles(unsigned int width, unsigned int height, unsigned int chars, unsigned int alignm);
        void setSize(unsigned int width, unsigned int height, unsigned int cha, unsigned int alignm);
        void fillTiles();
        int getTile(unsigned int x, unsigned int y);
        bool connect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
        bool check();
        void shuffle();
        bool isEmpty();
        std::string getLastPath();
        std::string getHint();
        char getChar(unsigned int c);
        void rAlign();
        unsigned int sx, sy, ex, ey;

        static const int UP=0, RIGHT=1, DOWN=2, LEFT=3;
    private:
        unsigned int align;
        unsigned int chars;
        int* tile;
        unsigned int width;
        unsigned int height;
        void findPath(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,
                    int c, int d, std::string pt);
        void pah2(unsigned int x, unsigned int y, int c, int d, std::string pt, int n);
        std::string path;
        std::string hint;

        int* pairs;

};

#endif // TILES_H
