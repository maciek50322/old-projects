#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include "Tiles.h"

//minimum window width/height
const unsigned int minwwidth = 400, minwheight = 200;

std::string itos(int integer) {
    if (integer==0) return "0";
    std::string s="";
    bool m=false;
    if (integer<0) {
        m=true;
        integer*=-1;
    }
    while (integer>0) {
        s=(char)('0'+integer%10)+s;
        integer/=10;
    }
    if (m) s="-"+s;
    return s;
}

void corrwind(sf::RenderWindow &window, sf::Event &event) {
    if (event.size.width < minwwidth) {
        event.size.width = minwwidth;
    }
    if (event.size.width >sf::VideoMode::getDesktopMode().width) {
        event.size.width=sf::VideoMode::getDesktopMode().width;
    }
    if (event.size.height < minwheight) {
        event.size.height = minwheight;
    }
    window.setSize(sf::Vector2u(event.size.width, event.size.height));
    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
    window.setView(sf::View(visibleArea));
}

int main( int argv, char* argc[])
{

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width*0.6,
                                          sf::VideoMode::getDesktopMode().height*0.6),
                            "Connect") ;

    sf::Vector2i lastpos=window.getPosition();

    window.setFramerateLimit(30);

    bool arial=false;
//font inkfree/arial
//"C:\\Windows\\Fonts\\Inkfree.ttf"
    sf::Font font;
   // std::cout<<font.loadFromMemory(MyFont_compressed_data, sizeof(MyFont_compressed_data));
    if (!font.loadFromFile("C:\\Windows\\Fonts\\Inkfree.ttf"))
        if (!font.loadFromFile("Inkfree.ttf"))
            if (!font.loadFromFile("inkfree.ttf")) {
                if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
                    if (!font.loadFromFile("Arial.ttf"))
                        if (!font.loadFromFile("arial.ttf")) {
                            window.close();
                            return 0; //no font found
                        }
                arial=true;
            }


//tiles
    sf::RectangleShape thet, fram;
    fram.setPosition(2, 2);
    fram.setOutlineThickness(2);
    fram.setOutlineColor(sf::Color(50, 100, 200, 100));
    fram.setFillColor(sf::Color::Transparent);
    sf::Text txt("START", font);    //start & letters
    txt.setFillColor(sf::Color(20, 20, 0));
    sf::Text txt2(txt);
    sf::Text txt3(txt);
    sf::Text txtt(txt);


    txtt.setString("00:00");
    int gamet;      //game clock
    sf::Clock gamec;
    int lastat=0, gameat=0, gameatc=0; //additional time main game or custom game
    const int subtimeconnect=1, subtimeshuffle=15, addtimehint=10;

    unsigned int width=4, height=4, chars=8, align=0;
        //align 0 - none, 1-top, 2-right, 3-bottom, 4-left, 5-topbottom, 6-leftright
    Tiles game(width, height, chars, align);


        //width, height, chars, align
    const unsigned int levels[] =
   {4, 4, 8, 0,     //1
    6, 4, 12, 0,    //2
    8, 6, 14, 3,    //3
    10, 6, 18, 1,    //4
    10, 6, 26, 4,
    12, 8, 26, 2,
    14, 10, 52, 0,  //7
    18, 10, 52, 6,
    16, 10, 52, 5,
    };

    const unsigned int maxwns=sizeof(levels)/sizeof(unsigned int) /4;
    unsigned int wns=1;
    bool cst=false;

    //screens
    const int selmenu=1, selplay=2, selcustom=3;
    int sel=selmenu;



    while (window.isOpen()) {
        bool change=true; //draw

//---------------------------------------------------------MENU SCREEN--------------------------------------------------------------
        if (sel==selmenu) {
            cst=false;
            txt.setString("START"+ ( wns==1 ? "" : "  "+itos(wns)+"/"+itos(maxwns)) );
            txt.setCharacterSize( std::min(window.getSize().x/7, window.getSize().y/7) );
            txt.setOutlineThickness(std::min(window.getSize().x/80, window.getSize().y/80));
            txt.setOrigin(txt.getGlobalBounds().width/2, txt.getGlobalBounds().height/2);
            txt.setPosition(window.getSize().x/2,
                            window.getSize().y/2-txt.getGlobalBounds().height*0.75);
            txt.setScale(1, 1);
            txt.setFillColor(sf::Color(240, 240, 255));
            txt.setOutlineColor(sf::Color(0, 0, 75));

            txt2.setScale(1, 1);
            txt2.setString("custom game");
            txt2.setCharacterSize(std::min(window.getSize().x/12, window.getSize().y/12));
            txt2.setOutlineThickness(std::min(window.getSize().x/160, window.getSize().y/160));
            txt2.setOrigin(txt2.getGlobalBounds().width/2, txt2.getGlobalBounds().height/2);
            txt2.setPosition(window.getSize().x/2,
                             window.getSize().y/2+txt.getGlobalBounds().height*0.5);
            txt2.setOutlineColor(sf::Color(0, 0, 75));
            txt2.setFillColor(sf::Color(240, 240, 255));

            if (arial) {
                    txt3.setString("try this with installed \"Inkfree.ttf\" font ");
                txt3.setFillColor(sf::Color::Red);
                txt3.setCharacterSize(std::min(window.getSize().x/16, window.getSize().y/16));
                txt3.setOrigin(txt3.getGlobalBounds().width/2, txt3.getGlobalBounds().height);
                txt3.setPosition(window.getSize().x/2, txt.getGlobalBounds().top-10);
            }

            fram.setSize(sf::Vector2f(window.getSize().x-4, window.getSize().y-4));

            while (window.isOpen()) {
                sf::Event event;
                if (!change && window.waitEvent(event)) {

                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::Resized) {
                        corrwind(window, event);

                        txt.setCharacterSize( std::min(event.size.width/7, event.size.height/7) );
                        txt.setOutlineThickness(std::min(event.size.width/80, event.size.height/80));
                        txt.setOrigin(txt.getGlobalBounds().width/2, txt.getGlobalBounds().height/2);
                        txt.setPosition(event.size.width/2,
                                        event.size.height/2-0.75*txt.getGlobalBounds().height);
                        txt2.setCharacterSize(std::min(event.size.width/12, event.size.height/12));
                        txt2.setOutlineThickness(std::min(event.size.width/160, event.size.height/160));
                        txt2.setOrigin(txt2.getGlobalBounds().width/2, txt2.getGlobalBounds().height/2);
                        txt2.setPosition(event.size.width/2,
                                         event.size.height/2+0.5*txt.getGlobalBounds().height);
                        txt3.setCharacterSize(std::min(event.size.width/16, event.size.height/16));
                        txt3.setOrigin(txt3.getGlobalBounds().width/2, txt3.getGlobalBounds().height);
                        txt3.setPosition(event.size.width/2, txt.getGlobalBounds().top);
                        fram.setSize(sf::Vector2f(window.getSize().x-4, window.getSize().y-4));
                        change=true;
                    }
                    if (event.type == sf::Event::MouseMoved) {
                        if (event.mouseMove.x>txt.getGlobalBounds().left && event.mouseMove.x<txt.getGlobalBounds().left+txt.getGlobalBounds().width &&
                            event.mouseMove.y>txt.getGlobalBounds().top  && event.mouseMove.y<txt.getGlobalBounds().top+txt.getGlobalBounds().height) {
                            change=true;
                            txt.setScale(1.1, 1.1);
                        } else if (txt.getScale().x!=1) {
                            change=true;
                            txt.setScale(1, 1);
                        }
                        if (event.mouseMove.x>txt2.getGlobalBounds().left && event.mouseMove.x<txt2.getGlobalBounds().left+txt2.getGlobalBounds().width &&
                            event.mouseMove.y>txt2.getGlobalBounds().top  && event.mouseMove.y<txt2.getGlobalBounds().top+txt2.getGlobalBounds().height) {
                            change=true;
                            txt2.setScale(1.1, 1.1);
                        } else if (txt2.getScale().x!=1) {
                            change=true;
                            txt2.setScale(1, 1);
                        }
                    }
                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left) {
                        if (txt.getScale().x!=1) {
                            sel=selplay;
                            txt.setScale(1, 1);
                        }
                        else if (txt2.getScale().x!=1) {
                            sel=selcustom;
                            txt2.setScale(1, 1);
                        }
                    }
                    if (event.type == sf::Event::MouseEntered) {
                        change=true;
                    }

                }
                if (sel!=selmenu) break;
                if (change) {
                    window.clear( sf::Color(0, 0, 0) );
                    window.draw(fram);
                    window.draw(txt);
                    window.draw(txt2);
                    if (arial) window.draw(txt3);
                    window.display();
                    change=false;
                }
            }
            txt.setScale(1, 1);
        }

