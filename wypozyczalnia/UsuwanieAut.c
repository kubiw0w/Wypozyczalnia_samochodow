#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "UsuwanieAut.h"
#pragma warning(disable : 4996)	

/**
 * Funkcja usu� s�u�y do usuwania danych o samochodach z pliku tekstowego o nazwie baza.txt. W tym celu u�ytkownik wprowadza
 * numer rejestracyjny samochodu, kt�ry ma zosta� usuni�ty. Funkcja wczytuje dane z pliku baza.txt i por�wnuje numer rejestracyjny
 * z wprowadzonym przez u�ytkownika numerem. Je�li numery si� zgadzaj�, funkcja pomija ten samoch�d i wy�wietla informacj� o usuni�ciu.
 * Je�li numery si� nie zgadzaj�, funkcja zapisuje dane o samochodzie do pliku tymczasowego temp i tworzy nowy w�ze� listy
 * dwukierunkowej zawieraj�cej te same dane. W przypadku niepowodzenia kt�rego� z tych dzia�a�, funkcja wy�wietli b��d.
 *
 * \param nr_rejestracyjny - Numer rejestracyjny samochodu do usuni�cia.
 */
void usun_samochod(const char* nr_rejestracyjny)
{
    FILE* plik_wejscie = fopen("baza.txt", "r");    /// Otwarcie pliku "baza.txt" w trybie do odczytu
    FILE* plik_wyjscie = fopen("temp.txt", "w");    /// Otwarcie pliku "temp.txt" w trybie do zapisu

    if (plik_wejscie == NULL || plik_wyjscie == NULL)   /// Sprawdzenie, czy uda�o si� otworzy� pliki
    {
        printf("Nie uda�o si� otworzy� plik�w.\n");
        return;
    }

    char linia[256];
    int znaleziono = 0;
    int wypozyczony = 0;

    FILE* plik_wypozyczenie = fopen("wypozyczanie.txt", "r");   /// Otwarcie pliku "wypozyczanie.txt" w trybie do odczytu
    if (plik_wypozyczenie != NULL)  /// Sprawdzenie, czy uda�o si� otworzy� plik "wypozyczanie.txt"
    {
        while (fgets(linia, sizeof(linia), plik_wypozyczenie) != NULL)  /// Odczyt kolejnych linii z pliku "wypozyczanie.txt"
        {
            if (strstr(linia, nr_rejestracyjny) != NULL)    /// Sprawdzenie, czy linia zawiera podany numer rejestracyjny
            {
                wypozyczony = 1;
                break;
            }
        }
        fclose(plik_wypozyczenie);  /// Zamkni�cie pliku "wypozyczanie.txt"
    }

    if (wypozyczony)    /// Sprawdzenie, czy samoch�d jest wypo�yczony
    {
        printf("Nie mo�na usun�� wypo�yczonego samochodu!\n");
        fclose(plik_wejscie);   /// Zamkni�cie pliku "baza.txt"
        fclose(plik_wyjscie);   /// Zamkni�cie pliku "temp.txt"
        remove("temp.txt"); /// Usuni�cie pliku "temp.txt"
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

    fclose(plik_wejscie);   /// Zamkni�cie pliku "baza.txt"
    fclose(plik_wyjscie);   /// Zamkni�cie pliku "temp.txt"

    if (znaleziono) /// Sprawdzenie, czy znaleziono samoch�d o podanym numerze rejestracyjnym
    {
        remove("baza.txt"); /// Usuni�cie pliku "baza.txt"
        rename("temp.txt", "baza.txt"); /// Zmiana nazwy pliku "temp.txt" na "baza.txt"
        printf("Samoch�d zosta� usuni�ty z bazy.\n");
    }
    else
    {
        remove("temp.txt"); /// Usuni�cie pliku "temp.txt"
        printf("Nie znaleziono samochodu o podanym numerze rejestracyjnym.\n");
    }
}