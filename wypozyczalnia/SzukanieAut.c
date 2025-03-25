#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "WyswietlenieAut.h"
#include "SzukanieAut.h"
#pragma warning(disable : 4996)

/**
 * Wyszukuje samoch�d na podstawie podanego ID i wy�wietla jego informacje.Funkcja wyszukuje samoch�d o podanym ID
 * w li�cie samochod�w i wy�wietla jego szczeg�owe informacje,takie jak numer rejestracyjny, marka, model,
 * rok produkcji, kolor i przebieg.Je�li samoch�d o podanym ID nie zostanie znaleziony, wypisuje odpowiedni komunikat.
 *
 * \param glowa - Wska�nik na g�ow� listy samochod�w. 
 */
void wyszukaj_auto(Auto* glowa)
{
	if (glowa == NULL) {
		printf("Nie ma �adnych aut na li�cie.\n");
		return;
	}

	int szukane_id;
	printf("Podaj ID samochodu: ");
	scanf("%d", &szukane_id);	/// Wprowadzanie ID samochodu

	Auto* bufor = glowa;	/// Ustawienie wska�nika bufor na g�ow� listy samochod�w
	int znaleziono = 0;

	while (bufor != NULL)	
	{
		if (bufor->id == szukane_id)	/// Sprawdzenie czy ID samochodu zgadza si� z podanym ID
		{
			printf("\n\n");
			printf("ID samochodu: %d\n", bufor->id);
			printf("Nr rejestracyjny: %s\n", bufor->nr_rejestracyjny);
			printf("Marka: %s\n", bufor->marka);
			printf("Model: %s\n", bufor->model);
			printf("Rok produkcji: %d\n", bufor->rok_produkcji);
			printf("Kolor: %s\n", bufor->kolor);
			printf("Przebieg: %d km\n", bufor->przebieg);
			printf("\n");
			znaleziono = 1;
			break;
		}
		bufor = bufor->next;	/// Przej�cie do nast�pnego samochodu
	}

	if (!znaleziono) 
	{
		printf("Nie znaleziono samochodu o podanym ID.\n");	/// Je�eli nie znaleziono samochodu o podanym ID
	}
}