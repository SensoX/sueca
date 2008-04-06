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

#include <cards.h>

#include <stdio.h>

struct _SuecaCarta
{
	SuecaCardsNaipe naipe;
	SuecaCardsTipo tipo;
};

SuecaCarta *
sueca_cards_new(const SuecaCardsNaipe naipe, const SuecaCardsTipo tipo)
{
	SuecaCarta *carta = g_new0(SuecaCarta, 1);
	carta->naipe = naipe;
	carta->tipo = tipo;
	return carta;
}

SuecaCardsNaipe
sueca_cards_get_naipe(const SuecaCarta *carta)
{
	if(carta != NULL)
		return carta->naipe;
	return -1;
}

SuecaCardsTipo
sueca_cards_get_tipo(const SuecaCarta *carta)
{
	if(carta != NULL)
		return carta->tipo;
	return -1;
}

gint
sueca_cards_get_type_value(const SuecaCardsTipo t)
{
	if(t == AS)
		return 11;
	if(t == BISCA)
		return 10;
	if(t == REI)
		return 4;
	if(t == VALETE)
		return 3;
	if(t == DAMA)
		return 2;
	return 0;
}

void
sueca_cards_printf(const SuecaCarta *carta)
{
	if(carta == NULL)
		return;
	
	printf("%d\n", sueca_cards_get_naipe(carta) + sueca_cards_get_tipo(carta));
}
