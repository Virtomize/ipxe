/*
 * Copyright (C) 2021 Carsten Seeger <cseeger@virtomize.com>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * You can also choose to distribute this program under the terms of
 * the Unmodified Binary Distribution Licence (as given in the file
 * COPYING.UBDL), provided that you have satisfied its requirements.
 */

FILE_LICENCE ( GPL2_OR_LATER_OR_UBDL );

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <time.h>
#include <ipxe/command.h>
#include <ipxe/parseopt.h>
#include <ipxe/timer.h>

/** @file
 *
 * Ping command
 *
 */

/** "expire" options */
struct expire_options {
	/** timestamp */
	unsigned int timestamp;
};

/** "expire" option list */
static struct option_descriptor expire_opts[] = {
};

/** "expire" command descriptor */
static struct command_descriptor expire_cmd =
	COMMAND_DESC ( struct expire_options, expire_opts, 1, 1, "<timestamp>" );

/**
 * The "expire" command
 *
 * @v argc		Argument count
 * @v argv		Argument list
 * @ret rc		Return status code
 */
static int expire_exec ( int argc, char **argv ) {
  struct expire_options opts;
  unsigned int now;
  unsigned int timestamp;
  int rc;


  /* Initialise options */
  memset ( &opts, 0, sizeof ( opts ) );

  /* Parse options */
  if ( ( rc = reparse_options ( argc, argv, &expire_cmd, &opts ) ) != 0 )
    return rc;


  /* Parse timestamp */
  if ( ( rc = parse_integer ( argv[optind], &timestamp ) ) != 0 )
    return rc;


  now = (int)time(NULL);

  printf ( "checking now - timestamp: %d - %d\n", now, timestamp );

  if ( now > timestamp ) {
    printf ( "date expired\n" );
    return -EACCES;
  }

	return 0;
}

/** expire command */
struct command expire_command __command = {
	.name = "expire",
	.exec = expire_exec,
};
