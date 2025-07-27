# encoding: utf-8

import sympy as sp
from sympy import symbols, Matrix, pprint, Add, Max, Piecewise, lambdify, eye
import numpy as np
import itertools

from sympy.polys.fglmtools import _identity_matrix

def geometric_mean_method(C, w):

  n = len(w)  # ����������� ������� � �������
  w_new = np.zeros(n)  # ������� ����� ������ ��� ����������

  for i in range(n):
    # ��������� ������������ ��������� ������ i ������� C
    prod_c = np.prod(C[i])
    # ��������� ������������ ��������� ������� w
    prod_w = np.prod(w)**(1/n)

    # ��������� ������� w_i
    w_new[i] = (prod_c**(1/n)) * prod_w

  return w_new

# ������ �������������:
C = np.array([[1, 3, 5, 7, 2],
              [1/3, 1, 3, 3, 1/5],
              [1/5, 1/3, 1, 2, 1/4],
              [1/7, 1/3, 1/2, 1, 1/3],
              [1/2, 5, 4, 3, 1]])
w = np.array([0.5, 2, 1, 1, 1])
geometric_means = np.sum(np.prod(C, axis=1)**(1/C.shape[1]))
w_result = geometric_mean_method(C, w)
print("cumprod: ", w_result.cumprod()**(1/3))
print("w unnormalized: ", w_result)
print("w normalized: ", w_result/geometric_means)
print("geom_means: ", geometric_means)
print((3*5*7*2)**(1/5))

w_result = w_result/geometric_means

A_1 = np.array([[1, 2, 3, 7, 4],
              [1/2, 1, 4, 1/4, 1/3],
              [1/3, 1/4, 1, 1/5, 1/2],
              [1/7, 1/4, 5, 1, 1/3],
              [1/4, 3, 2, 3, 1]])

A_2 = np.array([[1, 2, 3, 6, 4],
              [1/3, 1, 6, 6, 6],
              [1/5, 1/6, 1, 3, 4],
              [1/6, 1/6, 1/3, 1, 3],
              [1/4, 1/6, 1/4, 1/3, 1]])

A_3 = np.array([[1, 2, 3, 1/2, 1/5],
              [1/2, 1, 2, 1/4, 1/4],
              [1/3, 1/2, 1, 1/6, 1/6],
              [2, 4, 6, 1, 1/2],
              [5, 4, 6, 2, 1]])

A_4 = np.array([[1, 3, 5, 7, 9],
              [1/3, 1, 2, 5, 5],
              [1/5, 1/3, 1, 3, 3],
              [1/7, 1/5, 1/3, 1, 2],
              [1/9, 1/5, 1/3, 1/2, 1]])

A_5 = np.array([[1, 2, 3, 2, 3],
              [1/2, 1, 3, 4, 5],
              [1/3, 1/3, 1, 2, 2],
              [1/3, 1/4, 1/2, 1, 3],
              [1/2, 1/5, 1/2, 1/3, 1]])

res = np.array([geometric_mean_method(A_1, w),
                geometric_mean_method(A_2, w),
                geometric_mean_method(A_3, w),
                geometric_mean_method(A_4, w),
                geometric_mean_method(A_5, w)])

print("res: ", res)


# ������� ������� C
C_t = np.array([[1, 2, 3],
              [4, 5, 6],
              [7, 8, 9]])

# ������� ������ a
a = np.array([2, 3, 1])

# �������� ������ C � ������� a
C_powered = np.transpose(C_t) ** a  # Broadcasting
print(C_powered)
# ������� ������������ ������������ ����� C_powered
result = np.prod(C_powered, axis=1)

print(result)  # �����: [ 4 125 343]
 
A = np.transpose(res)**w_result
print("results: ", np.prod(A, axis=1))
print((1.3509)**(0.4363)*(0.3222)**(0.1352)*2.9926**0.0759*0.3264**0.0569*0.4409**0.2957)

print(A[0])

A_prod = np.prod(A, axis = 1)
A_max = np.max(A_prod)
print(A_prod/A_max)
print(A_prod/np.sum(A_prod))

print("C^2: ", C.diagonal())
for i in range(1, 6):
  print(f'C^{i}', (C**i).diagonal())
  
