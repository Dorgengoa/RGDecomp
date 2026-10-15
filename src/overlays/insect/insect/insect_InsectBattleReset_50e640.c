#include "types.h"
/* insect 0x0050E640 -- 452 bytes.  The battle-scene reset: rewind every
 * sub-system, seed the two screen sizes, cache two feature ids, then apply the
 * per-mode flags selected by the 0x5DA8 entry code. */

typedef struct Own {
    u8  pad0000[0x884];
    s32 f884;                       /* +0x0884 */
    s32 f888;                       /* +0x0888 */
    u8  pad088C[0x4960 - 0x88C];
    u8  f4960[0x1EC];               /* +0x4960 */
    u8  f4B4C[0x444];               /* +0x4B4C */
    u8  f4F90[0x2C];                /* +0x4F90 */
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5000 - 0x4FBD];
    u8  f5000[0x80];                /* +0x5000 */
    u8  f5080[0x8];                 /* +0x5080 */
    s16 f5088;                      /* +0x5088 */
    s16 f508A;                      /* +0x508A */
    u8  pad508C[0x5D18 - 0x508C];
    u8  f5D18[0x64];                /* +0x5D18 */
    u8  pad5D7C[0x5D90 - 0x5D7C];
    s32 f5D90;                      /* +0x5D90 */
    s8  f5D94;                      /* +0x5D94 */
    u8  pad5D95[0x5DA8 - 0x5D95];
    s32 f5DA8;                      /* +0x5DA8 */
    u8  pad5DAC[0x5DD0 - 0x5DAC];
    s16 f5DD0;                      /* +0x5DD0 */
    s16 f5DD2;                      /* +0x5DD2 */
    u8  pad5DD4[0x5EF4 - 0x5DD4];
    s32 f5EF4;                      /* +0x5EF4 */
    u8  pad5EF8[0x5EFC - 0x5EF8];
    s16 f5EFC;                      /* +0x5EFC */
    s16 f5EFE;                      /* +0x5EFE */
    u8  pad5F00[0x5FC2 - 0x5F00];
    s8  f5FC2;                      /* +0x5FC2 */
    s8  f5FC3;                      /* +0x5FC3 */
    s8  f5FC4;                      /* +0x5FC4 */
} Own;

typedef struct Sys {
    u8  pad0000[0x10];
    s32 f10;                        /* +0x10 */
    u8  pad0014[0x24 - 0x14];
    s32 f24;                        /* +0x24 */
} Sys;

typedef struct Rec {
    u8 pad0000[0x4C6];
    u8 f4C6;                        /* +0x4C6 */
    u8 f4C7;                        /* +0x4C7 */
} Rec;

extern s32   insect_InsectBattleTestFlag_50da40(Own *o, s32 k);
extern void  insect_InsectBattleClearFlag_50da90(Own *o, s32 k);
extern void  insect_InsectBattleReleaseRes_50a270(Own *o);
extern void  insect_InsectBoardClear_4efb00(u8 *p);
extern void  insect_InsectModelMemClear_512a40(u8 *p);
extern void  insect_InsectCursorSetInit_511f00(u8 *p);
extern void  insect_InsectFileSlotReset_512270(u8 *p);
extern void  insect_InsectBattleLogInit_51c5b0(u8 *p);
extern Sys  *func_1FEDE0(void);
extern s32   func_3CCAC0(s32 h, s32 k);
extern void  insect_InsectBattleClearTextBuf_50e120(Own *o, s32 k);
extern Rec  *func_430B70(s32 k);
extern s32   func_430B50(s32 k);
extern void  func_131B60(u8 *p, s32 v, s32 n);

void insect_InsectBattleReset_50e640(Own *o)
{
    Sys *s;
    Rec *r;
    s32  i;

    if (insect_InsectBattleTestFlag_50da40(o, 4) != 0) {
        insect_InsectBattleClearFlag_50da90(o, 4);
    } else {
        insect_InsectBattleReleaseRes_50a270(o);
    }
    insect_InsectBoardClear_4efb00(o->f4960);
    insect_InsectModelMemClear_512a40(o->f4B4C);
    insect_InsectCursorSetInit_511f00(o->f4F90);
    insect_InsectFileSlotReset_512270(o->f5000);
    insect_InsectBattleLogInit_51c5b0(o->f5080);
    o->f5088 = 0x20;
    o->f508A = 0x60;
    s = func_1FEDE0();
    if (s != 0) {
        o->f5EFC = func_3CCAC0(s->f10, 6);
        o->f5EFE = func_3CCAC0(s->f10, 7);
    }
    insect_InsectBattleClearTextBuf_50e120(o, 3);
    o->f884 = 0;
    o->f888 = 0;
    for (i = 5; i <= 0x4D; i++) {
        insect_InsectBattleClearFlag_50da90(o, i);
    }
    o->f5DD0 = 2;
    o->f5FC4 = -1;
    o->f5FC3 = -1;
    o->f5FC2 = -1;
    o->f5EF4 = 0;
    switch (o->f5DA8) {
    case 3:
        r = func_430B70(s->f24);
        if (r->f4C6 != 0) {
            o->f4FBC |= 4;
        }
        if (r->f4C7 != 0) {
            o->f4FBC |= 8;
        }
        break;
    case 4:
        o->f5EF4 = func_430B50(s->f24) + 0x279;
        break;
    case 0:
        break;
    }
    insect_InsectBattleClearFlag_50da90(o, 0);
    insect_InsectBattleClearFlag_50da90(o, 1);
    o->f5DD2 = 0;
    func_131B60(o->f5D18, 0, 0x64);
    o->f5D90 = 0;
    o->f5D94 = 0;
}
