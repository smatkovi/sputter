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
plt.subplots_adjust(left=0.25, bottom=0.6)
t = np.arange(2e19, 1.4e20, 1e15) #this is the sputter rate Y
J = 4.0
S_N = 0.1
T = 273.0
S_M = 1.0
z_t = 1
e = 1.6021766e-19

S = 50
M = 4.6518e-26
z_c = 1
A_t = 0.127
A_c = 1.27
k_B = 1.38065e-23 


s = (J*(-e*t + J*S_M)*S_N*(S + (A_t*z_t*(-e*t + J*S_N)*(e*t*A_t*z_t*(S_M - S_N)*(e*t - J*S_N) + A_c*z_c*(e*J*t*S_M**2 + e*t*(-e*S*t + (J*S + e*t)*S_N) + J*S_M*(e*S*t + S_N*(-J*S - 3*e*t + J*S_N)))))/(J*(-S_M + S_N)*(e*t*A_t*z_t*(S_M - S_N)*(e*t - J*S_N) - A_c*z_c*(e*t - J*S_M)*(e*S*t - (J*S + e*t - J*S_M)*S_N))*np.sqrt(2*M*np.pi*T*k_B)))*np.sqrt(2*M*np.pi*T*k_B))/(2*e*z_t*(e*t - J*S_N))
#s = (A_c*z_c*t*(1-(S_N/((J*S_N*np.sqrt(m*T))/(z_t*t)+1)+(A_c*z_c*t)/(A_t*np.sqrt(m*T)))/(S_M*(1-1/((J*S_N*np.sqrt(m*T))/(z_t*t)+1))+S_N/((J*S_N*np.sqrt(m*T))/(z_t*t)+1)+(A_c*z_c*t)/(A_t*J*np.sqrt(m*T)))))/np.sqrt(m*T)+(A_t*z_t*t*(1-1/((J*S_N*np.sqrt(m*T))/(z_t*t)+1)))/np.sqrt(m*T)+S*t
l, = plt.plot(t, s, lw=2, color='red')
plt.axis([1e19, 1e20, -4e20, 5e20])

axcolor = 'lightgoldenrodyellow'
axfreq = plt.axes([0.25, 0.1, 0.65, 0.03], facecolor=axcolor)
axamp = plt.axes([0.25, 0.15, 0.65, 0.03], facecolor=axcolor)
axS_M = plt.axes([0.25, 0.2, 0.65, 0.03], facecolor=axcolor)
axz_t = plt.axes([0.25, 0.25, 0.65, 0.03], facecolor=axcolor)
axT = plt.axes([0.25, 0.3, 0.65, 0.03], facecolor=axcolor)
axS = plt.axes([0.25, 0.35, 0.65, 0.03], facecolor=axcolor)
axz_c = plt.axes([0.25, 0.4, 0.65, 0.03], facecolor=axcolor)
axA_t = plt.axes([0.25, 0.45, 0.65, 0.03], facecolor=axcolor)
axA_c = plt.axes([0.25, 0.5, 0.65, 0.03], facecolor=axcolor)



sfreq = Slider(axfreq, 'J', 0.1, 30.0, valinit=J)
samp = Slider(axamp, 'S_N', 0.1, 10.0, valinit=S_N)
sS_M = Slider(axS_M, 'S_M', 1.0, 3.0, valinit=S_M)
sz_t = Slider(axz_t, 'z_t', 0.1, 1.0, valinit=z_t)
sT = Slider(axT, 'T', 273.0, 500.0, valinit=T)
sS = Slider(axS, 'S', 10.0, 200.0, valinit=S)
sz_c = Slider(axz_c, 'z_c', 0.1, 1.0, valinit=z_c)
sA_t = Slider(axA_t, 'A_t', 0.001, 0.3, valinit=A_t)
sA_c = Slider(axA_c, 'A_c', 0, 3.0, valinit=A_c)





def update(val):
    J = samp.val
    S_N = sfreq.val
    S_M = sS_M.val
    z_t = sz_t.val
    T = sT.val
    S = sS.val
    z_c = sz_c.val
    A_t = sA_t.val
    A_c = sA_c.val
    l.set_ydata((J*(-e*t + J*S_M)*S_N*(S + (A_t*z_t*(-e*t + J*S_N)*(e*t*A_t*z_t*(S_M - S_N)*(e*t - J*S_N) + A_c*z_c*(e*J*t*S_M**2 + e*t*(-e*S*t + (J*S + e*t)*S_N) + J*S_M*(e*S*t + S_N*(-J*S - 3*e*t + J*S_N)))))/(J*(-S_M + S_N)*(e*t*A_t*z_t*(S_M - S_N)*(e*t - J*S_N) - A_c*z_c*(e*t - J*S_M)*(e*S*t - (J*S + e*t - J*S_M)*S_N))*np.sqrt(2*M*np.pi*T*k_B)))*np.sqrt(2*M*np.pi*T*k_B))/(2*e*z_t*(e*t - J*S_N)))
#    l.set_ydata((A_c*z_c*t*(1-(S_N/((J*S_N*np.sqrt(m*T))/(z_t*t)+1)+(A_c*z_c*t)/(A_t*np.sqrt(m*T)))/(S_M*(1-1/((J*S_N*np.sqrt(m*T))/(z_t*t)+1))+S_N/((J*S_N*np.sqrt(m*T))/(z_t*t)+1)+(A_c*z_c*t)/(A_t*J*np.sqrt(m*T)))))/np.sqrt(m*T)+(A_t*z_t*t*(1-1/((J*S_N*np.sqrt(m*T))/(z_t*t)+1)))/np.sqrt(m*T)+S*t)
    fig.canvas.draw_idle()
sfreq.on_changed(update)
samp.on_changed(update)
sS_M.on_changed(update)
sz_t.on_changed(update)
sT.on_changed(update)
sS.on_changed(update)
sz_c.on_changed(update)
sA_t.on_changed(update)
sA_c.on_changed(update)

resetax = plt.axes([0.8, 0.025, 0.1, 0.04])
button = Button(resetax, 'Reset', color=axcolor, hovercolor='0.975')


def reset(event):
    sfreq.reset()
    samp.reset()
    sS_M.reset()
    sz_t.reset()
    sT.reset()
    sS.reset()
    sz_c.reset()
    sA_t.reset()
    sA_c.reset()

button.on_clicked(reset)

rax = plt.axes([0.025, 0.5, 0.15, 0.15], facecolor=axcolor)
radio = RadioButtons(rax, ('red', 'blue', 'green'), active=0)


def colorfunc(label):
    l.set_color(label)
    fig.canvas.draw_idle()
radio.on_clicked(colorfunc)

plt.show()
