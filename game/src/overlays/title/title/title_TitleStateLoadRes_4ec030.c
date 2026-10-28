/* rgp:protos */
#define RGP_SELF_title_TitleStateLoadRes_4ec030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EC030 -- load the title screen's archives and hand
 * the decoded pieces to the three display objects.
 *
 * Reads either a single archive (when func_207F20() reports the alternate
 * path) or two from the gp table at D_004803C0, then builds the two sprite
 * objects and the model object from func_42C500/func_42C040 records.
 *
 * D_004803C0 is declared `[2]` deliberately: at 8 bytes it is under mwcc's
 * small-data threshold and takes `addiu $2, $28, %gp_rel(...)`, which is what
 * the reference has.  Sized [4] it would be 16 bytes, over the threshold, and
 * compile to `lui`/`%lo`.  The declared size is a RELOCATION CONTROL here, not
 * a bound.
 *
 * ⚠ func_207F20 takes NO arguments.  m2c gives it two at 0x004EC4F4 because
 * $4 and $5 still hold the preceding bitfield insert's operands.
 *
 * The `bgez / sra 4 / addiu 0xF / sra 4` block is just a signed divide by 16;
 * writing it out longhand as m2c does is the same code.
 *
 * THREE THINGS MOVED THIS FROM `len` TO BYTE-IDENTICAL, in order of value:
 *  1. The 14-bit field at +0xA has to be read into a LOCAL before the call it
 *     precedes.  Left inline in the argument list mwcc computes the
 *     `lhu / dsll32 / dsrl32` triple AFTER the call; retail computes it before
 *     and holds it in a callee-saved register.  Worth 6 words across the three
 *     identical blocks.
 *  2. `dev` must be assigned AFTER `func_207DF0()`, not before.  Assigned
 *     first its live range crosses the call, so it needs a callee-saved
 *     register and the later field writes go through that; retail re-loads the
 *     global into `$5` after the call and never keeps it across one.  Write
 *     `t = func_207DF0(); dev = D_0048415C; dev->field018 = t;`.
 *     ⚠ `volatile` on the extern does NOT do this -- the value was never CSE'd
 *     across a call, it was simply live too early.
 *  3. ★ THAT REORDER THEN COSTS 40 WORDS OF PURE REGISTER NAMING, and the fix
 *     is the DECLARATION ORDER of the pointer locals.  Once `dev` stops
 *     needing a callee-saved register the whole pool shifts one place; the
 *     pointers are handed $19, $18, $17, $16 in DECLARATION order, so `buf`
 *     has to be declared first to land in $19.  Moving `dev`'s own
 *     declaration does nothing -- it is the surviving callee-saved locals'
 *     order that matters.
 */

typedef struct Rec_title_FUN_004ec030 {
    u8 pad000[0x4];
    s32 field004;
    u8 pad008[0x2];
    __extension__ unsigned short bits00A_0 : 2;
    unsigned short field00A : 14;             /* (v << 48) >>> 50 == bits 2..15 */
} __attribute__((aligned(2))) Rec_title_FUN_004ec030;

typedef struct Wk_title_FUN_004ec030 {
    u8 pad000[0x8];
    s32 field008;
} Wk_title_FUN_004ec030;

typedef struct Dev_title_FUN_004ec030 {
    u8 pad000[0x18];
    s32 field018;
    u8 pad01C[0x4];
    u8 bit020 : 1;
    u8 field021;
} Dev_title_FUN_004ec030;

typedef struct Blk_title_FUN_004ec030 {
    u8 pad000[0x7C];
} Blk_title_FUN_004ec030;

extern s32 D_004802CC;
extern s32 D_004803A0;
extern u8 D_004803A4;
extern s32 D_004803C0[2];
extern u8 D_004B2570;
extern void *D_00484150;
extern void *D_00484158;
extern void *D_0048415C;
extern Wk_title_FUN_004ec030 *D_00484170;
extern void *D_00484174;
extern s32 D_00484180;
extern u8 title_D_004F1550;
extern u8 title_D_004F1570;
extern u8 title_D_004F1590;
extern u8 title_D_004F15B0;
extern u8 title_D_004F15C8;
extern u8 title_D_004F15E0;

