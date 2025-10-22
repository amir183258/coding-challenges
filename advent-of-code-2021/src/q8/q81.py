if __name__ == "__main__":
    with open("input.txt") as f:
        data = f.readlines()

    data = [x.split("|") for x in data]
    data = [x[1].split() for x in data]
    data = [x for d in data for x in d]

    unique_numbers = [2, 4, 3, 7]

    sum = 0
    for d in data:
        if len(d) in unique_numbers:
            sum += 1
    print(f"Result: {sum}")
