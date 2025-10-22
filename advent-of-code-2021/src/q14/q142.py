import collections

if __name__ == "__main__":
    # Import data
    with open("input.txt") as f:
        data = f.readlines()

    template = data[0].strip()
    data = [d.strip().split("->") for d in data]
    formulas = collections.defaultdict(set)
    for i in range(2, len(data)):
        formulas[data[i][0].strip()] = data[i][1].strip()

    # Create dictionary of current and next pair elements count
    current_elements = collections.defaultdict(int)
    next_elements = collections.defaultdict(int)

    for i in range(len(template) - 1):
        current_elements[template[i : i + 2]] += 1

    # Compute pairs count in each step
    steps = 40
    for i in range(steps):
        for c in current_elements:
            next_elements[c[0] + formulas[c]] += current_elements[c]
            next_elements[formulas[c] + c[1]] += current_elements[c]
        current_elements = next_elements.copy()
        next_elements = collections.defaultdict(int)
    
    elements = set()
    for f in formulas:
        elements.add(formulas[f])
    elements_count = collections.defaultdict(int)
    for e in elements:
        elements_count[e] = 0
    for c in current_elements:
        for e in elements:
            if e in c and current_elements[c]:
                if c[0] == c[1]:
                    elements_count[e] += current_elements[c] * 2
                else:
                    elements_count[e] += current_elements[c]
    
    for ec in elements_count:
        if elements_count[ec] % 2 == 0:
            elements_count[ec] /= 2
        else:
            elements_count[ec] += 1
            elements_count[ec] /= 2

    print(f"Result: {max(elements_count.values()) - min(elements_count.values())}")





