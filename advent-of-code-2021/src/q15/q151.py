import numpy as np

step = 0
if __name__ == "__main__":
    # Import data into numpy array
    with open("input.txt") as f:
        data = f.readlines()
    data = [[int(x) for x in d.strip()] for d in data]
    data = np.array(data)

    added_nodes = np.zeros((data.shape[0], data.shape[1]), dtype=bool)
    distances = np.ones((data.shape[0], data.shape[1])) * np.inf

    distances[0, 0] = data[0, 0]
    while True:
        # Extract min indices in distances matrix
        min_value = np.inf
        for i in range(distances.shape[0]):
            for j in range(distances.shape[1]):
                if distances[i, j] < min_value and not added_nodes[i, j]:
                    min_value = distances[i, j]
                    min_indices = (i, j)

        # Add min distance node to nodes list
        added_nodes[min_indices] = True

        # Compute neighbors distances
        neighbors = [(min_indices[0] + 1, min_indices[1]),
                     (min_indices[0] - 1, min_indices[1]),
                     (min_indices[0], min_indices[1] + 1),
                     (min_indices[0], min_indices[1] - 1)]
        for n in neighbors:
            if n[0] in range(distances.shape[0]) and n[1] in range(distances.shape[1]) and not added_nodes[n]:
                if distances[n] == np.inf:
                    distances[n] = distances[min_indices] + data[n]
                else:
                    if distances[n] > distances[min_indices] + data[n]:
                        distances[n] = distances[min_indices] + data[n]



        step += 1

        if min_indices == (distances.shape[0] - 1, distances.shape[1] - 1):
            print(distances)
            break
    
    result = distances[-1, -1] - distances[0, 0]
    print(f"Reslut: {result}")




