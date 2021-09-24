import math
from typing import Tuple
import numpy as np
import random
from time import time
import matplotlib.pyplot as plt
import sys
from matplotlib.font_manager import FontProperties
fp = FontProperties(fname='C:\WINDOWS\Fonts\msgothic.ttc', size=14)


def main(argv: Tuple):
    start = time()
    bnp = Bnp()
    #bnp.create_needle()
    num_times = 3000
    for i in range(num_times):
        bnp.drop()
    bnp.totaling_touch_line()
    pi = bnp.calc()
    result_time = time() - start
    print("π=", pi)
    print("触れた回数:", bnp.touch_line_count, sep="")
    print("経過時間", round(result_time, 3), "秒")

    #x1 = np.arange(0, num_times)
    y1 = bnp.drop_angle

    y2 = np.empty(0)
    for i in range(num_times):
        y2 = np.append(math.sin(random.random() * math.pi), y2)

    fig, ax = plt.subplots(2, 1)
    plt.subplots_adjust(hspace=0.6)

    ax[0].hist(y1, bins=60)
    ax[0].set_ylabel('freq')
    ax[0].set_title('xをランダムに決定しy座標を算出する', FontProperties=fp)
    ax[0].set_xlabel('sinΘ')

    ax[1].hist(y2, bins=60)
    ax[1].set_ylabel('freq')
    ax[1].set_title('Θを0~180°で一様にダンダム', FontProperties=fp)
    ax[1].set_xlabel('sinΘ')
    fig.show()
    plt.savefig("result.png")
    plt.show()


class Bnp():

    needle_length: int  = 5                 # 針の長さl
    line_width: int     = needle_length * 2 # 線の幅w

    def __init__(self):
        self.drop_point = np.empty(0)   # 針の中心と線までの距離d
        self.drop_angle = np.empty(0)   # sinΘ
        self.touch_line_count: int  = 0 # 針が線に触れた数

    def drop(self) -> None:
        self.drop_point = np.append(random.random() * (Bnp.line_width / 2), self.drop_point)
        self.drop_angle = np.append(Bnp.simulation2(), self.drop_angle)  # 0°~180°
        #self.drop_angle = np.append(math.sin(random.random() * (math.pi/4)), self.drop_angle)  # 0°~180°

    def totaling_touch_line(self) -> None:
        """針が線に触れている数を集計"""
        self.touch_line_count = 0
        cu = len(self.drop_angle)
        for i in range(cu):
            h: float = (self.needle_length / 2) * self.drop_angle[i]   # 1/2*l*sinΘ
            if h >= self.drop_point[i]:
                self.touch_line_count = self.touch_line_count + 1

    def calc(self) -> float:
        numberOfTrials = len(self.drop_angle)
        print("回数:", numberOfTrials, sep="")
        return numberOfTrials / self.touch_line_count

    def simulation() -> float:
        """単位円上にランダムに点を置き、一様な分布を用いて
        Θをランダムに決定しsinΘを返す
        """
        r = 1
        x: float = random.random() * r     # 0 <= x <= 1
        y: float = np.sqrt(r**2 - (x**2))   # y = √(1 - x^2)
        sin_theta: float = y / r           # sinΘ = 対辺/斜辺, Θ の対辺 = y, 斜辺は単位円なので 1
        return sin_theta

    def simulation2() -> float:
        """単位円内にランダムに点を置き、一様な分布を用いてΘをランダムに
        決定しsinΘを返す
        """
        radius: float = 0.0
        dy: float = 0.0
        while True:
            dx: float = random.random()
            dy = random.random()
            if dx == 0 and dy == 0:
                continue
            if np.sqrt(dx**2 + dy**2) <= 1:
                radius = np.sqrt(dx**2 + dy**2)
                break
        sin_theta = dy / radius
        return sin_theta


if __name__ == "__main__":
    main(sys.argv)
