/*
 * Copyright © 2014 Daiki Ueno
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the licence or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Daiki Ueno <dueno@src.gnome.org>
 */

#include "config.h"

#include <gio/gio.h>
#include <string.h>

static gboolean
key_event (GInputMethodEngine *engine,
           guint               keycode,
           gboolean            pressed,
           gpointer            user_data)
{
  if (keycode == 38 && pressed)
    {
      g_input_method_engine_commit (engine, "Hello!");
      return TRUE;
    }

  return FALSE;
}

static GInputMethodEngine *
create_engine (GInputMethod *inputmethod,
               const gchar  *client_id,
               gpointer      user_data)
{
  GInputMethodEngine *engine = g_input_method_engine_new (client_id);

  g_signal_connect (engine, "key-event", G_CALLBACK (key_event), NULL);

  return engine;
}

int
main (int argc, char **argv)
{
  GInputMethod *inputmethod;
  int status;

  inputmethod = g_input_method_new ("org.gtk.TestInputMethod",
                                    G_APPLICATION_FLAGS_NONE,
                                    NULL);
  g_signal_connect (inputmethod, "create-engine", G_CALLBACK (create_engine),
                    NULL);
#ifdef STANDALONE
  g_application_set_inactivity_timeout (G_APPLICATION (inputmethod), 10000);
#else
  g_application_set_inactivity_timeout (G_APPLICATION (inputmethod), 1000);
#endif

  status = g_application_run (G_APPLICATION (inputmethod), argc - 1, argv + 1);

  g_object_unref (inputmethod);

  g_print ("exit status: %d\n", status);

  return 0;
}
