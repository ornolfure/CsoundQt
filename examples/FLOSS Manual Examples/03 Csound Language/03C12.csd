see http://www.flossmanuals.net/csound/ch018_c-control-structures

<CsoundSynthesizer>
<CsOptions>
-odac
</CsOptions>
<CsInstruments>
;example by joachim heintz
sr = 44100
ksmps = 32
nchnls = 2
0dbfs = 1

giSine    ftgen     0, 0, 2^10, 10, 1

  instr 1
kFreq     expseg    400, p3, 600
aTone     poscil    .2, kFreq, giSine
          outs      aTone, aTone
  endin

</CsInstruments>
<CsScore>
i 1 0 3
i 1 4 5
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
