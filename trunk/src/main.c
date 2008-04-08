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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <config.h>

#include <gtk/gtk.h>

#include <cards.h>
#include <deck.h>
#include <hand.h>
#include <player.h>
#include <table.h>



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
	SuecaBaralho *baralho;
/* 	SuecaPlayer *player;  */
	//SuecaCarta *carta;
	//int i;
	
 	#ifdef ENABLE_NLS
		bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
		bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
		textdomain(GETTEXT_PACKAGE);
	#endif
	
	gtk_set_locale();
	gtk_init(&argc, &argv);
	
	printf("SUECA\n");
	baralho = sueca_deck_new ();
	sueca_deck_printf (baralho);
/* 	printf("SUECA\n");
 * 	sueca_deck_push (baralho, sueca_deck_pop (baralho));
 * 	sueca_deck_printf (baralho);
 */
/* 	player = sueca_player_new("marco");
 * 	sueca_player_printf(player);
 * 	sueca_player_delete(player);
 * 	player = sueca_player_new("andré");
 * 	sueca_player_printf(player);
 * 	sueca_player_delete(player);
 */
	sueca_deck_delete (baralho);
	
	//gtk_main();
	return 0;
}
