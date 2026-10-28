/* rgp:protos */
#define RGP_SELF_Vec3VectorReserve_171230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Vec3;

typedef struct {
    u32 cap;
    s32 n;
    Vec3 *data;
} VecV;

/*rgp*/
/*rgp*/
/*rgp*/
extern void Fprintf_12f9a0(s32, void *);
/*rgp*/
extern u8 D_00449858[0x400];
extern u8 D_004591F0[];
extern u8 D_00459210[];

void Vec3VectorReserve_171230(VecV *v, u32 n)
{
    VecV tmp __attribute__((aligned(16)));
    Vec3 *dst;
    Vec3 *src;
    Vec3 *end;
    u32 t0;
    Vec3 *t1;
    s32 t2;

    if (v->cap < n) {
        if (n > 0x15555555U) {
            Fprintf_12f9a0(*(s32 *)(*(u8 **)D_00449858 + 0xC), D_004591F0);
            Abort_12de80();
        }
        tmp.cap = 0;
        tmp.n = 0;
        tmp.data = 0;
        dst = ((Vec3 *)OperatorNew_100990(n * 0xC));
        if (dst == NULL) {
            Fprintf_12f9a0(*(s32 *)(*(u8 **)D_00449858 + 0xC), D_00459210);
            Abort_12de80();
        }
        tmp.cap = n;
        tmp.data = dst;
        src = v->data;
        end = src + v->n;
        for (; src < end; src++, dst++) {
            if (dst != NULL) {
                *dst = *src;
            }
            tmp.n++;
        }
        if (&tmp != v) {
            t0 = tmp.cap;
            tmp.cap = v->cap;
            v->cap = t0;
            t1 = tmp.data;
            tmp.data = v->data;
            v->data = t1;
            t2 = tmp.n;
            tmp.n = v->n;
            v->n = t2;
        }
        Vec3VectorClear_171420(&tmp);
        if (tmp.data != NULL) {
            OperatorDelete_100840(tmp.data);
        }
    }
}
