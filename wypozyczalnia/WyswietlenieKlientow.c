#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "WyswietlenieKlientow.h"
#pragma warning(disable : 4996)

/**
 * Wczytuje dane klientów z pliku i tworzy listê klientów.Funkcja otwiera plik klienci.txt w trybie odczytu i odczytuje kolejne
 * linie z pliku. Dla ka¿dej linii tworzy nowego klienta, wczytuje dane klienta z linii i dodaje go na koniec listy klientów.
 * Po zakoñczeniu odczytu pliku, funkcja zamyka plik i zwraca wskaŸnik do g³owy listy klientów. Jeœli wyst¹pi³ b³¹d podczas
 * alokacji pamiêci lub otwierania pliku, funkcja zwraca NULL.
 *
 * \return WskaŸnik do g³owy listy klientów lub NULL w przypadku b³êdu.
 */
Klient* wczytaj()
{
    FILE* plik;
    Klient* glowa = NULL;   /// Inicjalizacja wskaŸnika na g³owê listy klientów
    Klient* ogon = NULL;    /// Inicjalizacja wskaŸnika na ogon listy klientów

    char linia[100];

    plik = fopen("klienci.txt", "r");   /// Otwarcie pliku do odczytu
    if (plik == NULL)
    {
        printf("Nie uda³o siê otworzyæ pliku z klientami.\n");
        return NULL;
    }

    while (fgets(linia, sizeof(linia), plik))   /// Odczytywanie kolejnych linii z pliku
    {
        long long int numer_karty = 0;
        char imie[20] = { 0 };
        char nazwisko[20] = { 0 };
        char adres[50] = { 0 };
        long long int telefon = 0;

        Klient* nowy = (Klient*)malloc(sizeof(Klient)); /// Alokacja pamiêci dla nowego klienta
        if (nowy == NULL)
        {
            printf("B³¹d alokacji pamiêci.\n");
            return NULL;
        }

        sscanf(linia, "%lld %[^\t] %[^\t] %[^\t] %lld", &numer_karty, imie, nazwisko, adres, &telefon); /// Wczytanie danych klienta z linii

        nowy->numer_karty = numer_karty;
        strcpy(nowy->imie, imie);
        strcpy(nowy->nazwisko, nazwisko);
        strcpy(nowy->adres, adres);
        nowy->telefon = telefon;

        nowy->prev = ogon;  /// Ustawienie poprzednika na aktualny ogon listy
        nowy->next = NULL;  /// Ustawienie nastêpnika na NULL, poniewa¿ klient jest dodawany na koniec listy

        if (ogon != NULL)
        {
            ogon->next = nowy;  /// Przypisanie nastêpnika aktualnemu ogonowi listy
        }
        else
        {
            glowa = nowy;   /// Jeœli ogon jest NULL, to oznacza, ¿e lista jest pusta, wiêc nowy klient staje siê g³ow¹ listy
        }

        ogon = nowy;    /// Przypisanie nowego klienta jako nowego ogona listy
    }

    fclose(plik);   /// Zamkniêcie pliku

    return glowa;   /// Zwrócenie g³owy listy klientów
}

/**
 * Wyœwietla dane wszystkich klientów znajduj¹cych siê na liœcie. Funkcja przyjmuje wskaŸnik do g³owy listy klientów.
 * Jeœli lista jest pusta (g³owa jest NULL), wypisuje informacjê o braku klientów i koñczy dzia³anie. W przeciwnym razie,
 * przechodzi przez listê klientów, wyœwietlaj¹c informacje o ka¿dym kliencie, takie jak numer karty, imiê, nazwisko, adres
 * i numer telefonu. Po przejœciu przez ca³¹ listê, zwraca wskaŸnik do g³owy listy klientów.
 *
 * \param head - WskaŸnik do g³owy listy klientów.
 * \return WskaŸnik do g³owy listy klientów.
 */
Klient* wyswietl(Klient* head)
{
	if (head == NULL)
	{
		printf("Nie ma ¿adnych klientów na liœcie.\n");
		return;
	}

	Klient* bufor = head;   /// Inicjalizacja wskaŸnika buforowego na g³owê listy

	while (bufor != NULL)
	{
		printf("Numer karty: %lld\n", bufor->numer_karty);
		printf("Imiê: %s\n", bufor->imie);
		printf("Nazwisko: %s\n", bufor->nazwisko);
		printf("Adres: %s\n", bufor->adres);
		printf("Numer telefonu: %lld\n", bufor->telefon);
		printf("\n");

		bufor = bufor->next;    /// Przejœcie do nastêpnego klienta na liœcie
	}
		
	return head;    /// Zwrócenie g³owy listy klientów
}