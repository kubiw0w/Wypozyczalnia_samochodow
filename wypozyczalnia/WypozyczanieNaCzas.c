/*#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Auto
{
    int id;
    char nr_rejestracyjny[20];
    char marka[20];
    char model[20];
    int rok_produkcji;
    char kolor[30];
    int przebieg;
    int wypozyczony;
    struct Auto* next, * prev;
} Auto;

typedef struct Klient
{
    long long int numer_karty;
    char imie[20];
    char nazwisko[20];
    char adres[50];
    long long int telefon;
    struct Klient* next, * prev;
} Klient;

typedef struct Wypozyczenie
{
    int id_samochodu;
    long long int numer_karty;
    SYSTEMTIME data_wypozyczenia;
    int czas_wypozyczenia;
    struct Wypozyczenie* next, * prev;
} Wypozyczenie;

Auto* glowa_aut = NULL;
Klient* glowa_kl = NULL;
Wypozyczenie* glowa_wyp = NULL; 


void wypozycz_samochod(int id_samochodu, long long int numer_karty, int czas_wypozyczenia)
{
    Auto* samochod = glowa_aut;
    while (samochod != NULL)
    {
        if (samochod->id == id_samochodu)
        {
            break;
        }
        samochod = samochod->next;
    }


    Klient* klient = glowa_kl;
    while (klient != NULL)
    {
        if (klient->numer_karty == numer_karty)
        {
            break;
        }
        klient = klient->next;
    }

    if (samochod == NULL || klient == NULL)
    {
        printf("Nie znaleziono samochodu lub klienta.\n");
        return;
    }


    if (samochod->wypozyczony)
    {
        printf("Samochód o ID %d jest ju¿ wypo¿yczony.\n", id_samochodu);
        return;
    }


    SYSTEMTIME czas_teraz;
    GetLocalTime(&czas_teraz);

    Wypozyczenie* nowe_wyp = (Wypozyczenie*)malloc(sizeof(Wypozyczenie));
    nowe_wyp->id_samochodu = id_samochodu;
    nowe_wyp->numer_karty = numer_karty;
    nowe_wyp->data_wypozyczenia = czas_teraz;
    nowe_wyp->czas_wypozyczenia = czas_wypozyczenia;
    nowe_wyp->prev = NULL;
    nowe_wyp->next = NULL;
    if (glowa_wyp == NULL)
    {
        glowa_wyp = nowe_wyp;
    }
    else
    {
        nowe_wyp->next = glowa_wyp;
        glowa_wyp->prev = nowe_wyp;
        glowa_wyp = nowe_wyp;
    }
    samochod->wypozyczony = 1;
    printf("Samochód o ID %d zosta³ wypo¿yczony klientowi o numerze karty %lld.\n", id_samochodu, numer_karty);
}
*/