#include "types.h"

/* Clone group w2b-007: `jalr $25` off the vptr at +0x00, slot 0xC0 =
   index (0xC0-8)/4 = 46.  The sltu/xori pair is a bool NEGATION of the
   s32 the virtual returned. */

class ObjFUN_003b67c0 {
public:
    virtual s32 s000();
    virtual s32 s001();
    virtual s32 s002();
    virtual s32 s003();
    virtual s32 s004();
    virtual s32 s005();
    virtual s32 s006();
    virtual s32 s007();
    virtual s32 s008();
    virtual s32 s009();
    virtual s32 s010();
    virtual s32 s011();
    virtual s32 s012();
    virtual s32 s013();
    virtual s32 s014();
    virtual s32 s015();
    virtual s32 s016();
    virtual s32 s017();
    virtual s32 s018();
    virtual s32 s019();
    virtual s32 s020();
    virtual s32 s021();
    virtual s32 s022();
    virtual s32 s023();
    virtual s32 s024();
    virtual s32 s025();
    virtual s32 s026();
    virtual s32 s027();
    virtual s32 s028();
    virtual s32 s029();
    virtual s32 s030();
    virtual s32 s031();
    virtual s32 s032();
    virtual s32 s033();
    virtual s32 s034();
    virtual s32 s035();
    virtual s32 s036();
    virtual s32 s037();
    virtual s32 s038();
    virtual s32 s039();
    virtual s32 s040();
    virtual s32 s041();
    virtual s32 s042();
    virtual s32 s043();
    virtual s32 s044();
    virtual s32 s045();
    virtual s32 s046();
};

extern "C" bool CharaIsTargetable_3b67c0(ObjFUN_003b67c0 *self)
{
    return !self->s046();
}
