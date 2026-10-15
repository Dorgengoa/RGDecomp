#include "types.h"

typedef struct N1981f0 {
    u8 type;
    u8 pad1[3];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u16 unk10;
    u16 pad12;
    s32 unk14;
    struct N1981f0 *next;
} N1981f0;

s32 MemStackNew_14e1b0(s32, s32);
N1981f0 *MemStackNew_14e230(s32);

N1981f0 *EffTexAnimeParamAppendStep_1981f0(N1981f0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 buf;
    N1981f0 *p;
    N1981f0 *n;

    n = MemStackNew_14e230(0x1C);
    if (n != NULL) {
        n->type = arg2;
        n->unk4 = 0;
        n->unkC = 0;
        n->unk8 = 0;
        n->next = NULL;
    }
    if (n == NULL) {
        return NULL;
    }
    if ((arg2 & 0xFF) == 2) {
        buf = MemStackNew_14e1b0(arg3 * 2, arg1);
        n->unk14 = buf;
        if (buf != 0) {
            n->unk10 = arg3;
        } else {
            n->unk10 = 0;
        }
    }
    if (arg0->next == NULL) {
        arg0->next = n;
    } else {
        p = arg0->next;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = n;
    }
    return n;
}
