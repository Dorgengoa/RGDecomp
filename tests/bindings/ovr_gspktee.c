/* Bindings test for the gspktee lane: Level-5's GS packet builder (MAIN
 * 0x13E520..0x140000, linked in the SDK address band) and a few small
 * game-scope asm functions, ported as overrides.  Self-contained functions
 * only (no calls out to other game functions), checked against hand-computed
 * values.  This file is derived from the game's behaviour and, like
 * overrides/, is not covered by the repository's CC0 dedication. */
#include "types.h"
#include "bt.h"

extern void GsPktWriteAD_13ec80(void *pkt, s32 reg, u64 data);
extern void GsPktSetRGBAQ_13ee40(void *pkt, s32 r, s32 g, s32 b, s32 a);
extern void GsPktSetRGBAQVec_13edd0(void *pkt, const f32 *rgba);
extern void GsPktSetUV_13ed60(void *pkt, s32 u, s32 v);
extern void GsPktSetXYZPixel_13f110(void *pkt, s32 x, s32 y, s32 z);
extern void GsPktSetXYZf_13f060(void *pkt, f32 x, f32 y, f32 z);
extern void GsPktOpenGifTag_13f3b0(void *pkt, s32 prim, s32 regs_lo, s32 regs_hi, s32 nreg);
extern void GsPktBeginPrimAD_13f6b0(void *pkt);
extern void GsPktFinalizeTags_13f260(void *pkt);
extern void *DListNodeAdvance_42eb00(void *list, s32 n);
extern s32 MotionListIsFinished_171d90(void *list, s32 id);
extern void *MotionListFindSubEntry_172430(void *list, s32 id, s32 id2);
extern s32 EventVoicePendingPop_24e6b0(void *self);
extern s32 CharaTableEntryGetWaitFrameParam_2260c0(void *o, s32 n);
extern void MesWinAddCharY_274d10(void *base, s32 idx, s16 delta);
extern void MotionPlayerGetBlendMaybe_172ce0(void *player, void *out);
extern void *SurfaceParamFindByTriAttr_23a2b0(void *table, void *tri);
extern void VecCopy_1cbe30(void *dst, const void *src);

#define W32(b, o) (*(s32 *)((u8 *)(b) + (o)))
#define U32(b, o) (*(u32 *)((u8 *)(b) + (o)))
#define U64(b, o) (*(u64 *)((u8 *)(b) + (o)))
#define PTR(b, o) (*(u8 **)((u8 *)(b) + (o)))
#define F32(b, o) (*(f32 *)((u8 *)(b) + (o)))

static u8 g_pkt[0x140] __attribute__((aligned(16)));
static u8 g_buf[0x200] __attribute__((aligned(16)));

static void pkt_reset(void)
{
    __builtin_memset(g_pkt, 0, sizeof(g_pkt));
    __builtin_memset(g_buf, 0xCC, sizeof(g_buf));
    PTR(g_pkt, 0xF4) = g_buf;
}

