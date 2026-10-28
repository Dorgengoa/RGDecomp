"""Generate straight-line COP2 leaf overrides (lane gamecop2).

spec: sym -> (signature, {reg: cexpr}, {freg: cname})
The asm body is read from game/<relpath>; supported EE insns: daddu alias,
addiu alias on an arg, mfc1/mtc1/qmfc2/qmtc2/cfc2 through the model GPRs,
jr/nop/j/labels (straight-line only), .word special2 (vdiv/vsqrt/vrsqrt).
"""
import re, sys, os
sys.path.insert(0, 'tools')
import portxform as px

ROOT = '.'
rows = {}
for l in open(os.path.join(os.path.dirname(__file__), 'rows.tsv')):
    s, f, h = l.rstrip('\n').split('\t')
    rows[s] = (f, h)

P2 = 'void *pd, void *ps'
P3 = 'void *pd, void *pa, void *pb'
A2 = {4: 'pd', 5: 'ps'}
A3 = {4: 'pd', 5: 'pa', 6: 'pb'}

SPECS = {
 # sym: (ret, params, intregs, fregs)
 'VecCopyAsPoint_1cbe10': ('void', P2, A2, {}),
 'VecMax_1cb5b0': ('void', P3, A3, {}),
 'VecMin_1cb590': ('void', P3, A3, {}),
 'VecNegate_1cb9a0': ('void', P2, A2, {}),
 'VecAddXyzW0_1cbda0': ('void', P3, A3, {}),
 'VecAddXyzW1_1cbd80': ('void', P3, A3, {}),
 'VecSubAsPoint_1cbcc0': ('void', P3, A3, {}),
 'VecSubXyzW0_1cbce0': ('void', P3, A3, {}),
 'VecAdd3_1cbd60': ('void', 'void *pd, void *pa, void *pb, void *pc', {4: 'pd', 5: 'pa', 6: 'pb', 7: 'pc'}, {}),
 'VecAddMaxZero_1cbd40': ('void', P3, A3, {}),
 'VecAddMinZero_1cbd20': ('void', P3, A3, {}),
 'VecCross_1cb9f0': ('void', P3, A3, {}),
 'VecLengthSqXZ_1cb450': ('f32', 'void *pv', {4: 'pv'}, {}),
 'VecMinMax_1cb570': ('void', 'void *pmax, void *pmin, void *pa, void *pb', {4: 'pmax', 5: 'pmin', 6: 'pa', 7: 'pb'}, {}),
 'VecScale_1cbca0': ('void', 'void *pd, void *ps, f32 s', A2, {12: 's'}),
 'VecScalePoint_1cbc60': ('void', 'void *pd, void *ps, f32 s', A2, {12: 's'}),
 'MatIdentity_1cbe40': ('void', 'void *pm', {4: 'pm'}, {}),
 'VecDotXZ_1cba70': ('f32', 'void *pa, void *pb', {4: 'pa', 5: 'pb'}, {}),
 'VecLengthSq_1cb470': ('f32', 'void *pv', {4: 'pv'}, {}),
 'VecScaleDir_1cbc80': ('void', 'void *pd, void *ps, f32 s', A2, {12: 's'}),
 'MtxMulDir_1cb910': ('void', 'void *pd, void *pm, void *pv', {4: 'pd', 5: 'pm', 6: 'pv'}, {}),
 'VecDistSqXZ_1cb390': ('f32', 'void *pa, void *pb', {4: 'pa', 5: 'pb'}, {}),
 'VecDot3_1cba90': ('f32', 'void *pa, void *pb', {4: 'pa', 5: 'pb'}, {}),
 'VecLengthXZ_1cb490': ('f32', 'void *pv', {4: 'pv'}, {}),
 'VecSubCross_1cb9c0': ('void', 'void *pd, void *pa, void *pb, void *pc', {4: 'pd', 5: 'pa', 6: 'pb', 7: 'pc'}, {}),
 'TriCalcBounds_1cb540': ('void', 'void *pmax, void *pmin, void *pa, void *pb, void *pc', {4: 'pmax', 5: 'pmin', 6: 'pa', 7: 'pb', 8: 'pc'}, {}),
 'TriNormal_1cb970': ('void', 'void *pd, void *pa, void *pb, void *pc', {4: 'pd', 5: 'pa', 6: 'pb', 7: 'pc'}, {}),
 'VecDistSq_1cb3c0': ('f32', 'void *pa, void *pb', {4: 'pa', 5: 'pb'}, {}),
 'VecDivScalar_1cbbf0': ('void', 'void *pd, void *ps, f32 s', A2, {12: 's'}),
 'VecLength_1cb4c0': ('f32', 'void *pv', {4: 'pv'}, {}),
 'VecSubDotXZ_1cba10': ('f32', 'void *pa, void *pb, void *pc', {4: 'pa', 5: 'pb', 6: 'pc'}, {}),
 'VecDistXZ_1cb3f0': ('f32', 'void *pa, void *pb', {4: 'pa', 5: 'pb'}, {}),
 'VecDivScalarPoint_1cbbc0': ('void', 'void *pd, void *ps, f32 s', A2, {12: 's'}),
 'VecDotDiff_1cba40': ('f32', 'void *pa, void *pb, void *pc', {4: 'pa', 5: 'pb', 6: 'pc'}, {}),
 'VecLerp_1cbb20': ('void', 'void *pd, void *pa, void *pb, f32 t', A3, {12: 't'}),
 'MatMulPointRelMaybe_1cb5d0': ('void', 'void *pd, void *pbase, void *pm, void *pv', {4: 'pd', 5: 'pbase', 6: 'pm', 7: 'pv'}, {}),
 'VecDist_1cb420': ('f32', 'void *pa, void *pb', {4: 'pa', 5: 'pb'}, {}),
 'VecLerpDir_1cbaf0': ('void', 'void *pd, void *pa, void *pb, f32 t', A3, {12: 't'}),
 'VecLerpPoint_1cbac0': ('void', 'void *pd, void *pa, void *pb, f32 t', A3, {12: 't'}),
 'VecLinearCombine_1cb8b0': ('void', 'void *pd, void *pa, void *pb, f32 sa, f32 sb', A3, {12: 'sa', 13: 'sb'}),
 'VecNormalizeXZ_1cbb50': ('void', P2, A2, {}),
 'VecScaleToLength_1cb510': ('void', 'void *pd, void *ps, f32 len', A2, {12: 'len'}),
 'MatScaleRows_1cbc20': ('void', 'void *pd, void *pm, void *pv', {4: 'pd', 5: 'pm', 6: 'pv'}, {}),
 'VecNormalize_1cbb80': ('void', P2, A2, {}),
 'TriNormalDot_1cb600': ('f32', 'void *pa, void *pb, void *pc, void *pn', {4: 'pa', 5: 'pb', 6: 'pc', 7: 'pn'}, {}),
 'MatMul_1cb700': ('void', P3, A3, {}),
 'MatOrthonormalizeY_1cb300': ('void', P2, A2, {}),
 'MtxInverseAffine_1cb640': ('f32', P2, A2, {}),
 'CollTriTransform_16c1a0': ('void', 'void *p0, void *p1, void *p2, void *p3', {4: 'p0', 5: 'p1', 6: 'p2', 7: 'p3'}, {}),
}

