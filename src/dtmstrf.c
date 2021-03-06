/*
 * tmfmt.c
 *
 * tmfmt
 * ==========
 * Time to string by format
 *
 * Author   :
 * Created  :  28.08.19 14:30
 *
 * Copyright (C) Denis Karabadjak <denkar@mail.ru>
 */

#include "dtmstrf.h"
#include <memory.h>
#include <locale.h>

int dtm_strfsec(char *dst, time_t src, int nfmt, char *fmt) {
    int       ndst;
    char      fmt_buf[nfmt + 1];
    struct tm *utm;

    utm = localtime(&src);

    /* duplicate string FMT for insert null terminal end string */

    memcpy(fmt_buf, fmt, (size_t) nfmt);
    *(fmt_buf + nfmt) = '\0';

    /* apply std func. from libc */

    ndst = (int) strftime(dst, 100, fmt_buf, utm);

    return ndst;
}

