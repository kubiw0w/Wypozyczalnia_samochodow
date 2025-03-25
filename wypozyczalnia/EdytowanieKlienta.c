#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>				
#include "WyswietlenieKlientow.h"
#include "EdytowanieKlienta.h"
#pragma warning(disable : 4996)

/**
 * Funkcja umo¿liwia edycjê danych klienta na podstawie numeru karty. Na pocz¹tku funkcja deklaruje zmienne i wskaŸniki plikowe,
 * tworzy pust¹ listê head. Nastêpnie u¿ytkownik jest proszony o podanie numeru karty klienta,
 * którego chce edytowaæ. Funkcja otwiera plik klienci.txt do odczytu. Nastêpnie funkcja otwiera plik tymczasowy temp.txt do zapisu.
 * Nastêpuje iteracja przez plik klienci.txt. Dla ka¿dego klienta odczytywane s¹ dane: numer karty, imiê, nazwisko, adres i numer
 * telefonu. Jeœli numer karty odczytany z pliku odpowiada numerowi karty do edycji, u¿ytkownik jest proszony o podanie nowych danych:
 * imienia, nazwiska, adresu i numeru telefonu. Nastêpnie zapisywane s¹ zaktualizowane dane klienta do pliku tymczasowego.
 * Ka¿dy klient jest równie¿ dodawany na pocz¹tek listy dwukierunkowej head. Po zakoñczeniu iteracji, plik klienci.txt jest zamykany,
 * a plik tymczasowy temp.txt jest zamykany i zamieniany nazwê na klienci.txt. Efektem dzia³ania tej funkcji jest edycja danych klienta
 * na podstawie numeru karty.
 *
 * \param glowa - WskaŸnik na pierwszy element listy klientów.
 * \param szukany_numer_karty - Numer karty klienta, który ma zostaæ edytowany.
 */
void edytuj_klienta(Klient* glowa, long long int szukany_numer_karty)   /// Funkcja s³u¿¹ca do edycji danych klienta
{
    Klient* bufor = glowa;  /// Ustawienie wskaŸnika bufor na pocz¹tek listy klientów

    while (bufor != NULL)   /// Pêtla iteruj¹ca po wszystkich elementach listy klientów
    {
        if (bufor->numer_karty == szukany_numer_karty)  /// Warunek jeœli numer karty klienta pasuje do szukanego numeru karty
        {
            char imie[20] = { 0 };
            char nazwisko[20] = { 0 };
            char adres[50] = { 0 };
            long long int telefon = 0;

            while (getchar() != '\n');  /// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
            printf("Podaj nowe imiê: ");
            fgets(imie, sizeof(imie), stdin);   /// Wprowadzanie imienia klienta
            imie[strcspn(imie, "\n")] = '\0';   /// Usuwa znak nowej linii z koñca

            printf("Podaj nowe nazwisko: ");
            fgets(nazwisko, sizeof(nazwisko), stdin);   /// Wprowadzanie nazwiska klienta
            nazwisko[strcspn(nazwisko, "\n")] = '\0';   /// Usuwa znak nowej linii z koñca

            printf("Podaj nowy adres: ");
            fgets(adres, sizeof(adres), stdin); /// Wprowadzanie adresu klienta
            adres[strcspn(adres, "\n")] = '\0'; /// Usuwa znak nowej linii z koñca

            printf("Podaj nowy numer telefonu: ");
            scanf("%lld", &telefon);    /// Wprowadzanie numeru telefonu klienta

            Klient* dodaj = glowa;  /// Ustawienie wskaŸnika dodaj na pocz¹tek listy klientów
            while (dodaj != NULL)   /// Pêtla dopóki dodaj nie osi¹gnie koñca listy
            {
                if (dodaj->numer_karty == szukany_numer_karty)  /// Warunek jeœli numer karty klienta pasuje do szukanego numeru klienta
                {
                    strcpy(dodaj->imie, imie);  /// Skopiowanie nowego imienia do struktury klienta
                    strcpy(dodaj->nazwisko, nazwisko);  /// Skopiowanie nowego nazwiska do struktury klienta
                    strcpy(dodaj->adres, adres);    /// Skopiowanie nowego adresu do struktury klienta    
                    dodaj->telefon = telefon;   /// Przypisanie nowego numeru telefonu do struktury klienta
                    break;  /// Przerwanie
                }
                dodaj = dodaj->next;    /// Przesuniêcie wskaŸnika dodaj na kolejnego klienta w liœcie
            }   

            FILE* plik_zapis = fopen("klienci.txt", "w");   /// Otwarcie pliku klienci.txt w trybie do zapisu
            if (plik_zapis == NULL)
            {
                printf("Nie uda³o siê otworzyæ pliku z klientami.\n");
                return;
            }
            dodaj = glowa;  /// Przywrócenie wskaŸnika dodaj na pocz¹tek listy klientów
            while (dodaj != NULL) /// Pêtla dopóki dodaj nie osi¹gnie koñca listy
            {
                fprintf(plik_zapis, "%lld \t%s \t%s \t%s \t%lld\n",
                    dodaj->numer_karty, dodaj->imie, dodaj->nazwisko, dodaj->adres, dodaj->telefon);    /// Zapisanie danych klienta do pliku
                dodaj = dodaj->next;    /// Przesuniêcie wskaŸnika dodaj na kolejnego klienta w liœcie
            }

            fclose(plik_zapis); /// Zamkniêcie pliku

            printf("Dane klienta o numerze karty %lld zosta³y zaktualizowane.\n", szukany_numer_karty); /// Wyœwietlenie informacji o zaktualizowanych danych klienta
            return;
        }

        bufor = bufor->next;    /// Przesuniêcie wskaŸnika bufor na kolejnego klienta w liœcie
    }

    printf("Nie znaleziono klienta o podanym numerze karty.\n");    /// Wyœwietlenie informacji o nieznalezionym kliencie
}
