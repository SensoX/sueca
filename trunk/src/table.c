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

#include <table.h>

struct _SuecaMesa
{
	SuecaBaralho *baralho;
	GList *equipas; // 2 equipas
	GList *jogadores; // 4 jogadores
	GList *vaza; // 4 cartas
};

void sueca_table_delete_equipas(gpointer data, gpointer user_data);
void sueca_table_delete_vaza(gpointer data, gpointer user_data);


SuecaMesa *
sueca_table_new(const SuecaMesaInit *init)
{
	gint k;
	SuecaMesa *mesa = g_new0 (SuecaMesa, 1);
	
	mesa->baralho = sueca_deck_new ();
	
	for (k = 0; k < SUECA_TABLE_NUMBER_OF_PLAYERS; k++)
		mesa->jogadores = g_list_append(mesa->jogadores,
									  sueca_player_new (init->player_name[k]));
	for (k = 0; k < SUECA_NUMBER_OF_TEAMS; k++)
		mesa->equipas = g_list_append(mesa->equipas,
									sueca_team_new (init->team_name[k],
													g_list_nth_data(mesa->jogadores,
																	k),
													g_list_nth_data(mesa->jogadores,
																	k+2)));
	mesa->vaza = NULL;
	
	return mesa;
}

void
sueca_table_delete(SuecaMesa *mesa)
{
	sueca_deck_delete (mesa->baralho);
	g_list_foreach(mesa->equipas, sueca_table_delete_equipas, NULL);
	g_list_foreach(mesa->vaza, sueca_table_delete_vaza, NULL);
	g_free(mesa);
}

void
sueca_table_delete_equipas(gpointer data, gpointer user_data)
{
	sueca_team_delete ((SuecaEquipa*) data);
}

void
sueca_table_delete_vaza(gpointer data, gpointer user_data)
{
	sueca_cards_delete ((SuecaCarta*) data);
}

void
sueca_table_print(SuecaMesa *mesa)
{
	gint k;
	
	g_printf("MESA\n");
	g_printf("BARALHO\n");
	sueca_deck_print (mesa->baralho);
	g_printf("EQUIPAS\n");
	for(k = 0; k < SUECA_NUMBER_OF_TEAMS; k++)
		sueca_team_print (g_list_nth_data(mesa->equipas, k));
	g_printf("JOGADORES\n");
	for(k = 0; k < SUECA_TABLE_NUMBER_OF_PLAYERS; k++)
		sueca_player_print (g_list_nth_data(mesa->jogadores, k));
	g_printf("\nVAZA\n");
	for(k = 0; k < SUECA_VAZA_SIZE; k++)
		sueca_cards_print (g_list_nth_data(mesa->vaza, k));
	g_printf("\n");
}
