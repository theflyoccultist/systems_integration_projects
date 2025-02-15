CC = gcc
CFLAGS = -Wall
LDFLAGS = -lws2_32

TARGET = http_server
SRCS = src/main.c src/server.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)