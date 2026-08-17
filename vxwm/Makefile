# vxwm - Versatile X Window Manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c vxwm.c util.c
OBJ = ${SRC:.c=.o}

all: vxwm

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h modules.h config.mk

config.h:
	cp config.def.h $@

modules.h:
	cp modules.def.h $@

vxwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f vxwm ${OBJ} vxwm-${VERSION}.tar.gz

dist: clean
	mkdir -p vxwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		vxwm.1 drw.h util.h ${SRC} transient.c vxwm-${VERSION}
	tar -cf vxwm-${VERSION}.tar vxwm-${VERSION}
	gzip vxwm-${VERSION}.tar
	rm -rf vxwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
		cp -f vxwm ${DESTDIR}${PREFIX}/bin/vxwm
		chmod 755 ${DESTDIR}${PREFIX}/bin/vxwm
		mkdir -p ${DESTDIR}${MANPREFIX}/man1
		sed "s/VERSION/${VERSION}/g" < vxwm.1 > ${DESTDIR}${MANPREFIX}/man1/vxwm.1
		chmod 644 ${DESTDIR}${MANPREFIX}/man1/vxwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/vxwm\
		${DESTDIR}${MANPREFIX}/man1/vxwm.1
	rm -f ${DESTDIR}${PREFIX}/bin/rvx

.PHONY: all clean dist install uninstall
