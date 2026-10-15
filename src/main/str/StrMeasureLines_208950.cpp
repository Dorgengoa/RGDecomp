#include "types.h"

extern "C" {

s32 StrMeasureLines_208950(s32 *arg0, s32 *arg1, char *arg2)
{
    s32 max;
    s32 cnt;
    char *start;
    s32 len;
    char c;

    if (arg0 != NULL) {
        *arg0 = 0;
    }
    if (arg1 != NULL) {
        *arg1 = 0;
    }
    if (arg2 != NULL) goto body;
    return 0;
body:
    {
        max = 0;
        cnt = 0;
        while (*arg2) {
            start = arg2;
            while ((c = *arg2) && c != '\n') {
                arg2++;
            }
            len = arg2 - start;
            if (max < len) {
                max = len;
            }
            cnt++;
            arg2++;
        }
        if (arg0 != NULL) {
            *arg0 = max;
        }
        if (arg1 != NULL) {
            *arg1 = cnt;
        }
        return 1;
    }
}

}
