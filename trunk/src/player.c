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
	if(name == NULL)
		return NULL;
	
	SuecaJogador *player;
	
	player = g_new0(SuecaJogador, 1);
	
	player->name = g_new0(gchar, SUECA_PLAYER_NAME_SIZE);
	sueca_player_set_name(player, name);
	
	player->mao = sueca_hand_new();
	
	return player;
}

void
sueca_player_delete(SuecaJogador *jogador)
{
	if(jogador == NULL)
		return;
	
	sueca_hand_delete(jogador->mao);
	g_free(jogador->name);
	g_free(jogador);
}

void
sueca_player_set_name(SuecaJogador *jogador, const gchar *name)
{
	if(jogador == NULL || name == NULL)
		return;
	
	g_strlcpy(jogador->name, name, SUECA_PLAYER_NAME_SIZE);
}

gchar *
sueca_player_get_name(const SuecaJogador *jogador)
{
	if(jogador == NULL)
		return NULL;
	
	gchar *name = g_new0(gchar, SUECA_PLAYER_NAME_SIZE);
	
	g_strlcpy(name, jogador->name, SUECA_PLAYER_NAME_SIZE);
	
	return name;
}

void
sueca_player_set_hand(SuecaJogador *jogador, SuecaMao *mao)
{
	if(jogador == NULL || mao == NULL)
		return;
	
	jogador->mao = mao;
}

SuecaCarta *
sueca_player_play(SuecaJogador* jogador, SuecaCarta *vaza[], SuecaCarta *trunfo)
{
	
	return NULL;
}

void
sueca_player_print(const SuecaJogador *jogador)
{
	if(jogador == NULL)
		return;
	
	g_printf("\"%s\"", sueca_player_get_name(jogador));
}
