OBJ := main.o args.o utils.o client.o server.o
INCLUDE := $(addprefix ../, $(INCLUDE))
TARGET := ../$(TARGET)
CFLAGS += $(patsubst %, -I%, $(INCLUDE))

all: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

.phony: clean static

static: $(OBJ)
	$(CC) -static $(OBJ) -o $(TARGET)-static $(LDFLAGS)

$(OBJ):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)