#include "types.h"
/* normal 0x004F9970 -- open the 0x81 widget and pick one of two box layouts
 * off bit 0 of the head node's 0x1A flags.  The `beql $2, $0, .L004F9A78`
 * carries the shared `p->f49C = 1` constant in its delay slot, so the store
 * is ONE statement at the end, not one per arm. */

typedef struct Box {
    u8  pad00[0x24];
    s16 f24;
    s16 f26;
    s16 f28;
    s16 f2A;
    s16 f2C;
    s16 f2E;
} Box;

typedef struct Ent  { u8 pad00[0x20]; Box *f20; } Ent;
typedef struct Node { u8 pad00[0x1A]; s16 f1A; } Node;
typedef struct Ctx  { u8 pad00[0xC]; Node *f0C; } Ctx;

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x49C - 0x37A];
    s16 f49C;
} Obj;

extern Ctx  *func_1FEDE0(void);
extern Ent  *func_290460(Obj *a, u16 id);
extern void  func_291110(Obj *a, u16 id, s32 c, s32 d);
extern void  func_290F60(Obj *a, u16 id, s32 c, s32 d);
extern void  func_2907A0(Obj *a, u16 id, f32 t);

void normal_FieldHudWidget81Open_4f9970(Obj *p)
{
    Ctx *h;
    Ent *e;
    Box *q;

    if (p->f378 == 0) {
        return;
    }
    func_291110(p, 0x81, 1, 1);
    func_290F60(p, 0x81, 0x12, 0x46);
    func_2907A0(p, 0x81, 1.0f);
    h = func_1FEDE0();
    if (h == NULL) {
        return;
    }
    if ((h->f0C->f1A & 1) == 0) {
        e = func_290460(p, 0x81);
        if (e != NULL) {
            q = e->f20;
            if (q != NULL) {
                q->f28 = 0x9C;
                q->f2A = 0x128;
                q->f2C = 0x2A;
                q->f24 = 0x2A;
                q->f2E = 0x10;
                q->f26 = 0x10;
            }
        }
    } else {
        e = func_290460(p, 0x81);
        if (e != NULL) {
            q = e->f20;
            if (q != NULL) {
                q->f28 = 0xC6;
                q->f2A = 0x128;
                q->f2C = 0x2A;
                q->f24 = 0x2A;
                q->f2E = 0x10;
                q->f26 = 0x10;
            }
        }
    }
    p->f49C = 1;
}
