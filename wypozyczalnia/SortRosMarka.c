#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>			
#include "WyswietlenieAut.h"
#include "SortRosMarka.h"
#pragma warning(disable : 4996)			

/**
 * Funkcja sortuje listê samochodów po wartoœci marce w kolejnoœci rosn¹cej.
 * W wyniku sortowania, samochody zostan¹ ustawione w nowej kolejnoœci, zgodnie z kryterium
 * sortowania. Funkcja modyfikuje istniej¹c¹ listê i zwraca wskaŸnik do nowej g³owy listy
 * (jeœli kolejnoœæ siê zmieni³a) lub wskaŸnik do oryginalnej g³owy listy (jeœli kolejnoœæ
 * nie zmieni³a siê).
 *
 * \param glowa - WskaŸnik do g³owy listy samochodów.
 * \return WskaŸnik do g³owy listy samochodów po sortowaniu.
 */
Auto* sortuj_po_marce_rosnaco(Auto* glowa)
{
    if (glowa == NULL || glowa->next == NULL) /// Warunek jeœli lista jest pusta lub zawiera tylko jeden element, zwróæ listê bez zmian
    {
        return glowa;
    }

    Auto* posortowana = NULL; /// Inicjalizacja wskaŸnika na posortowan¹ listê jako pusty
    Auto* aktualna = glowa; /// Ustawienie aktualnej pozycji na pocz¹tek listy

    while (aktualna != NULL) /// Pêtla dopóki nie osi¹gniêto koñca listy
    {
        Auto* nastepna = aktualna->next; /// Zapamiêtanie wskaŸnika na nastêpn¹ pozycjê

        if (posortowana == NULL || strcmp(aktualna->marka, posortowana->marka) < 0) /// Warunek jeœli posortowana lista jest pusta lub aktualny samochód ma mniejsz¹ markê
        {
            aktualna->next = posortowana; /// Przypisanie wskaŸnika na kolejny samochód w posortowanej liœcie do aktualnego samochodu
            posortowana = aktualna; /// Przypisanie aktualnego samochodu jako nowy pocz¹tek posortowanej listy
        }
        else
        {
            Auto* bufor = posortowana; /// Ustawienie wskaŸnika bufora na pocz¹tek posortowanej listy

            while (bufor->next != NULL && strcmp(bufor->next->marka, aktualna->marka) < 0) /// Pêtla dopóki nie osi¹gniêto koñca listy bufora lub marka kolejnego samochodu jest mniejsza
            {
                bufor = bufor->next; /// Przesuñ wskaŸnik bufora na kolejny samochód
            }

            aktualna->next = bufor->next; /// Przypisanie wskaŸnika na kolejny samochód w posortowanej liœcie do aktualnego samochodu
            bufor->next = aktualna; /// Przypisanie aktualnego samochodu jako kolejny samochód w posortowanej liœcie
        }

        aktualna = nastepna; /// Przesuniêcie wskaŸnika aktualnej pozycji na nastêpn¹ pozycjê
    }

    return posortowana; /// Zwrócenie posortowanej listy samochodów
}