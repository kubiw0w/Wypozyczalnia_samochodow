#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "WyswietlenieAut.h"
#include "SzukanieAut.h"
#pragma warning(disable : 4996)

/**
 * Wyszukuje samochód na podstawie podanego ID i wyœwietla jego informacje.Funkcja wyszukuje samochód o podanym ID
 * w liœcie samochodów i wyœwietla jego szczegó³owe informacje,takie jak numer rejestracyjny, marka, model,
 * rok produkcji, kolor i przebieg.Jeœli samochód o podanym ID nie zostanie znaleziony, wypisuje odpowiedni komunikat.
 *
 * \param glowa - WskaŸnik na g³owê listy samochodów. 
 */
void wyszukaj_auto(Auto* glowa)
{
	if (glowa == NULL) {
		printf("Nie ma ¿adnych aut na liœcie.\n");
		return;
	}

	int szukane_id;
	printf("Podaj ID samochodu: ");
	scanf("%d", &szukane_id);	/// Wprowadzanie ID samochodu

	Auto* bufor = glowa;	/// Ustawienie wskaŸnika bufor na g³owê listy samochodów
	int znaleziono = 0;

	while (bufor != NULL)	
	{
		if (bufor->id == szukane_id)	/// Sprawdzenie czy ID samochodu zgadza siê z podanym ID
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
		bufor = bufor->next;	/// Przejœcie do nastêpnego samochodu
	}

	if (!znaleziono) 
	{
		printf("Nie znaleziono samochodu o podanym ID.\n");	/// Je¿eli nie znaleziono samochodu o podanym ID
	}
}