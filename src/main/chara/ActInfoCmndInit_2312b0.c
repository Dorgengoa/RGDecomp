#include "types.h"

typedef struct {
    char *m00;
    s32 m04;
    s32 m08;
} Rec;

void ActInfoCmndInit_2312b0(Rec *o, char *s, u64 y)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m08 = 0;
    if (s == 0 || s[0] == 0 || y == 0) {
        return;
    }
    o->m00 = s;
    o->m04 = (s32)y;
    o->m08 = (s32)(y >> 32);
}
