#pragma cplusplus on
typedef unsigned int U;
struct S { U flags, size; char *data; };
struct Short { unsigned char flag:1, size:7; };
extern "C" void StringReserve_107e80(S *, U);
extern "C" void StringReplaceSubstr_107cd0(S *, U, U, const S *, U, U);
static inline const U& minimum(const U& a, const U& b) { return a<b?a:b; }
extern "C" S *StringCtorSubstr_107b70(S *s, const S *other, U pos, U count) {
 s->flags=0; s->size=0; s->data=0;
 U size;
 if(other->flags&1) size=other->size; else size=((const Short *)other)->size;
 U capacity;
 if(pos<=size) capacity=minimum(size-pos,count); else capacity=0;
 StringReserve_107e80(s,capacity);
 StringReplaceSubstr_107cd0(s,0,0,other,pos,count);
 return s;
}
