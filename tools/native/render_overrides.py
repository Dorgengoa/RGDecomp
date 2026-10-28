#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Generate the native renderer's game overrides (docs/NATIVE-RENDER.md "Front end").

  python tools/native/render_overrides.py [--check]

Writes, from the current game/ files (their SHA-256 goes into the
`rg-override` header, so a moved snapshot makes tools/ingest.py --check fail
loudly and this script can be re-run):

  overrides/src/main/model/ModelEmitDrawPacketsMaybe_14ec20.cpp
      per mesh: nr_model_record(); a native mesh gets the 3-qword marker
      instead of DmaPktAddMscalCall (MSCAL 0x320 + CALL mesh)
  overrides/src/main/model/ModelQueueSortedPackets_14f0d0.cpp
      the sorted path: the record id travels in the node's free word (+0x28);
      the node header's view / light packets resolved at build time
      (nr_chain_packet: a copy when the memory is no longer live)
  overrides/src/main/gfx/DrawListEmitBucket_1405a0.c
      emits the marker for nodes that carry a record id
  overrides/src/main/gfx/DrawPktBuildCameraMatrix_1486c0.c
      notes the camera matrix packet per draw context (nr_note_cammtx)
  overrides/src/main/gfx/LightStateWritePacket_1484a0.c
      notes the light packet per draw context (nr_note_light)
  overrides/src/main/gfx/DrawPktBuildPlaneShadowMtx_147eb0.c
      notes the plane-shadow packet per draw context (nr_note_plane)
  overrides/src/main/gfx/DrawListFrameBegin_1425d0.c
      numbers the frames for the frame list (nr_frame_begin); RG_NR_POISON:
      poisons the frame packet stack before the reset (nr_poison_stack)
  overrides/src/main/gfx/CameraWriteViewPacket_148740.c
      notes every camera view packet by address (nr_note_view)
  overrides/src/main/gfx/DrawListResetClipRangeMaybe_148040.c
      notes the reset of the composite's screen bbox (nr_clip_reset)
  overrides/src/main/gfx/ScreenTexOverlayWriteSpriteMaybe_16a890.c
      the composite sprite natively (nr_comp_sprite) instead of MSCAL 0x960
  overrides/src/main/gs/DrawListEndPrim_141a20.c
      immediate (2D / effect) packets natively (nr_im_end_prim): the finished
      GsPkt sub-chain is decoded once and replaced by a marker