//--------------------------------------------------------------PLAYING ----------------------------------------------------
        if (sel==selplay) {

            if (!cst) {
                if (wns>maxwns) wns=maxwns;
                else if (wns<1) wns=1;
                width=levels[(wns-1)*4];
                height=levels[(wns-1)*4+1];
                chars=levels[(wns-1)*4+2];
                align=levels[(wns-1)*4+3];

                if (wns==1) lastat=0;
            }
            game.setSize(width, height, chars, align);
            sf::Vector2f positions[width+1][height+1];


            thet.setSize(sf::Vector2f(  std::min(window.getSize().x/(width+2+2), window.getSize().y/(height+2+2)*4/5),
                                        std::min(window.getSize().x/(width+2+2)*5/4, window.getSize().y/(height+2+2) ) ));
            thet.setFillColor(sf::Color(0, 0, 75));
            thet.setOutlineColor(sf::Color::White);
            thet.setOutlineThickness(1);
            thet.setOrigin(0, 0);

            for (unsigned int i=1;i<=height;i++) {
                for (unsigned int j=1;j<=width;j++) {
                    positions[j][i]=sf::Vector2f( (window.getSize().x-thet.getSize().x*(width))/2 + thet.getSize().x*(j-1),
                                                  (window.getSize().y-thet.getSize().y*(height))/2 + thet.getSize().y*(i-1) );

                }
            }

            txt.setOutlineThickness(0);
            txt2.setOutlineThickness(0);
            txt.setOrigin(-0.15*thet.getSize().x, 0);
            txt.setCharacterSize( thet.getSize().x );
            txt.setFillColor(sf::Color(255, 255, 255));
            txt3.setString("? Hint ?");
            txt3.setCharacterSize(std::min(window.getSize().x/18, window.getSize().y/18));
            txt3.setOrigin(txt3.getGlobalBounds().width/2, txt3.getGlobalBounds().height/2);
            txt3.setPosition( window.getSize().x-txt3.getGlobalBounds().width/2*1.2,
                                window.getSize().y-txt3.getGlobalBounds().height);
            txt3.setFillColor(sf::Color(245, 245, 255));
            txt2.setFillColor(sf::Color(245, 245, 255));
            txt2.setString("<- Back");
            txt2.setScale(1, 1);
            txt2.setCharacterSize( std::min(window.getSize().x/18, window.getSize().y/18) );
            txt2.setOrigin(txt2.getGlobalBounds().width/2, txt2.getGlobalBounds().height/2);
            txt2.setPosition(txt2.getGlobalBounds().width/2*1.1, window.getSize().y-txt2.getGlobalBounds().height*1.2);

        //selected tile x, selected tile y, when 0, 0 => no tile selected
            int stx=0, sty=0;

            std::string lastpath="";
            sf::VertexArray lsp(sf::TriangleStrip, 8);
            for (int i=0;i<8;i++) {
                lsp[i].color=sf::Color::Red;
            }
            sf::Time tim; //time before disappearing
            sf::Clock clo;

            txtt.setFillColor(sf::Color(245, 245, 255));

            gamec.restart();
            gamet=gamec.getElapsedTime().asSeconds();

            if (cst) gameatc=0;
            else gameat=lastat;

            txtt.setCharacterSize(std::min(window.getSize().x/14, window.getSize().y/14));
            txtt.setString( ( (gamet+ (cst ? gameatc : gameat))/60<10 ? "0" : "") + itos( (gamet+ (cst ? gameatc : gameat))/60 )+":"+
                           ( (int)(gamet+ (cst ? gameatc : gameat))%60<10 ? "0" : "") + itos( (int)(gamet+ (cst ? gameatc : gameat))%60 ) );
            txtt.setOrigin(txtt.getGlobalBounds().width/2, 0);
            txtt.setPosition(window.getSize().x/2, 0);

            fram.setSize(sf::Vector2f(window.getSize().x-4, window.getSize().y-4));

            change=true;

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {

                    if (event.type == sf::Event::Closed)
                        window.close();

                    if (event.type == sf::Event::Resized){
        //resize window
                        corrwind(window, event);

        //size, position of tiles
                        thet.setSize(sf::Vector2f( std::min(event.size.width/(width+2+2), event.size.height/(height+2+2)*4/5),
                                                   std::min(event.size.width/(width+2+2)*5/4, event.size.height/(height+2+2) ) ));
                        txt.setOrigin(-0.15*thet.getSize().x, 0);
                        txt.setCharacterSize( thet.getSize().x );
                        txt3.setCharacterSize(std::min(window.getSize().x/18, window.getSize().y/18));
                        txt3.setScale(1, 1);
                        txt3.setOrigin(txt3.getGlobalBounds().width/2, txt3.getGlobalBounds().height/2);
                        txt3.setPosition( event.size.width-txt3.getGlobalBounds().width/2*1.2,
                                          event.size.height-txt3.getGlobalBounds().height);
                        for (unsigned int i=1;i<=height;i++) {
                            for (unsigned int j=1;j<=width;j++) {
                                positions[j][i]=sf::Vector2f( (event.size.width-thet.getSize().x*(width))/2 + thet.getSize().x*(j-1),
                                                              (event.size.height-thet.getSize().y*(height))/2 + thet.getSize().y*(i-1) );
                            }
                        }
                        txt2.setCharacterSize( std::min(event.size.width/18, event.size.height/18) );
                        txt2.setScale(1, 1);
                        txt2.setOrigin(txt2.getGlobalBounds().width/2, txt2.getGlobalBounds().height/2);
                        txt2.setPosition(txt2.getGlobalBounds().width/2*1.1, event.size.height-txt2.getGlobalBounds().height*1.2);
                        change=true;
                        fram.setSize(sf::Vector2f(window.getSize().x-4, window.getSize().y-4));
                        txtt.setCharacterSize(std::min(window.getSize().x/14, window.getSize().y/14));
                        txtt.setString( ( (gamet+ (cst ? gameatc : gameat))/60<10 ? "0" : "") + itos( (gamet+ (cst ? gameatc : gameat))/60 )+":"+
                                        ( (int)(gamet+ (cst ? gameatc : gameat))%60<10 ? "0" : "") + itos( (int)(gamet+ (cst ? gameatc : gameat))%60 ) );                        txtt.setOrigin(txtt.getGlobalBounds().width/2, 0);
                        txtt.setOrigin(txtt.getGlobalBounds().width/2, 0);
                        txtt.setPosition(window.getSize().x/2, 0);
                        tim=sf::Time::Zero;
                    }

                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button==sf::Mouse::Left) {
                            if ((event.mouseButton.x > positions[1][1].x && event.mouseButton.x < positions[width][height].x+thet.getSize().x &&
                                event.mouseButton.y > positions[1][1].y && event.mouseButton.y < positions[width][height].y+thet.getSize().y) ||
                                txt3.getScale().x!=1 ) {
            //click on tile or get hint
                                int setlines=0;
                                if (txt3.getScale().x!=1) {
                //lines by hint
                                    game.check();
                                    lastpath=game.getHint();
                                    setlines=2;
                                    tim=sf::seconds(3);
                                    if (cst) gameatc+=addtimehint;
                                    else gameat+=addtimehint;
                                } else {
                //click on tile, select tile, connect tile
                                    int nsx=1+(event.mouseButton.x-positions[1][1].x)/thet.getSize().x;
                                    int nsy=1+(event.mouseButton.y-positions[1][1].y)/thet.getSize().y;
                                    if (stx>0) {
                //connecting
                                        if (game.connect(stx, sty, nsx, nsy)) {
                //correctly connected
                                            if (cst) {
                                                gameatc-=subtimeconnect;
                                                while (gameatc+gamet<0) gameatc++;
                                            } else {
                                                gameat-=subtimeconnect;
                                                while (gameat+gamet<0) gameat++;
                                            }

                                            if (game.isEmpty()) {
                                                if (!cst) {
                                                    sel=selmenu;
                                                    wns++;
                                                    lastat=gameat+gamec.getElapsedTime().asSeconds();
                                                } else {
                                                    sel=selcustom;
                                                }
                                                stx=0; sty=0;

                                                break;
                                            }

                                            game.rAlign();
                                            if (!game.check()) {
                                                if (cst) {
                                                    gameatc-=subtimeshuffle;
                                                    while (gameatc+gamet<0) gameatc++;
                                                } else {
                                                    gameat-=subtimeshuffle;
                                                    while (gameat+gamet<0) gameat++;
                                                }
                                            }

                //lines by connect
                                            lastpath=game.getLastPath();
                                            setlines=1;
                                            tim=sf::milliseconds(150);
                                            game.sx=stx; game.sy=sty;
                                            game.ex=nsx; game.ey=nsy;

                                            stx=0; sty=0;
                                        } else if (game.getTile(nsx, nsy)>0) {
                                            stx=nsx; sty=nsy;
                                        } else  {
                                            stx=0; sty=0;
                                        }

                                    } else if (game.getTile(nsx, nsy)>0) {
                //selecting
                                        stx=nsx;
                                        sty=nsy;
                                    }
                                }
                                if (setlines>0) {
                                    unsigned int donc=2, li=0;
                                    lsp[0].position=sf::Vector2f(positions[game.sx][game.sy].x+thet.getSize().x/2,
                                                                 positions[game.sx][game.sy].y+thet.getSize().y/2);
                                    for (unsigned int i=1;i<lastpath.length();i++) {
                                        if (lastpath[i]!=lastpath[i-1]) {
                                            if (lastpath[i-1]=='0'+game.UP) {
                                                lsp[donc].position=sf::Vector2f(lsp[donc-2].position.x,
                                                                                lsp[donc-2].position.y-(i-li)*thet.getSize().y);
                                            } else if (lastpath[i-1]=='0'+game.RIGHT) {
                                                lsp[donc].position=sf::Vector2f(lsp[donc-2].position.x+(i-li)*thet.getSize().x,
                                                                                lsp[donc-2].position.y);
                                            } else if (lastpath[i-1]=='0'+game.DOWN) {
                                                lsp[donc].position=sf::Vector2f(lsp[donc-2].position.x,
                                                                                lsp[donc-2].position.y+(i-li)*thet.getSize().y);
                                            } else if (lastpath[i-1]=='0'+game.LEFT) {
                                                lsp[donc].position=sf::Vector2f(lsp[donc-2].position.x-(i-li)*thet.getSize().x,
                                                                                lsp[donc-2].position.y);
                                            }
                                            donc+=2;
                                            li=i;
                                        }
                                    }
                                    lsp[donc].position=sf::Vector2f(positions[game.ex][game.ey].x+thet.getSize().x/2,
                                                                    positions[game.ex][game.ey].y+thet.getSize().y/2);
                                    for (unsigned int i=donc+2;i<8;i+=2) {
                                        lsp[i].position=lsp[donc].position;
                                    }
                                    for (unsigned int i=1;i<8;i+=2) {
                                        lsp[i].position=sf::Vector2f(lsp[i-1].position.x+thet.getSize().x/16,
                                                                     lsp[i-1].position.y+thet.getSize().x/16);
                                    }


                                    clo.restart();
                                    setlines=0;
                                }
                            } else {
            //deselect
                                stx=0; sty=0;
                            }

                            change=true;

                            if (txt2.getScale().x!=1) {
                                if (!cst)
                                    sel=selmenu;
                                else sel=selcustom;
                                txt2.setScale(1, 1);
                            }
                        }
                    }
                    if (event.type==sf::Event::MouseMoved) {
                        if (event.mouseMove.x<txt2.getGlobalBounds().left+txt2.getGlobalBounds().width && event.mouseMove.y>txt2.getGlobalBounds().top ) {
                            txt2.setScale(1.1, 1.1);
                            change=true;
                        } else if (txt2.getScale().x!=1){
                            txt2.setScale(1, 1);
                            change=true;
                        }
                        if (event.mouseMove.x>txt3.getGlobalBounds().left && event.mouseMove.y>txt3.getGlobalBounds().top) {
                            txt3.setScale(1.1, 1.1);
                            change=true;
                        } else if (txt3.getScale().x!=1) {
                            txt3.setScale(1, 1);
                            change=true;
                        }
                    }
                    if (event.type==sf::Event::MouseEntered) {
                        change=true;
                    }
                }

                if (sel!=selplay) break;

        //------------------------------------------------------------DRAWING-------------------------------------------------------------
                if (change) {
                window.clear( sf::Color(0, 0, 0) );
                window.draw(fram);
        //draw tiles, lines

                    for (unsigned int i=1;i<=height;i++) {
                        for (unsigned int j=1;j<=width;j++) {
                            if ( game.getTile(j, i)>0 ) {
                                thet.setPosition(positions[j][i]);
                                txt.setPosition(positions[j][i]);
                                txt.setString( game.getChar( game.getTile(j, i) ) );
                                window.draw(thet);
                                window.draw(txt);
                            }
                        }
                    }

                    if (clo.getElapsedTime()<=tim) {
                        if (tim.asMilliseconds()!=150 && game.getTile(game.sx, game.sy)!=0 && game.getTile(game.ex, game.ey)!=0)  {
                            thet.setPosition(positions[game.sx][game.sy]);
                            txt.setPosition(positions[game.sx][game.sy]);
                            txt.setString( game.getChar(game.getTile(game.sx, game.sy)) );
                            thet.setFillColor(sf::Color(0, 0, 175));
                            window.draw(thet);
                            window.draw(txt);
                            thet.setPosition(positions[game.ex][game.ey]);
                            txt.setPosition(positions[game.ex][game.ey]);
                            txt.setString( game.getChar(game.getTile(game.ex, game.ey)) );
                            window.draw(thet);
                            window.draw(txt);
                            thet.setFillColor(sf::Color(0, 0, 75));
                        }
                        window.draw(lsp);
                        change=true;
                        sf::sleep(sf::milliseconds(50));
                    } else change=false;

                    if (stx>0) {
                        thet.setPosition(positions[stx][sty]);
                        txt.setPosition(positions[stx][sty]);
                        txt.setString(game.getChar(game.getTile(stx, sty)));
                        thet.setOutlineThickness(1+thet.getGlobalBounds().width/32);
                        window.draw(thet);
                        window.draw(txt);
                        thet.setOutlineThickness(1);
                    }

                    window.draw(txt2);
                    window.draw(txt3);

                    gamet=gamec.getElapsedTime().asSeconds();
                    txtt.setString( ( (gamet+ (cst ? gameatc : gameat))/60<10 ? "0" : "") + itos( (gamet+ (cst ? gameatc : gameat))/60 )+":"+
                                    ( (int)(gamet+ (cst ? gameatc : gameat))%60<10 ? "0" : "") + itos( (int)(gamet+ (cst ? gameatc : gameat))%60 ) );
                    txtt.setOrigin(txtt.getGlobalBounds().width/2, 0);
                    window.draw(txtt);

                    window.display();
                } else  {
                    sf::sleep(sf::milliseconds(100));

                    if (gamet!=gamec.getElapsedTime().asSeconds()) {
                        change=true;
                    }

                    if (lastpos!=window.getPosition()) {
                        change=true;
                        lastpos=window.getPosition();
                    }
                }
            }
        }

