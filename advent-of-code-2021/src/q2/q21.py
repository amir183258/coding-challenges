with open("input.txt") as f:
    data = f.readlines()

movements = []
for d in data:
    temp = d.split()
    temp[1] = int(temp[1].strip())
    movements.append(temp)

depth = 0
horizontal = 0
for m in movements:
    if m[0] == "forward":
        horizontal += m[1]
    elif m[0] == "up":
        depth -= m[1]
    else:
        depth += m[1]

print(f"Horizontal: {horizontal}")
print(f"Depth: {depth}")
print(f"Result: {depth * horizontal}")

