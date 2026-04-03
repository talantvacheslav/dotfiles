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
	install -D -m 755 vxwm ${DESTDIR}${PREFIX}/bin/vxwm
	install -D -m 755 rvx  ${DESTDIR}${PREFIX}/bin/rvx
	install -D -m 644 vxwm.1 ${DESTDIR}${MANPREFIX}/man1/vxwm.1
	sed -i 's/VERSION/${VERSION}/g' ${DESTDIR}${MANPREFIX}/man1/vxwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/vxwm\
		${DESTDIR}${MANPREFIX}/man1/vxwm.1
	rm -f ${DESTDIR}${PREFIX}/bin/rvx

.PHONY: all clean dist install uninstall
