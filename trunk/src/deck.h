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

#ifndef _DECK_H_
#define _DECK_H_

#define SUECA_DECK_SIZE 40
#define SUECA_SUIT_SIZE 40/4

#include <glib.h>

#include <cards.h>

typedef struct _SuecaBaralho SuecaBaralho;

SuecaBaralho *sueca_deck_new();
void sueca_deck_shuffle(SuecaBaralho *);
void sueca_deck_cut(SuecaBaralho *);
SuecaCarta *sueca_deck_pop(SuecaBaralho *);

void sueca_deck_printf(const SuecaBaralho *);

#endif /* _DECK_H_ */
