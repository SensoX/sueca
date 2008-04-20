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

#include <player.h>

struct _SuecaJogador
{
	gchar *name;
	SuecaMao *mao;
};

SuecaJogador *
sueca_player_new(const gchar *name)
{
	SuecaJogador *player;
		
	if(name == NULL)
		return NULL;
	
	player = g_new0(SuecaJogador, 1);
	
	player->name = g_new0(gchar, SUECA_PLAYER_NAME_SIZE);
	sueca_player_set_name(player, name);
	
	player->mao = sueca_hand_new();
	
	return player;
}

void
sueca_player_delete(SuecaJogador *player)
{
	sueca_hand_delete(player->mao);
	g_free(player->name);
	g_free(player);
}

void
sueca_player_set_name(SuecaJogador *player, const gchar *name)
{
	if(player == NULL || name == NULL)
		return;
	
	g_strlcpy(player->name, name, SUECA_PLAYER_NAME_SIZE);
}

gchar *
sueca_player_get_name(const SuecaJogador *player)
{
	gchar *name = g_new0(gchar, SUECA_PLAYER_NAME_SIZE);
		
	if(player == NULL)
		return NULL;
	
	g_strlcpy(name, player->name, SUECA_PLAYER_NAME_SIZE);
	
	return name;
}

void
sueca_player_print(const SuecaJogador *player)
{
	if(player == NULL)
		return;
	
	g_printf("name:%s\n", sueca_player_get_name(player));
}
