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
	SuecaEquipa *equipa_1;
	SuecaEquipa *equipa_2;
	SuecaJogador *jogadores[SUECA_NUMBER_OF_PLAYERS];
	SuecaCarta *vaza[SUECA_VAZA_MAX_SIZE];
	SuecaCarta trunfo;
	gint primeiro;
	gint jogador;
};

SuecaMesa *
sueca_table_new(const SuecaMesaInit *init)
{
	if(init->team_1_name == NULL || init->team_2_name == NULL ||
	   init->player_1_name == NULL || init->player_2_name == NULL ||
	   init->player_3_name == NULL || init->player_4_name == NULL)
		return NULL;
	
	SuecaMesa *mesa = g_new0 (SuecaMesa, 1);
	
	mesa->baralho = sueca_deck_new ();
	
	mesa->equipa_1 = sueca_team_new (init->team_1_name,
									 (mesa->jogadores[0] = sueca_player_new (init->player_1_name)),
									 (mesa->jogadores[2] = sueca_player_new (init->player_2_name)));
	mesa->equipa_2 = sueca_team_new (init->team_2_name,
									 (mesa->jogadores[1] = sueca_player_new (init->player_3_name)),
									 (mesa->jogadores[3] = sueca_player_new (init->player_4_name)));
	
	mesa->trunfo = -1;
	mesa->primeiro = -1;
	mesa->jogador = -1;
	
	return mesa;
}

void
sueca_table_delete(SuecaMesa *mesa)
{
	if(mesa == NULL)
		return;
	
	sueca_deck_delete (mesa->baralho);
	sueca_team_delete (mesa->equipa_1);
	sueca_team_delete (mesa->equipa_2);
	gint k;
	for(k = 0; k < SUECA_VAZA_MAX_SIZE; k++)
		sueca_cards_delete (mesa->vaza[k]);
	g_free(mesa);
}

void
sueca_table_start (SuecaMesa *mesa)
{
	if(mesa == NULL)
		return;

	g_random_set_seed(time(NULL));
	
	sueca_deck_shuffle (mesa->baralho);
	sueca_deck_cut (mesa->baralho);
	
	mesa->primeiro = g_random_int_range(0, SUECA_NUMBER_OF_PLAYERS);
	
	sueca_player_play (mesa->jogadores[mesa->primeiro], mesa->vaza, mesa->trunfo);
	
}

void
sueca_table_print(const SuecaMesa *mesa)
{
	if(mesa == NULL)
		return;
	
	gint k;
	
	g_printf("**MESA**\n");
	g_printf("BARALHO\n");
	sueca_deck_print (mesa->baralho);
	
	g_printf("\nEQUIPAS\n");
	sueca_team_print (mesa->equipa_1);
	sueca_team_print (mesa->equipa_2);
	
	g_printf("\nVAZA\n");
	for(k = 0; k < SUECA_VAZA_MAX_SIZE; k++)
		sueca_cards_print (mesa->vaza[k]);
	g_printf("\n");		
}
