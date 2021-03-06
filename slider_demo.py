"""
===========
Slider Demo
===========

Using the slider widget to control visual properties of your plot.

In this example, a slider is used to choose the frequency of a sine
wave. You can control many continuously-varying properties of your plot in
this way.
"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, RadioButtons

fig, ax = plt.subplots()
plt.subplots_adjust(left=0.25, bottom=0.25)
t = np.arange(0.0, 1.0, 0.001)
J = 14.0
S_N = 0.3
M = 4.6518e-26
T= 300.0
S_M = 1.5
p = 1e-7
a_t = 1

s = J*S_N*(J*np.sqrt(M*T)*S_M+p*a_t)/(J*np.sqrt(M*T)*S_N+p*a_t)
l, = plt.plot(t, s, lw=2, color='red')
plt.axis([0, 1, -10, 10])

axcolor = 'lightgoldenrodyellow'
axfreq = plt.axes([0.25, 0.1, 0.65, 0.03], facecolor=axcolor)
axamp = plt.axes([0.25, 0.15, 0.65, 0.03], facecolor=axcolor)

sfreq = Slider(axfreq, 'J', 0.1, 30.0, valinit=J)
samp = Slider(axamp, 'S_N', 0.1, 1.0, valinit=S_N)


def update(val):
    S_N = samp.val
    J = sfreq.val
    l.set_ydata(J*S_N*(J*np.sqrt(M*T)*S_M+p*a_t)/(J*np.sqrt(M*T)*S_N+p*a_t)
)
    fig.canvas.draw_idle()
sfreq.on_changed(update)
samp.on_changed(update)

#rax = plt.axes([0.025, 0.5, 0.15, 0.15], facecolor=axcolor)



plt.show()
