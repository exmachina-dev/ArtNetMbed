ArtNetMbed
==========

This is an example using libartnet using mbed toolkit.
This program is tested on a mbed LPC1768.

To install mbed toolkit, please refer to [this guide](http://devblog.exmachina.fr/tutorial/2016/12/08/LPC1768-development-toolkit)

# License

This is released under MIT license. See [LICENSE](LICENSE) for mor information.
# Configuration

In the [config](config.h) file, you'll find some features disabled,
please look at [libartnet/README.md](https://github.com/exmachina-dev/libartnet/blob/mbed/README.md) for details.

The only thing you should configure is the `DMX_START` constant. It defines the DMX channel for the device. This device has a DMX footrpint of 4.

# Links

Original code: [ArtNetMbed](https://github.com/exmachina-dev/ArtNetMbed)
libartnet library: [libartnet](https://github.com/exmachina-dev/libartnet)