def cyclic_geometric_means(A, n, k):
    """
    Finds all cyclic geometric means of length k <= n for a given matrix A.

    Args:
        A: An n x n numpy array representing the matrix.
        n: The dimension of the matrix (n x n).

    Returns:
        A list of all cyclic geometric means.
    """
    means = []
    for indices in itertools.product(range(1, n + 1), repeat=k):  # Get all permutations of k indices
        product = 1
        for i in range(k):
            product *= A[indices[i] - 1, indices[(i + 1) % k] - 1]  # Access elements using indices
        means.append(product ** (1 / k))
    return means
# Example usage:
A = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
n = 5
for i in range(1, n+1):
    cyclic_means = cyclic_geometric_means(C, n, i)
    print(f"Cyclic geometric means {i}-th iteration: {max(cyclic_means)}")
    

def cyclic_geometric_means_max(A, n):
    """
    Finds the maximum cyclic geometric mean for each length k <= n and its corresponding permutation.

    Args:
        A: An n x n numpy array representing the matrix.
        n: The dimension of the matrix (n x n).

    Returns:
        A list of tuples, where each tuple contains:
            - The maximum cyclic geometric mean for a given length k.
            - The permutation of indices corresponding to the maximum mean.
    """

    results = []
    for k in range(1, n + 1):  # Loop through lengths k from 1 to n
        max_mean = float('-inf')  # Initialize max_mean to negative infinity
        max_permutation = None
        for indices in itertools.permutations(range(1, n + 1), k):  # Get all permutations of k indices
            product = 1
            for i in range(k):
                product *= A[indices[i] - 1, indices[(i + 1) % k] - 1]  # Access elements using indices
            mean = product ** (1 / k)
            if mean > max_mean:  # Update max_mean and max_permutation if a larger mean is found
                max_mean = mean
                max_permutation = indices
        results.append((max_mean, max_permutation))
    return results


# Example usage:
A = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
n = 5
max_means = cyclic_geometric_means_max(C, n)
print(f"Maximum cyclic geometric means and their permutations: {max_means}")
print(1/1.7782794100389228)

def max_algebra_multiply(A, B):
  """
  Multiplies two matrices A and B in max-algebra.

  Args:
    A: A numpy array representing the first matrix.
    B: A numpy array representing the second matrix.

  Returns:
    A numpy array representing the product of A and B in max-algebra.
  """

  rows_A = A.shape[0]
  cols_A = A.shape[1]
  cols_B = B.shape[1]

  # Create a result matrix filled with negative infinity
  C = np.full((rows_A, cols_B), -np.inf)

  for i in range(rows_A):
    for j in range(cols_B):
      for k in range(cols_A):
        C[i, j] = max(C[i, j], A[i, k]*B[k, j])

  return C

# Example usage:
A = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
B = np.array([[10, 11, 12], [13, 14, 15], [16, 17, 18]])

result = C
lamb = 10**(-1/4)
I = np.identity(5)
result = result*lamb
print("iden: ", I)
print("C:\n", result)
res=[I, result]
for i in range(2, 5):
   result = max_algebra_multiply(result, C)*lamb
   res.append(result)
   print(f"C^{i}:\n", result)
   

def max_algebra_sum(matrix_list):
  """
  Calculates the max-algebra sum of matrices in a list.

  Args:
    matrix_list: A list of NumPy matrices.

  Returns:
    A NumPy matrix representing the max-algebra sum of the input matrices.
  """

  # Find the dimensions of the first matrix in the list
  rows = matrix_list[0].shape[0]
  cols = matrix_list[0].shape[1]

  # Create a result matrix initialized with negative infinity
  result_matrix = np.full((rows, cols), -np.inf)

  # Iterate through each matrix in the list
  for matrix in matrix_list:
    # Perform element-wise max operation
    result_matrix = np.maximum(result_matrix, matrix)

  return result_matrix

# Example usage:
matrix1 = np.array([[1, 2], [3, 4]])
matrix2 = np.array([[5, 6], [7, 8]])
matrix3 = np.array([[1, 10], [11, 12]])
matrix_list = [matrix1, matrix2, matrix3]

max_sum_matrix = max_algebra_sum(res)
print("\n", max_sum_matrix)
print(np.max(max_sum_matrix))
print(np.linalg.matrix_rank(max_sum_matrix))

