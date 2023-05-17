"""
mux4 channel switch test
"""
from MUX4 import *

mux = MUX4([2,3])
print(f"DEFAULT LIMIT = {mux.chan_limit}")
print("SET LIMIT TEST")
for i in range(-1,6):
    print(f"SET LIMIT {i}")
    mux.set_chan_limit(i)
    print(f"RESULT = {mux.get_chan_limit()}")
mux.clear_chan_limit()
print(f"LIMIT CLEAR= {mux.get_chan_limit()}")

print("\nLIMIT TEST")
for k in range(5):
    print(f"SET LIMIT = {k}")
    mux.set_chan_limit(k)
    for i in range (10):
        print(mux.get_chan())
        mux.advance()
    print("\n")
print("\n")
#mux.clear_chan_limit()
for i in range(4):
    print(f"SET CHANNEL {i}")
    mux.select(i)
    print(f"RESULT = {mux.get_chan()}")
print(mux.get_chan())