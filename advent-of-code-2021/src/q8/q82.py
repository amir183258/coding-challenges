import re

class Signal:
    def __init__(self, signals, digits):
        self.signals = signals
        self.decode = {"a": None, "b": None, "c": None,
                "d": None, "e": None, "f": None, "g": None}
        self.digits = digits

    def find_a_segment(self):
        for s in self.signals:
            if len(s) == 2:
                digit_1 = s
            elif len(s) == 3:
                digit_7 = s

        self.decode["a"] = re.search("[^" + digit_1 + "]", digit_7).group(0)
    def find_g_segment(self):
        digits_069 = []
        for s in self.signals:
            if len(s) == 4:
                digit_4 = s
            elif len(s) == 6:
                digits_069.append(s)
        digit_4 = digit_4 + self.decode["a"]
        for d in digits_069:
            temp = re.findall("[^" + digit_4 + "]", d)
            if len(temp) == 1:
                self.decode["g"] = temp[0]
    
    def find_e_segment(self):
        for s in self.signals:
            if len(s) == 4:
                digit_4 = s
            elif len(s) == 7:
                digit_8 = s
        digit_4 += self.decode["a"] + self.decode["g"]
        self.decode["e"] = re.search("[^" + digit_4 + "]", digit_8).group(0)

    def find_c_segment(self):
        digits_069 = []
        for s in self.signals:
            if len(s) == 2:
                digit_1 = s
            elif len(s) == 6:
                digits_069.append(s)
        for d in digits_069:
            if len(re.findall("[" + digit_1 + "]", d)) == 1:
                self.decode["c"] = re.findall("[^" + d + "]", digit_1)[0]

    def find_f_segment(self):
        for s in self.signals:
            if len(s) == 2:
                digit_1 = s
        self.decode["f"] = re.findall("[^" + self.decode["c"] + "]", digit_1)[0]

    def find_d_segment(self):
        for s in self.signals:
            if len(s) == 4:
                digit_4 = s
            elif len(s) == 6 and self.decode["c"] in s and self.decode["e"] in s:
                digit_0 = s
        self.decode["d"] = re.findall("[^" + digit_0 + "]", digit_4)[0]

    def find_b_segment(self):
        s = ""
        for k, v in self.decode.items():
            if v is not None:
                s += v
        self.decode["b"] = re.findall("[^" + s + "]", "abcdefg")[0]

    def decode_digits(self):
        decoded = []
        for d in self.digits:
            temp = ""
            for s in d:
                for k, v in self.decode.items():
                    if s == v:
                        temp += k
            decoded.append(temp)
        return decoded

                
if __name__ == "__main__":
    with open("input.txt") as f:
        data = f.readlines()
    data = [x.split("|") for x in data]

    signals = [x[0].split() for x in data]
    display = [x[1].split() for x in data]

    # Create signal objects
    Signals = []
    for i in range(len(signals)):
        Signals.append(Signal(signals[i], display[i]))

    for s in Signals:
        s.find_a_segment()
        s.find_g_segment()
        s.find_e_segment()
        s.find_c_segment()
        s.find_f_segment()
        s.find_d_segment()
        s.find_b_segment()

    print(Signals[0].decode)
    print(Signals[0].decode_digits())
    print(Signals[0].digits)


    digits_keys = {0: "abcefg", 1: "cf", 2: "acdeg", 3: "acdfg", 4: "bdcf",
            5: "abdfg", 6: "abdefg", 7: "acf", 8: "abcdefg", 9: "abcdfg"}

            
    decoded = []
    for s in Signals:
        temp = []
        for d in s.decode_digits():
            for k, v in digits_keys.items():
                if set(d) == set(v):
                    temp.append(k)
        decoded.append(temp)

    result = []
    for d in decoded:
        temp = ""
        for n in d:
            temp += str(n)
        result.append(int(temp))

    print(result)
    print(sum(result))
            


            
    


