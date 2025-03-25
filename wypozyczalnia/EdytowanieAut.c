#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "WyswietlenieAut.h"
#include "EdytowanieAut.h"
#pragma warning(disable : 4996)

/**
 * Funkcja najpierw pobiera od u�ytkownika numer rejestracyjny samochodu, kt�ry chce edytowa�, a nast�pnie otwiera plik baza.txt
 * w trybie do odczytu i tworzy plik tymczasowy temp.txt w trybie do zapisu. Nast�pnie funkcja przechodzi przez ca�y plik baza.txt
 * i por�wnuje numer rejestracyjny ka�dego samochodu z podanym przez u�ytkownika numerem rejestracyjnym do edycji. Je�li zostanie
 * znaleziony samoch�d o podanym numerze rejestracyjnym, funkcja pobiera od u�ytkownika nowe dane samochodu (mark�, model, rok produkcji,
 * kolor, przebieg) i zapisuje je do pliku tymczasowego. Na koniec funkcja usuwa plik baza.txt i zmienia nazw� pliku tymczasowego na
 * baza.txt, aby zaktualizowa� dane samochodu w pliku. Je�li podany numer rejestracyjny nie odpowiada �adnemu samochodowi w pliku, funkcja
 * wy�wietli komunikat.
 *
 * \param glowa - Wska�nik na pierwszy element listy samochod�w.
 * \param szukane_id - ID samochodu, kt�ry ma zosta� edytowany.
 */
void edytuj_samochod(Auto* glowa, int szukane_id)
{
    Auto* bufor = glowa;    /// Inicjalizacja wska�nika bufor jako wska�nika na g�ow� listy

    while (bufor != NULL)   /// P�tla s�u��ca do iteracji po wszystkich elementach listy samochod�w
    {
        if (bufor->id == szukane_id)
        {
            char nr_rejestracyjny[20] = { 0 };
            char marka[20] = { 0 };
            char model[20] = { 0 };
            int rok_produkcji = 0;
            char kolor[30] = { 0 };
            int przebieg = 0;
				
            while (getchar() != '\n');  /// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
            printf("Podaj nowy nr rejestracyjny: ");
            fgets(nr_rejestracyjny, sizeof(nr_rejestracyjny), stdin);   /// Wprowadzanie numeru rejestracyjnego samochodu
            nr_rejestracyjny[strcspn(nr_rejestracyjny, "\n")] = '\0';   /// Usuwa znak nowej linii z ko�ca

            printf("Podaj now� mark�: ");
            fgets(marka, sizeof(marka), stdin); /// Wprowadzanie marki samochodu
            marka[strcspn(marka, "\n")] = '\0'; /// Usuwa znak nowej linii z ko�ca

            printf("Podaj nowy model: ");
            fgets(model, sizeof(model), stdin); /// Wprowadzanie modelu samochodu
            model[strcspn(model, "\n")] = '\0'; /// Usuwa znak nowej linii z ko�ca

            printf("Podaj nowy rok produkcji: ");
            scanf("%d", &rok_produkcji);    /// Wprowadzanie roku produkcji samochodu

            while (getchar() != '\n');  /// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
            printf("Podaj nowy kolor: ");
            fgets(kolor, sizeof(kolor), stdin); /// Wprowadzanie koloru samochodu
            kolor[strcspn(kolor, "\n")] = '\0'; /// Usuwa znak nowej linii z ko�ca

            printf("Podaj nowy przebieg: ");
            scanf("%d", &przebieg); /// Wprowadzanie przebiegu samochodu

            Auto* dodaj = glowa;    /// Inicjalizacja wska�nika dodaj na pocz�tek listy samochod�w
            while (dodaj != NULL)
            {
                if (dodaj->id == szukane_id)    /// Warunek sprawdzaj�cy czy wpisany samoch�d ma takie same ID
                {
                    strcpy(dodaj->nr_rejestracyjny, nr_rejestracyjny);  /// Aktualizacja numeru rejestracyjnego samochodu
                    strcpy(dodaj->marka, marka);    /// Aktualizacja marki samochodu
                    strcpy(dodaj->model, model);    /// Aktualizacja modelu samochodu
                    dodaj->rok_produkcji = rok_produkcji;   /// Aktualizacja roku produkcji samochodu
                    strcpy(dodaj->kolor, kolor);    /// Aktualizacja koloru samochodu
                    dodaj->przebieg = przebieg; /// Aktualizacja przebiegu samochodu
                    break;  /// Przerwanie
                }
                dodaj = dodaj->next;    /// Przesuni�cie wska�nika dodaj na nast�pny element listy samochod�w
            }

            FILE* plik_zapis = fopen("baza.txt", "w");  /// Otwarcie pliku baza.txt w trybie zapisu
            if (plik_zapis == NULL)
            {
                printf("Nie uda�o si� otworzy� pliku z samochodami.\n");
                return;
            }
            dodaj = glowa;  /// Ustawienie wska�nika dodaj na pocz�tek listy samochod�w
            while (dodaj != NULL)
            {
                fprintf(plik_zapis, "%d \t%s \t%s \t%s \t%d \t%s \t%d\n",
                    dodaj->id, dodaj->nr_rejestracyjny, dodaj->marka, dodaj->model, dodaj->rok_produkcji, dodaj->kolor, dodaj->przebieg);/// Zapisywanie danych samochod�w do pliku baza.txt
                dodaj = dodaj->next; /// Przesuni�cie wska�nika dodaj na nast�pny element listy
            }

            fclose(plik_zapis); /// Zamkni�cie pliku

            printf("Dane samochodu o ID %d zosta�y zaktualizowane.\n", szukane_id); /// Wy�wietlenie komunikatu o zaktualizowaniu listy samochod�w
            return;
        }

        bufor = bufor->next;    /// Przesuni�cie wska�nika bufor na nast�pny element listy samochod�w
    }

    printf("Nie znaleziono samochodu o podanym ID.\n"); /// Wy�wietlenie komunikatu w przypadku nieznalezienia samochodu na li�cie
}