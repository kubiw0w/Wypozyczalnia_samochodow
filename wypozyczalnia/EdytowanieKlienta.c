#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>				
#include "WyswietlenieKlientow.h"
#include "EdytowanieKlienta.h"
#pragma warning(disable : 4996)

/**
 * Funkcja umo�liwia edycj� danych klienta na podstawie numeru karty. Na pocz�tku funkcja deklaruje zmienne i wska�niki plikowe,
 * tworzy pust� list� head. Nast�pnie u�ytkownik jest proszony o podanie numeru karty klienta,
 * kt�rego chce edytowa�. Funkcja otwiera plik klienci.txt do odczytu. Nast�pnie funkcja otwiera plik tymczasowy temp.txt do zapisu.
 * Nast�puje iteracja przez plik klienci.txt. Dla ka�dego klienta odczytywane s� dane: numer karty, imi�, nazwisko, adres i numer
 * telefonu. Je�li numer karty odczytany z pliku odpowiada numerowi karty do edycji, u�ytkownik jest proszony o podanie nowych danych:
 * imienia, nazwiska, adresu i numeru telefonu. Nast�pnie zapisywane s� zaktualizowane dane klienta do pliku tymczasowego.
 * Ka�dy klient jest r�wnie� dodawany na pocz�tek listy dwukierunkowej head. Po zako�czeniu iteracji, plik klienci.txt jest zamykany,
 * a plik tymczasowy temp.txt jest zamykany i zamieniany nazw� na klienci.txt. Efektem dzia�ania tej funkcji jest edycja danych klienta
 * na podstawie numeru karty.
 *
 * \param glowa - Wska�nik na pierwszy element listy klient�w.
 * \param szukany_numer_karty - Numer karty klienta, kt�ry ma zosta� edytowany.
 */
void edytuj_klienta(Klient* glowa, long long int szukany_numer_karty)   /// Funkcja s�u��ca do edycji danych klienta
{
    Klient* bufor = glowa;  /// Ustawienie wska�nika bufor na pocz�tek listy klient�w

    while (bufor != NULL)   /// P�tla iteruj�ca po wszystkich elementach listy klient�w
    {
        if (bufor->numer_karty == szukany_numer_karty)  /// Warunek je�li numer karty klienta pasuje do szukanego numeru karty
        {
            char imie[20] = { 0 };
            char nazwisko[20] = { 0 };
            char adres[50] = { 0 };
            long long int telefon = 0;

            while (getchar() != '\n');  /// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
            printf("Podaj nowe imi�: ");
            fgets(imie, sizeof(imie), stdin);   /// Wprowadzanie imienia klienta
            imie[strcspn(imie, "\n")] = '\0';   /// Usuwa znak nowej linii z ko�ca

            printf("Podaj nowe nazwisko: ");
            fgets(nazwisko, sizeof(nazwisko), stdin);   /// Wprowadzanie nazwiska klienta
            nazwisko[strcspn(nazwisko, "\n")] = '\0';   /// Usuwa znak nowej linii z ko�ca

            printf("Podaj nowy adres: ");
            fgets(adres, sizeof(adres), stdin); /// Wprowadzanie adresu klienta
            adres[strcspn(adres, "\n")] = '\0'; /// Usuwa znak nowej linii z ko�ca

            printf("Podaj nowy numer telefonu: ");
            scanf("%lld", &telefon);    /// Wprowadzanie numeru telefonu klienta

            Klient* dodaj = glowa;  /// Ustawienie wska�nika dodaj na pocz�tek listy klient�w
            while (dodaj != NULL)   /// P�tla dop�ki dodaj nie osi�gnie ko�ca listy
            {
                if (dodaj->numer_karty == szukany_numer_karty)  /// Warunek je�li numer karty klienta pasuje do szukanego numeru klienta
                {
                    strcpy(dodaj->imie, imie);  /// Skopiowanie nowego imienia do struktury klienta
                    strcpy(dodaj->nazwisko, nazwisko);  /// Skopiowanie nowego nazwiska do struktury klienta
                    strcpy(dodaj->adres, adres);    /// Skopiowanie nowego adresu do struktury klienta    
                    dodaj->telefon = telefon;   /// Przypisanie nowego numeru telefonu do struktury klienta
                    break;  /// Przerwanie
                }
                dodaj = dodaj->next;    /// Przesuni�cie wska�nika dodaj na kolejnego klienta w li�cie
            }   

            FILE* plik_zapis = fopen("klienci.txt", "w");   /// Otwarcie pliku klienci.txt w trybie do zapisu
            if (plik_zapis == NULL)
            {
                printf("Nie uda�o si� otworzy� pliku z klientami.\n");
                return;
            }
            dodaj = glowa;  /// Przywr�cenie wska�nika dodaj na pocz�tek listy klient�w
            while (dodaj != NULL) /// P�tla dop�ki dodaj nie osi�gnie ko�ca listy
            {
                fprintf(plik_zapis, "%lld \t%s \t%s \t%s \t%lld\n",
                    dodaj->numer_karty, dodaj->imie, dodaj->nazwisko, dodaj->adres, dodaj->telefon);    /// Zapisanie danych klienta do pliku
                dodaj = dodaj->next;    /// Przesuni�cie wska�nika dodaj na kolejnego klienta w li�cie
            }

            fclose(plik_zapis); /// Zamkni�cie pliku

            printf("Dane klienta o numerze karty %lld zosta�y zaktualizowane.\n", szukany_numer_karty); /// Wy�wietlenie informacji o zaktualizowanych danych klienta
            return;
        }

        bufor = bufor->next;    /// Przesuni�cie wska�nika bufor na kolejnego klienta w li�cie
    }

    printf("Nie znaleziono klienta o podanym numerze karty.\n");    /// Wy�wietlenie informacji o nieznalezionym kliencie
}
