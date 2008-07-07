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

#include <team.h>

struct _SuecaEquipa
{
	gchar *name;
	SuecaJogador *jogador[2];
	SuecaVaza *vazas;
	int vitorias;
};

void sueca_team_set_name(SuecaEquipa *, const gchar *);

SuecaEquipa *
sueca_team_new(const gchar *name, SuecaJogador *player_0, SuecaJogador *player_1)
{
	if(name == NULL || player_0 == NULL || player_1 == NULL)
		return NULL;
	
	SuecaEquipa *equipa;
	
	equipa = g_new0(SuecaEquipa, 1);
	
	equipa->name = g_new0(gchar, SUECA_TEAM_NAME_SIZE);
	sueca_team_set_name(equipa, name);
	
	equipa->jogador[0] = player_0;
	equipa->jogador[1] = player_1;
	
	equipa->vazas = sueca_trick_new();
	
	equipa->vitorias = 0;
	
	return equipa;
}

void
sueca_team_delete(SuecaEquipa *equipa)
{
	if(equipa == NULL)
		return;
	
	g_free(equipa->name);
	sueca_player_delete (equipa->jogador[0]);
	sueca_player_delete (equipa->jogador[1]);
	sueca_trick_delete (equipa->vazas);
	g_free(equipa);
}

void
sueca_team_set_name(SuecaEquipa *equipa, const gchar *name)
{
	if(equipa == NULL || name == NULL)
		return;
	
	g_strlcpy(equipa->name, name, SUECA_TEAM_NAME_SIZE);
}

gchar *
sueca_team_get_name(const SuecaEquipa *equipa)
{		
	if(equipa == NULL)
		return NULL;
	
	gchar *name = g_new0(gchar, SUECA_PLAYER_NAME_SIZE);
	
	g_strlcpy(name, equipa->name, SUECA_PLAYER_NAME_SIZE);
	
	return name;
}

void
sueca_team_inc_vitorias(SuecaEquipa *equipa, const gint num)
{
	if(equipa == NULL)
		return;
	
	equipa->vitorias += num;
}

void
sueca_team_reset_vitorias(SuecaEquipa *equipa)
{
	if(equipa == NULL)
		return;
	
	equipa->vitorias = 0;
}

int
sueca_team_get_vitorias(const SuecaEquipa *equipa)
{
	if(equipa == NULL)
		return -1;
	
	return equipa->vitorias;
}

void
sueca_team_add_vaza(SuecaEquipa *equipa, const SuecaCarta *carta)
{
	if(equipa == NULL || carta == NULL)
		return;
	
	sueca_trick_append (equipa->vazas, carta);
}

SuecaJogador *
sueca_team_get_player(const SuecaEquipa *equipa, const gint num_jogador)
{
	if(equipa == NULL)
		return NULL;
	
	if(num_jogador == 0)
		return equipa->jogador[0];
	if(num_jogador == 1)
		return equipa->jogador[1];
	return NULL;
}

void
sueca_team_print(const SuecaEquipa *equipa)
{
	if(equipa == NULL)
		return;
	
	g_printf("[\"%s\", [", equipa->name);
	sueca_player_print(equipa->jogador[0]);
	g_printf(", ");
	sueca_player_print(equipa->jogador[1]);
	g_printf("], ");
	sueca_trick_print (equipa->vazas);
	g_printf(", %d]", equipa->vitorias);
}
