import numpy as np

def fold(screen, fold_line, screen_range):

    i = 1 
    print(int(fold_line[1]))
    result = np.zeros((int(fold_line[1]), screen.shape[1]))
    screen_range[1][1] += 1
    while True:
        if int(fold_line[1]) + i in range(*screen_range[1]) and \
                int(fold_line[1]) - 1 in range(*screen_range[1]):
                    result[int(fold_line[1]) - i] = \
                            screen[int(fold_line[1]) - i] + \
                            screen[int(fold_line[1]) + i]
                    i += 1
        else:
            break
    return result
                    
if __name__ == "__main__":
    # Open a file and seperate data
    with open("input.txt") as f:
        data = f.readlines()
    folds = []

    while True:
        temp = data.pop()
        if temp != "\n":
            folds.append(temp.strip())
        else:
            break
    coordinates = [[int(x) for x in d.split(",")] for d in data]
    coordinates = np.array(coordinates)
    folds = [f.split()[2].split("=") for f in reversed(folds)]
   
   # Compute screen range for displaying screen
    screen_range = [[np.min(coordinates[:, 0]), np.max(coordinates[:, 0])],
        [np.min(coordinates[:, 0]), np.max(coordinates[:, 1])]]

    # Create screen
    # We add 1 to ranges because they start from 0
    screen = np.zeros((screen_range[1][1] - screen_range[1][0] + 1,
        screen_range[0][1] - screen_range[0][0] + 1))
    
    # Mark dots in screen
    for c in coordinates:
        screen[c[1], c[0]] = True

    print(list(reversed(screen_range)))
    screen = fold(np.transpose(screen), folds[0], list(reversed(screen_range)))

    # Compute result
    dots = 0
    for i in range(screen.shape[0]):
        for j in range(screen.shape[1]):
            if screen[i, j]:
                dots += 1
    print(folds)
    
    print(f"Result: {dots}")


