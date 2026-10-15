#include "types.h"

struct Ent {
    char *name;
    s32 b;
    s32 c;
    u16 d;
    u16 e;
};

struct Tbl {
    char *names[21];
};

class Obj {
public:
    u8 pad[0x2C];
    virtual void v08();
};

extern "C" {
extern s32 StrHash16_1f56d0(char *);
extern void TaskResetAll_27c300();
extern void DebugMenuWidgetInit_2092c0(void *);
extern void DebugMenuWidgetSetLabel_209bb0(void *, void *);
extern void DebugMenuWidgetSetFlags_209c30(void *, s32);
extern void DebugTaskItemSetList_208bc0(void *, void *);
extern s32 StrEqualNonNull_1ca6c0(char *, char *);
extern Ent D_0044ECF0[0xB0];
extern s32 D_0044F7F0[21];
extern char D_0045FF60[];
extern u8 D_00460CF8[];
extern s32 D_00482278;
extern Ent D_004D7FA0[0xB0];
extern u8 D_004D8AA0[];
extern u8 D_004DAE60[];
extern void *D_004DAE90[];
}

extern "C" void TaskTableInit_27c310(void)
{
    Ent *src;
    Ent *dst;
    s32 i;
    Tbl t;
    char **p;
    Ent *e;
    Obj *o;
    void **slot;

    src = D_0044ECF0;
    dst = D_004D7FA0;
    for (i = 0; i < 0xB0; i++) {
        src->e = StrHash16_1f56d0(src->name);
        *dst = *src;
        src++;
        dst++;
    }
    TaskResetAll_27c300();
    D_00482278 = 0;
    t = *(Tbl *)D_0044F7F0;
    DebugMenuWidgetInit_2092c0(D_004DAE60);
    DebugMenuWidgetSetLabel_209bb0(D_004DAE60, D_00460CF8);
    DebugMenuWidgetSetFlags_209c30(D_004DAE60, 1);
    e = D_004D7FA0;
    o = (Obj *)D_004D8AA0;
    slot = D_004DAE90;
    while (e->name != 0) {
        o->v08();
        DebugTaskItemSetList_208bc0(o, D_004DAE90);
        if (StrEqualNonNull_1ca6c0(e->name, D_0045FF60) != 0) {
            *slot = D_004DAE60;
        } else {
            for (p = t.names; *p != 0; p++) {
                if (StrEqualNonNull_1ca6c0(e->name, *p) != 0) {
                    break;
                }
            }
            if (*p != 0) {
                DebugMenuWidgetSetFlags_209c30(o, 8);
            }
            *slot = o;
        }
        o = (Obj *)((u8 *)o + 0x34);
        e++;
        slot++;
    }
    *slot = 0;
}
