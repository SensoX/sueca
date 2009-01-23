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

void
sueca_cards_delete(SuecaCarta *carta)
{
	g_free(carta);
}

SuecaCardsNaipe
sueca_cards_get_naipe(const SuecaCarta *carta)
{
	if(carta == NULL)
		return -1;
	return carta->naipe;
}

SuecaCardsTipo
sueca_cards_get_tipo(const SuecaCarta *carta)
{
	if(carta == NULL)
		return -1;
	return carta->tipo;
}

gint
sueca_cards_get_value(const SuecaCarta *carta)
{
	if(carta == NULL)
		return -1;
	return sueca_cards_get_naipe(carta) + sueca_cards_get_tipo(carta);
}

GString *
sueca_cards_get_name(const SuecaCarta *carta)
{
	if(carta == NULL)
		return NULL;
	int v;
	if((v = sueca_cards_get_value(carta)) == -1)
		return NULL;
	GString *s = g_string_new("");
	// naipe
	if(v > OUROS)
	{
		s = g_string_append (s, "OUROS");
		v -= 30;
	}
	else if (v > PAUS)
	{
		s = g_string_append (s, "PAUS");
		v -= 20;
	}
	else if (v > COPAS)
	{
		s = g_string_append (s, "COPAS");
		v -= 10;
	}
	else if (v > ESPADAS)
	{
		s = g_string_append (s, "ESPADAS");
	}
	// tipo
	if(v == DUQUE)
		s = g_string_prepend (s, "DUQUE");
	else if(v == TERNO)
		s = g_string_prepend (s, "TERNO");
	else if(v == QUADRA)
		s = g_string_prepend (s, "QUADRA");
	else if(v == QUINA)
		s = g_string_prepend (s, "QUINA");
	else if(v == SENA)
		s = g_string_prepend (s, "SENA");
	else if(v == DAMA)
		s = g_string_prepend (s, "DAMA");
	else if(v == VALETE)
		s = g_string_prepend (s, "VALETE");
	else if(v == REI)
		s = g_string_prepend (s, "REI");
	else if(v == BISCA)
		s = g_string_prepend (s, "BISCA");
	else if(v == AS)
		s = g_string_prepend (s, "AS");
	return s;
}

gint
sueca_cards_get_pontuation(const SuecaCarta *carta)
{
	if(carta == NULL)
		return -1;
	gint t = sueca_cards_get_tipo (carta);
	if(t == AS)
		return 11;
	else if(t == BISCA)
		return 10;
	else if(t == REI)
		return 4;
	else if(t == VALETE)
		return 3;
	else if(t == DAMA)
		return 2;
	return 0;
}

void
sueca_cards_print(const SuecaCarta *carta)
{
	if(carta == NULL)
		return;
	
	g_printf("%s", sueca_cards_get_name(carta)->str);
}
