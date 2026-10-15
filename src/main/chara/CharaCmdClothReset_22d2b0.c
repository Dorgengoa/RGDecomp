#include "types.h"

/* `if (argc != 0 && argc != 1) return 0;` - the two beq's both jump INTO the
   body and the fall-through is the failure return.  The 0x1E default is in the
   `bne` delay slot, so it is an unconditional initialiser overwritten by the
   call in the argc==1 arm. */

extern s32 GetCurrentScene_1f5be0(void);
extern struct Rec *ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 ScriptArgGetInt_302d70(s32);

struct Obj0 {
    s32 m00;
};

struct Rec {
    u8 pad[0x464];
    s32 m464;
    s8 m468;
};

s32 CharaCmdClothReset_22d2b0(struct Obj0 *p0, s32 p1, s32 argc)
{
    s32 r0;
    struct Rec *rec;
    s32 v;

    if (argc != 0 && argc != 1) {
        return 0;
    }
    r0 = GetCurrentScene_1f5be0();
    rec = ObjRecGetLiveObject_1c4a90(r0, p0->m00);
    if (rec == 0) {
        return 1;
    }
    v = 0x1E;
    if (argc == 1) {
        v = ScriptArgGetInt_302d70(p1);
    }
    rec->m464 = v + 1;
    rec->m468 = 0;
    return 1;
}
