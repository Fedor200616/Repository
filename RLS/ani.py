import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

# Чтение файла Targets.txt
filename = "Targets.txt"
frames = {}
with open(filename, "r") as f:
    lines = f.readlines()
    for line in lines:
        if "===" in line or line.startswith("Time"):
            continue
        parts = line.strip().split()
        if len(parts) < 4:
            continue
        time = float(parts[0])
        tid = int(parts[1])
        dist = float(parts[2])
        bearing = float(parts[3])
        
        angle_rad = np.radians(360 - bearing)  # перевод в радианы
        x = dist * np.cos(angle_rad)
        y = dist * np.sin(angle_rad)

        if time not in frames:
            frames[time] = []
        frames[time].append((x, y, tid))

sorted_times = sorted(frames.keys())

fig, ax = plt.subplots()
scat = ax.scatter([], [], s=100, c=[], cmap='tab10')
ax.set_xlim(-60, 60)
ax.set_ylim(-60, 60)
ax.set_title("Target Animation")
ax.grid(True)

colors = {}

def update(i):
    time = sorted_times[i]
    points = frames[time]
    xs = [p[0] for p in points]
    ys = [p[1] for p in points]
    ids = [p[2] for p in points]
    col = []
    for tid in ids:
        if tid not in colors:
            colors[tid] = tid
        col.append(colors[tid])
    scat.set_offsets(np.column_stack((xs, ys)))
    scat.set_array(np.array(col))
    ax.set_title(f"Time = {time:.2f}s")
    return scat,

ani = animation.FuncAnimation(fig, update, frames=len(sorted_times), interval=300, repeat=False)
plt.show()