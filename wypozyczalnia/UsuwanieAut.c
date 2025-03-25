#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "UsuwanieAut.h"
#pragma warning(disable : 4996)	

/**
 * Funkcja usuñ s³u¿y do usuwania danych o samochodach z pliku tekstowego o nazwie baza.txt. W tym celu u¿ytkownik wprowadza
 * numer rejestracyjny samochodu, który ma zostaæ usuniêty. Funkcja wczytuje dane z pliku baza.txt i porównuje numer rejestracyjny
 * z wprowadzonym przez u¿ytkownika numerem. Jeœli numery siê zgadzaj¹, funkcja pomija ten samochód i wyœwietla informacjê o usuniêciu.
 * Jeœli numery siê nie zgadzaj¹, funkcja zapisuje dane o samochodzie do pliku tymczasowego temp i tworzy nowy wêze³ listy
 * dwukierunkowej zawieraj¹cej te same dane. W przypadku niepowodzenia któregoœ z tych dzia³añ, funkcja wyœwietli b³¹d.
 *
 * \param nr_rejestracyjny - Numer rejestracyjny samochodu do usuniêcia.
 */
void usun_samochod(const char* nr_rejestracyjny)
{
    FILE* plik_wejscie = fopen("baza.txt", "r");    /// Otwarcie pliku "baza.txt" w trybie do odczytu
    FILE* plik_wyjscie = fopen("temp.txt", "w");    /// Otwarcie pliku "temp.txt" w trybie do zapisu

    if (plik_wejscie == NULL || plik_wyjscie == NULL)   /// Sprawdzenie, czy uda³o siê otworzyæ pliki
    {
        printf("Nie uda³o siê otworzyæ plików.\n");
        return;
    }

    char linia[256];
    int znaleziono = 0;
    int wypozyczony = 0;

    FILE* plik_wypozyczenie = fopen("wypozyczanie.txt", "r");   /// Otwarcie pliku "wypozyczanie.txt" w trybie do odczytu
    if (plik_wypozyczenie != NULL)  /// Sprawdzenie, czy uda³o siê otworzyæ plik "wypozyczanie.txt"
    {
        while (fgets(linia, sizeof(linia), plik_wypozyczenie) != NULL)  /// Odczyt kolejnych linii z pliku "wypozyczanie.txt"
        {
            if (strstr(linia, nr_rejestracyjny) != NULL)    /// Sprawdzenie, czy linia zawiera podany numer rejestracyjny
            {
                wypozyczony = 1;
                break;
            }
        }
        fclose(plik_wypozyczenie);  /// Zamkniêcie pliku "wypozyczanie.txt"
    }

    if (wypozyczony)    /// Sprawdzenie, czy samochód jest wypo¿yczony
    {
        printf("Nie mo¿na usun¹æ wypo¿yczonego samochodu!\n");
        fclose(plik_wejscie);   /// Zamkniêcie pliku "baza.txt"
        fclose(plik_wyjscie);   /// Zamkniêcie pliku "temp.txt"
        remove("temp.txt"); /// Usuniêcie pliku "temp.txt"
        return;
    }

    while (fgets(linia, sizeof(linia), plik_wejscie) != NULL)   /// Odczyt kolejnych linii z pliku "baza.txt"
    {
        if (strstr(linia, nr_rejestracyjny) != NULL)    /// Sprawdzenie, czy linia zawiera podany numer rejestracyjny
        {
            znaleziono = 1;
            continue;
        }

        fputs(linia, plik_wyjscie); ///Zapisanie linii do pliku "temp.txt"
    }

    fclose(plik_wejscie);   /// Zamkniêcie pliku "baza.txt"
    fclose(plik_wyjscie);   /// Zamkniêcie pliku "temp.txt"

    if (znaleziono) /// Sprawdzenie, czy znaleziono samochód o podanym numerze rejestracyjnym
    {
        remove("baza.txt"); /// Usuniêcie pliku "baza.txt"
        rename("temp.txt", "baza.txt"); /// Zmiana nazwy pliku "temp.txt" na "baza.txt"
        printf("Samochód zosta³ usuniêty z bazy.\n");
    }
    else
    {
        remove("temp.txt"); /// Usuniêcie pliku "temp.txt"
        printf("Nie znaleziono samochodu o podanym numerze rejestracyjnym.\n");
    }
}