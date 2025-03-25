#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>		
#include "UsuwanieKlientow.h"
#pragma warning(disable : 4996)		

/**
 * Funkcja kt�ra s�u�y do usuwania klienta na podstawie numeru karty. Na pocz�tku funkcja otwiera pliki wej�ciowy
 * klienci.txt i wyj�ciowy temp.txt do odpowiednich operacji odczytu i zapisu. Plik wypozyczanie.txt jest otwierany do odczytu.
 * Je�li otwarcie tego pliku powiedzie si�, funkcja iteruje przez ka�d� odczytan� lini� i sprawdza, czy zawiera podany numer
 * karty. Je�li tak, ustawiana jest flaga wypozycza_samochod na 1 i p�tla jest przerywana. Po zako�czeniu iteracji plik wypozyczanie.txt
 * jest zamykany. Nast�pnie funkcja iteruje przez plik wej�ciowy klienci.txt. Dla ka�dej odczytanej linii parsuje dane klienta:
 * numer karty, imi�, nazwisko, adres i numer telefonu. Je�li numer karty odczytany z pliku jest r�wny podanemu numerowi karty,
 * ustawiana jest flaga znaleziono na 1 i kontynuowana jest kolejna iteracja bez zapisywania danej linii do pliku wyj�ciowego.
 * W przeciwnym przypadku linia jest zapisywana do pliku wyj�ciowego. Po zako�czeniu iteracji pliki s� zamykane. Je�li flaga
 * znaleziono jest r�wna 1, oznacza to, �e klient zosta� znaleziony i usuni�ty. Plik klienci.txt jest usuwany, a plik tymczasowy
 * temp.txt jest zmieniany nazw� na klienci.txt. Wy�wietlany jest komunikat potwierdzaj�cy usuni�cie klienta. Je�li flaga znaleziono
 * jest r�wna 0, oznacza to, �e klient o podanym numerze karty nie zosta� znaleziony. Plik tymczasowy temp.txt jest usuwany i wy�wietlany
 * jest odpowiedni komunikat. Efektem dzia�ania tej funkcji jest usuni�cie klienta na podstawie numeru karty, je�li taki klient istnieje
 * i nie wypo�ycza samochodu.
 *
 * \param nr_karty - Numer karty klienta do usuni�cia.
 */
void usun_klienta(const char* nr_karty)
{
    FILE* plik_wejscie = fopen("klienci.txt", "r"); /// Otwarcie pliku "klienci.txt" w trybie odczytu
    FILE* plik_wyjscie = fopen("temp.txt", "w");    /// Otwarcie pliku "temp.txt" w trybie zapisu

    if (plik_wejscie == NULL || plik_wyjscie == NULL)   /// Sprawdzenie, czy uda�o si� otworzy� pliki
    {
        printf("Nie uda�o si� otworzy� plik�w.\n");
        return;
    }

    char linia[100];
    int znaleziono = 0;
    int wypozycza_samochod = 0;

    FILE* plik_wypozyczenie = fopen("wypozyczanie.txt", "r");   /// Otwarcie pliku "wypozyczanie.txt" w trybie odczytu
    if (plik_wypozyczenie != NULL)  
    {
        while (fgets(linia, sizeof(linia), plik_wypozyczenie) != NULL)  ///Wczytywanie linii z pliku "wypozyczanie.txt"
        {
            if (strstr(linia, nr_karty) != NULL)    /// Sprawdzenie, czy linia zawiera numer karty klienta
            {
                wypozycza_samochod = 1;
                break;
            }
        }
        fclose(plik_wypozyczenie);  /// Zamkni�cie pliku "wypozyczanie.txt"
    }

    if (wypozycza_samochod) /// Sprawdzenie, czy klient wypo�ycza samoch�d
    {
        printf("Nie mo�esz usun�� klienta, poniewa� wypo�ycza on samoch�d!\n");
        fclose(plik_wejscie);   /// Zamkni�cie pliku "klienci.txt"
        fclose(plik_wyjscie);   /// Zamkni�cie pliku "temp.txt"
        remove("temp.txt"); /// Usuni�cie pliku "temp.txt"
        return;
    }

    while (fgets(linia, sizeof(linia), plik_wejscie))   /// Wczytywanie linii z pliku "klienci.txt"
    {
        char numer_karty[20];
        char imie[20];
        char nazwisko[20];
        char adres[50];
        char telefon[20];

        sscanf(linia, "%s \t%s \t%s \t%s \t%s", numer_karty, imie, nazwisko, adres, telefon);   /// Wczytanie danych z linii do odpowiednich bufor�w

        if (strcmp(numer_karty, nr_karty) == 0) /// Por�wnanie numeru karty z numerem karty klienta do usuni�cia
        {
            znaleziono = 1;
            continue;
        }

        fputs(linia, plik_wyjscie); /// Zapisanie bie��cej linii do pliku wyj�ciowego
    }

    fclose(plik_wejscie);   /// Zamkni�cie pliku "klienci.txt"
    fclose(plik_wyjscie);   /// Zamkni�cie pliku "temp.txt"

    if (znaleziono) /// Sprawdzenie, czy znaleziono klienta do usuni�cia
    {
        remove("klienci.txt");  /// Usuni�cie pliku "klienci.txt"
        rename("temp.txt", "klienci.txt");  /// Zmiana nazwy pliku "temp.txt" na "klienci.txt"
        printf("Klient o podanym numerze karty zosta� usuni�ty.\n");    
    }
    else
    {
        remove("temp.txt"); /// Usuni�cie pliku "temp.txt"
        printf("Nie znaleziono klienta o podanym numerze karty.\n");
    }
}