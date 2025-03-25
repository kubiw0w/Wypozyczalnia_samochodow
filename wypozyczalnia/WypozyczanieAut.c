#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "WyswietlenieAut.h"
#include "WyswietlenieKlientow.h"
#include "WypozyczanieAut.h"
#pragma warning(disable : 4996)

typedef struct Wypozyczenie {
    int id_samochodu; /**< ID wypo¿yczonego samochodu. */
    long long int numer_karty; /**< Numer karty klienta. */
    struct Wypozyczenie* next; /**< WskaŸnik na nastêpny element listy. */
} Wypozyczenie;

Wypozyczenie* glowa_wyp = NULL; /**< WskaŸnik na g³owê listy wypo¿yczeñ. Zmienna wskazuje na g³owê listy wypo¿yczeñ (glowa_wyp), która przechowuje informacje o wypo¿yczonych samochodach. Na pocz¹tku programu inicjalizowana jako NULL, a nastêpnie u¿ywana do dodawania i zarz¹dzania wypo¿yczeniami. */

/**
 * Funkcja pobiera od u¿ytkownika ID samochodu i numer karty klienta, a nastêpnie sprawdza, czy oba s¹ poprawne.
 * Jeœli tak, tworzy nowe wypo¿yczenie, dodaje je do listy wypo¿yczeñ, zapisuje informacje o wypo¿yczeniu do pliku,
 * oznacza samochód jako wypo¿yczony i wyœwietla odpowiednie komunikaty.
 *
 * \param glowa_aut - WskaŸnik na g³owê listy samochodów.
 * \param glowa_kl - WskaŸnik na g³owê listy klientów.
 */
void wypozycz_samochod(Auto* glowa_aut, Klient* glowa_kl)
{
    int id_samochodu;
    long long int numer_karty;

    printf("Podaj ID samochodu do wypo¿yczenia: ");
    scanf("%d", &id_samochodu); /// Wprowadzanie ID samochodu

    printf("Podaj numer karty klienta: ");
    scanf("%lld", &numer_karty);    /// Wprowadzanie numeru karty klienta

    Auto* samochod = glowa_aut; /// Ustawienie wskaŸnika samochod na g³owê listy samochodów
    Klient* klient = glowa_kl;  /// Ustawienie wskaŸnika klient na g³owê listy klientów

    while (samochod != NULL)
    {
        if (samochod->id == id_samochodu)   /// Sprawdzenie czy ID samochodu zgadza siê z podanym ID
            break;
        samochod = samochod->next;  /// Przejœcie do nastêpnego samochodu
    }

    while (klient != NULL)
    {
        if (klient->numer_karty == numer_karty) /// Sprawdzenie czy numer karty klienta zgadza siê z podanym numerem karty
            break;
        klient = klient->next;  /// Przejœcie do nastêpnego klienta
    }

    if (samochod == NULL)   /// Je¿eli nie znaleziono samochodu o podanym ID
    {
        printf("Nie znaleziono samochodu o podanym ID.\n");
        return;
    }

    if (klient == NULL) /// Je¿eli nie znaleziono klienta o podanym numerze karty
    {
        printf("Nie znaleziono klienta o podanym numerze karty.\n");
        return;
    }

    Wypozyczenie* wyp = glowa_wyp;  /// Ustawienie wskaŸnika wyp na g³owê listy wypo¿yczeñ
    while (wyp != NULL)
    {
        if (wyp->id_samochodu == id_samochodu)  /// Sprawdzenie czy samochód o podanym ID jest ju¿ wypo¿yczony
        {
            printf("Ten samochód jest ju¿ wypo¿yczony.\n");
            return;
        }
        wyp = wyp->next;    /// Przejœcie do nastêpnego wypo¿yczenia
    }

    Wypozyczenie* nowe_wyp = (Wypozyczenie*)malloc(sizeof(Wypozyczenie));   /// Alokacja pamiêci dla nowego wypo¿yczenia
    if (nowe_wyp == NULL)
    {
        printf("B³¹d alokacji pamiêci.\n");
        return;
    }

    nowe_wyp->id_samochodu = id_samochodu;  /// Ustawienie danych nowego wypo¿yczenia
    nowe_wyp->numer_karty = numer_karty;
    nowe_wyp->next = glowa_wyp;
    glowa_wyp = nowe_wyp;   /// Dodanie nowego wypo¿yczenia na pocz¹tek listy wypo¿yczeñ

    FILE* plik = fopen("wypozyczanie.txt", "a");    /// Otwarcie pliku w trybie dopisywania
    if (plik == NULL)
    {
        printf("Nie uda³o siê otworzyæ pliku wypozyczanie.txt.\n");
        return;
    }

    /// Zapisanie informacji o wypo¿yczeniu do pliku
	fprintf(plik, "Wypo¿yczenie:\n");
    fprintf(plik, "ID samochodu: %d\n", id_samochodu);
    fprintf(plik, "Nr rejestracyjny: %s\n", samochod->nr_rejestracyjny);
    fprintf(plik, "Marka: %s\n", samochod->marka);
    fprintf(plik, "Model: %s\n", samochod->model);
    fprintf(plik, "Rok produkcji: %d\n", samochod->rok_produkcji);
    fprintf(plik, "Kolor: %s\n", samochod->kolor);
    fprintf(plik, "Przebieg: %d\n", samochod->przebieg);
    fprintf(plik, "Numer karty klienta: %lld\n", numer_karty);
    fprintf(plik, "Imiê klienta: %s\n", klient->imie);
    fprintf(plik, "Nazwisko klienta: %s\n", klient->nazwisko);
    fprintf(plik, "Adres klienta: %s\n", klient->adres);
    fprintf(plik, "Telefon klienta: %lld\n", klient->telefon);
    fprintf(plik, "----------------------------------------\n");
    fclose(plik);

    samochod->wypozyczony = 1;

    printf("Samochód o ID %d zosta³ wypo¿yczony przez klienta o numerze karty %lld.\n", id_samochodu, numer_karty);
}