int bt_ovr_gspktee(void)
{
    int fails = 0;

    /* 1. RGBAQ: (0x10,0x20,0x30,0x40), Q = 1.0f -> 0x3F800000_40302010, reg 1 */
    pkt_reset();
    U32(g_pkt, 0x110) = 0x3F800000u;
    GsPktSetRGBAQ_13ee40(g_pkt, 0x10, 0x20, 0x30, 0x40);
    BT_EQ(fails, U64(g_buf, 0x0), 0x3F80000040302010ull);
    BT_EQ(fails, U64(g_buf, 0x8), BT_WRONG(1));
    BT_EQ(fails, PTR(g_pkt, 0xF4) - g_buf, 0x10);

    /* 2. UV from texels (3, 5): 12.4 -> u 0x30, v 0x50 << 16; reg 3 */
    GsPktSetUV_13ed60(g_pkt, 3, 5);
    BT_EQ(fails, U64(g_buf, 0x10), 0x00500030ull);
    BT_EQ(fails, U64(g_buf, 0x18), 3);

    /* 3. XYZ2 from pixels (10, 20, z 7), origin (0x6C00, 0x7000):
          x = 160 + 0x6C00 = 0x6CA0, y = 320 + 0x7000 = 0x7140 */
    W32(g_pkt, 0x120) = 0x6C00;
    W32(g_pkt, 0x124) = 0x7000;
    GsPktSetXYZPixel_13f110(g_pkt, 10, 20, 7);
    BT_EQ(fails, U64(g_buf, 0x20), 0x0000000771406CA0ull);
    BT_EQ(fails, U64(g_buf, 0x28), 5);

    /* 4. XYZ2 from floats through VU0: vftoi4 1.5 -> 24, 2.25 -> 36,
          vftoi0 100.7 -> 100 (truncation) */
    W32(g_pkt, 0x120) = 0;
    W32(g_pkt, 0x124) = 0;
    GsPktSetXYZf_13f060(g_pkt, 1.5f, 2.25f, 100.7f);
    BT_EQ(fails, U64(g_buf, 0x30), 0x0000006400240018ull);
    /* negative x: -1.03125 * 16 = -16.5 -> -16 (toward zero); the X field is
       sign-extended to 64 bits before the OR, so it floods bits 63:16 */
    GsPktSetXYZf_13f060(g_pkt, -1.03125f, 0.0f, 0.0f);
    BT_EQ(fails, U64(g_buf, 0x40), 0xFFFFFFFFFFFFFFF0ull);

    /* 5. RGBAQ from a float vector: vftoi0 (128.9, 64, 0.5, 255.99) ->
          (128, 64, 0, 255); Q bits 0x3F000000 (0.5f) from +0x110 */
    {
        f32 c[4] __attribute__((aligned(16))) = { 128.9f, 64.0f, 0.5f, 255.99f };
        U32(g_pkt, 0x110) = 0x3F000000u;
        GsPktSetRGBAQVec_13edd0(g_pkt, c);
        BT_EQ(fails, U64(g_buf, 0x50), 0x3F000000FF004080ull);
        BT_EQ(fails, U64(g_buf, 0x58), 1);
    }

    /* 6. OpenGifTag + 3 A+D qwords + FinalizeTags:
          prim word 0x156 -> PRIM bits 0x156 << 15 = 0xAB0000;
          tag hi = 3 << 28 | 0xAB0000 | 0x4000 (PRE) = 0x30AB4000;
          after 3 data qwords (cursor = buf + 0x50): DMA QWC 4, VIF 4,
          NLOOP = (0x40/16 - 1) / NREG 3 = 1 */
    pkt_reset();
    U64(g_pkt, 0x70) = 0x150;
    GsPktOpenGifTag_13f3b0(g_pkt, 6, 0x441, 0, 3);
    BT_EQ(fails, g_pkt[0x70], 0x56);
    BT_EQ(fails, U32(g_buf, 0x14), 0x30AB4000u);
    BT_EQ(fails, U32(g_buf, 0x18), 0x441);
    BT_EQ(fails, PTR(g_pkt, 0xF4) - g_buf, 0x20);
    GsPktWriteAD_13ec80(g_pkt, 0x3F, 0);
    GsPktWriteAD_13ec80(g_pkt, 0x3F, 0);
    GsPktWriteAD_13ec80(g_pkt, -2, 0x123456789ull);
    BT_EQ(fails, U64(g_buf, 0x40), 0x123456789ull);
    BT_EQ(fails, U64(g_buf, 0x48), 0xFFFFFFFFFFFFFFFEull); /* sd of a sign-extended id */
    GsPktFinalizeTags_13f260(g_pkt);
    BT_EQ(fails, U32(g_buf, 0x0), 0x10000004u);
    BT_EQ(fails, U32(g_buf, 0xC), 0x50000004u);
    BT_EQ(fails, U32(g_buf, 0x10), 0x8001u);

    /* 7. BeginPrimAD: tag qword, A+D GIF tag, PRIM qword from +0x70; finalize
          with +0x114 = 0: DMA 2, VIF 2, NLOOP (0x20/16 - 1) = 1 | 0x8000 */
    pkt_reset();
    U64(g_pkt, 0x70) = 0x0000000000000156ull;
    GsPktBeginPrimAD_13f6b0(g_pkt);
    BT_EQ(fails, PTR(g_pkt, 0xF4) - g_buf, 0x30);
    BT_EQ(fails, U32(g_buf, 0x14), 0x10000000u);
    BT_EQ(fails, U32(g_buf, 0x18), 0xE);
    BT_EQ(fails, U64(g_buf, 0x20), 0x156);
    BT_EQ(fails, U64(g_buf, 0x28), 0);
    GsPktFinalizeTags_13f260(g_pkt);
    BT_EQ(fails, U32(g_buf, 0x0), 0x10000002u);
    BT_EQ(fails, U32(g_buf, 0xC), 0x50000002u);
    BT_EQ(fails, U32(g_buf, 0x10), 0x8001u);
    /* only the tag qword since +0xF8 (DMA count 0): rewind the cursor to +0xF8 */
    PTR(g_pkt, 0xF8) = g_buf + 0x30;
    PTR(g_pkt, 0xFC) = g_buf + 0x30;
    PTR(g_pkt, 0x100) = g_buf + 0x30;
    PTR(g_pkt, 0xF4) = g_buf + 0x40;
    GsPktFinalizeTags_13f260(g_pkt);
    BT_EQ(fails, PTR(g_pkt, 0xF4) - g_buf, 0x30);

    /* 8. DListNodeAdvance: a -> b -> c via +0x4 */
    {
        u8 a[8], b[8], c[8];
        PTR(a, 4) = b; PTR(b, 4) = c; PTR(c, 4) = 0;
        BT_EQ(fails, (u8 *)DListNodeAdvance_42eb00(a, 2) == c, 1);
        BT_EQ(fails, (u8 *)DListNodeAdvance_42eb00(a, 0) == a, 1);
        BT_EQ(fails, DListNodeAdvance_42eb00(a, 5) == 0, 1);
        BT_EQ(fails, DListNodeAdvance_42eb00(0, 3) == 0, 1);
    }

    /* 9. motion list: list +4 -> n1 (id 3) -> n2 (id 9); entry = node + 0x10;
          state at entry +0x24; sub-list head at entry +0x48 */
    {
        u8 list[8], n1[0x80], n2[0x80], s1[0x20], s2[0x20];
        __builtin_memset(n1, 0, sizeof(n1));
        __builtin_memset(n2, 0, sizeof(n2));
        __builtin_memset(s1, 0, sizeof(s1));
        __builtin_memset(s2, 0, sizeof(s2));
        PTR(list, 4) = n1;
        PTR(n1, 0) = n2; W32(n1, 0xC) = 3; W32(n1, 0x10 + 0x24) = 4;
        PTR(n2, 0) = 0;  W32(n2, 0xC) = 9; W32(n2, 0x10 + 0x24) = 2;
        PTR(n2, 0x10 + 0x48) = s1;
        PTR(s1, 0) = s2; W32(s1, 0xC) = 100;
        PTR(s2, 0) = 0;  W32(s2, 0xC) = 200;
        BT_EQ(fails, MotionListIsFinished_171d90(list, 3), 1);
        BT_EQ(fails, MotionListIsFinished_171d90(list, -1), 1); /* -1 = first */
        BT_EQ(fails, MotionListIsFinished_171d90(list, 9), 0);
        BT_EQ(fails, MotionListIsFinished_171d90(list, 7), 0);
        BT_EQ(fails, (u8 *)MotionListFindSubEntry_172430(list, 9, 200) == s2 + 0x10, 1);
        BT_EQ(fails, MotionListFindSubEntry_172430(list, 9, 300) == 0, 1);
        BT_EQ(fails, MotionListFindSubEntry_172430(list, 3, 100) == 0, 1); /* empty sub-list */
    }

    /* 10. EventVoicePendingPop: queue [7, 8, 9] -> 7, [8, 9, -1], count 2 */
    {
        u8 q[0x48];
        __builtin_memset(q, 0, sizeof(q));
        W32(q, 0x44) = 3;
        W32(q, 0x24) = 7; W32(q, 0x28) = 8; W32(q, 0x2C) = 9;
        BT_EQ(fails, EventVoicePendingPop_24e6b0(q), 7);
        BT_EQ(fails, W32(q, 0x44), 2);
        BT_EQ(fails, W32(q, 0x24), 8);
        BT_EQ(fails, W32(q, 0x28), 9);
        BT_EQ(fails, W32(q, 0x2C), -1);
        W32(q, 0x44) = 0;
        BT_EQ(fails, EventVoicePendingPop_24e6b0(q), -1);
    }

    /* 11. CharaTableEntryGetWaitFrameParam: +0x3C + n*4, n in 0..1 */
    {
        u8 e[0x48];
        W32(e, 0x3C) = 11; W32(e, 0x40) = 22;
        BT_EQ(fails, CharaTableEntryGetWaitFrameParam_2260c0(e, 1), 22);
        BT_EQ(fails, CharaTableEntryGetWaitFrameParam_2260c0(e, 2), 0);
        BT_EQ(fails, CharaTableEntryGetWaitFrameParam_2260c0(e, -1), 0);
    }

    /* 12. MesWinAddCharY: s16 at +0xC8 + idx*8 */
    {
        u8 w[0x100];
        __builtin_memset(w, 0, sizeof(w));
        *(s16 *)(w + 0xC8 + 16) = 100;
        MesWinAddCharY_274d10(w, 2, -5);
        BT_EQ(fails, *(s16 *)(w + 0xC8 + 16), 95);
        MesWinAddCharY_274d10(w, 0x300, 1); /* out of range: no write */
        MesWinAddCharY_274d10(w, -1, 1);
        BT_EQ(fails, *(s16 *)(w + 0xC8), 0);
    }

    /* 13. MotionPlayerGetBlendMaybe: blend 0.25 -> 1 - 0.75^2 = 0.4375;
           node A key 1 of 2 (48-byte keys, +0x24) = 0.25, frame 1.5 -> 1.75 */
    {
        u8 p[0x40], out[0x18], na[0x20];
        u8 keys[96];
        __builtin_memset(p, 0, sizeof(p));
        __builtin_memset(out, 0xEE, sizeof(out));
        __builtin_memset(na, 0, sizeof(na));
        W32(p, 0x28) = 77;
        F32(p, 0x34) = 0.25f;
        PTR(p, 0xC) = na;
        W32(p, 0x14) = 1;
        F32(p, 0x18) = 1.5f;
        PTR(p, 0x10) = 0;
        PTR(na, 0x18) = keys;
        W32(na, 0x14) = 2;
        F32(keys, 48 + 0x24) = 0.25f;
        MotionPlayerGetBlendMaybe_172ce0(p, out);
        BT_EQ(fails, W32(out, 0x0), 77);
        BT_FBITS(fails, F32(out, 0x4), 0.4375f);
        BT_EQ(fails, PTR(out, 0x8) == na + 0x10, 1);
        BT_FBITS(fails, F32(out, 0xC), 1.75f);
        BT_EQ(fails, PTR(out, 0x10) == 0, 1);
        BT_EQ(fails, U32(out, 0x14), 0xEEEEEEEEu); /* untouched without node B */
    }

    /* 14. SurfaceParamFindByTriAttr: keys 3, 5, then terminator -1 */
    {
        u8 tab[0x30], tri[0x44];
        W32(tab, 0x00) = 3; W32(tab, 0x10) = 5; W32(tab, 0x20) = -1;
        *(s16 *)(tri + 0x42) = 5;
        BT_EQ(fails, (u8 *)SurfaceParamFindByTriAttr_23a2b0(tab, tri) == tab + 0x10, 1);
        *(s16 *)(tri + 0x42) = 4; /* miss: the terminator record (retail quirk) */
        BT_EQ(fails, (u8 *)SurfaceParamFindByTriAttr_23a2b0(tab, tri) == tab + 0x20, 1);
        *(s16 *)(tri + 0x42) = -2;
        BT_EQ(fails, SurfaceParamFindByTriAttr_23a2b0(tab, tri) == 0, 1);
        BT_EQ(fails, SurfaceParamFindByTriAttr_23a2b0(tab, 0) == 0, 1);
    }

    /* 15. VecCopy: 16 bytes */
    {
        u32 s[4] __attribute__((aligned(16))) = { 1, 2, 3, 0xDEADBEEF };
        u32 d[4] __attribute__((aligned(16))) = { 0, 0, 0, 0 };
        VecCopy_1cbe30(d, s);
        BT_EQ(fails, d[3], 0xDEADBEEFu);
        BT_EQ(fails, d[0] + d[1] + d[2], 6);
    }

    return fails;
}
