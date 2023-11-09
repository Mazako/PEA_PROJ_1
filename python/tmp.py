import subprocess
from itertools import islice
import numpy
from python_tsp.exact import solve_tsp_brute_force
from python_tsp.exact import solve_tsp_branch_and_bound

cpp_program = '../cmake-build-debug/PEA_PROJ_1.exe'
BRUTE_FORCE_ARG = 'GENERATE_BRUTE'


def check_python():
    paths = [
        "../Graphs/tsp_6_1.txt",
        "../Graphs/tsp_6_2.txt",
        "../Graphs/tsp_10.txt",
        "../Graphs/tsp_12.txt",
        "../Graphs/tsp_13.txt",
        "../Graphs/tsp_14.txt",
        "../Graphs/tsp_15.txt",
        "../Graphs/tsp_17_1.txt",
        "../Graphs/tsp_18_1.txt",
        "../Graphs/tsp_19_1.txt",
        "../Graphs/tsp_20_1.txt"
    ]

    for path in paths:
        with open(path) as file:
            length = int(file.readline())
            print(length)
            # print(list(islice(file, length)))
            matrix = numpy.array([[int(number) for number in row.replace('  ', ' ').strip().split(' ')] for row in list(islice(file, length))])
            print(path, 'cost=', solve_tsp_branch_and_bound(matrix)[1])


check_python()
# subprocess.run([cpp_program, BRUTE_FORCE_ARG, '10', '1'])
# with open('./brute_force_sample.txt', 'r') as file:
#     [matrixSize, count] = file.readline().split(' ')
#     matrixSize = int(matrixSize)
#     count = int(count)
#     results = []
#     for i in range(count):
#         file.readline()
#         matrix = numpy.array([[int(number) for number in row.split(' ')] for row in list(islice(file, matrixSize))])
#         # info = file.readline().split(';')
#         # cost = int(info[0])
#         # path = [int(i) for i in info[1].split(' ')]
#         lib_cost = solve_tsp_branch_and_bound(matrix)
#         print(matrix)
#         print(lib_cost[1])
#         # print(cost, path, lib_cost, lib_cost[1] == cost)
#         # if lib_cost[1] == cost:
#         #     results.append(True)
#         # print('\n')
#     # if results.count(False) == 0:
#     #     print("SUCCESS")
