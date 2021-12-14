# Easily adaptable makefile
# Note: remove comments (#) to activate some features
#
# author Vitor Carreira
# date 2010-09-26 / updated: 2016-03-15 (Patricio)
# date 2021-30-11 / updated: 2021-30-11 (Gabriel Vieira)

# Directories
DIR_GENGETOPT=./gengetopt
DIR_LIBS=./libs
DIR_COMMON=./common
DIR_SRC=./src

# Libraries to include (if any)
LIBS=#-lm -pthread

# Compiler flags
CFLAGS=-Wall -Wextra -ggdb -std=c11 -pedantic -D_POSIX_C_SOURCE=200809L #-pg

# Linker flags
LDFLAGS=#-pg

# Indentation flags
# IFLAGS=-br -brs -brf -npsl -ce -cli4 -bli4 -nut
IFLAGS=-linux -brs -brf -br

# ! SERVER
SERVER=server
SERVER_OPT_NODIR=server_opt
SERVER_OPT=$(DIR_GENGETOPT)/$(SERVER_OPT_NODIR)
SERVER_OBJS=$(DIR_SRC)/$(SERVER).o $(DIR_LIBS)/debug.o $(DIR_LIBS)/memory.o $(DIR_LIBS)/string_aux.o $(DIR_LIBS)/inet_aux.o $(SERVER_OPT).o $(DIR_LIBS)/binary_aux.o
SERVER_HEADERS=$(DIR_SRC)/$(SERVER).c $(DIR_LIBS)/debug.h $(DIR_LIBS)/memory.h $(DIR_LIBS)/string_aux.h $(DIR_LIBS)/inet_aux.h $(DIR_COMMON)/common.h $(SERVER_OPT).h $(DIR_LIBS)/binary_aux.h

# ! CLIENT
CLIENT=client
CLIENT_OPT_NODIR=client_opt
CLIENT_OPT=$(DIR_GENGETOPT)/$(CLIENT_OPT_NODIR)
CLIENT_OBJS=$(DIR_SRC)/$(CLIENT).o $(DIR_LIBS)/debug.o $(DIR_LIBS)/memory.o $(DIR_LIBS)/string_aux.o $(DIR_LIBS)/inet_aux.o $(CLIENT_OPT).o $(DIR_LIBS)/binary_aux.o
CLIENT_HEADERS=$(DIR_SRC)/$(CLIENT).c $(DIR_LIBS)/debug.h $(DIR_LIBS)/memory.h $(DIR_LIBS)/string_aux.h $(DIR_LIBS)/inet_aux.h $(DIR_COMMON)/common.h $(CLIENT_OPT).h $(DIR_LIBS)/binary_aux.h

# ! DEPENDENCIES GO TO - # Dependencies vendor

# Specifies which targets are not files
.PHONY: clean all docs indent debugon args optimize

all: args $(SERVER) $(CLIENT)

# activate DEBUG, defining the SHOW_DEBUG macro
debugon: CFLAGS += -D SHOW_DEBUG -g
debugon: $(SERVER) $(CLIENT)

# activate optimization (-O...)
OPTIMIZE_FLAGS=-O2 # possible values (for gcc): -O2 -O3 -Os -Ofast
optimize: CFLAGS += $(OPTIMIZE_FLAGS)
optimize: LDFLAGS += $(OPTIMIZE_FLAGS)
optimize: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	$(CC) -o $@ $(SERVER_OBJS) $(LIBS)

$(CLIENT): $(CLIENT_OBJS)
	$(CC) -o $@ $(CLIENT_OBJS) $(LIBS)

# Dependencies
$(DIR_SRC)/(SERVER).o: $(SERVER_HEADERS)
$(SERVER_OPT).o: $(SERVER_OPT).c $(SERVER_OPT).h

$(DIR_SRC)/$(CLIENT).o: $(CLIENT_HEADERS)
$(CLIENT_OPT).o: $(CLIENT_OPT).c $(CLIENT_OPT).h

# Dependencies vendor
$(DIR_LIBS)/debug.o: $(DIR_LIBS)/debug.c $(DIR_LIBS)/debug.h
$(DIR_LIBS)/memory.o: $(DIR_LIBS)/memory.c $(DIR_LIBS)/memory.h
$(DIR_LIBS)/inet_aux.o: $(DIR_LIBS)/inet_aux.c $(DIR_LIBS)/inet_aux.h
$(DIR_LIBS)/string_aux.o: $(DIR_LIBS)/string_aux.c $(DIR_LIBS)/string_aux.h
$(DIR_LIBS)/binary_aux.o: $(DIR_LIBS)/binary_aux.c $(DIR_LIBS)/binary_aux.h

# disable warnings from gengetopt generated files
$(SERVER_OPT).o: $(SERVER_OPT).c $(SERVER_OPT).h
	$(CC) -ggdb -std=c11 -pedantic -c -o $@ $<

$(CLIENT_OPT).o: $(CLIENT_OPT).c $(CLIENT_OPT).h
	$(CC) -ggdb -std=c11 -pedantic -c -o $@ $<


#how to create an object file (.o) from C file (.c)
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# Generates command line arguments code from gengetopt configuration file
$(SERVER_OPT).c $(SERVER_OPT).h: $(SERVER_OPT).ggo
	gengetopt < $(SERVER_OPT).ggo --file-name=$(SERVER_OPT_NODIR)  --set-package=$(SERVER) --output-dir=$(DIR_GENGETOPT)

$(CLIENT_OPT).c $(CLIENT_OPT).h: $(CLIENT_OPT).ggo
	gengetopt < $(CLIENT_OPT).ggo --file-name=$(CLIENT_OPT_NODIR)  --set-package=$(CLIENT) --output-dir=$(DIR_GENGETOPT)
	
clean:
	rm -f *.o core.* *~ .*~ $(SERVER) $(CLIENT) *.bak $(SERVER_OPT).h $(SERVER_OPT).c $(CLIENT_OPT).h $(CLIENT_OPT).c $(DIR_GENGETOPT)/*.o $(DIR_LIBS)/*.o $(DIR_COMMON)/*.o $(DIR_SRC)/*.o

docs: Doxyfile
	doxygen Doxyfile

# entry to create the list of dependencies
depend:
	$(CC) -MM *.c

# entry 'indent' requires the application indent (sudo apt-get install indent)
indent:
	indent $(IFLAGS) *.c *.h

# entry to run the pmccabe utility (computes the "complexity" of the code)
# Requires the application pmccabe (sudo apt-get install pmccabe)
pmccabe:
	pmccabe -v *.c

# entry to run the cppcheck tool
cppcheck:
	cppcheck --enable=all --verbose *.c *.h

args:
	gengetopt < $(SERVER_OPT).ggo --file-name=$(SERVER_OPT_NODIR)  --set-package=$(SERVER) --output-dir=$(DIR_GENGETOPT)
	gengetopt < $(CLIENT_OPT).ggo --file-name=$(CLIENT_OPT_NODIR)  --set-package=$(CLIENT) --output-dir=$(DIR_GENGETOPT)