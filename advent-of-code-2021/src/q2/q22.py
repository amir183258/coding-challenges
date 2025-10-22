with open("input.txt") as f:
    data = f.readlines()

movements = []
for d in data:
    temp = d.split()
    temp[1] = int(temp[1].strip())
    movements.append(temp)

horizontal = 0
depth = 0
aim = 0
for m in movements:
    if m[0] == "forward":
        horizontal += m[1]
        if aim != 0:
            depth += aim * m[1]
    elif m[0] == "up":
        aim -= m[1]
    else:
        aim += m[1]

print(f"Horizontal: {horizontal}")
print(f"Depth: {depth}")
print(f"Result: {horizontal * depth}")

