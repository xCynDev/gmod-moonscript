
ifeq ($(OS),Windows_NT)
FLAGS=-Iinclude/ -O2
LINK=-L.
else
FLAGS=-fpic -O2
LINK=
endif

all: moon.exe moonc.exe moonscript.dll

moon.exe: moon.c lfs.o lpeg.o moonscript.h moon.h alt_getopt.h
	gcc $(LINK) $(FLAGS) -o $@ $< lfs.o lpeg.o -llua51

moonc.exe: moonc.c lfs.o lpeg.o moonscript.h moonc.h alt_getopt.h
	gcc $(LINK) $(FLAGS) -o $@ $< lfs.o lpeg.o -llua51

moonscript.dll: lpeg.o moonscript.o
	gcc $(LINK) $(FLAGS) -o $@ $+ -llua51 -shared

moon.o: moon.c moonscript.h moon.h alt_getopt.h
	gcc $(FLAGS) -c $< -o $@

moonc.o: moonc.c moonscript.h moon.h alt_getopt.h
	gcc $(FLAGS) -c $< -o $@

moonscript.o: moonscript.c moonscript.h
	gcc $(FLAGS) -c $< -o $@

lpeg.o: lpeg/lpeg.c
	gcc $(FLAGS) -c $< -o $@

lfs.o: luafilesystem/src/lfs.c
	gcc $(FLAGS) -c $< -o $@

# commited to repo:

headers: moonscript.h moonc.h moon.h alt_getopt.h

moonscript.h:
	(cd moonscript/; bin/splat.moon -l moonscript moonscript moon) > moonscript.lua
	xxd -i moonscript.lua > $@
	rm moonscript.lua

alt_getopt.h: alt_getopt.lua
	xxd -i $< > $@

moon.h:
	awk 'FNR>1' moonscript/bin/moon > moon.lua
	xxd -i moon.lua > $@
	rm moon.lua

moonc.h:
	awk 'FNR>1' moonscript/bin/moonc > moonc.lua
	xxd -i moonc.lua > $@
	rm moonc.lua

clean:
	-rm *.o
	-rm *.exe
	-rm moon
	-rm moonc

clean_headers:
	rm *.h

# linux

moon: moon.o lfs.o lpeg.o
	gcc -o $@ $+ -llua -O2

moonc: moonc.o lfs.o lpeg.o
	gcc -o $@ $+ -llua -O2

moonscript.so: moonscript.o lpeg.o
	gcc -o $@ $+ -fpic -shared -O2

# misc
love_header: moonscript.lua.h
moonscript.lua.h::
	cd moonscript/; bin/splat.moon -l moonscript moonscript moon > ../moonscript.lua
	echo namespace love { > $@
	xxd -i moonscript.lua >> $@
	echo } >> $@


