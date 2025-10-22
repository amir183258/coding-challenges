import numpy as np

def flood_fill(i, j, category):
    if nines[i, j] != 0:
        return
    nines[i, j] = category
    flood_fill(i + 1, j, category)
    flood_fill(i - 1, j, category)
    flood_fill(i, j - 1, category)
    flood_fill(i, j + 1, category)

if __name__ == "__main__":
    # Read data and put in numpy array
    with open("input.txt") as f:
        data = f.readlines()
    data = [[int(s) for s in x.strip()] for x in data]
    data = np.array(data)

    # Create nines matrix to detect basins boundary
    nines  = np.ones((data.shape[0] + 2, data.shape[1] + 2)) * 9
    nines[1 : data.shape[0] + 1, 1 : data.shape[1] + 1] = data

    for i in range(nines.shape[0]):
        for j in range(nines.shape[1]):
            if nines[i, j] == 9:
                nines[i, j] = 1
            else:
                nines[i, j] = 0

    # We can use flood_fill function now.
    category = 10 # Initial category
    classes = {}
    for i in range(nines.shape[0]):
        for j in range(nines.shape[1]):
            if nines[i, j] == 0:
                category += 1
                classes[category] = 0

            flood_fill(i, j, category)

    # Count each class
    for k, v in classes.items():
        for i in range(nines.shape[0]):
            for j in range(nines.shape[1]):
                if nines[i, j] == k:
                    classes[k] += 1

    # Compute result
    # First we sort values
    classes_sorted_values = list(reversed(sorted(list(classes.values()))))
    # We need 3 maximum values
    result = 1
    for i in range(3):
        result *= classes_sorted_values[i]

        
    print(f"Result: {result}")




