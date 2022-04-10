import math
import numpy as np


class Polynomial:
    def __init__(self):
        data_list = [line.strip() for line in open(f'Input.txt', 'r')]
        self.pol_str = data_list[0]
        self.points = data_list[1].split()
        self.F = lambda x: x[0] ** 2 + x[0] * x[1] + x[1] ** 2 - 3 * x[0] - 6 * x[1]
        self.f = lambda x,y: x ** 2 + x * y + y ** 2 - 3 * x - 6 * y

    def simplex_method(self):
        x1 = float(self.points[0])
        x2 = float(self.points[1])
        gamma = 0.5
        n = len(self.points)
        delta = 1
        p = delta * ((n + 1) ** 0.5 + n - 1) / (n * 2 ** 0.5)
        g = p - delta * (2 ** 0.5 / 2)

        simplex = np.zeros((n + 1, n))
        simplex[0] = x1, x2

        for i in range(1, n + 1):
            for j in range(n):
                if i - 1 == j:
                    simplex[i][j] = simplex[0][j] + p
                else:
                    simplex[i][j] = simplex[0][j] + g

        while True:
            sum_col1, sum_col2 = self.sum_simplex(simplex)
            f_list = [self.F(row) for row in simplex]

            middle_x = [sum_col1 / (n + 1), sum_col2 / (n + 1)]
            max_index = f_list.index(max(f_list))

            r_x = [(sum_col1 - simplex[max_index][0]) * 2 / n - simplex[max_index][0],
                   (sum_col2 - simplex[max_index][1]) * 2 / n - simplex[max_index][1]]

            if self.F(r_x) <= self.F(simplex[max_index]):
                simplex[max_index] = r_x
            else:
                delta *= gamma
                min_index = f_list.index(min(f_list))
                a = [simplex[min_index][0] * (1 - gamma), simplex[min_index][1] * (1 - gamma)]

                for i in range(n + 1):
                    simplex[i] = summ(gamma * simplex[i], a)

            # for i in range(n + 1):
            #     for j in range(n + 1):
            #         if i != j:
            #             print("check = ", np.linalg.norm(sub(simplex[i], simplex[j])), delta)

            sum_col1, sum_col2 = self.sum_simplex(simplex)
            new_x = [sum_col1 / (n + 1), sum_col2 / (n + 1)]

            if np.linalg.norm(sub(new_x, middle_x)) <= 0.00001 and abs(self.F(new_x) - self.F(middle_x)) <= 0.00001:
                return new_x

    def sum_simplex(self, simplex):
        temp = 0
        temp1 = 0
        for i in range(len(self.points) + 1):
            temp += simplex[i][0]
            temp1 += simplex[i][1]
        return temp, temp1

    def jivs_method(self):
        res = [float(self.points[0]), float(self.points[1])]
        x = res
        gamma = 2
        delta = [0.3, 0.3]

        i = 0
        while True:
            e = [0, 1] if i % 2 == 0 else [1, 0]

            new_x = [x[0] + delta[0] * e[0], x[1] + delta[1] * e[1]]
            if self.F(new_x) < self.F(x):
                x = new_x
                new_res = self.sample_search(x, res)
            else:
                new_x = [x[0] - delta[0] * e[0], x[1] - delta[1] * e[1]]
                if self.F(new_x) < self.F(x):
                    x = new_x
                    new_res = self.sample_search(x, res)
                else:
                    new_res = res
                    delta = [delta[0] / gamma, delta[1] / gamma]
            if np.linalg.norm(delta) <= 0.00001 and abs(self.F(new_res) - self.F(res)) <= 0.00001:
                return new_res
            x = res = new_res
            i += 1

    def sample_search(self, base_x, x):
        sample_x = summ(base_x, sub(base_x, x))
        return sample_x if self.F(sample_x) < self.F(base_x) else base_x


def summ(a, b):
    return [x + y for x, y in zip(a, b)]


def sub(a, b):
    return [x - y for x, y in zip(a, b)]


p = Polynomial()
s_res = p.simplex_method()
print(f'x = {s_res}')
j_res = p.jivs_method()
print(f'x = {j_res}')


