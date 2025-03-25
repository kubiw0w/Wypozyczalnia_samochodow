#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "WyswietlenieAut.h"
#include "WyswietlenieKlientow.h"
#include "WypozyczanieAut.h"
#pragma warning(disable : 4996)

typedef struct Wypozyczenie {
    int id_samochodu; /**< ID wypo�yczonego samochodu. */
    long long int numer_karty; /**< Numer karty klienta. */
    struct Wypozyczenie* next; /**< Wska�nik na nast�pny element listy. */
} Wypozyczenie;

Wypozyczenie* glowa_wyp = NULL; /**< Wska�nik na g�ow� listy wypo�ycze�. Zmienna wskazuje na g�ow� listy wypo�ycze� (glowa_wyp), kt�ra przechowuje informacje o wypo�yczonych samochodach. Na pocz�tku programu inicjalizowana jako NULL, a nast�pnie u�ywana do dodawania i zarz�dzania wypo�yczeniami. */

/**
 * Funkcja pobiera od u�ytkownika ID samochodu i numer karty klienta, a nast�pnie sprawdza, czy oba s� poprawne.
 * Je�li tak, tworzy nowe wypo�yczenie, dodaje je do listy wypo�ycze�, zapisuje informacje o wypo�yczeniu do pliku,
 * oznacza samoch�d jako wypo�yczony i wy�wietla odpowiednie komunikaty.
 *
 * \param glowa_aut - Wska�nik na g�ow� listy samochod�w.
 * \param glowa_kl - Wska�nik na g�ow� listy klient�w.
 */
void wypozycz_samochod(Auto* glowa_aut, Klient* glowa_kl)
{
    int id_samochodu;
    long long int numer_karty;

    printf("Podaj ID samochodu do wypo�yczenia: ");
    scanf("%d", &id_samochodu); /// Wprowadzanie ID samochodu

    printf("Podaj numer karty klienta: ");
    scanf("%lld", &numer_karty);    /// Wprowadzanie numeru karty klienta

    Auto* samochod = glowa_aut; /// Ustawienie wska�nika samochod na g�ow� listy samochod�w
    Klient* klient = glowa_kl;  /// Ustawienie wska�nika klient na g�ow� listy klient�w

    while (samochod != NULL)
    {
        if (samochod->id == id_samochodu)   /// Sprawdzenie czy ID samochodu zgadza si� z podanym ID
            break;
        samochod = samochod->next;  /// Przej�cie do nast�pnego samochodu
    }

    while (klient != NULL)
    {
        if (klient->numer_karty == numer_karty) /// Sprawdzenie czy numer karty klienta zgadza si� z podanym numerem karty
            break;
        klient = klient->next;  /// Przej�cie do nast�pnego klienta
    }

    if (samochod == NULL)   /// Je�eli nie znaleziono samochodu o podanym ID
    {
        printf("Nie znaleziono samochodu o podanym ID.\n");
        return;
    }

    if (klient == NULL) /// Je�eli nie znaleziono klienta o podanym numerze karty
    {
        printf("Nie znaleziono klienta o podanym numerze karty.\n");
        return;
    }

    Wypozyczenie* wyp = glowa_wyp;  /// Ustawienie wska�nika wyp na g�ow� listy wypo�ycze�
    while (wyp != NULL)
    {
        if (wyp->id_samochodu == id_samochodu)  /// Sprawdzenie czy samoch�d o podanym ID jest ju� wypo�yczony
        {
            printf("Ten samoch�d jest ju� wypo�yczony.\n");
            return;
        }
        wyp = wyp->next;    /// Przej�cie do nast�pnego wypo�yczenia
    }

    Wypozyczenie* nowe_wyp = (Wypozyczenie*)malloc(sizeof(Wypozyczenie));   /// Alokacja pami�ci dla nowego wypo�yczenia
    if (nowe_wyp == NULL)
    {
        printf("B��d alokacji pami�ci.\n");
        return;
    }

    nowe_wyp->id_samochodu = id_samochodu;  /// Ustawienie danych nowego wypo�yczenia
    nowe_wyp->numer_karty = numer_karty;
    nowe_wyp->next = glowa_wyp;
    glowa_wyp = nowe_wyp;   /// Dodanie nowego wypo�yczenia na pocz�tek listy wypo�ycze�

    FILE* plik = fopen("wypozyczanie.txt", "a");    /// Otwarcie pliku w trybie dopisywania
    if (plik == NULL)
    {
        printf("Nie uda�o si� otworzy� pliku wypozyczanie.txt.\n");
        return;
    }

    /// Zapisanie informacji o wypo�yczeniu do pliku
	fprintf(plik, "Wypo�yczenie:\n");
    fprintf(plik, "ID samochodu: %d\n", id_samochodu);
    fprintf(plik, "Nr rejestracyjny: %s\n", samochod->nr_rejestracyjny);
    fprintf(plik, "Marka: %s\n", samochod->marka);
    fprintf(plik, "Model: %s\n", samochod->model);
    fprintf(plik, "Rok produkcji: %d\n", samochod->rok_produkcji);
    fprintf(plik, "Kolor: %s\n", samochod->kolor);
    fprintf(plik, "Przebieg: %d\n", samochod->przebieg);
    fprintf(plik, "Numer karty klienta: %lld\n", numer_karty);
    fprintf(plik, "Imi� klienta: %s\n", klient->imie);
    fprintf(plik, "Nazwisko klienta: %s\n", klient->nazwisko);
    fprintf(plik, "Adres klienta: %s\n", klient->adres);
    fprintf(plik, "Telefon klienta: %lld\n", klient->telefon);
    fprintf(plik, "----------------------------------------\n");
    fclose(plik);

    samochod->wypozyczony = 1;

    printf("Samoch�d o ID %d zosta� wypo�yczony przez klienta o numerze karty %lld.\n", id_samochodu, numer_karty);
}