class Node:
    def __init__(self, value, prev_node):
        self.value = value
        self.prev_node = prev_node

if __name__ == "__main__":
    # Read data and put them into a list
    with open("input.txt") as f:
        data = f.readlines()
    data = [x.strip() for x in data]

    # Opening and valid chunks
    openings = "{[(<"
    valids = ["{}", "()", "<>", "[]"]
    # Founded syntax errors
    errors = ""
    # We used tree based algorithm here
    for d in data:
        current_node = Node(d[0], None)
        for i in range(1, len(d)):
            if d[i] in openings:
                current_node = Node(d[i], current_node)
            elif current_node.value + d[i] in valids:
                current_node = current_node.prev_node
            else:
                errors += d[i]
                break
    
    # Syntax error scores
    scores = {")": 3, "]": 57, "}": 1197, ">": 25137}
    syntax_error_score = 0
    # Compute final syntax error score
    for e in errors:
        for k, v in scores.items():
            if e == k:
                syntax_error_score += scores[k]

    print(f"Result: {syntax_error_score}")
