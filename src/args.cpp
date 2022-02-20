#include "args.h"

#include <cstdlib>

WCHAR *findArgument(WCHAR *string, const WCHAR *arg) {
    WCHAR *lowerArg = _wcsdup(arg);
    _wcslwr_s(lowerArg, wcslen(lowerArg) + 1);
    size_t currentIndex = 0;
    while (true) {
        WCHAR current = *string;
        if (current == L'\0') {
            free(lowerArg);
            return nullptr;
        }
        if (current >= L'A' && current <= L'Z') {
            current += L'a' - L'A';
        }
        if (current != lowerArg[currentIndex]) {
            string -= currentIndex - 1;
            currentIndex = 0;
            continue;
        }

        if (++currentIndex == wcslen(lowerArg)) {
            free(lowerArg);
            return string - currentIndex + 1;
        }
        ++string;
    }
}

WCHAR *argumentEnd(WCHAR *string) {
    WCHAR *result = wcschr(string, L' ');
    if (result != nullptr) {
        return result;
    }
    return string + wcslen(string);
}

void removeArgument(WCHAR *string, const WCHAR *arg) {
    WCHAR *argStart = findArgument(string, arg);
    if (argStart != nullptr) {
        WCHAR *argEnd = argumentEnd(argStart);
        if (*argEnd == L' ') {
            ++argEnd;
        }
        wcscpy_s(argStart, wcslen(argStart) + 1, argEnd);
    }
}
