# $FreeBSD: soc2013/dpl/head/sys/dev/etherswitch/mdio_if.m 235150 2012-05-01 06:11:38Z adrian $

#include <sys/bus.h>

INTERFACE mdio;

#
# Read register from device on MDIO bus
#
METHOD int readreg {
	device_t		dev;
	int			phy;
	int			reg;
};

#
# Write register to device on MDIO bus
#
METHOD int writereg {
	device_t		dev;
	int			phy;
	int			reg;
	int			val;
};
