import matplotlib.pyplot as plt

def read_coordinates(filename):
    coordinates = []
    with open(filename, 'r') as file:
        for line in file:
            x, y = map(int, line.strip().split(','))
            coordinates.append((x, y))
    return coordinates

def plot_polygon(coordinates):
    coordinates.append(coordinates[0])
    xs, ys = zip(*coordinates) 
    plt.figure(figsize=(6, 6))
    plt.plot(xs, ys, marker='o', linestyle='-', color='b')
    plt.fill(xs, ys, color='skyblue', alpha=0.3)
    
    point_65 = coordinates[218]
    point_359 = coordinates[248]
    
    rect_x_min = min(point_65[0], point_359[0])
    rect_x_max = max(point_65[0], point_359[0])
    rect_y_min = min(point_65[1], point_359[1])
    rect_y_max = max(point_65[1], point_359[1])
    
    rect_x = [rect_x_min, rect_x_max, rect_x_max, rect_x_min, rect_x_min]
    rect_y = [rect_y_min, rect_y_min, rect_y_max, rect_y_max, rect_y_min]
    
    plt.plot(rect_x, rect_y, color='red', linestyle='-', linewidth=2)
    plt.fill(rect_x, rect_y, color='red', alpha=0.2) 
    
    plt.gca().invert_yaxis()

    plt.gca().set_aspect('equal', adjustable='box') 
    plt.title("Polygon with Rectangle in SDL-like Coordinates")
    plt.xlabel("X axis")
    plt.ylabel("Y axis")
    plt.grid(True)
    plt.show()

filename = 'adventofcode.com_2025_day_9_input.txt'
coordinates = read_coordinates(filename)
plot_polygon(coordinates)

