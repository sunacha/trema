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


#include "event_handler.h"
#include "event_connection.h"
#include "event_timer.h"
#include "timer.h"
#include "trema.h"

#include "../../src/lib/event_handler.h"

extern VALUE mTrema;
VALUE cEventHandler;
VALUE cCurrentEventHandler;


static VALUE
eh_init_event_handler( VALUE self ) {
  error( "Called unmodified init_event_handler function." );
  return self;
}


static VALUE
eh_finalize_event_handler( VALUE self ) {
  error( "Called unmodified finalize_event_handler function." );
  return self;
}


static VALUE
eh_start_event_handler( VALUE self ) {
  error( "Called unmodified start_event_handler function." );
  return self;
}


static VALUE
eh_stop_event_handler( VALUE self ) {
  error( "Called unmodified stop_event_handler function." );
  return self;
}


static VALUE
eh_run_event_handler_once( VALUE self ) {
  error( "Called unmodified run_event_handler_once function." );
  return self;
}


static VALUE
eh_set_fd_handler( VALUE self, VALUE fd, VALUE event_connection ) {
  UNUSED( fd );
  UNUSED( event_connection );

  error( "Called unmodified set_fd_handler function." );
  return self;
}


static VALUE
eh_delete_fd_handler( VALUE self, VALUE fd ) {
  UNUSED( fd );

  error( "Called unmodified delete_fd_handler function." );
  return self;
}


static VALUE
eh_set_readable( VALUE self, VALUE fd, VALUE state ) {
  UNUSED( fd );
  UNUSED( state );

  error( "Called unmodified set_readable function." );
  return self;
}


static VALUE
eh_set_writable( VALUE self, VALUE fd, VALUE state ) {
  UNUSED( fd );
  UNUSED( state );

  error( "Called unmodified set_writable function." );
  return self;
}


static VALUE
eh_readable( VALUE self, VALUE fd ) {
  UNUSED( fd );
  UNUSED( self );

  error( "Called unmodified readable function." );
  return Qfalse;
}


static VALUE
eh_writable( VALUE self, VALUE fd ) {
  UNUSED( fd );
  UNUSED( self );

  error( "Called unmodified writable function." );
  return Qfalse;
}


static VALUE
eh_init_timer( VALUE self ) {
  error( "Called unmodified init_timer function." );
  return self;
}


static VALUE
eh_finalize_timer( VALUE self ) {
  error( "Called unmodified finalize_timer function." );
  return self;
}


static VALUE
eh_add_timer_event( VALUE self, VALUE interval ) {
  UNUSED( interval );

  error( "Called unmodified add_timer_event function." );
  return self;
}


static VALUE
eh_add_periodic_event( VALUE self, VALUE interval, VALUE callback ) {
  UNUSED( interval );
  UNUSED( callback );

  error( "Called unmodified add_periodic_event function." );
  return self;
}


static VALUE
eh_delete_timer_event( VALUE self, VALUE timer_event ) {
  UNUSED( timer_event );

  error( "Called unmodified delete_timer_event function." );
  return self;
}


static VALUE
eh_execute_timer_events( VALUE self ) {
  error( "Called unmodified execute_timer_events function." );
  return self;
}


/*
 * Wrapper functions for calling the EventHandlers from C code.
 */
#define CALL_RB_FUNC( func_name, ... )                                  \
  rb_funcall( cCurrentEventHandler, rb_intern( func_name ), __VA_ARGS__ )

#define VERIFY_FD( verify_fd ) \
  if ( verify_fd < 0 ) { rb_fatal( "Called with invalid fd: %i.", verify_fd ); }


static void
call_init_event_handler() {
  CALL_RB_FUNC( "init_event_handler", 0 );
}


static void
call_finalize_event_handler() {
  CALL_RB_FUNC( "finalize_event_handler", 0 );
}


static bool
call_start_event_handler() {
  CALL_RB_FUNC( "start_event_handler", 0 );

  // Fixme...
  return true;
}


static void
call_stop_event_handler() {
  CALL_RB_FUNC( "stop_event_handler", 0 );
}


static bool
call_run_event_handler_once() {
  CALL_RB_FUNC( "run_event_handler_once", 0 );

  // Fixme...
  return true;
}


static void
call_set_fd_handler( int fd, event_fd_callback read_callback, void* read_data, event_fd_callback write_callback, void* write_data ) {
  VALUE event_connection = create_event_connection( fd, read_callback, read_data, write_callback, write_data );

  CALL_RB_FUNC( "set_fd_handler", 2, INT2NUM( fd ), event_connection );
}


static void
call_delete_fd_handler( int fd )  {
  CALL_RB_FUNC( "delete_fd_handler", 1, INT2NUM( fd ) );
}


static void
call_set_readable( int fd, bool state )  {
  VERIFY_FD( fd );
  CALL_RB_FUNC( "set_readable", 2, INT2NUM( fd ), state ? Qtrue : Qfalse );
}


