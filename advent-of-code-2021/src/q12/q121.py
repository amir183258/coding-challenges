import collections
if __name__ == "__main__":
    with open("input.txt") as f:
        data = f.readlines()
    edges = collections.defaultdict(set)
    for l in data:
        src, dst = l.strip().split("-")
        edges[src].add(dst)
        edges[dst].add(src)

    all_paths = set() # Cant use {}; it creates an empty dict.
    todo = [("start", )]
    while todo:
        path = todo.pop()

        if path[-1] == "end":
            all_paths.add(path)
            continue
        
        for cand in edges[path[-1]]:
            if not cand.islower() or cand not in path:
                todo.append((*path, cand))

    print(f"Result: {len(all_paths)}")
