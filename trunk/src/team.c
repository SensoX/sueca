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
	SuecaJogador *jogador_1;
	SuecaJogador *jogador_2;
	GList *vazas;
	int vitorias;
};

void sueca_team_delete_cards(gpointer, gpointer);
void sueca_team_add_vaza_cards(gpointer, gpointer);

SuecaEquipa *
sueca_team_new(const gchar *name, SuecaJogador *player_1, SuecaJogador *player_2)
{
	if(name == NULL || player_1 == NULL || player_2 == NULL)
		return NULL;
	
	SuecaEquipa *equipa;
	
	equipa = g_new0(SuecaEquipa, 1);
	
	equipa->name = g_new0(gchar, SUECA_TEAM_NAME_SIZE);
	sueca_team_set_name(equipa, name);
	
	equipa->jogador_1 = player_1;
	equipa->jogador_2 = player_2;
	
	equipa->vazas = NULL;
	
	equipa->vitorias = 0;
	
	return equipa;
}

void
sueca_team_delete(SuecaEquipa *equipa)
{
	if(equipa == NULL)
		return;
	
	g_free(equipa->name);
	sueca_player_delete (equipa->jogador_1);
	sueca_player_delete (equipa->jogador_2);
	g_list_foreach(equipa->vazas, sueca_team_delete_cards, NULL);
	g_free(equipa);
}

void
sueca_team_delete_cards(gpointer data, gpointer user_data)
{
	sueca_cards_delete ((SuecaCarta*) data);
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
sueca_team_inc_vitorias(SuecaEquipa *equipa)
{
	if(equipa == NULL)
		return;
	
	equipa->vitorias++;
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
sueca_team_add_vaza(SuecaEquipa *equipa, GList *vaza)
{
	if(equipa == NULL || vaza == NULL)
		return;
	
	g_list_foreach(vaza, sueca_team_add_vaza_cards, equipa->vazas);
}

void
sueca_team_add_vaza_cards(gpointer data, gpointer user_data)
{
	user_data = g_list_append (user_data, data);
}

GList *
sueca_team_remove_vazas(SuecaEquipa *equipa)
{
	if(equipa == NULL)
		return NULL;
	
	GList *gltemp = equipa->vazas;
	equipa->vazas = NULL;
	return gltemp;
}

void
sueca_team_print(const SuecaEquipa *equipa)
{
	if(equipa == NULL)
		return;
	
	GList *iter;
	
	g_printf("\"%s\", ", equipa->name);
	
	g_printf("[");
	sueca_player_print(equipa->jogador_1);
	g_printf(", ");
	sueca_player_print(equipa->jogador_2);
	g_printf("], ");
	
	g_printf("[");
	for(iter = equipa->vazas; iter != NULL; iter = g_list_next(iter))
	{
		sueca_cards_print(g_list_nth_data (iter, 0));
		g_printf(" ");
	}
	g_printf("], ");
	
	g_printf("(%d)", equipa->vitorias);
}
