#include "types.h"
/* insect 0x0050E260 -- 76 bytes, 19 instructions, 2 calls, no branches. */

typedef struct Obj {
    u8    pad00[0x500];
    u8    f500[0x870 - 0x500];      /* +0x500 */
    s32   f870;                     /* +0x870 */
    u8    pad874[0x5178 - 0x874];
    void *f5178;                    /* +0x5178 */
    s32   f517C;                    /* +0x517C */
    u8    pad5180[0x51C0 - 0x5180];
    f32   f51C0;                    /* +0x51C0 */
    u8    pad51C4[0x5FC8 - 0x51C4];
    f32   f5FC8;                    /* +0x5FC8 */
} Obj;

extern void insect_InsectBattleSetFlag_50dad0(Obj *o, s32 k);
extern void insect_InsectBattleEffectsInit_51e040(void *p);

void insect_InsectBattleSetupEffects_50e260(Obj *o)
{
    insect_InsectBattleEffectsInit_51e040(&o->f5178);
    o->f517C = o->f870;
    o->f5178 = o->f500;
    o->f51C0 = o->f5FC8;
    insect_InsectBattleSetFlag_50dad0(o, 0x2A);
}
