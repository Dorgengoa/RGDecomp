#include "types.h"
/* normal 0x00519D50 -- two field stores through the parameter before it is
 * copied to a callee-saved register, then four calls. */
typedef struct Obj {
    u8  pad00[0xA];
    s16 f0A;
    u8  pad0C[2];
    s16 f0E;
} Obj;

extern void func_37B490(s32 a);
extern void normal_TransSaveSlotCursorBob_518990(Obj *p, void *q, s32 c);
extern void normal_TransSaveSlotMoveCb_519dd0(Obj *p, void *q);
extern void func_3777A0(Obj *p, s32 b, s32 c);

s32 normal_TransSaveSlotListEnterCb_519d50(Obj *p, void *q)
{
    p->f0E = 0x31;
    p->f0A = 2;
    func_37B490(0x75A2);
    normal_TransSaveSlotCursorBob_518990(p, q, 1);
    normal_TransSaveSlotMoveCb_519dd0(p, q);
    func_3777A0(p, 0x75A1, 0);
    return 1;
}
