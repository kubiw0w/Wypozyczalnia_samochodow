#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "WyswietlenieAut.h"
#pragma warning(disable : 4996) 

/**
 * Wczytuje dane samochodów z pliku i tworzy listê jednokierunkow¹.Funkcja otwiera plik baza.txt w trybie odczytu i
 * odczytuje kolejne linie, z których pobiera informacje o samochodach. Ka¿da linia powinna zawieraæ dane samochodu
 * w okreœlonym formacie. Nastêpnie funkcja alokuje pamiêæ dla nowego samochodu, wczytuje dane z linii do struktury samochodu
 * i dodaje samochód na koniec listy. G³owa listy samochodów oraz ogon listy s¹ odpowiednio aktualizowane. Na koñcu funkcja
 * zamyka plik i zwraca wskaŸnik do g³owy listy samochodów.
 *
 * \return WskaŸnik do g³owy listy samochodów lub NULL w przypadku b³êdu. 
 */
Auto* wczytaj_z_pliku()
{
    FILE* plik;
    Auto* glowa = NULL; /// G³owa listy samochodów
    Auto* ogon = NULL;  /// Ogon listy samochodów

    char linia[100];

    plik = fopen("baza.txt", "r");  /// Otwarcie pliku baza.txt w trybie odczytu
    if (plik == NULL)
    {
        printf("Nie uda³o siê otworzyæ pliku z samochodami.\n");
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

        Auto* nowy = (Auto*)malloc(sizeof(Auto));   /// Alokacja pamiêci dla nowego samochodu
        if (nowy == NULL)
        {
            printf("B³¹d alokacji pamiêci.\n");
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

        nowy->prev = ogon;  /// Ustawienie wskaŸnika prev nowego samochodu na ostatni element listy
        nowy->next = NULL;  /// Ustawienie wskaŸnika next nowego samochodu na NULL

        if (ogon != NULL)
        {
            ogon->next = nowy;  /// Jeœli lista nie jest pusta, ustaw wskaŸnik next ostatniego samochodu na nowy samochód
        }
        else
        {
            glowa = nowy;   /// Jeœli lista jest pusta, ustaw g³owê listy na nowy samochód
        }

        ogon = nowy;    /// Ustawienie ogona listy na nowy samochód
    }

    fclose(plik);   /// Zamkniêcie pliku
		
    return glowa;   /// Zwróæ wskaŸnik do g³owy listy samochodów
}

/**
 * Wyœwietla dane wszystkich samochodów znajduj¹cych siê na liœcie. Funkcja przyjmuje wskaŸnik do g³owy listy samochodów
 * i iteruje po wszystkichsamochodach, wyœwietlaj¹c ich dane na standardowym wyjœciu. Jeœli lista jest pusta, funkcja wyœwietla
 * odpowiedni komunikat. Po zakoñczeniu iteracji, funkcja zwraca wskaŸnik do g³owy listy samochodów.
 *
 * \param glowa - WskaŸnik do g³owy listy samochodów. 
 * \return WskaŸnik do g³owy listy samochodów lub NULL, jeœli lista jest pusta.
 */
Auto* wyswietl_auta(Auto* glowa)    /// Funkcja s³u¿y do wyœwietlania danych wszystkich aut
{
    if (glowa == NULL)
    {
        printf("Nie ma ¿adnych aut na liœcie.\n");
        return NULL;
    }

    Auto* bufor = glowa;    /// Utworzenie bufora wskazuj¹cego na g³owê listy

    while (bufor != NULL)   /// Wyœwietlanie wszystkich samochodów
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

        bufor = bufor->next;    /// Przejœcie do nastêpnego samochodu
    }

    return glowa;   /// Zwrócenie g³owy listy samochodów
}