#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <cmath>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <queue>

#define L 18
#define C 18

using namespace std;

ifstream fin("path.out");

///constante

const int width = 1520;
const int height = 800;
float speed=200;
int ZiduriLaRand=0;
bool isMusicPlaying=false;
bool sound=true;
int paritateMiscare = rand()%2;
int padding=1;
int marimeButon=100;
int ox=280,oy=250, vx=ox,vy=oy+200;
int P1Wins=0;
int P2Wins=0;
/// Initializari
bool primaMiscare=true;
int quit;
char m[L][C];
int i,j;
int x,y,nx,ny;
int byTudorAndBogdan=0;
int finish = 0;
int nrZiduri1 =10;
int nrZiduri2 = 10;
bool aFostConvertit=true;
int selection=3;
///Prototipuri
void Meniu();
void playStartAnimation();
void playAnimation();
void WaitForClickMeniu(int&,int&);
void selectarePatrat();
void creareTabla(char[L][C]);
void afisareMatriceDirectii(char[L][C]);
void copiereMatrice(char[L][C],char[L][C]);
void desenareMutariValide(char, int, int);
void WaitForOrientare(char[10]);
void ResetAtPlayAgain(char[L][C]);
void desenareButoaneOV(int);
void desenareMatrice(char[L][C]);
void desenareTablaDeJoc(char[L][C]);
void afisareMatriceLee(int[18][18]);
void verificareSusP1(char[L][C], char[L][C], int,int,bool&);
void verificareJosP1(char[L][C], char[L][C], int,int,bool&);
void verificareStangaP1(char[L][C], char[L][C], int,int,bool&);
void verificareDreaptaP1(char[L][C], char[L][C], int,int,bool&);
void verificareSusP2(char[L][C], char[L][C], int,int,bool&);
void verificareJosP2(char[L][C], char[L][C], int,int,bool&);
void verificareStangaP2(char[L][C], char[L][C], int,int,bool&);
void verificareDreaptaP2(char[L][C], char[L][C], int,int,bool&);
void afisareTablaJoc(char[L][C]);
void WaitForClick(int&, int&);
void ToString(int, char[3]);
void plasareZidBot(char m[L][C], int, int,int,int&);
void plasareZid(char m[L][C], int, int);
void play(char[1000]);
void Gameplay();
void SmartBot();
void Finish(int&, char[L][C]);
void DumbBot(int,int);
void FindPlayer2(char[L][C],int&, int&);
void FindPlayer1(char[L][C],int&, int&);
void mutarePion(char[L][C], int,int,char);
void getAndSortHighScores();
char selectarePatratBot(char[L][C]);
char getContinut(char[L][C],int, int);
int Can1Escape(char[L][C]);
int Can2Escape(char[L][C]);
int main();
char selectarePatratPVP(char[L][C],int, int);
bool verificareZiduriDreapta(char[L][C], int, int);
bool verificareZiduriStanga(char[L][C], int, int);
bool verificareZiduriJos(char[L][C], int, int);
bool verificareZiduriSus(char[L][C], int, int);
bool miscareValidaPion(char[L][C],int,int,int,int);
bool miscareValidaPionPtDesenare(char[L][C],int,int,int,int);
bool apartinInterval(int,int,int,int,int,int);



///---------------------LEE----------------------------

struct Highscores
{
    int player;
    int score;
} v[6];
int dx[]= {0,0,-2,2};
int dy[]= {-2,2,0,0};

bool inMat(int i, int j)
{
    return i>=1 && i<=17 && j>=1 && j<=17;
}
void Lee(char m[L][C], char p, int is, int js, int &minDistance)
{

    int lee[18][18];

    for(int i=1; i<=17; i++)
    {
        for(int j=1; j<=17; j++)
        {

            lee[i][j]=0;

        }
    }
    queue<pair<int,int>> Q;
    Q.push(make_pair(is,js));
    lee[is][js]=1;
    while(!Q.empty())
    {

        pair<int,int> P = Q.front();
        int x = P.first;
        int y = P.second;
        Q.pop();

        for(int i=0; i<4; i++)
        {

            int inou=dx[i]+x;
            int jnou=dy[i]+y;
            if(inMat(inou, jnou) && m[(x+inou)/2][(y+jnou)/2]=='1' && lee[inou][jnou]==0)
            {
                lee[inou][jnou] = lee[x][y]+1;
                Q.push(make_pair(inou,jnou));
            }

        }


    }

    ///Calculam dist minima de pe ultima linie;
    int index;
    if(p=='*')
    {
        for(int i=1; i<=17; i+=2)
        {
            if(lee[17][i]!=0)
            {
                index=i;
                i=18;
            }
        }
        minDistance=lee[17][index];
        for(int i=index+2; i<=17; i+=2)
        {
            if(lee[17][i]!=0)
                minDistance=min(minDistance, lee[17][i]);
        }
    }
    if(p=='#')
    {
        for(int i=1; i<=17; i+=2)
        {
            if(lee[1][i]!=0)
            {
                index=i;
                i=18;
            }
        }
        minDistance=lee[1][index];
        for(int i=index+2; i<=17; i+=2)
        {
            if(lee[1][i]!=0)
                minDistance=min(minDistance, lee[1][i]);
        }
    }

}

void afisareMatriceLee(int lee[18][18])
{
    system("cls");
    for(int i=1; i<=17 ; i++)
    {
        for(int j=1; j<=17 ; j++)
        {
            cout<<lee[i][j]<<" ";

        }
        cout<<endl;
    }
}

int LeePlayer(int paritate)
{

    int xp1,yp1,xp2,yp2;
    FindPlayer1(m,xp1,yp1);
    FindPlayer2(m,xp2,yp2);
    if(paritate==1)
    {
        int d;
        Lee(m,'#',xp2,yp2,d);

    }
    else
    {
        int d;
        Lee(m,'*',xp1,yp1,d);
    }
}




///----------------------------------------------------






///-----------------------BOT--------------------------

char selectarePatratCuBot(char m[L][C])
{
    //desenareTablaDeJoc(m);
    if(!(paritateMiscare%2))
    {
        desenareTablaDeJoc(m);
        int x,y;
        WaitForClick(y,x);
        if(!aFostConvertit)
        {
            if(apartinInterval(y,x,1400,20,1500,120))
            {
                if(sound==true)
                {


                    sound=false;
                    readimagefile("soundoff.jpg", 1400,20,1500, 120);
                }
                else if(sound==false)
                {


                    sound=true;
                    readimagefile("soundoff.jpg", 1400,20,1500, 120);
                }
                selectarePatrat();
            }
            else if(apartinInterval(y,x,20,20,120,120))
            {
                int sure=0,x,y;
                readimagefile("areyousure.jpg", width/2-732/2,height/2-500/2,width/2+732/2,height/2+500/2);
                while(sure==0)
                {
                    WaitForClickMeniu(x,y);

                    if(apartinInterval(x,y,454,481,633,590))
                    {
                        system("cls");
                        cout<<x<<" "<<y;
                        Meniu();
                        sure=1;
                    }
                    if(apartinInterval(x,y,890,481,1069,590))
                    {
                        system("cls");
                        cout<<x<<" "<<y;
                        sure=1;
                        desenareTablaDeJoc(m);
                    }

                }
            }
            else if(apartinInterval(y,x,180,350,280,450))
                {
                    if(paritateMiscare%2)
                    {
                        finish=1;
                        Finish(finish,m);
                    }
                    else
                    {
                        finish=2;
                        Finish(finish,m);
                    }
                }
            else selectarePatrat();
        }
        else
        {


            char continut = getContinut(m, x, y);
            if(continut=='*')
            {
                play("select.wav");
                desenareMutariValide('*',x,y);
            }
            if(continut=='*')
            {
                mutarePion(m, x, y, '*');


            }
            else if(continut=='1' && !(x%2) && !(y%2))
            {
                play("select.wav");
                if(nrZiduri1!=0)
                {
                    plasareZid(m, x, y);

                }
                else if(nrZiduri1<=0)
                {
                    selectarePatrat();
                }
            }
            else
            {
                desenareMatrice(m);
                play("eroare_selectie.wav");
                selectarePatrat();
            }


        }
    }
    else if(paritateMiscare%2)
    {
        if(selection==2)
        {


            int botx, boty;
            FindPlayer1(m,botx,boty);
            DumbBot(botx,boty);
        }
        else if (selection==3)
        {
            SmartBot();
        }

    }

}



void plasareZidBot(char m[L][C],int x,int y, int o, int &plasat)
{
    //desenareTablaDeJoc(m);

    char orientare[10];
    char copie[L][C];
    copiereMatrice(m, copie);

    if(o==0)
    {
        strcpy(orientare, "vertical");
    }
    else if(o==1)
    {
        strcpy(orientare, "orizontal");
    }




    if(strcmp(orientare, "vertical")==0)
    {
        if(copie[x-1][y] == '1' && copie[x+1][y] == '1' && copie[x][y] != '^'&& copie[x][y] != '>')
        {
            copie[x-1][y] = '|';
            copie[x][y] = '|';
            copie[x+1][y] = '|';
        }
        else
        {
            return;
        }
        if(Can1Escape(copie)&&Can2Escape(copie))
        {

            if(m[x-1][y] == '1' && m[x+1][y] == '1')
            {

                nrZiduri2--;
                setfillstyle(SOLID_FILL, WHITE);
                setcolor(WHITE);
                int xPtDesen = y/2*80+400;
                int yPtDesen = x/2*80+40;
                fillellipse(xPtDesen,yPtDesen,10,10);
                delay(400);
                play("zid.wav");
                m[x-1][y] = '|';
                m[x][y] = '^';
                m[x+1][y] = '|';
                desenareTablaDeJoc(m);
                plasat=1;
            }

        }
        else
        {
            return;
        }
    }
    else if(strcmp(orientare,"orizontal")==0)
    {

        if(copie[x-1][y] == '1' && copie[x+1][y] == '1' && copie[x][y] != '^'&& copie[x][y] != '>')
        {
            copie[x][y-1] = '-';
            copie[x][y] = '-';
            copie[x][y+1] = '-';
        }
        else
        {

            return;


        }
        if(Can1Escape(copie)&&Can2Escape(copie)&&plasat==0)
        {


            if(m[x][y-1] == '1' && m[x][y+1] == '1')
            {

                nrZiduri2--;
                setfillstyle(SOLID_FILL, WHITE);
                setcolor(WHITE);
                int xPtDesen = y/2*80+400;
                int yPtDesen = x/2*80+40;
                fillellipse(xPtDesen,yPtDesen,10,10);
                delay(400);
                play("zid.wav");
                m[x][y-1] = '-';
                m[x][y] = '>';
                m[x][y+1] = '-';
                desenareTablaDeJoc(m);
                plasat=1;


            }
        }
        else
        {
            return;

        }
    }



}

