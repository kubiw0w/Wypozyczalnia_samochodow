#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "WyswietlenieKlientow.h"
#pragma warning(disable : 4996)

/**
 * Wczytuje dane klient�w z pliku i tworzy list� klient�w.Funkcja otwiera plik klienci.txt w trybie odczytu i odczytuje kolejne
 * linie z pliku. Dla ka�dej linii tworzy nowego klienta, wczytuje dane klienta z linii i dodaje go na koniec listy klient�w.
 * Po zako�czeniu odczytu pliku, funkcja zamyka plik i zwraca wska�nik do g�owy listy klient�w. Je�li wyst�pi� b��d podczas
 * alokacji pami�ci lub otwierania pliku, funkcja zwraca NULL.
 *
 * \return Wska�nik do g�owy listy klient�w lub NULL w przypadku b��du.
 */
Klient* wczytaj()
{
    FILE* plik;
    Klient* glowa = NULL;   /// Inicjalizacja wska�nika na g�ow� listy klient�w
    Klient* ogon = NULL;    /// Inicjalizacja wska�nika na ogon listy klient�w

    char linia[100];

    plik = fopen("klienci.txt", "r");   /// Otwarcie pliku do odczytu
    if (plik == NULL)
    {
        printf("Nie uda�o si� otworzy� pliku z klientami.\n");
        return NULL;
    }

    while (fgets(linia, sizeof(linia), plik))   /// Odczytywanie kolejnych linii z pliku
    {
        long long int numer_karty = 0;
        char imie[20] = { 0 };
        char nazwisko[20] = { 0 };
        char adres[50] = { 0 };
        long long int telefon = 0;

        Klient* nowy = (Klient*)malloc(sizeof(Klient)); /// Alokacja pami�ci dla nowego klienta
        if (nowy == NULL)
        {
            printf("B��d alokacji pami�ci.\n");
            return NULL;
        }

        sscanf(linia, "%lld %[^\t] %[^\t] %[^\t] %lld", &numer_karty, imie, nazwisko, adres, &telefon); /// Wczytanie danych klienta z linii

        nowy->numer_karty = numer_karty;
        strcpy(nowy->imie, imie);
        strcpy(nowy->nazwisko, nazwisko);
        strcpy(nowy->adres, adres);
        nowy->telefon = telefon;

        nowy->prev = ogon;  /// Ustawienie poprzednika na aktualny ogon listy
        nowy->next = NULL;  /// Ustawienie nast�pnika na NULL, poniewa� klient jest dodawany na koniec listy

        if (ogon != NULL)
        {
            ogon->next = nowy;  /// Przypisanie nast�pnika aktualnemu ogonowi listy
        }
        else
        {
            glowa = nowy;   /// Je�li ogon jest NULL, to oznacza, �e lista jest pusta, wi�c nowy klient staje si� g�ow� listy
        }

        ogon = nowy;    /// Przypisanie nowego klienta jako nowego ogona listy
    }

    fclose(plik);   /// Zamkni�cie pliku

    return glowa;   /// Zwr�cenie g�owy listy klient�w
}

/**
 * Wy�wietla dane wszystkich klient�w znajduj�cych si� na li�cie. Funkcja przyjmuje wska�nik do g�owy listy klient�w.
 * Je�li lista jest pusta (g�owa jest NULL), wypisuje informacj� o braku klient�w i ko�czy dzia�anie. W przeciwnym razie,
 * przechodzi przez list� klient�w, wy�wietlaj�c informacje o ka�dym kliencie, takie jak numer karty, imi�, nazwisko, adres
 * i numer telefonu. Po przej�ciu przez ca�� list�, zwraca wska�nik do g�owy listy klient�w.
 *
 * \param head - Wska�nik do g�owy listy klient�w.
 * \return Wska�nik do g�owy listy klient�w.
 */
Klient* wyswietl(Klient* head)
{
	if (head == NULL)
	{
		printf("Nie ma �adnych klient�w na li�cie.\n");
		return;
	}

	Klient* bufor = head;   /// Inicjalizacja wska�nika buforowego na g�ow� listy

	while (bufor != NULL)
	{
		printf("Numer karty: %lld\n", bufor->numer_karty);
		printf("Imi�: %s\n", bufor->imie);
		printf("Nazwisko: %s\n", bufor->nazwisko);
		printf("Adres: %s\n", bufor->adres);
		printf("Numer telefonu: %lld\n", bufor->telefon);
		printf("\n");

		bufor = bufor->next;    /// Przej�cie do nast�pnego klienta na li�cie
	}
		
	return head;    /// Zwr�cenie g�owy listy klient�w
}