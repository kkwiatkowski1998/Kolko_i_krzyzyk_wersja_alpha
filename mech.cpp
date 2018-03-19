#include <iostream>
#include <cstdlib>
#include <string>

#include <mech.h>
#include <menu.h>
#include <plansza.h>

using namespace std;

menu MENU;


// TABLICA;
void mech::wymiary_planszy()
{
    system("cls");
    MENU.okno_powitalne();
    MENU.podaj_wymiary_planszy(rozmiar_planszy);

}

void mech::nowa_plansza(int rozmiar_planszy, char**&tablica)
{

    tablica = new char *[rozmiar_planszy];
    for (int i = 0; i < rozmiar_planszy; i++)
    tablica[i] = new char [rozmiar_planszy];

    for (int i = 0; i < rozmiar_planszy; i++)
    {
        for (int j = 0; j < rozmiar_planszy; j++)
        {
             tablica[i][j]= '_';
        }
    }
}

void mech::drukuj_plansze()
{
    for (int i = 0; i < mech::rozmiar_planszy; i++)
    {
        for (int j = 0; j < mech::rozmiar_planszy; j++)
        {
            cout << mech::tablica[i][j] << '\t';
        }
        cout << endl << endl;
    }
}

// GRACZE

void mech::dane_graczy()
{
    gracz1.nick = MENU.nick("pierwszy");
    gracz2.nick = MENU.nick("drugi");

    zmienna_char = MENU.znak(gracz1.nick);
    switch (zmienna_char)
    {
    case 'O':
        gracz1.znak = 'O';
        gracz2.znak = 'X';
        break;
    case 'X':
        gracz1.znak = 'X';
        gracz2.znak = 'O';
        break;
    }

    zmienna_int = MENU.wartosc(gracz2.nick);
    switch (zmienna_int)
    {
    case 1:
        gracz1.wartosc = 0;
        gracz2.wartosc = 1;
        break;
    case 0:
        gracz1.wartosc = 1;
        gracz2.wartosc = 0;
    default:
        break;
    }
}

//GRACZ VS GRACZ

void mech::pelna_mechanika_gg()
{
    mech::wymiary_planszy();
    mech::nowa_plansza(rozmiar_planszy, tablica);
    mech::rozgrywka_gg(gracz1, gracz2, rozmiar_planszy, tablica);

}

void mech::powtorka_gg()
{
    mech::nowa_plansza(rozmiar_planszy, tablica);
    if(gracz1.wartosc == 0)
    {
        gracz1.wartosc = 1;
        gracz2.wartosc = 0;
    }
    else if(gracz1.wartosc == 1)
    {
        gracz1.wartosc = 0;
        gracz2.wartosc = 1;
    }
    mech::rozgrywka_gg(gracz1, gracz2, rozmiar_planszy, tablica);
}

void mech::rozgrywka_gg(zawodnik gracz1, zawodnik gracz2, int rozmiar_planszy, char **&tablica)
{
    for(int i = 0; i < rozmiar_planszy*rozmiar_planszy; i++)
    {
        system("cls");

        MENU.okno_powitalne();

        if(gracz1.wartosc == 1)
        {
            zaczynajacy = gracz1;
        }
        else if(gracz1.wartosc == 0)
        {
            zaczynajacy = gracz2;
        }

        drukuj_plansze();

        cout << zaczynajacy.nick << ", twoj ruch "<< zaczynajacy.znak << endl;
        cout << liczba_ruchow << endl;

        mech::wspolrzedne_ruchu(x, y, rozmiar_planszy);
        while(tablica[x-1][y-1]!=('_'))
        {
            cout << "Pole zajete!" << endl;
            mech::wspolrzedne_ruchu(x, y, rozmiar_planszy);
        }
        tablica[x-1][y-1] = zaczynajacy.znak;

        gracz_pomocniczy.wartosc = gracz1.wartosc;
        gracz1.wartosc = gracz2.wartosc;
        gracz2.wartosc = gracz_pomocniczy.wartosc;

        mech::sprawdzenie(rozmiar_planszy, tablica);
    }

}

void mech::wspolrzedne_ruchu(int &x, int &y, int rozmiar_planszy)
{
    cout << "Podaj wspolrzedna x " ;
    cin >> x;
    while(x<1 || x>rozmiar_planszy)
    {
        cout << "Podaj wspolrzedna x " ;
        cin >> x;
    }

    cout << "Podaj wspolrzedna y " ;
    cin >> y;
    while(y<1 || y>rozmiar_planszy)
    {
        cout << "Podaj wspolrzedna y " ;
        cin >> y;
    }
}

// G VS K

// SPRAWDZENIA

void mech::sprawdzenie(int rozmiar_planszy, char **tablica)
{
    liczba_ruchow++;
    for(int i = 0; i < rozmiar_planszy; i++)
    {
        for(int j = 0; j < rozmiar_planszy; j++)
        {
            if(tablica[i][j]=='X')
            {
                suma++;
            }
            if(tablica[i][j]=='O')
            {
                suma--;
            }
        }
        wynik(suma, rozmiar_planszy, liczba_ruchow);
        suma = 0;

        for(int j = 0; j < rozmiar_planszy; j++)
        {
            if(tablica[j][i]=='X')
            {
                suma++;
            }
            if(tablica[j][i]=='O')
            {
                suma--;
            }

        }
        wynik(suma, rozmiar_planszy, liczba_ruchow);
        suma = 0;
    }

    for(int i = 0; i < rozmiar_planszy; i++)
    {
        if(tablica[i][i]=='X')
        {
            suma++;
        }
        if(tablica[i][i]=='O')
        {
            suma--;
        }
    }
    wynik(suma, rozmiar_planszy, liczba_ruchow);
    suma = 0;

    for(int i = 0; i < rozmiar_planszy; i++)
    {
        if(tablica[rozmiar_planszy-1-i][i]=='X')
        {
            suma++;
        }
        if(tablica[rozmiar_planszy-1-i][i]=='O')
        {
            suma--;
        }
    }
    wynik(suma, rozmiar_planszy, liczba_ruchow);
    suma = 0;
}

void mech::wynik(int suma, int rozmiar_planszy, int c)
{
    if(gracz1.znak == 'O')
    {
        if(suma == rozmiar_planszy)
        {
            MENU.zwyciestwo(gracz2);
        }

        if(suma == (-rozmiar_planszy))
        {
            MENU.zwyciestwo(gracz1);
        }
    }
    if(gracz1.znak == 'X')
    {
        if(suma == rozmiar_planszy)
        {
            MENU.zwyciestwo(gracz1);
        }

        if(suma == (-rozmiar_planszy))
        {
            MENU.zwyciestwo(gracz2);
        }
    }
    else if(c == (rozmiar_planszy)*(rozmiar_planszy))
    {
        MENU.remis();
    }
}