//---------------------------------------------------------------WIN / LOSE SCREEN---------------------------------------------------------------------


        if ( (!cst && wns==maxwns+1 && sel==selmenu) ||
             (cst && game.isEmpty())) {

            if (!cst && wns>maxwns) {
                wns=1;
            }

            sel=0; //void, stay here

            txt.setString("YOU WIN");
            txt.setFillColor(sf::Color(200, 200, 255));
            txt.setScale(1, 1);
            txt.setCharacterSize( std::min(window.getSize().x/5, window.getSize().y/5) );
            txt.setOutlineThickness( std::min(window.getSize().x/120, window.getSize().y/120) );
            txt.setOutlineColor(sf::Color(225, 225, 255, 200));
            txt.setOrigin(txt.getGlobalBounds().width/2, txt.getGlobalBounds().height/2);
            txt.setPosition(window.getSize().x/2, window.getSize().y/2-txt.getGlobalBounds().height*1.1);

            txt3.setString("your score: "+itos(cst ? 0 : lastat));
            txt3.setFillColor(sf::Color(200, 200, 255));
            txt3.setScale(1, 1);
            txt3.setCharacterSize( std::min(window.getSize().x/12, window.getSize().y/12) );
            txt3.setOutlineThickness( std::min(window.getSize().x/240, window.getSize().y/240 ));
            txt3.setOutlineColor(sf::Color(225, 225, 255, 200));
            txt3.setOrigin(txt3.getGlobalBounds().width/2, txt3.getGlobalBounds().height/2);
            txt3.setPosition(window.getSize().x/2, window.getSize().y/2);

            txt2.setOutlineThickness(0);
            txt2.setFillColor(sf::Color::White);
            txt2.setString("<- Back");
            txt2.setScale(1, 1);
            txt2.setCharacterSize( std::min(window.getSize().x/18, window.getSize().y/18) );
            txt2.setOrigin(txt2.getGlobalBounds().width/2, txt2.getGlobalBounds().height/2);
            txt2.setPosition(txt2.getGlobalBounds().width/2*1.1, window.getSize().y-txt2.getGlobalBounds().height*1.2);

            fram.setSize(sf::Vector2f(window.getSize().x-4, window.getSize().y-4));

            change=true;
            while (window.isOpen()) {

                sf::Event event;
                if (!change && window.waitEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::Resized) {
                        corrwind(window, event);

                        txt2.setCharacterSize( std::min(window.getSize().x/18, window.getSize().y/18) );
                        txt2.setScale(1, 1);
                        txt2.setOrigin(txt2.getGlobalBounds().width/2, txt2.getGlobalBounds().height/2);
                        txt2.setPosition(txt2.getGlobalBounds().width/2*1.1, window.getSize().y-txt2.getGlobalBounds().height*1.2);
                        txt.setCharacterSize( std::min(window.getSize().x/5, window.getSize().y/5) );
                        txt.setOutlineThickness( std::min(window.getSize().x/120, window.getSize().y/120) );
                        txt.setOrigin(txt.getGlobalBounds().width/2, txt.getGlobalBounds().height/2);
                        txt.setPosition(window.getSize().x/2, window.getSize().y/2-txt.getGlobalBounds().height*1.1);
                        txt3.setCharacterSize( std::min(window.getSize().x/12, window.getSize().y/12) );
                        txt3.setOutlineThickness( std::min(window.getSize().x/240, window.getSize().y/240 ));
                        txt3.setOrigin(txt3.getGlobalBounds().width/2, txt3.getGlobalBounds().height/2);
                        txt3.setPosition(window.getSize().x/2, window.getSize().y/2);
                        change=true;
                        fram.setSize(sf::Vector2f(window.getSize().x-4, window.getSize().y-4));


                    }
                    if (event.type== sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (txt2.getScale().x!=1) {
                                if (!cst)
                                    sel=selmenu;
                                else sel=selcustom;
                            }
                        }
                    }
                    if (event.type == sf::Event::MouseMoved) {
                        if (event.mouseMove.x<txt2.getGlobalBounds().left+txt2.getGlobalBounds().width && event.mouseMove.y>txt2.getGlobalBounds().top ) {
                            txt2.setScale(1.1, 1.1);
                            change=true;
                        } else if (txt2.getScale().x!=1){
                            txt2.setScale(1, 1);
                            change=true;
                        }
                    }
                    if (event.type==sf::Event::MouseEntered) {
                        change=true;
                    }
                }

                if (sel!=0) break;

                if (change) {
                    window.clear(sf::Color(0, 0, 55) );
                    window.draw(fram);

                    window.draw(txt);
                    window.draw(txt2);
                    window.draw(txt3);

                    window.display();

                    change=false;
                }
            }
        }