void plasareZidBotDoarVerificare(char m[L][C],int x,int y, int o, int &plasat)
{
    //desenareTablaDeJoc(m);

    char orientare[10];
    char copie[L][C];
    copiereMatrice(m, copie);

    if(o==0)
    {
        strcpy(orientare, "vertical");
    }
    else if(o==1)
    {
        strcpy(orientare, "orizontal");
    }




    if(strcmp(orientare, "vertical")==0)
    {
        if(copie[x-1][y] == '1' && copie[x+1][y] == '1' && copie[x][y] != '^'&& copie[x][y] != '>')
        {
            copie[x-1][y] = '|';
            copie[x][y] = '|';
            copie[x+1][y] = '|';
        }
        else
        {
            return;
        }
        if(Can1Escape(copie)&&Can2Escape(copie))
        {

            if(m[x-1][y] == '1' && m[x+1][y] == '1')
            {
                m[x-1][y] = '|';
                m[x][y] = '^';
                m[x+1][y] = '|';
                plasat=1;

            }

        }
        else
        {
            return;
        }
    }
    else if(strcmp(orientare,"orizontal")==0)
    {

        if(copie[x-1][y] == '1' && copie[x+1][y] == '1' && copie[x][y] != '^'&& copie[x][y] != '>')
        {
            copie[x][y-1] = '-';
            copie[x][y] = '-';
            copie[x][y+1] = '-';
        }
        else
        {

            return;


        }
        if(Can1Escape(copie)&&Can2Escape(copie)&&plasat==0)
        {


            if(m[x][y-1] == '1' && m[x][y+1] == '1')
            {
                m[x][y-1] = '-';
                m[x][y] = '>';
                m[x][y+1] = '-';
                plasat=1;

            }
        }
        else
        {
            return;

        }
    }



}

void plasareZid(char m[L][C],int x,int y)
{
    //desenareTablaDeJoc(m);
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(WHITE);
    int xPtDesen = y/2*80+400;
    int yPtDesen = x/2*80+40;
    fillellipse(xPtDesen,yPtDesen,10,10);
    desenareButoaneOV(100);
    char orientare[10];
    char copie[L][C];
    copiereMatrice(m, copie);

    if(aFostConvertit==true)
    {

        WaitForOrientare(orientare);
    }




    if(strcmp(orientare, "vertical")==0)
    {
        if(copie[x-1][y] == '1' && copie[x+1][y] == '1')
        {
            copie[x-1][y] = '|';
            copie[x][y] = '|';
            copie[x+1][y] = '|';
        }
        else
        {


            desenareButoaneOV(200);
            desenareMatrice(m);
            int i,j;
            selectarePatrat();
        }
        if(Can1Escape(copie)&&Can2Escape(copie))
        {

            if(m[x-1][y] == '1' && m[x+1][y] == '1')
            {
                if(paritateMiscare%2==0)
                {
                    nrZiduri1--;
                    paritateMiscare++;
                }
                else
                {
                    nrZiduri2--;
                    paritateMiscare++;
                }
                play("zid.wav");
                m[x-1][y] = '|';
                m[x][y] = '^';
                m[x+1][y] = '|';
            }

        }
        else
        {
            play("ingradit.wav");


            int i,j;
            desenareButoaneOV(200);
            desenareMatrice(m);
            selectarePatrat();
        }
    }
    else if(strcmp(orientare,"orizontal")==0)
    {

        if(copie[x][y-1] == '1' && copie[x][y+1] == '1')
        {
            copie[x][y-1] = '-';
            copie[x][y] = '-';
            copie[x][y+1] = '-';
        }
        else
        {


            int i,j;
            desenareButoaneOV(200);
            desenareMatrice(m);
            selectarePatrat();
        }
        if(Can1Escape(copie)&&Can2Escape(copie))
        {


            if(m[x][y-1] == '1' && m[x][y+1] == '1')
            {
                if(paritateMiscare%2==0)
                {
                    nrZiduri1--;
                    paritateMiscare++;
                }
                else
                {
                    nrZiduri2--;
                    paritateMiscare++;
                }
                play("zid.wav");
                m[x][y-1] = '-';
                m[x][y] = '>';
                m[x][y+1] = '-';
                int plasareX, plasareY;


            }
        }
        else
        {
            play("ingradit.wav");

            int i,j;
            desenareButoaneOV(200);
            desenareMatrice(m);
            selectarePatrat();

        }
    }
    else if(strcmp(orientare,"razgandit")==0)
    {
        play("razgandit.wav");
        setfillstyle(SOLID_FILL, RGB(32,32,32));
        setcolor(RGB(64,64,64));
        int xPtDesen = y/2*80+400;
        int yPtDesen = x/2*80+40;
        fillellipse(xPtDesen,yPtDesen,10,10);
        desenareButoaneOV(200);
        selectarePatrat();
    }


}

