#include "types.h"

typedef struct { u8 d[0x1A0]; } ObjC;
typedef struct { u8 d[0x630]; } ObjB;
typedef struct { u8 d[0x1A0]; } ObjA;

typedef struct {
    u8 pad00[0x18];
    s32 f18;
} Cur;

extern s32 ScriptSlotGetInt_3348b0(void *);
extern f32 ScriptSlotGetFloat_334890(void *);
extern void AttackObjBaseCtor_3181b0(ObjC *, s32, s32, s32, f32);
extern void ProjectileCtor_317eb0(ObjB *, s32, s32, s32, f32);
extern void AttackObjCtor_3175c0(ObjA *, s32, s32, s32, f32);
extern s32 AttackObjBaseCloneAndRegister_27bd90(ObjC *);
extern s32 ProjectileCloneAndRegister_22e560(ObjB *);
extern s32 AttackObjCloneAndRegister_3348e0(ObjA *);
extern void ScriptSlotStoreIntRef_3347f0(void *, s32);

extern char D_00471AA0[];
extern Cur *D_004826E0;

/* compare chain 5,4,3 = the switch's case order REVERSED -> source is 3,4,5.
   stack locals are allocated in REVERSE declaration order: a -> 0x60,
   b -> 0x200, c -> 0x830. */
s32 ScriptCmdAttackObjCreate_32f9e0(u8 *p, s32 mode)
{
    ObjC c;
    ObjB b;
    ObjA a;
    s32 r;
    s32 x;
    s32 y;
    s32 z;

    if (mode != 5 && mode != 6) {
        return 0;
    }
    r = -1;
    switch (ScriptSlotGetInt_3348b0(p)) {
    case 3:
        x = ScriptSlotGetInt_3348b0(p + 8);
        y = ScriptSlotGetInt_3348b0(p + 0x10);
        z = ScriptSlotGetInt_3348b0(p + 0x18);
        AttackObjBaseCtor_3181b0(&c, x, y, z, ScriptSlotGetFloat_334890(p + 0x20));
        r = AttackObjBaseCloneAndRegister_27bd90(&c);
        *(void **)((u8 *)&c + 0xB0) = D_00471AA0;
        break;
    case 4:
        x = ScriptSlotGetInt_3348b0(p + 8);
        y = ScriptSlotGetInt_3348b0(p + 0x10);
        z = ScriptSlotGetInt_3348b0(p + 0x18);
        ProjectileCtor_317eb0(&b, x, y, z, ScriptSlotGetFloat_334890(p + 0x20));
        r = ProjectileCloneAndRegister_22e560(&b);
        *(void **)((u8 *)&b + 0xB0) = D_00471AA0;
        break;
    case 5:
        x = ScriptSlotGetInt_3348b0(p + 8);
        y = ScriptSlotGetInt_3348b0(p + 0x10);
        z = ScriptSlotGetInt_3348b0(p + 0x18);
        AttackObjCtor_3175c0(&a, x, y, z, ScriptSlotGetFloat_334890(p + 0x20));
        r = AttackObjCloneAndRegister_3348e0(&a);
        *(void **)((u8 *)&a + 0xB0) = D_00471AA0;
        break;
    }
    if (D_004826E0 != 0) {
        if (r >= 0) {
            D_004826E0->f18 = r;
        }
    }
    if (mode == 6) {
        ScriptSlotStoreIntRef_3347f0(p + 0x28, r);
    }
    return 1;
}
