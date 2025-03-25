#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "WyswietlenieWypozyczen.h"
#pragma warning(disable : 4996)	

/**
 * Wyœwietla listê wypo¿yczonych samochodów.Funkcja otwiera plik "wypozyczanie.txt" w trybie odczytu. Jeœli nie uda siê
 * otworzyæ pliku,wyœwietla odpowiedni komunikat i koñczy dzia³anie. Nastêpnie odczytuje kolejne linie z pliku i wyœwietla
 * je na standardowym wyjœciu. Po wyœwietleniu wszystkich linii, zamyka plik.
 */
void wyswietl_wypozyczenia()
{
	FILE* plik = fopen("wypozyczanie.txt", "r");	/// Otwarcie pliku w trybie odczytu
	if (plik == NULL)
	{
		printf("Nie uda³o siê otworzyæ pliku wypozyczanie.txt.\n");
		return;
	}

	char linia[100];
	printf("					Lista wypo¿yczonych samochodów:\n");
	printf("----------------------------------------\n");

	while (fgets(linia, sizeof(linia), plik) != NULL)	/// Wyœwietlenie odczytanej linii z pliku wypozyczenia.txt
	{
		printf("%s", linia);
	}

	printf("----------------------------------------\n");

	fclose(plik);	/// Zamkniêcie pliku
}