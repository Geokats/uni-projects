import sys
import time
import csp

def add(numbers):
	if not numbers:
		return None

	sum = 0
	for n in numbers:
		sum += n
	return sum

def mult(numbers):
	if not numbers:
		return None

	prod = 1
	for n in numbers:
		prod *= n
	return prod

def sub(numbers):
	if len(numbers) != 2:
		return None

	diff = abs(numbers[0] - numbers[1])
	return diff

def div(numbers):
	if len(numbers) != 2:
		return None

	return max(numbers)/min(numbers)


class KenKen(csp.CSP):
	
	def kenken_constraints(self, A, a, B, b):
		if A[1] == B[1] or A[2] == B[2]:
			if a == b:
				return False

		numbers = [ ]
		varsWithNoValue = 0

		for cage in self.cages:
			variables, function, result = cage
			if function == 'const' and (A in variables or B in variables):
				if A in variables:
					return a == result
				elif B in variables:
					return b == result
			elif function == 'add':
				func = add
			elif function == 'div':
				func = div
			elif function == 'sub':
				func = sub
			elif function == 'mult':
				func = mult

			if A in variables and B in variables:
				if len(variables) == 2:
					return func([a,b]) == result					
				else:
					for var in variables:
						if var == A:
							numbers.append(a)
						elif var == B:
							numbers.append(b)
						else:
							if self.curr_domains == None or len(self.curr_domains[var]) > 1:
								varsWithNoValue += 1
							elif len(self.curr_domains[var]) == 1:
								numbers.append(*self.curr_domains[var])
					if varsWithNoValue == 0:
						return func(numbers) == result
					else:
						return func(numbers) <= result

		return True

	def __init__(self, size, cages):
		self.size = size
		self.cages = cages

		variables = [ ]
		domains = { }
		neighbors = { }

		for i in range(size):
			for j in range(size):
				var = "X%d%d" % (i+1, j+1)
				variables.append(var)
				domains[var] = [n + 1 for n in range(size)]
				neighbors[var] = [ ]
				for k in range(size):
					for l in range(size):
						neighbor = "X%d%d" % (k+1, l+1)
						if neighbor != var and (i == k or j == l):
							neighbors[var].append(neighbor)

		for cage in cages:
			vars, function, result = cage
			for var in vars:
				for neighbor in vars:
					if neighbor != var and neighbor not in neighbors[var]:
						neighbors[var].append(neighbor)

		csp.CSP.__init__(self, variables, domains, neighbors, self.kenken_constraints)


if __name__ == '__main__':
	if len(sys.argv) != 2:
		print("Usage: kenken.py <input_file>")
	else:
		inputFile = open(sys.argv[1], 'r')
		data = inputFile.readlines()
		inputFile.close()

		size = int(data[0])
		cages = [ ]

		for i in range(1, len(data)):
			substrings = data[i].split()

			cur_vars = [ ]

			substrings[0] = substrings[0][2:-2]
			points = substrings[0].split("),(")
			
			for point in points:
				cur_var = "X%d%d" % (int(point[0]) + 1, int(point[2]) + 1)
				cur_vars.append(cur_var)


			cur_func = substrings[1]
			if cur_func == "\'\'":
				cur_func = 'const'

			cur_res = int(substrings[2])

			cur_cage = [cur_vars, cur_func, cur_res]
			cages.append(cur_cage)
		

		#BT
		print("Solving with BT...")
		problem_BT = KenKen(size, cages)
		start = time.time()
		result_BT = csp.backtracking_search(problem_BT)
		end = time.time()
		print("Solved with BT in %d seconds with %d assignments.\n" % (end - start, problem_BT.nassigns))

		#BT+MRV
		print("Solving with BT+MRV...")
		problem_BTMRV = KenKen(size, cages)
		start = time.time()
		result_BTMRV = csp.backtracking_search(problem_BTMRV, select_unassigned_variable=csp.mrv)
		end = time.time()
		print("Solved with BT+MRV in %d seconds with %d assignments.\n" % (end - start, problem_BTMRV.nassigns))

		#FC
		print("Solving with FC...")
		problem_FC = KenKen(size, cages)
		start = time.time()
		result_FC = csp.backtracking_search(problem_FC, inference=csp.forward_checking)
		end = time.time()
		print("Solved with FC in %d seconds with %d assignments.\n" % (end - start, problem_FC.nassigns))

		#FC+MRV
		print("Solving with FC+MRV...")
		problem_FCMRV = KenKen(size, cages)
		start = time.time()
		result_FCMRV = csp.backtracking_search(problem_FCMRV, select_unassigned_variable=csp.mrv, inference=csp.forward_checking)
		end = time.time()
		print("Solved with FC+MRV in %d seconds with %d assignments.\n" % (end - start, problem_FCMRV.nassigns))

		#MAC
		print("Solving with MAC...")
		problem_MAC = KenKen(size, cages)
		start = time.time()
		result_MAC = csp.backtracking_search(problem_MAC, inference=csp.mac)
		end = time.time()
		print("Solved with MAC in %d seconds with %d assignments.\n" % (end - start, problem_MAC.nassigns))

		#Min Conflicts
		print("Solving with Min Conflicts...")
		problem_MIN = KenKen(size, cages)
		max_steps = 10000
		start = time.time()
		result_MIN = csp.min_conflicts(problem_MIN, max_steps)
		end = time.time()
		if result_MIN != None:
			print("Solved with Min Conflicts in %d seconds with %d assignments.\n" % (end - start, problem_MIN.nassigns))
		else:
			print("Min Conficts could not find a solution after %d steps.\n" % (max_steps))


		print("\nSollution:\n")
		for i in range(size):
			for j in range(size):
				for (var, val) in result_BT.items():
					if var == "X%d%d" % (i+1, j+1):
						print("%s = %d" % (var, val), end = "  ")
			print("")