#include "types.h"
/* insect 0x00511CF0 -- 304 bytes.  An eight-slot ring: take the first empty
 * slot, otherwise shift the whole table down one and use the last.  The `break`
 * needs the explicit flag because the shift path is guarded by it. */

typedef struct Obj {
    u8    pad00[0xC];
    void *f0C[8];                   /* +0x0C */
    u8    f2C;                      /* +0x2C */
} Obj;

typedef struct Ent {
    u8 pad00[0x8];
    s8 f08;                         /* +0x08 */
    s8 f09;                         /* +0x09 */
    s8 f0A;                         /* +0x0A */
    s8 f0B;                         /* +0x0B */
} Ent;

extern Ent *insect_InsectCursorSetGetCurPage_511e20(Obj *o);
extern Ent *insect_InsectCursorSetFindPage_511e60(Obj *o, s32 k);

Ent *insect_InsectCursorSetPushPage_511cf0(Obj *o, s32 k, s32 clear)
{
    Ent   *r;
    s32    found;
    void **p;
    s32    i;
    s32    j;

    r = 0;
    found = 0;
    o->f2C = o->f2C | 2;
    o->f2C = o->f2C & 0xBF;
    if (insect_InsectCursorSetGetCurPage_511e20(o) != insect_InsectCursorSetFindPage_511e60(o, k)) {
        for (i = 0; i < 8; i++) {
            p = &o->f0C[i];
            if (*p == 0) {
                r = *p = insect_InsectCursorSetFindPage_511e60(o, k);
                found = 1;
                break;
            }
        }
        if (found == 0) {
            for (j = 0; j < 7; j++) {
                o->f0C[j] = o->f0C[j + 1];
            }
            r = o->f0C[7] = insect_InsectCursorSetFindPage_511e60(o, k);
        }
    }
    if (clear != 0) {
        if (r != 0) {
            r->f09 = 0;
            r->f08 = 0;
            r->f0B = 0;
            r->f0A = 0;
        }
    }
    return r;
}
