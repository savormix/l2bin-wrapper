#include "paths.h"

const WCHAR *GetFilename(const WCHAR *path) {
    const WCHAR *end = wcsrchr(path, L'\\');
    return end != nullptr ? end + 1 : path;
}