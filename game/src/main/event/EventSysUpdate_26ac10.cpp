/* rgp:protos */
#line 1
#include "vec.h"
#pragma opt_dead_assignments off

/* The system-VM -> event-player hop, run once per frame.

   Three parts. Step the 0x20 sub-machines in the D_00482068 array; then, for
   every one of the 224 slots whose flag word has bit 0 set, find the object
   and its track, take the followed node's position, and probe the world around
   it; then, if the rig block at D_004BD9B0 is armed, rebuild its matrix and
   hand it to the renderer. Finally tick the event player.

   â˜… The probe radius is computed in DOUBLE precision, which on the EE means
   the software helpers: `fptodp`, `dpadd`, `dpsub`, `dptofp`. mwcc emits them
   for ordinary `double` arithmetic, and passes a double in ONE 64-bit GPR --
   `lui v0, 0x4034 / dsll32 v0, v0, 0` is the constant 20.0. Those four
   library entries are now named in config/main.symbols.txt.

   So each of x, y and z is scaled up by twenty and down by twenty, giving the
   two corners of a box around the followed node -- and doing it through
   `double` rather than `float` is deliberate, because 20.0 and 1/20.0 are not
   exact in binary and the two corners have to stay symmetric.

   The probe hands back a HEIGHT, and it replaces the track position's Y, not
   its W -- retail stores it at +0x04 of the copied vector.

   â˜… IT RETURNS 1. Retail's epilogue interleaves `addiu $2, $0, 0x1` with the
   register restores; the function was prototyped `void` here and that was one
   of the two missing words. 92.79 -> 93.49%, two words short -> one.
   â‡’ **Read the epilogue for a stray `$2` before believing a `void` return.**

   STATUS 93.49% on b210, ONE word short, and it is the box loop: retail
   materialises BOTH addresses (`addiu $2, $3, 0x6140` for the source and
   `addiu $16, $3, 0x6120` for the destination, off the shared `k*4 + sp`)
   where mwcc folds our single-use source pointer into the `lwc1`'s
   displacement. âš  Eight spellings measured 2026-08-22 and all are inert or
   worse: `const f32 *`, `src[0]` as its own statement, declaring dst before
   src, reading `*src` twice instead of a named `v`, `*src++`, a dead
   `src = src + 1`, `*(dst + 4)`, and hoisting both bases out of the loop and
   indexing them (that last one is FIVE words long).
   âš âš  FIVE MORE measured 2026-08-22 (third session), so THIRTEEN spellings are
   now dead here and the next reader should want a MECHANISM, not a spelling:
   `(u8 *)&pos.x + k * 4` pointer arithmetic (inert, 190); a `static inline`
   helper taking both pointers (inert, 190); three separate pointers
   `src`/`up`/`dn` so `&box[1].x + k` is named (inert, 190); base-plus-index
   `f32 *src = &pos.x; v = src[k]` with `dst[k]`/`dst[k+4]` (inert, 190, and
   the emitted loop is instruction-identical to the baseline); and integer
   address arithmetic `(f32 *)(k * 4 + (s32)&pos.x)`, which DOES materialise
   both addresses but costs six words (196).
   â˜… What the last two together say: mwcc reassociates every spelling to the
   same `(sp + k*4) + const` tree and then folds a SINGLE-USE address into the
   load's displacement. `dst` survives only because it has two uses. So the
   open question is not "which spelling" but "what gives the source pointer a
   second use, or otherwise blocks the fold, without adding an instruction" --
   and reading `*src` twice does not, because mwcc then CSEs the whole
   `(double)*src` conversion and the function loses THREE words (187).

   The rig block's six differing words are LENGTH-NEUTRAL: retail spells both
   tests as likely branches with the taken block's first instruction moved into
   the delay slot -- `beql owner == 0` carrying `sw $0, 0x4($16)`, and
   `beql locked == 0` carrying the `addiu $4, $29, 0x70` that is
   sceVu0UnitMatrix's own argument -- with a `b merge` + `nop` as the
   fall-through. Ours emits the ordinary layout. âš  Inverting the outer test so
   `dirty = 0` moves into an `else` gives EXACTLY retail's length (191 words)
   and 101 bad words, so the region shifts; the `goto rigDone` form is
   byte-identical to the baseline.
   âš  `rig = &D_004BD9B0` assigned in a DIFFERENT basic block does stop mwcc
   folding `rig->owner` into a `%hi`/`%lo` pair (the per-block
   constant-propagation rule again), but mwcc then hoists the address
   materialisation above the `D_004BD9B4` test and the function loses three
   words. */

typedef struct Machine { u8 bytes[0x5F0]; } Machine;

typedef struct Follow {
    u8 pad00[0x4];
    void *node;        /* +0x04 */
} Follow;

typedef struct Track {
    u8 pad000[0x180];
    Vec4 pos;          /* +0x180 */
} Track;

typedef struct RigBlock {
    void *owner;       /* +0x00 */
    s32 dirty;         /* +0x04 */
    s32 locked;        /* +0x08 */
    u8 pad0c[0x4];
    Vec4 euler;        /* +0x10 */
    Vec4 offset;       /* +0x20 */
} RigBlock;

