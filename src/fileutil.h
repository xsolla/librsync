/*= -*- c-basic-offset: 4; indent-tabs-mode: nil; -*- *
 *
 * librsync -- library for network deltas
 * 
 * Copyright (C) 2000, 2001 by Martin Pool <mbp@sourcefrog.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

FILE * rs_file_open(char const *filename, char const * mode, int force);

#if _WIN32
FILE *rs_file_open_ws(const wchar_t *filename, const wchar_t *mode, int force);
#endif
int rs_file_close(FILE * file);
void rs_get_filesize(FILE *f, rs_long_t *size);
