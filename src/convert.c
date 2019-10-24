/*
 * tmconv.c
 *
 * tmconv
 * ==========
 * Convert time to string with format passed time
 *
 * Author   :
 * Created  :  29.08.19 08:10 (base 16.11.18)
 *
 * Copyright (C) Denis Karabadjak <denkar@mail.ru>
 */

#include "tmconv.h"
#include <stdio.h>
#include <string.h>

struct tm_fmt_item_s tm_fmt_item_ls[8] = {
        {.id = TM_FMT_MILLISECOND, .name = "ms", .val = 0l},
        {.id = TM_FMT_SECOND, .name = "sec", .val = 1000l},
        {.id = TM_FMT_MINUTE, .name = "min", .val = 60l * 1000},
        {.id = TM_FMT_HOUR, .name = "hour", .val = 3600l * 1000},
        {.id = TM_FMT_DAY, .name = "day", .val = 86400l * 1000},
        {.id = TM_FMT_WEEK, .name = "week", .val = 86400l * 7 * 1000},
        {.id = TM_FMT_MONTH, .name = "month", .val = 86400ll * 30 * 1000},
        {.id = TM_FMT_YEAR, .name = "year", .val = 86400ll * 365 * 1000},
};

dtmfmt_item_t *tmfmt_item(dtmms_t time, dtmfmt_t fmt) {
    if (!fmt) {
        if (time < 1000l) {
            fmt = TM_FMT_MILLISECOND;
        } else if (time < (60L * 1000)) {
            fmt = TM_FMT_SECOND;
        } else if (time < (3600l * 1000)) {
            fmt = TM_FMT_MINUTE;
        } else if (time < (86400l * 1000)) {
            fmt = TM_FMT_HOUR;
        } else if (time < (86400l * 7) * 1000) {
            fmt = TM_FMT_DAY;
        } else if (time < ((86400ll * 30) * 1000)) {
            fmt = TM_FMT_WEEK;
        } else if (time < (86400ll * 365) * 1000) {
            fmt = TM_FMT_MONTH;
        } else {
            fmt = TM_FMT_YEAR;
        }
    }

    dtmfmt_item_t *item = &tm_fmt_item_ls[fmt];

    return item;
}

dtmfmt_item_t *dtmconv(char *dest, dtmms_t *src_ms, dtmfmt_t fmt) {
    *dest                      = 0;
    dtmfmt_item_t *tm_fmt_item = tmfmt_item(*src_ms, fmt);
    dtmms_t       val;

    if (tm_fmt_item->val > 0) {
        val = *src_ms / tm_fmt_item->val;
        *src_ms = *src_ms - (val * tm_fmt_item->val);
    } else {
        val = *src_ms;
    }

    char tmp[20];

    sprintf(tmp, "%lu", val);
    /*itoa(val,tmp,2);*/
    strcat(dest, tmp);
    strcat(dest, " ");

    strcat(dest, tm_fmt_item->name);

    return tm_fmt_item;
}

char *dtmconv_group(char *dest, dtmms_t src_ms, dtmfmt_t fmt, uint8_t groups,
                       _Bool is_empty) {
    *dest = 0;

    if (groups == 0) {
        groups = 1;
    }

    for (uint8_t i = 0; i < groups; i++) {
        char          _dest[30];
        dtmfmt_item_t *tm_fmt_item = dtmconv(_dest, &src_ms, fmt);

        if (i) {
            strcat(dest, " ");
        }

        strcat(dest, _dest);

        /* fmt = tm_fmt_item->id + 1; fixme */

        if (tm_fmt_item->id == TM_FMT_MILLISECOND) {
            break;
        }
    }

    return dest;
}
