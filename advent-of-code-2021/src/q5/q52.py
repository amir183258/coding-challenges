import numpy as np

class Line:
    """Line can be horizontal or vertical"""

    def __init__(self, points):
        self.point1 = (points[0][0], points[0][1])
        self.point2 = (points[1][0], points[1][1])

        # Define coordinates
        self.x1 = self.point1[0]
        self.y1 = self.point1[1]
        self.x2 = self.point2[0]
        self.y2 = self.point2[1]

        # Line is horizontal or vertical
        if self.x1 == self.x2:
            self.mode = "vertical"
        elif self.y1 == self.y2:
            self.mode = "horizontal"
        else:
            self.mode = "oblique"
    
    def get_points(self):
        return (self.point1, self.point2)

    def get_mode(self):
        return self.mode


# Read data file
with open("input.txt") as f:
    data = f.readlines()

# Extract lines
data = [d.strip().split("->") for d in data]
for i in range(len(data)):
    for j in range(len(data[i])):
        data[i][j] = data[i][j].split(",")
        for k in range(len(data[i][j])):
            data[i][j][k] = int(data[i][j][k].strip())

# Create Line objects
lines = []
for d in data:
    line = Line(d)
    lines.append(line)

# Create Screen
coordinates_x = [l.x1 for l in lines] + [l.x2 for l in lines]
coordinates_y = [l.y1 for l in lines] + [l.y2 for l in lines]

max_x = max(coordinates_x)
min_x = min(coordinates_x)
max_y = max(coordinates_y)
min_y = min(coordinates_y)

screen = np.zeros((max_y - min_y + 1, max_x - min_x + 1))

print(max_x, max_y)
print(min_x, min_y)
print(screen.shape)

# Compute overlaps
for line in lines:
    if line.get_mode() == "horizontal":
        y = -min_y + line.y1 # or line.y2
        x1 = -min_x + min(line.x1, line.x2)
        x2 = -min_x + max(line.x1, line.x2)
        for xi in range(x1, x2 + 1):
            screen[y, xi] += 1
    elif line.get_mode() == "vertical":
        x = -min_x + line.x1 # or line.x2
        y1 = -min_y + min(line.y1, line.y2)
        y2 = -min_y + max(line.y1, line.y2)
        for yi in range(y1, y2 + 1):
            screen[yi, x] += 1
    else:
        m = (line.y2 - line.y1) / (line.x2 - line.x1)
        print(m)
        if m == 1:
            x1 = -min_x + min(line.x1, line.x2)
            x2 = -min_x + max(line.x1, line.x2)
            y1 = -min_y + min(line.y1, line.y2)
            y2 = -min_y + max(line.y1, line.y2)
            for (xi, yi) in zip(range(x1, x2 + 1), range(y1, y2 + 1)):
                    screen[yi, xi] += 1
        else:
            x1 = -min_x + min(line.x1, line.x2)
            x2 = -min_x + max(line.x1, line.x2)
            y1 = -min_y + max(line.y1, line.y2)
            y2 = -min_y + min(line.y1, line.y2)
            for (xi, yi) in zip(range(x1, x2 + 1), range(y1, y2 - 1, -1)):
                screen[yi, xi] += 1




print(len(lines))
print(screen)

print(np.sum(screen >= 2))
