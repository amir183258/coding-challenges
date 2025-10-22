class Tree:
    def __init__(self, node):
        self.current_node = node

    def insert_node(self, node):
        self.current_node = node

class Node:
    def __init__(self, value, prev_node):
        self.value = value
        self.prev_node = prev_node

if __name__ == "__main__":
    # Read data and put them into a list
    with open("input.txt") as f:
        data = f.readlines()
    data = [x.strip() for x in data]

    openings = "{[(<"
    valids = ["{}", "()", "<>", "[]"]
    errors = ""
    for d in data:
        tree = Tree(Node(d[0], None))
        for i in range(1, len(d)):
            if d[i] in openings:
                tree.insert_node(Node(d[i], tree.current_node))
            elif tree.current_node.value + d[i] in valids:
                tree.current_node = tree.current_node.prev_node
            else:
                errors += d[i]
                break
    print(errors)
    
    scores = {")": 3, "]": 57, "}": 1197, ">": 25137}
    syntax_error_score = 0
    for e in errors:
        for k, v in scores.items():
            if e == k:
                syntax_error_score += scores[k]

    print(f"Result: {syntax_error_score}")