void DumbBot(int botx, int boty)
{
    int k=rand()%2;
    int plasat=0;
    int moveOrPlace =rand()%2;
    bool hasMoved=false;
    if(k==1)
        SmartBot();
    else
        while(hasMoved==false && paritateMiscare%2==1)
        {
            if(moveOrPlace==1 && nrZiduri2!=0  && hasMoved==false)   ///Plasare zid daca moveOrPlace=1 si are ziduri
            {
                int wallX = 0;
                int wallY = 0;
                for(int i=1; i<=200; i++) //ii dam 200 de incercari sa puna un zid
                {
                    wallX=2+2*(rand()%8);
                    wallY=2+2*(rand()%8);
                    int o=rand()%2;

                    plasareZidBot(m,wallX,wallY,o,plasat);
                    if(plasat)
                    {
                        paritateMiscare++;
                        i=201;
                        hasMoved=true;
                    }
                }
                if(plasat)
                {
                    selectarePatrat();

                }
                else moveOrPlace=0; ///mutare pion daca nu a reusit
            }
            if((moveOrPlace==0 && hasMoved==false) || nrZiduri2==0)   ///Mutare pion daca moveOrPlace=0
            {

                while(hasMoved == false)
                {
                    struct moves
                    {
                        int x, y;
                    } v[13];

                    v[1].x = botx+2;
                    v[1].y = boty;  //jos
                    v[2].x = botx-2;
                    v[2].y = boty;  //sus
                    v[3].x = botx  ;
                    v[3].y = boty-2;  //stanga
                    v[4].x = botx  ;
                    v[4].y = boty+2;  //dreapta
                    v[5].x = botx+4;
                    v[5].y = boty;  //jos peste player
                    v[6].x = botx-4;
                    v[6].y = boty;  //sus peste player
                    v[7].x = botx  ;
                    v[7].y = boty-4;  //stanga peste player
                    v[8].x = botx  ;
                    v[8].y = boty+4;  //dreapta peste player
                    v[9].x = botx+2;
                    v[9].y = boty+2;  //dreapta-jos
                    v[10].x = botx-2;
                    v[10].y = boty+2;  //stanga-jos
                    v[11].x = botx-2;
                    v[11].y = boty-2;  //stanga-sus
                    v[12].x = botx+2;
                    v[12].y = boty-2;  //dreapta-sus

                    int mutare = rand()%12 + 1;
                    if(miscareValidaPionPtDesenare(m,v[mutare].x, v[mutare].y, botx, boty))
                    {
                        desenareMutariValide('#',botx,boty);
                        delay(500);


                        play("mutare.wav");
                        swap(m[v[mutare].x][v[mutare].y], m[botx][boty]);
                        desenareTablaDeJoc(m);
                        if(v[mutare].x==1)
                        {
                            paritateMiscare-=1;
                            finish=2;
                            desenareTablaDeJoc(m);
                        }
                        paritateMiscare++;
                        hasMoved=true;
                        Finish(finish,m);
                    }
                }
                if(hasMoved==true)
                {

                    selectarePatrat();
                }
            }
        }

}
void SmartBot()
{
    /**
    *----Move smart and place smart----*

    1. Pentru fiecare mutare a robotului disponibila calculam distanta pana la final.
    2. Pentru fiecare mutare a playerului disponibila calculam distanta pana la final
    3. Verificam daca este mai avantajos sa mutam decat sa plasam un zid
       - Daca distanta minima a robotului in cazul unei mutari se mareste la plasarea unui zid, mutam robotul
       - Daca distanta minima a robotului in cazul unei mutari ramane la fel in cazul plasarii unui zid iar distanta minima
         a playerului se mareste, plasam acel zid
       - Daca distanta minima a playerului a fost marita cu 2  mutam robotul la urmatoarea miscare
    4. CAlculam unde putem opri avansarea unui pionmai tarziu

    **/

    int botx,x2,boty,y2;
    FindPlayer1(m,botx,boty);
    FindPlayer2(m,x2,y2);
    int distantaMinimaP1;
    int distantaMinimaP2;
    Lee(m,'#', botx, boty, distantaMinimaP1);
    Lee(m,'*', x2, y2, distantaMinimaP2);
    struct moves
    {
        int x, y;
    } v[13],miscariValideBot[6],s[13],miscariValidePlayer[6];
    ///toate miscarile posibile pt bot
    v[1].x = botx+2;
    v[1].y = boty;  //jos
    v[2].x = botx-2;
    v[2].y = boty;  //sus
    v[3].x = botx  ;
    v[3].y = boty-2;  //stanga
    v[4].x = botx  ;
    v[4].y = boty+2;  //dreapta
    v[5].x = botx+4;
    v[5].y = boty;  //jos peste player
    v[6].x = botx-4;
    v[6].y = boty;  //sus peste player
    v[7].x = botx  ;
    v[7].y = boty-4;  //stanga peste player
    v[8].x = botx  ;
    v[8].y = boty+4;  //dreapta peste player
    v[9].x = botx+2;
    v[9].y = boty+2;  //dreapta-jos
    v[10].x = botx-2;
    v[10].y = boty+2;  //stanga-jos
    v[11].x = botx-2;
    v[11].y = boty-2;  //stanga-sus
    v[12].x = botx+2;
    v[12].y = boty-2;  //dreapta-sus



    int k=1,g=1;
    for(int i=1; i<=12; i++)   ///STOCAM MISCARILE VALIDE PT BOT
    {
        if(miscareValidaPionPtDesenare(m,v[i].x, v[i].y, botx, boty))
        {
            miscariValideBot[k].x=v[i].x;
            miscariValideBot[k].y=v[i].y;
            k++;
        }
    }

    k--;

    int distanteMinimeBot[6]= {};

    for(int i=1; i<=k; i++)   ///calculam distantele minime din orice punct de plecare (BOT)
    {
        Lee(m,'#',miscariValideBot[i].x,miscariValideBot[i].y,distanteMinimeBot[i]);

    }

    int bestx=miscariValideBot[1].x, besty=miscariValideBot[1].y;
    int distMinBot=distanteMinimeBot[1];
    int distMinPlayer;
    Lee(m,'*',x2,y2,distMinPlayer);
    distMinPlayer--;

    for(int i=1; i<=k; i++)
    {


        if(distanteMinimeBot[i]<distMinBot)
        {

            bestx=miscariValideBot[i].x;
            besty=miscariValideBot[i].y;
            distMinBot=distanteMinimeBot[i];
        }

    }


    system("cls");
    cout<<bestx<<" "<<besty<<endl;
    if((abs(distMinPlayer-distMinBot)==1 && distMinPlayer>=4) || distMinBot-distMinPlayer<=-2)   ///Prioritate nr 1
    {





        ///---------------------

        ZiduriLaRand=0;
        desenareMutariValide('#',botx,boty);
        swap(m[botx][boty], m[bestx][besty]);
        paritateMiscare++;
        delay(500);
        play("mutare.wav");
        if(bestx==1)
        {
            finish=2;
        }
        desenareTablaDeJoc(m);
        Finish(finish, m);
        selectarePatrat();
    }
    else if((nrZiduri2!=0 && distMinPlayer<=distMinBot) || (nrZiduri2!=0 && nrZiduri1<=1) )   ///Incepem verificarea distantelor in momentul plasarii oricarui zid
    {


        int distMaxLenght=distMinPlayer, bestWallX, bestWallY,orientare,k;
        for(int i=2; i<=16; i+=2)
        {
            for(int j=2; j<=16; j+=2)
            {
                int minDistH=0,minDistV=0;
                int newBotDist=0;
                int plasat=0;

                char aux1[L][C];
                char aux2[L][C];
                copiereMatrice(m,aux1);
                copiereMatrice(m,aux2);
                ///Vom avea nevoie sa retinem cea mai mare distanta minima,coordonatele si orientarea
                plasareZidBotDoarVerificare(aux1, i,j,0,plasat);

                if(plasat)
                {
                    Lee(aux1, '*',x2,y2,minDistV);
                    minDistV--;
                    Lee(aux1, '#',botx,boty,newBotDist);
                    newBotDist--;
                    if(minDistV>distMaxLenght  && newBotDist<=distMinBot)
                    {
                        cout<<0;
                        distMaxLenght=minDistV;
                        bestWallX=i;
                        bestWallY=j;
                        orientare=0;
                    }
                }
                plasat=0;
                plasareZidBotDoarVerificare(aux2, i,j,1,plasat);
                if(plasat)
                {

                    Lee(aux2, '*',x2,y2,minDistH);
                    minDistH--;
                    Lee(aux2, '#',botx,boty,newBotDist);
                    newBotDist--;

                    if(minDistH>distMaxLenght  && newBotDist<=distMinBot)
                    {
                        cout<<1;
                        distMaxLenght=minDistH;
                        bestWallX=i;
                        bestWallY=j;
                        orientare=1;

                    }
                }

            }
        }

        if(distMaxLenght==distMinPlayer)
        {
            ZiduriLaRand=0;
            desenareMutariValide('#',botx,boty);
            swap(m[botx][boty], m[bestx][besty]);
            paritateMiscare++;
            delay(500);
            play("mutare.wav");
            if(bestx==1)
            {
                finish=2;
            }
            desenareTablaDeJoc(m);
            Finish(finish, m);
            selectarePatrat();
        }
        else if(ZiduriLaRand<2)
        {
            cout<<"gata";
            ZiduriLaRand++;
            k=0;
            plasareZidBot(m,bestWallX,bestWallY,orientare,k);
            paritateMiscare++;
            desenareTablaDeJoc(m);
            selectarePatrat();

        }
        else
        {
            ZiduriLaRand=0;
            desenareMutariValide('#',botx,boty);
            swap(m[botx][boty], m[bestx][besty]);
            paritateMiscare++;
            delay(500);
            play("mutare.wav");
            if(bestx==1)
            {
                finish=2;
            }
            desenareTablaDeJoc(m);
            Finish(finish, m);
            selectarePatrat();
        }
    }
    else
    {
        ZiduriLaRand=0;
        desenareMutariValide('#',botx,boty);
        swap(m[botx][boty], m[bestx][besty]);
        paritateMiscare++;
        delay(500);
        play("mutare.wav");
        if(bestx==1)
        {
            finish=2;
        }
        desenareTablaDeJoc(m);
        Finish(finish, m);
        selectarePatrat();
    }





    ///distantaMinimaP1 - ROBOT
    ///distantaMinimaP2 - OM









}

/// Functii de baza
void selectarePatrat()
{


    if(selection==1)
    {

        if(!primaMiscare)
        {
            int x,y;
            WaitForClick(y,x);
            cout<<aFostConvertit<<" "<<x<<" "<<y;
            if(aFostConvertit)
            {
                selectarePatratPVP(m,x,y);

            }
            else
            {
                if(apartinInterval(y,x,1400,20,1500,120))
                {


                    if(sound==true)
                    {


                        sound=false;
                        readimagefile("soundoff.jpg", 1400,20,1500, 120);
                    }
                    else if(sound==false)
                    {


                        sound=true;
                        readimagefile("soundoff.jpg", 1400,20,1500, 120);
                    }

                }
                else if(apartinInterval(y,x,20,20,120,120))
                {
                    int sure=0,x,y;
                    readimagefile("areyousure.jpg", width/2-732/2,height/2-500/2,width/2+732/2,height/2+500/2);
                    while(sure==0)
                    {
                        WaitForClickMeniu(x,y);

                        if(apartinInterval(x,y,454,481,633,590))
                        {
                            system("cls");
                            cout<<x<<" "<<y;
                            Meniu();
                            sure=1;
                        }
                        if(apartinInterval(x,y,890,481,1069,590))
                        {
                            system("cls");
                            cout<<x<<" "<<y;
                            sure=1;
                            desenareTablaDeJoc(m);
                        }

                    }
                }
                else if(apartinInterval(y,x,180,350,280,450))
                {
                    if(paritateMiscare%2)
                    {
                        finish=1;
                        Finish(finish,m);
                    }
                    else
                    {
                        finish=2;
                        Finish(finish,m);
                    }
                }
                else selectarePatrat();
            }
        }
        else
        {
            selectarePatratPVP(m,::x,::y);
        }

    }

    if(selection==2 || selection==3)
    {
        if(primaMiscare&&paritateMiscare%2==0)
        {
            primaMiscare=false;

        }
        selectarePatratCuBot(m);
    }
}

void AdaugareScorLa(int n)
{
    for(i=1; i<=5; i++)
    {
        if(v[i].player==n)
            v[i].score++;
    }
}
void Finish(int &finish, char m[L][C])
{

    if(finish!=0)
    {
        isMusicPlaying = true;

        char player[3];
        char whoWon[14];
        ToString(finish, player);
        strcpy(whoWon, "Player   won!");
        whoWon[7]=player[0];


        ///Player won TEXT
        if(finish==1)
            setbkcolor(RGB(255,100,100));
        else setbkcolor(RGB(100,100,255));

        if(selection==1)
        {
            if(finish==1)
            {
                P1Wins++;
                AdaugareScorLa(1);
            }
            else
            {
                P2Wins++;
                AdaugareScorLa(2);
            }

        }
        if(selection==2)
        {
            if(finish==1)
            {
                P1Wins++;
                AdaugareScorLa(3);
            }
            else
            {
                P2Wins++;
                AdaugareScorLa(4);
            }

        }
        if(selection==3)
        {
            if(finish==1)
            {
                P1Wins++;
                AdaugareScorLa(3);
            }
            else
            {
                P2Wins++;
                AdaugareScorLa(5);
            }
        }

        setcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, 0, 19);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(width/2,height/2-150, whoWon);
        if(sound)
            PlaySound("won.wav", NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
        FILE * pathout = fopen("\path.out","w");
        getAndSortHighScores();
        for(i=1; i<=5; i++)
        {
            fprintf(pathout,"%d",i);
            fprintf(pathout,"%s", " ");
            fprintf(pathout,"%d",v[i].player);
            fprintf(pathout,"%s"," ");
            fprintf(pathout,"%d",v[i].score);
            fprintf(pathout,"%s", "\n");
        }




        ResetAtPlayAgain(m);




    }
}