FLD = 'xyzw'


def word(w):
    op = (((w >> 6) & 0x1f) << 2) | (w & 3)
    ftf, fsf = (w >> 23) & 3, (w >> 21) & 3
    ft, fs = (w >> 16) & 31, (w >> 11) & 31
    if (w >> 25) != 0x25 or ((w >> 2) & 0xF) != 0xF:
        raise ValueError(hex(w))
    if op == 0x38:
        return f'vdiv Q, vf{fs}{FLD[fsf]}, vf{ft}{FLD[ftf]}'
    if op == 0x39:
        return f'vsqrt Q, vf{ft}{FLD[ftf]}'
    if op == 0x3A:
        return f'vrsqrt Q, vf{fs}{FLD[fsf]}, vf{ft}{FLD[ftf]}'
    raise ValueError(hex(w))


def gen(sym):
    ret, params, iregs, fregs = SPECS[sym]
    rel, sha = rows[sym]
    src = open(f'{ROOT}/game/{rel}').read()
    body = src[src.index('{', src.index(sym)) + 1:src.rindex('}')]
    alias = {r: f'(char *){c}' for r, c in iregs.items()}  # reg -> C address expr
    x = px.VuXlat()
    out = []
    has_ret = False
    for line in body.split('\n'):
        st = line.strip().rstrip(';').strip()
        if not st or st.startswith('.set') or st.endswith(':') or st.startswith('/*'):
            continue
        orig = st
        parts = st.split(None, 1)
        mn = parts[0].lower()
        ops = [o.strip() for o in re.split(r',(?![^()]*\))', parts[1])] if len(parts) > 1 else []
        mnb = re.sub(r'\.(ni|i)$', '', mn)
        c = None
        if mn in ('nop', 'vnop', 'vwaitq'):
            c = 'rg_vu0_waitq();' if mn == 'vwaitq' else None
        elif mn == 'jr':
            continue
        elif mn == 'j':
            c = None  # straight-line: target is the next instruction after the slot
        elif mn == '.word':
            st2 = word(int(ops[0], 16))
            c = x.stmt(st2)
            orig = f'{orig}  ({st2})'
        elif mn in ('daddu', 'addu', 'or') and ops[2] == '$0':
            d, s = int(ops[0][1:]), int(ops[1][1:])
            alias[d] = alias[s]
            c = None
        elif mn == 'addiu' and int(ops[1][1:]) in alias:
            d, s = int(ops[0][1:]), int(ops[1][1:])
            alias[d] = f'({alias[s]} + {ops[2]})'
        elif mn == 'mfc1':
            g = int(ops[0][1:]); f = int(ops[1][2:])
            alias.pop(g, None)
            c = f'rg_vu0_mfc1({g}, {fregs[f]});'
        elif mn == 'mtc1':
            g = int(ops[0][1:]); f = int(ops[1][2:])
            assert f == 0 and ret == 'f32', orig
            c = f'ret = rg_vu0_mtc1({g});'
            has_ret = True
        elif mnb in ('qmfc2', 'qmtc2', 'cfc2'):
            g = int(ops[0][1:])
            if mnb != 'qmtc2':
                alias.pop(g, None)
            op1 = ops[1].replace('$', '')
            c = x.stmt(f'{mnb} ${g}, {op1}') if mnb != 'qmtc2' else f'rg_vu0_qmtc2({g}, {int(op1[2:])});'
        elif mnb in ('lqc2', 'sqc2'):
            n = int(ops[0].replace('$vf', ''))
            m = re.fullmatch(r'(-?0x[0-9A-Fa-f]+|\d+)\((\$\d+)\)', ops[1])
            off, base = m.group(1), int(m.group(2)[1:])
            a = alias[base]
            a = a if int(off, 16) == 0 else f'{a} + {off}'
            c = f'rg_vu0_{mnb}({n}, {a});'
        elif mn.startswith('v'):
            c = x.stmt(st.replace('$', ''))
        else:
            raise ValueError(f'{sym}: unhandled {orig}')
        o = orig.replace('*/', '* /')
        out.append(f'    {c} /* {o} */' if c else f'    /* {o} */')
    if ret == 'f32':
        assert has_ret, sym
    hdr = (f'/* rg-override: replaces game/{rel} sha256 {sha}\n'
           f' * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */\n'
           '#include "types.h"\n\n')
    fn = f'{ret} {sym}({params})\n{{\n'
    if ret == 'f32':
        fn += '    f32 ret;\n'
    fn += '\n'.join(out) + '\n'
    if ret == 'f32':
        fn += '    return ret;\n'
    fn += '}\n'
    dst = f'{ROOT}/overrides/{rel}'
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    open(dst, 'w', newline='\n').write(hdr + fn)
    return rel


if __name__ == '__main__':
    for s in (sys.argv[1:] or SPECS):
        print(gen(s))
