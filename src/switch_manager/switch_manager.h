/*
 * OpenFlow Switch Listener
 *
 * Author: Kazushi SUGYO
 *
 * Copyright (C) 2008-2012 NEC Corporation
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


#ifndef SWITCH_LISTENER_H
#define SWITCH_LISTENER_H


#include <sys/types.h>


static const char SWITCH_MANAGER_NAME_OPTION[] = "--name=";
static const uint SWITCH_MANAGER_NAME_OPTION_STR_LEN = sizeof( SWITCH_MANAGER_NAME_OPTION );
static const char SWITCH_MANAGER_SOCKET_OPTION[] = "--socket=";
static const uint SWITCH_MANAGER_SOCKET_OPTION_STR_LEN = sizeof( SWITCH_MANAGER_SOCKET_OPTION );
static const char SWITCH_MANAGER_DAEMONIZE_OPTION[] = "--daemonize";
static const uint SWITCH_MANAGER_SOCKET_STR_LEN = sizeof( "2147483647" );
static const char SWITCH_MANAGER_COMMAND_PREFIX[] = "switch.";
static const uint SWITCH_MANAGER_COMMAND_PREFIX_STR_LEN = sizeof( SWITCH_MANAGER_COMMAND_PREFIX );
static const char SWITCH_MANAGER_PREFIX[] = "switch.";
static const uint SWITCH_MANAGER_PREFIX_STR_LEN = sizeof( SWITCH_MANAGER_PREFIX );
static const uint SWITCH_MANAGER_ADDR_STR_LEN = sizeof( "255.255.255.255:65535" );

static const char SWITCH_MANAGER_PATH[] = "objects/switch_manager/switch";
static const char SWITCH_MANAGER_STATE_PREFIX[] = "state_notify::";

enum {
  LISTENER_INFO_NONE,
  LISTENER_INFO_INET,
  LISTENER_INFO_UNIX
};

struct listener_info {
  const char *switch_daemon;
  int switch_daemon_argc;
  char **switch_daemon_argv;

  int listen_fd;
  int listen_protocol;

  union {
    uint16_t listen_port;
    char *listen_path;
  };
};


#endif // SWITCH_LISTENER_H


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
