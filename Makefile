NAME         := apr_stack
APR_CONFIG   := $(shell which apr-1-config)
BIN          := main
BIN_DIR      := bin
CC           := $(shell ${APR_CONFIG} --cc)
CFLAGS       := $(shell ${APR_CONFIG} --cflags --cppflags) -Wall -pedantic -std=c17
INCLUDES_APR := $(shell ${APR_CONFIG} --includes)
INCLUDES_PRJ := -Iinclude
INCLUDES     := $(INCLUDES_APR) $(INCLUDES_MONGO) $(INCLUDES_PRJ)
LDFLAGS      := $(shell ${APR_CONFIG} --ldflags)
LDLIBS       := $(shell ${APR_CONFIG} --libs --link-ld)
LIB_DIR      := lib
LIB_SRC      := $(wildcard $(NAME)*.c)
LIB_OBJ      := $(LIB_SRC:.c=.o)
LIB_NAME     := $(NAME)
MD           := mkdir

all: folders $(BIN)
#	$(RM) -rf *.o

folders:
	$(MD) -p $(BIN_DIR) $(LIB_DIR)

$(BIN): main.o lib$(LIB_NAME)
	$(CC) -o $(BIN_DIR)/$@ $< $(CFLAGS) $(INCLUDES) $(LDLIBS) -L$(LIB_DIR) -l$(LIB_NAME)

lib$(LIB_NAME): $(LIB_OBJ)
	$(CC) -o $(LIB_DIR)/$@.so -shared -fPIC $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^

clean:
	$(RM) -rf *.o $(BIN_DIR) $(LIB_DIR)
