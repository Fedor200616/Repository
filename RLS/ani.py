import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

# Чтение файла Targets.txt
filename = r"C:\Users\I\source\repos\Repository\RLS\Targets.txt"
if not filename.endswith(".txt"):
    raise ValueError("Файл должен иметь расширение .txt")
frames = {}
with open(filename, "r") as f:
    lines = f.readlines()
    for line in lines:
        if "===" in line or line.startswith("Time"):
            continue
        parts = line.strip().split()
        if len(parts) < 4:
            continue
        time = float(parts[0].replace(',', '.'))
        tid = int(parts[1].replace(',', '.'))
        dist = float(parts[2].replace(',', '.'))
        bearing = float(parts[3].replace(',', '.'))
        #dist = float(parts[2])
        #bearing = float(parts[3])
        
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
ax.set_aspect('equal', adjustable='box')
ax.set_title("Target Animation")
ax.grid(True)
circle = plt.Circle((0, 0), 50, color='gray', fill=False, linestyle='--')
ax.add_patch(circle)

colors = {}

trails = {}  # Словарь для хранения истории точек по id
lines = {}   # Словарь для линий

def update(i):
    time = sorted_times[i]
    points = frames[time]
    for p in points:
        x, y, tid = p
        if tid not in trails:
            trails[tid] = []
            lines[tid], = ax.plot([], [], '-', linewidth=1)
        trails[tid].append((x, y))

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
    for tid in trails:
        trail_x = [pt[0] for pt in trails[tid]]
        trail_y = [pt[1] for pt in trails[tid]]
        lines[tid].set_data(trail_x, trail_y)
    return scat,

ani = animation.FuncAnimation(fig, update, frames=len(sorted_times), interval=100, repeat=False)
plt.show()