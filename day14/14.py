from sys import stdin
from math import floor

l = [x.split(" => ") for x in stdin.read().split("\n")]

recipes = dict()

for left, right in l:

    # Produced
    amount, name = right.split(" ")
    amount = int(amount)

    recipes[name] = {
        "makes": amount,
        "requires": dict()
    }

    # Needed
    for req in left.split(", "):

        n, m = req.split(" ")
        n = int(n)

        recipes[name]["requires"][m] = n


start_buffer = {name: 0 for name in recipes}
start_buffer["FUEL"] = -1
start_buffer["ORE"] = 0


def ore(buffer):

    while any(value < 0 for name, value in buffer.items() if name != "ORE"):

        items = list(x for x in buffer if buffer[x] < 0 and x != "ORE")

        current = items.pop(0)

        recipe = recipes[current]

        k = abs(buffer[current] // recipe["makes"])
        buffer[current] += recipe["makes"] * k

        for create, amount in recipe["requires"].items():
            buffer[create] -= amount * k


    return buffer


# Part One
print(abs(ore(start_buffer.copy())["ORE"]))

# Part Two
x1 = 100000
x2 = 100000000

t = 1000000000000

b1, b2 = start_buffer.copy(), start_buffer.copy()
b1["FUEL"] = -1 * x1
b2["FUEL"] = -1 * x2

y1 = abs(ore(b1)["ORE"])
y2 = abs(ore(b2)["ORE"])

slope = (y2 - y1) / (x2 - x1)
t_fuel = floor((t - (y1 - slope * x1)) / slope)

print(t_fuel)
