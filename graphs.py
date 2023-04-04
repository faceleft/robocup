import matplotlib.pyplot as plt
import numpy as np
V = 12
r = 6

def maxpower(V, r, x):
    I = ((V/2)/(r+x))
    Ur = r*I
    return(Ur/(2**0.5))**2 / r
def stay(V, r ,x):
    return (V**2)/(2*x)

x = np.linspace(1,100, 100)
y1 = [maxpower(V, r ,i) for i in x]
y2 = [stay(V, r ,i) for i in x]
y3 = [maxpower(V, r , i)/stay(V, r , i)*100 for i in x]

plt.plot(x,y1)
plt.plot(x,y2)
plt.plot(x,y3)
plt.show()