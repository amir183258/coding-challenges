import collections

if __name__ == "__main__":
    with open("input.txt") as f:
        data = f.readlines()

    template = data[0].strip()
    data = [d.strip().split("->") for d in data]
    formulas = collections.defaultdict(set)
    for i in range(2, len(data)):
        formulas[data[i][0].strip()] = data[i][1].strip()

    steps = 10
    for s in range(steps):
        result = ""
        for i in range(len(template) - 1):
            temp = template[i : i + 2]
            result += (temp[0] + formulas[temp])
        result += temp[1]
        template = result

    elements = set()
    for e in formulas.values():
        elements.add(e)
    elements_count = collections.defaultdict(int)
    for e in elements:
        elements_count[e] = 0
    for r in result:
        elements_count[r] += 1
    print(f"Elements Count: {elements_count}")
    print(f"Result: {max(elements_count.values()) - min(elements_count.values())}")



