#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "WyswietlenieAut.h"						
#include "DodawanieAut.h"
#include "DodawanieKlientow.h"
#include "WyswietlenieKlientow.h"
#include "EdytowanieAut.h"
#include "EdytowanieKlienta.h"
#include "SortRosRokProd.h"
#include "SortMalRokProd.h"
#include "SortRosMarka.h"
#include "SortMalMarka.h"
#include "SortRosModel.h"
#include "SortMalModel.h"
#include "SortRosKolor.h"
#include "SortMalKolor.h"
#include "SortRosPrzebieg.h"
#include "SortMalPrzebieg.h"
#include "SortRosNrRej.h"
#include "SortMalNrRej.h"
#include "SzukanieAut.h"
#include "UsuwanieAut.h"
#include "UsuwanieKlientow.h"
#include "WypozyczanieAut.h"
#include "WyswietlenieWypozyczen.h"
#include "ZwrotSamochodu.h"
 
#pragma warning(disable : 4996)

/**
 * Funkcja główna programu. Zawarte w niej są wywołania wszystkich funkcji użytych w programie tak, aby kontrolowała główny przebieg programu.
 *
 * \return Kod zakończenia programu.
 */
int main()
{
	setlocale(LC_ALL, "polish");	
	Klient* head = NULL;
	int x;
	int y;

	printf("WITAMY W NASZEJ WYPOŻYCZALNI SAMOCHODÓW. WYBIERZ CO CHCESZ ZROBIĆ:\n");
	do														
	{
		printf("///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
		printf("					1. Dodaj samochód.\n");
		printf("					2. Wyświetl samochody.\n");
		printf("					3. Edytuj samochód.\n");
		printf("					4. Dodaj klienta.\n");
		printf("					5. Wyświetl klientów.\n");
		printf("					6. Edytuj klienta.\n");
        printf("					7. Wyszukaj samochód. \n");
		printf("					8. Usuń samochód. \n");
		printf("					9. Usuń klienta. \n");
		printf("					10. Wypożycz samochód.\n");
		printf("					11. Wyświetl listę wypożyczonych samochodów.\n");
		printf("					12. Zwróć samochód.\n");
		printf("					13. Wyjdź z wypożyczalni.\n");
		printf("///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
		scanf("%d", &x);

		switch (x)
		{
		case 1:												/// Case wywołujący funkcję do dodawania danych samochodu
		{
			Auto* glowa = wczytaj_z_pliku();
			dodaj_samochod(&glowa);
			break;
		}
		case 2:												/// Case wywołujący funkcję do wyświetlania danych wszystkich samochodów
		{
			printf("						WYBIERZ OPCJĘ: \n");
			printf("///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
			printf("				1. Wyświetl listę samochodów. \n");
			printf("				2. Wyświetl samochody rosnąco po roku produkcji. \n");
			printf("				3. Wyświetl samochody malejąco po roku produkcji. \n");
			printf("				4. Wyświetl samochody rosnąco po marce samochodu. \n");
			printf("				5. Wyświetl samochody malejąco po marce samochodu. \n");
			printf("				6. Wyświetl samochody rosnąco po modelu samochodu. \n");
			printf("				7. Wyświetl samochody malejąco po modelu samochodu. \n");
			printf("				8. Wyświetl samochody rosnąco po kolorze samochodu. \n");
			printf("				9. Wyświetl samochody malejąco po kolorze samochodu. \n");
			printf("				10. Wyświetl samochody rosnąco po przebiegu samochodu. \n");
			printf("				11. Wyświetl samochody malejąco po przebiegu samochodu. \n");
			printf("				12. Wyświetl samochody rosnąco po numerze rejestracyjnym. \n");
			printf("				13. Wyświetl samochody malejąco po numerze rejestracyjnym. \n");
			printf("///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
			scanf("%d", &y);
			switch(y)
			{
			case 1:
			{
				printf("						Lista samochodów:\n");
				Auto* lista_aut = wczytaj_z_pliku();
				wyswietl_auta(lista_aut);
				break;
			}
			case 2:
			{
				printf("				Posortowana lista aut rosnąco po roku produkcji: \n");
				Auto* head = wczytaj_z_pliku();
				head = sortuj_po_roku_produkcji_rosnaco(head);
				wyswietl_auta(head);
				break;
			}
			case 3:
			{
				printf("				Posortowana lista aut malejąco po roku produkcji: \n");
				Auto* head2 = wczytaj_z_pliku();
				head2 = sortuj_po_roku_produkcji_malejaco(head2);
				wyswietl_auta(head2);
				break;
			}
			case 4:
			{
				printf("				Posortowana lista aut rosnąco po marce samochodu: \n");
				Auto* head3 = wczytaj_z_pliku();
				head3 = sortuj_po_marce_rosnaco(head3);
				wyswietl_auta(head3);
				break;
			}
			case 5:
			{
				printf("				Posortowana lista aut malejąco po marce samochodu: \n");
				Auto* head4 = wczytaj_z_pliku();
				head4 = sortuj_po_marce_malejaco(head4);
				wyswietl_auta(head4);
				break;
			}
			case 6:
			{
				printf("				Posortowana lista aut rosnąco po modelu samochodu: \n");
				Auto* head5 = wczytaj_z_pliku();
				head5 = sortuj_po_modelu_rosnaco(head5);
				wyswietl_auta(head5);
				break;
			}
			case 7:
			{
				printf("				Posortowana lista aut malejąco po modelu samochodu: \n");
				Auto* head6 = wczytaj_z_pliku();
				head6 = sortuj_po_modelu_malejaco(head6);
				wyswietl_auta(head6);
				break;
			}
			case 8:
			{
				printf("				Posortowana lista aut rosnąco po kolorze samochodu: \n");
				Auto* head7 = wczytaj_z_pliku();
				head7 = sortuj_po_kolorze_rosnaco(head7);
				wyswietl_auta(head7);
				break;
			}
			case 9:
			{
				printf("				Posortowana lista aut malejąco po kolorze samochodu: \n");
				Auto* head8 = wczytaj_z_pliku();
				head8 = sortuj_po_kolorze_malejaco(head8);
				wyswietl_auta(head8);
				break;
			}
			case 10:
			{
				printf("				Posortowana lista aut rosnąco po przebiegu samochodu: \n");
				Auto* head9 = wczytaj_z_pliku();
				head9 = sortuj_po_przebiegu_rosnaco(head9);
				wyswietl_auta(head9);
				break;
			}
			case 11:
			{
				printf("				Posortowana lista aut malejąco po przebiegu samochodu: \n");
				Auto* head10 = wczytaj_z_pliku();
				head10 = sortuj_po_przebiegu_malejaco(head10);
				wyswietl_auta(head10);
				break;
			}
			case 12:
			{
				printf("				Posortowana lista aut rosnąco po numerze rejestracyjnym. \n");
				Auto* head11 = wczytaj_z_pliku();
				head11 = sortuj_po_numerze_rejestracyjnym_rosnaco(head11);
				wyswietl_auta(head11);
				break;
			}
			case 13:
			{
				printf("				Posortowana lista aut malejąco po numerze rejestracyjnym. \n");
				Auto* head12 = wczytaj_z_pliku();
				head12 = sortuj_po_numerze_rejestracyjnym_malejaco(head12);
				wyswietl_auta(head12);
				break;
			}
			}

			break;
		}
		case 3:													/// Case wywołujący funkcję do edycji danych samochodu
		{
			Auto* head13 = wczytaj_z_pliku();
			int szukane_id;
			printf("					Podaj ID samochodu który chcesz edytować: \n");
			scanf("%d", &szukane_id);
			edytuj_samochod(head13, szukane_id);
			break;
		}
		
		
		case 4:													/// Case wywołujący funkcję do dodawania danych klienta
		{
			dodaj_klienta(&head);
			break;
		}
		case 5:													/// Case wywołujący funkcję do wyświetlenia danych wszystkich klientów
		{
			printf("							Lista klientów:\n");
			Klient* lista_klientow = wczytaj();
			wyswietl(lista_klientow);
			break;
		}
		case 6:													/// Case wywołujący funkcję do edycji danych klienta
		{
			Klient* head20 = wczytaj();
			int szukany_numer_karty;
			printf("					Podaj numer karty klienta, którego chcesz edytować: \n");
			scanf("%d", &szukany_numer_karty);
			edytuj_klienta(head20, szukany_numer_karty);
			break;
		}
        
		case 7:													/// Case wywołujący funkcję do wyszukania danego samochodu
		{
			Auto* head13 = wczytaj_z_pliku();
			wyszukaj_auto(head13);
			break;
		}
		case 8:													/// Case wywołujący funkcję do usunięcia danego samochodu
		{
			char nr_rejestracyjny[20];
			printf("					Podaj numer rejestracyjny samochodu do usunięcia: ");
			while (getchar() != '\n');
			fgets(nr_rejestracyjny, sizeof(nr_rejestracyjny), stdin);
			nr_rejestracyjny[strcspn(nr_rejestracyjny, "\n")] = '\0';
			usun_samochod(nr_rejestracyjny);
			break;
		}
		case 9:													/// Case wywołujący funkcję do usunięcia danego klienta
		{
			char numer_karty[20];
			printf("					Podaj numer karty klienta do usunięcia: ");
			scanf("%s", numer_karty);
			usun_klienta(numer_karty);
			break;
		}
		case 10:												/// Case wywołujący funkcję do wypożyczenia danego samochodu klientowi
		{
			Auto* head14 = wczytaj_z_pliku();
			Klient* head15 = wczytaj();
			wypozycz_samochod(head14, head15);
			break;
		}
		case 11:												/// Case wywołujący funkcję do wyświetlenia listy wypożyczeń 
		{
			wyswietl_wypozyczenia();
			break;
		}
		case 12:												/// Case wywołujący funkcję do zwrotu samochodu 
		{
			
			int id_samochodu;

			printf("Podaj ID samochodu do zwrotu: ");
			scanf("%d", &id_samochodu);

			zwroc_samochod(id_samochodu);

			
			break;
		}
		case 13:												/// Case służący do przerwania pętli i zakończenia działania programu
		{
			break;
		}
		default:												/// Case obsługujący przypadek wpisania nieodpowiedniej liczby w programie
		{
			printf("Nieprawidłowa wartość. Wpisz ponownie:\n");
		}
		}

	}while (x != 13);

	printf("			Dziękujemy za skorzystanie z naszej wypożyczalni. Zapraszamy ponownie!");	/// Komunikat wyświetlający się po zakończeniu działania programu

	return 0;

}