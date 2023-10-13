import subprocess
from itertools import islice
import numpy
from python_tsp.exact import solve_tsp_brute_force

cpp_program = '../cmake-build-debug/PEA_PROJ_1.exe'
BRUTE_FORCE_ARG = 'GENERATE_BRUTE'

subprocess.run([cpp_program, BRUTE_FORCE_ARG, '10', '1'])
with open('./brute_force_sample.txt', 'r') as file:
    [matrixSize, count] = file.readline().split(' ')
    matrixSize = int(matrixSize)
    count = int(count)
    results = []
    for i in range(count):
        file.readline()
        matrix = numpy.array([[int(number) for number in row.split(' ')] for row in list(islice(file, matrixSize))])
        info = file.readline().split(';')
        cost = int(info[0])
        path = [int(i) for i in info[1].split(' ')]
        lib_cost = solve_tsp_brute_force(matrix)
        print(matrix)
        print(cost, path, lib_cost, lib_cost[1] == cost)
        if lib_cost[1] == cost:
            results.append(True)
        print('\n')
    if results.count(False) == 0:
        print("SUCCESS")
