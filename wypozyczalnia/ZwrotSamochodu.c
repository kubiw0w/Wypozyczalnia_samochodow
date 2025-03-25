#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "ZwrotSamochodu.h"
#pragma warning(disable : 4996)

/**
 * Zwraca samochód o podanym identyfikatorze. Funkcja otwiera plik wypozyczanie.txt w trybie odczytu i plik tymczasowy.txt
 * w trybie zapisu. Nastêpnie odczytuje kolejne linie z pliku wypo¿yczeñ. Jeœli ID samochodu jest zgodne z podanym ID,
 * ustawia flagê wypo¿yczenia na true. W przeciwnym przypadku zapisuje odczytan¹ liniê do pliku tymczasowego. Po zakoñczeniu
 * odczytu, zamyka oba pliki. Nastêpnie usuwa oryginalny plik wypo¿yczeñ i zmienia nazwê pliku tymczasowego na wypozyczanie.txt.
 * Na koniec wyœwietla komunikat potwierdzaj¹cy zwrócenie samochodu.
 *
 * \param id_samochodu - Identyfikator samochodu do zwrotu.
 */
void zwroc_samochod(int id_samochodu)
{
	FILE* plik = fopen("wypozyczanie.txt", "r");	/// Otwarcie pliku wypo¿yczeñ w trybie odczytu
	FILE* tymczasowy = fopen("tymczasowy.txt", "w");	/// Otwarcie pliku tymczasowego w trybie zapisu

	if (plik == NULL || tymczasowy == NULL)
	{
		printf("B³¹d otwarcia plików.\n");
		return;
	}

	char linia[100];
	int flaga_wypozyczenia = 0;

	while (fgets(linia, sizeof(linia), plik) != NULL)
	{
		if (strcmp(linia, "Wypo¿yczenie:\n") == 0)	/// Sprawdzenie, czy linia wskazuje na pocz¹tek wypo¿yczenia
		{
			fgets(linia, sizeof(linia), plik);	/// Odczytanie linii zawieraj¹cej ID samochodu
			int id;
			sscanf(linia, "ID samochodu: %d", &id);	/// Wyci¹gniêcie ID samochodu z linii

			if (id == id_samochodu)	/// Sprawdzenie, czy ID samochodu jest zgodne z podanym ID
			{
				flaga_wypozyczenia = 1;
				continue;
			}
		}

		if (!flaga_wypozyczenia)	/// Jeœli nie jesteœmy w sekcji wypo¿yczenia
		{
			fputs(linia, tymczasowy);	/// Zapisz odczytan¹ liniê do pliku tymczasowego
		}
		else if (strcmp(linia, "----------------------------------------\n") == 0)	/// Sprawdzenie, czy linia wskazuje na koniec wypo¿yczenia
		{
			flaga_wypozyczenia = 0;
		}
	}

	fclose(plik);	/// Zamkniêcie pliku wypo¿yczeñ
	fclose(tymczasowy);	/// Zamkniêcie pliku tymczasowego

	remove("wypozyczanie.txt");	/// Usuniêcie oryginalnego pliku wypo¿yczeñ
	rename("tymczasowy.txt", "wypozyczanie.txt");	/// Zmiana nazwy pliku tymczasowego na wypo¿yczanie.txt

	printf("Samochód o ID %d zosta³ zwrócony.\n", id_samochodu);
}