delta=np.max(max_sum_matrix)
rows = res[0].shape[0]
cols = res[0].shape[1]
delta_matrix = np.full((rows, cols), 1/delta)
delta_matrix = np.maximum(delta_matrix, np.identity(rows))
print(delta_matrix)

new_res = np.maximum(max_sum_matrix, delta_matrix)
print(new_res)

print(np.linalg.matrix_rank(new_res))

delta_matrix = np.full((rows, cols), 1/delta)
delta_lambda_matrix = np.maximum(delta_matrix, res[1])
print(delta_lambda_matrix)

cont=[I, delta_lambda_matrix]
result = delta_lambda_matrix
print("delta^-1 oplus C^1:\n: ", result)
for i in range(2, 5):
   result = max_algebra_multiply(result, delta_lambda_matrix)
   cont.append(result)
   print(f"delta^-1 oplus C^{i}:\n", result)
   
delta_lambda_result = max_algebra_sum(cont)
print("delta_lambda_result:\n ", delta_lambda_result)
print("rank: ", np.linalg.matrix_rank(delta_lambda_result))


# test

# Define symbolic variables
delta, lambda_sym = symbols('delta lambda')

# Define matrices (using SymPy's Matrix)
delta_matrix = Matrix([[delta, 2*delta], [3*delta, 4*delta]])
lambda_matrix = Matrix([[lambda_sym, 2*lambda_sym], [3*lambda_sym, 4*lambda_sym]])


def max_algebra_sum_symbolic(A, B):
    """
    Computes the max-algebra sum of two symbolic matrices.

    Args:
        A: A sympy Matrix.
        B: A sympy Matrix.

    Returns:
        A sympy Matrix representing the max-algebra sum.
    """
    rows, cols = A.shape
    result_matrix = Matrix.zeros(rows, cols)  # Initialize with symbolic zeros

    for i in range(rows):
        for j in range(cols):
            result_matrix[i, j] = Max(A[i, j], B[i, j])  # Max-algebra sum

    return result_matrix


# Calculate max-algebra sum
result = max_algebra_sum_symbolic(delta_matrix, lambda_matrix)
print("Max-algebra sum:")
print(result)

# Substitute numerical values if needed:
delta_val = 6
lambda_val = 10**(-1/4)
result_numeric = result.subs({delta: delta_val, lambda_sym: lambda_val})
print("\nMax-algebra sum (with numerical substitution):")
print(result_numeric)


# test

# Define symbolic variables
delta, lambd = symbols('delta lambda')

# Define matrices (using SymPy's Matrix)
delta_matrix = Matrix([[delta, 2*delta], [3*delta, 4*delta]])
lambda_matrix = Matrix([[lambd, 2*lambd], [3*lambd, 4*lambd]])


def max_algebra_sum_symbolic_piecewise(A, B):
    rows, cols = A.shape
    result_matrix = Matrix.zeros(rows, cols)

    for i in range(rows):
        for j in range(cols):
            result_matrix[i, j] = Piecewise((A[i, j], A[i, j] > B[i, j]), (B[i, j], True))

    return result_matrix


# Calculate max-algebra sum using piecewise function
result = max_algebra_sum_symbolic_piecewise(delta_matrix, lambda_matrix)
print("Max-algebra sum (symbolic, piecewise):")
print(result)


# test

# Define symbolic variables
delta, lambd = symbols('delta lambda')

# Define symbolic matrices
delta_matrix_sym = Matrix([[delta, 5*delta], [3*delta, 4*delta]])
lambda_matrix_sym = Matrix([[lambd, 2*lambd], [3*lambd, 4*lambd]])

# Define numerical values
delta_val = 2
lambd_val = 3

def max_algebra_sum_symbolic(delta_matrix, lambda_matrix, delta_val, lambd_val):
    rows, cols = delta_matrix.shape
    result_matrix = Matrix.zeros(rows, cols)
    for i in range(rows):
        for j in range(cols):
            delta_val_ij = delta_matrix[i, j].subs({delta: delta_val, lambd: lambd_val})
            lambd_val_ij = lambda_matrix[i, j].subs({delta: delta_val, lambd: lambd_val})
            if delta_val_ij >= lambd_val_ij:
                result_matrix[i, j] = delta_matrix[i, j]
            else:
                result_matrix[i, j] = lambda_matrix[i, j]
    return result_matrix

# Calculate max-algebra sum symbolically
result_sym = max_algebra_sum_symbolic(delta_matrix_sym, lambda_matrix_sym, delta_val, lambd_val)

