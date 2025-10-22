import re

# Hits target function
def hits_target(vx, vy):
    x = y = 0
    while True:
        if x > xmax:
            return False
        if vx == 0 and not xmin <= x <= xmax:
            return False
        if y < ymin:
            return False

        if xmin <= x <= xmax and ymin <= y <= ymax:
            return True

        x += vx
        y += vy

        if vx > 0:
            vx -= 1
        elif vx < 0:
            vx += 1
        vy -= 1




if __name__ == "__main__":
    # Read data
    with open("data.txt") as f:
        data = f.readlines()
    data = data[0]
    data = re.findall("\-?\d+", data)
    data = [int(d) for d in data]

    # Compute x and y ranges
    xmin, xmax, ymin, ymax = data

    # Brute force code
    vy_max = abs(ymin)
    distinct_velocities = 0
    for vx in range(xmax + 1):
        for vy in range(-vy_max, vy_max + 1):
            distinct_velocities += hits_target(vx, vy)
    print(distinct_velocities)
            














def test_get_y():
    assert get_y(6, 1) == 6
    assert get_y(6, 7) == 21



