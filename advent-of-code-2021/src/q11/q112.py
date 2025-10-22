import numpy as np

def flash(flashes):
    for i in range(flashes.shape[0]):
        for j in range(flashes.shape[1]):
            if flashes[i, j]:
                data[i, j] -= 10000
                neighbors = ((i - 1, j - 1), (i, j - 1), (i + 1, j - 1),
                        (i - 1, j), (i + 1, j), (i - 1, j + 1), (i, j + 1),
                        (i + 1, j + 1))
                for m, n in neighbors:
                    if m in range(flashes.shape[0]) and n in range(flashes.shape[1]):
                        data[m, n] += 1

if __name__ == "__main__":
    with open("input.txt") as f:
        data = f.readlines()
    data = [[int(n) for n in d.strip()] for d in data]
    data = np.array(data)

    print(f"Before any steps:\n{data}")
    steps = 1000
    for s in range(steps):
        data += 1
        flashes = data > 9
        while True:
            flash(flashes)
            flashes = data > 9
            if np.sum(flashes) == 0:
                break
        for i in range(data.shape[0]):
            for j in range(data.shape[1]):
                if data[i, j] < 0:
                    data[i, j] = 0
        if np.sum(data) == 0:
            print(f"After step {s + 1}:\n{data}")
            break


                    
