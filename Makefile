# The location of the helpers
LIDE_HELPER_LIB = /usr/share/helper/
HELPER_NAME = daily.helper
BIN_DIR = /usr/bin
CFLAGS = -Wall -g -O2 -ansi $(shell dpkg-buildflags --get CFLAGS)
CPPFLAGS = $(shell dpkg-buildflags --get CPPFLAGS)
LDFLAGS = $(shell dpkg-buildflags --get LDFLAGS)
MAN_DIR = /usr/share/man/man1

all : helper

clean :
	rm -f helper *~

distclean : clean

helper : helper.c
	gcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DLIDE_HELPER_LIB=\"$(LIDE_HELPER_LIB)$(HELPER_NAME)\" -o helper helper.c
	strip helper

install : helper $(HELPER_NAME)
	install -m 755 -d debian/helper/$(BIN_DIR)
	install -m 755 helper debian/helper/$(BIN_DIR)
	install -m 755 -d debian/helper/$(LIDE_HELPER_LIB)
	install -m 644 $(HELPER_NAME) debian/helper/$(LIDE_HELPER_LIB)$(HELPER_NAME)
	install -m 755 -d debian/helper/$(MAN_DIR)
	install -m 644 helper.1 debian/helper/$(MAN_DIR)
