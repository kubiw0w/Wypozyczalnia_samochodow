#pragma once

typedef struct Auto
{
    int id; /**< ID samochodu. */
	char nr_rejestracyjny[20]; /**< Numer rejestracyjny samochodu. */
    char marka[20]; /**< Marka samochodu. */
    char model[20]; /**< Model samochodu. */
    int rok_produkcji; /**< Rok produkcji samochodu. */
    char kolor[30]; /**< Kolor samochodu. */
    int przebieg; /**< Wartoœæ przebiegu samochodu. */
    int wypozyczony; /**< Flaga "czy wypo¿yczony". */
    struct Auto* next; /**< WskaŸnik na nastêpny element listy samochodów. */
    struct Auto* prev; /**< WskaŸnik na poprzedni element listy samochodów. */
}Auto;

Auto* wczytaj_z_pliku();
Auto* wyswietl_auta(Auto* glowa);
