/*
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

#include "ruby.h"
#include "trema.h"

#include "event_connection.h"

#include "../../src/lib/event_handler.h"


extern VALUE mTrema;
VALUE cEventConnection;

typedef struct event_fd {
  int fd;
  event_fd_callback read_callback;
  event_fd_callback write_callback;
  void* read_data;
  void* write_data;
} event_fd;


static VALUE
event_connection_alloc( VALUE klass ) {
  struct event_fd *data = xmalloc( sizeof( struct event_fd ) );
  return Data_Wrap_Struct( klass, NULL, xfree, data );
}


static VALUE
event_connection_file_no( VALUE self ) {
  event_fd* data;
  Data_Get_Struct( self, struct event_fd, data );

  return INT2NUM( data->fd );
}


static VALUE
event_connection_notify_readable( VALUE self ) {
  event_fd* data;
  Data_Get_Struct( self, struct event_fd, data );

  if (data->read_callback != NULL) {
    data->read_callback( data->fd, data->read_data );
  }

  return self;
}


static VALUE
event_connection_notify_writable( VALUE self ) {
  event_fd* data;
  Data_Get_Struct( self, struct event_fd, data );

  if (data->write_callback != NULL) {
    data->write_callback( data->fd, data->write_data );
  }

  return self;
}


VALUE
create_event_connection( int fd, event_fd_callback read_callback, void* read_data, event_fd_callback write_callback, void* write_data ) {
  VALUE event_connection = rb_funcall( rb_eval_string( "Trema::EventConnection" ), rb_intern( "new" ), 0 );

  event_fd* data;
  Data_Get_Struct( event_connection, struct event_fd, data );
  
  data->fd = fd;
  data->read_callback = read_callback;
  data->read_data = read_data;
  data->write_callback = write_callback;
  data->write_data = write_data;

  return event_connection;
}

void
Init_event_connection() {
  cEventConnection = rb_define_class_under( mTrema, "EventConnection", rb_cObject );

  rb_define_alloc_func( cEventConnection, event_connection_alloc );

  rb_define_method( cEventConnection, "file_no", event_connection_file_no, 0 );
  rb_define_method( cEventConnection, "notify_readable", event_connection_notify_readable, 0 );
  rb_define_method( cEventConnection, "notify_writable", event_connection_notify_writable, 0 );
}


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
