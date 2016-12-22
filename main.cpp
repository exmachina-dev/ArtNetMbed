
#include "main.h"

#define DMX_START       0

EthernetInterface* ARTNET_ETH_PTR = NULL;
EthernetInterface eth;
Serial* USBport = NULL;
Serial USBport0(p28, p27);

static artnet_node local_node;
uint16_t counter;

int main(void) {
    ARTNET_ETH_PTR = &eth;

    HBled.period(0.020);
    APled.period(0.020);
    ANled.period(0.020);
    ERled.period(0.020);

    USBport = &USBport0;

    USBport->baud(115200);

#ifdef ARTNET_DEBUG
    USBport->printf("AN_new\r\n");
#endif
    local_node = artnet_new(NULL, "", "", true);
    if (local_node == NULL) {
        USBport->printf("%s", artnet_strerror());
        return -1;
    } else {
        USBport->printf("AN_new.\r\n\r\n");
    }

    artnet_setoem(local_node, AN_OEM_HI, AN_OEM_LO);
    artnet_setesta(local_node, AN_ESTA_HI, AN_ESTA_LO);
    artnet_set_short_name(local_node, "ArtNetMbed");
    artnet_set_long_name(local_node, "ArtNetMbed");
    artnet_set_node_type(local_node, ARTNET_NODE);
    artnet_set_subnet_addr(local_node, 0);

    artnet_set_port_type(local_node, 0, ARTNET_ENABLE_OUTPUT, ARTNET_PORT_DMX);
    artnet_set_port_addr(local_node, 0, ARTNET_OUTPUT_PORT, ARTNET_PORT_DMX);

    artnet_dump_config(local_node);

    int rtn;


#ifdef ARTNET_DEBUG
    USBport->printf("AN_start\r\n");
#endif
    rtn = artnet_start(local_node);
#ifdef ARTNET_DEBUG
    USBport->printf("MAC: %s\r\n", eth.get_mac_address());
    USBport->printf("IP: %s\r\n", eth.get_ip_address());
    USBport->printf("NM: %s\r\n", eth.get_netmask());
    USBport->printf("GW: %s\r\n", eth.get_gateway());
    if (rtn != 0)
        USBport->printf("AN_start: %s", artnet_strerror());
    USBport->printf("AN_start.\r\n\r\n");
#endif

    artnet_set_dmx_handler(local_node, &dmx_handler, NULL);

    while (1) {
        artnet_read(local_node, 0);
        counter += 1;

        Thread::wait(1);
    }
}

int dmx_handler(artnet_node n, int port, void *data) {
    int length = DMX_START + 4;
    uint8_t *dmx = artnet_read_dmx(n, port, &length);
    USBport->printf("DMX on port %d\r\n", port);
    USBport->printf("%d\t%d\t%d\t%d\r\n",
            dmx[DMX_START + 0], dmx[DMX_START + 1],
            dmx[DMX_START + 2], dmx[DMX_START + 3]);
    HBled = dmx[DMX_START + 0] / 255.0;
    ANled = dmx[DMX_START + 1] / 255.0;
    APled = dmx[DMX_START + 2] / 255.0;
    ERled = dmx[DMX_START + 3] / 255.0;
    return 0;
}
