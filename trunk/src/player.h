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
 
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PLAYER_NAME_SIZE 21

#include <glib.h>

typedef struct _SuecaPlayer SuecaPlayer;

struct _SuecaPluginPlayer
{
	gushort cod;
	gchar *name;
	void (*set_mao)(void);
	
};

/* SuecaPlayer *sueca_player_new(const gchar *);
 * void sueca_player_delete(SuecaPlayer *);
 * void sueca_player_set_name(SuecaPlayer *, const gchar *);
 * gchar *sueca_player_get_name(const SuecaPlayer *player);
 * 
 * void sueca_player_printf(const SuecaPlayer *);
 */

#endif /* _PLAYER_H_ */

 
