import numpy as np
import heapq


def next_p(x, y):
    yield x - 1, y
    yield x + 1, y
    yield x, y - 1
    yield x, y + 1

if __name__ == "__main__":
    with open("input.txt") as f:
        data = f.readlines()
    data = [[int(x) for x in d.strip()] for d in data]
    data = np.array(data)

    # Here we have to create new data
    repeats = np.zeros((5, 5))
    for i in range(repeats.shape[0]):
        for j in range(repeats.shape[1]):
            repeats[i, j] = i + j
    temp = np.zeros((data.shape[0] * 5, data.shape[1] * 5))
    for i in range(temp.shape[0]):
        for j in range(temp.shape[1]):
            i_repeats = int(i / data.shape[0])
            j_repeats = int(j / data.shape[1])

            i_data = i % data.shape[0]
            j_data = j % data.shape[1]

            temp[i, j] = data[(i_data, j_data)] + repeats[(i_repeats, j_repeats)]
            if temp[i, j] != 9:
                temp[i, j] %= 9
    data = temp




    coords = {}
    for y in range(data.shape[0]):
        for x in range(data.shape[1]):
            coords[(x, y)] = data[x, y]

    last_x, last_y = max(coords)

    best_at: dict[tuple[int, int], int] = {}

    todo = [(0, (0, 0))]
    while todo:
        cost, last_coord = heapq.heappop(todo)

        if last_coord in best_at and cost >= best_at[last_coord]:
            continue
        else:
            best_at[last_coord] = cost

        if last_coord == (last_x, last_y):
            print(cost)
            break

        for cand in next_p(*last_coord):
            if cand in coords:
                todo.append((cost + coords[cand], cand))
    print(best_at[(last_x, last_y)])