--check: exit 1 if a generated file differs from what is on disk.
"""
import hashlib, sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]

VARIANT_FN = r'''
/* ---- native renderer (docs/NATIVE-RENDER.md "Front end") ----------------
 * The microcode packets uploaded for a mesh (D_00491280 row: head, kind,
 * tail, decode by LOD, colour by k4, output by k5) name the program variant;
 * nr_model_record() decides whether the mesh is drawn natively. */
extern u8 D_00436CB0[];
extern u8 D_0043E980[];
extern u8 D_0043EA30[];
extern u8 D_0043EF20[];
extern u8 D_0043F100[];
extern u8 D_004371D0[];
extern u8 D_00438520[];
extern u8 D_00438540[];
extern u8 D_004425F0[];
extern u8 D_00441660[];
extern u8 D_00436FB0[];
extern u8 D_0043ECD0[];
u32 nr_model_record(u32 mesh_pkt, int variant);
u32 nr_model_record2(u32 mesh_pkt, int variant, const u32 *src);
void nr_marker_qwords(u32 id, u32 q[12]);
int nr_keep_original(void);
int nr_lazy_item_packets(void);

/* nr_vu1.h NRV_* */
static int nr_variant(const s32 *info)
{
    u32 b = (u32)D_00438540, d, c, o;
    int v = 0;
    if ((u32)info[0] == (u32)D_004425F0) {
        /* shadow volumes (head 0x4425F0, main piece 0x4427E0; nr_vu1sh.h):
         * decode 0x43A020 skinned, 0x4392C0 / 0x439F90 rigid */
        d = (u32)info[3] - b;
        if (d == 0x1AE0) return (1 << 8) | (1 << 0);
        if (d == 0xD80 || d == 0x1A50) return 1 << 8;           /* rigid 0x4392C0 / 0x439F90 */
        return -1;
    }
    if ((u32)info[0] == (u32)D_00441660) {
        /* line strands (head 0x441660, main piece 0x441840; nr_vu1ln.h) */
        d = (u32)info[3] - b;
        if (d == 0x1AE0) return (1 << 9) | (1 << 0);
        if (d == 0xD80 || d == 0x1A50) return 1 << 9;
        return -1;
    }
    if ((u32)info[0] == (u32)D_00436FB0) {
        /* the refraction material (VuMicrocodeTableInit row 6: kind 0x43ECD0,
         * output 0x43E380; nr_vu1.h NRV_REFRACT) */
        if ((u32)info[1] != (u32)D_0043ECD0) return -1;
        v = 1 << 10;
        d = (u32)info[3] - b;
        if (d == 0xE70) v |= 1 << 0;
        else if (d != 0xD80) return -1;
        c = (u32)info[4] - b;
        if (c == 0x2980) v |= 1 << 2;
        else if (c != 0x20E0) return -1;                       /* (lights: no constant rows left) */
        if ((u32)info[5] - b != 0x5E40) return -1;             /* 0x43E380 */
        return v;
    }
    if ((u32)info[0] != (u32)D_00436CB0) return -1;
    if ((u32)info[1] == (u32)D_0043E980) v |= 1 << 1;          /* UV scroll */
    else if ((u32)info[1] == (u32)D_0043EA30) v |= 1 << 6;     /* environment map */
    else if ((u32)info[1] == (u32)D_0043EF20) v |= 0;          /* row 7 UV waves: plain UV (qw900.z, see docs) */
    else if ((u32)info[1] == (u32)D_0043F100) v |= 1 << 12;    /* reflection map (INSECT floors) */
    else return -1;
    if ((u32)info[2] != (u32)D_004371D0 && (u32)info[2] != (u32)D_00438520) return -1;
    d = (u32)info[3] - b;
    if (d == 0xE70) v |= 1 << 0;                               /* skinned 0x4393B0 */
    else if (d != 0xD80) return -1;                            /* rigid 0x4392C0 */
    c = (u32)info[4] - b;
    if (c == 0x2980) v |= 1 << 2;                              /* vertex colour 0x43AEC0 */
    else if (c == 0x21C0 && !(v & (1 << 12))) v |= 1 << 7;     /* lights 0x43A700 (not with the reflection: constant rows) */
    else if (c == 0x2BE0 && !(v & (1 << 12))) v |= (1 << 7) | (1 << 2);   /* lights x vertex colour 0x43B120 */
    else if (c != 0x20E0) return -1;                           /* constant 0x43A620 */
    o = (u32)info[5] - b;
    switch (o) {
    case 0x3750: break;                                        /* 0x43BC90 */
    case 0x3A20: v |= 1 << 4; break;                           /* 0x43BF60 guard */
    case 0x3D70: v |= (1 << 4) | (1 << 5); break;              /* 0x43C2B0 guard + cull */
    case 0x4550: v |= 1 << 3; break;                           /* 0x43CA90 Z scale */
    case 0x4800: v |= (1 << 3) | (1 << 4); break;              /* 0x43CD40 */
    case 0x4BD0: v |= (1 << 3) | (1 << 4) | (1 << 5); break;   /* 0x43D110 */
    default: return -1;
    }
    return v;
}
'''


def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()


def gen_emit():
    rel = 'src/main/model/ModelEmitDrawPacketsMaybe_14ec20.cpp'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Front end"): a mesh whose VU1 program\n'
            ' * variant the native pipeline covers gets a draw marker instead of MSCAL 0x320 + CALL.\n'
            ' * Generated by tools/native/render_overrides.py; RG_RENDER=emu (default) emits the\n'
            ' * original packets. */\n' % (rel, sha(PORT / 'game' / rel)))
    old_decl = 'void DmaPktAddMscalCall_145b20(Ctx *, s32);\n'
    assert old_decl in src
    src = src.replace(old_decl, old_decl + 'void DmaPktPushQword_141b60(Ctx *, void *);\n'
                      's32 LightStateGetPacket_1428f0(Ctx *, s32 *);\n' + VARIANT_FN, 1)
    # the item's packets (object matrix + MSCAL 0, model info, skin) are sent
    # lazily in native mode: only before the item's first emulated mesh (they
    # hold no GS writes, and every item sends its own, so the VU state an
    # emulated mesh sees is unchanged); a native mesh needs neither them nor
    # its microcode uploads (DrawCtxAddChangedCallTags keeps tracking what VU1
    # really holds).  RG_RENDER=emu / verify: the original order.
    old = '    s32 off;\n'
    assert src.count(old) == 1
    src = src.replace(old, old + '    s32 nitem;\n', 1)
    old = ('        DmaPktAddCallTag_141b80(o, d->f14);\n'
           '        DmaPktAddCallTag_141b80(o, d->f18);\n'
           '        DmaPktAddCallTag_141b80(o, d->f1C);\n')
    assert src.count(old) == 1
    src = src.replace(old, '        nitem = 0;\n'
                      '        if (!nr_lazy_item_packets()) {\n'
                      + old.replace('        ', '            ') +
                      '            nitem = 1;\n'
                      '        }\n', 1)
    old = ('            DrawCtxAddChangedCallTags_13fd70(o, info, 6);\n'
           '            DmaPktAddCallTag_141b80(o, v);\n'
           '            DmaPktAddMscalCall_145b20(o, w);\n')
    assert src.count(old) == 1
    new = ('            {\n'
           '                u32 nsrc[8];\n'
           '                s32 nlo;\n'
           '                u32 nid;\n'
           '                u32 q[12] __attribute__((aligned(16)));\n'
           '                nsrc[0] = (u32)o;\n'
           '                nsrc[1] = *(u32 *)((u8 *)o + 0x36B0);\n'
           '                nsrc[2] = (u32)LightStateGetPacket_1428f0(o, &nlo);\n'
           '                nsrc[3] = (u32)d->f14;\n'
           '                nsrc[4] = (u32)d->f18;\n'
           '                nsrc[5] = (u32)d->f1C;\n'
           '                nsrc[6] = (u32)v;\n'
           '                nsrc[7] = (u32)info;\n'
           '                nid = nr_model_record2((u32)w, nr_variant(info), nsrc);\n'
           '                if (nid != 0 && !nr_keep_original()) {\n'
           '                    DmaPktAddCallTag_141b80(o, v);\n'
           '                    nr_marker_qwords(nid, q);\n'
           '                    DmaPktPushQword_141b60(o, q);\n'
           '                    DmaPktPushQword_141b60(o, q + 4);\n'
           '                    DmaPktPushQword_141b60(o, q + 8);\n'
           '                } else {\n'
           '                    if (!nitem) {\n'
           '                        DmaPktAddCallTag_141b80(o, d->f14);\n'
           '                        DmaPktAddCallTag_141b80(o, d->f18);\n'
           '                        DmaPktAddCallTag_141b80(o, d->f1C);\n'
           '                        nitem = 1;\n'
           '                    }\n'
           '                    DrawCtxAddChangedCallTags_13fd70(o, info, 6);\n'
           '                    DmaPktAddCallTag_141b80(o, v);\n'
           '                    if (nid != 0) {\n'
           '                        nr_marker_qwords(nid, q);\n'
           '                        DmaPktPushQword_141b60(o, q);\n'
           '                        DmaPktPushQword_141b60(o, q + 4);\n'
           '                        DmaPktPushQword_141b60(o, q + 8);\n'
           '                    }\n'
           '                    DmaPktAddMscalCall_145b20(o, w);\n'
           '                }\n'
           '            }\n')
    src = src.replace(old, new, 1)
    return rel, head + src


def gen_sorted():
    rel = 'src/main/model/ModelQueueSortedPackets_14f0d0.cpp'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Front end"): the sorted path records\n'
            ' * natively drawn meshes; the record id rides in the node\'s free word (Rec.pad[1], node\n'
            ' * +0x28) and DrawListEmitBucket_1405a0 (override) emits the marker for it; the node\n'
            ' * header\'s view / light packets are resolved at build time (nr_chain_packet).\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    anchor = 'extern Row D_00491280[];\n'
    assert anchor in src
    src = src.replace(anchor, anchor + VARIANT_FN, 1)
    # the node header's view / light packets: DrawListEmitBucket CALLs them, so a stale mark
    # (the context's +0x36B0 view, the light record's +4) is resolved here like the records
    # resolve it (docs/NATIVE-RENDER.md "Remembered packets"); live = unchanged
    old = '        rec.hdr[4] = d->f1C;\n'
    assert src.count(old) == 1
    src = src.replace(old, old + '        {\n'
                      '            u32 nq;\n'
                      '            rec.hdr[0] = (s32)nr_chain_packet((u32)o, 0, (u32)r100, (u32)cur, &nq);\n'
                      '            cur += nq;\n'
                      '            rec.hdr[1] = (s32)nr_chain_packet((u32)o, 1, (u32)r110, (u32)cur, &nq);\n'
                      '            cur += nq;\n'
                      '        }\n', 1)
    old = 'u32 nr_model_record2(u32 mesh_pkt, int variant, const u32 *src);\n'
    assert src.count(old) == 1
    src = src.replace(old, old + 'u32 nr_chain_packet(u32 ctx, int kind, u32 pkt, u32 dst, u32 *qw);\n', 1)
    old = '            rec.w = w;\n'
    assert src.count(old) == 1
    src = src.replace(old, old + '            {\n'
                      '                u32 nsrc[8];\n'
                      '                nsrc[0] = (u32)o;\n'
                      '                nsrc[1] = (u32)r100;\n'
                      '                nsrc[2] = (u32)r110;\n'
                      '                nsrc[3] = (u32)d->f14;\n'
                      '                nsrc[4] = (u32)d->f18;\n'
                      '                nsrc[5] = (u32)d->f1C;\n'
                      '                nsrc[6] = (u32)v;\n'
                      '                nsrc[7] = (u32)q;\n'
                      '                rec.pad[1] = (s32)nr_model_record2((u32)w, nr_variant(q), nsrc);\n'
                      '            }\n', 1)
    return rel, head + src


def gen_bucket():
    rel = 'src/main/gfx/DrawListEmitBucket_1405a0.c'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Front end"): a node whose word +0x28\n'
            ' * holds a native record id (ModelQueueSortedPackets_14f0d0 override) gets the draw\n'
            ' * marker instead of CALL (RET + MSCAL 0x320) + CALL mesh.\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    old_ent = '    s32 a20;        /* 0x20 */\n} Ent;\n'
    assert old_ent in src
    src = src.replace(old_ent, '    s32 a20;        /* 0x20 */\n    s32 link24;     /* 0x24: bucket list (DrawListAddNode) */\n'
                      '    s32 nr28;       /* 0x28: native record id or 0 (native renderer) */\n} Ent;\n'
                      '\nvoid nr_marker_qwords(u32 id, u32 q[12]);\nint nr_keep_original(void);\nint nr_lazy_item_packets(void);\n', 1)
    # native mode: a native node needs only the view and light packets (slots
    # 0, 1) besides its texture packet; the item's packets (slots 2-4) and the
    # microcode uploads are skipped.  "Changed" is then judged against what
    # was last emitted per slot (= the previous node's when all are emulated).
    src = src.replace('    s32 j;\n', '    s32 j;\n    s32 nem;\n    s32 nem_src[8];\n    s32 nemv[8];\n', 1)
    src = src.replace('    prev = 0;\n', '    prev = 0;\n    nem = -1;\n', 1)
    old_hdr = ('        if (prev == 0 || n != prev->n) {\n'
               '            for (j = 0; j < n; j++) {\n'
               '                EMIT(o, *src);\n'
               '                src++;\n'
               '            }\n'
               '        } else {\n'
               '            psrc = prev->src;\n'
               '            if (psrc != src) {\n'
               '                for (j = 0; j < n; j++, src++, psrc++) {\n'
               '                    if (*src != *psrc) {\n'
               '                        EMIT(o, *src);\n'
               '                    }\n'
               '                }\n'
               '            }\n'
               '        }\n'
               '        DrawCtxAddChangedCallTags_13fd70(o, e->a18, e->a14);\n')
    assert src.count(old_hdr) == 1
    new_hdr = ('        if (nr_lazy_item_packets()) {\n'
               '            if (n != nem) {\n'
               '                nem = n;\n'
               '                for (j = 0; j < 8; j++) nemv[j] = 0;\n'
               '            }\n'
               '            for (j = 0; j < n; j++, src++) {\n'
               '                if (e->nr28 != 0 && j >= 2) continue;\n'
               '                if (j >= 8 || !nemv[j] || nem_src[j] != *src) {\n'
               '                    EMIT(o, *src);\n'
               '                    if (j < 8) { nem_src[j] = *src; nemv[j] = 1; }\n'
               '                }\n'
               '            }\n'
               '            if (e->nr28 == 0) DrawCtxAddChangedCallTags_13fd70(o, e->a18, e->a14);\n'
               '        } else {\n'
               + ''.join('    ' + l + '\n' for l in old_hdr.rstrip('\n').split('\n')) +
               '        }\n')
    src = src.replace(old_hdr, new_hdr, 1)
    old = ('        *(u128 *)o->cur = D_0047DE40;\n'
           '        ((u32 *)o->cur)[1] = ha;\n'
           '        o->cur += 0x10;\n'
           '        EMIT(o, (*pp)->a20);\n')
    assert src.count(old) == 1
    new = ('        if ((*pp)->nr28 != 0) {\n'
           '            u32 q[12] __attribute__((aligned(16)));\n'
           '            nr_marker_qwords((u32)(*pp)->nr28, q);\n'
           '            *(u128 *)o->cur = *(u128 *)q; o->cur += 0x10;\n'
           '            *(u128 *)o->cur = *(u128 *)(q + 4); o->cur += 0x10;\n'
           '            *(u128 *)o->cur = *(u128 *)(q + 8); o->cur += 0x10;\n'
           '        }\n'
           '        if ((*pp)->nr28 == 0 || nr_keep_original()) {\n'
           + old.replace('        ', '            ') +
           '        }\n')
    src = src.replace(old, new, 1)
    return rel, head + src


def gen_cammtx():
    rel = 'src/main/gfx/DrawPktBuildCameraMatrix_1486c0.c'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Constants from the game"): the camera\n'
            ' * matrix packet (VU qw 24-28) a draw context built last is noted for the records\n'
            ' * (nr_note_cammtx); the packet itself is unchanged.\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    anchor = 'typedef rg_u128 u128;\n'
    assert anchor in src
    src = src.replace(anchor, anchor + '\nvoid nr_note_cammtx(u32 ctx, u32 pkt);\n', 1)
    old = '    return 6;\n}'
    assert src.count(old) == 1
    src = src.replace(old, '    nr_note_cammtx((u32)p0, (u32)p1);\n' + old, 1)
    return rel, head + src


def gen_light():
    rel = 'src/main/gfx/LightStateWritePacket_1484a0.c'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Constants from the game"): the light\n'
            ' * packet (VU qw 30-51) a draw context wrote last is noted for records whose draw\n'
            ' * request carries no light packet (nr_note_light); the packet itself is unchanged.\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    anchor = '#include "vec.h"\n'
    assert anchor in src
    src = src.replace(anchor, anchor + '\nvoid nr_note_light(u32 ctx, u32 pkt);\n', 1)
    old = '    return n;\n}'
    assert src.count(old) == 1
    src = src.replace(old, '    nr_note_light((u32)o, (u32)pkt);\n' + old, 1)
    return rel, head + src


def gen_plane():
    rel = 'src/main/gfx/DrawPktBuildPlaneShadowMtx_147eb0.c'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Shadow volumes"): the plane-shadow\n'
            ' * packet (VU qw 30-40: plane projection, light direction, the two register packets)\n'
            ' * a draw context built last is noted for the shadow-volume records (nr_note_plane);\n'
            ' * the packet itself is unchanged.\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    anchor = 'typedef rg_u128 u128;\n'
    assert anchor in src
    src = src.replace(anchor, anchor + '\nvoid nr_note_plane(u32 ctx, u32 pkt);\n', 1)
    old = '    return n;\n}'
    assert src.count(old) == 1
    src = src.replace(old, '    nr_note_plane((u32)arg0, (u32)arg1);\n' + old, 1)
    return rel, head + src


def gen_framebegin():
    rel = 'src/main/gfx/DrawListFrameBegin_1425d0.c'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Frame list"): a draw context\n'
            ' * starting a frame numbers the frame for the native records (nr_frame_begin);\n'
            ' * RG_NR_POISON poisons the frame packet stack before the reset (nr_poison_stack,\n'
            ' * diagnostic); the function is otherwise unchanged.\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    anchor = 'typedef rg_u128 u128;\n'
    assert anchor in src
    src = src.replace(anchor, anchor + '\nvoid nr_frame_begin(u32 ctx);\nvoid nr_poison_stack(u32 base, u32 qwords);\n', 1)
    old = '    a->m0F18 = 1;\n'
    assert src.count(old) == 1
    src = src.replace(old, old + '    nr_frame_begin((u32)a);\n', 1)
    old = '    MemStackReset_14d830(el->m08);\n'
    assert src.count(old) == 1
    src = src.replace(old, '    nr_poison_stack(*(u32 *)(el->m08 + 0x28), *(u32 *)(el->m08 + 0x2C));\n' + old, 1)
    return rel, head + src


def gen_view():
    rel = 'src/main/gfx/CameraWriteViewPacket_148740.c'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Remembered packets"): every camera view\n'
            ' * packet (VU qw 0-19) is noted by address (nr_note_view), so a draw request naming it\n'
            ' * later applies the copy, not memory the game may have reused; the packet is unchanged.\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    anchor = 'typedef rg_u128 u128;\n'
    assert src.count(anchor) == 1
    src = src.replace(anchor, anchor + '\nvoid nr_note_view(u32 ctx, u32 pkt);\n', 1)
    old = '    return 0x15;\n}'
    assert src.count(old) == 1
    src = src.replace(old, '    nr_note_view((u32)o, (u32)pkt);\n' + old, 1)
    return rel, head + src


def gen_clipreset():
    rel = 'src/main/gfx/DrawListResetClipRangeMaybe_148040.c'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Offscreen composite"): the reset of the\n'
            ' * screen bbox (VU qw98/99) the Z-scale meshes accumulate is noted (nr_clip_reset), so\n'
            ' * the composite sprites can be built without VU1; the packet itself is unchanged.\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    anchor = 'typedef rg_u128 u128;\n'
    assert anchor in src
    src = src.replace(anchor, anchor + '\nvoid nr_clip_reset(u32 ctx);\n', 1)
    old = '            DmaPktAddCallTag_141b80(arg0, temp_16);\n'
    assert src.count(old) == 1
    src = src.replace(old, old + '            nr_clip_reset((u32)arg0);\n', 1)
    return rel, head + src


SPRITE_WRAP = r'''
/* ---- native renderer (docs/NATIVE-RENDER.md "Offscreen composite") -------
 * The composite sprite without VU1: the floats the original uploads to VU
 * qw140-143 (z/w lanes: the words its packet buffer holds there, which the
 * original leaves as they are) go to nr_comp_sprite, which writes the GIF
 * packet the VU program 0x445C60 would kick (DMA CNT + VIF DIRECT) while the
 * screen bbox is known on the EE; otherwise the original packet. */
int nr_comp_sprite(u32 ctx, const f32 *r, u32 *dst, int cap_qw);
void ScreenTexOverlayWriteSpriteMaybe_16a890(s32 arg0, s32 *arg1, s32 *arg2)
{
    s32 sess = GetDrawCtx_15de80();
    s32 dxW = DrawEnvGetCenterX_145130(sess) * 16;
    s32 dxH = DrawEnvGetCenterY_145120(sess) * 16;
    s32 dyW = -dxW + DrawEnvGetWidth_1451e0(sess) * 8;
    s32 dyH = -dxH + DrawEnvGetHeight_1451d0(sess) * 8;
    u32 *pk = (u32 *)GsPktReserveQwords_13f230(arg0, 0);
    f32 r[16];
    s32 n;
    r[0] = (f32)(arg1[1] + dxW) / 16.0f; r[1] = (f32)(arg1[0] + dxH) / 16.0f; r[2] = F(pk, 6); r[3] = F(pk, 7);
    r[4] = (f32)(arg1[3] + dxW) / 16.0f; r[5] = (f32)(arg1[2] + dxH) / 16.0f; r[6] = F(pk, 10); r[7] = F(pk, 11);
    r[8] = (f32)dyW / 16.0f; r[9] = (f32)dyH / 16.0f; r[10] = F(pk, 14); r[11] = F(pk, 15);
    r[12] = (f32)arg2[0] / 16.0f; r[13] = (f32)arg2[1] / 16.0f; r[14] = F(pk, 18); r[15] = F(pk, 19);
    n = nr_comp_sprite((u32)sess, r, pk, 160);
    if (n >= 0) {
        if (n) GsPktReserveQwords_13f230(arg0, n);
        return;
    }
    nr_orig_ScreenTexOverlayWriteSprite_16a890(arg0, arg1, arg2);
}
'''


def gen_sprite():
    rel = 'src/main/gfx/ScreenTexOverlayWriteSpriteMaybe_16a890.c'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Offscreen composite"): the composite\n'
            ' * sprite is built by the semantics of its VU1 program (nr_comp_sprite) and sent as a GIF\n'
            ' * packet when the screen bbox it clips to is known on the EE; else the original MSCAL.\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    old = 'void ScreenTexOverlayWriteSpriteMaybe_16a890(s32 arg0, s32 *arg1, s32 *arg2)\n'
    assert src.count(old) == 1
    src = src.replace(old, 'static void nr_orig_ScreenTexOverlayWriteSprite_16a890(s32 arg0, s32 *arg1, s32 *arg2)\n', 1)
    return rel, head + src + SPRITE_WRAP


def gen_endprim():
    rel = 'src/main/gs/DrawListEndPrim_141a20.c'
    src = (PORT / 'game' / rel).read_text()
    head = ('/* rg-override: replaces game/%s sha256 %s\n'
            ' * why: native renderer (docs/NATIVE-RENDER.md "Immediate packets"): the finished GsPkt\n'
            ' * sub-chain (2D, HUD, fonts, menus, effect passes) is decoded once on the EE and replaced\n'
            ' * by a marker the GS thread runs natively (nr_im_end_prim); the CALL to it is unchanged.\n'
            ' * Generated by tools/native/render_overrides.py. */\n' % (rel, sha(PORT / 'game' / rel)))
    anchor = 'extern const u128 D_0047DE40 __attribute__((section(".sdata")));\n'
    assert src.count(anchor) == 1
    src = src.replace(anchor, anchor + '\nint nr_im_end_prim(u32 pkt);\n', 1)
    old = '    if (t != 0) {\n'
    assert src.count(old) == 1
    src = src.replace(old, old + '        nr_im_end_prim((u32)t);\n', 1)
    return rel, head + src


def main():
    check = '--check' in sys.argv
    bad = 0
    for rel, text in (gen_emit(), gen_sorted(), gen_bucket(), gen_cammtx(), gen_light(), gen_plane(), gen_framebegin(),
                      gen_view(), gen_clipreset(), gen_sprite(), gen_endprim()):
        out = PORT / 'overrides' / rel
        if check:
            if not out.exists() or out.read_text() != text:
                print('DIFFERS', out)
                bad = 1
        else:
            out.parent.mkdir(parents=True, exist_ok=True)
            out.write_text(text, newline='\n')
            print('wrote', out)
    return bad


if __name__ == '__main__':
    sys.exit(main())
