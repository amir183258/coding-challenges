

if __name__ == "__main__":
    with open("input.txt") as f:
        data = f.readline()
    data = [int(x) for x in data.split(",")]
    print(data)

    ages = [0] * 9
    for d in data:
        ages[d] += 1
    print(ages) 

    days = 256
    for day in range(days):
        ages_6_8 = ages[0]
        ages[0] = 0
        for i in range(len(ages) - 1):
            ages[i] += ages[i + 1]
            ages[i + 1] = 0
        ages[6] += ages_6_8
        ages[8] += ages_6_8
    print(sum(ages))

        
