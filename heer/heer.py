import numpy as np
from numpy import cos, sin, pi
import matplotlib.pyplot as plt
from matplotlib import animation
import matplotlib

def u(x, t0, L, a, prec=1e-7):
    x = np.asarray(x)
    uu = np.zeros_like(x)
    nn = 0
    while True:
        uu_ = ((-1) ** nn *
               sin((2 * nn + 1) * pi * x / L) *
               cos((2 * nn + 1) * pi * t0 / L) /
               (2 * nn + 1) ** 2)
        uu += uu_
        if np.all(np.abs(uu_ / a) < prec):
            break
        nn += 1
    uu *= 8 * a / pi**2
    return uu


if __name__ == '__main__':# s
   
    matplotlib.use('Qt4Agg')

    L = 1.0  # m
    a = 0.05  # m
    t0 = 0.0  # s
    dt = 0.05 # s
    x = np.linspace(0, L, num=101)
    def anim(i):
        line.set_data(x, u(x, t0 + i * dt, L, a))
        return line,
    fig = plt.gcf()
    line, = plt.plot(x, u(x, t0, L, a, prec=1e-9))
    plt.ylim(-a * 2, a * 2)
    animate = animation.FuncAnimation(fig, anim, range(40), repeat=True, blit=False)
    plt.show()
    #animate.save('string.mp4', fps=90)