extern void memcpy(void *dst, void *src, s32 n);
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleStateLoadRes_4ec030(void)
{
    Blk_title_FUN_004ec030 blk __attribute__((aligned(16)));
    s32 size;
    Rec_title_FUN_004ec030 *r;
    void *buf;
    void *arch;
    void *fs;
    void *disc;
    void *mem;
    s32 id;
    s32 bits;
    s32 i;
    Dev_title_FUN_004ec030 *dev;

    GetDrawCtxNameTable_15de40();
    buf = 0;
    arch = GetMenuResGroup_206a40();
    disc = GetReadBuffHeap_2025e0();
    if (disc != 0) {
        buf = MemStackHeapAlloc_14db10(disc, 2, 0, 0x40);
        MemStackReturnToOwnerMaybe_14dad0(disc);
        MemStackHeapFree_14dcb0(disc, buf);
    }
    fs = D_00484150;
    if (IsTgsDemoBuild_207f20() != 0) {
        MemStackAlign64_14d8e0(fs);
        if (ResidentFileReadLocalizedMaybe_1c2860(D_004802CC, buf, &size) != 0) {
            PadWaitReady_1849e0(&D_004B2570);
            ResGroupLoadByKind_42b840(arch, 2, 0xD, fs, buf);
            PadWaitReady_1849e0(&D_004B2570);
            D_00484180 = MsgTableLoadFromArchive_202a50(buf, &title_D_004F1550, fs);
            PadWaitReady_1849e0(&D_004B2570);
            TexGroupLoadFromArchive_202be0(buf, &title_D_004F1570, fs, 0x32D, 0);
            TexGroupLoadFromArchive_202be0(buf, &title_D_004F1590, fs, 0x32D, 0);
            TexGroupLoadFromArchive_202be0(buf, &title_D_004F15B0, fs, 0x32D, 0);
            PadWaitReady_1849e0(&D_004B2570);
        }
    } else {
        i = 0;
        do {
            MemStackAlign64_14d8e0(fs);
            if (ResidentFileReadLocalizedMaybe_1c2860(D_004803C0[i], buf, &size) != 0) {
                PadWaitReady_1849e0(&D_004B2570);
                if (i == 1) {
                    ResGroupLoadByKind_42b840(arch, 2, 0xD, fs, buf);
                    PadWaitReady_1849e0(&D_004B2570);
                    ({ __typeof__(((s32)ArchiveGetFileByPath_1c2800(buf, &title_D_004F15C8, &size))) rgp_ao0 = ((s32)ArchiveGetFileByPath_1c2800(buf, &title_D_004F15C8, &size)); SaveMenuMsgTableParse_376b40(fs, rgp_ao0, size); });
                    PadWaitReady_1849e0(&D_004B2570);
                    D_00484180 = MsgTableLoadFromArchive_202a50(buf, &title_D_004F1550, fs);
                    PadWaitReady_1849e0(&D_004B2570);
                    TexGroupLoadFromArchive_202be0(buf, &title_D_004F1570, fs, 0x32D, 0);
                    TexGroupLoadFromArchive_202be0(buf, &title_D_004F1590, fs, 0x32D, 0);
                    TexGroupLoadFromArchive_202be0(buf, &title_D_004F15E0, fs, 0x32D, 0);
                    PadWaitReady_1849e0(&D_004B2570);
                } else {
                    mem = MemStackAllocAligned64_14da10(fs, size / 16 + 1);
                    if (mem != 0) {
                        memcpy(mem, buf, size);
                        SaveIconFilesLoad_37bbd0(&blk, mem);
                        title_TitleSaveIconDataSet_4ede80(&blk);
                        PadWaitReady_1849e0(&D_004B2570);
                    }
                }
            }
            i = i + 1;
        } while (i < 2);
    }
    D_004803A4 = 1;
    r = ((Rec_title_FUN_004ec030 *)ResGroupListFindById_42c500(arch, 0xD));
    id = r->field004;
    bits = r->field00A;
    UiWidgetListReset_2912e0(D_00484170);
    UiInitWidgetPool_290390(D_00484170, D_00484150, bits);
    UiAddWidgets_2901d0(D_00484170, id, 0);
    D_00484170->field008 = 0x32D;
    UiTextStyleReset_290450();
    if (title_TitleDemoPvRowEnabledMaybe_4ed340() != 0) {
        UiSetSpriteUv_28f970(D_00484170, 0x63, 0, 0x127, 0);
        UiSetSpriteUv_28f970(D_00484170, 0x64, 0, 0x9C, 0);
        UiSetSpriteSizeUvSize_28f670(D_00484170, 0x64, 0x200, 0x8A, 0x200, 0x8A, 0);
    } else {
        UiSetSpriteUv_28f970(D_00484170, 0x63, 0, 0x9C, 0);
        UiSetSpriteUv_28f970(D_00484170, 0x64, 0, 0x126, 0);
        UiSetSpriteSizeUvSize_28f670(D_00484170, 0x64, 0x200, 0x9A, 0x200, 0x9A, 0);
    }
    r = ((Rec_title_FUN_004ec030 *)ResGroupListFindById_42c500(arch, 0xC));
    id = r->field004;
    bits = r->field00A;
    UiWidgetListReset_2912e0(D_00484174);
    UiInitWidgetPool_290390(D_00484174, D_00484150, bits);
    UiAddWidgets_2901d0(D_00484174, id, 0);
    ((Wk_title_FUN_004ec030 *)D_00484174)->field008 = 0x32D;
    UiTextStyleReset_290450();
    r = ((Rec_title_FUN_004ec030 *)ResGroupListFindById_42c040(arch, 9));
    id = r->field004;
    bits = r->field00A;
    UiEntryListReset_28ec80(D_0048415C);
    UiEntryListAlloc_28e0c0(D_0048415C, D_00484150, bits);
    UiEntryListLoad_28eb70(D_0048415C, id, D_00484170);
    id = SceneSoundGetSlot0HandleCur_207df0();
    dev = D_0048415C;
    dev->field018 = id;
    dev->bit020 = 0;
    dev->field021 = 0;
    if (IsTgsDemoBuild_207f20() != 0) {
        McSetPortCardType_373110(0, 0);
        McSetPortCardType_373110(0, 1);
    }
    if (McSaveFlagMergeEnabledMaybe_373150() != 0 && IsTgsDemoBuild_207f20() == 0) {
        StateMachineSetState_28ede0(D_00484158, 0xE, 1);
    } else {
        StateMachineSetState_28ede0(D_00484158, 4, 1);
    }
    D_004803A0 = -1;
    title_TitleEnablePadCheck_4f13e0();
    return 1;
}