void ResetAtPlayAgain(char m[L][C])
{

    int playAgainx=width/2-250;
    int playAgainy=height/2-100;

    ///PLAY AGAIN BUTTON + TEXT
    setfillstyle(SOLID_FILL, RGB(100,200,100));
    setcolor(RGB(100,200,100));
    bar(playAgainx, playAgainy, playAgainx+500, playAgainy+200);
    setfillstyle(SOLID_FILL, RGB(150,200,150));
    bar(playAgainx+20, playAgainy+20, playAgainx+500-20, playAgainy+200-20);


    setbkcolor(RGB(150,200,150));
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, 0, 19);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(width/2,height/2+25, "PLAY AGAIN");



    int clicked=0;
    while(!clicked)
    {

        WaitForClick(ny,nx);
        if(apartinInterval(ny,nx,1400,20,1500,120))
        {
            if(sound==true)
            {
                sound=false;
                PlaySound(nullptr,nullptr,0);
                readimagefile("soundoff.jpg", 1400,20,1500, 120);
            }
            else if(sound==false)
            {
                sound=true;
                readimagefile("soundoff.jpg", 1400,20,1500, 120);
            }

        }
        else if(apartinInterval(ny,nx,20,20,120,120))
        {
            Meniu();


        }
        else if(ny>=playAgainx && ny<=playAgainx+500 && nx>=playAgainy && nx<=playAgainy+200)
        {

            playAnimation();
            cleardevice();
            finish=0;
            creareTabla(m);
            playStartAnimation();
            PlaySound(nullptr, nullptr, 0);
            desenareTablaDeJoc(m);
            nrZiduri1=10;
            nrZiduri2=10;
            paritateMiscare=rand()%2;
            if(selection!=1)
                paritateMiscare=0;
            primaMiscare=true;
            aFostConvertit=true;
            clicked=1;
            Gameplay();


        }
    }
}
void copiereMatrice(char m[L][C], char copie[L][C])
{
    for(int i=1; i<=17; i++)
    {
        for(int j=1; j<=17; j++)
        {
            copie[i][j]=m[i][j];
        }
    }

}

