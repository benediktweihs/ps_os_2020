from exercise07.converter import convert
import matplotlib.pyplot as plt
import numpy as np

def plotTimes(names, filename):
    c = 0
    for name in names:
        data = np.array(convert(name, "txt", ","), dtype=float)
        if c==0: plt.plot(1e-11*data[0], "ro", markersize=1)
        else: plt.plot(1e-11*data[0], "ko", markersize=1)
        c+=1
    plt.savefig(filename)


if __name__ == "__main__":
    programs = ["task1", "task2"]
    names = ["times"+p for p in programs]
    plotTimes(names, "TimesFirst.pdf")

    programs = ["task3", "task3_atomic"]
    names = ["times"+p for p in programs]
    plotTimes(names, "TimesSecond.pdf")

