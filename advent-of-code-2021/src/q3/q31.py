import numpy as np

with open("input.txt") as f:
    data = f.readlines()
for i in range(len(data)):
    data[i] = data[i].strip()

sum_of_bits = np.zeros(len(data[0]))
for binary in data:
    for i in range(len(binary)):
        sum_of_bits[i] += int(binary[i])

gamma_rate = "0b"
epsilon_rate = "0b"
for s in sum_of_bits:
    if s > len(data) - s:
        gamma_rate += "1"
        epsilon_rate += "0"
    else:
        gamma_rate += "0"
        epsilon_rate += "1"
print(f"Gamma Rate: {int(gamma_rate, 2)}")
print(f"Epsilon Rate: {int(epsilon_rate, 2)}")
print(f"Result: {int(gamma_rate, 2) * int(epsilon_rate, 2)}")



