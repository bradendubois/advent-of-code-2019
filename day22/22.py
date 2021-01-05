from sys import stdin
import sympy
import re

l = [x.split(" ") for x in stdin.read().split("\n")]

def sequence(deck_size, instructions):

    cards = list(range(deck_size))

    for line in instructions:
        
        if " ".join(line) == "deal into new stack":
            cards = cards[::-1]

        elif line[0] == "cut":
            value = int(line[1])
            cards = cards[value:] + cards[:value]

        else:
            new_positions = dict()
            offset = int(line[-1])
            index = 0

            for card in cards:
                new_positions[index] = card
                index += offset
                index %= len(cards)

            cards = [new_positions[i] for i in range(len(cards))]

    return cards

# Part One
print(sequence(10007, l).index(2019))


# Part Two
# Special thanks to https://github.com/mcpower for providing a really clean
#   solution to this part two

deck_size = 119315717514047
repeat_process = 101741582076661

inv = lambda n: pow(n, deck_size-2, deck_size)

inc = 1
off = 0

for line in l:

    if line[0] == "deal" and line[1] == "into":
        inc *= -1
        inc %= deck_size
  
        off += inc
        off %= deck_size

    elif line[0] == "cut":
        off += int(line[1]) * inc
        off %= deck_size

    else:
        inc *= inv(int(line[-1]))
        inc %= deck_size

increment = pow(inc, repeat_process, deck_size)

offset = off * (1 - increment) * inv((1 - inc) % deck_size)
offset %= deck_size

print((offset + 2020 * increment) % deck_size)
