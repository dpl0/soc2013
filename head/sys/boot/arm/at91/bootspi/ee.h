/* $FreeBSD: soc2013/dpl/head/sys/boot/arm/at91/bootspi/ee.h 163641 2006-10-21 22:51:21Z imp $ */

void EEInit(void);
void EERead(unsigned ee_off, char *data_addr, unsigned size);
void EEWrite(unsigned ee_off, const char *data_addr, unsigned size);

