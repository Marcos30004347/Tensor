#ifndef CORE_H
#define CORE_H


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include "platforms/windows.h"
#endif

#if defined(__unix__) || defined(__linux__) || defined(_POSIX_VERSION) || (defined(__APPLE__) && defined(TARGET_OS_MAC))
#include "platforms/linux.h"
#endif

#include "types.h"

#endif