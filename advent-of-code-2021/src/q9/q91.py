import numpy as np

if __name__ == "__main__":
    # Read data from file
    with open("input.txt") as f:
        data = f.readlines()
    # Extract digits
    data = [[int(s) for s in x.strip()] for x in data]
    # Convert list to numpy array for faster calculations
    data = np.array(data)

    # Create filter
    min_numbers = []
    # Define boundry for valid indices
    boundry_i = range(data.shape[0])
    boundry_j = range(data.shape[1])

    for i in range(data.shape[0]):
        for j in range(data.shape[1]):
            temp = []
            filter_index_i = [i - 1, i, i + 1, i, i]
            filter_index_j = [j, j, j, j - 1, j + 1]
            filter_index_i_valid = [x in boundry_i for x in filter_index_i]
            filter_index_j_valid = [x in boundry_j for x in filter_index_j]
            for m, n in zip(range(len(filter_index_i)), range(len(filter_index_j))):
                if filter_index_i_valid[m] and filter_index_j_valid[n]:
                    temp.append(data[filter_index_i[m], filter_index_j[n]])
            test = 0
            for t in temp:
                if t == data[i, j]:
                    test += 1
            if min(temp) == data[i, j] and test == 1:
                min_numbers.append(data[i, j] + 1)

    print(f"Result: {sum(min_numbers)}")
