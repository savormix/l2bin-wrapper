#ifndef L2BIN_WRAPPER_PATHS_H
#define L2BIN_WRAPPER_PATHS_H

#include <Windows.h>

#define PATH_BUFFER_SIZE MAX_PATH+1

const WCHAR *GetFilename(const WCHAR *path);

#endif //L2BIN_WRAPPER_PATHS_H
