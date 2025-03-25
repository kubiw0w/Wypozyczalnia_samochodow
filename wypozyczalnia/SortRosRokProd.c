#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>	
#include "WyswietlenieAut.h"
#include "SortRosRokProd.h"
#pragma warning(disable : 4996)	

/**
 * Funkcja sortuje list� samochod�w po warto�ci roku produkcji w kolejno�ci rosn�cej.
 * W wyniku sortowania, samochody zostan� ustawione w nowej kolejno�ci, zgodnie z kryterium
 * sortowania. Funkcja modyfikuje istniej�c� list� i zwraca wska�nik do nowej g�owy listy
 * (je�li kolejno�� si� zmieni�a) lub wska�nik do oryginalnej g�owy listy (je�li kolejno��
 * nie zmieni�a si�).
 *
 * \param glowa - Wska�nik do g�owy listy samochod�w.
 * \return Wska�nik do g�owy listy samochod�w po sortowaniu.
 */
Auto* sortuj_po_roku_produkcji_rosnaco(Auto* glowa)
{
    if (glowa == NULL || glowa->next == NULL) /// Warunek je�li lista jest pusta lub zawiera tylko jeden element, zwr�� list� bez zmian
    {
        return glowa;
    }

    Auto* posortowana = NULL; /// Inicjalizacja wska�nika na posortowan� list� jako pusty
    Auto* aktualna = glowa; /// Ustawienie aktualnej pozycji na pocz�tek listy

    while (aktualna != NULL) /// P�tla dop�ki nie osi�gni�to ko�ca listy
    {
        Auto* nastepna = aktualna->next; /// Zapami�tanie wska�nika na nast�pn� pozycj�

        if (posortowana == NULL || aktualna->rok_produkcji < posortowana->rok_produkcji) /// Warunek je�li posortowana lista jest pusta lub aktualny samoch�d ma mniejszy rok produkcji
        {
            aktualna->next = posortowana; /// Przypisanie wska�nika na kolejny samoch�d w posortowanej li�cie do aktualnego samochodu
            posortowana = aktualna; /// Przypisanie aktualnego samochodu jako nowy pocz�tek posortowanej listy
        }
        else
        {
            Auto* bufor = posortowana; /// Ustawienie wska�nika bufora na pocz�tek posortowanej listy

            while (bufor->next != NULL && bufor->next->rok_produkcji < aktualna->rok_produkcji) /// P�tla dop�ki nie osi�gni�to ko�ca listy bufora lub rok produkcji kolejnego samochodu jest mniejszy
            {
                bufor = bufor->next; /// Przesu� wska�nik bufora na kolejny samoch�d
            }

            aktualna->next = bufor->next; /// Przypisanie wska�nika na kolejny samoch�d w posortowanej li�cie do aktualnego samochodu
            bufor->next = aktualna; /// Przypisanie aktualnego samochodu jako kolejny samoch�d w posortowanej li�cie
        }

        aktualna = nastepna; /// Przesuni�cie wska�nika aktualnej pozycji na nast�pn� pozycj�
    }

    return posortowana; /// Zwr�cenie posortowanej listy samochod�w
}