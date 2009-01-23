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

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <unistd.h>
//#include <string.h>

//#include <config.h>

#include <gtk/gtk.h>
#include <glib/gprintf.h>

#include <cards.h>
#include <deck.h>
#include <hand.h>
#include <player.h>
#include <table.h>
#include <trick.h>



/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif



int
main(int argc, char *argv[])
{
	int i;
	
 	#ifdef ENABLE_NLS
		bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
		bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
		textdomain(GETTEXT_PACKAGE);
	#endif
	
	gtk_set_locale();
	gtk_init(&argc, &argv);
	
	
/* 	// carta
 * 	SuecaCarta *sc = sueca_cards_new (PAUS, BISCA);
 * 	g_printf("NAIPE: %d\n", sueca_cards_get_naipe (sc));
 * 	g_printf("TIPO: %d\n", sueca_cards_get_tipo (sc));
 * 	g_printf("VALOR: %d\n", sueca_cards_get_value (sc));
 * 	g_printf("NOME CARTA: %s\n", sueca_cards_get_name (sc)->str);
 * 	g_printf("PONTUAÇÃO: %d\n", sueca_cards_get_pontuation (sc));
 * 	sueca_cards_print (sc);
 * 	sueca_cards_delete (sc);
 */
/* 	// deck
 * 	SuecaBaralho *sb = sueca_deck_new ();
 * 	printf("\n");
 * 	sueca_deck_print (sb);
 * 	sueca_deck_shuffle (sb);
 * 	printf("\n");
 * 	sueca_deck_print (sb);
 * 	sueca_deck_cut (sb);
 * 	printf("\n");
 * 	sueca_deck_print (sb);
 * 	SuecaCarta *sbc = sueca_deck_pop (sb);
 * 	printf("\n");
 * 	sueca_cards_print (sbc);
 * 	printf("\n");
 * 	sueca_deck_print (sb);
 * 	sueca_deck_delete (sb);
 */
/* 	// hand
 * 	SuecaMao *sm = sueca_hand_new ();
 * 	SuecaBaralho *smb = sueca_deck_new ();
 * 	sueca_deck_shuffle (smb);
 * 	for(i = 0; i < 10; i++)
 * 		sueca_hand_insert (sm, sueca_deck_pop (smb), 0);
 * 	sueca_hand_print (sm);
 * 	printf("\n");
 * 	sueca_hand_sort (sm);
 * 	sueca_hand_print (sm);
 */
	// player // equipa
	SuecaJogador *j1 = sueca_player_new ("ja");
	SuecaJogador *j2 = sueca_player_new ("je");
	SuecaJogador *j3 = sueca_player_new ("jo");
	SuecaJogador *j4 = sueca_player_new ("ju");
	
	sueca_player_print (j1);
	g_printf("\n");
	sueca_player_print (j2);
	g_printf("\n");
	sueca_player_print (j3);
	g_printf("\n");
	sueca_player_print (j4);
	g_printf("\n");
	
	SuecaEquipa *e1 = sueca_team_new ("ae", j1, j2);
	sueca_team_inc_vitorias (e1, 4);
	sueca_team_add_vaza (e1, sueca_cards_new (1, 2));
	sueca_team_print (e1);
	
	g_printf("\n");
	SuecaEquipa *e2 = sueca_team_new ("ou", j3, j4);
	sueca_team_inc_vitorias (e2, 1);
	sueca_team_add_vaza (e2, sueca_cards_new (3, 2));
	sueca_team_print (e2);
	
	g_printf("\n");
	SuecaMesa *m = sueca_table_new (e1, e2);
	sueca_table_print (m);
	
	sueca_table_delete (m);
	//sueca_team_delete (e1);
	//sueca_player_delete (j1);
	//sueca_player_delete (j2);
	

	
	//gtk_main();
	return 0;
}
