def most_common(l, which_bit = 0, mode = "m"):
    bits_sum = 0
    for b in l:
        bits_sum += int(b[which_bit])

    if bits_sum >= len(l) - bits_sum:
        if mode == "m":
            result = [x for x in l if int(x[which_bit]) == 1]
        else:
            result = [x for x in l if int(x[which_bit]) == 0]
    else:
        if mode == "m":
            result = [x for x in l if int(x[which_bit]) == 0]
        else:
            result = [x for x in l if int(x[which_bit]) == 1]
    
    which_bit += 1

    if(len(result) == 1):
        return result
    return most_common(result, which_bit, mode)

# Main
with open("input.txt") as f:
    data = f.readlines()
for i in range(len(data)):
    data[i] = data[i].strip()

oxygen_generator_rating = most_common(data)[0]
CO2_scrubber_rating = most_common(data, mode = "l")[0]

print(f"Oxygen Generator Rating: {int(oxygen_generator_rating, 2)}")
print(f"CO2 Scrubber Rating: {int(CO2_scrubber_rating, 2)}")
print(f"Result: {int(oxygen_generator_rating, 2) * int(CO2_scrubber_rating, 2)}")
