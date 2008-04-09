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

#include <stdio.h>

struct _SuecaTable
{
	SuecaBaralho *baralho;
	SuecaPlayer *team; // 2 equipas
	SuecaCarta *cartas; // 4 cartas
};

SuecaTable *
sueca_table_new()
{
	//gint k;
	SuecaTable *table = g_new0 (SuecaTable, 1);
	
	table->baralho = sueca_deck_new ();
/* 	table->player =g_new0 (SuecaPlayer, SUECA_NUMBER_OF_PLAYERES);
 * 	for(k = 0; k < SUECA_NUMBER_OF_PLAYERES; k++)
 * 		table->player[k] = sueca_player_new ();
 */
	
	return table;
}
