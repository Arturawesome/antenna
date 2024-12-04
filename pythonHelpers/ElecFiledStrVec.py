"""
Python script to generate input signal that hits antenna

# plate of the signal 1.5x+0.5y+z−5

def get_elliptical_signal() - main funtion for signal generation

def plot_signal_and_planes(signal) - function for plotting the signal plate and antenna plate

"""
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def get_elliptical_signal(num_samples=100, time= 2,  time_steps=100, noise_std=0.075):

    np.random.seed(42)
    t = np.linspace(0, time * np.pi, time_steps)
    signals = []

    # plate of the signal 1.5x+0.5y+z−5
    normal = np.array([1.5, 0.5, 1])

    point_in_plate = np.array([2, 2, 5 - 1.5 * 2 - 0.5 * 2]) # point in the 1.5x+0.5y+z−5


    # basis
    basis1 = np.array([1, 0, -1.5])
    basis2 = np.cross(normal, basis1)

    basis1 /= np.linalg.norm(basis1)
    basis2 /= np.linalg.norm(basis2)

    for _ in range(num_samples):
        A1 = np.random.uniform(0.5, 1.0)
        A2 = np.random.uniform(0.5, 1.0)
        phi1 = np.random.uniform(0, 2 * np.pi)
        phi2 = np.random.uniform(0, 2 * np.pi)

        godograph = (point_in_plate +
                      A1 * np.cos(t + phi1)[:, None] * basis1 +
                      A2 * np.sin(t + phi2)[:, None] * basis2)

        godograph += np.random.normal(0, noise_std, size=godograph.shape)
        signals.append(godograph)

    return np.array(signals)


def plot_signal_and_planes(signals, num_samples):
    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection='3d')
    for i in range(num_samples):
        signal = signals[i]
        E_x, E_y, E_z = signal[:, 0], signal[:, 1], signal[:, 2]
        ax.plot(E_x, E_y, E_z)

    # plane of the signal
    xx1, yy1 = np.meshgrid(np.linspace(0, 3, 10), np.linspace(0, 3, 10))
    zz1 = 5 - 1.5 * xx1 - 0.5 * yy1
    # !!!!!!!!!!!!!!!!!!!
    # set the plane of antena
    xx2, yy2 = np.meshgrid(np.linspace(0, 3, 10), np.linspace(0, 3, 10))
    zz2 = 1 - xx2 - yy2
    ax.plot_surface(xx1, yy1, zz1, alpha=0.3, color="orange")
    ax.plot_surface(xx2, yy2, zz2, alpha=0.3, color="skyblue")


    ax.set_xlabel("E_x")
    ax.set_ylabel("E_y")
    ax.set_zlabel("E_z")
    plt.savefig("Figs/Fig1.pdf")

def save_signal(signals, num_samples, filename):
    with open(filename, "w") as file:
        file.write("E_x\tE_y\tE_z\n")  # Заголовок
        for sample in range(num_samples):
            signal = signals[sample]
            for row in signal:
                file.write(f"{row[0]:.6f}\t{row[1]:.6f}\t{row[2]:.6f}\n")


time_steps = 1000
signals = get_elliptical_signal(num_samples=100, time = 2, time_steps=time_steps)

plot_signal_and_planes(signals, 50)
save_signal(signals, 100, "signals.txt")






















