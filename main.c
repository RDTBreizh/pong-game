#include <windows.h> /* for HANDLE type, and console functions */
#include <stdio.h>
#include <stdlib.h>

int touche,touche_2,xballe,yballe, difficultee;
char get_key(void);
void gotoxy(int x,int y);
void hidecursor(void);
void clrscr(void);
void affichage_barre(int y,int num_joueur);
void affichage_Balle();

void color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}


int main(void)
{
    //*variables*
    char c,o;
    int ligne,l,colonne,tab[20][20];
    HANDLE wHnd;
    HANDLE rHnd;
    int  Yjoueur1=8,Yjoueur2=8, Xjoueur1, Xjoueur2,dX,dY,xballe,yballe,rebond_haut, rebond_bas,dead ;
    int i;
    int duree;

    touche_2=14/2;
    touche=14;
    xballe=50;
    yballe=15;
    dead=0;
    difficultee=500;
    dY=+1;
    dX=+1;

// dimension écran console
    SMALL_RECT windowSize = {0,0,100,25};
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleTitle("PONG!");
    hidecursor();





    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
//initialisation du tableau
    for (l=0; l<20; l++)
    {
        for (colonne=0; colonne<20; colonne++)
        {
            tab[l][colonne]=1;
        }
    }


    while (difficultee>10)
    {
        printf("Choisissez un niveau de difficulte entre 0 et 10\n\n");
        scanf("%d",&difficultee);


//Recherche du dernier caractère (renvoie 0 si il n'y a pas de caractère)

        touche_2=14/2;
        touche=14;
        xballe=50;
        yballe=15;
        dead=0;
        //difficultee=500;
        dY=1;
        dX=1;

        while(dead==0)
        {
            duree=110-(10*difficultee);
            Sleep(duree);
            clrscr();
            c=get_key();
            {
                if (c!=0)
                {
                    //monter descente joueur 1
                    if (c=='8')
                    {
                        Yjoueur2=Yjoueur2-1;
                    }
                    if (c=='2')
                    {
                        Yjoueur2=Yjoueur2+1;
                    }
//monter descente joueur 2
                    if (c=='z'||c=='Z')
                    {
                        Yjoueur1=Yjoueur1-1;
                    }
                    if(c=='s'|| c=='S')
                    {
                        Yjoueur1=Yjoueur1+1;
                    }
                }

            }
            //Blocage des barres sur un axe Y déterminé
            if ( Yjoueur1<0)
            {
                Yjoueur1=0;

            }
            if ( Yjoueur1>21)
            {
                Yjoueur1=21;

            }
            if ( Yjoueur2<0)
            {
                Yjoueur2=0;

            }
            if ( Yjoueur2>21)
            {
                Yjoueur2=21;
            }

            affichage_Balle(xballe,yballe);
            affichage_barre(Yjoueur2,2);
            affichage_barre(Yjoueur1,1);

            //rebond de la balle
            xballe=dX+xballe;
            yballe=dY+yballe;

            // rebond sur un axe Y ( haut et bas )
            if (yballe>23 || yballe<=1)
            {
                dY=-dY;

            }
            // rebond sur l'axe X droite et gauche

            if (xballe>=96)
            {
                for(i=0; i<5; i++)
                {
                    if(yballe == Yjoueur2+i)
                    {
                        dX=-dX;
                    }
                    else
                    {
                        dX=+dX;
                    }

                }
            }

            if (xballe<=3)
            {
                for(i=0; i<5; i++)
                {
                    if(yballe == (Yjoueur1+i))
                    {
                        dX=-dX;
                    }
                    else
                    {
                        dX=+dX;
                    }
                }
            }
            //

            if (xballe == 0)
            {
                dead=1;
            }
            if (xballe==98)
            {
                dead=1;
            }
        }
        if (xballe==0)
        {
            printf("                    Joueur 2 a gagne!\n");
        }
        if (xballe==98)
        {
            printf("                   Joueur 1 a gagne!\n");
        }

    }
}

// Quelques fonctions en vrac
    char get_key(void)
    {
        char c=0;
        while(_kbhit())
        {
            c = _getch();
        }
        return c;
    }

//Supression du curseur sur l'ecran
    void hidecursor()
    {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
    }

//Recherche du dernier caractère (renvoie 0 si il n'y a pas de caractère)

// deplace le curseur sur l'écran aux coordonnées x et y
    void gotoxy(int x,int y)
    {
        HANDLE handle;
        COORD coord= {x,y};
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(handle,coord);
    }

// vide l'écran

    void clrscr(void)
    {
        HANDLE handle;
        COORD coord= { 0, 0 };
        DWORD nbcar;
        CONSOLE_SCREEN_BUFFER_INFO info;
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(handle,&info);
        FillConsoleOutputCharacter(handle, (TCHAR) ' ',info.dwSize.X *
                                   info.dwSize.Y,coord,&nbcar);
        SetConsoleCursorPosition(handle,coord);
    }

    void affichage_barre(int y,int num_joueur)
    {
        int l, colonne;
        int x;

        if (num_joueur==1)
        {
            x=3;
        }
        else
        {
            x=97;
        }

        for(l=0; l<5; l++)
        {
            gotoxy(x,l+y);
            printf("%c",219);
        }
    }

    void affichage_Balle(xballe,yballe)

    {
        //affichage de la balle

        int l, colonne;

        gotoxy(xballe,yballe);
        printf("%c",64);



    }









