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
	SuecaMesaInit *tinit = g_new0(SuecaMesaInit, 1);
	SuecaMesa *mesa;
	
 	#ifdef ENABLE_NLS
		bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
		bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
		textdomain(GETTEXT_PACKAGE);
	#endif
	
	gtk_set_locale();
	gtk_init(&argc, &argv);
	
	g_printf("SUECA\n");
	tinit->player_name[0] = "MARCO";
	tinit->player_name[1] = "RUI";
	tinit->player_name[2] = "ANDRE";
	tinit->player_name[3] = "JOEL";
	tinit->team_name[0] = "A";
	tinit->team_name[1] = "B";
	
	mesa = sueca_table_new (tinit);
	
	sueca_table_print (mesa);
	sueca_table_delete (mesa);
	
	//gtk_main();
	return 0;
}
