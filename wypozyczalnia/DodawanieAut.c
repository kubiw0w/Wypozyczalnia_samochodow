#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>									
#include "WyswietlenieAut.h"
#include "DodawanieAut.h"
#pragma warning(disable : 4996)

/**
 * Funkcja, kt�ra s�u�y do dodawania nowych samochod�w do listy. Na pocz�tku definiuje si� kilka zmiennych,
 * takich jak nr_rejestracyjny, marka, model, rok_produkcji, kolor i przebieg, a nast�pnie u�ytkownik wprowadza
 * warto�ci dla ka�dej z tych zmiennych. Nast�pnie tworzy si� nowy w�ze� listy o nazwie nowy za pomoc� funkcji
 * malloc i przypisuje mu warto�ci wprowadzone przez u�ytkownika. Nast�pnie ten nowy w�ze� ��czy z reszt� listy
 * poprzez ustawienie odpowiednio wska�nik�w. Nast�pnie otwiera si� plik baza gdzie zapisuje si� warto�ci samochodu
 * do tego pliku za pomoc� funkcji fprintf. Na koniec zamyka si� plik i wy�wietla komunikat potwierdzaj�cy dodanie
 * samochodu do bazy danych.
 *
 * \param glowa - Wska�nik na wska�nik do pierwszego elementu listy samochod�w.
 */
void dodaj_samochod(Auto** glowa)
{
	char nr_rejestracyjny[20] = { 0 };
	char marka[20] = { 0 };
	char model[20] = { 0 };
	int rok_produkcji = 0;
	char kolor[30] = { 0 };
	int przebieg = 0;
	int id = 0;

	while (getchar() != '\n');	/// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
	printf("Podaj ID samochodu: ");
	scanf("%d", &id);	/// Wprowadzanie ID samochodu

	while (getchar() != '\n');	/// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
	printf("Podaj nr rejestracyjny: ");
	fgets(nr_rejestracyjny, sizeof(nr_rejestracyjny), stdin);	/// Wprowadzanie numeru rejestracyjnego samochodu
	nr_rejestracyjny[strcspn(nr_rejestracyjny, "\n")] = '\0';	/// Usuwa znak nowej linii z ko�ca

	printf("Podaj mark�: ");
	fgets(marka, sizeof(marka), stdin);	/// Wprowadzanie marki samochodu
	marka[strcspn(marka, "\n")] = '\0';	/// Usuwa znak nowej linii z ko�ca

	printf("Podaj model: ");
	fgets(model, sizeof(model), stdin);	/// Wprowadzanie modelu samochodu
	model[strcspn(model, "\n")] = '\0';	/// Usuwa znak nowej linii z ko�ca

	printf("Podaj rok produkcji: ");
	scanf("%d", &rok_produkcji);	/// Wprowadzanie roku produkcji samochodu

	while (getchar() != '\n');	/// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
	printf("Podaj kolor: ");
	fgets(kolor, sizeof(kolor), stdin);	/// Wprowadzanie koloru samochodu
	kolor[strcspn(kolor, "\n")] = '\0';	/// Usuwa znak nowej linii z ko�ca

	printf("Podaj przebieg: ");
	scanf("%d", &przebieg);	/// Wprowadzanie przebiegu samochodu

	Auto* nowy = (Auto*)malloc(sizeof(Auto)); /// Alokuje pami�� dla nowego elementu struktury Auto
	if (nowy == NULL)
	{
		printf("B��d alokacji pami�ci.\n");
		return;
	}

	nowy->id = id;	/// Przypisanie warto�ci zmiennej id do pola id nowego samochodu
	strcpy(nowy->nr_rejestracyjny, nr_rejestracyjny);	/// Skopiowanie warto�ci zmiennej nr_rejestracyjny do pola nr_rejestracyjny nowego samochodu
	strcpy(nowy->marka, marka);	/// Skopiowanie warto�ci zmiennej marka do pola marka nowego samochodu
	strcpy(nowy->model, model);	/// Skopiowanie warto�ci zmiennej model do pola model nowego samochodu
	nowy->rok_produkcji = rok_produkcji;	/// Przypisanie warto�ci zmiennej rok_produkcji do pola rok_produkcji nowego samochodu
	strcpy(nowy->kolor, kolor);	/// Skopiowanie warto�ci zmiennej kolor do pola kolor nowego samochodu
	nowy->przebieg = przebieg;	/// Przypisanie warto�ci zmiennej przebieg do pola przebieg nowego samochodu

	nowy->prev = NULL;	/// Inicjalizacja wska�nika prev nowego samochodu na NULL
	nowy->next = *glowa;	/// Przypisanie wska�nika *glowa do wska�nika next nowego samochodu

	if (*glowa != NULL)
	{
		(*glowa)->prev = nowy; /// Je�li lista nie by�a pusta, ustaw wska�nik prev pierwszego elementu listy na nowy samoch�d
	}

	*glowa = nowy;	/// Ustaw *glowa na nowy samoch�d, kt�ry staje si� pierwszym elementem listy

	FILE* plik = fopen("baza.txt", "a");	/// Otwarcie pliku "baza.txt" w trybie dopisywania
	if (plik == NULL)
	{
		printf("Nie uda�o si� otworzy� pliku z samochodami.\n");
		return;
	}

	fprintf(plik, "%d \t%s \t%s \t%s \t%d \t%s \t%d\n", id, nr_rejestracyjny, marka, model, rok_produkcji, kolor, przebieg);	/// Zapisanie danych nowego samochodu do pliku

	fclose(plik);	/// Zamkni�cie pliku

	printf("Samoch�d zosta� dodany do bazy.\n");	/// Wy�wietlenie komunikatu o pomy�lnym dodaniu samochodu
}