print("Symbolic result:")
print(result_sym)




# Define symbolic variables
delta, lambd = symbols('delta lambda')

# Define symbolic matrices
matrix_A_sym = Matrix([[delta, 2*lambd], [3*delta, 4*lambd]])
matrix_B_sym = Matrix([[lambd, delta], [2*delta, 3*lambd]])

# Define numerical values
delta_val = 2
lambd_val = 3

def max_algebra_multiply_symbolic(A, B, delta_val, lambd_val):
    rows_A, cols_A = A.shape
    rows_B, cols_B = B.shape
    if cols_A != rows_B:
        raise ValueError("Matrices are not compatible for multiplication")
    C = Matrix.zeros(rows_A, cols_B)
    
    #This creates a dictionary that will store the symbolic form of every numerical multiplication operation
    numerical_to_symbolic = {} 
    
    for i in range(rows_A):
        for j in range(cols_B):
            max_val = -float('inf')
            max_expression = None
            for k in range(cols_A):
                num_val_ik = A[i,k].subs({delta:delta_val, lambd:lambd_val})
                num_val_kj = B[k,j].subs({delta:delta_val, lambd:lambd_val})
                cur_val = num_val_ik * num_val_kj
                
                #Store the symbolic expression corresponding to each numerical operation. 
                #The tuple (i,j,k) serves as a unique key for this
                numerical_to_symbolic[(i,j,k)] = A[i,k] * B[k,j]
                
                if cur_val > max_val:
                    max_val = cur_val
                    max_expression = numerical_to_symbolic[(i,j,k)]

            C[i,j] = max_expression #Assign the symbolic expression to the result

    return C

# Calculate max-algebra product
result_sym = max_algebra_multiply_symbolic(matrix_A_sym, matrix_B_sym, delta_val, lambd_val)

print("Symbolic result:")
print(result_sym)


delta, lambd = symbols('delta lambda')

delta_val = 6
lambd_val = 10**(1/4)

C_lambda = C/lambd
delta_matrix = Matrix([
   [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],
   [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],
   [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],
   [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],
   [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],])
# print('delta_matrix: \n', delta_matrix)
# delta_matrix=max_algebra_sum_symbolic(delta_matrix, eye(5), delta_val, delta_val)
# print("delta_matrix:\n", delta_matrix)
# print("C_lambda:\n", C_lambda)

delta_C = max_algebra_sum_symbolic(delta_matrix, C_lambda, delta_val, lambd_val)
print("delta_C:\n", delta_C)
delta_res = [eye(5), delta_C]
result = delta_C
print("delta_C:\n")
pprint(result)
for i in range(2, 5):
   result = max_algebra_multiply_symbolic(result, delta_C, delta_val, lambd_val)
   delta_res.append(result)
   print(f"delta_C^{i}:\n")
   pprint(result)

def max_algebra_sum_list(matrix_list, delta_val, lambd_val):
    """Computes the max-algebra sum of a list of symbolic matrices."""
    if not matrix_list:
        return Matrix([])  # Handle empty list case

    # Get dimensions of the first matrix (assuming all matrices have the same dimensions)
    rows, cols = matrix_list[0].shape

    # Initialize result matrix with negative infinity (neutral element for max)
    result_matrix = Matrix.zeros(rows, cols)
    for i in range(rows):
        for j in range(cols):
            result_matrix[i,j] = -float('inf')

    # Iterate through matrices in the list and perform max-algebra sum
    for matrix in matrix_list:
        result_matrix = max_algebra_sum_symbolic(result_matrix, matrix, delta_val, lambd_val)
    return result_matrix

delta_C_result = max_algebra_sum_list(delta_res, delta_val, lambd_val)
print("delta_C_result:\n")
pprint(delta_C_result)
pprint(delta_C_result.subs({delta:delta_val, lambd:lambd_val}))
print("rank:\n", delta_C_result.subs({delta:delta_val, lambd:lambd_val}).rank())
print("rank:\n", np.linalg.matrix_rank(max_sum_matrix))

print(10/(lambd_val**2), 5/lambd_val)

print(5*lambd_val**2/3, 1, lambd_val/3,5/(3*lambd_val**2), 5/lambd_val)

print(5*lambd_val**2/3, 10/(lambd_val**2))
print(2*lambd_val, lambd_val**2)

