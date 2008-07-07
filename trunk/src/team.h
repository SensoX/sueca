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
 
#ifndef _TEAM_H_
#define _TEAM_H_

#define SUECA_TEAM_NAME_SIZE 11

#include <glib.h>
#include <glib/gprintf.h>

#include <player.h>
#include <trick.h>

typedef struct _SuecaEquipa SuecaEquipa;

SuecaEquipa *sueca_team_new(const gchar *, SuecaJogador *, SuecaJogador *);
void sueca_team_delete(SuecaEquipa *);
gchar *sueca_team_get_name(const SuecaEquipa *);
void sueca_team_inc_vitorias(SuecaEquipa *, const gint);
void sueca_team_reset_vitorias(SuecaEquipa *);
int sueca_team_get_vitorias(const SuecaEquipa *);
void sueca_team_add_vaza(SuecaEquipa *, const SuecaCarta *);
GList *sueca_team_remove_vazas(SuecaEquipa *);
SuecaJogador *sueca_team_get_player(const SuecaEquipa *, const gint);

void sueca_team_print(const SuecaEquipa *);

#endif /* _TEAM_H_ */
 
