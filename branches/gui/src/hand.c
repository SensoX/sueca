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

#include <hand.h>

struct _SuecaMao
{
	GList *cartas;
};

void sueca_hand_delete_cards(gpointer, gpointer);
gint sueca_hand_sort_cards(gconstpointer, gconstpointer);

SuecaMao *
sueca_hand_new()
{
	SuecaMao *mao = g_new0(SuecaMao, 1);
	mao->cartas = NULL;
	return mao;
}

void
sueca_hand_delete(SuecaMao *mao)
{
	if(mao == NULL)
		return;
	g_list_foreach(mao->cartas, sueca_hand_delete_cards, NULL);
	g_free(mao);
}

void
sueca_hand_delete_cards(gpointer data, gpointer user_data)
{
	sueca_cards_delete ((SuecaCarta*) data);
}

void
sueca_hand_sort(SuecaMao *mao)
{
	mao->cartas = g_list_sort (mao->cartas, sueca_hand_sort_cards);
}

gint
sueca_hand_sort_cards(gconstpointer a, gconstpointer b)
{
	a = (SuecaCarta *)a;
	b = (SuecaCarta *)b;
	
	if(sueca_cards_get_value (a) > sueca_cards_get_value (b))
		return -1;
	if(sueca_cards_get_value (a) < sueca_cards_get_value (b))
		return 1;
	return 0;
}

void
sueca_hand_insert(SuecaMao *mao, const SuecaCarta *carta, const gint pos)
{
	if(mao == NULL || carta == NULL || pos < 0 || pos >= SUECA_HAND_MAX_SIZE)
		return;
	if(g_list_length(mao->cartas) == SUECA_HAND_MAX_SIZE)
	   return;
	
	mao->cartas = g_list_insert (mao->cartas, (gpointer)carta, pos);
}

SuecaCarta *
sueca_hand_remove(SuecaMao *mao, const gint pos)
{	
	if(mao == NULL || pos < 0 || pos >= SUECA_HAND_MAX_SIZE)
		return NULL;
	
	SuecaCarta *carta;
	
	carta = g_list_nth_data (mao->cartas, pos);
	mao->cartas = g_list_delete_link (mao->cartas,
										  g_list_nth (mao->cartas, pos));
	mao->cartas = g_list_insert (mao->cartas, NULL, pos);
	return carta;
}

void
sueca_hand_print(const SuecaMao *mao)
{
	if(mao == NULL)
		return;
	
	GList * iter;
	
	g_printf("[");
	for(iter = mao->cartas; iter != NULL; iter = g_list_next(iter))
	{
		sueca_cards_print(g_list_nth_data (iter, 0));
		g_printf(" ");
	}
	g_printf("]");
}