A_1 = Matrix([[1, 2, 3, 7, 4],
              [1/2, 1, 4, 1/4, 1/3],
              [1/5, 1/4, 1, 1/5, 1/2],
              [1/7, 1/4, 5, 1, 1/3],
              [1/4, 3, 2, 3, 1]])

A_2 = Matrix([[1, 2, 3, 6, 4],
              [1/3, 1, 6, 6, 6],
              [1/5, 1/6, 1, 3, 4],
              [1/6, 1/6, 1/3, 1, 3],
              [1/4, 1/6, 1/4, 1/3, 1]])

A_3 = Matrix([[1, 2, 3, 1/2, 1/5],
              [1/2, 1, 2, 1/4, 1/3],
              [1/3, 1/2, 1, 1/6, 1/6],
              [2, 4, 6, 1, 1/2],
              [5, 4, 6, 2, 1]])

A_4 = Matrix([[1, 3, 5, 7, 9],
              [1/3, 1, 2, 5, 5],
              [1/5, 1/3, 1, 3, 3],
              [1/7, 1/5, 1/3, 1, 2],
              [1/9, 1/5, 1/3, 1/2, 1]])

A_5 = Matrix([[1, 2, 3, 2, 3],
              [1/2, 1, 3, 4, 5],
              [1/3, 1/3, 1, 2, 2],
              [1/3, 1/4, 1/2, 1, 3],
              [1/2, 1/5, 1/2, 1/3, 1]])

# Example list of symbolic matrices 
matrix_list = [
    Matrix([[1, 2], [3, 4]]),
    Matrix([[5, 6], [7, 8]]),
    Matrix([[9, 10], [11, 12]])
]

# Example vector (replace with your actual vector) - must have same length as matrix_list
vector = Matrix([1, 2, 3])


def multiply_matrix_list_by_vector_elements(matrix_list, vector):
    """Multiplies each matrix in a list by the corresponding element in a vector."""
    if len(matrix_list) != vector.shape[0]:
        raise ValueError("Length of matrix list and vector must be equal.")

    result_matrices = []
    for i, matrix in enumerate(matrix_list):
        scalar_multiplier = vector[i]
        result_matrix = scalar_multiplier * matrix
        result_matrices.append(result_matrix)
    return result_matrices

# Perform the element-wise multiplication
result_matrices = multiply_matrix_list_by_vector_elements(matrix_list, vector)

# Print the results
print("Resulting matrices:")
for i, matrix in enumerate(result_matrices):
    print(f"Matrix {i+1}: \n{matrix}")

worst_weight=Matrix([1,1/lambd**2,1/(3*lambd), 1/delta, lambd/2])
best_weight=Matrix([5*lambd**2/3, 1, lambd/3, lambd**2/6, lambd**3/2])
worst_res = [A_1, A_2, A_3, A_4, A_5]
best_res = [A_1, A_2, A_3, A_4, A_5]
worst_result_matrices=multiply_matrix_list_by_vector_elements(worst_res, worst_weight)
for i, matrix in enumerate(worst_result_matrices):
    print(f"Matrix {i+1}:\n")
    pprint(matrix)
print("worst-above\n---------------\n---------------\nbest-below")
best_result_matrices=multiply_matrix_list_by_vector_elements(best_res, best_weight)
for i, matrix in enumerate(best_result_matrices):
    print(f"Matrix {i+1}:\n")
    pprint(matrix)
    
worst_sum_matrix=max_algebra_sum_list(worst_result_matrices, delta_val, lambd_val)
best_sum_matrix=max_algebra_sum_list(best_result_matrices, delta_val, lambd_val)

print('worst matrix:\n')
pprint(worst_sum_matrix)
print('best matrix:\n')
pprint(best_sum_matrix)

n=5
res_worst = cyclic_geometric_means_max(worst_sum_matrix.subs({delta: delta_val, lambd: lambd_val}), n)
res_best = cyclic_geometric_means_max(best_sum_matrix.subs({delta: delta_val, lambd: lambd_val}), n)

print("res_worst:\n", res_worst)
print("res_best: \n", res_best)
print((15*lambd_val/2)**(1/2),(25*lambd_val**5/2)**(1/2))
print("\n\n\n\n\n\n\n")
pprint(worst_sum_matrix)

