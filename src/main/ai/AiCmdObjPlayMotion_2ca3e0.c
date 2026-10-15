#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 ScriptSlotGetInt_2cc9c0(E8 *);
extern char *ScriptSlotGetCodeAddr_2cc980(E8 *);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern char *ModelObjGetMotionName_1add90(s32);
extern s32 strcmp(char *, char *);
extern void CharaPlayMotion_212590(s32, s32, f32, char *, s32);

extern struct { s32 v; s32 pad[3]; } D_004DB920;
extern const s32 D_004DB92C;
extern f32 D_0047D240;

s32 AiCmdObjPlayMotion_2ca3e0(E8 *p0)
{
    s32 h;
    s32 a;
    char *b;
    s32 c;
    s32 r;

    h = D_004DB920.v;
    a = ScriptSlotGetInt_2cc9c0(p0++);
    b = ScriptSlotGetCodeAddr_2cc980(p0++);
    c = ScriptSlotGetInt_2cc9c0(p0);
    r = ObjRecGetLiveObject_1c4a90(h, a);
    if (r == 0) {
        return 0;
    }
    if (ModelObjGetMotionName_1add90(r) != 0) {
        if (strcmp(ModelObjGetMotionName_1add90(r), b) == 0) {
            return 1;
        }
    }
    if (r != 0) {
        CharaPlayMotion_212590(D_004DB92C, r, D_0047D240, b, c);
    }
    return 1;
}
