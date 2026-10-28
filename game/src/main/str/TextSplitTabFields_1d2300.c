/* rgp:protos */
#define RGP_SELF_TextSplitTabFields_1d2300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 *unk0;
    s8 *unk4;
} Obj001B78D0;

s32 memcmp(u8 *, u8 *, s32);
extern u8 D_0047E2FC;
extern u8 D_0047E2FD;

u8 *TextSplitTabFields_1d2300(u8 *arg0, u8 *p, u8 *end) {
    u8 sp[2];
    s32 n;
    s32 k;
    Obj001B78D0 *e;
    s8 c;

    n = 0;
    sp[0] = D_0047E2FC;
    sp[1] = D_0047E2FD;
    while (p < end) {
        if (memcmp(p, sp, 2) == 0) {
            p += 2;
            break;
        }
        if (memcmp(p, sp, 1) == 0) {
            p += 1;
            break;
        }
        if (memcmp(p, &sp[1], 1) == 0) {
            p += 1;
            break;
        }
        k = 0;
        e = (Obj001B78D0 *)(arg0 + n * 4);
        while (p < end) {
            if (memcmp(p, sp, 2) == 0) break;
            if (memcmp(p, sp, 1) == 0) break;
            if (memcmp(p, &sp[1], 1) == 0) break;
            c = *p;
            if (c == 9) {
                p++;
                if (e->unk4 != NULL) {
                    *e->unk4 = 0;
                }
                break;
            }
            if (c != 0x20) {
                if (e->unk0 != NULL) {
                    e->unk0[k] = c;
                    k++;
                }
            }
            p++;
        }
        if (e->unk0 != NULL) {
            n++;
            e->unk0[k] = 0;
        }
    }
    return p;
}
