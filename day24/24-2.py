from sys import stdin
import numpy as np
from scipy.signal import convolve

# Special thanks to reddit user "naclmolecule" for a detailed breakdown of their
#  solution and of convolutions
#
# This solution is a re-write of theirs that I find more readable.

l = stdin.read().split("\n")

data = [[c == "#" for c in line] for line in l]

bug_array = np.array(data)

adj = np.array([
    [0, 1, 0],
    [1, 0, 1],
    [0, 1, 0]
])

states = set()

while (s := str(bug_array)) not in states:
    states.add(s)
    adjacent = convolve(bug_array, adj, mode='same')
    bug_array = (bug_array & (adjacent == 1)) | (~bug_array & np.isin(adjacent, [1, 2]))

# Part One
print((bug_array.flatten() * np.logspace(0, 24, 25, base=2, dtype=int)).sum())


levels = np.pad(np.array(data)[None], [(100,), (0,), (0,)])
adj3D = np.pad(adj[None], [(1,), (0,), (0,)])

up, down = slice(1, None), slice(None, -1)

points = (((0,), (1, 2)), ((...,  0), (2, 1)), ((-1,), (3, 2)), ((..., -1), (2, 3)))

for step in range(200):

    neighbor_count = convolve(levels, adj3D, mode='same')
    neighbor_count[:, 2, 2] = 0

    for outer, inner in points:
        neighbor_count[(up, *outer)] += levels[(down, *inner, None)]
        neighbor_count[(down, *inner)] += levels[(up, *outer)].sum(axis=1)

    levels = (levels & (neighbor_count == 1)) | (~levels & np.isin(neighbor_count, [1, 2]))

# Part Two
print(levels.sum())
