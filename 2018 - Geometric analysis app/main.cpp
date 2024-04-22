#include <iostream>
#include <cmath>
#include <sstream>
#include "Point.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

RenderWindow app(VideoMode(800, 600), "Gometry");
Font font;
RectangleShape rectangle, rectangle2;           //rigth-side, left-side
double centerx=0, centery=0;
double scalesteps[]={1.0/100, 1.0/50, 1.0/20, 1.0/10, 1.0/5, 1.0/2, 1, 2, 5, 10};   // 1/10 - zoomed in, 10 - zoomed out
unsigned int maxstep=sizeof(scalesteps)/sizeof(double) , scalestep=4;
double scale=scalesteps[scalestep];
bool byc=false;

int catchedpoint=-1;                            //point
int pcount=0;                                   //number of selected points (0-3)
string bp="   ";                                //selected points
Text bpt( bp , font);                           //selected points
VertexArray cbp(LinesStrip, 3);                 //connects points
VertexArray cooax(Lines, 4);                    //axes
Text posxys("x1 (0; 0)", font);

CircleShape circle;                             //point sample
CircleShape csh;                                // help circle
VertexArray lsh(Lines, 2);                      // help line
double line1, line2, line3;
Text pinfocheck("AB=[0; 0]", font);             //info check
Text pinfo("", font);                           //info
Text nin("A'x=  Type number...", font);         //textbox
bool gettin=false;                              //textbox
string getn="";                                 //textbox
int chg=0;                                      //button (ch/choose)
Text chin1("x", font);                          //choose1
Text chin2("y", font);                          //choose2
Text chin3("x", font);                          //choose3
Text chin4("y", font);                          //choose4
Text chinenter("Enter", font);                  //enter
RectangleShape ch1, ch2, ch3, ch4, chenter;

string dtos(double x);                          //double to string
void upva();                                    //board<- shapes etc.
void addpoint();                                //"+"
void removepoint();                             //"-"
string ppssp(int p);
void ppss();
void selectpoint(int i);                        //select point
void deselectpoint(int i);                      //deselect point
bool inrect(RectangleShape& r, double x, double y);//if point in rectangle r
void setfocus(int which, bool activate);        //set focus of ch
void endtyping();
void bacti(int i);                              //actions for buttons
void msetpp(int cp, double x, double y);        //mouse set point position

struct Pt {                                     //point-board bridge
    Point p;
    CircleShape* circle;
    Text nm;
    char name;
    Pt(double x, double y, char n, CircleShape* c) {
        name=n;
        nm.setFont(font);
        nm.setString(n);
        circle=c;
        setpos(x, y);
        nm.setCharacterSize(22);
        nm.setColor(Color(64, 64, 64));
    }
    void setpos(double x, double y) {               //point
        p.x=x;
        p.y=y;
        dpl();
    }
    void dpl() {                                    //board<-point
        circle->setPosition((app.getSize().x-rectangle.getSize().x+rectangle2.getSize().x)/2+(p.x-centerx)/scale,
                            app.getSize().y/2-(p.y-centery)/scale);
        nm.setPosition(circle->getPosition().x-8, circle->getPosition().y-33);
    }
};

vector<Pt> vp;

