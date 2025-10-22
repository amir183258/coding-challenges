import math
import re

def magnitude(s):
    while True:
        if s.isdigit():
            break
        reg = re.search("\[\d+,\d+\]", s)
        i = reg.start()
        j = reg.end()
        reg = reg.group(0)

        n = re.findall("\d+", reg)

        mag = 3 * int(n[0]) + 2 * int(n[1])
        s = s[:i] + str(mag) + s[j:]
    return int(s)

def Split(i, j, s):
    n = int(s[i:j])
    left = str(math.floor(n / 2.0))
    right = str(math.ceil(n / 2.0))

    s = s[:i] + "[" + left + "," + right + "]" + s[j:]
    return s

def explode(i, s):
    # Pick left and right number
    for k in range(i, len(s)):
        if s[k] == ",":
            left = int(s[i + 1:k])
            j = k
        if s[k] == "]":
            right = int(s[j + 1:k])
            break

    # Make exploded pair to 0
    for j in range(i, len(s)):
        if s[j] == "]":
            break
    s = s[:i] + "0" + s[j + 1:]

    # Add left number
    l = i - 1
    while l >= 0:
        if s[l].isdigit():
            j = l - 1
            while j >= 0:
                if not s[j].isdigit():
                    break
                else:
                    j -= 1
            break
        else:
            l -= 1
    if l > 0:
        s = s[:j + 1] + str(int(s[j + 1 : l + 1]) + left) + s[l + 1:]

    for k in range(i, len(s)):
        if s[k] == "0":
            i = k
            break

    # Add right number
    r = i + 1
    while r < len(s):
        if s[r].isdigit():
            j = r + 1
            while j < len(s):
                if not s[j].isdigit():
                    break
                else:
                    j += 1
            break
        else:
            r += 1
    if r < len(s) - 1:
        s = s[:r] + str(int(s[r:j]) + right) + s[j:] 

    return s

def reduce(s):
    # First we have to use explode functoin
    depth = 0
    i = 0
    while True:
        if i >= len(s):
            break
        if s[i] == "[":
            depth += 1
        elif s[i] == "]":
            depth -= 1

        if depth == 5:
            s = explode(i, s)
            depth -= 1
        i += 1

    # Second we have to use split function
    check = False
    i = 0
    while True:
        if i >= len(s):
            break
        if s[i].isdigit():
            for j in range(i + 1, len(s)):
                if not s[j].isdigit():
                    break
            if j != i + 1:
                s = Split(i, j, s)
                check = True
                break
        i += 1
    
    if check:
        return reduce(s)
    else:
        return s

def addition(s1, s2):
    result = "[" + s1 + "," + s2 + "]"


    result = reduce(result)
    return result


if __name__ == "__main__":
    # Read data
    with open("data_slight2.txt") as f:
        data = [d.strip() for d in f.readlines()]

    Sum = data[0]
    for i in range(1, len(data)):
        Sum = addition(Sum, data[i])
    print(Sum)
    print(magnitude(Sum))


# Tests for functions
def test_explode():
    assert explode(4, "[[[[[9,8],1],2],3],4]") == "[[[[0,9],2],3],4]"
    assert explode(12, "[7,[6,[5,[4,[3,2]]]]]") == "[7,[6,[5,[7,0]]]]"
    assert explode(10, "[[6,[5,[4,[3,2]]]],1]") == "[[6,[5,[7,0]]],3]"
    assert explode(10, "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]") == "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]"
    assert explode(24, "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]") == "[[3,[2,[8,0]]],[9,[5,[7,0]]]]"
    assert explode(16, "[[[[0,7],4],[7,[[8,4],9]]],[1,1]]") == "[[[[0,7],4],[15,[0,13]]],[1,1]]"
    assert explode(4, "[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]") == "[[[[0,7],4],[7,[[8,4],9]]],[1,1]]"

def test_Split():
    assert Split(13, 15 , "[[[[0,7],4],[15,[0,13]]],[1,1]]") == "[[[[0,7],4],[[7,8],[0,13]]],[1,1]]"
    assert Split(22, 24, "[[[[0,7],4],[[7,8],[0,13]]],[1,1]]") == "[[[[0,7],4],[[7,8],[0,[6,7]]]],[1,1]]"

def test_magnitude():
    assert magnitude("[[1,2],[[3,4],5]]") == 143
    assert magnitude("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]") == 1384 
    assert magnitude("[[[[1,1],[2,2]],[3,3]],[4,4]]") == 445 
    assert magnitude("[[[[3,0],[5,3]],[4,4]],[5,5]]") == 791 
    assert magnitude("[[[[5,0],[7,4]],[5,5]],[6,6]]") == 1137
    assert magnitude("[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]") == 3488 

