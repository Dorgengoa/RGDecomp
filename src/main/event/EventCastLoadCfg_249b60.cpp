#include "types.h"

/* Load an event project: hand the blob to the reader, publish a small
   {owner, ..., project} record as the current parse context for the duration,
   and clear it again on the way out.

   The template at D_0044CE50 is 40 bytes of callbacks copied onto the stack
   before the read, so the reader gets a private, mutable copy. */

typedef struct ReaderTemplate {
    void *fn[10];      /* 40 bytes */
} ReaderTemplate;

typedef struct ParseContext {
    void *owner;       /* +0x00 */
    s32 unk04;         /* +0x04 */
    void *project;     /* +0x08 */
} ParseContext;

typedef struct Reader { u8 bytes[0xED0]; } Reader;

/* A real class: retail's prepare() goes through $t9, and the vptr lands at
   +0x58 because the padding in front of it is declared first. */
class Owner {
    u8 pad00[0x58];
public:
    /* vtable +0x08, the first slot a virtual can occupy */
    virtual void prepare();
    /* +0x58 is the vptr; data resumes after it. */
    u8 pad5c[0x4];
    u8 sub60[0x4];     /* +0x60 */
};

extern "C" {
extern const ReaderTemplate D_0044CE50;
extern ParseContext *D_00481F54;
extern void *D_00481F34;

extern void TextReaderCtor_15f140(Reader *r);
extern void BuildKeywordHashTable_15f270(Reader *r, ReaderTemplate *t);
extern void TextReaderOpen_15f1b0(Reader *r, void *blob, s32 size);
extern void TextReaderParseAll_15f3f0(Reader *r);
extern void EventCastListAllocIds_24bae0(void *sub, void *project);
extern void MemStackAlign64_14d8e0(void *project);
extern void *MemStackAllocAligned64_14da10(void *project, s32 flags);
}

extern "C" void EventCastLoadCfg_249b60(Owner *owner, void *project, void *blob, s32 size)
{
    ReaderTemplate temp;
    Reader reader;
    ParseContext context;

    owner->prepare();

    /* Copied through a char pointer. mwcc assumes any named global is qword
       aligned and moves 16 bytes an iteration; retail's loop is 5 iterations
       of 8 bytes built from `lw`/`sw`, which is the 4-byte-alignment path --
       the cast is what stops the compiler proving the alignment. */
    temp = *(const ReaderTemplate *)((const char *)&D_0044CE50);
    TextReaderCtor_15f140(&reader);

    context.owner = NULL;
    context.project = NULL;
    context.unk04 = 0;
    D_00481F54 = &context;
    D_00481F54->owner = owner;
    D_00481F54->project = project;

    BuildKeywordHashTable_15f270(&reader, &temp);
    TextReaderOpen_15f1b0(&reader, blob, size);
    TextReaderParseAll_15f3f0(&reader);

    EventCastListAllocIds_24bae0(owner->sub60, project);
    MemStackAlign64_14d8e0(project);
    D_00481F34 = MemStackAllocAligned64_14da10(project, 0x801);
    D_00481F54 = 0;   /* C++: no implicit void * conversion */
}
