#include "types.h"

extern void WorldSubsysLinkIds_4147d0(s32, s32);
extern void WorldSubsysLinkIds_415190(s32, s32);
extern void WorldSubsysLinkIds_4155c0(s32, s32);
extern void WorldSubsysLinkIds_415aa0(s32, s32);
extern void WorldSubsysLinkParents_415ea0(s32, s32);
extern void WorldSubsysLinkIds_416a70(s32, s32);

s32 WorldSubsysLinkAll_411d10(void *self)
{
    u8 *p = (u8 *)self;
    s32 t;

    t = *(s32 *)(p + 0x14);
    if (t != 0) {
        WorldSubsysLinkParents_415ea0(t, *(s32 *)(p + 4));
    }
    t = *(s32 *)(p + 0x18);
    if (t != 0) {
        WorldSubsysLinkIds_415aa0(t, *(s32 *)(p + 4));
    }
    t = *(s32 *)(p + 0x8);
    if (t != 0) {
        WorldSubsysLinkIds_416a70(t, *(s32 *)(p + 4));
    }
    t = *(s32 *)(p + 0x1C);
    if (t != 0) {
        WorldSubsysLinkIds_4155c0(t, *(s32 *)(p + 4));
    }
    t = *(s32 *)(p + 0x24);
    if (t != 0) {
        WorldSubsysLinkIds_415190(t, *(s32 *)(p + 4));
    }
    t = *(s32 *)(p + 0x34);
    if (t != 0) {
        WorldSubsysLinkIds_4147d0(t, *(s32 *)(p + 4));
    }
    return 1;
}