//------------------------------------------------------------------CUSTOM GAME------------------------------------------------------------------------


        if (sel==selcustom) {
            const unsigned int vwmin=2, vwmax=40, vhmin=2, vhmax=15, vwstep=2, vhstep=1, vcmax=chr.length()-1, vcmin=1, vcstep=1;
            sf::RectangleShape slid, slim;
            sf::RectangleShape gal, gch;
            int chgsl=0;


            txt.setOutlineThickness(0);
            txt2.setOutlineThickness(0);
            txt.setString("  Chars: " +itos(chars)+ (chars<10 ? "   " : " ") +"\n  Width: "+ itos(width)+(width<10 ? "   " : " ") +"\nHeight: "+itos(height)+(height<10 ? "   " : " "));
            txt.setFillColor(sf::Color::White);
            txt2.setString("START");
            txt2.setFillColor(sf::Color::White);
            txt2.setScale(1, 1);
            txt3.setOutlineThickness(0);
            txt3.setString("<- Back");
            txt3.setFillColor(sf::Color::White);
            txt3.setScale(1, 1);

            slid.setFillColor(sf::Color::Transparent);
            slid.setOutlineColor(sf::Color::White);
            slid.setOutlineThickness(1);

            slim.setFillColor(sf::Color::Black);
            slim.setOutlineColor(sf::Color::White);
            slim.setOutlineThickness(1);

            gal.setFillColor(sf::Color(100, 100, 150, 200));
            gal.setOutlineColor(sf::Color(200, 200, 255));
            gal.setOutlineThickness(1);
            gch.setFillColor(sf::Color(255, 255, 255, 100));
            gch.setOutlineThickness(0);
            thet.setFillColor(sf::Color(0, 0, 0, 0));
            thet.setOutlineColor(sf::Color::White);
            thet.setOutlineThickness(1);

           txt.setCharacterSize( std::min(window.getSize().x/13, window.getSize().y/13) );
                        txt.setPosition(window.getSize().x*0.45, window.getSize().y/5);
                        txt.setOrigin(txt.getGlobalBounds().width, txt.getGlobalBounds().height/2);
                        slid.setSize(sf::Vector2f(window.getSize().x*0.55-txt.getGlobalBounds().left,
                                                  std::min(window.getSize().x*0.01, window.getSize().y*0.01)));
                        slid.setOrigin(0, slid.getSize().y/2);
                        slim.setSize(sf::Vector2f( std::min(window.getSize().x*0.01, window.getSize().y*0.01),
                                                std::min(window.getSize().x*0.03, window.getSize().y*0.03) ));
                        slim.setOrigin(slim.getGlobalBounds().width/2 , slim.getGlobalBounds().height/2);
                        txt3.setCharacterSize( std::min(window.getSize().x/18, window.getSize().y/18) );
                        txt3.setOrigin(txt3.getGlobalBounds().width/2, txt3.getGlobalBounds().height/2);
                        txt3.setPosition(txt3.getGlobalBounds().width/2*1.1, window.getSize().y-txt3.getGlobalBounds().height*1.2);
                        thet.setSize(sf::Vector2f( window.getSize().x/4, window.getSize().y/4) );
                        thet.setOrigin(thet.getSize().x/2, thet.getSize().y/2);
                        thet.setPosition(window.getSize().x/2 , window.getSize().y/2);
                        txt2.setCharacterSize( std::min(window.getSize().x/16, window.getSize().y/16) );
                        txt2.setOrigin(txt2.getGlobalBounds().width/2, txt2.getGlobalBounds().height/2);
                        txt2.setPosition(window.getSize().x-txt2.getGlobalBounds().width/2*1.2, window.getSize().y-txt2.getGlobalBounds().height);
                        fram.setSize(sf::Vector2f(window.getSize().x-4, window.getSize().y-4));
            if (cst) txt3.setScale(1.1, 1.1);

            change=true;
            int cat=0;
            while (window.isOpen()) {

                sf::Event event;
                if (!change && window.waitEvent(event)) {
                    if (event.type==sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::Resized){
                        corrwind(window, event);

                        txt.setCharacterSize( std::min(window.getSize().x/13, window.getSize().y/13) );
                        txt.setPosition(window.getSize().x*0.45, window.getSize().y/5);
                        txt.setOrigin(txt.getGlobalBounds().width, txt.getGlobalBounds().height/2);
                        slid.setSize(sf::Vector2f(window.getSize().x*0.55-txt.getGlobalBounds().left,
                                                  std::min(window.getSize().x*0.01, window.getSize().y*0.01)));
                        slid.setOrigin(0, slid.getSize().y/2);
                        slim.setSize(sf::Vector2f( std::min(window.getSize().x*0.01, window.getSize().y*0.01),
                                                std::min(window.getSize().x*0.03, window.getSize().y*0.03) ));
                        slim.setOrigin(slim.getGlobalBounds().width/2 , slim.getGlobalBounds().height/2);
                        txt3.setCharacterSize( std::min(window.getSize().x/18, window.getSize().y/18) );
                        txt3.setScale(1, 1);
                        txt3.setOrigin(txt3.getGlobalBounds().width/2, txt3.getGlobalBounds().height/2);
                        txt3.setPosition(txt3.getGlobalBounds().width/2*1.1, window.getSize().y-txt3.getGlobalBounds().height*1.2);
                        thet.setSize(sf::Vector2f( window.getSize().x/4, window.getSize().y/4) );
                        thet.setOrigin(thet.getSize().x/2, thet.getSize().y/2);
                        thet.setPosition(window.getSize().x/2 , window.getSize().y/2);
                        txt2.setCharacterSize( std::min(window.getSize().x/16, window.getSize().y/16) );
                        txt2.setScale(1, 1);
                        txt2.setOrigin(txt2.getGlobalBounds().width/2, txt2.getGlobalBounds().height/2);
                        txt2.setPosition(window.getSize().x-txt2.getGlobalBounds().width/2*1.2, window.getSize().y-txt2.getGlobalBounds().height);
                        fram.setSize(sf::Vector2f(window.getSize().x-4, window.getSize().y-4));

                        change=true;
                    }

                    if (event.type==sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button==sf::Mouse::Left) {
                            if (event.mouseButton.x>slid.getPosition().x-slim.getSize().x && event.mouseButton.x<slid.getSize().x+slid.getPosition().x+slim.getSize().x) {
                                if (event.mouseButton.y>txt.getGlobalBounds().top && event.mouseButton.y<txt.getGlobalBounds().top + txt.getGlobalBounds().height/3) {
                                    chars=(int)((event.mouseButton.x+slid.getGlobalBounds().width/(vcmax-vcmin)/2*vwstep-slid.getPosition().x)*((vcmax-vcmin)/vcstep)/slid.getGlobalBounds().width)*vcstep +vcmin;
                                    cat=1;
                                } else if (event.mouseButton.y>txt.getGlobalBounds().top+ txt.getGlobalBounds().height/3 && event.mouseButton.y<txt.getGlobalBounds().top + txt.getGlobalBounds().height/3*2) {
                                    width=(int)((event.mouseButton.x+slid.getGlobalBounds().width/(vwmax-vwmin)/2*vwstep-slid.getPosition().x)*((vwmax-vwmin)/vwstep)/slid.getGlobalBounds().width)*vwstep +vwmin;
                                    cat=2;
                                } else if (event.mouseButton.y>txt.getGlobalBounds().top+txt.getGlobalBounds().height/3*2 && event.mouseButton.y<txt.getGlobalBounds().top + txt.getGlobalBounds().height) {
                                    height=(int)((event.mouseButton.x+slid.getGlobalBounds().width/(vhmax-vhmin)/2*vhstep-slid.getPosition().x)*((vhmax-vhmin)/vhstep)/slid.getGlobalBounds().width)*vhstep +vhmin;
                                    cat=3;
                                }
                                txt.setString("  Chars: " +itos(chars)+ (chars<10 ? "   " : " ") +"\n  Width: "+ itos(width)+(width<10 ? "   " : " ") +"\nHeight: "+itos(height)+(height<10 ? "   " : " "));
                            }
                            if (chgsl>0) {
                                if(chgsl==1) {
                                    if (align==1) align=0;
                                    else if (align==3) align=5;
                                    else if (align==5) align=3;
                                    else align=1;
                                } else if (chgsl==2) {
                                    if (align==2) align=0;
                                    else if (align==4) align=6;
                                    else if (align==6) align=4;
                                    else align=2;
                                } else if (chgsl==3) {
                                    if (align==3) align=0;
                                    else if (align==1) align=5;
                                    else if (align==5) align=1;
                                    else align=3;
                                } else if (chgsl==4) {
                                        if (align==4) align=0;
                                        else if (align==2) align=6;
                                        else if (align==6) align=2;
                                        else align=4;
                                }
                            }

                            if (txt3.getScale().x!=1) {
                                sel=selmenu;
                                txt3.setScale(1, 1);
                            }
                            if (txt2.getScale().x!=1) {
                                sel=selplay;
                                txt2.setScale(1, 1);
                                cst=true;
                            }
                            change=true;
                        }
                    }
                    if (event.type==sf::Event::MouseButtonReleased) {
                        if (event.mouseButton.button==sf::Mouse::Left) cat=0;
                    }
                    if (event.type==sf::Event::MouseMoved) {
                        if (cat>0) {
                            if (cat==1) {
                                if (event.mouseMove.x<slid.getPosition().x) chars=vcmin;
                                else if (event.mouseMove.x>slid.getPosition().x+slid.getGlobalBounds().width) chars=vcmax;
                                else chars=(int)((event.mouseMove.x+slid.getGlobalBounds().width/(vcmax-vcmin)/2*vcstep-slid.getPosition().x)*((vcmax-vcmin)/vcstep)/slid.getGlobalBounds().width)*vcstep +vcmin;
                            }
                            else if (cat==2) {
                                if (event.mouseMove.x<slid.getPosition().x) width=vwmin;
                                else if (event.mouseMove.x>slid.getPosition().x+slid.getGlobalBounds().width) width=vwmax;
                                else width=(int)((event.mouseMove.x+slid.getGlobalBounds().width/(vwmax-vwmin)/2*vwstep-slid.getPosition().x)*((vwmax-vwmin)/vwstep)/slid.getGlobalBounds().width)*vwstep +vwmin;
                            }
                            else if (cat==3) {
                                if (event.mouseMove.x<slid.getPosition().x) height=vhmin;
                                else if (event.mouseMove.x>slid.getPosition().x+slid.getGlobalBounds().width) height=vhmax;
                                else height=(int)((event.mouseMove.x+slid.getGlobalBounds().width/(vhmax-vhmin)/2*vhstep-slid.getPosition().x)*((vhmax-vhmin)/vhstep)/slid.getGlobalBounds().width)*vhstep +vhmin;
                            }
                            txt.setString("  Chars: " +itos(chars)+ (chars<10 ? "   " : " ") +"\n  Width: "+ itos(width)+(width<10 ? "   " : " ") +"\nHeight: "+itos(height)+(height<10 ? "   " : " "));
                            change=true;
                        }
                        else if (event.mouseMove.x<txt3.getGlobalBounds().left+txt3.getGlobalBounds().width && event.mouseMove.y>txt3.getGlobalBounds().top) {
                            txt3.setScale(1.1, 1.1);
                            change=true;
                        } else if (txt3.getScale().x!=1) {
                            txt3.setScale(1, 1);
                            change=true;
                        }
                        if (event.mouseMove.x>txt2.getGlobalBounds().left && event.mouseMove.y>txt2.getGlobalBounds().top) {
                            txt2.setScale(1.1, 1.1);
                            change=true;
                        } else if (txt2.getScale().x!=1) {
                            txt2.setScale(1, 1);
                            change=true;
                        }
                        if (cat==0) {
                            if (event.mouseMove.x>=thet.getGlobalBounds().left && event.mouseMove.x<=thet.getGlobalBounds().left+thet.getGlobalBounds().width &&
                                    event.mouseMove.y<=thet.getGlobalBounds().top+thet.getGlobalBounds().height && event.mouseMove.y>=thet.getGlobalBounds().top) {
                                if ( (event.mouseMove.x-thet.getGlobalBounds().left)*thet.getGlobalBounds().height>(event.mouseMove.y-thet.getGlobalBounds().top)*thet.getGlobalBounds().width) {
                                    if ( thet.getGlobalBounds().height*(1-(event.mouseMove.x-thet.getGlobalBounds().left)/thet.getGlobalBounds().width)>(event.mouseMove.y-thet.getGlobalBounds().top)) {
                                        if (chgsl!=1) {
                                            change=true;
                                            chgsl=1;
                                        }
                                    } else {
                                        if (chgsl!=2) {
                                            change=true;
                                            chgsl=2;
                                        }
                                    }
                                } else {
                                    if ( thet.getGlobalBounds().height*(1-(event.mouseMove.x-thet.getGlobalBounds().left)/thet.getGlobalBounds().width)<(event.mouseMove.y-thet.getGlobalBounds().top))
                                    {
                                        if (chgsl!=3) {
                                            change=true;
                                            chgsl=3;
                                        }
                                    }
                                    else {
                                        if (chgsl!=4) {
                                            change=true;
                                            chgsl=4;
                                        }
                                    }
                                }
                            } else if (chgsl!=0) {
                                chgsl=0;
                                change=true;
                            }
                        }
                    }
                    if (event.type==sf::Event::MouseEntered) {
                        change=true;
                    }

                }
                if (sel!=selcustom) break;

                if (change) {
                    window.clear( sf::Color(0, 0, 0) );
                    window.draw(fram);

                    for (int i=0;i<3;i++) {
                        slid.setPosition(window.getSize().x*0.45, txt.getGlobalBounds().top+(2*i+1)*txt.getGlobalBounds().height/6);
                        if (i==0)
                            slim.setPosition(slid.getPosition().x+slid.getGlobalBounds().width/((vcmax-vcmin))*(chars-vcmin), slid.getPosition().y);
                        else if (i==1)
                            slim.setPosition(slid.getPosition().x+slid.getGlobalBounds().width/((vwmax-vwmin))*(width-vwmin), slid.getPosition().y);
                        else if (i==2)
                            slim.setPosition(slid.getPosition().x+slid.getGlobalBounds().width/((vhmax-vhmin))*(height-vhmin), slid.getPosition().y);
                        window.draw(slid);
                        window.draw(slim);
                    }
                    window.draw(txt);

                    window.draw(thet);

                    if (align>0) {
                        if (align%2==1) {
                            gal.setSize(sf::Vector2f( thet.getGlobalBounds().width-2, std::min(thet.getGlobalBounds().width, thet.getGlobalBounds().height)/10-2));
                            gal.setPosition(thet.getGlobalBounds().left+1, thet.getGlobalBounds().top+1);
                            if (align!=3) window.draw(gal);
                            if (align!=1) gal.setPosition(thet.getGlobalBounds().left+1, thet.getGlobalBounds().top+thet.getGlobalBounds().height-gal.getSize().y-1);
                        } else {
                            gal.setSize(sf::Vector2f(std::min(thet.getGlobalBounds().width-2, thet.getGlobalBounds().height)/10, thet.getGlobalBounds().height-2));
                            gal.setPosition(thet.getGlobalBounds().left+1, thet.getGlobalBounds().top+1);
                            if (align!=2) window.draw(gal);
                            if (align!=4) gal.setPosition(thet.getGlobalBounds().left+thet.getGlobalBounds().width-gal.getSize().x-1, thet.getGlobalBounds().top+1);
                        }
                        window.draw(gal);
                    }
                    if (chgsl>0) {
                        if (chgsl%2==1) {
                            gch.setSize(sf::Vector2f( thet.getGlobalBounds().width, std::min(thet.getGlobalBounds().width, thet.getGlobalBounds().height)/10));
                            if (chgsl==1) gch.setPosition(thet.getGlobalBounds().left, thet.getGlobalBounds().top);
                            if (chgsl==3) gch.setPosition(thet.getGlobalBounds().left, thet.getGlobalBounds().top+thet.getGlobalBounds().height-gch.getSize().y);
                        } else {
                            gch.setSize(sf::Vector2f(std::min(thet.getGlobalBounds().width, thet.getGlobalBounds().height)/10, thet.getGlobalBounds().height));
                            if (chgsl==4) gch.setPosition(thet.getGlobalBounds().left, thet.getGlobalBounds().top);
                            if (chgsl==2) gch.setPosition(thet.getGlobalBounds().left+thet.getGlobalBounds().width-gch.getSize().x, thet.getGlobalBounds().top);
                        }
                        window.draw(gch);
                    }

                    window.draw(txt3);
                    window.draw(txt2);
                    window.display();
                    change=false;
                }
            }
        }
    }

    return 0;
}
