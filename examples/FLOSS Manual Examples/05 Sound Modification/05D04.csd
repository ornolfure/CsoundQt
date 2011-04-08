see http://www.flossmanuals.net/csound/ch034_d-delay-and-feedback

<CsoundSynthesizer>

<CsOptions>
-odac ;activates real time sound output
</CsOptions>

<CsInstruments>
;Example by Iain McCurdy

sr = 44100
ksmps = 32
nchnls = 1
0dbfs = 1

giSine   ftgen   0, 0, 2^12, 10, 1; a sine wave

  instr 1
; create an input signal
kEnv    loopseg  0.5, 0, 0, 0,0.0005, 1 , 0.1, 0, 1.9, 0; repeating envelope
kCps    randomh  400, 1000, 0.5; 'held' random values
aEnv    interp   kEnv; interpolate kEnv to create a-rate version
aSig    poscil   aEnv, kCps, giSine; generate audio

; create a delay buffer
aBufOut delayr   0.5; read audio from end of 0.3s buffer
aTap1   deltap   0.1373; delay tap 1
aTap2   deltap   0.2197; delay tap 2
aTap3   deltap   0.4139; delay tap 3
        delayw   aSig + (aTap3*0.4); write audio into buffer (mix in feedback signal)

; send audio to ther output (mix the input signal with the delayed signals)
        out      aSig + ((aTap1+aTap2+aTap3)*0.4)
  endin


</CsInstruments>

<CsScore>
i 1 0 25
e
</CsScore>

</CsoundSynthesizer>
<bsbPanel>
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
