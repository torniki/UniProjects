import math
from copy import copy
def grad_x1(x1, x2):
    return 3*pow(x1,2)+pow(x2,3) - 3 * x2
#Частная производная по x2
def grad_x2(x1, x2):
    return pow(x1,3) + 3*pow(x2,2) -3 *x1
    #return 8 * x1 * x2 - 10 * x1 + 2 * x2
    # f(x2) = 8*x1*x2 -10*x1 + 2*x2
def Phi(f, a, x1, x2, d1, d2):
    return f(x1 - a * d1, x2 - a * d2)
def Gold_Ratio(f, e, a, b, x1, x2, d1, d2):
    y = a + (3 - math.sqrt(5)) / 2 * (b - a)
    z = a + b - y
    while True:
        if Phi(f, y, x1, x2, d1, d2) <= Phi(f, z, x1, x2, d1, d2):
            b = z
            z = y
            y = a + b - y
        elif Phi(f, y, x1, x2, d1, d2) > Phi(f, z, x1, x2, d1, d2):
            a = y
            y = z
            z = a + b - z
        if abs(b - a) > e:
            break
    return (a + b) / 2
def cauchy(f, x0, e):
    x = copy(x0)
    d = [ 0, 0 ]
    while True:
        d[0] = grad_x1(x[0], x[1])
        d[1] = grad_x2(x[0], x[1])
        a = Gold_Ratio(f, e, 0, 0.09, x[0], x[1], d[0], d[1])
        #Общая итерационная формула
        for i in range(0, 2):
            x[i] -= a * d[i]
        if math.sqrt(2 * math.pow(d[0], 2)) <= e:
            break
    return x
if __name__ == "__main__":
    func = lambda x1,x2: 2*pow(x1,3) + x1*pow(x2,2) - 5*pow(x1,2)+pow(x2,2)
    x = [0.3,0.5]
    e = 10e-4
    ans = cauchy(func, x, e)
    print("Коши: {0}\t{1}\t{2}".format(ans[0], ans[1], func(ans[0], ans[1])))
