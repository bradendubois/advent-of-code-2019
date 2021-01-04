from os import curdir, makedev
from sys import displayhook, stdin
from string import ascii_uppercase

l = stdin.read().split("\n")

floor = set()

# (Y, X) -> Label
marked_tiles = dict()

# Temporary to link portals. Label -> First (Y, X) found
first_found = dict()

# (Y, X) -> (Y, X)
portal = dict()

for y, row in enumerate(l):
    for x, col in enumerate(row):

        if col == ".":
            
            floor.add((y, x))

            above = l[y-2][x] + l[y-1][x]
            left = l[y][x-2] + l[y][x-1]
            right = l[y][x+1] + l[y][x+2]
            below = l[y+1][x] + l[y+2][x]
            potential = [above, left, right, below]
            
            try:
                portal_label =  next(filter(lambda x: x[0] in ascii_uppercase and x[1] in ascii_uppercase, potential))

                if portal_label not in first_found:
                    first_found[portal_label] = (y, x)

                else:
                    other = first_found[portal_label]
                    portal[(y, x)] = other
                    portal[other] = (y, x)

                marked_tiles[(y, x)] = portal_label

            except StopIteration:
                continue


def search(entrance_y, entrance_x, recursive=False):

    # Y, X, Dimension, Distance
    queue = [(entrance_y, entrance_x, 0, 0)]
    seen = set()

    while len(queue):

        y, x, dimension, distance = queue.pop(0)

        if dimension > 40:
            continue

        if (y, x) not in floor or (y, x, dimension) in seen or dimension < 0:
            continue

        # print(y, x, dimension, distance)

        seen.add((y, x, dimension))

        if (y, x) in marked_tiles and marked_tiles[(y, x)] == "ZZ" and (not recursive or dimension == 0):
            return distance

        elif (y, x) in portal:

            if not recursive:
                queue.append((*portal[(y, x)], dimension, distance + 1))
            
            else:
                change = 1 if 3 <= x < len(l[y])-4 and 3 <= y < len(l)-4 else -1
                queue.append((*portal[(y, x)], dimension + change, distance + 1))

        queue.append((y - 1, x, dimension, distance + 1))
        queue.append((y + 1, x, dimension, distance + 1))
        queue.append((y, x - 1, dimension, distance + 1))
        queue.append((y, x + 1, dimension, distance + 1))


entrance_y, entrance_x = first_found["AA"]

# Part One
print(search(entrance_y, entrance_x))

# Part Two
print(search(entrance_y, entrance_x, recursive=True))