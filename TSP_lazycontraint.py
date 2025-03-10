from ortools.linear_solver import pywraplp
from itertools import combinations

class TSP:
    def __init__(self, n, C):
        self.n = n
        self.C = C
        self.solver = pywraplp.Solver.CreateSolver("SCIP")
        self.x = [[self.solver.IntVar(0, 1, f'x_{i}_{j}') for j in range(n)] for i in range(n)]
        self.SECS_constraints = [] 

    def find_cycles(self):
        cycles = []
        visited = [False] * self.n

        for start in range(self.n):
            if not visited[start]:
                cycle = []
                current = start
                while not visited[current]:
                    visited[current] = True
                    cycle.append(current)
                    for next_node in range(self.n):
                        if self.x[current][next_node].solution_value() > 0.5:
                            current = next_node
                            break
                if len(cycle) < self.n:
                    cycles.append(cycle)
        return cycles

    def add_SEC_constraints(self, cycles):
        for cycle in cycles:
            if len(cycle) > 1: 
                self.solver.Add(sum(self.x[i][j] for i in cycle for j in cycle if i != j) <= len(cycle) - 1)

    def Solve(self):
        for i in range(self.n):
            self.solver.Add(sum(self.x[i][j] for j in range(self.n) if i != j) == 1)
        for j in range(self.n):
            self.solver.Add(sum(self.x[i][j] for i in range(self.n) if i != j) == 1)

        self.solver.Minimize(sum(self.x[i][j] * self.C[i][j] for i in range(self.n) for j in range(self.n)))

    
        while True:
            status = self.solver.Solve()
            if status != pywraplp.Solver.OPTIMAL:
                return -1  

            cycles = self.find_cycles()
            if not cycles:
                break  
            self.add_SEC_constraints(cycles)

        return int(self.solver.Objective().Value())

if __name__ == "__main__":
    n = int(input())
    
    C = [list(map(int, input().split())) for _ in range(n)]
    
    tsp = TSP(n, C)
    print(tsp.Solve())
