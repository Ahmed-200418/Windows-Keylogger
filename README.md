# Windows Keylogger

This is a simple keylogger written in C using the Windows API.  
It logs all keyboard events and prints them both to the console and a text file `log.txt`.

> ⚠️ **This project is for educational purposes only. Do not use it for malicious activities.**

## 🔧 Features

- Captures all keystrokes using `WH_KEYBOARD_LL` hook.
- Logs both normal characters and special keys like `ENTER`, `ESC`, `TAB`, `F1-F12`, arrow keys, etc.
- Outputs logs to:
  - Console window
  - `log.txt` file in the same directory
- Detects shift, control, alt, capslock, and function keys.

## 🖥️ How It Works

- Uses a low-level keyboard hook (`SetWindowsHookEx`) to intercept key presses.
- Special keys are handled explicitly via `switch` statements.
- Other keys are translated using `ToUnicode()` to handle modifier keys (Shift, Caps Lock, etc.).
- All results are written to the console and flushed to `log.txt`.

## 🛠️ Requirements

- Windows OS
- GCC compiler (e.g., via MinGW)

## 🔧 How to Compile and run

Open terminal in project directory and run:

```bash
gcc main.c -o keylogger.exe
./keylogger.exe
