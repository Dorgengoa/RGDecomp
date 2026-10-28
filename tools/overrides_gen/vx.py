import sys, re
sys.path.insert(0, 'tools')
import portxform as px
x = px.VuXlat()
for l in sys.stdin:
    st = l.strip().rstrip(';').strip()
    if not st: continue
    c = x.stmt(st.replace('$', ''))
    print(f'    {c} /* {st} */')
