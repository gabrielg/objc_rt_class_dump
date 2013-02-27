# objc_rt_class_dump

This is a small amount of code that uses the [Objective-C Runtime functions](https://developer.apple.com/library/mac/#documentation/Cocoa/Reference/ObjCRuntimeRef/Reference/reference.html)
to dump a program's Objective-C class information when injected into a running
process via GDB.

## Building

For iOS: `make`

For OS X: `PLATFORM=osx make`

## Usage

1. Build the library:

        $ PLATFORM=osx make
		
2. Attach GDB to a running process:

        $ gdb -p `pidof stickies`
        GNU gdb 6.3.50-20050815 (Apple version gdb-1824) (Thu Nov 15 10:42:43 UTC 2012)
        Copyright 2004 Free Software Foundation, Inc.
        GDB is free software, covered by the GNU General Public License, and you are
        welcome to change it and/or distribute copies of it under certain conditions.
        Type "show copying" to see the conditions.
        There is absolutely no warranty for GDB.  Type "show warranty" for details.
        This GDB was configured as "x86_64-apple-darwin".
        /Users/ggironda/Repositories/gdb/28760: No such file or directory
        Attaching to process 28760.
        Reading symbols for shared libraries . done
        Reading symbols for shared libraries ...................................................................................................................................................................................... done
        Reading symbols for shared libraries + done
        0x00007fff8a36e686 in mach_msg_trap ()
        (gdb)

3. Load the library:

        $ ls
        Makefile            README.md           obj_c_rt_util.c     obj_c_rt_util.c.o   obj_c_rt_util.dylib
        $ pwd
        /Users/ggironda/Repositories/objc_rt_class_dump
        
        (gdb) call (void *) dlopen("/Users/ggironda/Repositories/objc_rt_class_dump/objc_rt_class_dump.dylib")

4. Check `/tmp` for the output:

        $ grep NSThemeFrameTitleTextField -A20 /tmp/obj_c_rt_util.txt
        NSThemeFrameTitleTextField
          Methods
            dealloc
            isFlipped
            setFrameOrigin:
            drawRect:
            _windowChangedKeyState
            setAttributedStringValue:
            attributedStringValue
            canSmoothFontsInLayer
            invalidateOnFrameOriginChange
            setInvalidateOnFrameOriginChange:
          Properties
            attributedStringValue
            invalidateOnFrameOriginChange
        _NSKeyedUnarchiverHelper
          Methods
            allowedClassNames
            setAllowedClassNames:
            classNameAllowed:
            init
