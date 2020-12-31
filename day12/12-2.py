from sys import stdin
from re import findall
from numpy import lcm

original_moons = [[int(x.strip(",")) for x in findall('-?(?:\d+,?)+', line)] for line in stdin.read().split("\n")]

velocities = [[0] * 3 for _ in range(len(original_moons))]

start_x = [moon[0] for moon in original_moons]
start_y = [moon[1] for moon in original_moons]
start_z = [moon[2] for moon in original_moons]

period_x, period_y, period_z = None, None, None

moons = [x.copy() for x in original_moons]

steps = 0

seen_x, seen_y, seen_z = dict(), dict(), dict()

while not all([period_x, period_y, period_z]):

    for i, moon_1 in enumerate(moons):
        for j, moon_2 in enumerate(moons[i+1:], start=i+1):

            for axis in range(3):
                if moon_1[axis] > moon_2[axis]:
                    velocities[i][axis] -= 1
                    velocities[j][axis] += 1
                
                elif moon_1[axis] < moon_2[axis]:
                    velocities[i][axis] += 1
                    velocities[j][axis] -= 1

    for i, moon in enumerate(moons):
        for axis in range(3):
            moons[i][axis] += velocities[i][axis]

    steps += 1

    if steps > 0:
        
        current_x = [moon[0] for moon in moons]
        current_y = [moon[1] for moon in moons]
        current_z = [moon[2] for moon in moons]

        velocity_x = [velocity[0] for velocity in velocities]
        velocity_y = [velocity[1] for velocity in velocities]
        velocity_z = [velocity[2] for velocity in velocities]

        if not period_x:
            x_rep = str(current_x) + str(velocity_x)

            if x_rep in seen_x:
                period_x = steps - seen_x[x_rep]
            else:
                seen_x[x_rep] = steps

        if not period_y:
            y_rep = str(current_y) + str(velocity_y)

            if y_rep in seen_y:
                period_y = steps - seen_y[y_rep]
            else:
                seen_y[y_rep] = steps

        if not period_z:
            z_rep = str(current_z) + str(velocity_z)

            if z_rep in seen_z:
                period_z = steps - seen_z[z_rep]
            else:
                seen_z[z_rep] = steps


print(period_x, period_y, period_z)
print(lcm.reduce([period_x, period_y, period_z]))