#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off
struct Tbl {
    s32 start[32];
    s32 count[32];
    bool Valid(s32 i) { return i >= 0 && i < 32; }
    s32 Start(s32 i) { bool v = Valid(i); if (!v) return -1; return start[i]; }
    s32 Count(s32 i) { bool v = Valid(i); if (!v) return 0; return count[i]; }
};

struct Ent {
    s32 used;
    Tbl *tbl;
    bool IsUsed() { return used != 0; }
};

struct Obj {
    u8 pad[0x210];
    s32 n;
    Ent e[1];
};

extern "C" s32 SceneTableCollectDrawGroupTexIdsMaybe_1961a0(Obj *o, s32 k, s32 *out, s32 max)
{
    s32 n = 0;
    s32 i;
    for (i = 0; i < o->n; i++) {
        
        Tbl *t;
        s32 s;
        s32 c;
        s32 j;
        bool b;
        {
            u8 *q = (u8 *)o + i * 8;
            b = !(*(s32 *)(q + 0x214) != 0);
            if (b) continue;
            t = *(Tbl **)(q + 0x218);
        }
        if (t == 0) continue;
        s = t->Start(k);
        if (s < 0) continue;
        c = t->Count(k);
        if (c <= 0) continue;
        for (j = 0; j < c; j++) {
            if (n >= max) break;
            out[n++] = s + j;
        }
    }
    return n;
}
