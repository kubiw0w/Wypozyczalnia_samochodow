#pragma once

typedef struct Klient
{
	long long int numer_karty; /**< Numer karty klienta. */
	char imie[20]; /**< Imie klienta. */
	char nazwisko[20]; /**< Nazwisko klienta. */
	char adres[50]; /**< Adres zamieszkania klienta. */
	long long int telefon; /**< Numer telefonu klienta. */
	struct Klient* next; /**< WskaŸnik na nastêpny element listy klientów. */
	struct Klient* prev; /**< WskaŸnik na poprzedni element listy klientów. */
}Klient;

Klient* wczytaj();
Klient* wyswietl(Klient* head);
