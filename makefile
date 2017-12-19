CFLAGS=-Wall -g -o3 -std=gnu++11
LDFLAGS=-Wall -g -pthread

COMPILE=g++ $(CFLAGS) -c
LINK=g++ $(LDFLAGS) -o

SRCDIR=./src
OBJDIR=./obj
#OBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
OBJ=$(OBJDIR)/des.o $(OBJDIR)/buffer.o $(OBJDIR)/decryptor.o $(OBJDIR)/encryptor.o $(OBJDIR)/keygenerator.o $(OBJDIR)/util.o $(OBJDIR)/client.o
BINDIR=./bin
BIN=$(BINDIR)/des


all: $(BIN) 

$(BIN): $(OBJ)
	$(LINK) $(BIN) $(OBJ)

$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp
	$(COMPILE) $< -o $@

clean:
	rm -f $(OBJ) $(BIN)