#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "WyswietlenieAut.h"
#pragma warning(disable : 4996) 

/**
 * Wczytuje dane samochod�w z pliku i tworzy list� jednokierunkow�.Funkcja otwiera plik baza.txt w trybie odczytu i
 * odczytuje kolejne linie, z kt�rych pobiera informacje o samochodach. Ka�da linia powinna zawiera� dane samochodu
 * w okre�lonym formacie. Nast�pnie funkcja alokuje pami�� dla nowego samochodu, wczytuje dane z linii do struktury samochodu
 * i dodaje samoch�d na koniec listy. G�owa listy samochod�w oraz ogon listy s� odpowiednio aktualizowane. Na ko�cu funkcja
 * zamyka plik i zwraca wska�nik do g�owy listy samochod�w.
 *
 * \return Wska�nik do g�owy listy samochod�w lub NULL w przypadku b��du. 
 */
Auto* wczytaj_z_pliku()
{
    FILE* plik;
    Auto* glowa = NULL; /// G�owa listy samochod�w
    Auto* ogon = NULL;  /// Ogon listy samochod�w

    char linia[100];

    plik = fopen("baza.txt", "r");  /// Otwarcie pliku baza.txt w trybie odczytu
    if (plik == NULL)
    {
        printf("Nie uda�o si� otworzy� pliku z samochodami.\n");
        return NULL;
    }

    while (fgets(linia, sizeof(linia), plik))   /// Odczytaj kolejne linie z pliku
    {
        int id = 0;
    	char nr_rejestracyjny[20] = { 0 };
        char marka[20] = { 0 };
        char model[20] = { 0 };
        int rok_produkcji = 0;
        char kolor[30] = { 0 };
        int przebieg = 0;

        Auto* nowy = (Auto*)malloc(sizeof(Auto));   /// Alokacja pami�ci dla nowego samochodu
        if (nowy == NULL)
        {
            printf("B��d alokacji pami�ci.\n");
            return NULL;
        }

        sscanf(linia, "%d %[^\t] %[^\t] %[^\t] %d %[^\t] %d", &id, nr_rejestracyjny, marka, model, &rok_produkcji, kolor, &przebieg);   /// Wczytaj dane samochodu ze wczytanej linii

        nowy->id = id;
    	strcpy(nowy->nr_rejestracyjny, nr_rejestracyjny);
        strcpy(nowy->marka, marka);
        strcpy(nowy->model, model);
        nowy->rok_produkcji = rok_produkcji;
        strcpy(nowy->kolor, kolor);
        nowy->przebieg = przebieg;

        nowy->prev = ogon;  /// Ustawienie wska�nika prev nowego samochodu na ostatni element listy
        nowy->next = NULL;  /// Ustawienie wska�nika next nowego samochodu na NULL

        if (ogon != NULL)
        {
            ogon->next = nowy;  /// Je�li lista nie jest pusta, ustaw wska�nik next ostatniego samochodu na nowy samoch�d
        }
        else
        {
            glowa = nowy;   /// Je�li lista jest pusta, ustaw g�ow� listy na nowy samoch�d
        }

        ogon = nowy;    /// Ustawienie ogona listy na nowy samoch�d
    }

    fclose(plik);   /// Zamkni�cie pliku
		
    return glowa;   /// Zwr�� wska�nik do g�owy listy samochod�w
}

/**
 * Wy�wietla dane wszystkich samochod�w znajduj�cych si� na li�cie. Funkcja przyjmuje wska�nik do g�owy listy samochod�w
 * i iteruje po wszystkichsamochodach, wy�wietlaj�c ich dane na standardowym wyj�ciu. Je�li lista jest pusta, funkcja wy�wietla
 * odpowiedni komunikat. Po zako�czeniu iteracji, funkcja zwraca wska�nik do g�owy listy samochod�w.
 *
 * \param glowa - Wska�nik do g�owy listy samochod�w. 
 * \return Wska�nik do g�owy listy samochod�w lub NULL, je�li lista jest pusta.
 */
Auto* wyswietl_auta(Auto* glowa)    /// Funkcja s�u�y do wy�wietlania danych wszystkich aut
{
    if (glowa == NULL)
    {
        printf("Nie ma �adnych aut na li�cie.\n");
        return NULL;
    }

    Auto* bufor = glowa;    /// Utworzenie bufora wskazuj�cego na g�ow� listy

    while (bufor != NULL)   /// Wy�wietlanie wszystkich samochod�w
    {
        printf("ID samochodu: %d\n", bufor->id);
    	printf("Nr rejestracyjny: %s\n", bufor->nr_rejestracyjny);
        printf("Marka: %s\n", bufor->marka);
        printf("Model: %s\n", bufor->model);
        printf("Rok produkcji: %d\n", bufor->rok_produkcji);
        printf("Kolor: %s\n", bufor->kolor);
        printf("Przebieg: %d", bufor->przebieg);
        printf(" km\n");
        printf("\n");

        bufor = bufor->next;    /// Przej�cie do nast�pnego samochodu
    }

    return glowa;   /// Zwr�cenie g�owy listy samochod�w
}