static void
call_set_writable( int fd, bool state )  {
  VERIFY_FD( fd );
  CALL_RB_FUNC( "set_writable", 2, INT2NUM( fd ), state ? Qtrue : Qfalse );
}


static bool
call_readable( int fd )  {
  VERIFY_FD( fd );
  return CALL_RB_FUNC( "readable", 1, INT2NUM( fd ) ) == Qtrue;
}


static bool
call_writable( int fd )  {
  VERIFY_FD( fd );
  return CALL_RB_FUNC( "writable", 1, INT2NUM( fd ) ) == Qtrue;
}


/*
 * Wrapper functions for calling the timer event handlers from C code.
 */
static bool
call_init_timer() {
  return CALL_RB_FUNC( "init_timer", 0 ) == Qtrue;
}


static bool
call_finalize_timer() {
  return CALL_RB_FUNC( "finalize_timer", 0 ) == Qtrue;
}


static bool
call_add_timer_event( struct itimerspec *interval, timer_callback callback, void *user_data ) {
  VALUE timer_event = create_event_timer( interval, callback, user_data );
  return CALL_RB_FUNC( "add_timer_event_callback", 1, timer_event ) == Qtrue;
}


static bool
call_add_periodic_event( const time_t seconds, timer_callback callback, void *user_data ) {
  VALUE timer_event = create_event_timer( NULL, callback, user_data );
  return CALL_RB_FUNC( "add_periodic_event_callback", 2, rb_float_new( (double)seconds ), timer_event ) == Qtrue;
}


static bool
call_delete_timer_event( timer_callback callback, void *user_data ) {
  VALUE timer_event = create_event_timer( NULL, callback, user_data );

  CALL_RB_FUNC( "delete_timer_event", 1, timer_event );
  return true;
}


static void
call_execute_timer_events() {
  CALL_RB_FUNC( "execute_timer_events", 0 );
}


VALUE
event_handler_set_as_handler( VALUE self ) {
  // TODO: Make the event handler selection safe...

  // if ( init_event_handler != NULL || cCurrentEventHandler != Qnil ) {
  if ( cCurrentEventHandler != Qnil ) {
    error( "Event handler already set, cannot set a new one." );
    return self;
  }

  info( "Setting Ruby-based custom event handler." );

  init_event_handler = call_init_event_handler;
  finalize_event_handler = call_finalize_event_handler;
  start_event_handler = call_start_event_handler;
  stop_event_handler = call_stop_event_handler;

  run_event_handler_once = call_run_event_handler_once;

  set_fd_handler = call_set_fd_handler;
  delete_fd_handler = call_delete_fd_handler;

  set_readable = call_set_readable;
  set_writable = call_set_writable;
  readable = call_readable;
  writable = call_writable;

  init_timer = call_init_timer;
  finalize_timer = call_finalize_timer;

  add_timer_event_callback = call_add_timer_event;
  add_periodic_event_callback = call_add_periodic_event;
  delete_timer_event = call_delete_timer_event;
  execute_timer_events = call_execute_timer_events;

  cCurrentEventHandler = self;

  return self;
}

void
Init_event_handler() {
  cEventHandler = rb_define_class_under( mTrema, "EventHandler", rb_cObject );
  cCurrentEventHandler = Qnil;

  rb_define_method( cEventHandler, "init_event_handler", eh_init_event_handler, 0 );
  rb_define_method( cEventHandler, "finalize_event_handler", eh_finalize_event_handler, 0 );
  rb_define_method( cEventHandler, "start_event_handler", eh_start_event_handler, 0 );
  rb_define_method( cEventHandler, "stop_event_handler", eh_stop_event_handler, 0 );
  rb_define_method( cEventHandler, "run_event_handler_once", eh_run_event_handler_once, 0 );
  rb_define_method( cEventHandler, "set_fd_handler", eh_set_fd_handler, 2 );
  rb_define_method( cEventHandler, "delete_fd_handler", eh_delete_fd_handler, 1 );
  rb_define_method( cEventHandler, "set_readable", eh_set_readable, 2 );
  rb_define_method( cEventHandler, "set_writable", eh_set_writable, 2 );
  rb_define_method( cEventHandler, "readable", eh_readable, 1 );
  rb_define_method( cEventHandler, "writable", eh_writable, 1 );

  rb_define_method( cEventHandler, "init_timer", eh_init_timer, 0 );
  rb_define_method( cEventHandler, "finalize_timer", eh_finalize_timer, 0 );
  rb_define_method( cEventHandler, "add_timer_event_callback", eh_add_timer_event, 1 );
  rb_define_method( cEventHandler, "add_periodic_event_callback", eh_add_periodic_event, 2 );
  rb_define_method( cEventHandler, "delete_timer_event", eh_delete_timer_event, 1 );
  rb_define_method( cEventHandler, "execute_timer_events", eh_execute_timer_events, 0 );

  rb_define_method( cEventHandler, "set_as_handler", event_handler_set_as_handler, 0 );
}


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
