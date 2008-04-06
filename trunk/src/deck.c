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
	SuecaCarta *carta[NUMBER_OF_CARDS];
	gint size;
};

void sueca_deck_push(SuecaBaralho *baralho, SuecaCarta *carta);

SuecaBaralho *
sueca_deck_new()
{
	gint i, j;
	SuecaBaralho *baralho = g_new0(SuecaBaralho, 1);
		
	baralho->size = 0;
	for(i = ESPADAS; i <= OUROS; i+= 10)
	{
		for(j = DUQUE; j <= AS; j++)
		{
			baralho->carta[baralho->size] = sueca_cards_new (i, j);
			baralho->size++;
		}
	}
	
	sueca_deck_shuffle(baralho);
	
	return baralho;
}

void
sueca_deck_shuffle(SuecaBaralho *baralho)
{
	gint k;
	SuecaCarta *temp;
	
	if(baralho == NULL)
		return;
	
	srandom(time(NULL));
	
	for(k = 0; k < baralho->size; k++)
	{
		gint r = random() % NUMBER_OF_CARDS;
		temp = baralho->carta[k];
		baralho->carta[k] = baralho->carta[r];
		baralho->carta[r] = temp;
	}
}

void
sueca_deck_cut(SuecaBaralho *baralho)
{
	SuecaBaralho *b1, *b2;
	gint r, k;
	
	if(baralho == NULL)
		return;
	
	srandom(time(NULL));
	r = 1 + random() % (NUMBER_OF_CARDS - 1);
	
	b1 = g_new0(SuecaBaralho, 1);
	b2 = g_new0(SuecaBaralho, 1);
	
	for(k = 0; k < r; k++)
	{
		sueca_deck_push(b1, sueca_deck_pop(baralho));
	}
	for(k = r; k < NUMBER_OF_CARDS; k++)
	{
		sueca_deck_push(b2, sueca_deck_pop(baralho));
	}
	
	for(k = 0; k < r; k++)
	{
		sueca_deck_push(baralho, sueca_deck_pop(b1));
	}
	for(k = r; k < NUMBER_OF_CARDS; k++)
	{
		sueca_deck_push(baralho, sueca_deck_pop(b2));
	}
}

void
sueca_deck_push(SuecaBaralho *baralho, SuecaCarta *carta)
{
	if(baralho == NULL || carta == NULL)
		return;
	
	if(baralho->size + 1 <= 40)
	{
		baralho->carta[baralho->size] = carta;
		baralho->size++;
	}
}

SuecaCarta *
sueca_deck_pop(SuecaBaralho *baralho)
{
	SuecaCarta *carta;
	
	if(baralho == NULL)
		return NULL;

	if(baralho->size - 1 >= 0)
	{
		baralho->size--;
		carta = baralho->carta[baralho->size];
		baralho->carta[baralho->size] = NULL;
		return carta;
	}
	return NULL;
}

void
sueca_deck_printf(const SuecaBaralho *baralho)
{
	gint k;
	
	if(baralho == NULL)
		return;
	
	for(k = 0; k < baralho->size; k++)
		sueca_cards_printf(baralho->carta[k]);
	printf("\n");
}
