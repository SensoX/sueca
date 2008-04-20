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

#ifndef _HAND_H_
#define _HAND_H_

#define SUECA_HAND_SIZE 10

#include <glib.h>
#include <glib/gprintf.h>

#include <cards.h>

typedef struct _SuecaMao SuecaMao;

SuecaMao *sueca_hand_new(void);
void sueca_hand_delete(SuecaMao *);
void sueca_hand_sort(SuecaMao *);
void sueca_hand_insert(SuecaMao *, const SuecaCarta *, const gint);
SuecaCarta *sueca_hand_remove(SuecaMao *, const gint);
void sueca_hand_print(const SuecaMao *);


#endif /* _HAND_H_ */
