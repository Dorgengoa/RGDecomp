import sys
sys.path.insert(0,'.')
import gen
NOTES = {
 'VecDistSq_1cb3c0': 'returns $f0 (f32); caller conflict f32:17 / void:1 -> f32 (a void-declaring caller leaves ST0 on the x87 stack)',
 'MtxInverseAffine_1cb640': 'returns $f0 = det (vf9.x, before the divide); caller conflict void:2 / f32:2 -> f32 (void-declaring callers leave ST0 on the x87 stack)',
 'VecCopyAsPoint_1cbe10': 'asm writes no $v0/$f0 -> void; callers conflict void:11 / s32:4 (two declare one arg (void *))',
 'MatMulPointRelMaybe_1cb5d0': 'no caller sig; 4 pointer args from the asm ($5 only supplies +0x30 translation)',
 'VecScaleDir_1cbc80': 'no callers; signature from the asm',
 'MatScaleRows_1cbc20': 'callers declare arg2 f32*/s32: pointer either way',
}
out = open('build/bind-i686/lane_gamecop2.tsv', 'w', newline='\n')
out.write('symbol\trelpath\tstatus\tsignature\tnote\n')
for s, (ret, params, ir, fr) in gen.SPECS.items():
    out.write(f"{s}\t{gen.rows[s][0]}\tdone\t{ret} {s}({params})\t{NOTES.get(s, 'straight-line COP2 leaf')}\n")
for l in open('manual.tsv'):
    if l.strip(): out.write(l if l.endswith('\n') else l + '\n')
out.write(open('testsrc.txt').read() if __import__('os').path.exists('testsrc.txt') else '')
