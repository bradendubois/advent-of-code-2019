from sys import stdin

l = [int(x) for x in stdin.read()]

repeats = [[0]*i + [1]*i + [0]*i + [-1]*i for i in range(1, len(l)+1)]

def fft(signal):

    new_pattern = []

    for index in range(1, len(signal)+1):

        repeat = repeats[index-1]

        t = 0

        for i, num in enumerate(signal, start=1):
            t += num * repeat[i%len(repeat)]

        new_pattern.append(abs(t)%10)

    return new_pattern


# Part One
cur = l.copy()
for _ in range(100):
    cur = fft(cur)
print("".join(str(x) for x in cur)[:8])


# Part Two
def triangle(vec):
    
    s = sum(vec)
    out = []

    for x in vec:
        out.append(s % 10)
        s -= x
        
    return out


offset = int("".join(str(x) for x in l[:7]))

l *= 10000
l = l[offset:]
for _ in range(100):
    l = triangle(l)

print("".join(str(x) for x in l)[:8])
