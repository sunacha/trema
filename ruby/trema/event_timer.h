/*
 * Wrapper class for timer events.
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


#ifndef RUBY_TREMA_EVENT_TIMER_H
#define RUBY_TREMA_EVENT_TIMER_H


#include "ruby.h"
#include "timer.h"

#include "../../src/lib/event_handler.h"

extern VALUE cEventTimer;

typedef struct event_timer {
  struct itimerspec interval; // Don't include this here?
  timer_callback_t callback;
  void *user_data;
} event_timer;


void Init_event_timer( void );

VALUE create_event_timer( struct itimerspec *interval, timer_callback_t callback, void* user_data );


#endif // RUBY_TREMA_EVENT_TIMER_H


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
