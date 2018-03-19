#ifndef MECH_H
#define MECH_H
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct zawodnik
{
    string nick;
    bool wartosc;
    char znak;
};

class mech
{
private:
        int x, y;
        int rozmiar_planszy;
        char **tablica;
        int zmienna_int;
        char zmienna_char;
        zawodnik gracz_pomocniczy, zaczynajacy;
public:
        zawodnik gracz1, gracz2;
        int suma = 0;
        int liczba_ruchow = 0;

    void wymiary_planszy();
    void nowa_plansza(int rozmiar_planszy, char **&tablica);
    void drukuj_plansze();
    void pelna_mechanika_gg();
    void dane_graczy();
    void rozgrywka_gg(zawodnik gracz1, zawodnik gracz2, int rozmiar_planszy, char **&tablica);
    void wspolrzedne_ruchu(int &x, int &y, int rozmiar_planszy);
    void sprawdzenie(int rozmiar_planszy, char **tablica);
    void wynik(int suma, int rozmiar_planszy, int liczba_ruchow);
    void powtorka_gg();
};
#endif // MECH_H
