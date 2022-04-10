#include <math.h>
#include <iostream>

using namespace std;

double HookeJeeves() 
{

}

def HookeJeeves(f, x0, e) :
    x = copy(x0)
    increment = [1, 1]
    y = x
    xtemp = x
    a = 2
    success = 0

    while True:
func = f(y[0], y[1])

if f(y[0] + increment[0], y[1]) < func :
    y[0] += increment[0]
    success += 1

    if f(y[0], y[1] + increment[1]) < func :
        y[1] += increment[1]
        success += 1

        if success == 0 :
            if f(y[0] - increment[0], y[1]) < func :
                y[0] -= increment[0]
                success += 1

                if f(y[0], y[1] - increment[1]) < func :
                    y[1] -= increment[1]
                    success += 1

                    if success != 0 :
                        while True :
                            success = 0
                            xtemp[0] = y[0] + (y[0] - x[0])
                            xtemp[1] = y[1] + (y[1] - x[1])

                            if f(xtemp[0], xtemp[1]) < f(y[0], y[1]) :
                                x = y
                                y = xtemp
                            else:
break

                    else:
if math.sqrt(increment[0] * *2 + increment[1] * *2) > e:
increment[0] /= a
increment[1] /= a
else :
    break

    return x


int main() 
{
    int x[2] = { 3, 2 };
    double e = pow(10, -4);
    return 0;
}
double myFunc(int x1,int x2)
{
    return pow(x1, 2) + x1 * x2 + pow(x2, 2) - 3 * x1 - 6 * x2;;
}

//Питон
import math
from copy import copy


def HookeJeeves(f, x0, e) :
    x = copy(x0)
    increment = [1, 1]
    y = x
    xtemp = x
    a = 2
    success = 0

    while True:
func = f(y[0], y[1])

if f(y[0] + increment[0], y[1]) < func :
    y[0] += increment[0]
    success += 1

    if f(y[0], y[1] + increment[1]) < func :
        y[1] += increment[1]
        success += 1

        if success == 0 :
            if f(y[0] - increment[0], y[1]) < func :
                y[0] -= increment[0]
                success += 1

                if f(y[0], y[1] - increment[1]) < func :
                    y[1] -= increment[1]
                    success += 1

                    if success != 0 :
                        while True :
                            success = 0
                            xtemp[0] = y[0] + (y[0] - x[0])
                            xtemp[1] = y[1] + (y[1] - x[1])

                            if f(xtemp[0], xtemp[1]) < f(y[0], y[1]) :
                                x = y
                                y = xtemp
                            else:
break

                    else:
if math.sqrt(increment[0] * *2 + increment[1] * *2) > e:
increment[0] /= a
increment[1] /= a
else :
    break

    return x


    def simplex(f, x0, e) :
    x = copy(x0)
    xtemp = [0, 0]
    vmirror = [0, 0]

    V = [[x[0], x[1]], [0, 0], [0, 0]]
    k = min = max = indexm = indexp = 0
    n = 2
    delta = 1
    y = 0.5

    for i in range(1, n + 1) :
        for j in range(0, n) :
            if (i - j) == 1 :
                V[i][j] = x[j] + delta * (math.sqrt(n + 1) + n - 1) / (n * math.sqrt(2))
            else :
                V[i][j] = x[j] + delta * (math.sqrt(n + 1) - 1) / (n * math.sqrt(2))

                for i in range(0, n + 1) :
                    for j in range(0, n) :
                        x[j] += (1 / (n + 1)) * V[i][j]

                        while True :
                            for i in range(0, n + 1) :
                                func = f(V[i][0], V[i][1])
                                if i == 0 :
                                    max = func

                                    if func >= max :
                                        max = func
                                        indexp = i

                                        for i in range(0, n + 1) :
                                            for j in range(0, n) :
                                                if indexp != i :
                                                    vmirror[j] += (2 / n) * V[i][j]
                                                    if i == n :
                                                        vmirror[j] -= V[indexp][j]

                                                        if f(vmirror[0], vmirror[1]) <= max :
                                                            for j in range(0, n) :
                                                                V[indexp][j] = vmirror[j]
                                                        else:
delta *= y
for i in range(0, n + 1) :
    func = f(V[i][0], V[i][1])
    if i == 0 :
        min = func
        if func <= min :
            min = func
            indexm = i

            for i in range(0, n + 1) :
                for j in range(0, n) :
                    V[i][j] = y * V[i][j] + (1 - y) * V[indexm][j]

                    xtemp = copy(x)
                    x[0] = 0
                    x[1] = 0
                    for i in range(0, n + 1) :
                        for j in range(0, n) :
                            x[j] += (1 / (n + 1)) * V[i][j]

                            if abs(x[0] - xtemp[0]) <= e and abs(x[1] - xtemp[1]) <= e and abs(
                                f(x[0], x[1]) - f(xtemp[0], xtemp[1])) <= e :
                                break
                            else:
k += 1

return x


import math
from copy import copy



def main() :
    func = lambda x1, x2 : math.pow(x1, 2) + x1 * x2 + math.pow(x2, 2) - 3 * x1 - 6 * x2
    x = [3, 2]
    e = math.pow(10, -4)

    ans = simplex(func, x, e)
    print("Симплекс: {0}\t{1}\t{2}".format(ans[0], ans[1], func(ans[0], ans[1])))
    ans = HookeJeeves(func, x, e)
    print("Хук Живс: {0}\t{1}\t{2}".format(ans[0], ans[1], func(ans[0], ans[1])))


    if __name__ == "__main__":
main()
