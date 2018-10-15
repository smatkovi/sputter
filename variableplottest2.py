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
plt.subplots_adjust(left=0.25, bottom=0.45)
t = np.arange(1e-7, 1e-7+5e-2, 1e-5) #this is the pressure p
J = 4.0
S_N = 0.1
M = 4.6518e-26
T = 273.0
S_M = 1.0
alpha_t = 1.0
e = 1.6021766e-19
k_B = 1.38065e-23
pi = 4.0*np.arctan(1.0)

s = t*(S + J*A_t*S_N*(1.0/(2.0*e*t + (J*S_N np.sqrt(2.0*M*pi*T*k_B))/alpha_t) + (J*A_c*alpha_c*S_M*np.sqrt(2.0*M*pi*T*k_B))/(J*A_t*S_N*np.sqrt(2.0*M*pi*T*k_B) (2.0*e*alpha_t*t + J*S_M*np.sqrt(2 M pi T k_B)) + 2.0*e*A_c*alpha_c*t*(2.0*e*alpha_t*t + J*S_N*np.sqrt(2.0*M*pi*T*k_B)))))
#s = (J*S_N*(2.0*e*alpha_t*t + J*S_M*np.sqrt(2.0*M*pi*T*k_B)))/(e*(2.0*e*alpha_t*t + J*S_N*np.sqrt(2.0*M*pi*T*k_B)))
#s = J*S_N*(J*np.sqrt(M*T)*S_M+t*alpha_t)/(J*np.sqrt(M*T)*S_N+t*alpha_t)
l, = plt.plot(t, s, lw=2, color='red')
plt.axis([3e1, 1.4e2, 1.0e17, 4.5e18])

axcolor = 'lightgoldenrodyellow'
axfreq = plt.axes([0.25, 0.1, 0.65, 0.03], facecolor=axcolor)
axamp = plt.axes([0.25, 0.15, 0.65, 0.03], facecolor=axcolor)
axS_M = plt.axes([0.25, 0.2, 0.65, 0.03], facecolor=axcolor)
axalpha_t = plt.axes([0.25, 0.25, 0.65, 0.03], facecolor=axcolor)
axT = plt.axes([0.25, 0.3, 0.65, 0.03], facecolor=axcolor)




sfreq = Slider(axfreq, 'J', J, 30.0, valinit=J)
samp = Slider(axamp, 'S_N', 0.1, 0.3, valinit=S_N)
sS_M = Slider(axS_M, 'S_M', 1.0, 3.0, valinit=S_M)
salpha_t = Slider(axalpha_t, 'alpha_t', 0.1, 1.0, valinit=alpha_t)
sT = Slider(axT, 'T', 273.0, 300.0, valinit=T)




def update(val):
    J = samp.val
    S_N = sfreq.val
    S_M = sS_M.val
    alpha_t = salpha_t.val
    T = sT.val
    l.set_ydata((J*S_N*(2.0*e*alpha_t*t + J*S_M*np.sqrt(2.0*M*pi*T*k_B)))/(e*(2.0*e*alpha_t*t + J*S_N*np.sqrt(2.0*M*pi*T*k_B))))
            
    fig.canvas.draw_idle()
sfreq.on_changed(update)
samp.on_changed(update)
sS_M.on_changed(update)
salpha_t.on_changed(update)
sT.on_changed(update)




resetax = plt.axes([0.8, 0.025, 0.1, 0.04])
button = Button(resetax, 'Reset', color=axcolor, hovercolor='0.975')


def reset(event):
    sfreq.reset()
    samp.reset()
    sS_M.reset()
    salpha_t.reset()
    sT.reset()
button.on_clicked(reset)
button.on_clicked(reset)
button.on_clicked(reset)
button.on_clicked(reset)

rax = plt.axes([0.025, 0.5, 0.15, 0.15], facecolor=axcolor)
radio = RadioButtons(rax, ('red', 'blue', 'green'), active=0)


def colorfunc(label):
    l.set_color(label)
    fig.canvas.draw_idle()
radio.on_clicked(colorfunc)

plt.show()
