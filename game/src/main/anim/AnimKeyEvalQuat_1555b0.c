/* rgp:protos */
#define RGP_SELF_AnimKeyEvalQuat_1555b0 1
#define RGP_SELF_Dec 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "vec.h"

/* AnimKeyEvalQuat_1555b0 -- the rotation-channel sampler (renames.txt: AnimSampleRotChannel).
   Build the clip clock on the stack (t, type, keys, base, count, keyA, keyB at
   sp+0x50), ask AnimKeyFindSpan_155ff0 for a key pair and a blend, decode the two keys,
   and slerp between them (QuatSlerp_13c270). Three key formats; blend == 0 is a
   shortcut in all three:
     0x20  full Vec4 keys, 16 bytes each.
     0x10  four s16 per key, decoded on VU0: vitof15.xyzw (1.15 fixed point)
           then one vmul by the per-channel scale at +0x10.
     0x08  four s8 per key, decoded on the FPU: byte / 128.0f * scale[i].

   Asm-free (s88m, was 2x inline `asm volatile { lqc2; lqc2; vitof15; vmul;
   sqc2 }`): mwcc VU0 intrinsics on file-scope `extern` vf1/vf2 bindings
   (extern = no .bss). The asm blocks were scheduling barriers and hid vf1's
   value from the optimiser; the C stand-ins are:
   - zero-word basic-block splits `if (p) { p = (T)(s32)(u32)p; }` on a LIVE
     pointer: at Dec entry (key address in a GPR), between the loads and
     vitof15 (keeps lqc2 vf1, lqc2 vf2, vitof15 order), after the first decode
     on ps (blend compare stays below the sqc2; ps becomes a4 for decode 2),
     and after the second decode on out (call setup stays below the sqc2);
   - volatile qword loads keep the key-then-scale lqc2 order;
   - the blend-0 copy reads va back through a volatile qword (retail reloads
     lq from sp+0x40 instead of forwarding vf1). */
#pragma always_inline on
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v1_1555b0_t; /* rg:vu0bind vf1 */
#define v1_1555b0 RG_VU0_BIND_VF(1, rgvb_v1_1555b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v2_1555b0_t; /* rg:vu0bind vf2 */
#define v2_1555b0 RG_VU0_BIND_VF(2, rgvb_v2_1555b0_t)

/* lqc2 vf1,(d); lqc2 vf2,(s); vitof15.xyzw vf1,vf1; vmul.xyzw vf1,vf1,vf2; sqc2 vf1,(d) */
static inline void Dec(rg_vu0_state *rg_vu0_p_, Vec4 *d, Vec4 *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    if (d) { d = (Vec4 *)(s32)(u32)d; }
    v1_1555b0 = *(volatile u128 *)d;
    v2_1555b0 = *(volatile u128 *)s;
    if (d) { d = (Vec4 *)(s32)(u32)d; }
    v1_1555b0 = _vitof15(v1_1555b0, 0xF, v1_1555b0);
    v1_1555b0 = _vmul(v1_1555b0, 0xF, v1_1555b0, v2_1555b0);
    *(u128 *)d = v1_1555b0;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

typedef struct AnimClock {
    f32 t;
    s32 type;
    s16 *keys;
    s32 base;
    s32 count;
    s32 keyA;
    s32 keyB;
    s32 timeA;
    s32 timeB;
} AnimClock;

typedef struct Channel {
    u8 pad00[0x1];
    u8 fmt;        /* +0x01, 0x08 / 0x10 / 0x20 */
    u8 type;       /* +0x02 */
    u8 pad03[0x1];
    s16 base;      /* +0x04 */
    u16 count;     /* +0x06 */
    s16 *keys;     /* +0x08 */
    u8 *data;      /* +0x0C */
    Vec4 scale;    /* +0x10 */
} Channel;

/*rgp*/
/*rgp*/

void AnimKeyEvalQuat_1555b0(Vec4 *out, Channel *ch, f32 t)
{ RG_VU0_FRAME;
    AnimClock clk __attribute__((aligned(16)));
    Vec4 va __attribute__((aligned(16)));
    Vec4 vb __attribute__((aligned(16)));
    Vec4 *pa;
    Vec4 *pb;
    u8 *data;
    Vec4 *ps;
    s16 *ka;
    s16 *kb;
    s8 *ba;
    s8 *bb;
    f32 blend;
    s32 i;

    clk.type = ch->type;
    clk.keys = ch->keys;
    clk.count = ch->count;
    clk.t = t;
    clk.base = ch->base;
    blend = AnimKeyFindSpan_155ff0(&clk);

    switch (ch->fmt) {
    case 0x10:
        pa = &va;
        data = ch->data;
        ka = (s16 *)(data + clk.keyA * 8);
        ps = &ch->scale;
        *(s32 *)&va.x = ka[0];
        *(s32 *)&va.y = ka[1];
        *(s32 *)&va.z = ka[2];
        *(s32 *)&va.w = ka[3];
        Dec(&rg_vu0, pa, ps);
        if (ps) { ps = (Vec4 *)(s32)(u32)ps; }
        if (blend == 0.0f) {
            *(u128 *)out = *(volatile u128 *)&va;
            return;
        }
        pb = &vb;
        kb = (s16 *)(data + clk.keyB * 8);
        *(s32 *)&vb.x = kb[0];
        *(s32 *)&vb.y = kb[1];
        *(s32 *)&vb.z = kb[2];
        *(s32 *)&vb.w = kb[3];
        Dec(&rg_vu0, pb, ps);
        if (out) { out = (Vec4 *)(s32)(u32)out; }
        QuatSlerp_13c270(out, &va, &vb, blend);
        return;

    case 0x20:
        data = ch->data;
        if (blend == 0.0f) {
            *out = *(Vec4 *)(data + clk.keyA * 16);
            return;
        }
        QuatSlerp_13c270(out, (Vec4 *)(data + clk.keyA * 16),
                     (Vec4 *)(data + clk.keyB * 16), blend);
        return;

    case 0x08:
        data = ch->data;
        ba = (s8 *)(data + clk.keyA * 4);
        for (i = 0; i < 4; i++) {
            f32 k = (f32)ba[i] / 128.0f;
            (&va.x)[i] = k * (&ch->scale.x)[i];
        }
        if (blend == 0.0f) {
            *out = va;
            return;
        }
        bb = (s8 *)(data + clk.keyB * 4);
        for (i = 0; i < 4; i++) {
            f32 k = (f32)bb[i] / 128.0f;
            (&vb.x)[i] = k * (&ch->scale.x)[i];
        }
        QuatSlerp_13c270(out, &va, &vb, blend);
        return;
    }
}
