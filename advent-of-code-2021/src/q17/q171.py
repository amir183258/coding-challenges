import re

if __name__ == "__main__":
    # Read data
    with open("data.txt") as f:
        data = f.readlines()
    data = data[0]
    data = re.findall("\-?\d+", data)
    data = [int(d) for d in data]

    # Extract x and y min and max values 
    xmin, xmax, ymin, ymax = data

    n = -ymin - 1
    ans = n * (n + 1) / 2
    print(ans)



