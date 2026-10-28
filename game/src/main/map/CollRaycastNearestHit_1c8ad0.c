/* rgp:protos */
#define RGP_SELF_CollRaycastNearestHit_1c8ad0 1
#define RGP_SELF_clear 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4;

typedef struct {
    f32 t0;
    f32 t1;
    u8 pad8[8];
    V4 c0;
    V4 d0;
    V4 e0;
    V4 f0;
    f32 x100;
    f32 x104;
} Ray;

typedef struct {
    u8 pad0[0x46];
    s16 unk46;
    u8 pad48[0x18];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline void clear(u8 *q, u32 n)
{
    if (q) {
        for (; n != 0; n--) {
            *q++ = 0;
        }
    }
}

s32 CollRaycastNearestHit_1c8ad0(V4 *dst, s32 id, Obj *obj, s32 n, s32 mask, V4 *arg3, V4 *arg4, f32 *out)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x10 + sizeof(V4)]; char m1[0x0 + sizeof(V4)]; char m2[(0x30 - __builtin_offsetof(Ray, c0)) + sizeof(Ray)]; char m3[0x10]; char m4[0x20]; char m5[0x50]; char m6[0x40]; char m7[0x70]; char m8[0x60]; char m9[0x78]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(V4) <= (0x10) && (0x0) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk1[(0x10) + sizeof(V4) <= ((0x30 - __builtin_offsetof(Ray, c0))) && (0x10) >= 0 ? 1 : -1];
    
    
    V4 e __attribute__((aligned(16)));
    V4 c __attribute__((aligned(16)));
    V4 d __attribute__((aligned(16)));
    s32 best;
    Obj *o;
    s32 i;
    s32 k;

    if (out != NULL) {
        *out = 1.0f;
    }
    if (obj == NULL || n <= 0) {
        return -1;
    }
    VecCopyAsPoint_1cbe10(&(*(V4 *)(rgp_blk1 + 0x0)), arg3);
    VecCopyAsDir_1cbe20(&(*(V4 *)(rgp_blk1 + 0x10)), arg4);
    (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).t0 = 0.0f;
    (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).x100 = (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).t0 * (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).t0;
    (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).x104 = VecLengthSq_1cb470(&(*(V4 *)(rgp_blk1 + 0x10)), 0);
    (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).t1 = 1.0f;
    VecLinearCombine_1cb8b0(&c, &(*(V4 *)(rgp_blk1 + 0x10)), &(*(V4 *)(rgp_blk1 + 0x0)), 1.0f, 1.0f);
    VecMinMax_1cb570(&(*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).d0, &(*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).c0, &(*(V4 *)(rgp_blk1 + 0x0)), &c);
    clear((u8 *)&d, sizeof(d));
    d.x = (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).t0;
    d.y = (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).t0;
    d.z = (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).t0;
    VecAdd_1cbdc0(&(*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).f0, &(*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).d0, &d);
    VecSub_1cbd00(&(*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).e0, &(*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).c0, &d);
    k = id;
    best = -1;
    o = obj;
    for (i = 0; i < n; i++, o++) {
        if (!(o->unk46 & mask) && CollSweepTri_1c7790(&(*(V4 *)(rgp_blk1 + 0x0)), o, (u8 *)o + 0x10, (u8 *)o + 0x20) != 0) {
            best = i;
            k = id;
        }
    }
    if (out != NULL) {
        *out = (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).t1;
    }
    if (best >= 0) {
        VecScale_1cbca0(&e, arg4, (*(Ray *)(rgp_blk1 + (0x30 - __builtin_offsetof(Ray, c0)))).t1);
        VecAdd_1cbdc0(dst, &e, arg3);
        VecCopy_1cbe30(k, (u8 *)&obj[best] + 0x30);
    }
    return best;
}
