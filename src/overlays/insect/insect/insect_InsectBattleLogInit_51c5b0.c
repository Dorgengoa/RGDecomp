#include "types.h"
/* insect 0x0051C5B0 -- object reset.  insect_InsectBattleLogSetRect_51c210 takes FIVE integer
 * arguments ($4..$8); the R5900 EABI numbers integers $4..$11, so the 0x60 in
 * $8 is an ordinary fifth argument and not a leftover.  The two store blocks
 * are written in retail's emission order. */
typedef struct Ent {
    s32 f00;
    s32 f04;           /* +0x04 */
    s16 f08, f0A, f0C, f0E;
    u8 pad10[0x8];
    s16 f18, f1A, f1C, f1E;
    u8 pad20[0x2];
    s16 f22;
    s8 f24, f25, f26;
    u8 pad27[0x1];
    u8 f28[0x4];       /* +0x28 -- a sub-object */
} Ent;

extern void insect_InsectBattleLogSetRect_51c210(Ent *o, s32 b, s32 c, s32 d, s32 e);
extern void insect_InsectBattleLogResetWait_51c0e0(Ent *o);
extern void func_26C610(void *p);
extern void func_26EDF0(void *p, s32 b);
extern void func_26F2B0(void *p, s32 b, s32 c);

void insect_InsectBattleLogInit_51c5b0(Ent *o)
{
    o->f04 = 0;
    o->f0C = 0;
    o->f0E = 0;
    o->f0A = 0;
    o->f08 = 0;
    insect_InsectBattleLogSetRect_51c210(o, 0, 0, -1, 0x60);
    o->f18 = 2;
    o->f22 = 0;
    o->f24 = 0;
    o->f1A = 2;
    o->f1C = 0x4B;
    insect_InsectBattleLogResetWait_51c0e0(o);
    o->f1E = 0;
    o->f25 = 0;
    o->f26 = 0;
    func_26C610(&o->f28);
    func_26EDF0(&o->f28, 2);
    func_26F2B0(&o->f28, 3, 0);
}
