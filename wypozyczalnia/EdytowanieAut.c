#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "WyswietlenieAut.h"
#include "EdytowanieAut.h"
#pragma warning(disable : 4996)

/**
 * Funkcja najpierw pobiera od u¿ytkownika numer rejestracyjny samochodu, który chce edytowaæ, a nastêpnie otwiera plik baza.txt
 * w trybie do odczytu i tworzy plik tymczasowy temp.txt w trybie do zapisu. Nastêpnie funkcja przechodzi przez ca³y plik baza.txt
 * i porównuje numer rejestracyjny ka¿dego samochodu z podanym przez u¿ytkownika numerem rejestracyjnym do edycji. Jeœli zostanie
 * znaleziony samochód o podanym numerze rejestracyjnym, funkcja pobiera od u¿ytkownika nowe dane samochodu (markê, model, rok produkcji,
 * kolor, przebieg) i zapisuje je do pliku tymczasowego. Na koniec funkcja usuwa plik baza.txt i zmienia nazwê pliku tymczasowego na
 * baza.txt, aby zaktualizowaæ dane samochodu w pliku. Jeœli podany numer rejestracyjny nie odpowiada ¿adnemu samochodowi w pliku, funkcja
 * wyœwietli komunikat.
 *
 * \param glowa - WskaŸnik na pierwszy element listy samochodów.
 * \param szukane_id - ID samochodu, który ma zostaæ edytowany.
 */
void edytuj_samochod(Auto* glowa, int szukane_id)
{
    Auto* bufor = glowa;    /// Inicjalizacja wskaŸnika bufor jako wskaŸnika na g³owê listy

    while (bufor != NULL)   /// Pêtla s³u¿¹ca do iteracji po wszystkich elementach listy samochodów
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
            nr_rejestracyjny[strcspn(nr_rejestracyjny, "\n")] = '\0';   /// Usuwa znak nowej linii z koñca

            printf("Podaj now¹ markê: ");
            fgets(marka, sizeof(marka), stdin); /// Wprowadzanie marki samochodu
            marka[strcspn(marka, "\n")] = '\0'; /// Usuwa znak nowej linii z koñca

            printf("Podaj nowy model: ");
            fgets(model, sizeof(model), stdin); /// Wprowadzanie modelu samochodu
            model[strcspn(model, "\n")] = '\0'; /// Usuwa znak nowej linii z koñca

            printf("Podaj nowy rok produkcji: ");
            scanf("%d", &rok_produkcji);    /// Wprowadzanie roku produkcji samochodu

            while (getchar() != '\n');  /// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
            printf("Podaj nowy kolor: ");
            fgets(kolor, sizeof(kolor), stdin); /// Wprowadzanie koloru samochodu
            kolor[strcspn(kolor, "\n")] = '\0'; /// Usuwa znak nowej linii z koñca

            printf("Podaj nowy przebieg: ");
            scanf("%d", &przebieg); /// Wprowadzanie przebiegu samochodu

            Auto* dodaj = glowa;    /// Inicjalizacja wskaŸnika dodaj na pocz¹tek listy samochodów
            while (dodaj != NULL)
            {
                if (dodaj->id == szukane_id)    /// Warunek sprawdzaj¹cy czy wpisany samochód ma takie same ID
                {
                    strcpy(dodaj->nr_rejestracyjny, nr_rejestracyjny);  /// Aktualizacja numeru rejestracyjnego samochodu
                    strcpy(dodaj->marka, marka);    /// Aktualizacja marki samochodu
                    strcpy(dodaj->model, model);    /// Aktualizacja modelu samochodu
                    dodaj->rok_produkcji = rok_produkcji;   /// Aktualizacja roku produkcji samochodu
                    strcpy(dodaj->kolor, kolor);    /// Aktualizacja koloru samochodu
                    dodaj->przebieg = przebieg; /// Aktualizacja przebiegu samochodu
                    break;  /// Przerwanie
                }
                dodaj = dodaj->next;    /// Przesuniêcie wskaŸnika dodaj na nastêpny element listy samochodów
            }

            FILE* plik_zapis = fopen("baza.txt", "w");  /// Otwarcie pliku baza.txt w trybie zapisu
            if (plik_zapis == NULL)
            {
                printf("Nie uda³o siê otworzyæ pliku z samochodami.\n");
                return;
            }
            dodaj = glowa;  /// Ustawienie wskaŸnika dodaj na pocz¹tek listy samochodów
            while (dodaj != NULL)
            {
                fprintf(plik_zapis, "%d \t%s \t%s \t%s \t%d \t%s \t%d\n",
                    dodaj->id, dodaj->nr_rejestracyjny, dodaj->marka, dodaj->model, dodaj->rok_produkcji, dodaj->kolor, dodaj->przebieg);/// Zapisywanie danych samochodów do pliku baza.txt
                dodaj = dodaj->next; /// Przesuniêcie wskaŸnika dodaj na nastêpny element listy
            }

            fclose(plik_zapis); /// Zamkniêcie pliku

            printf("Dane samochodu o ID %d zosta³y zaktualizowane.\n", szukane_id); /// Wyœwietlenie komunikatu o zaktualizowaniu listy samochodów
            return;
        }

        bufor = bufor->next;    /// Przesuniêcie wskaŸnika bufor na nastêpny element listy samochodów
    }

    printf("Nie znaleziono samochodu o podanym ID.\n"); /// Wyœwietlenie komunikatu w przypadku nieznalezienia samochodu na liœcie
}