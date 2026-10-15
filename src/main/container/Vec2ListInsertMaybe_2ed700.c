#include "types.h"

extern u8 *OperatorNew_100990(s32);
extern void OperatorDelete_100840(u8 *);
extern void Fprintf_12f9a0(s32, u8 *);
extern void Abort_12de80(void);
extern u8 *D_00449858[];
extern u8 D_00461A40[];

typedef struct {
    s32 *cnt;
    u8 *p;
    s32 pad;
    s8 flag;
} Hold2ed;

typedef struct { f32 x; f32 y; } Vec2ed;

s32 Vec2ListInsertMaybe_2ed700(u8 **arg0, s32 *arg1, u8 ***arg2, Vec2ed *arg3) {
    Hold2ed h;
    Hold2ed *hp;
    u8 *n;
    u8 **head;
    u8 *t;
    Vec2ed *v;
    s32 *c;

    hp = &h;
    hp->flag = 0;
    c = arg1 + 1;
    n = OperatorNew_100990(0x10);
    n = (u8 *)(u32)n;
    if (n == NULL) {
        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00461A40);
        Abort_12de80();
    }
    v = (Vec2ed *)(n + 8);
    h.cnt = c;
    h.p = n;
    if (v != NULL) {
        *v = *arg3;
    }
    t = hp->p;
    head = *arg2;
    hp->p = NULL;
    *(u8 **)(*head + 4) = t;
    *(u8 **)t = *head;
    *head = t;
    *(u8 ***)(t + 4) = head;
    *arg1 += 1;
    *arg0 = t;
    if (hp->p != NULL) {
        OperatorDelete_100840(hp->p);
    }
    return 0;
}
