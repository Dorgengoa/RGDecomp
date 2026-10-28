/* rgp:protos */
#define RGP_SELF_FuncAnimeArrayBuild_187250 1
#define RGP_SELF_look 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
#pragma peephole off

typedef struct {
    void *unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x28];
} Elem00187250;

typedef struct {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x6C - 0x64];
} Node00187250;

typedef struct {
    u8 pad0[0x504];
    s32 unk504;
    s32 *unk508;
    u8 pad50c[0x1640 - 0x50c];
    s32 unk1640;
    Elem00187250 *unk1644;
    u8 pad1648[0x1664 - 0x1648];
} Obj00187250;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 strcmp(const char *, const char *);
/*rgp*/

static inline s32 look(Obj00187250 *arg0, s32 name) {
    s32 cnt = arg0->unk504;
    s32 *arr = arg0->unk508;
    s32 i;
    s32 found;
    for (i = 0; i < cnt; i++) {
        found = arr[i];
        if (found != 0 && strcmp((char *) name, (char *) (found + 0x6C)) == 0) {
            return found;
        }
    }
    return 0;
}

void FuncAnimeArrayBuild_187250(Obj00187250 *arg0, s32 arg1) {
    s32 n;
    Elem00187250 *e;
    Node00187250 *node;

    arg0->unk1640 = n = FuncDataTableCountBucket_190930((u8 *) arg0 + 0x1664, 5);
    if (n <= 0) {
        return;
    }
    arg0->unk1644 = ((Elem00187250 *)ConstructNewArray_100710(MemStackNew_14e1b0((n << 6) + 0x10, arg1), FuncAnimeCtorMaybe_1873c0, 0, 0x40, n));
    e = arg0->unk1644;
    if (e != NULL) {
        FuncDataTableIterBegin_1908e0((u8 *) arg0 + 0x1664, 5);
        while ((node = ((Node00187250 *)FuncDataTableIterNext_1908b0((u8 *) arg0 + 0x1664))) != NULL) {
            s32 name;
            s32 found;
            e->unk4 = 0;
            e->unk8 = 0;
            e->unkC = 0;
            e->unk0 = NULL;
            e->unk14 = 0;
            e->unk10 = 0;
            e->unk0 = node;
            name = node->unk60;
            found = 0;
            if (name != 0) {
                found = look(arg0, name);
            }
            FuncAnimeBind_190fc0(e, node, found);
            e++;
        }
        FuncDataTableIterEnd_1908a0((u8 *) arg0 + 0x1664);
        return;
    }
}
