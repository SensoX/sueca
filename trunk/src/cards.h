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

#ifndef _CARDS_H_
#define _CARDS_H_

#include <glib.h>

typedef struct _SuecaCarta SuecaCarta;

typedef enum
{
	ESPADAS = 0,	/* spades */
	COPAS = 10,		/* hearts */
	PAUS = 20,		/* clubs */
	OUROS = 30,		/* diamonds */
} SuecaCardsNaipe;	/* suit */

typedef enum
{
	DUQUE = 1,		/* Two */
	TERMO,			/* Three */
	QUADRA,			/* Four */
	QUINA,			/* Five */
	SENA,			/* Six */
    DAMA,			/* Queen */
	VALETE,			/* Jack */
	REI,			/* King */
	BISCA,			/* Seven */
	AS				/* ACE */
} SuecaCardsTipo;	/* rank */

SuecaCarta *sueca_cards_new(const SuecaCardsNaipe, const SuecaCardsTipo);
SuecaCardsNaipe sueca_cards_get_naipe(const SuecaCarta *);
SuecaCardsTipo sueca_cards_get_tipo(const SuecaCarta *);
int sueca_cards_get_type_value(const SuecaCardsTipo);

void sueca_cards_printf(const SuecaCarta *);

#endif /* _CARDS_H_ */
