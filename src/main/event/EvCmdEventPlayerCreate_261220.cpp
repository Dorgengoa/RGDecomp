#include "types.h"

/* System-script opcode 0x5D8: create the event player and load its project.

   The four operands are pulled off the script's argument block eight bytes at
   a time -- a scene id, two resource names, and, only when the script passed
   four or more arguments, an archive to resolve them against.

   The player itself is 0xA70 bytes allocated out of the scene's heap. Its
   vtable is D_00471480 and its four sub-objects sit at +0x60, +0x420, +0x48C
   and +0x4A0 -- the same three that EventPlayerUpdate_249a80's tick drives, so create and
   tick corroborate each other. It is published to D_00482040 before anything
   can fail, which is why every later error path still returns 0 with the
   pointer already live.

   STATUS: MATCHED, byte for byte (2026-08-22).

   ★★★★ THE CURSOR IS THE PARAMETER ITSELF, not a local initialised from it.
   With a local `Slot *p = args`, mwcc parks the cursor in s3 and the argument
   count in s4; retail has them the other way round, and every later
   scene/player pointer inherits the opposite register -- nine words of pure
   register naming that read as the unfixable symmetric-naming class. Declaring
   the parameter as `Slot *args` and writing `f(args++)` directly closes ALL
   NINE at once: mwcc then copies args to the callee-saved register first
   (it has to, the increment precedes the first call) and argc second, which
   is the order that picks s4 and s3 the way retail did.
   ⚠ Moving the local's declaration to the end of the block was tried and cost
   4%. The lever was never declaration order -- it was that the local should
   not exist.

   ★ The operand cursor is a POST-INCREMENTED pointer to 8-byte slots. Written
   as `args + 8` / `args + 16` mwcc folds it into immediate offsets and the
   whole prologue drifts -- 89% against this. */

/* The script's operand slots are 8 bytes each -- see the VM note. */
typedef struct Slot {
    u8 b[8];
} Slot;

class Player {
    u8 pad000[0x58];
public:
    /* vtable +0x08 -- the init slot */
    virtual void init();
    /* +0x58 is the vptr */
};

typedef struct Scene {
    u8 pad00[0x28];
    u8 *base;      /* +0x28 */
    s32 used;      /* +0x2C */
    u8 pad30[0x4];
    s32 x34;       /* +0x34 */
} Scene;

typedef struct World {
    u8 pad0000[0x1808];
    Scene *sub;    /* +0x1808 */
} World;

extern "C" {
extern u8 D_00471480[];
extern void *D_004BD980[];
extern World *D_00481F78;
extern Player *D_00482040;

extern s32 ScriptGetInt_26a2a0(Slot *slot);
extern void *ScriptGetCodeAddr_26a200(Slot *slot);
extern Scene *RecStackGetSlot_1c4330(World *world, void *key);
extern void MemStackAlign64_14d8e0(Scene *scene);
extern void *MemStackNew_14e230(s32 size, Scene *scene);
extern void EventScriptBaseCtor_261720(void *player);
extern void EventCastCtor_261530(void *sub);
extern void EventVoiceListCtor_261510(void *sub);
extern void Vec4VectorCtor_2614f0(void *sub);
extern void EventSoundTableCtor_2614c0(void *sub);
extern void *ArchiveGetFileByPath_1c2800(void *archive, void *name, u32 *size);
extern void *FileLoadCached_26a6c0(void *name, u32 *size);
extern void memcpy(void *dst, void *src, u32 size);
extern void MemStackAllocQw_14d950(Scene *scene, u32 blocks);
extern void EventScriptVmInit_23ffa0(Player *player, void *data, Scene *scene);
extern void EventCastLoadCfg_249b60(Player *player, Scene *scene, void *blob, u32 size);
extern void *MemStackHeapAlloc_14db10(Scene *scene, s32 a, s32 b, s32 c);
extern void EventPlayerInitVoiceList_249b50(Player *player, Scene *scene, void *data,
                         s32 a, s32 b, s32 c, s32 d);
extern s32 MesMgrGetSlotWin_266af0(s32 which);
extern void MemStackReturnToOwnerMaybe_14dad0(Scene *scene);
extern void MemStackHeapFree_14dcb0(Scene *scene, void *handle);
}

