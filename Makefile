CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC -fstack-protector-all -D_FORTIFY_SOURCE=2 -I./src
LDFLAGS = -shared -lpam

TARGET = pam_secure.so
TEST_TARGET = test_runner

SRC = src/pam_secure.c src/utils.c
OBJ = $(SRC:.c=.o)

TEST_SRC = tests/test_runner.c
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJ) $(OBJ)
	$(CC) $(CFLAGS) -o $@ tests/test_runner.c src/utils.c -lpam -ldl

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)

.PHONY: all clean
