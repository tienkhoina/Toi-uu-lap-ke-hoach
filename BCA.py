# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import sys
import os

file_path = r'C:\Users\PC\Desktop\BCAtest.txt'

if not os.path.exists(file_path):
    print("Lỗi: File không tồn tại!")
else:
    sys.stdin = open(file_path, 'r', encoding='utf-8')
from ortools.linear_solver import pywraplp

solver = pywraplp.Solver.CreateSolver("SCIP")

m,n = map(int, input().split())

tc = [[0 for j in range(n)] for i in range(m)]

for i in range(m):
    A = list(map(int, input().split()))
    for j in range(1,A[0]+1):
        tc[i][A[j]-1] = 1

h = int(input())

f =[[0 for j in range(n)] for i in range(n)]

for i in range(h):
    a,b = map(int, input().split())
    f[a-1][b-1]=1
    f[b-1][a-1]=1
    
x = [[solver.IntVar(0,1,f'x_{i}_{j}') for j in range(m)] for i in range(n)]

t = solver.IntVar(0,solver.infinity(),'t')

for i in range(m):
    for j in range(n):
        if tc[i][j] == 0:
            solver.Add(x[j][i] == 0)
for i in range(n):
    for j in range(n):
        if f[i][j] == 1:
            for k in range(m):
                solver.Add(x[i][k]+x[j][k] <= 1)
for i in range(n):
    solver.Add(solver.Sum(x[i][j] for j in range(m)) == 1)
    
for j in range(m):
    solver.Add(t >= solver.Sum(x[i][j] for i in range(n)))

solver.Minimize(t)

status = solver.Solve()

if status == pywraplp.Solver.OPTIMAL:
    print(int(solver.Objective().Value()))
else:
    print(-1)
                
            