typedef struct PlayerTail {
    u8 pad000[0x42C];
    s32 x42C;
} PlayerTail;

extern "C" s32 EvCmdEventPlayerCreate_261220(Slot *args, s32 argc)
{
    Scene *scene;
    Player *player;
    void *nameA;
    void *nameB;
    void *archive;
    void *data;
    void *blob;
    void *handle;
    Scene *sub;
    s32 id;
    /* TWO size slots, not one reused: retail keeps them at sp+0x7C and
       sp+0x78. Unsigned -- the block count is `srl`, not `sra`. */
    u32 sizeA;
    u32 sizeB;

    /* A moving cursor, not indexed offsets. The FIRST read goes through the
       parameter itself -- retail passes the incoming a0 untouched and keeps a
       separate register that is already one slot ahead. */
    archive = 0;
    id = ScriptGetInt_26a2a0(args++);
    nameA = ScriptGetCodeAddr_26a200(args++);
    nameB = ScriptGetCodeAddr_26a200(args++);
    if (argc >= 4) {
        archive = ScriptGetCodeAddr_26a200(args);
    }

    /* Assigned inside the test: retail branches on the raw return value and
       copies it into the callee-saved register in the delay slot. */
    if ((scene = RecStackGetSlot_1c4330(D_00481F78, D_004BD980[id])) == 0) {
        return 0;
    }

    MemStackAlign64_14d8e0(scene);
    if ((player = (Player *)MemStackNew_14e230(0xA70, scene)) != 0) {
        EventScriptBaseCtor_261720(player);
        *(u8 **)((u8 *)player + 0x58) = D_00471480;
        EventCastCtor_261530((u8 *)player + 0x60);
        EventVoiceListCtor_261510((u8 *)player + 0x420);
        Vec4VectorCtor_2614f0((u8 *)player + 0x48C);
        EventSoundTableCtor_2614c0((u8 *)player + 0x4A0);
        player->init();
    }
    D_00482040 = player;
    if (player == 0) {
        return 0;
    }

    sizeA = 0;
    if (archive != 0) {
        data = ArchiveGetFileByPath_1c2800(archive, nameB, &sizeA);
    } else {
        data = FileLoadCached_26a6c0(nameB, &sizeA);
    }
    if (data == 0) {
        return 0;
    }
    MemStackAlign64_14d8e0(scene);
    {
        u8 *dst = scene->base + scene->used * 16;

        memcpy(dst, data, sizeA);
        /* Rounded up to whole 16-byte blocks, as one argument expression --
           written through a local the shift is hoisted out of both paths. */
        MemStackAllocQw_14d950(scene, (sizeA & 0xF) != 0 ? (sizeA >> 4) + 1 : sizeA >> 4);
        MemStackAlign64_14d8e0(scene);
        EventScriptVmInit_23ffa0(D_00482040, dst, scene);
    }

    sizeB = 0;
    if (archive != 0) {
        blob = ArchiveGetFileByPath_1c2800(archive, nameA, &sizeB);
    } else {
        blob = FileLoadCached_26a6c0(nameA, &sizeB);
    }
    if (blob == 0) {
        return 0;
    }
    MemStackAlign64_14d8e0(scene);
    EventCastLoadCfg_249b60(D_00482040, scene, blob, sizeB);

    sub = D_00481F78->sub;
    handle = MemStackHeapAlloc_14db10(sub, 2, 0, 0x40);
    EventPlayerInitVoiceList_249b50(D_00482040, scene, sub->base + sub->x34 * 16, 2, 4, 2, 1);
    ((PlayerTail *)D_00482040)->x42C = MesMgrGetSlotWin_266af0(6);
    MemStackReturnToOwnerMaybe_14dad0(sub);
    MemStackHeapFree_14dcb0(sub, handle);
    return 1;
}
