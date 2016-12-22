#ifndef CONFIG_H_
#define CONFIG_H_

// Enable TOD feature
// #define ARTNET_FEATURE_TOD

// Enable RDM feature
// #define ARTNET_FEATURE_RDM

// Enable firmware upload feature
// #define ARTNET_FEATURE_FIRMWARE

// Enable input feature
// #define ARTNET_FEATURE_INPUT

// Enable debug prints
// #define ARTNET_DEBUG

// Manufacturer and product constants
#define AN_OEM_LO   0x00
#define AN_OEM_HI   0x00

#define AN_ESTA_LO  0x00
#define AN_ESTA_HI  0x00

#define ARTNET_PRINTF USBport->printf

#endif
