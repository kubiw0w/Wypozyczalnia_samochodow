#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "WyswietlenieWypozyczen.h"
#pragma warning(disable : 4996)	

/**
 * Wy�wietla list� wypo�yczonych samochod�w.Funkcja otwiera plik "wypozyczanie.txt" w trybie odczytu. Je�li nie uda si�
 * otworzy� pliku,wy�wietla odpowiedni komunikat i ko�czy dzia�anie. Nast�pnie odczytuje kolejne linie z pliku i wy�wietla
 * je na standardowym wyj�ciu. Po wy�wietleniu wszystkich linii, zamyka plik.
 */
void wyswietl_wypozyczenia()
{
	FILE* plik = fopen("wypozyczanie.txt", "r");	/// Otwarcie pliku w trybie odczytu
	if (plik == NULL)
	{
		printf("Nie uda�o si� otworzy� pliku wypozyczanie.txt.\n");
		return;
	}

	char linia[100];
	printf("					Lista wypo�yczonych samochod�w:\n");
	printf("----------------------------------------\n");

	while (fgets(linia, sizeof(linia), plik) != NULL)	/// Wy�wietlenie odczytanej linii z pliku wypozyczenia.txt
	{
		printf("%s", linia);
	}

	printf("----------------------------------------\n");

	fclose(plik);	/// Zamkni�cie pliku
}