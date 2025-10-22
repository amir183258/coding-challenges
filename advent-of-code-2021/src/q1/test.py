with open("input.txt") as f:
    data = f.readlines()

for i in range(len(data)):
    data[i] = int(data[i].strip())

sum = 0
for i in range(1, len(data)):
    if data[i] > data[i - 1]:
        sum += 1

print(sum)