extern "C" {
extern Machine *D_00482068;   /* a POINTER in small data, not an array */
extern s32 D_004BD980[];
extern s32 D_004BD9A4;  /* const keeps it off %gp_rel */
extern s32 D_004BD9B4;
extern RigBlock D_004BD9B0;
extern void *D_00482060;
extern void *D_00481F78;
extern void *D_00482040;

extern void EvSubMachineUpdate_251980(Machine *m);
extern void EventCameraUpdate_2544f0(void *p);
extern void *ObjRecHasFlags6_1c3eb0(void *world, s32 one, s32 slot);
extern Track *ObjRecGetLiveObject_1c4a90(void *world, s32 slot);
extern Follow *ModelGetRootFrame_1511a0(Track *track);
extern void FrameGetWorldPos_148f30(void *node, Vec4 *out);
extern s32 ObjGetAttachNodePos_1adec0(Track *track, s32 one, Vec4 *out);
extern s32 SceneMapAreasCollectCollTrisMaybe_1c5090(void *world, void *list, f32 *box, s32 max);
extern s32 MeshProbeGroundHeight_26af10(Vec4 *pos, void *list, s32 count, s32 zero,
                        f32 *hitW, void *work, f32 radius);
extern void ModelSetPos_151110(Track *track, Vec4 *v);
extern void sceVu0UnitMatrix(Mtx4 *m);
extern void VecAdd_13be20(Vec4 *out, const Vec4 *a, const Vec4 *b);
extern f32 WrapAngle_13c050(f32 a);
extern void sceVu0RotMatrixY(Mtx4 *out, Mtx4 *m, f32 a);
extern void sceVu0RotMatrixX(Mtx4 *out, Mtx4 *m, f32 a);
extern void sceVu0RotMatrixZ(Mtx4 *out, Mtx4 *m, f32 a);
extern void MtxStore3x4_186390(void *owner, Mtx4 *m);
extern void EventPlayerUpdate_249a80(void *player, void *world);
extern void FileReqThreadResume_182670(void);
}

extern "C" s32 EventSysUpdate_26ac10(void)
{
    /* Declaration order sets the frame: hit at sp+0x6150 down to the matrix
       at sp+0x70, with the 0x6000-byte candidate list in between. */
    Vec4 hit __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    /* ONE box of two adjacent Vec4s, not two arrays: only the first is passed
       to SceneMapAreasCollectCollTrisMaybe_1c5090 and it reads both, so split into separate locals mwcc
       proves the second dead and drops three of the six soft-double calls. */
    Vec4 box[2] __attribute__((aligned(16)));
    u8 list[0x6000] __attribute__((aligned(16)));
    u8 work[0x60] __attribute__((aligned(16)));
    Vec4 tmp __attribute__((aligned(16)));
    Mtx4 m __attribute__((aligned(16)));
    s32 i;
    s32 j;
    Track *track;
    s32 k;
    s32 count;
    Follow *follow;
    void *node;
    /* One pointer to the rig block: retail materialises its address ONCE into
       a callee-saved register and works from offsets. */
    RigBlock *rig;

    for (i = 0; i < 0x20; i++) {
        EvSubMachineUpdate_251980(&D_00482068[i]);
    }

    if (D_004BD9A4 != 0) {
        if (D_00482060 != 0) {
            EventCameraUpdate_2544f0(D_00482060);
        }
    }

    for (j = 0; j < 0xE0; j++) {
        if ((D_004BD980[0x2A + j] & 1) == 0) {
            continue;
        }
        if (((void *)(long)(unsigned char)ObjRecHasFlags6_1c3eb0(D_00481F78, 1, j)) == 0) {
            continue;
        }
        if ((track = ObjRecGetLiveObject_1c4a90(D_00481F78, j)) == 0) {
            continue;
        }
        follow = ModelGetRootFrame_1511a0(track);
        if (follow == 0) {
            continue;
        }

        node = follow->node;
        if (node != 0) {
            FrameGetWorldPos_148f30(node, &pos);
        } else if (ObjGetAttachNodePos_1adec0(track, 1, &pos) == 0) {
            FrameGetWorldPos_148f30(follow, &pos);
        }

        /* Through pointers, not indices: retail materialises `&pos.x + k` and
           `&box[0].x + k` and writes the second corner at [4] off the same
           one, which is what puts the two Vec4s in one object. */
        for (k = 0; k < 3; k++) {
            f32 *src = &pos.x + k;
            f32 *dst = &box[0].x + k;
            f32 v = *src;

            dst[0] = (f32)(20.0 + (double)v);
            dst[4] = (f32)((double)v - 20.0);
        }
        box[0].w = 1.0f;
        box[1].w = 1.0f;

        count = SceneMapAreasCollectCollTrisMaybe_1c5090(D_00481F78, list, &box[0].x, 0x100);
        if (MeshProbeGroundHeight_26af10(&pos, list, count, 0, &hit.w, work, 20.0f) != 0) {
            tmp = track->pos;
            /* the probe hands back a HEIGHT -- it replaces Y, not W */
            tmp.y = hit.w;
            ModelSetPos_151110(track, &tmp);
        }
    }

    if (D_004BD9B4 == 1) {
        rig = (RigBlock *)((u8 *)&D_004BD9B0 + 0);
        if (rig->owner != 0) {
            switch (rig->locked) {
            case 0:
            sceVu0UnitMatrix(&m);
            VecAdd_13be20(&rig->euler, &rig->euler, &rig->offset);
            for (k = 0; k < 4; k++) {
                (&rig->euler.x)[k] = WrapAngle_13c050((&rig->euler.x)[k]);
            }
            sceVu0RotMatrixY(&m, &m, rig->euler.y);
            sceVu0RotMatrixX(&m, &m, rig->euler.x);
            sceVu0RotMatrixZ(&m, &m, rig->euler.z);
            MtxStore3x4_186390(rig->owner, &m);
            }
        } else {
            rig->dirty = 0;
        }
    }

    if (D_00482040 != 0) {
        EventPlayerUpdate_249a80(D_00482040, D_00481F78);
    }
    FileReqThreadResume_182670();
    return 1;
}
