import statistics # For median function

if __name__ == "__main__":
    # Read data
    with open("input.txt") as f:
        data = f.readlines()
    data = [d.strip() for d in data]

    # Discard corrupted data, using a new method here
    # This method is like previous question but we 
    # didnt use Node calss; we use a simple list for
    # that duty.
    openings = "{[(<"
    valids = ["{}", "[]", "()", "<>"]
    valid_data = []
    for i in range(len(data)):
        nodes = []
        for s in data[i]:
            if s in openings:
                current_node = s
                nodes.append(s)
            elif current_node + s in valids:
                if len(nodes) > 1:
                    current_node = nodes[-2]
                nodes.pop()
            else:
                nodes = None
                break
        if nodes:
            valid_data.append(nodes)
    valid_data = ["".join(list(reversed(d))) for d in valid_data]

    # Scoring the results
    scores = {"(": 1, "[": 2, "{": 3, "<": 4}
    total_score = 0
    total_scores = []
    for d in valid_data:
        for s in d:
            for k, v in scores.items():
                if s == k:
                    total_score = total_score * 5 + scores[k]
        total_scores.append(total_score)
        total_score = 0

    print(f"Result: {statistics.median(total_scores)}")
