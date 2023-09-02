#include "SDL.h"
#include "utils.h"
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>

void die(const char *fmt, ...)
{
    va_list vargs;

    va_start(vargs, fmt);
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, fmt,
                    vargs);
    va_end(vargs);

    exit(EXIT_FAILURE);
}

void *xmalloc(size_t size)
{
    void *p = malloc(size);
    if (!p)
        die("malloc: %s", strerror(errno));
    return p;
}
