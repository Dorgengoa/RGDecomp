#include "script_vm.h"

/* Attach a compiled script blob to a VM and give it its working memory.

   The caller supplies two buffers: an operand stack of 8-byte slots (the
   {type, value} pairs the VM pushes) and a call-frame buffer of 12-byte
   entries. Both get an end pointer computed up front so the interpreter can
   bounds-check by comparison instead of arithmetic.

   The blob is only accepted if its header says "SB2". Once accepted, the
   bottom of the operand stack is carved off as the script's globals -- that
   many slots are taken away from the stack and zeroed. */

/* The "SB2" magic lives in the data segment, so from this unit it is an
   external the same way any other cross-unit constant is -- naming it lets the
   relocation compare equal instead of pointing at mwcc's internal @N label. */
extern const char D_00459610[];

extern s32 strncmp(const void *blob, const char *magic, s32 len);
extern void memset(void *dst, s32 fill, s32 len);

void ScriptVmInit_176af0(ScriptVm *vm, ScriptBlob *blob, u8 *stack, s32 stackSlots,
                  u8 *frames, s32 frameCount)
{
    vm->stack = stack;
    vm->stackSlots = stackSlots;
    vm->frames = frames;
    vm->frameCount = frameCount;
    vm->stackEnd = vm->stack + stackSlots * 8;
    vm->framesEnd = vm->frames + frameCount * 12;
    vm->blob = blob;
    vm->code = (u8 *)blob + blob->codeOffset;

    if (strncmp(vm->blob, D_00459610, 3) != 0) {
        return;
    }

    vm->state = 2;
    vm->globals = vm->stack;
    vm->stack = vm->stack + vm->blob->globalCount * 8;
    vm->stackSlots = vm->stackSlots - vm->blob->globalCount;
    memset(vm->globals, 0, vm->blob->globalCount * 8);
}
