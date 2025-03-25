#pragma once

typedef struct Auto
{
    int id; /**< ID samochodu. */
	char nr_rejestracyjny[20]; /**< Numer rejestracyjny samochodu. */
    char marka[20]; /**< Marka samochodu. */
    char model[20]; /**< Model samochodu. */
    int rok_produkcji; /**< Rok produkcji samochodu. */
    char kolor[30]; /**< Kolor samochodu. */
    int przebieg; /**< Warto�� przebiegu samochodu. */
    int wypozyczony; /**< Flaga "czy wypo�yczony". */
    struct Auto* next; /**< Wska�nik na nast�pny element listy samochod�w. */
    struct Auto* prev; /**< Wska�nik na poprzedni element listy samochod�w. */
}Auto;

Auto* wczytaj_z_pliku();
Auto* wyswietl_auta(Auto* glowa);
