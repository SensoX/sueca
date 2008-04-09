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

#include <stdio.h>
#include <string.h>

struct _SuecaTeam
{
	gchar *name;
	GList *jogadores;
};

SuecaTeam *
sueca_team_new(const gchar *name)
{
	SuecaTeam *team = g_new0(SuecaTeam, 1);
	
	team->name = g_new0(gchar, SUECA_TEAM_NAME_SIZE);
	sueca_team_set_name(team, name);
	
	return team;
}

void
sueca_team_delete_players(gpointer data, gpointer user_data)
{
	sueca_player_delete ((SuecaPlayer*) data);
}

void
sueca_team_delete(SuecaTeam *equipa)
{
	g_list_foreach(equipa->jogadores, sueca_team_delete_players, NULL);
	g_free(equipa);
}

void
sueca_team_set_name(SuecaTeam *equipa, const gchar *name)
{
	if(equipa == NULL || name == NULL)
		return;
	
	g_strlcpy(equipa->name, name, SUECA_TEAM_NAME_SIZE);
}

gchar *
sueca_team_get_name(const SuecaTeam *equipa)
{
	gchar *name = g_new0(gchar, SUECA_PLAYER_NAME_SIZE);
		
	if(equipa == NULL)
		return NULL;
	
	g_strlcpy(name, equipa->name, SUECA_PLAYER_NAME_SIZE);
	
	return name;
}

void
sueca_team_add_player(SuecaTeam *equipa, const SuecaPlayer *jogador)
{
	if(equipa == NULL)
		return;
	
	if(g_list_length (equipa->jogadores) < SUECA_TEAM_NUMBER_OF_PLAYERS)
		equipa->jogadores = g_list_append (equipa->jogadores, (gpointer)jogador);
}

void
sueca_team_printf(const SuecaTeam *equipa)
{
	gint size, k;
	
	if(equipa == NULL)
		return;
	
	size = g_list_length (equipa->jogadores);
	
	for(k = 0; k < size; k++)
		sueca_player_printf (g_list_nth_data (equipa->jogadores, k));
	printf("\n");
}
