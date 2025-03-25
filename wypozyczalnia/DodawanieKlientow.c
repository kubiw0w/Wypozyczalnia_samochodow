#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "DodawanieKlientow.h"
#include "WyswietlenieKlientow.h"
#pragma warning(disable : 4996)

/**
 * Funkcja ta dodaje nowego klienta do listy klientów oraz zapisuje dane klienta do pliku tekstowego.
 * Funkcja pobiera dane nowego klienta od u¿ytkownika, tworzy nowy wêze³ listy klientów i wstawia
 * go na pocz¹tek listy. Nastêpnie zapisuje dane klienta do pliku tekstowego i wyœwietla komunikat o dodaniu
 * klienta do bazy
 *
 * \param glowa - WskaŸnik na wskaŸnik do pierwszego elementu listy klientów. 
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
	imie[strcspn(imie, "\n")] = '\0';	/// Usuwa znak nowej linii z koñca

	printf("Podaj nazwisko: ");
	fgets(nazwisko, sizeof(nazwisko), stdin);	/// Wprowadzanie nazwiska klienta
	nazwisko[strcspn(nazwisko, "\n")] = '\0';	/// Usuwa znak nowej linii z koñca

	printf("Podaj adres: ");
	fgets(adres, sizeof(adres), stdin);	/// Wprowadzanie adresu klienta
	adres[strcspn(adres, "\n")] = '\0';	/// Usuwa znak nowej linii z koñca

	printf("Podaj telefon: ");
	scanf("%lld", &telefon);	/// Wprowadzanie numeru telefonu klienta

	Klient* nowy = (Klient*)malloc(sizeof(Klient));	/// Alokuje pamiêæ dla nowego elementu struktury Klient
	if (nowy == NULL)
	{
		printf("B³¹d alokacji pamiêci.\n");
		return;
	}

	nowy->numer_karty = numer_karty;	/// Przypisanie wartoœci zmiennej numer_karty do pola numer_karty nowego klienta
	strcpy(nowy->imie, imie);	/// Skopiowanie wartoœci zmiennej imie do pola imie nowego klienta
	strcpy(nowy->nazwisko, nazwisko);	/// Skopiowanie wartoœci zmiennej nazwisko do pola nazwisko nowego klienta
	strcpy(nowy->adres, adres);	/// Skopiowanie wartoœci zmiennej adres do pola adres nowego klienta
	nowy->telefon = telefon;	/// Przypisanie wartoœci zmiennej telefon do pola telefon nowego klienta

	nowy->next = *glowa;	/// Przypisanie wskaŸnika *glowa do wskaŸnika next nowego klienta
	nowy->prev = NULL;	/// Inicjalizacja wskaŸnika prev nowego klienta na NULL

	if (*glowa != NULL)
	{
		(*glowa)->prev = nowy;	/// Jeœli lista nie by³a pusta, ustaw wskaŸnik prev pierwszego elementu listy na nowego klienta
	}

	*glowa = nowy;	/// Ustaw *glowa na nowego klienta, który staje siê pierwszym elementem listy

	FILE* plik = fopen("klienci.txt", "a");	/// Otwarcie pliku "klienci.txt" w trybie dopisywania
	if (plik == NULL)
	{
		printf("Nie uda³o siê otworzyæ bazy klientów.\n");
		return;
	}

	fprintf(plik, "%lld \t%s \t%s \t%s \t%lld\n", numer_karty, imie, nazwisko, adres, telefon);	/// Zapisanie danych nowego klienta do pliku
	fclose(plik);	/// Zamkniêcie pliku

	printf("Klient zosta³ dodany do bazy.\n");	/// Wyœwietlenie komunikatu o pomyœlnym dodaniu klienta
}