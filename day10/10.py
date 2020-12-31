#!/usr/bin/env python

from sys import stdin 
from math import atan2, pi, sqrt

lines = stdin.read().split("\n")

asteroids = set()

for y, row in enumerate(lines):
    for x, column in enumerate(row):
        if column == "#":
            asteroids.add((x, y))


def detection(x, y):
    others = asteroids - {(x, y)}
    see = {atan2(y2 - y, x2 - x) for x2, y2 in others}
    return len(see)


def first_detections(x, y, remaining):

    # Angle -> Closest asteroid
    line_of_sight = dict()

    for x2, y2 in remaining:
        angle = (atan2(y - y2, x - x2) / pi * 180) - 90
        if angle < 0:
            angle += 360

        if angle not in line_of_sight:
            line_of_sight[angle] = (x2, y2, sqrt(abs(x2-x)**2 + abs(y2-y)**2))
        else:
            current_distance = sqrt(abs(x2-x)**2 + abs(y2-y)**2)
            contest_distance = line_of_sight[angle][2]

            if current_distance < contest_distance:
                line_of_sight[angle] = (x2, y2, current_distance)

    return [line_of_sight[k][:-1] for k in sorted(line_of_sight.keys())]


best_x, best_y, best_count = 0, 0, 0

for x, y in asteroids:
    if (result := detection(x, y)) > best_count:
        best_x, best_y, best_count = x, y, result

# Part One
print(best_count)

# Part Two
vaporize_contestants = asteroids - {(best_x, best_y)}

vaporized = 0

while len(vaporize_contestants):

    next_up = first_detections(best_x, best_y, vaporize_contestants)

    for poor_soul in next_up:
        
        vaporized += 1        
        vaporize_contestants.remove(poor_soul)
        # print("Vaporizing", vaporized, poor_soul)

        if vaporized == 200:
            x, y = poor_soul
            print(x * 100 + y)
            exit()