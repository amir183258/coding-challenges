import re
import numpy as np
import queue

def find_equal_points(first, second):
    number = 0
    temp = []
    for i in range(len(first)):
        for j in range(len(first[i])):
            for k in range(len(second)):
                for l in range(len(second[k])):
                    if first[i][j] == second[k][l]:
                        temp.append(((o[0], i, j + i + 1), (o[1], k, l + k + 1)))
                        number += 1
                    if number == 2:
                        return temp

def addEdgesToGraph():
    for i in range(graph.shape[0]):
        for j in range(graph.shape[1]):
            if graph[i, j]:
                adj[i].append(j)

def computeShortestPathForRequiredNodes():
    destinationNode = 0
    paths = []
    for sourceNode in requiredNodes:
        paths.append(printShortestDistance(adj, sourceNode, destinationNode, v))
    return paths

def printShortestDistance(adj, s, dest, v):
     
    pred=[0 for i in range(v)]
    dist=[0 for i in range(v)];
  
    if (BFS(adj, s, dest, v, pred, dist) == False):
        print("Given source and destination are not connected")
  
    path = []
    crawl = dest;
    crawl = dest;
    path.append(crawl);
     
    while (pred[crawl] != -1):
        path.append(pred[crawl]);
        crawl = pred[crawl];
     
    return list(reversed(path))

def BFS(adj, src, dest, v, pred, dist):
 
    queue = []
  
    visited = [False for i in range(v)];
  
    for i in range(v):
 
        dist[i] = 1000000
        pred[i] = -1;
     
    visited[src] = True;
    dist[src] = 0;
    queue.append(src);
  
    while (len(queue) != 0):
        u = queue[0];
        queue.pop(0);
        for i in range(len(adj[u])):
         
            if (visited[adj[u][i]] == False):
                visited[adj[u][i]] = True;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.append(adj[u][i]);
  
                if (adj[u][i] == dest):
                    return True;
  
    return False;

def computeTransformations():
    transformations = []
    for p in paths:
        temp = []
        for i in range(len(p) - 1):
            temp.append((p[i], p[i + 1]))
        transformations.append(temp)
    return transformations

def executeTransformations(i):
    if i != 0:
        for t in transformations:
            if t[-1][-1] == i:
                transformation = t
        for t in transformation:
            transformCoordinates(t, i)

def transformCoordinates(t, i):
    point = points[i]
    if t in transformingParameters:
        transformIndex = transformingParameters.index(t)
        transformedCoordinate =  \
                        np.matmul(parameters[transformIndex][1][0], point) + \
                        parameters[transformIndex][1][1]

    else:
        transformIndex = reversedTransformingParameters.index(t)
        transformedCoordinate =  \
                        np.matmul(np.linalg.inv(parameters[transformIndex][1][0]), point - \
                        parameters[transformIndex][1][1])

    points[i] = transformedCoordinate

def executeRotations(i):
    if i != 0:
        for t in reversedTransformations:
            if t[0][0] == i:
                transformation = t
        for t in transformation:
            rotationCoordinates(t, i)

def rotationCoordinates(t, i):
    point = points[i]
    if t in transformingParameters:
        transformIndex = transformingParameters.index(t)
        transformedCoordinate =  \
                        np.matmul(parameters[transformIndex][1][0], point)

    else:
        transformIndex = reversedTransformingParameters.index(t)
        transformedCoordinate =  \
                        np.matmul(np.linalg.inv(parameters[transformIndex][1][0]), point)

    points[i] = transformedCoordinate

