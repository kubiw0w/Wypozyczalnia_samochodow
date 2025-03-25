#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "ZwrotSamochodu.h"
#pragma warning(disable : 4996)

/**
 * Zwraca samoch�d o podanym identyfikatorze. Funkcja otwiera plik wypozyczanie.txt w trybie odczytu i plik tymczasowy.txt
 * w trybie zapisu. Nast�pnie odczytuje kolejne linie z pliku wypo�ycze�. Je�li ID samochodu jest zgodne z podanym ID,
 * ustawia flag� wypo�yczenia na true. W przeciwnym przypadku zapisuje odczytan� lini� do pliku tymczasowego. Po zako�czeniu
 * odczytu, zamyka oba pliki. Nast�pnie usuwa oryginalny plik wypo�ycze� i zmienia nazw� pliku tymczasowego na wypozyczanie.txt.
 * Na koniec wy�wietla komunikat potwierdzaj�cy zwr�cenie samochodu.
 *
 * \param id_samochodu - Identyfikator samochodu do zwrotu.
 */
void zwroc_samochod(int id_samochodu)
{
	FILE* plik = fopen("wypozyczanie.txt", "r");	/// Otwarcie pliku wypo�ycze� w trybie odczytu
	FILE* tymczasowy = fopen("tymczasowy.txt", "w");	/// Otwarcie pliku tymczasowego w trybie zapisu

	if (plik == NULL || tymczasowy == NULL)
	{
		printf("B��d otwarcia plik�w.\n");
		return;
	}

	char linia[100];
	int flaga_wypozyczenia = 0;

	while (fgets(linia, sizeof(linia), plik) != NULL)
	{
		if (strcmp(linia, "Wypo�yczenie:\n") == 0)	/// Sprawdzenie, czy linia wskazuje na pocz�tek wypo�yczenia
		{
			fgets(linia, sizeof(linia), plik);	/// Odczytanie linii zawieraj�cej ID samochodu
			int id;
			sscanf(linia, "ID samochodu: %d", &id);	/// Wyci�gni�cie ID samochodu z linii

			if (id == id_samochodu)	/// Sprawdzenie, czy ID samochodu jest zgodne z podanym ID
			{
				flaga_wypozyczenia = 1;
				continue;
			}
		}

		if (!flaga_wypozyczenia)	/// Je�li nie jeste�my w sekcji wypo�yczenia
		{
			fputs(linia, tymczasowy);	/// Zapisz odczytan� lini� do pliku tymczasowego
		}
		else if (strcmp(linia, "----------------------------------------\n") == 0)	/// Sprawdzenie, czy linia wskazuje na koniec wypo�yczenia
		{
			flaga_wypozyczenia = 0;
		}
	}

	fclose(plik);	/// Zamkni�cie pliku wypo�ycze�
	fclose(tymczasowy);	/// Zamkni�cie pliku tymczasowego

	remove("wypozyczanie.txt");	/// Usuni�cie oryginalnego pliku wypo�ycze�
	rename("tymczasowy.txt", "wypozyczanie.txt");	/// Zmiana nazwy pliku tymczasowego na wypo�yczanie.txt

	printf("Samoch�d o ID %d zosta� zwr�cony.\n", id_samochodu);
}