/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Sueca
 * Copyright (C) 2008 Marco Monteiro <nok.marco@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <deck.h>

#include <stdio.h>
#include <stdlib.h>

struct _SuecaBaralho
{
	GList *cartas;
};

void sueca_deck_push(SuecaBaralho *baralho, const SuecaCarta *carta);

SuecaBaralho *
sueca_deck_new()
{
	gint i, j;
	SuecaBaralho *baralho = g_new0 (SuecaBaralho, 1);
	baralho->cartas = NULL;
	
	for(i = ESPADAS; i <= OUROS; i+= SUECA_SUIT_SIZE)
	{
		for(j = DUQUE; j <= AS; j++)
		{
			baralho->cartas = g_list_prepend (baralho->cartas, (gpointer)sueca_cards_new(i, j));
		}
	}
	baralho->cartas = g_list_reverse (baralho->cartas);
	
	//sueca_deck_shuffle(baralho);
	//sueca_deck_cut (baralho);
	
	return baralho;
}

void
sueca_deck_delete_cards(gpointer data, gpointer user_data)
{
	sueca_cards_delete ((SuecaCarta*) data);
}

void
sueca_deck_delete(SuecaBaralho *baralho)
{
	g_list_foreach(baralho->cartas, sueca_deck_delete_cards, NULL);
	g_free(baralho);
}

void
sueca_deck_shuffle(SuecaBaralho *baralho)
{
	gint size, k;
	gpointer temp;
	GList *gltemp;
	
	if(baralho == NULL)
		return;
	
	size = g_list_length (baralho->cartas);
	g_random_set_seed(time(NULL));
	
	for(k = 0; k < size; k++)
	{
		gint32 r = g_random_int_range(0, SUECA_DECK_SIZE);
		
		temp = g_list_nth_data (baralho->cartas, k);
		
		gltemp = g_list_nth (baralho->cartas, k);
		baralho->cartas = g_list_insert (baralho->cartas, g_list_nth_data (baralho->cartas, r), k);
		baralho->cartas = g_list_delete_link (baralho->cartas, gltemp);
		
		gltemp = g_list_nth (baralho->cartas, r);
		baralho->cartas = g_list_insert (baralho->cartas, temp, r);
		baralho->cartas = g_list_delete_link (baralho->cartas, gltemp);
	}
}

void
sueca_deck_cut(SuecaBaralho *baralho)
{
	SuecaBaralho *b1, *b2;
	gint32 r;
	gint k;
	
	if(baralho == NULL)
		return;
	
	g_random_set_seed(time(NULL));
	r = g_random_int_range(1, SUECA_DECK_SIZE - 1);
	
	b1 = g_new0(SuecaBaralho, 1);
	b2 = g_new0(SuecaBaralho, 1);
	
	for(k = 0; k < r; k++)
	{
		sueca_deck_push(b1, sueca_deck_pop(baralho));
	}
	for(k = r; k < SUECA_DECK_SIZE; k++)
	{
		sueca_deck_push(b2, sueca_deck_pop(baralho));
	}
	
	for(k = 0; k < r; k++)
	{
		sueca_deck_push(baralho, sueca_deck_pop(b1));
	}
	for(k = r; k < SUECA_DECK_SIZE; k++)
	{
		sueca_deck_push(baralho, sueca_deck_pop(b2));
	}
	
	g_free(b1);
	g_free(b2);
}

void
sueca_deck_push(SuecaBaralho *baralho, const SuecaCarta *carta)
{
	gint size;
	
	if(baralho == NULL || carta == NULL)
		return;
	
	size = g_list_length (baralho->cartas);
	
	if(size < SUECA_DECK_SIZE)
		baralho->cartas = g_list_append (baralho->cartas, (gpointer)carta);
}

SuecaCarta *
sueca_deck_pop(SuecaBaralho *baralho)
{
	SuecaCarta *carta;
	GList *gltemp;
	gint size;
	
	if(baralho == NULL)
		return NULL;
	
	size = g_list_length (baralho->cartas);

	if(size > 0)
	{
		carta = g_list_nth_data (baralho->cartas, size - 1);
		gltemp = g_list_nth (baralho->cartas, size - 1);
		baralho->cartas = g_list_delete_link (baralho->cartas, gltemp);
		return carta;
	}
	return NULL;
}

void
sueca_deck_printf(const SuecaBaralho *baralho)
{
	gint size, k;
	
	if(baralho == NULL)
		return;
	
	size = g_list_length (baralho->cartas);
	
	for(k = 0; k < size; k++)
		sueca_cards_printf (g_list_nth_data (baralho->cartas, k));
	printf("\n");
}
