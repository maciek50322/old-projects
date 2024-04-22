#include "Tiles.h"

Tiles::Tiles(unsigned int wid, unsigned int hei, unsigned int cha, unsigned int ali) {
    srand(time(NULL));
    tile=NULL;
    pairs=NULL;
    setSize(wid, hei, cha, ali);
}

void Tiles::setSize(unsigned int wid, unsigned int hei, unsigned int cha, unsigned int ali) {
  //  if (wid%2!=0) wid++;
 //   if (hei%2!=0) hei++;
    width=wid+2;
    height=hei+2;
    if (cha>=chr.length()) cha=chr.length()-1;
    chars=cha;
    align=ali;
    if (tile!=NULL)
        delete[] tile;
    if (pairs!=NULL);
        delete[] pairs;
    tile = new int[width*height]();
    pairs= new int[chars+1]();
    fillTiles();
}

void Tiles::fillTiles() {
    for (unsigned int i=0;i<chars+1;i++) {
        pairs[i]=0;
    }
    for (unsigned int i=1;i<(width-2)*(height-2)/2+1;i++) {
        unsigned int n=rand()%(chars)+1;
        pairs[n]+=2;
        unsigned int w, h;
        for (int j=0;j<2;j++) {
            do {
                w=rand()%(width-2)+1;
                h=rand()%(height-2)+1;
            } while ( getTile(w, h)>0 );
            tile[h*width+w]=n;
        }
    }
    check();
}


void Tiles::shuffle() {
    for (unsigned int i=0;i<height*width;i++) {
        if (tile[i]>0) tile[i]=-1;
    }
    std::vector<int> pr;
    for (unsigned int i=1;i<chars+1;i++) {
        for (int j=0;j<pairs[i];j++)
            pr.push_back(i);
    }
    unsigned int n;
    for (unsigned int i=0;i<height*width;i++) {
        if (tile[i]==-1){
            n=rand()%(pr.size());
            tile[i]=pr[ n ];
            pr.erase( pr.begin()+n );
        }
    }

    check();
}

int Tiles::getTile(unsigned int x, unsigned int y) {
    return tile[ y*width + x ];
}

bool Tiles::connect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
    if ( (x1==x2 && y1==y2 ) || x1*x2*y1*y2==0 || x1>=width-1 || x2>=width-1 || y1>=height-1 || y2>=height-1 ||
        getTile(x1, y1)*getTile(x2, y2)==0 || getTile(x1, y1)!=getTile(x2, y2))
            return false;
    path="";
    findPath(x1, y1, x2, y2, 1, UP, "");
    if (path!="") {
        sx=x1; sy=y2; ex=x2; ey=y2;
        pairs[ tile[ y1*width + x1 ] ]-=2;
        tile[ y1*width + x1 ]=0;
        tile[ y2*width + x2 ]=0;
        return true;
    }
    return false;

}

void Tiles::findPath(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,
                     int c, int d, std::string pt) {

    if (x1==x2 && y1==y2) {
        if (path=="" || path.length()>pt.length()) {
            path=pt;
        }
    } else if (getTile(x1, y1)==0 || pt=="") {

        for (int i=0;i<4;i++) {
            if ( (i==(d+2)%4 && pt!="") || (i==UP && y1<=0) || (i==RIGHT && x1>=width-1) || (i==DOWN && y1>=height-1) || (i==LEFT && x1<=0) ) {
                    //dont go back
            } else  if (c + ( (d==i) ? 0 : 1 ) <= 3) {
                findPath(x1 + ( i==RIGHT ? 1 : (i==LEFT ? -1 : 0) ), y1 + (i==UP ? -1 : (i==DOWN ? 1 : 0) ), x2, y2,
                            c + ( (d==i) ? 0 : 1 )*(pt=="" ? 0 : 1), i, pt+(char)(i+'0'));
            }
        }
    }
}

bool Tiles::check() {
    bool av=false;
    if (!isEmpty()) {
        for (unsigned int i=1;i<height-1;i++) {
            for (unsigned int j=1;j<width-1;j++) {
                if (getTile(j, i)>0) {
                    hint="";
                    pah2(j, i, 1, UP, "", getTile(j, i));
                    if (hint!="") {
                        sx=j; sy=i;
                        av=true;
                        break;
                    }
                }
            }
            if (av) break;
        }
        if (!av) shuffle();
    }


    return av;
}

