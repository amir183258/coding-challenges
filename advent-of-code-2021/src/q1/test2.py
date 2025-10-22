with open("input.txt") as f:
    data = f.readlines()

for i in range(len(data)):
    data[i] = int(data[i].strip())

print(data)

sum_increases = 0
for i in range(len(data) - 2):
    A = sum(data[i : i + 3])
    B = sum(data[i + 1 : i + 4])
    if B > A:
        sum_increases += 1

print(sum_increases)
