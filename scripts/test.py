import mpl_toolkits.mplot3d as p3d
import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_xlim(0, 255)
ax.set_ylim(0, 255)
ax.set_zlim(0, 255)
ax.set_xticks(np.linspace(0, 255, 5))
ax.set_yticks(np.linspace(0, 255, 5))
ax.set_zticks(np.linspace(0, 255, 5))
ax.grid(True)
ax.scatter(xs=100, ys=50, zs=50, zdir='z',depthshade="true", c='r', marker='o')
plt.show()
