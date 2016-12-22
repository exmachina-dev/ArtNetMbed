#ifndef MAIN_H_
#define MAIN_H_

#include "config.h"

#include "mbed.h"
#include "EthernetInterface.h"

#define HAVE_CONFIG_H

#include "artnet.h"

#include "serial.h"
#include "leds.h"
// #include "watchdog.h"

int main(void);

int dmx_handler(artnet_node n, int port, void *data);

#endif
