import time
from random import uniform

start = time.time()
acertos = 0
for i in range (0, 10000000):
    x = uniform(0, 1)
    y = uniform(0, 1)

    z = x*x + y*y
    if z <= 1.0:
        acertos += 1
    
print(4 * acertos/i)

end = time.time()
print(f'{end - start} seconds')