if __name__ == "__main__":
    # Read data
    with open("data.txt") as f:
        temp = f.readlines()
    temp = [t.strip() for t in temp]

    data = []
    for t in temp:
        if t[0:3] == "---":
            temp2 = []
            continue
        x = re.findall("\-?\d+", t)
        if x:
            temp2.append((int(x[0]), int(x[1]), int(x[2])))
        if not x or t == temp[-1]:
            data.append(temp2)

    # Compute distances
    distances = []
    for s in range(len(data)):
        distance = []
        for i in range(len(data[s]) - 1):
            d = []
            for j in range(i + 1, len(data[s])):
                d.append((data[s][i][0] - data[s][j][0]) ** 2 + \
                          (data[s][i][1] - data[s][j][1]) ** 2 + \
                          (data[s][i][2] - data[s][j][2]) ** 2)
            distance.append(d)
        distances.append(distance)

    #for i in range(len(distances)):
    #    print(f"Scanned {i}:")
    #    for j in range(len(distances[i])):
    #        print(f"Distance {j}: ")
    #        print(distances[i][j])
    
    # Compute overlaps
    overlap_matrix = np.zeros((len(distances), len(distances)))
    for s in range(len(distances)):
        for i in range(len(distances[s])):
            for j in range(len(distances[s][i])):

                for k in range(s + 1, len(distances)):
                    for ki in range(len(distances[k])):
                            for kj in range(len(distances[k][ki])):
                                if distances[s][i][j] == distances[k][ki][kj]:
                                    overlap_matrix[s, k] += 1

    overlaps = []
    for i in range(overlap_matrix.shape[0]):
        for j in range(overlap_matrix.shape[1]):
            if overlap_matrix[i, j] >= 66:
                overlaps.append((i, j))
    
    # Read rotation matrices
    with open("rotations.txt") as f:
        rotations_raw = f.readlines()
    rotations_raw = [r.strip().split("\t") for r in rotations_raw]
    
    number_of_rotations = 24
    rotations = np.zeros((number_of_rotations, 3, 3))

    k = 0
    i = 0
    for r in rotations_raw:
        if len(r) == 3:
            rotations[k, i, 0:3] = [int(temp) for temp in r]
            i += 1
        else:
            k += 1
            i = 0

    # Compute transformation parameters for overlaps.
    equal_points = []
    for o in overlaps:
        first = distances[o[0]]
        second = distances[o[1]]
        temp = find_equal_points(first, second)
        equal_points.append(temp)
    #print(equal_points)
    #print(len(equal_points))

    parameters = []
    for e in equal_points:

        for r in rotations:
            delta1 = np.matmul(r, np.array(data[e[0][1][0]][e[0][1][1]]))
            delta2 = np.matmul(r, np.array(data[e[0][1][0]][e[0][1][2]]))

            T1 = -(delta1 - np.array(data[e[0][0][0]][e[0][0][1]]))
            T2 = -(delta2 - np.array(data[e[0][0][0]][e[0][0][1]]))

            if ((delta2 + T1) == (np.array(data[e[0][0][0]][e[0][0][2]]))).all():
                parameters.append(((e[0][1][0], e[0][0][0]), (r, T1)))

            if ((delta1 + T2) == (np.array(data[e[0][0][0]][e[0][0][2]]))).all():
                parameters.append(((e[0][1][0], e[0][0][0]), (r, T2)))
            
    transformingParameters = []
    for p in parameters:
        transformingParameters.append(p[0])
    reversedTransformingParameters = []
    for t in transformingParameters:
        reversedTransformingParameters.append(tuple(reversed(t)))
    
    print(equal_points)
    print(len(equal_points))
    print(parameters)
    graph = np.zeros((len(data), len(data)))
    for i in range(len(parameters)):
        graph[parameters[i][0]] = 1
        graph[tuple(reversed(parameters[i][0]))] = -1


    print(graph)

    v = graph.shape[0]
    adj = [[] for i in range(v)]
    addEdgesToGraph()

    requiredNodes= list(range(1, len(data)))
    paths = computeShortestPathForRequiredNodes()
    reversedTransformations = computeTransformations()
    paths = [list(reversed(p)) for p in paths]
    transformations = computeTransformations()

    print(paths)
    print(transformations)
    print(reversedTransformations)

    # Execute transformations
    points = []
    for d in range(len(data)):
        points.append(np.array([0, 0, 0]))

    for i in range(len(data)):
        executeTransformations(i)

    for i in range(len(data)):
        executeRotations(i)
    for i in range(len(points)):
        points[i] = -points[i]
    print(points)

    # Compute distances
    distances = np.zeros((len(points), len(points)))
    for i in range(distances.shape[0]):
        for j in range(distances.shape[1]):
            distances[i, j] = abs(points[j][0] - points[i][0]) + \
                    abs(points[j][1] - points[i][1]) + \
                    abs(points[j][2] - points[i][2])
    print(np.max(np.abs(distances)))

            

