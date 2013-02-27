CC        = gcc
PLATFORM ?= ios
CFLAGS    = -std=c99 -c -g
LDFLAGS   = -dynamiclib -undefined suppress -flat_namespace

ifeq ($(PLATFORM), ios)
	CC  	    = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/llvm-gcc-4.2
	SDK       = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS6.1.sdk
	CFLAGS  += -arch armv7 -isysroot ${SDK}
	LDFLAGS += -arch armv7 -isysroot ${SDK}
endif

objc_rt_class_dump.dylib: objc_rt_class_dump.c
	${CC} ${CFLAGS} -o $(<:.c=.o) $<
	${CC} ${LDFLAGS} -o $@ *.o

clean:
	rm -rf *.dylib *.o

.PHONY: clean