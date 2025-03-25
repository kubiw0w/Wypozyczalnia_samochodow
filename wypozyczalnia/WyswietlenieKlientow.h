#pragma once

typedef struct Klient
{
	long long int numer_karty; /**< Numer karty klienta. */
	char imie[20]; /**< Imie klienta. */
	char nazwisko[20]; /**< Nazwisko klienta. */
	char adres[50]; /**< Adres zamieszkania klienta. */
	long long int telefon; /**< Numer telefonu klienta. */
	struct Klient* next; /**< Wska�nik na nast�pny element listy klient�w. */
	struct Klient* prev; /**< Wska�nik na poprzedni element listy klient�w. */
}Klient;

Klient* wczytaj();
Klient* wyswietl(Klient* head);
