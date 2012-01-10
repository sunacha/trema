/*
 * Wrapper class for listening to events.
 *
 * Author: Jari Sundell
 *
 * Copyright (C) 2011 axsh Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
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


#ifndef RUBY_TREMA_EVENT_CONNECTION_H
#define RUBY_TREMA_EVENT_CONNECTION_H


#include "ruby.h"

#include "../../src/lib/event_handler.h"

extern VALUE cEventConnection;


void Init_event_connection( void );

extern VALUE create_event_connection( int fd, event_fd_callback read_callback, void* read_data, event_fd_callback write_callback, void* write_data );


#endif // RUBY_TREMA_EVENT_CONNECTION_H


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
