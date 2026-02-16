# Keylogger-C

A simple keylogger for Windows written in C.

## How it Works

This keylogger uses the windows Hook to insert low level hook and listen keys and convert it into UNICODE character then it will be written. This tool doesn't log keys like SHIFT, CTRL, Alt or Function keys. The only purpose is to log user key inputs.

The keylogger operates silently in the background, capturing all keyboard inputs and saving them to a file named `log.txt`.

## How to Compile and Run

To compile the keylogger, you will need a C compiler such as GCC.

1. **Compile the source code:**

   ```bash
   gcc main.c -o keystealer.exe
   ```

   Alternatively, you can use the provided Makefile:

   ```bash
   make
   ```

2. **Run the executable:**
   ```bash
   ./keystealer.exe
   ```

Once running, the keylogger will start capturing keystrokes and save them to `log.txt` in the same directory.

## Disclaimer

This keylogger is intended for educational purposes only. Unauthorized use of this software to monitor or record the activities of others without their express consent is illegal. The author is not responsible for any misuse or damage caused by this software.
