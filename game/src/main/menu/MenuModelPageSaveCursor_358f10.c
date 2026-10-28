/* rgp:protos */
#define RGP_SELF_MenuModelPageSaveCursor_358f10 1
#define RGP_SELF_clr 1
#include "port/game_protos.h"
#line 1
/* PARKED at triage (0 round trips): m2c's draft has the same ambiguous
 * local-array-on-stack address pattern as AttackChainMarkersShow_382c40/MenuPartySwapAnimWaitState_2b8680
 * (`(temp_2_2 + sp)->unk48`) plus an undeclared `sp4C` implied adjacent to
 * the declared `sp48` byte -- needs a raw-asm trace of the stack frame
 * before it's worth compiling. Deferred to preserve lane throughput.
 * See asm/matchings/main/MenuModelPageSaveCursor_358f10.s. */
/* s49m: MATCH */
#include "types.h"

/*rgp*/
/*rgp*/

static inline void clr(void *p, u32 n)
{
    u8 *q;
    u32 c;

    c = n;
    q = (u8 *)p;
    if (q != 0) {
        do {
            *q = 0;
            c--;
            q++;
        } while (c != 0);
    }
}

void MenuModelPageSaveCursor_358f10(u8 *self)
{
    s32 bits;
    s32 buf[2];
    s32 k;
    s32 j;
    s32 i;
    u8 *obj;

    obj = ((u8 *)GetGameData_1fede0());
    if (*(s16 *)(*(u8 **)(obj + 0xC) + 0x26) != 1) {
        return;
    }
    bits = 0;
    bits |= self[0xEA] & 7;
    for (i = 0; i < 8; i++) {
        bits |= (self[0xEB + i] & 1) << (i + 3);
    }
    PartyMenuCursorSet_3c0710(*(s32 *)(obj + 0x18), 0xF, (int)((s16)bits));
    for (j = 0; j < 8; j++) {
        k = *(s16 *)(self + 0xDA + j * 2) - 0x2AF9;
        if (k < 0) {
            continue;
        }
        clr(buf, 8);
        for (i = 0; i < 2; i++) {
            buf[i] = self[k * 4 + i * 2 + 0x114] + self[k * 4 + i * 2 + 0xF4];
        }
        PartyMenuCursorSet_3c0710(*(s32 *)(obj + 0x18), k + 0x1C, (int)((s16)(*(u8 *)&buf[0] | (*(u8 *)&buf[1] << 8)))
);
    }
}
