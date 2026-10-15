#include "types.h"
/* normal 0x004F6AB0 -- the store is through the PARAMETER, before it is copied
 * to the callee-saved register, so it is the first statement. */
typedef struct Obj {
    u8  pad000[0x14];
    u8  f014;
    u8  pad015[0x28 - 0x15];
    u8  f028;
    u8  pad029[0x3DC - 0x29];
    s16 f3DC;
} Obj;

extern void func_382FC0(void *a);
extern void func_290010(void *a, s32 b, s32 c, s32 d);

void normal_FieldHudAttackChainHide_4f6ab0(Obj *p)
{
    p->f3DC = 0;
    func_382FC0(&p->f028);
    func_290010(&p->f014, 1, 0, -1);
    func_290010(&p->f014, 2, 0, -1);
    func_290010(&p->f014, 3, 0, -1);
    func_290010(&p->f014, 4, 0, -1);
}
