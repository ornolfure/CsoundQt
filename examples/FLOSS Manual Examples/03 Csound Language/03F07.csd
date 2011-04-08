see http://www.flossmanuals.net/csound/ch021_f-user-defined-opcodes

<CsoundSynthesizer>
<CsInstruments>
;example by joachim heintz

  opcode Defaults, iii, opj
ia, ib, ic xin
xout ia, ib, ic
  endop

instr 1
ia, ib, ic Defaults
           print     ia, ib, ic
ia, ib, ic Defaults  10
           print     ia, ib, ic
ia, ib, ic Defaults  10, 100
           print     ia, ib, ic
ia, ib, ic Defaults  10, 100, 1000
           print     ia, ib, ic
endin

</CsInstruments>
<CsScore>
i 1 0 0
</CsScore>
</CsoundSynthesizer><bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>630</x>
 <y>260</y>
 <width>380</width>
 <height>205</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="background">
  <r>230</r>
  <g>140</g>
  <b>36</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
<MacGUI>
ioView background {59110, 35980, 9252}
</MacGUI>
