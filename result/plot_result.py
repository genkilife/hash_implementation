import os
os.environ['KMP_DUPLICATE_LIB_OK']='True'
import glob
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

offset = 10

keySize = 32749.0

def dump_performance(filename):
	plt.cla()
	with open(filename[1]) as f:
		data = [x.split(' ',1) for x in f.read().splitlines()]
		linearXasis = [float(x[0])/keySize for x in data[offset:]]
		linearYasis = [x[1] for x in data[offset:]]
	with open(filename[2]) as f:
		data = [x.split(' ',1) for x in f.read().splitlines()]
		chainedXasis = [float(x[0])/keySize for x in data[offset:]]
		chainedYasis = [x[1] for x in data[offset:]]
	with open(filename[3]) as f:
		data = [x.split(' ',1) for x in f.read().splitlines()]
		cuckooXasis = [float(x[0])/keySize for x in data[offset:]]
		cuckooYasis = [x[1] for x in data[offset:]]
	with open(filename[4]) as f:
		data = [x.split(' ',1) for x in f.read().splitlines()]
		doubleXasis = [float(x[0])/keySize for x in data[offset:]]
		doubleYasis = [x[1] for x in data[offset:]]
	
	plt.ylabel('Time per 200 operation(ms)')
	plt.xlabel('loading factor')
	plt.plot(linearXasis, linearYasis, '-', color='red')
	plt.plot(chainedXasis, chainedYasis, '-', color='green')
	plt.plot(cuckooXasis, cuckooYasis, '-', color='#ff7f0eff')
	plt.plot(doubleXasis, doubleYasis, '-', color='#1f77b4ff')
	plt.legend(['linear hashing', 'chained hashing', 'cuckoo hashing', 'double hashing'], loc='upper left')
	plt.savefig(filename[0])
	plt.show()

uniform_insert = ['uniform_insert.png', 'result/linearHash_uniform_insert_timestamp.txt', 'result/chainedHash_uniform_insert_timestamp.txt',
					'result/cuckooHash_uniform_insert_timestamp.txt', 'result/doubleHash_uniform_insert_timestamp.txt']

dump_performance(uniform_insert)

uniform_search = ['uniform_search.png', 'result/linearHash_uniform_search_timestamp.txt', 'result/chainedHash_uniform_search_timestamp.txt',
					'result/cuckooHash_uniform_search_timestamp.txt', 'result/doubleHash_uniform_search_timestamp.txt']

dump_performance(uniform_search)

uniform_delete = ['uniform_delete.png', 'result/linearHash_uniform_delete_timestamp.txt', 'result/chainedHash_uniform_delete_timestamp.txt',
					'result/cuckooHash_uniform_delete_timestamp.txt', 'result/doubleHash_uniform_delete_timestamp.txt']

dump_performance(uniform_delete)

collide_insert = ['collide_insert.png', 'result/linearHash_collide_insert_timestamp.txt', 'result/chainedHash_collide_insert_timestamp.txt',
					'result/cuckooHash_collide_insert_timestamp.txt', 'result/doubleHash_collide_insert_timestamp.txt']

dump_performance(collide_insert)

collide_search = ['collide_search.png', 'result/linearHash_collide_search_timestamp.txt', 'result/chainedHash_collide_search_timestamp.txt',
					'result/cuckooHash_collide_search_timestamp.txt', 'result/doubleHash_collide_search_timestamp.txt']

dump_performance(collide_search)

collide_delete = ['collide_delete.png', 'result/linearHash_collide_delete_timestamp.txt', 'result/chainedHash_collide_delete_timestamp.txt',
					'result/cuckooHash_collide_delete_timestamp.txt', 'result/doubleHash_collide_delete_timestamp.txt']

dump_performance(collide_delete)
