
class Fish:
    """fish class"""
    def __init__(self, days):
        self.days = days

    def reset(self, days):
        self.days = days

    def is_end(self):
        return self.days == 0

    def day_passed(self):
        self.days -= 1

# Main
if __name__ == "__main__":
    # Import data and convert them to integer
    with open("input_test.txt") as f:
        data = f.readline()
    data = [int(x) for x in data.split(",")]

    # Create fishes
    reset_time = 6
    birth_time = 8 + 1
    fishes = []
    for d in data:
        fishes.append(Fish(d))

    for day in range(256):
        for fish in fishes:
            if not fish.is_end():
                fish.day_passed()
            else:
                fish.reset(reset_time)
                fishes.append(Fish(birth_time))
        report = [x.days for x in fishes]

    print(f"After {day + 1} days: {len(fishes)}")

