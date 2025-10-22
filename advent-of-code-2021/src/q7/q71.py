import math

def cost(data, alpha):
    total_cost = 0
    for d in data:
        total_cost += math.fabs(d - alpha)
    return total_cost



if __name__ == "__main__":
    with open("input.txt") as f:
        data = f.readline()
    data = [int(d) for d in data.split(",")]

    
    min_cost = cost(data, 0)
    min_alpha = 0
    for i in range(min(data), max(data) + 1):
        cost_i = cost(data, i)
        if cost_i < min_cost:
            min_cost = cost_i
            min_alpha = i

    print(min_cost)
    print(min_alpha)

        