bool miscareValidaPion(char m[L][C], int x,int y,int plecareX,int plecareY)
{
    int distantaAbsolutaX= abs(x-plecareX);
    int distantaAbsolutaY= abs(y-plecareY);
    int distantaNulaX = x-plecareX;
    int distantaNulaY = y-plecareY;
    if(x<18 && y<18 && x>0 && y>0)
    {


        if((distantaAbsolutaX == 2 && distantaNulaY==0)||(distantaAbsolutaY == 2 && distantaNulaX==0))
        {
            if(m[(x+plecareX)/2][(y+plecareY)/2]=='1' && m[x][y]=='0')
            {
                paritateMiscare++;
                return true;
            }

        }
        else if((distantaAbsolutaX == 4 && distantaNulaY==0)||(distantaAbsolutaY == 4 && distantaNulaX==0))
        {
            if(m[(x+plecareX)/2][(y+plecareY)/2]=='*' || m[(x+plecareX)/2][(y+plecareY)/2]=='#')
            {
                if(y==plecareY)
                {
                    if(m[(x+plecareX)/2+1][y]=='1' &&  m[(x+plecareX)/2-1][y]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
                }
                else if (x==plecareX)
                {
                    if(m[x][(y+plecareY)/2+1]=='1' && m[x][(y+plecareY)/2-1]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
                }
            }
        }
        else if(distantaAbsolutaX == 2 && distantaAbsolutaY == 2)
        {
            if(x==plecareX-2 && y==plecareY+2)  //1
            {
                if(verificareZiduriDreapta(m, plecareX, plecareY))
                    if(m[plecareX-1][plecareY+2]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
                if(verificareZiduriSus(m, plecareX, plecareY))
                    if(m[plecareX-2][plecareY+1]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
            }
            if(x==plecareX+2 && y==plecareY+2)   //2
            {
                if(verificareZiduriDreapta(m, plecareX, plecareY))
                    if(m[plecareX+1][plecareY+2]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
                if(verificareZiduriJos(m, plecareX, plecareY))
                    if(m[plecareX+2][plecareY+1]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
            }
            if(x==plecareX+2 && y==plecareY-2)    //3
            {
                if(verificareZiduriJos(m, plecareX, plecareY))
                    if(m[plecareX+2][plecareY-1]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
                if(verificareZiduriStanga(m, plecareX, plecareY))
                    if(m[plecareX+1][plecareY-2]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
            }
            if(x==plecareX-2 && y==plecareY-2)     //4
            {

                if(verificareZiduriSus(m, plecareX, plecareY))
                    if(m[plecareX-2][plecareY-1]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
                if(verificareZiduriStanga(m, plecareX, plecareY))
                    if(m[plecareX-1][plecareY-2]=='1')
                    {
                        paritateMiscare++;
                        return true;
                    }
            }
        }

    }
    return false;

}



bool miscareValidaPionPtDesenare(char m[L][C], int x,int y,int plecareX,int plecareY)
{
    int distantaAbsolutaX= abs(x-plecareX);
    int distantaAbsolutaY= abs(y-plecareY);
    int distantaNulaX = x-plecareX;
    int distantaNulaY = y-plecareY;
    if(x<18 && y<18 && x>0 && y>0)
    {


        if((distantaAbsolutaX == 2 && distantaNulaY==0)||(distantaAbsolutaY == 2 && distantaNulaX==0))
        {
            if(m[(x+plecareX)/2][(y+plecareY)/2]=='1' && m[x][y]=='0')
            {

                return true;
            }

        }
        else if((distantaAbsolutaX == 4 && distantaNulaY==0)||(distantaAbsolutaY == 4 && distantaNulaX==0))
        {
            if(m[(x+plecareX)/2][(y+plecareY)/2]=='*' || m[(x+plecareX)/2][(y+plecareY)/2]=='#')
            {
                if(y==plecareY)
                {
                    if(m[(x+plecareX)/2+1][y]=='1' &&  m[(x+plecareX)/2-1][y]=='1')
                    {

                        return true;
                    }
                }
                else if (x==plecareX)
                {
                    if(m[x][(y+plecareY)/2+1]=='1' && m[x][(y+plecareY)/2-1]=='1')
                    {

                        return true;
                    }
                }
            }
        }
        else if(distantaAbsolutaX == 2 && distantaAbsolutaY == 2)
        {
            if(x==plecareX-2 && y==plecareY+2)  //1
            {
                if(verificareZiduriDreapta(m, plecareX, plecareY))
                    if(m[plecareX-1][plecareY+2]=='1')
                    {

                        return true;
                    }
                if(verificareZiduriSus(m, plecareX, plecareY))
                    if(m[plecareX-2][plecareY+1]=='1')
                    {

                        return true;
                    }
            }
            if(x==plecareX+2 && y==plecareY+2)   //2
            {
                if(verificareZiduriDreapta(m, plecareX, plecareY))
                    if(m[plecareX+1][plecareY+2]=='1')
                    {

                        return true;
                    }
                if(verificareZiduriJos(m, plecareX, plecareY))
                    if(m[plecareX+2][plecareY+1]=='1')
                    {

                        return true;
                    }
            }
            if(x==plecareX+2 && y==plecareY-2)    //3
            {
                if(verificareZiduriJos(m, plecareX, plecareY))
                    if(m[plecareX+2][plecareY-1]=='1')
                    {

                        return true;
                    }
                if(verificareZiduriStanga(m, plecareX, plecareY))
                    if(m[plecareX+1][plecareY-2]=='1')
                    {

                        return true;
                    }
            }
            if(x==plecareX-2 && y==plecareY-2)     //4
            {

                if(verificareZiduriSus(m, plecareX, plecareY))
                    if(m[plecareX-2][plecareY-1]=='1')
                    {

                        return true;
                    }
                if(verificareZiduriStanga(m, plecareX, plecareY))
                    if(m[plecareX-1][plecareY-2]=='1')
                    {

                        return true;
                    }
            }
        }

    }
    return false;

}




char getContinut(char m[L][C], int x, int y)
{
    return m[x][y];
}
void mutarePion(char m[L][C], int x, int y, char continut)
{
    int x1,y1;

    WaitForClick(y1,x1);

    if(miscareValidaPion(m, x1, y1, x, y))
    {
        play("mutare.wav");
        swap(m[x1][y1], m[x][y]);

        if(continut=='*' && x1==17)
        {
            paritateMiscare-=1;
            finish=1;
            desenareTablaDeJoc(m);
        }
        if(continut=='#' && x1==1)
        {
            paritateMiscare-=1;
            finish=2;
            desenareTablaDeJoc(m);
        }

    }
    else
    {
        play("razgandit.wav");

        desenareMatrice(m);
        selectarePatrat();
    }

}
char selectarePatratPVP(char m[L][C], int x, int y)
{

    char continut = getContinut(m, x, y);
    if(continut=='*' && paritateMiscare%2==0)
    {
        play("select.wav");
        desenareMutariValide('*',x,y);
    }
    if(continut=='#' && paritateMiscare%2==1)
    {
        play("select.wav");
        desenareMutariValide('#',x,y);
    }
    if(!(paritateMiscare%2))
    {

        if(continut=='*')
        {
            mutarePion(m, x, y, '*');

        }
        else if(continut=='1' && !(x%2) && !(y%2))
        {
            play("select.wav");
            if(nrZiduri1!=0)
            {
                plasareZid(m, x, y);

            }
            else if(nrZiduri1<=0)
            {


                int i,j;
                selectarePatrat();
            }
        }
        else
        {

            play("eroare_selectie.wav");

            selectarePatrat();
        }

    }
    else if(paritateMiscare%2)
    {

        if(continut=='#')
        {
            mutarePion(m,x,y,'#');

        }
        else if(continut=='1' && !(x%2) && !(y%2))
        {
            play("select.wav");
            if(nrZiduri2!=0)
            {
                plasareZid(m, x, y);

            }
            else if(nrZiduri2<=0)
            {


                selectarePatrat();
            }
        }
        else
        {
            play("eroare_selectie.wav");

            selectarePatrat();
        }
    }
}
void creareTabla(char m[L][C])
{
    for(int i=1; i<=17; i++)
    {
        for(int j=1; j<=17; j++)
        {
            if(i%2!=0)
            {
                if(j%2)
                {
                    m[i][j]='0';
                }
                else
                {
                    m[i][j]='1';
                }
            }
            else m[i][j]='1';
        }
    }
    m[1][9]='*';
    m[17][9]='#';
}
void eRandulLui()
{
    if(paritateMiscare%2)
        cout<<"E randul lui #.   Ziduri ramase: "<<nrZiduri2<<endl;
    else cout<<"E randul lui *.   Ziduri ramase: "<<nrZiduri1<<endl;
}


///Functii gasire a playerului

void FindPlayer1(char m[L][C], int &x, int &y)
{
    int i,j;
    for(i=1; i<=17; i++)
    {
        for(j=1; j<=17; j++)
        {
            if(m[i][j]=='#')
            {
                x=i;
                y=j;
                break;
            }
        }
    }
}
void FindPlayer2(char m[L][C], int &x, int &y)
{
    int i,j;
    for(i=1; i<=17; i++)
    {
        for(j=1; j<=17; j++)
        {
            if(m[i][j]=='*')
            {
                x=i;
                y=j;
                break;
            }
        }
    }
}



///Functii pentru verificare ziduri (regula de salt in stanga sau dreapta)

bool verificareZiduriDreapta(char m[L][C], int x, int y)
{
    if(m[x][y+3]!='1' && m[x][y+1] == '1' && m[x][y+2]!='0')
        return true;
    return false;
}
bool verificareZiduriSus(char m[L][C], int x, int y)
{
    if(m[x-3][y]!='1' && m[x-1][y] == '1' && m[x-2][y]!='0')
        return true;
    return false;
}
bool verificareZiduriJos(char m[L][C], int x, int y)
{
    if(m[x+3][y]!='1' && m[x+1][y] == '1' && m[x+2][y]!='0')
        return true;
    return false;
}
bool verificareZiduriStanga(char m[L][C], int x, int y)
{
    if(m[x][y-3]!='1' && m[x][y-1] == '1' && m[x][y-2]!='0')
        return true;
    return false;
}



///Functii pentru regula de ingradire PLAYER 1
void verificareSusP1(char m[L][C], char aux[L][C], int x, int y, bool & amGasit)
{
    if(x==1)
    {
        amGasit=true;
        return;
    }
    if(x<18 && y<18 && x>0 && y>0)
    {
        aux[x][y]='v';
        if(m[x-1][y]=='1' && aux[x-2][y]!='v')
        {
            if(amGasit==true)
            {
                return;
            }
            verificareSusP1(m, aux, x-2, y, amGasit);

        }
        if(m[x][y+1]=='1'&& aux[x][y+2]!='v')
        {
            if(amGasit==true)
            {
                return;
            }
            verificareDreaptaP1(m, aux, x, y+2, amGasit);

        }
        if(m[x][y-1]=='1' && aux[x][y-2]!='v')
        {
            if(amGasit==true)
            {
                return;
            }
            verificareStangaP1(m, aux, x, y-2, amGasit);

        }
    }
}
void verificareStangaP1(char m[L][C], char aux[L][C], int x, int y, bool & amGasit)
{
    if(x==1)
    {
        amGasit=true;
        return;
    }
    aux[x][y]='v';

    if(m[x-1][y]=='1'&& aux[x-2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareSusP1(m, aux, x-2, y, amGasit);
    }
    if(m[x][y-1]=='1' && aux[x][y-2]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareStangaP1(m, aux, x, y-2, amGasit);
    }
    if(m[x+1][y]=='1' && aux[x+2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareJosP1(m, aux, x+2, y, amGasit);
    }

}
void verificareDreaptaP1(char m[L][C], char aux[L][C], int x, int y, bool & amGasit)
{
    if(x==1)
    {
        amGasit=true;
        return;
    }
    aux[x][y]='v';
    if(m[x-1][y]=='1'&& aux[x-2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareSusP1(m, aux, x-2, y, amGasit);

    }
    if(m[x][y+1]=='1' && aux[x][y+2]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareDreaptaP1(m, aux, x, y+2, amGasit);

    }
    if(m[x+1][y]=='1' && aux[x+2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareJosP1(m, aux, x+2, y, amGasit);

    }

}
void verificareJosP1(char m[L][C], char aux[L][C], int x, int y, bool & amGasit)
{
    if(x==1)
    {
        amGasit=true;
        return;
    }
    aux[x][y]='v';

    if(m[x][y+1]=='1'&& aux[x][y+2]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareDreaptaP1(m, aux, x, y+2, amGasit);

    }
    if(m[x][y-1]=='1' && aux[x][y-2]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareStangaP1(m, aux, x, y-2, amGasit);

    }
    if(m[x+1][y]=='1' && aux[x+2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareJosP1(m, aux, x+2, y, amGasit);

    }

}
int Can1Escape(char m[L][C])
{
    int a,b,c,d;
    FindPlayer1(m,a,b);
    FindPlayer2(m,c,d);

    int x, y;
    char aux[L][C];
    creareTabla(aux);
    aux[c][d]='0';
    aux[a][b]='v';
    bool amGasit=false;
    FindPlayer1(m,x,y);

    if(m[x-1][y]=='1' &&  aux[x-2][y]!='v')
    {
        if(amGasit==true)
        {

            return 1;

        }
        verificareSusP1(m, aux, x-2, y, amGasit);

    }
    if(m[x][y+1]=='1' && aux[x][y+2]!='v')
    {
        if(amGasit==true)
        {

            return 1;
        }
        verificareDreaptaP1(m, aux, x, y+2, amGasit);


    }
    if(m[x][y-1]=='1' && aux[x][y-2]!='v')
    {

        if(amGasit==true)
        {

            return 1;
        }
        verificareStangaP1(m, aux, x, y-2, amGasit);
    }
    if(m[x+1][y]=='1' && aux[x+2][y]!='v')
    {

        if(amGasit==true)
        {

            return 1;
        }
        verificareJosP1(m, aux, x+2, y, amGasit);
    }
    if(amGasit==true)
    {

        return 1;
    }
    else
    {

        return 0;
    }

}


///Functii pentru regula de ingradire PLAYER 2
void verificareSusP2(char m[L][C], char aux[L][C], int x, int y, bool & amGasit)
{
    if(x==17)
    {
        amGasit=true;
        return;
    }
    if(x<18 && y<18 && x>0 && y>0)
    {
        aux[x][y]='v';
        if(m[x][y-1]=='1' && aux[x][y-2]!='v')
        {
            if(amGasit==true)
            {
                return;
            }
            verificareStangaP2(m, aux, x, y-2, amGasit);

        }
        if(m[x][y+1]=='1'&& aux[x][y+2]!='v')
        {
            if(amGasit==true)
            {
                return;
            }
            verificareDreaptaP2(m, aux, x, y+2, amGasit);

        }
        if(m[x-1][y]=='1' && aux[x-2][y]!='v')
        {
            if(amGasit==true)
            {
                return;
            }
            verificareSusP2(m, aux, x-2, y, amGasit);

        }
    }
}
void verificareStangaP2(char m[L][C], char aux[L][C], int x, int y, bool & amGasit)
{
    if(x==17)
    {
        amGasit=true;
        return;
    }
    aux[x][y]='v';
    if(m[x+1][y]=='1' && aux[x+2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareJosP2(m, aux, x+2, y, amGasit);

    }
    if(m[x][y-1]=='1' && aux[x][y-2]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareStangaP2(m, aux, x, y-2, amGasit);

    }
    if(m[x-1][y]=='1'&& aux[x-2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareSusP2(m, aux, x-2, y, amGasit);

    }

}
void verificareDreaptaP2(char m[L][C], char aux[L][C], int x, int y, bool & amGasit)
{
    if(x==17)
    {
        amGasit=true;
        return;
    }
    aux[x][y]='v';
    if(m[x+1][y]=='1' && aux[x+2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareJosP2(m, aux, x+2, y, amGasit);

    }
    if(m[x][y+1]=='1' && aux[x][y+2]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareDreaptaP2(m, aux, x, y+2, amGasit);

    }
    if(m[x-1][y]=='1'&& aux[x-2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareSusP2(m, aux, x-2, y, amGasit);

    }

}
void verificareJosP2(char m[L][C], char aux[L][C], int x, int y, bool & amGasit)
{
    if(x==17)
    {
        amGasit=true;
        return;
    }
    aux[x][y]='v';
    if(m[x+1][y]=='1' && aux[x+2][y]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareJosP2(m, aux, x+2, y, amGasit);

    }
    if(m[x][y-1]=='1' && aux[x][y-2]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareStangaP2(m, aux, x, y-2, amGasit);

    }
    if(m[x][y+1]=='1'&& aux[x][y+2]!='v')
    {
        if(amGasit==true)
        {
            return;
        }
        verificareDreaptaP2(m, aux, x, y+2, amGasit);

    }

}
int Can2Escape(char m[L][C])
{
    int a,b,c,d;
    FindPlayer1(m,a,b);
    FindPlayer2(m,c,d);
    int x, y;
    char aux[L][C];
    creareTabla(aux);
    aux[c][d]='v';
    aux[a][b]='0';
    bool amGasit=false;
    FindPlayer2(m,x,y);

    if(m[x+1][y]=='1' &&  aux[x+2][y]!='v')
    {
        if(amGasit==true)
        {

            return 1;
        }
        verificareJosP2(m, aux, x+2, y, amGasit);

    }
    if(m[x][y+1]=='1' && aux[x][y+2]!='v')
    {
        if(amGasit==true)
        {

            return 1;
        }
        verificareDreaptaP2(m, aux, x, y+2, amGasit);


    }
    if(m[x][y-1]=='1' && aux[x][y-2]!='v')
    {

        if(amGasit==true)
        {

            return 1;
        }
        verificareStangaP2(m, aux, x, y-2, amGasit);
    }
    if(m[x-1][y]=='1' && aux[x-2][y]!='v')
    {

        if(amGasit==true)
        {

            return 1;
        }
        verificareSusP2(m, aux, x-2, y, amGasit);
    }
    if(amGasit==true)
    {

        return 1;

    }
    else
    {

        return 0;
    }

}

///FUNCTII GRAFICA





///Afisare Tabla

void afisareTablaJoc(char m[L][C])
{

    int a,b,c,d;
    FindPlayer1(m,a,b);
    FindPlayer2(m,c,d);
    system("cls");
    for(int i=1; i<=17; i++)
    {
        for(int j=1; j<=17; j++)
        {
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"Pozitie Player 1 (#) : "<<a<<" "<<b<<endl;
    cout<<"Pozitie Player 2 (*) : "<<c<<" "<<d<<endl;
    cout<<nrZiduri1<<" "<<nrZiduri2;
}

void desenareFundal()
{
    int i;
    if(paritateMiscare%2==0)
        for(i=1; i<=16; i++)
        {

            setfillstyle(SOLID_FILL, RGB(255-10*i,100-3*i,100-3*i));
            bar(350,(i-1)*50, 1520-350, i*50);
        }
    if(paritateMiscare%2==1)
        for(i=1; i<=16; i++)
        {

            setfillstyle(SOLID_FILL, RGB(100-3*i,100-3*i,255-10*i));
            bar(350,(i-1)*50, 1520-350, i*50);
        }


}
void Scor()
{
    char s1[4],s2[4];
    ToString(P1Wins,s1);
    ToString(P2Wins,s2);
    setfillstyle(SOLID_FILL, RGB(64,64,64));
    setcolor(RGB(64,64,64));
    fillellipse(80,720,70,70);
    fillellipse(1440,720,70,70);
    setbkcolor(RGB(64,64,64));
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT,0,16);
    outtextxy(90,720,s1);
    outtextxy(1430,720,s2);


    setfillstyle(SOLID_FILL, RGB(255,100,100));
    setcolor(RGB(255,100,100));
    fillellipse(50,750,20,20);

    setfillstyle(SOLID_FILL, RGB(100,100,255));
    setcolor(RGB(100,100,255));
    fillellipse(1470,750,20,20);

}
void GiveUp()
{
    if(paritateMiscare%2)
    {
        setfillstyle(SOLID_FILL, RGB(100,100,255));
        setcolor(RGB(100,100,255));
        bar(180,350,280,450);
        settextstyle(SANS_SERIF_FONT,0,15);
        setbkcolor(RGB(100,100,255));
        setcolor(WHITE);
        outtextxy(231,390,"GIVE");
        outtextxy(231,430,"UP?");
    }
    else
    {
        setfillstyle(SOLID_FILL, RGB(255,100,100));
        setcolor(RGB(255,100,100));
        bar(180,350,280,450);
        setbkcolor(RGB(255,100,100));
        setcolor(WHITE);
        settextstyle(SANS_SERIF_FONT,0,15);
        outtextxy(231,390,"GIVE");
        outtextxy(231,430,"UP?");
    }
}
void desenareTablaDeJoc(char m[L][C])
{


    ///FUNDAL
    setfillstyle(SOLID_FILL, RGB(64,64,64));
    bar(0,0,1520,800);
    desenareFundal();



    ///FUNDAL TABLA
    setcolor(RGB(32,32,32));
    setfillstyle(SOLID_FILL, RGB(64,64,64));
    bar3d(380,20,1140,780,20,1);

    setcolor(RGB(64,64,64));
    setfillstyle(SOLID_FILL, RGB(42,42,42));
    bar(380+20,20+20,1140-20,780-20);
    floodfill(1, 1, RGB(32,32,32));

    desenareMatrice(m);
    desenareButoaneOV(200);
    if(sound)
    {
        readimagefile("soundon.jpg", 1400,20,1500, 120);
    }
    else readimagefile("soundoff.jpg", 1400,20,1500, 120);

    setcolor(RGB(205,82,255));
    setbkcolor(RGB(205,82,255));
    setfillstyle(SOLID_FILL, RGB(205,82,255));
    bar(20,20,120,120);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT,0,14);
    outtextxy(70,78,"EXIT");
    //readimagefile("quit.jpg",20,20,120,120);
    Scor();
    GiveUp();
}

void desenareMatrice(char m[L][C])
{
    float startX;
    float startY;
    startX=410;
    startY=50;
    int i,j;
    for(i=1; i<=9; i++)
    {
        for(j=1; j<=9; j++)
        {
            int col=64;
            int pad=col+5;
            ///PATRATELE
            if(i==1)
                setfillstyle(SOLID_FILL, RGB(105,col,col));
            else if (i==9) setfillstyle(SOLID_FILL, RGB(col,col,105));
            else setfillstyle(SOLID_FILL, RGB(col,col,col));
            bar(startX,startY,startX+60,startY+60);
            //Detaliu
            if(i==1)
                setfillstyle(SOLID_FILL, RGB(105,pad,pad));
            else if (i==9) setfillstyle(SOLID_FILL, RGB(pad,pad,105));
            else setfillstyle(SOLID_FILL, RGB(pad,pad,pad));
            bar(startX+10,startY+10,startX+60-10,startY+60-10);
            startX+=80;


            ///PLAYERI
            if(m[i*2-1][j*2-1]=='*')
            {
                setfillstyle(SOLID_FILL, RGB(255,100,100));
                setcolor(RGB(255,100,100));
                int xPtDesen = ((j*2-1)/2)*80+440;
                int yPtDesen = ((i*2-1)/2)*80+80;
                fillellipse(xPtDesen, yPtDesen, 25,25);
                setfillstyle(SOLID_FILL, RGB(200,83,83));
                fillellipse(xPtDesen, yPtDesen, 15,15);
            }
            if(m[i*2-1][j*2-1]=='#')
            {
                setfillstyle(SOLID_FILL, RGB(100,100,255));
                setcolor(RGB(100,100,255));
                int xPtDesen = ((j*2-1)/2)*80+440;
                int yPtDesen = ((i*2-1)/2)*80+80;
                fillellipse(xPtDesen, yPtDesen, 25,25);
                setfillstyle(SOLID_FILL, RGB(83,83,200));
                fillellipse(xPtDesen, yPtDesen, 15,15);
            }


            ///LOCURI DE ZID
            if(i!=9 && j!=9)
            {
                setfillstyle(SOLID_FILL, RGB(32,32,32));
                setcolor(RGB(70,70,70));
                int xPtDesen = j*80+400;
                int yPtDesen = i*80+40;
                fillellipse(xPtDesen, yPtDesen, 10,10);
            }


            ///ZIDURI
            if(m[i*2][j*2]=='>')
            {
                int plasareX=110+80*(((i*2+2)/2)-2);
                int plasareY=410+80*(((j*2+2)/2)-2);
                setfillstyle(SOLID_FILL, WHITE);
                bar(plasareY, plasareX, plasareY+140, plasareX+20);
            }
            if(m[i*2][j*2]=='^')
            {
                int plasareX=50+80*(((i*2+2)/2)-2);
                int plasareY=470+80*(((j*2+2)/2)-2);
                setfillstyle(SOLID_FILL, WHITE);
                bar(plasareY, plasareX, plasareY+20, plasareX+140);
            }



        }

        startY+=80;
        startX=410;
    }

}
bool apartinInterval(int x, int y,int x1, int y1, int x2, int y2)
{
    return x>=x1 && x<=x2 && y>=y1 && y<=y2;
}
void ToString(int x, char s[3])
{
    if(x<10)
    {
        x=x+48;
        s[0]=x;
        s[1]='\0';
    }
    else
    {
        s[0]=x/10+48;
        s[1]=x%10+48;
        s[2]='\0';
    }
}
void desenareButoaneOV(int on)
{
    //vertical
    if(paritateMiscare%2==0)
        setfillstyle(SOLID_FILL, RGB(255,on,on));
    else setfillstyle(SOLID_FILL, RGB(on,on,255));
    bar(ox, oy, ox+marimeButon, oy+marimeButon);
    setfillstyle(SOLID_FILL, WHITE);
    bar(ox+marimeButon/10*4, oy, ox+marimeButon/10*6, oy+marimeButon);

    //Numar Ziduri
    if(paritateMiscare%2==0)
    {
        setbkcolor(RGB(32,32,32));
        setfillstyle(SOLID_FILL,RGB(32,32,32));
        setcolor(RGB(255,150,150));
    }

    else
    {
        setbkcolor(RGB(32,32,32));
        setcolor(RGB(150,150,255));
        setfillstyle(SOLID_FILL, RGB(32,32,32));
    }
    bar(ox, oy+100, ox+marimeButon, oy+marimeButon+101);
    setcolor(WHITE);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(SANS_SERIF_FONT,0,9);

    char nr1[3], nr2[3];
    ToString(nrZiduri1, nr1);
    ToString(nrZiduri2, nr2);
    if(paritateMiscare%2==0)
        outtextxy(vx+50,vy-22,nr1);
    else outtextxy(vx+50,vy-22,nr2);

    //orizontal
    if(paritateMiscare%2==0)
        setfillstyle(SOLID_FILL, RGB(255,on,on));
    else setfillstyle(SOLID_FILL, RGB(on,on,255));
    bar(vx, vy+padding, vx+marimeButon, vy+marimeButon+padding);
    setfillstyle(SOLID_FILL, WHITE);
    bar(vx, vy+padding+marimeButon/10*4, vx+marimeButon, vy+padding+marimeButon/10*6);
}
void convertireCoordonate(int &x, int &y)
{
    ///                     PENTRU CASUTE
    if(x>=410 && x<=470)
        x=1;
    if(x>=410+80*1 && x<=470+80*1)
        x=3;
    if(x>=410+80*2 && x<=470+80*2)
        x=5;
    if(x>=410+80*3 && x<=470+80*3)
        x=7;
    if(x>=410+80*4 && x<=470+80*4)
        x=9;
    if(x>=410+80*5 && x<=470+80*5)
        x=11;
    if(x>=410+80*6 && x<=470+80*6)
        x=13;
    if(x>=410+80*7 && x<=470+80*7)
        x=15;
    if(x>=410+80*8 && x<=470+80*8)
        x=17;


    if(y>=50 && y<=110)
        y=1;
    if(y>=50+80*1 && y<=110+80*1)
        y=3;
    if(y>=50+80*2 && y<=110+80*2)
        y=5;
    if(y>=50+80*3 && y<=110+80*3)
        y=7;
    if(y>=50+80*4 && y<=110+80*4)
        y=9;
    if(y>=50+80*5 && y<=110+80*5)
        y=11;
    if(y>=50+80*6 && y<=110+80*6)
        y=13;
    if(y>=50+80*7 && y<=110+80*7)
        y=15;
    if(y>=50+80*8 && y<=110+80*8)
        y=17;



    ///                      PENTRU ZIDURI

    if(x>470 + 80*0 && x<490 + 80*0)
        x=2;
    if(x>470 + 80*1 && x<490 + 80*1)
        x=4;
    if(x>470 + 80*2 && x<490 + 80*2)
        x=6;
    if(x>470 + 80*3 && x<490 + 80*3)
        x=8;
    if(x>470 + 80*4 && x<490 + 80*4)
        x=10;
    if(x>470 + 80*5 && x<490 + 80*5)
        x=12;
    if(x>470 + 80*6 && x<490 + 80*6)
        x=14;
    if(x>470 + 80*7 && x<490 + 80*7)
        x=16;


    if(y>110 + 80*0 && y<130 + 80*0)
        y=2;
    if(y>110 + 80*1 && y<130 + 80*1)
        y=4;
    if(y>110 + 80*2 && y<130 + 80*2)
        y=6;
    if(y>110 + 80*3 && y<130 + 80*3)
        y=8;
    if(y>110 + 80*4 && y<130 + 80*4)
        y=10;
    if(y>110 + 80*5 && y<130 + 80*5)
        y=12;
    if(y>110 + 80*6 && y<130 + 80*6)
        y=14;
    if(y>110 + 80*7 && y<130 + 80*7)
        y=16;
}

void WaitForClick(int &x, int &y)
{
    int clicked=0;
    while(clicked==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {

            x=mousex();
            y=mousey();
            if(x>=410 && y>=50 && x<=410+720 && y<=50+720 &&finish==0)
            {

                aFostConvertit=true;
                convertireCoordonate(x,y);
            }
            else
            {
                aFostConvertit=false;

            }
            clicked=1;
            clearmouseclick(WM_LBUTTONDOWN);

        }

    }

}
void WaitForClickMeniu(int &x, int &y)
{
    int clicked=0;
    while(clicked==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {

            x=mousex();
            y=mousey();
            clicked=1;
            clearmouseclick(WM_LBUTTONDOWN);

        }

    }

}

void WaitForOrientare(char orientare[10])
{
    int x,y,clicked=0;
    while(clicked==0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {

            x=mousex();
            y=mousey();
            if(x>=ox && x<=ox+marimeButon && y>=oy && y<=oy+marimeButon)
            {
                strcpy(orientare, "vertical");
                clicked=1;
            }
            else if(x>=vx && x<=vx+marimeButon && y>=vy+10 && y<=vy+marimeButon+10)
            {
                strcpy(orientare, "orizontal");
                clicked=1;
            }
            else
            {
                strcpy(orientare, "razgandit");
                clicked=1;
            }

            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
void desenareMutariValide(char p, int x, int y)
{
    int i,j;
    char copie[L][C];
    copiereMatrice(m, copie);

    if(p=='*')
    {
        for(i=1; i<=17; i++)
        {
            for(j=1; j<=17; j++)
            {
                if(miscareValidaPionPtDesenare(copie,i,j,x,y))
                {
                    setfillstyle(SOLID_FILL, RGB(230,200,200));
                    setcolor(RGB(230,200,200));
                    int xPtDesen = (j/2)*80+440;
                    int yPtDesen = (i/2)*80+80;
                    fillellipse(xPtDesen, yPtDesen, 15,15);
                }

            }
        }
    }
    else if(p=='#')
    {
        for(i=1; i<=17; i++)
        {
            for(j=1; j<=17; j++)
            {
                if(miscareValidaPionPtDesenare(copie,i,j,x,y))
                {
                    setfillstyle(SOLID_FILL, RGB(200,200,230));
                    setcolor(RGB(200,200,230));
                    int xPtDesen = (j/2)*80+440;
                    int yPtDesen = (i/2)*80+80;
                    fillellipse(xPtDesen, yPtDesen, 15,15);
                }
            }
        }
    }
}


void play(char nume[1000])
{

    if(sound)
    {
        PlaySound(nullptr, nullptr, 0);
        PlaySound(nume, NULL, SND_FILENAME|SND_ASYNC);
    }
}
void playAnimation()
{

    for(i=0; i<=10; i++)
    {
        int x=width/2,y=height/2;

        setcolor(RGB(100,200,100));
        setfillstyle(SOLID_FILL, RGB(100,200,100));

        bar(x-i*100,y-i*100,x+i*100, y+i*100);
        delay(50);
    }
    delay(500);

}
void playStartAnimation()
{


    for(int i=64; i>=0; i--)
    {

        int x=width/2,y=height/2;


        setcolor(RGB(100-(100-1.56*i),200-(200-3.12*i),100-(100-1.56*i)));
        setfillstyle(SOLID_FILL, RGB(100-(100-1.56*i),200-(200-3.12*i),100-(100-1.56*i)));
        bar(0,0,x*2,y*2);


        setcolor(RGB(100,200,100));
        setfillstyle(SOLID_FILL, RGB(100,200,100));
        bar(x-i*50,y-i*50,x+i*50, y+i*50);

        delay(25);
    }

}
void Gameplay()
{
    afisareTablaJoc(m);
    while(finish==0)
    {


        ny=nx=0;


        desenareTablaDeJoc(m);
        setfillstyle(SOLID_FILL, WHITE);

        //afisareTablaJoc(m);

        if(primaMiscare)
        {
            primaMiscare=false;

        }



        selectarePatrat();


        Finish(finish,m);

    }
}

void Meniu()
{

    P1Wins=P2Wins=0;
    readimagefile("Menu.jpg",0,0,width, height);
    finish=0;
    nrZiduri1=10;
    nrZiduri2=10;
    int clicked=0;
    int cx,cy;
    if(sound)
            PlaySound("bg.wav", NULL, SND_FILENAME || SND_ASYNC || SND_LOOP);
    if(byTudorAndBogdan)
    {
        setcolor(RGB(205,82,255));
        setbkcolor(RGB(205,82,255));
        setfillstyle(SOLID_FILL,RGB(205,82,255));
        bar(735,208,1112,253);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        setcolor(WHITE);
        settextstyle(EUROPEAN_FONT,0,14);
        outtextxy(922,235,"by Tudor and Bogdan");
    }
    while(clicked==0)
    {
        if(sound)
        {
            readimagefile("soundon.jpg", 1400,20,1500, 120);
        }
        else readimagefile("soundoff.jpg", 1400,20,1500, 120);

        WaitForClickMeniu(cx,cy);
        if(apartinInterval(cx,cy,735,208,1112,253))
        {
            byTudorAndBogdan = 1;
            if(byTudorAndBogdan)
            {
                setcolor(RGB(205,82,255));
                setbkcolor(RGB(205,82,255));
                setfillstyle(SOLID_FILL,RGB(205,82,255));
                bar(735,208,1112,253);
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                setcolor(WHITE);
                settextstyle(EUROPEAN_FONT,0,14);
                outtextxy(922,235,"by Tudor and Bogdan");
            }
        }
        if(apartinInterval(cx,cy,1400,20,1500, 120))
        {
            if(sound)
            {
                sound=0;
                PlaySound(NULL, NULL, 0);
            }
            else
            {
                sound=1;
                PlaySound("bg.wav", NULL, SND_FILENAME || SND_ASYNC || SND_LOOP);
            }
        }
        if(apartinInterval(cx,cy,594,294,923,418))   ///start
        {
            clicked=1;
            readimagefile("start.jpg",0,0,width, height);
            int startClicked=0;
            if(byTudorAndBogdan)
            {
                setcolor(RGB(205,82,255));
                setbkcolor(RGB(205,82,255));
                setfillstyle(SOLID_FILL,RGB(205,82,255));
                bar(735,208,1112,253);
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                setcolor(WHITE);
                settextstyle(EUROPEAN_FONT,0,14);
                outtextxy(922,235,"by Tudor and Bogdan");
            }
            while(startClicked==0)
            {

                if(sound)
                {
                    readimagefile("soundon.jpg", 1400,20,1500, 120);
                }
                else readimagefile("soundoff.jpg", 1400,20,1500, 120);
                WaitForClickMeniu(cx,cy);
                if(apartinInterval(cx,cy,735,208,1112,253))
                {
                    byTudorAndBogdan = 1;
                    if(byTudorAndBogdan)
                    {
                        setcolor(RGB(205,82,255));
                        setbkcolor(RGB(205,82,255));
                        setfillstyle(SOLID_FILL,RGB(205,82,255));
                        bar(735,208,1112,253);
                        settextjustify(CENTER_TEXT,CENTER_TEXT);
                        setcolor(WHITE);
                        settextstyle(EUROPEAN_FONT,0,14);
                        outtextxy(922,235,"by Tudor and Bogdan");
                    }
                }
                if(apartinInterval(cx,cy,1400,20,1500, 120))
                {
                    if(sound)
                    {
                        sound=0;
                        PlaySound(NULL, NULL, 0);
                    }
                    else
                    {
                        sound=1;
                        PlaySound("bg.wav", NULL, SND_FILENAME || SND_ASYNC || SND_LOOP);
                    }
                }
                if(apartinInterval(cx,cy,450,294,1070,418))
                {

                    startClicked=1;
                    selection=1;
                    srand(time(0));
                    paritateMiscare=rand()%2;
                    if(selection!=1)
                        paritateMiscare=0;
                    creareTabla(m);
                    playAnimation();
                    playStartAnimation();
                    PlaySound(NULL, NULL, 0);
                    Gameplay();
                }
                if(apartinInterval(cx,cy,450,459,1070,580))
                {

                    startClicked=1;
                    selection=2;
                    srand(time(0));
                    paritateMiscare=rand()%2;
                    if(selection!=1)
                        paritateMiscare=0;
                    creareTabla(m);
                    playAnimation();
                    playStartAnimation();
                    PlaySound(NULL, NULL, 0);
                    Gameplay();
                }
                if(apartinInterval(cx,cy,450,624,1070,742))
                {

                    startClicked=1;
                    selection=3;
                    srand(time(0));
                    paritateMiscare=rand()%2;
                    if(selection!=1)
                        paritateMiscare=0;
                    creareTabla(m);
                    playAnimation();
                    playStartAnimation();
                    PlaySound(NULL, NULL, 0);
                    Gameplay();
                }


                if(apartinInterval(cx,cy,1263,662,1472,744))
                {
                    startClicked=1;
                    Meniu();
                }




            }



        }
        if(apartinInterval(cx,cy,594,459,923,580))  //RULES
        {
            int ro=1;
            clicked=1;
            if(ro)
            {
                readimagefile("rules.jpg",0,0,width, height);
                readimagefile("eng.jpg",1263,300,1472,509);
            }
            else
            {
                readimagefile("ruleseng.jpg",0,0,width, height);
                readimagefile("ro.jpg",1263,300,1472,509);
            }

            int ruleClicked=0;

            while(ruleClicked==0)
            {
                if(sound)
                {
                    readimagefile("soundon.jpg", 1400,20,1500, 120);
                }
                else readimagefile("soundoff.jpg", 1400,20,1500, 120);
                int a,b;

                WaitForClickMeniu(a,b);
                if(apartinInterval(a,b,1400,20,1500, 120))
                {
                    if(sound)
                    {
                        sound=0;
                        PlaySound(NULL, NULL, 0);
                    }
                    else
                    {
                        sound=1;
                        PlaySound("bg.wav", NULL, SND_FILENAME || SND_ASYNC || SND_LOOP);
                    }
                }
                if(apartinInterval(a,b,1263,300,1472,509))
                {
                    if(ro)
                    {
                        readimagefile("ruleseng.jpg",0,0,width,height);
                        readimagefile("ro.jpg",1263,300,1472,509);
                        ro=0;

                    }
                    else
                    {
                        readimagefile("rules.jpg",0,0,width,height);
                        readimagefile("eng.jpg",1263,300,1472,509);
                        ro=1;
                    }
                }
                if(apartinInterval(a,b,1263,662,1472,744))
                {
                    ruleClicked=1;
                    Meniu();
                }

            }

        }
        if(apartinInterval(cx,cy,594,624,923,745))  //HIGHSCORES
        {
            clicked=1;
            readimagefile("hs.jpg",0,0,width, height);
            int ruleClicked=0;
            settextjustify(LEFT_TEXT, CENTER_TEXT);
            setbkcolor(RGB(142,0,232));
            setcolor(WHITE);
            settextstyle(SANS_SERIF_FONT, 0, 17);

            char s1[3];
            char s2[3];
            char s3[3];
            char s4[3];
            char s5[3];


            for(i=1; i<=5; i++)
            {
                if(v[i].player==1)
                {
                    outtextxy(420,120+(i-1)*60, "PLAYER 1              - ");
                    ToString(v[i].score, s1);
                    outtextxy(1000,120+(i-1)*60, s1);
                }
                if(v[i].player==2)
                {
                    outtextxy(420,120+(i-1)*60, "PLAYER 2              - ");
                    ToString(v[i].score, s2);
                    outtextxy(1000,120+(i-1)*60, s2);
                }
                if(v[i].player==3)
                {
                    outtextxy(420,120+(i-1)*60, "PLAYER (VS BOT) - ");
                    ToString(v[i].score, s3);
                    outtextxy(1000,120+(i-1)*60, s3);
                }
                if(v[i].player==4)
                {
                    outtextxy(420,120+(i-1)*60, "BOT (EASY)           - ");
                    ToString(v[i].score, s4);
                    outtextxy(1000,120+(i-1)*60, s4);
                }
                if(v[i].player==5)
                {
                    outtextxy(420,120+(i-1)*60, "BOT (HARD)          - ");
                    ToString(v[i].score, s5);
                    outtextxy(1000,120+(i-1)*60, s5);
                }
            }
            setcolor(RGB(150,250,255));
            setfillstyle(SOLID_FILL, RGB(150,250,255));
            fillellipse(1100, 100, 20,20);

            setcolor(YELLOW);
            setfillstyle(SOLID_FILL, YELLOW);
            fillellipse(1100, 160, 20,20);


            setcolor(RGB(200,200,200));
            setfillstyle(SOLID_FILL, RGB(200,200,200));
            fillellipse(1100, 220, 20,20);


            setcolor(RGB(177,81,33));
            setfillstyle(SOLID_FILL, RGB(177,81,33));
            fillellipse(1100, 280, 20,20);
            while(ruleClicked==0)
            {
                if(sound)
                {
                    readimagefile("soundon.jpg", 1400,20,1500, 120);
                }
                else readimagefile("soundoff.jpg", 1400,20,1500, 120);
                int a,b;
                WaitForClickMeniu(a,b);
                if(apartinInterval(a,b,1400,20,1500, 120))
                {
                    if(sound)
                    {
                        sound=0;
                        PlaySound(NULL, NULL, 0);
                    }
                    else
                    {
                        sound=1;
                        PlaySound("bg.wav", NULL, SND_FILENAME || SND_ASYNC || SND_LOOP);
                    }
                }



                if(apartinInterval(a,b,1263,662,1472,744))
                {
                    ruleClicked=1;
                    Meniu();

                }

            }

        }

        if(apartinInterval(cx,cy,1263,662,1472,744))  ///QUIT
        {
            clicked=1;
            quit=1;
            main();

        }
    }
    /*
    WaitForClickMeniu(cx,cy);
    cout<<cx<<" "<<cy<<endl;
    WaitForClickMeniu(cx,cy);
    cout<<cx<<" "<<cy<<endl;
    */
}


void getAndSortHighScores()
{
    int n,p,s;
    while(fin>>n)
    {

        fin>>p;
        fin>>s;
        v[n].player=p;
        v[n].score=s;
    }
    for(i=1; i<=4; i++)
    {
        for(j=i+1; j<=5; j++)
        {
            int aux1,aux2;
            if(v[i].score<v[j].score)
            {
                aux1=v[i].score;
                aux2=v[i].player;
                v[i].score=v[j].score;
                v[i].player=v[j].player;
                v[j].score=aux1;
                v[j].player=aux2;
            }

        }
    }

}
int main()

{


    if(quit)
    {
        exit(1);
    }
    else{
         initwindow(width, height, "Quoridor");

        ///tragere la sorti

        int n;
        getAndSortHighScores();

        Meniu();
    }

    closegraph();
    return 0;

}



/**
*-player 1;
#-player 2;
1-spatiu pt zid
0-spatiu pt player;
- -zid orizontal
| - zid vertical


selection 1 - PVP
selection 2 - PVB (EASY)
selection 3 - PVB (HARD)

BOT - paritate 1
Player - paritate 0
**/