void Tiles::pah2(unsigned int x, unsigned int y, int c, int d, std::string pt, int n) {

    if (pt!="" && getTile(x, y)==n) {
        if (hint=="" || hint.length()>pt.length()) {
            hint=pt;
            ex=x; ey=y;
        }
    } else if (getTile(x, y)==0 || pt=="") {

        for (int i=0;i<4;i++) {
            if ( (i==(d+2)%4 && pt!="") || (i==UP && y<=0) || (i==RIGHT && x>=width-1) || (i==DOWN && y>=height-1) || (i==LEFT && x<=0) ) {
                    //dont go back
            } else  if (c + ( (d==i) ? 0 : 1 ) <= 3) {
                pah2(x + ( i==RIGHT ? 1 : (i==LEFT ? -1 : 0) ), y + (i==UP ? -1 : (i==DOWN ? 1 : 0) ),
                            c + ( (d==i) ? 0 : 1 )*(pt=="" ? 0 : 1), i, pt+(char)(i+'0'), n);
            }
        }
    }
}

bool Tiles::isEmpty(){
    for (unsigned int i=1;i<height-1;i++) {
        for (unsigned int j=1;j<width-1;j++) {
            if (getTile(j, i)>0) return false;
        }
    }
    return true;
}

std::string Tiles::getLastPath() {
    return path;
}
std::string Tiles::getHint() {
    return hint;
}
char Tiles::getChar(unsigned int c) {
    return chr[c];
}

void Tiles::rAlign() {
    if (align>0) {
        if (align==1) {
            for (unsigned int j=1; j<=width-2 ;j++) {
                int w=0;
                for (unsigned int i=1; i<=height-2; i++) {
                    if (tile[ i*width+j ]==0) {
                        w++;
                    } else if (w>0) {
                        tile[ (i-w)*width+j ]=tile[ i*width+j ];
                        tile[ i*width+j ]=0;
                    }
                }
            }
        } else if (align==3) {
            for (unsigned int j=1; j<=width-2 ;j++) {
                int w=0;
                for (unsigned int i=height-2; i>=1; i--) {
                    if (tile[ i*width+j ]==0) {
                        w++;
                    } else if (w>0) {
                        tile[ (i+w)*width+j ]=tile[ i*width+j ];
                        tile[ i*width+j ]=0;
                    }
                }
            }
        } else if (align==2) {
            for (unsigned int i=1; i<=height-2 ;i++) {
                int w=0;
                for (unsigned int j=width-2; j>=1; j--) {
                    if (tile[ i*width+j ]==0) {
                        w++;
                    } else if (w>0) {
                        tile[ i*width+j+w ]=tile[ i*width+j ];
                        tile[ i*width+j ]=0;
                    }
                }
            }
        } else if (align==4) {
            for (unsigned int i=1; i<=height-2 ;i++) {
                int w=0;
                for (unsigned int j=1; j<=width-2; j++) {
                    if (tile[ i*width+j ]==0) {
                        w++;
                    } else if (w>0) {
                        tile[ i*width+j-w ]=tile[ i*width+j ];
                        tile[ i*width+j ]=0;
                    }
                }
            }
        } else if (align==5){
            for (unsigned int j=1; j<=width-2 ;j++) {
                int w=0;
                for (unsigned int i=1; i<=(height-2)/2; i++) {
                    if (tile[ i*width+j ]==0) {
                        w++;
                    } else if (w>0) {
                        tile[ (i-w)*width+j ]=tile[ i*width+j ];
                        tile[ i*width+j ]=0;
                    }
                }
            }

            for (unsigned int j=1; j<=width-2 ;j++) {
                int w=0;
                for (unsigned int i=height-2; i>=(height-2)/2+1; i--) {
                    if (tile[ i*width+j ]==0) {
                        w++;
                    } else if (w>0) {
                        tile[ (i+w)*width+j ]=tile[ i*width+j ];
                        tile[ i*width+j ]=0;
                    }
                }
            }
        } else if (align==6) {
            for (unsigned int i=1; i<=height-2 ;i++) {
                int w=0;
                for (unsigned int j=1; j<=(width-2)/2; j++) {
                    if (tile[ i*width+j ]==0) {
                        w++;
                    } else if (w>0) {
                        tile[ i*width+j-w ]=tile[ i*width+j ];
                        tile[ i*width+j ]=0;
                    }
                }
            }
            for (unsigned int i=1; i<=height-2 ;i++) {
                int w=0;
                for (unsigned int j=width-2; j>=(width-2)/2+1; j--) {
                    if (tile[ i*width+j ]==0) {
                        w++;
                    } else if (w>0) {
                        tile[ i*width+j+w ]=tile[ i*width+j ];
                        tile[ i*width+j ]=0;
                    }
                }
            }
        }

    }
}
