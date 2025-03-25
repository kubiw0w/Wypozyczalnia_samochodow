#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "DodawanieKlientow.h"
#include "WyswietlenieKlientow.h"
#pragma warning(disable : 4996)

/**
 * Funkcja ta dodaje nowego klienta do listy klient�w oraz zapisuje dane klienta do pliku tekstowego.
 * Funkcja pobiera dane nowego klienta od u�ytkownika, tworzy nowy w�ze� listy klient�w i wstawia
 * go na pocz�tek listy. Nast�pnie zapisuje dane klienta do pliku tekstowego i wy�wietla komunikat o dodaniu
 * klienta do bazy
 *
 * \param glowa - Wska�nik na wska�nik do pierwszego elementu listy klient�w. 
 */
void dodaj_klienta(Klient** glowa)
{
	long long int numer_karty;
	char imie[20];
	char nazwisko[20];
	char adres[50];
	long long int telefon;

	printf("Podaj numer karty: ");
	scanf("%lld", &numer_karty);

	while (getchar() != '\n');	/// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
	printf("Podaj imie: ");
	fgets(imie, sizeof(imie), stdin); /// Wprowadzanie imienia klienta
	imie[strcspn(imie, "\n")] = '\0';	/// Usuwa znak nowej linii z ko�ca

	printf("Podaj nazwisko: ");
	fgets(nazwisko, sizeof(nazwisko), stdin);	/// Wprowadzanie nazwiska klienta
	nazwisko[strcspn(nazwisko, "\n")] = '\0';	/// Usuwa znak nowej linii z ko�ca

	printf("Podaj adres: ");
	fgets(adres, sizeof(adres), stdin);	/// Wprowadzanie adresu klienta
	adres[strcspn(adres, "\n")] = '\0';	/// Usuwa znak nowej linii z ko�ca

	printf("Podaj telefon: ");
	scanf("%lld", &telefon);	/// Wprowadzanie numeru telefonu klienta

	Klient* nowy = (Klient*)malloc(sizeof(Klient));	/// Alokuje pami�� dla nowego elementu struktury Klient
	if (nowy == NULL)
	{
		printf("B��d alokacji pami�ci.\n");
		return;
	}

	nowy->numer_karty = numer_karty;	/// Przypisanie warto�ci zmiennej numer_karty do pola numer_karty nowego klienta
	strcpy(nowy->imie, imie);	/// Skopiowanie warto�ci zmiennej imie do pola imie nowego klienta
	strcpy(nowy->nazwisko, nazwisko);	/// Skopiowanie warto�ci zmiennej nazwisko do pola nazwisko nowego klienta
	strcpy(nowy->adres, adres);	/// Skopiowanie warto�ci zmiennej adres do pola adres nowego klienta
	nowy->telefon = telefon;	/// Przypisanie warto�ci zmiennej telefon do pola telefon nowego klienta

	nowy->next = *glowa;	/// Przypisanie wska�nika *glowa do wska�nika next nowego klienta
	nowy->prev = NULL;	/// Inicjalizacja wska�nika prev nowego klienta na NULL

	if (*glowa != NULL)
	{
		(*glowa)->prev = nowy;	/// Je�li lista nie by�a pusta, ustaw wska�nik prev pierwszego elementu listy na nowego klienta
	}

	*glowa = nowy;	/// Ustaw *glowa na nowego klienta, kt�ry staje si� pierwszym elementem listy

	FILE* plik = fopen("klienci.txt", "a");	/// Otwarcie pliku "klienci.txt" w trybie dopisywania
	if (plik == NULL)
	{
		printf("Nie uda�o si� otworzy� bazy klient�w.\n");
		return;
	}

	fprintf(plik, "%lld \t%s \t%s \t%s \t%lld\n", numer_karty, imie, nazwisko, adres, telefon);	/// Zapisanie danych nowego klienta do pliku
	fclose(plik);	/// Zamkni�cie pliku

	printf("Klient zosta� dodany do bazy.\n");	/// Wy�wietlenie komunikatu o pomy�lnym dodaniu klienta
}