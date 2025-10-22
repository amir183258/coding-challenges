import numpy as np

def flash(data, i, j, flashes):
    rows = range(data.shape[0])
    cols = range(data.shape[1])
    if i in rows and j in cols and not flashes[i, j]:
        data[i, j] += 1
        if data[i, j] > 9:
            neighbors = ((i - 1, j - 1), (i, j - 1), (i + 1, j - 1), 
                    (i - 1, j), (i + 1, j),  (i - 1, j + 1), (i, j + 1), 
                    (i + 1, j + 1))
            data[i, j] -= 10
            flashes[i, j] = 1
            for m, n in neighbors:
                flash(data, m, n, flashes)
        
if __name__ == "__main__":
    # Open data and store them in numpy array
    with open("input.txt") as f:
        data = f.readlines()
    data = [[int(n) for n in d.strip()] for d in data]
    data = np.array(data)

    steps = 2
    sum_flashes = 0
    for s in range(steps):
        flashes = np.zeros((data.shape[0], data.shape[1]))
        for i in range(data.shape[0]):
            for j in range(data.shape[1]):
                flash(data, i, j, flashes)
        sum_flashes += np.sum(flashes)
    print(data)
    print(sum_flashes)
