#include "types.h"

struct Slot {
    s16 id;
    u8 a;
    u8 b;
};

struct Tbl {
    s16 n;
    Slot s[16];
    u8 pad42[2];
    u8 f : 1;
};

struct Cfg {
    u8 pad[0x2C];
    s16 mode;
};

struct Sys {
    u8 pad[0xC];
    Cfg *cfg;
};

extern Sys *D_004837BC;

extern "C" s32 CharaEventLogKeyAdd_3a6830(Tbl *t, s32 id, u8 *res)
{
    bool found;
    Slot *s;
    s32 i;

    if (id < 0) {
        return 0;
    }
    if (res != NULL) {
        *res = 0;
    }
    if (D_004837BC->cfg->mode != 1) {
        return 0;
    }
    found = false;
    {
        Slot *u;
        s32 j;
        for (u = t->s, j = 0; j < t->n; j++, u++) {
            if (u->id == id) {
                return 1;
            }
        }
    }
    for (s = t->s, i = 0; i < t->n; i++, s++) {
        if (s->id < 0) {
            s->id = id;
            found = true;
            s->a = 0;
            s->b = 0;
            break;
        }
    }
    if (!found && t->n < 16) {
        t->n++;
        found = true;
        s->id = id;
        s->a = 0;
        s->b = 0;
    }
    if (!found) {
        return 0;
    }
    t->f = 0;
    if (res != NULL) {
        *res = 1;
    }
    return 1;
}