int main() {
    app.setFramerateLimit(60);                  //fps up to 60

    if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
        if (!font.loadFromFile("D:\\Windows\\Fonts\\Arial.ttf"))
            if (!font.loadFromFile("Arial.ttf")) return EXIT_FAILURE;

    Text add("+", font);
    add.setColor(Color::Black);
    add.setOrigin(8, 18);
    add.setPosition(22, 20);
    Text sub("-", font);
    sub.setColor(Color::Black);
    sub.setOrigin(4, 22);
    sub.setPosition(22, 20+40);
    Text help("?", font);
    help.setColor(Color::Black);
    help.setOrigin(8, 20);
    help.setPosition(22, app.getSize().y-60);
    Text stn("...", font);
    stn.setColor(Color::Black);
    stn.setOrigin(12, 30);
    stn.setPosition(22, app.getSize().y-20);

    rectangle.setSize(Vector2f(195, app.getSize().y));    //right-side
    rectangle.setOutlineThickness(0);
    rectangle.setFillColor(Color(240, 240, 235));
    rectangle.setPosition(app.getSize().x-rectangle.getSize().x, 0);
    rectangle2.setPosition(0, 0);                               //left-side
    rectangle2.setSize(Vector2f(45, app.getSize().y));
    rectangle2.setFillColor(Color(220, 220, 240));
    rectangle2.setOutlineThickness(0);


    circle.setRadius(5);                    //point sample
    circle.setOrigin(5, 5);
    circle.setFillColor(Color(50, 50, 50));
    circle.setPointCount(60);

    csh.setFillColor(Color(0,0, 0, 0));
    csh.setOutlineColor(Color(180,0,0));
    csh.setOutlineThickness(1);
    csh.setPointCount(100);
    lsh[0].color=Color(180, 0, 0);
    lsh[1].color=lsh[0].color;

    cbp.setPrimitiveType(sf::Triangles);    //connects points
    cbp[0].color=Color(50, 50, 255, 10);
    cbp[1].color=Color(50, 50, 255, 170);
    cbp[2].color=Color(50, 50, 255, 10);
    cbp[0].position=Vector2f(0, 0);
    cbp[1].position=Vector2f(0, 0);
    cbp[2].position=Vector2f(0, 0);

    for (int i=0;i<4;i++) cooax[i].color=Color(0, 0, 0, 200);
    upva();

    bpt.setCharacterSize(20);               //selected points ("   ")
    bpt.setColor(Color::Black);
    bpt.setPosition(app.getSize().x-bpt.getLocalBounds().width/2-rectangle.getSize().x/2, 10);

    posxys.setColor(Color::Black);
    posxys.setCharacterSize(15);
    posxys.setPosition(rectangle2.getSize().x+5, app.getSize().y-20);

    pinfo.setCharacterSize(18);
    pinfo.setColor(Color(0, 0, 100, 200));
    pinfo.setPosition(rectangle.getPosition().x+10, 35);
    pinfocheck.setCharacterSize(18);
    pinfocheck.setColor(Color(0, 0, 100, 200));
    pinfocheck.setPosition(rectangle.getPosition().x+10, 35);

    nin.setCharacterSize(18);
    nin.setColor(Color(0, 0, 0));
    chinenter=chin4=chin3=chin2=chin1=nin;
    chinenter.setString("Enter");
    ch1.setSize(Vector2f(rectangle.getSize().x/2-2, 25));
    ch1.setFillColor(rectangle.getFillColor());
    ch1.setOutlineColor(Color(0, 0, 0, 64));
    ch1.setOutlineThickness(1);
    ch4=ch3=ch2=ch1;
    chenter=ch1;
    chenter.setSize(Vector2f(rectangle.getSize().x-2, 25));

    upva();
    ppss();

    bool catched=false;             //board
    double catchx, catchy;          //board
    while (app.isOpen()) {
        Event event;
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::MouseMoved) {                      //mouse moved
                if (event.mouseMove.x<rectangle2.getSize().x) {              //rectangle2
                    add.setScale(1, 1);
                    sub.setScale(1, 1);
                    help.setScale(1, 1);
                    stn.setScale(1, 1);
                    if (event.mouseMove.y<40) {                                 //"+"
                        add.setScale(1.5, 1.5);
                    } else if (event.mouseMove.y<80) {                          //"-"
                        sub.setScale(1.5, 1.5);
                    } else if (event.mouseMove.y>app.getSize().y-40) {          //"?"
                        stn.setScale(1.5, 1.5);
                    } else if (event.mouseMove.y>app.getSize().y-80) {          //"..."
                        help.setScale(1.5, 1.5);
                    }
                }
                else if (event.mouseMove.x+rectangle.getSize().x>app.getSize().x) {     //rectangle

                    if (pcount>0) {
                        ch1.setFillColor(rectangle.getFillColor());
                        ch2.setFillColor(rectangle.getFillColor());
                        ch3.setFillColor(rectangle.getFillColor());
                        ch4.setFillColor(rectangle.getFillColor());
                        chenter.setFillColor(rectangle.getFillColor());

                        if (inrect(ch1, event.mouseMove.x, event.mouseMove.y)) {                //ch1
                            ch1.setFillColor(Color(230, 230, 220));
                        } else if (inrect(ch2, event.mouseMove.x, event.mouseMove.y)) {         //ch2
                            ch2.setFillColor(Color(230, 230, 220));
                        } else if (inrect(chenter, event.mouseMove.x, event.mouseMove.y)) {     //chenter
                            chenter.setFillColor(Color(230, 230, 220));
                        } else if (inrect(ch3, event.mouseMove.x, event.mouseMove.y)) {         //ch3
                            ch3.setFillColor(Color(230, 230, 220));
                        } else if (inrect(ch4, event.mouseMove.x, event.mouseMove.y)) {         //ch4
                            ch4.setFillColor(Color(230, 230, 220));
                        }
                    }

                } else {                                                    //board
                    ch1.setFillColor(rectangle.getFillColor());
                    ch2.setFillColor(rectangle.getFillColor());
                    ch3.setFillColor(rectangle.getFillColor());
                    ch4.setFillColor(rectangle.getFillColor());
                    chenter.setFillColor(rectangle.getFillColor());
                    add.setScale(1, 1);
                    sub.setScale(1, 1);
                    help.setScale(1, 1);
                    stn.setScale(1, 1);
                    int thechosen=catchedpoint;
                    if (thechosen<0){
                        for (unsigned int i=0;i<vp.size();i++) {
                            vp[i].circle->setScale(1, 1);
                            if (vp[i].circle->getPosition().x-10<event.mouseMove.x &&
                                vp[i].circle->getPosition().y-10<event.mouseMove.y &&
                                vp[i].circle->getPosition().x+14>event.mouseMove.x &&
                                vp[i].circle->getPosition().y+14>event.mouseMove.y) {
                                thechosen=i;
                            }
                        }
                    }
                    if (thechosen>=0) {                                            //resize near/catched point
                        vp[thechosen].circle->setScale(2, 2);
                    }

                    if (catchedpoint>=0) {                                          //change position of catched point
                        msetpp(catchedpoint, event.mouseMove.x, event.mouseMove.y);
                    }

                    if (catched) {                                                  //change center of catched board
                        centerx=(-event.mouseMove.x+catchx)*scale;
                        centery=(event.mouseMove.y-catchy)*scale;
                        for (unsigned int i=0;i<vp.size();i++) {
                            vp[i].dpl();
                        }
                        upva();
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed ) {             //click
                if ( event.mouseButton.button == Mouse::Left ) {            //Left-click
                    if (event.mouseButton.x<rectangle2.getSize().x) {            //rectangle2
                        if (event.mouseButton.y<40) {                               //"+"
                            addpoint();
                        } else if (event.mouseButton.y<80) {                        //"-"
                            removepoint();
                        } else if (event.mouseButton.y>app.getSize().y-40) {        // "?"

                        } else if (event.mouseMove.y>app.getSize().y-80) {          // "..."

                        }
                    }
                    else if (event.mouseButton.x+rectangle.getSize().x>app.getSize().x) {   //rectangle
                        if (pcount>0) {

                            if (inrect(ch1, event.mouseButton.x, event.mouseButton.y)) {            //ch1
                                bacti(1);
                            } else if (inrect(ch2, event.mouseButton.x, event.mouseButton.y)) {     //ch2
                                bacti(2);
                            } else if (inrect(ch3, event.mouseButton.x, event.mouseButton.y)) {     //ch2
                                if ( (chg!=2 && chg>0 && pcount==2) || pcount==3) {
                                    bacti(3);
                                    ppss();
                                }
                            } else if (inrect(ch4, event.mouseButton.x, event.mouseButton.y)) {     //ch2
                                if (chg!=2 && chg>0 && pcount==2) {
                                    bacti(4);
                                    ppss();
                                }
                            } else if (inrect(chenter, event.mouseButton.x, event.mouseButton.y)) { //chenter
                                if (gettin) endtyping();
                            }

                        }
                    } else {                                                    //board
                        for (unsigned int i=0;i<vp.size();i++) {                    //catch point
                            if (vp[i].circle->getPosition().x-10<event.mouseButton.x && vp[i].circle->getPosition().y-10<event.mouseButton.y &&
                                vp[i].circle->getPosition().x+14>event.mouseButton.x && vp[i].circle->getPosition().y+14>event.mouseButton.y) {
                                catchedpoint=i;
                            }
                        }
                        if (catchedpoint<0) {                                      //if catched board
                            catched=true;
                            catchx=event.mouseButton.x+centerx/scale;
                            catchy=event.mouseButton.y-centery/scale;
                        }
                    }
                }
                if ( event.mouseButton.button == Mouse::Right ) {           //Right-click
                     if (event.mouseButton.x<rectangle2.getSize().x) {           //rectangle2
                        if (event.mouseButton.y<40) {                               //"+"

                        } else if (event.mouseMove.y<80) {                          //"-"

                        }
                    }
                    else if (event.mouseButton.x+rectangle.getSize().x>app.getSize().x) {   //rectangle

                    } else {                                                    //board
                        int thechosen=-1;
                        for (unsigned int i=0;i<vp.size();i++) {
                            if (vp[i].circle->getPosition().x-10<event.mouseButton.x && vp[i].circle->getPosition().y-10<event.mouseButton.y &&
                                vp[i].circle->getPosition().x+14>event.mouseButton.x && vp[i].circle->getPosition().y+14>event.mouseButton.y) {
                                thechosen=i;
                            }
                        }
                        if (thechosen>=0) {                                         //point
                            if (thechosen+'A'==bp[0] || thechosen+'A'==bp[1] ||
                                thechosen+'A'==bp[2]) {                                 //deselect point
                                deselectpoint(thechosen);
                            }
                            else if (pcount<3) {                                        //select point
                                selectpoint(thechosen);
                            }
                        }
                    }
                }

            }

            if (event.type==Event::MouseWheelMoved) {                   //wheel
                if ( Mouse::getPosition(app).x>rectangle2.getSize().x &&    //board
                     Mouse::getPosition(app).x<rectangle.getPosition().x) {

                    if (event.mouseWheel.delta==1 && scalestep>0) scalestep--;
                    if (event.mouseWheel.delta==-1 && scalestep<maxstep-1) scalestep++;

                    scale=scalesteps[scalestep];

                    for (unsigned int i=0;i<vp.size();i++) {
                        vp[i].dpl();
                    }
                    upva();
                    if (catchedpoint==bp[2]-'A' && pcount==3 && chg==3) {
                        double therad=sqrt(pow(vp[ bp[1]-'A' ].circle->getPosition().x-vp[ bp[2]-'A' ].circle->getPosition().x, 2)+
                                           pow(vp[ bp[1]-'A' ].circle->getPosition().y-vp[ bp[2]-'A' ].circle->getPosition().y, 2));
                        csh.setRadius(therad);
                        csh.setOrigin(therad, therad);
                    }
                    if (catchedpoint==bp[1]-'A' && pcount==3 && chg==2) {
                        double therad=sqrt(pow(vp[ bp[0]-'A' ].circle->getPosition().x-vp[ bp[1]-'A' ].circle->getPosition().x, 2)+
                                           pow(vp[ bp[0]-'A' ].circle->getPosition().y-vp[ bp[1]-'A' ].circle->getPosition().y, 2));
                        csh.setRadius(therad);
                        csh.setOrigin(therad, therad);
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased ) {            //release
                if (event.mouseButton.button==Mouse::Left) {
                    if (catchedpoint>=0) catchedpoint=-1;
                    if (catched==true) catched=false;
                }
            }
            if (event.type == Event::KeyPressed ) {                     //key press
                if (gettin==false) {
                    if (event.key.code>=0 && event.key.code<vp.size()) {        //select point A-Z
                        if (event.key.code+'A'!=bp[0] &&
                            event.key.code+'A'!=bp[1] && pcount<3)
                            selectpoint(event.key.code);
                    } else if (event.key.code==59) {                            //deselect last point backspace
                        if (pcount>0)
                            deselectpoint( bp[pcount-1]-'A' );
                    } else if (event.key.code==55) {                               //byc "="
                            byc=!byc;
                    }
                } else {                                                    //typing number
                    if (event.key.code==58) {                                   //enter
                        endtyping();
                    }
                    const unsigned int ml=12; //max length
                    if ( (event.key.code>=26 && event.key.code<=35 &&           //numbers etc.
                          getn.length()<ml) || ((event.key.code==49 || event.key.code==50)
                          && getn.length()<ml-1 && getn.length()>0) || event.key.code==59 ||
                          ( (event.key.code==68 || event.key.code==56) && getn.length()==0) )  {

                        if (event.key.code==68 || event.key.code==56) {
                            getn="-";
                        } else if (event.key.code==49 || event.key.code==50) {
                            bool pw=false;
                            for (int i=0;i<getn.length();i++) {
                                if (getn[i]=='.') {
                                    pw=true;
                                    break;
                                }
                            }
                            if (!pw)
                                getn=getn+".";
                        }
                        else if (event.key.code==59) {
                            if (getn.length()>0)getn.erase(getn.length()-1);
                        }
                        else getn.push_back(event.key.code-26+'0');

                        if (pcount==1)
                            nin.setString(vp[bp[0]-'A'].nm.getString()+"'"+ (chg==1 ? "x" : "y") + "= "+getn);
                        else if (pcount==2) {
                            if (chg==2)
                                nin.setString("|"+vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+"|= "+getn);
                            else nin.setString(vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+
                                                (chg==3 ? "x" : "y")+"= "+getn );
                        } else if (pcount==3) {
                            if (chg<3)
                                nin.setString("|"+vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+"'"+
                                                vp[bp[2]-'A'].nm.getString() + "|="+getn+"°" );
                            else if (chg==3)
                                nin.setString("|"+vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+
                                                vp[bp[2]-'A'].nm.getString() + "'|="+getn+"°" );
                        }

                    }

                }
            }
            if (event.type == Event::Resized) {                     //resize
                FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                app.setView(View(visibleArea));
                rectangle.setPosition(event.size.width-rectangle.getSize().x, 0);
                rectangle.setSize(Vector2f(rectangle.getSize().x, event.size.height));
                rectangle2.setSize(Vector2f(45, event.size.height));
                add.setPosition(22, 20);
                sub.setPosition(22, 20+40);
                help.setPosition(22, app.getSize().y-60);
                stn.setPosition(22, app.getSize().y-20);
                for (unsigned int i=0;i<vp.size();i++) {
                    vp[i].dpl();
                }
                upva();
                bpt.setPosition(app.getSize().x-bpt.getLocalBounds().width/2-rectangle.getSize().x/2, 10);
                posxys.setPosition(rectangle2.getSize().x+5, app.getSize().y-20);
                pinfo.setPosition(rectangle.getPosition().x+10, 35);
                ppss();
            }
        }


        app.clear(Color::White);

        app.draw(cooax);
         if ((chg==2 || chg==3) && pcount==3) {
            app.draw(csh);
        } else if ( (pcount==1 && chg>0) || (pcount==2 && chg==2) ||
                   (pcount==3 && chg==1) ) {
            app.draw(lsh);
        }
        app.draw(cbp);
        for (unsigned int i=0;i<vp.size();i++) {
            app.draw(*vp[i].circle);
            app.draw(vp[i].nm);
        }
        app.draw(posxys);
        app.draw(rectangle);
        if (pcount>0) {
            app.draw(pinfo);
            app.draw(ch1);
            app.draw(ch2);
            app.draw(chin1);
            app.draw(chin2);
            if (chg>0 && chg!=2 && pcount==2) {
                app.draw(ch3);
                app.draw(ch4);
                app.draw(chin3);
                app.draw(chin4);
            }
            if (pcount==3) {
                app.draw(ch3);
                app.draw(chin3);
            }
            if (gettin) {
                app.draw(nin);
                app.draw(chenter);
                app.draw(chinenter);
            }

        }
        app.draw(bpt);
        app.draw(rectangle2);
        app.draw(add);
        app.draw(sub);
        app.draw(help);
        app.draw(stn);

        app.display();
    }


    return EXIT_SUCCESS;
}

/// --------------------------------------------------------------------------------------------------------------------------------------------

string dtos(double x) {                     //double to string
    ostringstream strs;
    strs << x;
    string str = strs.str();
    return str;
}

void upva() {                                   //board<- shapes etc.
    cbp[0].position=cbp[1].position=cbp[2].position=Vector2f(0, 0);
    if (pcount==2) {
            cbp.setPrimitiveType(sf::LinesStrip);
            cbp[0].color=Color(50, 50, 255, 255);
            cbp[1].color=Color(50, 50, 255, 255);
            cbp[2].color=Color(50, 50, 255, 255);
    }
    if (pcount==3) {
            cbp.setPrimitiveType(sf::Triangles);
            cbp[0].color=Color(50, 50, 255, 10);
            cbp[1].color=Color(50, 50, 255, 170);
            cbp[2].color=Color(50, 50, 255, 10);
    }
    for (unsigned int i=0;i<vp.size();i++) {
        if (bp[0]==vp[i].name) {
            if (pcount==2) cbp[0].position=cbp[2].position=vp[i].circle->getPosition();
            if (pcount==3) cbp[0].position=vp[i].circle->getPosition();
        }
        if (bp[1]==vp[i].name) {
            if (pcount==2) cbp[1].position=vp[i].circle->getPosition();
            if (pcount==3) cbp[1].position=vp[i].circle->getPosition();
        }
        if (bp[2]==vp[i].name && pcount==3) cbp[2].position=vp[i].circle->getPosition();
    }
    double xax=(app.getSize().x-rectangle.getSize().x+rectangle2.getSize().x)/2-centerx/scale,
           yax=app.getSize().y/2+centery/scale;
    cooax[0].position=Vector2f(xax, 0);
    cooax[1].position=Vector2f(xax, app.getSize().y);
    cooax[2].position=Vector2f(rectangle2.getSize().x, yax);
    cooax[3].position=Vector2f(app.getSize().x-rectangle.getSize().x, yax);

    if (scale<=1)   posxys.setString( "x"+dtos(1/scale)+" ("+dtos(centerx)+"; "+dtos(centery)+")" );
    else            posxys.setString( "x1/"+dtos(scale)+" ("+dtos(centerx)+"; "+dtos(centery)+")" );

    if (pcount==3 && chg==3) {
        csh.setPosition( vp[ bp[1]-'A' ].circle->getPosition() );

        if (catchedpoint!=bp[2]-'A') {
            double therad=sqrt(pow(vp[ bp[1]-'A' ].circle->getPosition().x-vp[ bp[2]-'A' ].circle->getPosition().x, 2)+
                               pow(vp[ bp[1]-'A' ].circle->getPosition().y-vp[ bp[2]-'A' ].circle->getPosition().y, 2));
            csh.setRadius(therad);
            csh.setOrigin(therad, therad);
        }
        vp[ bp[2]-'A' ].circle->setFillColor(Color(180,0,0));

    } else if (pcount==3 && chg==2) {
        csh.setPosition( vp[ bp[0]-'A' ].circle->getPosition() );

        if (catchedpoint!=bp[1]-'A') {
            double therad=sqrt(pow(vp[ bp[0]-'A' ].circle->getPosition().x-vp[ bp[1]-'A' ].circle->getPosition().x, 2)+
                               pow(vp[ bp[0]-'A' ].circle->getPosition().y-vp[ bp[1]-'A' ].circle->getPosition().y, 2));
            csh.setRadius(therad);
            csh.setOrigin(therad, therad);
        }
        vp[ bp[1]-'A' ].circle->setFillColor(Color(180,0,0));

    } else if (( (pcount==3 && chg==1) || (pcount==2 && chg==2) || (pcount==1 && chg>0))  &&
               !((pcount==1 && catchedpoint+'A'==bp[0] && chg>0) || (pcount==2 && chg==2 && catchedpoint+'A'==bp[1]) ||
                (pcount==3 && catchedpoint+'A'==bp[1] && chg==1)) ) {

        double x1=vp[ bp[0]-'A' ].circle->getPosition().x, x2;
        double y1=vp[ bp[0]-'A' ].circle->getPosition().y, y2;
        if (pcount==1) {
            if (chg==1) {
                x2=x1+1;
                y2=y1;
            } else {
                x2=x1;
                y2=y1+1;
            }
        } else {
            x2=vp[ bp[1]-'A' ].circle->getPosition().x;
            y2=vp[ bp[1]-'A' ].circle->getPosition().y;
        }
        if (x1==x2) {
            lsh[0].position=Vector2f(x1, app.getSize().y);
            lsh[1].position=Vector2f(x2, 0);
            line1=1;
            line2=0;
            line3=-x1;
        } else if (y1==y2) {
            lsh[0].position=Vector2f(0, y1);
            lsh[1].position=Vector2f(app.getSize().x, y2);
            line1=0;
            line2=1;
            line3=-y1;
        } else {
            double a=(y1-y2)/(x1-x2), b=(x1*y2-x2*y1)/(x1-x2);
            line1=-a;
            line2=1;
            line3=-b;
            if (-b/a<=app.getSize().x && -b/a>=0) {
                    lsh[0].position=Vector2f(-b/a, 0);
            } else {
                lsh[0].position=Vector2f( app.getSize().x, app.getSize().x*a+b );
            }
            if (b<=app.getSize().y && b>=0) {
                lsh[1].position=Vector2f(0, b);
            } else {
                lsh[1].position=Vector2f( (app.getSize().y-b)/a, app.getSize().y);
            }
        }

        if (pcount==1) vp[ bp[0]-'A' ].circle->setFillColor(Color(180,0,0));
        else vp[ bp[1]-'A' ].circle->setFillColor(Color(180,0,0));
    }
}

void addpoint() {                               //"+"
    if (vp.size()<='Z'-'A') {
        CircleShape* cs=new CircleShape(circle);
        vp.push_back( Pt(centerx, centery, 'A'+vp.size(), cs) );
    }
}

void removepoint() {                            //"-"
    if (vp.size()>0) {
        for (int i=0;i<3;i++) {
            if (vp[vp.size()-1].name==bp[i]) {
                deselectpoint(vp.size()-1);
                break;
            }
        }
        if (vp.size()>0) {
            delete vp[vp.size()-1].circle;
            vp.pop_back();
        }
    }
}

string ppssp(int p) {
    string str;
    str=vp[p].nm.getString()+"("+dtos(vp[p].p.x)+"; "+dtos(vp[p].p.y)+")";
    pinfocheck.setString(str);
    if (pinfocheck.getGlobalBounds().width>rectangle.getSize().x-10)
        str=vp[p].nm.getString()+"("+dtos(vp[p].p.x)+";\n\t"+dtos(vp[p].p.y)+")";
    return str;
}
void ppss() {
    if (pcount>0) {
        string pi="", str;
        int a=bp[0]-'A';
        pi=ppssp(a);
        if (pcount>1) {
            int b=bp[1]-'A';
            pi=pi+"\n"+ppssp(b);
            if (pcount==2) {
                str=vp[a].nm.getString()+vp[b].nm.getString()+"=["+dtos(vp[b].p.x-vp[a].p.x)+"; "+dtos(vp[b].p.y-vp[a].p.y)+"]";
                pinfocheck.setString(str);
                if (pinfocheck.getGlobalBounds().width>rectangle.getSize().x-10)
                    str=vp[a].nm.getString()+vp[b].nm.getString()+"=["+dtos(vp[b].p.x-vp[a].p.x)+";\n\t\t"+dtos(vp[b].p.y-vp[a].p.y)+"]";

                pi=pi+"\n\n"+str+"\n\n|"+vp[a].nm.getString()+vp[b].nm.getString()+"|="+dtos(vp[a].p.getDistance(vp[b].p));
            }
            if (pcount>2) {
                int c=bp[2]-'A';
                pi=pi+"\n"+ppssp(c)+"\n\nA="+dtos(vp[b].p.getArea(vp[a].p, vp[c].p))+"\n\n|"+vp[a].nm.getString()+
                    vp[b].nm.getString()+vp[c].nm.getString()+"|="+dtos(vp[b].p.getAngle(vp[a].p, vp[c].p))+"°";
            }
        }
        pinfo.setString(pi);

        if (pcount==1) {
                pinfo.setString(pi+"\n\n\t\t\tSet "+vp[bp[0]-'A'].nm.getString()+":");
                chin1.setString("x");
                chin2.setString("y");
        } else if (pcount==2) {
                pinfo.setString(pi+"\n\n\t\t\t   Set:");
                chin1.setString(vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+"'");
                chin2.setString("|"+chin1.getString()+"|");
                chin3.setString("x");
                chin4.setString("y");
        } else if (pcount==3) {
                pinfo.setString(pi+"\n\n\t\t Set |"+vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+
                                vp[bp[2]-'A'].nm.getString()+"|:");
                chin1.setString(vp[bp[1]-'A'].nm.getString()+"' in "+vp[bp[0]-'A'].nm.getString()+
                                vp[bp[1]-'A'].nm.getString());
                chin2.setString("|"+vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+"'|=|"+
                                    vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+"|");
                chin3.setString("|"+vp[bp[1]-'A'].nm.getString()+vp[bp[2]-'A'].nm.getString()+"'|=|"+
                                    vp[bp[1]-'A'].nm.getString()+vp[bp[2]-'A'].nm.getString()+"|");
        }

        ch1.setPosition(rectangle.getPosition().x+1, pinfo.getGlobalBounds().height+pinfo.getPosition().y+15);
        ch2.setPosition(rectangle.getSize().x/2+rectangle.getPosition().x, ch1.getPosition().y);
        ch3.setPosition(ch1.getPosition().x, ch1.getPosition().y+ch1.getSize().y+1);
        ch4.setPosition(ch2.getPosition().x, ch2.getPosition().y+ch2.getSize().y+1);

        chin1.setPosition(ch1.getPosition().x+ch1.getSize().x/2-chin1.getGlobalBounds().width/2,
                              ch1.getPosition().y);
        chin2.setPosition(ch2.getPosition().x+ch2.getSize().x/2-chin2.getGlobalBounds().width/2,
                              ch2.getPosition().y);
        chin3.setPosition(ch3.getPosition().x+ch3.getSize().x/2-chin3.getGlobalBounds().width/2,
                              ch3.getPosition().y);
        chin4.setPosition(ch4.getPosition().x+ch4.getSize().x/2-chin4.getGlobalBounds().width/2,
                              ch4.getPosition().y);
        if (pcount==1 || (pcount==2 && chg<3))
            nin.setPosition(pinfo.getPosition().x, chin1.getPosition().y+nin.getGlobalBounds().height+15);
        else nin.setPosition(pinfo.getPosition().x, chin3.getPosition().y+nin.getGlobalBounds().height+15);

        chenter.setPosition(ch1.getPosition().x, nin.getPosition().y+nin.getGlobalBounds().height+15);
        chinenter.setPosition(rectangle.getSize().x/3+rectangle.getPosition().x+10, chenter.getPosition().y);

    }
}

void selectpoint(int i) {                                               //select point
    vp[i].circle->setFillColor(Color::Blue);
    bp[pcount]=vp[i].name;
    pcount++;

    upva();
    bpt.setString(bp);
    bpt.setPosition(app.getSize().x-bpt.getLocalBounds().width/2-rectangle.getSize().x/2, 10);

    gettin=false;
    setfocus(-1, gettin);
    ppss();
}
void deselectpoint(int i) {                                             //deselect point
    vp[i].circle->setFillColor(Color(50, 50, 50));
    pcount--;
    if (vp[i].name==bp[0]) {
        bp[0]=bp[1];
        bp[1]=bp[2];
    } else if (vp[i].name==bp[1]) {
        bp[1]=bp[2];
    }
    bp[2]=' ';
    upva();
    bpt.setString(bp);
    bpt.setPosition(app.getSize().x-bpt.getLocalBounds().width/2-rectangle.getSize().x/2, 10);

    gettin=false;
    setfocus(-1, gettin);
    ppss();
}

bool inrect(RectangleShape& r, double x, double y) {                    //if point in rect r
    if (r.getPosition().x<=x && r.getPosition().x+r.getSize().x>=x &&
        r.getPosition().y<=y && r.getPosition().y+r.getSize().y>=y)
        return true;
    return false;
}

void setfocus(int which, bool activate) {                               //set focus of ch which
    if (which<0) {
        ch1.setOutlineColor(Color(0, 0, 0, 64));
        ch2.setOutlineColor(Color(0, 0, 0, 64));
        ch3.setOutlineColor(Color(0, 0, 0, 64));
        ch4.setOutlineColor(Color(0, 0, 0, 64));
        chg=0;
    } else {
        if (which==1) ch1.setOutlineColor(Color(0, 0, 0, activate==true ? 255 : 64));
        else if (which==2) ch2.setOutlineColor(Color(0, 0, 0, activate==true ? 255 : 64));
        else if (which==3) ch3.setOutlineColor(Color(0, 0, 0, activate==true ? 255 : 64));
        else if (which==4) ch4.setOutlineColor(Color(0, 0, 0, activate==true ? 255 : 64));
    }
    if (pcount==1) {
        vp[ bp[0]-'A' ].circle->setFillColor(Color::Blue);
    } else if (pcount==2) {
        vp[ bp[1]-'A' ].circle->setFillColor(Color::Blue);
    } else if (pcount==3) {
        vp[ bp[1]-'A' ].circle->setFillColor(Color::Blue);
        vp[ bp[2]-'A' ].circle->setFillColor(Color::Blue);
    }
}

void endtyping() {
    gettin=false;
    if (getn.length()>0 && getn[getn.length()-1]=='.')
        getn.push_back('0');

    if (getn.length()>0) {
        if (pcount==1) {
            if (chg==1)
                vp[bp[0]-'A'].setpos( atof(getn.c_str()), vp[bp[0]-'A'].p.y );
            else if (chg==2)
                vp[bp[0]-'A'].setpos( vp[bp[0]-'A'].p.x, atof(getn.c_str()) );
        } else if (pcount==2) {
            if (chg==2)
                vp[bp[1]-'A'].p.setDistance(vp[bp[0]-'A'].p, atof(getn.c_str()));
            else if (chg==3)
                vp[bp[1]-'A'].p.x=atof(getn.c_str())+vp[bp[0]-'A'].p.x;
            else if (chg==4)
                vp[bp[1]-'A'].p.y=atof(getn.c_str())+vp[bp[0]-'A'].p.y;
        } else if (pcount==3) {
            if (chg==1)
                vp[bp[1]-'A'].p.setAngleL(vp[bp[0]-'A'].p, vp[bp[2]-'A'].p, atof(getn.c_str()));
            else if (chg==2)
                vp[bp[1]-'A'].p.setAngleC(vp[bp[0]-'A'].p, vp[bp[2]-'A'].p, atof(getn.c_str()));
            else if (chg==3)
                vp[bp[1]-'A'].p.setAngleS(vp[bp[0]-'A'].p, vp[bp[2]-'A'].p, atof(getn.c_str()));
        }


        for (unsigned int i=0;i<vp.size();i++) {
            vp[i].dpl();
        }
        upva();
        ppss();
    }

    if (chg>2 && pcount==2)
        setfocus(chg, false);
    else setfocus(-1, false);
}

void bacti(int i) {                                                     //action of buttons
    if (pcount==1 || pcount==3) {
        if (gettin && chg==i) {
            gettin=false;
            setfocus(-1, false);
        } else {
            gettin=true;
            getn="";
            if (pcount==1)
                nin.setString(vp[bp[0]-'A'].nm.getString()+"'"+ (i==1 ? "x" : "y") + "=  Type number..." );
            else if (pcount==3) {
                if (i<3)
                    nin.setString("|"+vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+"'"+
                              vp[bp[2]-'A'].nm.getString() + "|= Type number..." );
                else if (i==3)
                    nin.setString("|"+vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+
                                    vp[bp[2]-'A'].nm.getString() + "'|= Type number..." );
            }
            setfocus(-1, false);
            setfocus(i, true);
            chg=i;
        }
    } else if (pcount==2) {
        if ((gettin && chg==i && i<3) || (i==1 && (chg==1 || chg>2) )) {
            gettin=false;
            setfocus(-1, false);
        } else if (gettin && chg==i && i>2) {
            gettin=false;
            setfocus(3, false);
            setfocus(4, false);
        } else {
            if (i>1)
                gettin=true;
            else gettin=false;
            getn="";
            if (i==2)
                nin.setString("|"+vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+"|= Type number..." );
            else if (i>2) nin.setString(vp[bp[0]-'A'].nm.getString()+vp[bp[1]-'A'].nm.getString()+
                                        (i==3 ? "x" : "y")+"= Type number..." );
            if (i<3) {
                setfocus(-1, false);
                setfocus(i, true);
            } else {
                setfocus(3, (i==3 ? true : false));
                setfocus(4, (i==4 ? true : false));
            }
            chg=i;
        }
    }
    ppss();
    upva();
}

void msetpp(int cp, double x, double y) {
    if ( (pcount==3 && chg==2 && cp+'A'==bp[1])  ||
         (pcount==3 && chg==3 && cp+'A'==bp[2]) ) {
        double d=sqrt( pow((x-csh.getPosition().x), 2)+ pow( y-csh.getPosition().y , 2) );
        if (d!=0) {
            x=csh.getRadius()*(x-csh.getPosition().x)/d+csh.getPosition().x;
            y=csh.getRadius()*(y-csh.getPosition().y)/d+csh.getPosition().y;
            vp[cp].setpos(centerx+scale*(x-(app.getSize().x+rectangle2.getSize().x-rectangle.getSize().x)/2),
                          centery-scale*(y-(double)app.getSize().y/2) );
        }
    } else if ( (pcount==1 && cp+'A'==bp[0] && chg>0) || (pcount==2 && chg==2 && cp+'A'==bp[1]) ||
                (pcount==3 && cp+'A'==bp[1] && chg==1) ) {

        if (line1!=0 || line2!=0) {
            double k=(line1*x+line2*y+line3)/(pow(line1 , 2)+ pow(line2 , 2));
            x=x-line1*k;
            y=y-line2*k;
            vp[cp].setpos(centerx+scale*(x-(app.getSize().x+rectangle2.getSize().x-rectangle.getSize().x)/2),
                          centery-scale*(y-(double)app.getSize().y/2) );
        }
    } else {
        if (byc) {
            vp[cp].setpos( (long long int) (0.5+centerx+scale*(x-(app.getSize().x+rectangle2.getSize().x-rectangle.getSize().x)/2)),
                           (long long int) (0.5+centery-scale*(y-(double)app.getSize().y/2)) );
        } else
        vp[cp].setpos(centerx+scale*(x-(app.getSize().x+rectangle2.getSize().x-rectangle.getSize().x)/2),
                                centery-scale*(y-(double)app.getSize().y/2) );
    }

    upva();
    if ( cp+'A'==bp[0] || cp+'A'==bp[1] || cp+'A'==bp[2] ) {
        ppss();
    }
}