mu_1 = (15*lambd/2)**(1/2)
mu_2 = (25*lambd**5/2)**(1/2)

B_mu_1 = worst_sum_matrix/mu_1
pprint(B_mu_1)

def create_klini_matrix(matrix, delta_val, lambd_val):
    rows, cols = matrix.shape
    temp_matrix = matrix
    temp_holder = [eye(rows), matrix]
    for i in range(2, rows):
        temp_matrix = max_algebra_multiply_symbolic(temp_matrix, matrix, delta_val, lambd_val)
        temp_holder.append(temp_matrix)
    return max_algebra_sum_list(temp_holder, delta_val, lambd_val)

test = create_klini_matrix(delta_C, delta_val, lambd_val)
pprint(test)
print("\n")
pprint(delta_C_result)
print()

mu_1 = sp.symbols("mu_1")
B_mu_1_klini = create_klini_matrix(B_mu_1, delta_val, lambd_val)
print("Klini matrix for B_mu_1:")
pprint(B_mu_1_klini)
sp.print_latex(B_mu_1_klini)
print(B_mu_1_klini.subs({lambd:lambd_val}).rank())
pprint(B_mu_1_klini.subs({sp.Symbol("lambda"): 2*mu_1**2/15}))

delta_1_val = max(B_mu_1_klini.subs({lambd:lambd_val}))
# delta_matrix = Matrix.zeros(n,n)
# delta_matrix[:] = 1/delta
delta_val = delta_1_val
B_mu_1_combined = max_algebra_sum_symbolic(delta_matrix, B_mu_1, delta_val, lambd_val)
pprint(B_mu_1_combined)
B_mu_1_delta_klini = create_klini_matrix(B_mu_1_combined, delta_val, lambd_val)
print("B_mu_1_delta_klini:")
print("delta_1 = ", delta_1_val)
pprint(B_mu_1_delta_klini)
print("\n")
pprint(B_mu_1_delta_klini.subs({delta:delta_val, lambd:lambd_val}))
print("Rank? ", B_mu_1_delta_klini.subs({delta:delta_val, lambd:lambd_val}).rank())
# Непонятная ошибка, смотрим:

# Create a SymPy matrix with the symbol 'delta'
matrix = sp.Matrix([
    [sp.Symbol('delta'), 2],
    [3, sp.Symbol('delta')]
])

# Substitute 'delta' with 'lambda**2'
new_matrix = matrix.subs({sp.Symbol('delta'): sp.symbols('lambda')**2})

print(new_matrix)
print("Klini matrix: B_mu_1")
pprint(B_mu_1_klini)
print("With numeric values")
pprint(B_mu_1_klini.subs({lambd:lambd_val}))

def inverse_maxima_columns(matrix):
    """
    Finds the maximum element in each column of a matrix and returns a vector 
    containing the inverses of these maxima.

    Args:
        matrix: A NumPy 2D array (matrix).

    Returns:
        A NumPy 1D array (vector) containing the inverses of the column maxima.
        Returns None if the matrix is empty or contains non-numeric values.  
    """
    try:
        matrix = np.array(matrix, dtype=float)  # Convert to NumPy array with float type for inverse calculation.  Handles potential errors in input.
        if matrix.size == 0:
            return None
        column_maxima = np.max(matrix, axis=0) #Find maximum along each column (axis=0)
        inverse_maxima = 1 / column_maxima #Compute inverse
        return inverse_maxima
    except ValueError:
        return None  #Handle non-numeric values in input

B_mu_1_max = inverse_maxima_columns(B_mu_1_klini.subs({lambd:lambd_val}))

print("Max inverse column: \n", B_mu_1_max)

mu_2 = (25*lambd**5/2)**(1/2)
print("best_sum_matrix")
pprint(best_sum_matrix)
B_mu_2 = best_sum_matrix/mu_2
print("B_mu_2")
pprint(B_mu_2)
B_mu_2_klini = create_klini_matrix(B_mu_2, delta_val, lambd_val) 
mu_2 = sp.symbols("mu_2")
print("B_mu_2_klini_lambda:\n")
pprint(B_mu_2_klini)
print("Rank: ", B_mu_2_klini.subs({lambd:lambd_val}).rank())
print("Rank: ")
pprint(B_mu_2_klini.subs({lambd:lambd_val}))
print("B_mu_2_klini:\n")
pprint(B_mu_2_klini.subs({sp.Symbol("lambda") : (mu_2**2*2/25)**(1/5)}))


