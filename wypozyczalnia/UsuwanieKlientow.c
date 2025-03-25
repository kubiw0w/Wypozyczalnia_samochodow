#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>		
#include "UsuwanieKlientow.h"
#pragma warning(disable : 4996)		

/**
 * Funkcja która s³u¿y do usuwania klienta na podstawie numeru karty. Na pocz¹tku funkcja otwiera pliki wejœciowy
 * klienci.txt i wyjœciowy temp.txt do odpowiednich operacji odczytu i zapisu. Plik wypozyczanie.txt jest otwierany do odczytu.
 * Jeœli otwarcie tego pliku powiedzie siê, funkcja iteruje przez ka¿d¹ odczytan¹ liniê i sprawdza, czy zawiera podany numer
 * karty. Jeœli tak, ustawiana jest flaga wypozycza_samochod na 1 i pêtla jest przerywana. Po zakoñczeniu iteracji plik wypozyczanie.txt
 * jest zamykany. Nastêpnie funkcja iteruje przez plik wejœciowy klienci.txt. Dla ka¿dej odczytanej linii parsuje dane klienta:
 * numer karty, imiê, nazwisko, adres i numer telefonu. Jeœli numer karty odczytany z pliku jest równy podanemu numerowi karty,
 * ustawiana jest flaga znaleziono na 1 i kontynuowana jest kolejna iteracja bez zapisywania danej linii do pliku wyjœciowego.
 * W przeciwnym przypadku linia jest zapisywana do pliku wyjœciowego. Po zakoñczeniu iteracji pliki s¹ zamykane. Jeœli flaga
 * znaleziono jest równa 1, oznacza to, ¿e klient zosta³ znaleziony i usuniêty. Plik klienci.txt jest usuwany, a plik tymczasowy
 * temp.txt jest zmieniany nazwê na klienci.txt. Wyœwietlany jest komunikat potwierdzaj¹cy usuniêcie klienta. Jeœli flaga znaleziono
 * jest równa 0, oznacza to, ¿e klient o podanym numerze karty nie zosta³ znaleziony. Plik tymczasowy temp.txt jest usuwany i wyœwietlany
 * jest odpowiedni komunikat. Efektem dzia³ania tej funkcji jest usuniêcie klienta na podstawie numeru karty, jeœli taki klient istnieje
 * i nie wypo¿ycza samochodu.
 *
 * \param nr_karty - Numer karty klienta do usuniêcia.
 */
void usun_klienta(const char* nr_karty)
{
    FILE* plik_wejscie = fopen("klienci.txt", "r"); /// Otwarcie pliku "klienci.txt" w trybie odczytu
    FILE* plik_wyjscie = fopen("temp.txt", "w");    /// Otwarcie pliku "temp.txt" w trybie zapisu

    if (plik_wejscie == NULL || plik_wyjscie == NULL)   /// Sprawdzenie, czy uda³o siê otworzyæ pliki
    {
        printf("Nie uda³o siê otworzyæ plików.\n");
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
        fclose(plik_wypozyczenie);  /// Zamkniêcie pliku "wypozyczanie.txt"
    }

    if (wypozycza_samochod) /// Sprawdzenie, czy klient wypo¿ycza samochód
    {
        printf("Nie mo¿esz usun¹æ klienta, poniewa¿ wypo¿ycza on samochód!\n");
        fclose(plik_wejscie);   /// Zamkniêcie pliku "klienci.txt"
        fclose(plik_wyjscie);   /// Zamkniêcie pliku "temp.txt"
        remove("temp.txt"); /// Usuniêcie pliku "temp.txt"
        return;
    }

    while (fgets(linia, sizeof(linia), plik_wejscie))   /// Wczytywanie linii z pliku "klienci.txt"
    {
        char numer_karty[20];
        char imie[20];
        char nazwisko[20];
        char adres[50];
        char telefon[20];

        sscanf(linia, "%s \t%s \t%s \t%s \t%s", numer_karty, imie, nazwisko, adres, telefon);   /// Wczytanie danych z linii do odpowiednich buforów

        if (strcmp(numer_karty, nr_karty) == 0) /// Porównanie numeru karty z numerem karty klienta do usuniêcia
        {
            znaleziono = 1;
            continue;
        }

        fputs(linia, plik_wyjscie); /// Zapisanie bie¿¹cej linii do pliku wyjœciowego
    }

    fclose(plik_wejscie);   /// Zamkniêcie pliku "klienci.txt"
    fclose(plik_wyjscie);   /// Zamkniêcie pliku "temp.txt"

    if (znaleziono) /// Sprawdzenie, czy znaleziono klienta do usuniêcia
    {
        remove("klienci.txt");  /// Usuniêcie pliku "klienci.txt"
        rename("temp.txt", "klienci.txt");  /// Zmiana nazwy pliku "temp.txt" na "klienci.txt"
        printf("Klient o podanym numerze karty zosta³ usuniêty.\n");    
    }
    else
    {
        remove("temp.txt"); /// Usuniêcie pliku "temp.txt"
        printf("Nie znaleziono klienta o podanym numerze karty.\n");
    }
}