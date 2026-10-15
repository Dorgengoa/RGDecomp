#include "types.h"

s32 EhCatchTypeCompare_100a60(const char *throwtype, const char *catchtype, s64 *offset_result)
{
    const char *cptr1;
    const char *cptr2;

    *offset_result = 0;
    if ((cptr2 = catchtype) == 0) {
        return 1;
    }
    cptr1 = throwtype;

    if (*cptr2 == 'P') {
        cptr2++;
        if (*cptr2 == 'C') cptr2++;
        if (*cptr2 == 'V') cptr2++;
        if (*cptr2 == 'v') {
            if (*cptr1 == 'P' || *cptr1 == '*') {
                return 1;
            }
        }
        cptr2 = catchtype;
    }

    switch (*cptr1) {
    case '*':
    case '!':
        if (*cptr1++ != *cptr2++) return 0;
        for (;;) {
            if (*cptr1 == *cptr2++) {
                if (*cptr1++ == '!') {
                    s64 offset;

                    for (offset = 0; *cptr1 != '!';) offset = offset * 10 + *cptr1++ - '0';
                    *offset_result = offset;
                    return 1;
                }
            } else {
                while (*cptr1++ != '!') ;
                while (*cptr1++ != '!') ;
                if (*cptr1 == 0) return 0;
                cptr2 = catchtype + 1;
            }
        }
        return 0;
    }

    while ((*cptr1 == 'P' || *cptr1 == 'R') && *cptr1 == *cptr2) {
        cptr1++; cptr2++;
        if (*cptr2 == 'C') {
            if (*cptr1 == 'C') cptr1++;
            cptr2++;
        }
        if (*cptr1 == 'C') return 0;
        if (*cptr2 == 'V') {
            if (*cptr1 == 'V') cptr1++;
            cptr2++;
        }
        if (*cptr1 == 'V') return 0;
    }

    for (; *cptr1 == *cptr2; cptr1++, cptr2++) if (*cptr1 == 0) return 1;
    return 0;
}