def max_product_index(matrix):
    """
    Finds the maximum element and maximum inverse in each column of a square matrix,
    calculates the product of the index and these values, and returns the index
    with the maximum product.

    Args:
        matrix: A NumPy 2D array (square matrix).

    Returns:
        The index (integer) of the column with the maximum product of (index * max_element * max_inverse).
        Returns None if the matrix is invalid.

    """
    try:
        matrix = np.array(matrix, dtype=float)
        n = matrix.shape[0]  #get the number of rows (and columns since it's square)

        if matrix.shape != (n, n) or n == 0:  # Check for square and non-empty matrix
            return None

        column_maxima = np.max(matrix, axis=0)
        column_minima = np.min(matrix, axis=0) #Find minimum, avoiding 0 to prevent division error.
        
        #Handle cases where all elements in a column are 0 to avoid division by 0.
        inverse_minima = np.where(column_minima == 0, 0, 1/column_minima)
     
        products = column_maxima * inverse_minima  # Element-wise multiplication
        
        max_product_index = np.argmax(products)  #Find index of the maximum product
        return [max_product_index, products]

    except ValueError:
        return None # Handle cases with non-numeric values

# Example usage:
matrix = np.array([[1, 5, 9], [2, 6, 10], [3, 7, 11]])
index = max_product_index(matrix)
print(f"Index of column with maximum product: {index[0]}.")  # Output: 2
pprint(index)

index_B = max_product_index(B_mu_2_klini.subs({lambd:lambd_val}))
print("Index_B\n")
pprint(index_B)
# mu_1=(15*lambd/2)**(1/2)
# mu_2=(25*lambd**5/2)**(1/2)
# lambd_val=10**(1/4)
# delta_val = 6
# lambd_val = (15*lambd_val/2)**(1/2)
# mu_2_val = (25*lambd_val**5/2)**(1/2)
# iden=eye(5)
# temp_result = worst_sum_matrix/lambd
# result = temp_result
# b_matrices = [iden, temp_result]
# print("identity:")
# pprint(iden)
# print("B_1/mu_1")
# pprint(temp_result)
# for i in range(2, 5):
#     result = max_algebra_multiply_symbolic(result, temp_result, delta_val, lambd_val)
#     b_matrices.append(result)
#     print(f"(B/mu_1)^{i}:")
#     pprint(result)
    
# max_alg_B = max_algebra_sum_list(b_matrices, delta_val, lambd_val)
# print("max_alg_B")
# pprint(max_alg_B)
# print("rank_B_1: ", max_alg_B.subs({delta:delta_val, lambd:lambd_val}).rank())
# print("mu_1: ", lambd_val)

# delta_val = max(max_alg_B.subs({delta:delta_val, lambd:lambd_val}))
# print(delta_val)
# pprint(max_alg_B.subs({lambd:lambd_val}))

# delta_matrix = Matrix([
#    [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],
#    [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],
#    [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],
#    [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],
#    [1/delta, 1/delta, 1/delta, 1/delta, 1/delta],])
# pprint(delta_matrix.subs({delta:delta_val}))

# delta_B_1=max_algebra_sum_symbolic(delta_matrix, temp_result, delta_val, lambd_val)
# num_delta_B_1=np.array(delta_B_1.subs({delta:delta_val, }))
# print("Delta_B_1 matrix:")
# pprint(delta_B_1)

# delta_b_matrices = [iden, delta_B_1]
# res = delta_B_1
# for i in range(2, 5):
#     res = max_algebra_multiply_symbolic(res, delta_B_1, delta_val, lambd_val)
#     delta_b_matrices.append(res)
#     print(f"delta_B_1^{i}")
#     pprint(res)

# max_delta_b_matrix = max_algebra_sum_list(delta_b_matrices, delta_val, lambd_val)
# print("max delta b matrix:")
# pprint(max_delta_b_matrix)
# sp.print_latex(max_delta_b_matrix)
# print("rank:", max_delta_b_matrix.subs({delta:delta_val, lambd:lambd_val}).rank())
# print("rank:", delta_matrix.subs({delta:delta_val, lambd:lambd_val}).rank())
# pprint(max_delta_b_matrix.subs({delta:delta_val, lambd:lambd_val}))


