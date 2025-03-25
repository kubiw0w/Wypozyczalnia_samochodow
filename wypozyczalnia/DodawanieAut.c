#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>									
#include "WyswietlenieAut.h"
#include "DodawanieAut.h"
#pragma warning(disable : 4996)

/**
 * Funkcja, która s³u¿y do dodawania nowych samochodów do listy. Na pocz¹tku definiuje siê kilka zmiennych,
 * takich jak nr_rejestracyjny, marka, model, rok_produkcji, kolor i przebieg, a nastêpnie u¿ytkownik wprowadza
 * wartoœci dla ka¿dej z tych zmiennych. Nastêpnie tworzy siê nowy wêze³ listy o nazwie nowy za pomoc¹ funkcji
 * malloc i przypisuje mu wartoœci wprowadzone przez u¿ytkownika. Nastêpnie ten nowy wêze³ ³¹czy z reszt¹ listy
 * poprzez ustawienie odpowiednio wskaŸników. Nastêpnie otwiera siê plik baza gdzie zapisuje siê wartoœci samochodu
 * do tego pliku za pomoc¹ funkcji fprintf. Na koniec zamyka siê plik i wyœwietla komunikat potwierdzaj¹cy dodanie
 * samochodu do bazy danych.
 *
 * \param glowa - WskaŸnik na wskaŸnik do pierwszego elementu listy samochodów.
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
	nr_rejestracyjny[strcspn(nr_rejestracyjny, "\n")] = '\0';	/// Usuwa znak nowej linii z koñca

	printf("Podaj markê: ");
	fgets(marka, sizeof(marka), stdin);	/// Wprowadzanie marki samochodu
	marka[strcspn(marka, "\n")] = '\0';	/// Usuwa znak nowej linii z koñca

	printf("Podaj model: ");
	fgets(model, sizeof(model), stdin);	/// Wprowadzanie modelu samochodu
	model[strcspn(model, "\n")] = '\0';	/// Usuwa znak nowej linii z koñca

	printf("Podaj rok produkcji: ");
	scanf("%d", &rok_produkcji);	/// Wprowadzanie roku produkcji samochodu

	while (getchar() != '\n');	/// Odczytuje wszystkie znaki do momentu napotkania znaku nowej linii
	printf("Podaj kolor: ");
	fgets(kolor, sizeof(kolor), stdin);	/// Wprowadzanie koloru samochodu
	kolor[strcspn(kolor, "\n")] = '\0';	/// Usuwa znak nowej linii z koñca

	printf("Podaj przebieg: ");
	scanf("%d", &przebieg);	/// Wprowadzanie przebiegu samochodu

	Auto* nowy = (Auto*)malloc(sizeof(Auto)); /// Alokuje pamiêæ dla nowego elementu struktury Auto
	if (nowy == NULL)
	{
		printf("B³¹d alokacji pamiêci.\n");
		return;
	}

	nowy->id = id;	/// Przypisanie wartoœci zmiennej id do pola id nowego samochodu
	strcpy(nowy->nr_rejestracyjny, nr_rejestracyjny);	/// Skopiowanie wartoœci zmiennej nr_rejestracyjny do pola nr_rejestracyjny nowego samochodu
	strcpy(nowy->marka, marka);	/// Skopiowanie wartoœci zmiennej marka do pola marka nowego samochodu
	strcpy(nowy->model, model);	/// Skopiowanie wartoœci zmiennej model do pola model nowego samochodu
	nowy->rok_produkcji = rok_produkcji;	/// Przypisanie wartoœci zmiennej rok_produkcji do pola rok_produkcji nowego samochodu
	strcpy(nowy->kolor, kolor);	/// Skopiowanie wartoœci zmiennej kolor do pola kolor nowego samochodu
	nowy->przebieg = przebieg;	/// Przypisanie wartoœci zmiennej przebieg do pola przebieg nowego samochodu

	nowy->prev = NULL;	/// Inicjalizacja wskaŸnika prev nowego samochodu na NULL
	nowy->next = *glowa;	/// Przypisanie wskaŸnika *glowa do wskaŸnika next nowego samochodu

	if (*glowa != NULL)
	{
		(*glowa)->prev = nowy; /// Jeœli lista nie by³a pusta, ustaw wskaŸnik prev pierwszego elementu listy na nowy samochód
	}

	*glowa = nowy;	/// Ustaw *glowa na nowy samochód, który staje siê pierwszym elementem listy

	FILE* plik = fopen("baza.txt", "a");	/// Otwarcie pliku "baza.txt" w trybie dopisywania
	if (plik == NULL)
	{
		printf("Nie uda³o siê otworzyæ pliku z samochodami.\n");
		return;
	}

	fprintf(plik, "%d \t%s \t%s \t%s \t%d \t%s \t%d\n", id, nr_rejestracyjny, marka, model, rok_produkcji, kolor, przebieg);	/// Zapisanie danych nowego samochodu do pliku

	fclose(plik);	/// Zamkniêcie pliku

	printf("Samochód zosta³ dodany do bazy.\n");	/// Wyœwietlenie komunikatu o pomyœlnym dodaniu samochodu
}