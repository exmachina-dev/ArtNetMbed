
#define ARTNET_FEATURE_TOD
#define ARTNET_FEATURE_RDM
#define ARTNET_FEATURE_FIRMWARE
#define ARTNET_FEATURE_INPUT

#include "main.h"

#include "leds.h"
#include "packets.h"
// #include "watchdog.h"


EthernetInterface* ARTNET_ETH_PTR = NULL;
EthernetInterface eth;
Serial* USBport = NULL;
Serial USBport0(p28, p27);

static artnet_node local_node;
uint16_t counter;

int main(void) {
    ARTNET_ETH_PTR = &eth;

    USBport = &USBport0;

    USBport->baud(115200);

    USBport->printf("IP: %s\r\n", eth.get_ip_address());
    USBport->printf("AN_new\r\n");
    local_node = artnet_new("192.168.0.132", true);
    if (local_node == NULL) {
        USBport->printf("%s", artnet_strerror());
        return -1;
    }
    else
        USBport->printf("AN_new.\r\n");
    artnet_set_node_type(local_node, ARTNET_NODE);
    artnet_set_subnet_addr(local_node, 0);

    int rtn;

    const char ip[] = "192.168.0.148";
    const char mask[] = "255.255.255.0";
    const char gw[] = "192.168.0.1";


    USBport->printf("AN_start\r\n");
    rtn = artnet_start(local_node);
    USBport->printf("IP: %s\r\n", eth.get_ip_address());
    if (rtn != 0)
        USBport->printf("AN_start: %s", artnet_strerror());
    USBport->printf("AN_start.\r\n");

    while (1) {
        artnet_read(local_node, 0);
        counter += 1;
        if (counter % 200 == 1) {
            HBled = !HBled;
        }

        Thread::wait(1);
    }
}
