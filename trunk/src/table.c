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
	SuecaEquipa *equipas[1];
	SuecaJogador *jogadores[4];
	SuecaCarta *vaza[4];
	gint jogador;
};

SuecaMesa *
sueca_table_new(SuecaEquipa* equipa_0, SuecaEquipa* equipa_1)
{
	if(equipa_0 == NULL || equipa_1 == NULL)
		return NULL;
	
	SuecaMesa *mesa = g_new0 (SuecaMesa, 1);
	
	mesa->baralho = sueca_deck_new ();
	
	mesa->equipas[0] = equipa_0;
	mesa->jogadores[0] = sueca_team_get_player (equipa_0, 0);
	mesa->jogadores[2] = sueca_team_get_player (equipa_0, 1);
	
	mesa->equipas[1] = equipa_1;
	mesa->jogadores[1] = sueca_team_get_player (equipa_0, 0);
	mesa->jogadores[3] = sueca_team_get_player (equipa_0, 1);
	
	return mesa;
}

void
sueca_table_delete(SuecaMesa *mesa)
{
	if(mesa == NULL)
		return;
	
	sueca_deck_delete (mesa->baralho);
	sueca_team_delete (mesa->equipas[0]);
	sueca_team_delete (mesa->equipas[1]);
	gint k;
	for(k = 0; k < 4; k++)
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
	
	//mesa->primeiro = g_random_int_range(0, 4);
	
//	sueca_player_play (mesa->jogadores[mesa->primeiro], mesa->vaza, mesa->trunfo);
	
}

void
sueca_table_print(const SuecaMesa *mesa)
{
	if(mesa == NULL)
		return;
	
	gint k;
	
	g_printf("[");
	sueca_deck_print (mesa->baralho);
	g_printf(", [");
	sueca_team_print (mesa->equipas[0]);
	g_printf(", ");
	sueca_team_print (mesa->equipas[1]);
	g_printf("] ,[");
	for(k = 0; k < 4; k++)
		sueca_cards_print (mesa->vaza[k]);
	g_printf("]]");		
}
