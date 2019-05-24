import os
os.environ['KMP_DUPLICATE_LIB_OK']='True'
import glob
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

offset = 10

keySize = 32749.0

with open('result/linearHash_uniform_insert_timestamp.txt') as f:
	data = [x.split(' ',1) for x in f.read().splitlines()]
	linearXasis = [float(x[0])/keySize for x in data[offset:]]
	linearYasis = [x[1] for x in data[offset:]]
with open('result/chainedHash_uniform_insert_timestamp.txt') as f:
	data = [x.split(' ',1) for x in f.read().splitlines()]
	chainedXasis = [float(x[0])/keySize for x in data[offset:]]
	chainedYasis = [x[1] for x in data[offset:]]
with open('result/cuckooHash_uniform_insert_timestamp.txt') as f:
	data = [x.split(' ',1) for x in f.read().splitlines()]
	cuckooXasis = [float(x[0])/keySize for x in data[offset:]]
	cuckooYasis = [x[1] for x in data[offset:]]
with open('result/doubleHash_uniform_insert_timestamp.txt') as f:
	data = [x.split(' ',1) for x in f.read().splitlines()]
	doubleXasis = [float(x[0])/keySize for x in data[offset:]]
	doubleYasis = [x[1] for x in data[offset:]]

plt.plot(linearXasis, linearYasis, '-', color='red')
plt.plot(chainedXasis, chainedYasis, '-', color='green')
plt.plot(cuckooXasis, cuckooYasis, '-', color='#ff7f0eff')
plt.plot(doubleXasis, doubleYasis, '-', color='#1f77b4ff')

plt.ylabel('Time per 200 operation')
plt.xlabel('loading factor')
plt.legend(['linear hashing', 'chained hashing', 'cuckoo hashing', 'double hashing'], loc='upper left')
plt.show()
