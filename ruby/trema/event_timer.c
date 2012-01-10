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


#include "event_timer.h"
#include "trema.h"

#include "../../src/lib/event_handler.h"


extern VALUE mTrema;
VALUE cEventTimer;


static VALUE
event_timer_alloc( VALUE klass ) {
  event_timer *data = xmalloc( sizeof( event_timer ) );
  return Data_Wrap_Struct( klass, NULL, xfree, data );
}


static VALUE
event_timer_call( VALUE self ) {
  event_timer* data;
  Data_Get_Struct( self, struct event_timer, data );

  if (data->callback != NULL) {
    data->callback( data->user_data );
  }

  return self;
}


static VALUE
event_timer_interval( VALUE self ) {
  event_timer* data;
  Data_Get_Struct( self, struct event_timer, data );

  double interval = (double)data->interval.it_interval.tv_sec + (double)data->interval.it_interval.tv_nsec / 10.0e9;
  return rb_float_new( interval );
}

static VALUE
event_timer_expiration( VALUE self ) {
  event_timer* data;
  Data_Get_Struct( self, struct event_timer, data );

  double expiration = (double)data->interval.it_value.tv_sec + (double)data->interval.it_value.tv_nsec / 10.0e9;
  return rb_float_new( expiration );
}

static VALUE
event_timer_handle( VALUE self ) {
  return rb_iv_get(self, "handle");
}

static VALUE
event_timer_set_handle( VALUE self, VALUE handle ) {
  return rb_iv_set(self, "handle", handle);
}

VALUE
create_event_timer( struct itimerspec *interval, timer_callback_t callback, void* user_data ) {
  VALUE event_timer = rb_funcall( rb_eval_string( "Trema::EventTimer" ), rb_intern( "new" ), 0 );

  struct event_timer* data;
  Data_Get_Struct( event_timer, struct event_timer, data );
  
  if ( interval != NULL ) {
    data->interval = *interval;
  } else {
    memset( &data->interval, 0, sizeof( struct itimerspec ) );
  }

  data->callback = callback;
  data->user_data = user_data;

  return event_timer;
}


void
Init_event_timer() {
  cEventTimer = rb_define_class_under( mTrema, "EventTimer", rb_cObject );

  rb_define_alloc_func( cEventTimer, event_timer_alloc );

  rb_define_method( cEventTimer, "call", event_timer_call, 0 );
  rb_define_method( cEventTimer, "interval", event_timer_interval, 0 );
  rb_define_method( cEventTimer, "expiration", event_timer_expiration, 0 );

  rb_define_method( cEventTimer, "handle", event_timer_handle, 0 );
  rb_define_method( cEventTimer, "handle=", event_timer_set_handle, 1 );
}


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
