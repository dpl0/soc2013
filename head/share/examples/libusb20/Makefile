# $FreeBSD: soc2013/dpl/head/share/examples/libusb20/Makefile 239562 2012-07-18 21:30:17Z joerg $
TARGETS=	bulk control

all: $(TARGETS)

bulk: bulk.o aux.o
	$(CC) $(CFLAGS) -o bulk bulk.o aux.o -lusb

control: control.o aux.o
	$(CC) $(CFLAGS) -o control control.o aux.o -lusb

clean:
	rm -f $(TARGETS) *.o *~
