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
 
#ifndef _TABLE_H_
#define _TABLE_H_

#define SUECA_NUMBER_OF_TEAMS 2
#define SUECA_TABLE_NUMBER_OF_PLAYERS 4
#define SUECA_VAZA_SIZE 4

#include <glib.h>
#include <glib/gprintf.h>

#include <cards.h>
#include <deck.h>
#include <player.h>
#include <team.h>

typedef struct _SuecaMesa SuecaMesa;
typedef struct _SuecaMesaInit SuecaMesaInit;

struct _SuecaMesaInit
{
	const gchar *player_name[SUECA_TABLE_NUMBER_OF_PLAYERS];
	const gchar *team_name[SUECA_NUMBER_OF_TEAMS];
};

SuecaMesa *sueca_table_new(const SuecaMesaInit *);
void sueca_table_delete(SuecaMesa *);


void sueca_table_print(SuecaMesa *);

#endif /* _TABLE_H_ */
