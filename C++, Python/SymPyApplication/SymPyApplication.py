# Encoding: UTF-8

from mpmath.libmp.libintmath import _1_100
import sympy as sp
from sympy import N, pprint, print_latex
from sympy.parsing.mathematica import parse_mathematica

def full_expression(L,K):
    """
    Computes AE + EB - AEB  for square matrices A and B and rectangular matrix E.

    Args:
        L: Size of square matrices A and B.
        K: Number of columns in E (and rows in B).

    Returns:
        The matrix Y = AE + EB - AEB as a sympy Matrix.
        Returns None if input validation fails.
    """

    if L <= 0 or K <= 0:
        print("Error: Matrix dimensions must be positive integers.")
        return None

    A = sp.Matrix([[sp.symbols(f'a{i+1}{j+1}') for j in range(L)] for i in range(L)])
    E = sp.Matrix([[sp.symbols(f'e{i+j}') for j in range(K)] for i in range(L)])
    B = sp.Matrix([[sp.symbols(f'b{i+1}{j+1}') for j in range(K)] for i in range(K)])

    try:
        Y = A * E + E * B - (A * E * B)

        # Sort each element of Y by e_k
        Y_sorted = Y.applyfunc(lambda x: sp.collect(x, [sp.Symbol(f'e_{k}') for k in range(K+L-1)]))

        return Y_sorted
    except ValueError as e:
        print(f"Error during matrix multiplication: {e}")
        return None

def full_expression_sorted(L, K):
    """Computes AE + EB - AEB, sorting each element by e_k during calculation."""
    if L <= 0 or K <= 0:
        raise ValueError("Matrix dimensions must be positive integers.")

    A = sp.Matrix([[sp.symbols(f'a{i+1}{j+1}') for j in range(L)] for i in range(L)])
    E = sp.Matrix([[sp.symbols(f'e{i+j}') for j in range(K)] for i in range(L)])
    B = sp.Matrix([[sp.symbols(f'b{i+1}{j+1}') for j in range(K)] for i in range(K)])

    Y = sp.Matrix(L, K, lambda i, j: 0)  # Initialize result matrix

    for i in range(L):
        for j in range(K):
            AE_term = sum(A[i, k] * E[k, j] for k in range(L))
            EB_term = sum(E[i, k] * B[k, j] for k in range(K))
            AEB_term = sum(sum(A[i, k] * E[k, l] * B[l, j] for k in range(L)) for l in range(K))

            #Combine terms BEFORE applying collect to handle parentheses correctly
            combined_term = AE_term + EB_term - AEB_term

            # Correct range for k and apply collect
            Y[i, j] = sp.collect(combined_term, [sp.Symbol(f"e{k}") for k in range(L + K - 1)])

    return Y

# Example usage:
L = 2
K = 2
Y = full_expression_sorted(L, K)
print("\nAE + EB - AEB (sorted by e_k):")
pprint(Y)


def matrix_products_with_diagonal_averaging(L, K):
    """Computes AE + EB - AEB and creates the C matrix."""
    if L <= 0 or K <= 0:
        raise ValueError("Matrix dimensions must be positive integers.")

    A = sp.Matrix([[sp.symbols(f'a{i+1}{j+1}') for j in range(L)] for i in range(L)])
    E = sp.Matrix([[sp.symbols(f'e{i+j}') for j in range(K)] for i in range(L)])
    B = sp.Matrix([[sp.symbols(f'b{i+1}{j+1}') for j in range(K)] for i in range(K)])
    
    Y = A*E + E*B - A*E*B
    if Y is None:  # Handle potential errors from matrix_products
        return None

    N = L + K - 1
    g_k = []
    ek_symbols = [sp.Symbol(f'e{k}') for k in range(N)]

    for k in range(N):
        sum_term = 0
        if k < L - 1:
            for m in range(1, k + 2):
                sum_term += Y[m - 1, k - m + 1]
            gk = (1 / (k + 1)) * sum_term
        elif k < K:
            for m in range(1, L + 1):
                sum_term += Y[m - 1, k - m + 1]
            gk = (1 / L) * sum_term
        else:
            for m in range(k - K + 2, N - K + 2):
                sum_term += Y[m - 1, k - m + 1]
            gk = (1 / (N - k)) * sum_term

        expanded_gk = sp.expand(gk)
        g_k.append(sp.collect(expanded_gk, ek_symbols))
        
    return g_k


def make_C_matrix(g_k):
    N = len(g_k)
    ek_symbols = [sp.Symbol(f'e{k}') for k in range(N)]
    C_matrix = sp.Matrix(N, N, lambda i, j: 0)
    for i in range(N):
        coeff_dict = sp.Poly(g_k[i],*ek_symbols).as_poly().coeffs()
        for j in range(len(coeff_dict)):
            C_matrix[i,j] = coeff_dict[j]



    return C_matrix

# Example usage
L = 2
K = 2
g_k = matrix_products_with_diagonal_averaging(L, K)
pprint(g_k)
C = make_C_matrix(g_k)
pprint(C)
print_latex(C)

def gk_for_result(expr_matrix):
    Y = expr_matrix    
    if Y is None:  # Handle potential errors from matrix_products
        return None
    L, K = Y.shape
    N = L + K - 1
    g_k = []
    ek_symbols = [sp.Symbol(f'e{k}') for k in range(N)]

    for k in range(N):
        sum_term = 0
        if k < L - 1:
            for m in range(1, k + 2):
                sum_term += Y[m - 1, k - m + 1]
            gk = (1 / (k + 1)) * sum_term
        elif k < K:
            for m in range(1, L + 1):
                sum_term += Y[m - 1, k - m + 1]
            gk = (1 / L) * sum_term
        else:
            for m in range(k - K + 2, N - K + 2):
                sum_term += Y[m - 1, k - m + 1]
            gk = (1 / (N - k)) * sum_term

        expanded_gk = sp.expand(gk)
        g_k.append(sp.collect(expanded_gk, ek_symbols))
        
    return g_k

# L <= K
L = 4
K = 6
A = sp.Matrix([[sp.symbols(f'a{i+1}{j+1}') for j in range(L)] for i in range(L)])
E = sp.Matrix([[sp.symbols(f'e{i+j}') for j in range(K)] for i in range(L)])
B = sp.Matrix([[sp.symbols(f'b{i+1}{j+1}') for j in range(K)] for i in range(K)])

AE = A*E
EB = E*B
AEB = A*E*B

resAE = gk_for_result(AE)
resEB = gk_for_result(EB)
resAEB = gk_for_result(AEB)
print(resAE, "\n", resEB, "\n", resAEB)
accAE = make_C_matrix(resAE)
accEB = make_C_matrix(resEB)
accAEB = make_C_matrix(resAEB)
print("1")
print_latex(accAE)
pprint(resAE)
pprint(accAE)
print("2")
print_latex(accEB)
pprint(resEB)
pprint(accEB)
print("3")
print_latex(accAEB)
pprint(resAEB)
pprint(accAEB)

def format_matrix(matrix, precision=2):
    """Formats a SymPy matrix to a specified precision."""
    rows, cols = matrix.shape
    formatted_matrix = sp.Matrix(rows, cols, lambda i, j: N(matrix[i, j], precision))
    return formatted_matrix

formatted_A = format_matrix(accAE, precision=2)
print_latex(formatted_A)
print_latex(format_matrix(accEB))
print_latex(format_matrix(accAEB))
# def AE_product(L, K):
#     """
#     Computes AE + EB - AEB for matrices A, E, and B.

#     Args:
#         L: Size of square matrix A and number of rows in E.
#         K: Number of columns in E and size of square matrix B.

#     Returns:
#         The matrix Y = AE + EB - AEB as a list of lists, where elements are SymPy expressions.
#         Returns None if input validation fails.
#     """

#     # Generate symbolic matrices A, E, and B
#     A = [[sp.symbols(f'a{i+1}{j+1}') for j in range(L)] for i in range(L)]
#     E = [[sp.symbols(f'e{i+j}') for j in range(K)] for i in range(L)]


#     # Calculate AE
#     AE = []
#     for i in range(L):
#         row = []
#         for j in range(K):
#             sum_term = 0
#             for k in range(L):
#                 sum_term += A[i][k] * E[k][j]
#             row.append(sum_term)
#         AE.append(row)

#     return AE

# def EB_product(L, K):
#     """
#     Computes AE + EB - AEB for matrices A, E, and B.

#     Args:
#         L: Size of square matrix A and number of rows in E.
#         K: Number of columns in E and size of square matrix B.

#     Returns:
#         The matrix Y = AE + EB - AEB as a list of lists, where elements are SymPy expressions.
#         Returns None if input validation fails.
#     """

#     # Generate symbolic matrices A, E, and B
#     E = [[sp.symbols(f'e{i+j}') for j in range(K)] for i in range(L)]
#     B = [[sp.symbols(f'b{i+1}{j+1}') for j in range(K)] for i in range(K)]

#     # Calculate EB
#     EB = []
#     for i in range(K):
#         row = []
#         for j in range(K):
#             sum_term = 0
#             for k in range(L):
#                 sum_term += E[k][i] * B[i][j]
#             row.append(sum_term)
#         EB.append(row)

#     return EB

# def AEB_product(L, K):
#     """
#     Computes AE + EB - AEB for matrices A, E, and B.

#     Args:
#         L: Size of square matrix A and number of rows in E.
#         K: Number of columns in E and size of square matrix B.

#     Returns:
#         The matrix Y = AE + EB - AEB as a list of lists, where elements are SymPy expressions.
#         Returns None if input validation fails.
#     """

#     # Generate symbolic matrices A, E, and B
#     A = [[sp.symbols(f'a{i+1}{j+1}') for j in range(L)] for i in range(L)]
#     E = [[sp.symbols(f'e{i+j}') for j in range(K)] for i in range(L)]
#     B = [[sp.symbols(f'b{i+1}{j+1}') for j in range(K)] for i in range(K)]

#     # Calculate AEB
#     AEB = []
#     for i in range(L):
#         row = []
#         for j in range(K):
#             sum_term = 0
#             for k in range(K):
#                 for l in range(L):
#                     sum_term += A[i][l] * E[l][k] * B[k][j]
#             row.append(sum_term)
#         AEB.append(row)
    
#     return AEB

# def matrix_products(L, K):
#     """
#     Computes AE + EB - AEB for matrices A, E, and B.

#     Args:
#         L: Size of square matrix A and number of rows in E.
#         K: Number of columns in E and size of square matrix B.

#     Returns:
#         The matrix Y = AE + EB - AEB as a list of lists, where elements are SymPy expressions.
#         Returns None if input validation fails.
#     """

#     # Calculate AE
#     AE = AE_product(L,K)

#     # Calculate EB
#     EB = EB_product(L,K)


#     # Calculate AEB
#     AEB = AEB_product(L,K)
    


#     # Calculate Y = AE + EB - AEB
#     Y = []
#     for i in range(L):
#         row = []
#         for j in range(K):
#             sum_term = AE[i][j] + EB[i][j] - AEB[i][j]
#             row.append(sum_term)
#         Y.append(row)

#     return Y


# # Example usage
# L = 3  # Size of square matrices A and B
# K = 8  # Size of matrix E

# Ares = AE_product(L, K)

# if Ares:
#     for row in Ares:
#         print(row)
# print("\n")
# Bres = EB_product(L, K)

# if Bres:
#     for row in Bres:
#         print(row)
# print("\n")
# Eres = AEB_product(L, K)

# if Eres:
#     for row in Eres:
#         print(row)
# print("\n")

# result = matrix_products(L, K)


# if result:
#   for row in result:
#     print(row)


# def matrix_products_with_diagonal_averaging(L, K):
#     """
#     Computes AE + EB - AEB, applies diagonal averaging,
#     and returns g_k in the format "g_i: (...)*e0 + (...)*e1 + ...".

#     Args:
#         L: Size of square matrices A and B, and number of rows in E.
#         K: Number of columns in E and size of square matrix B.

#     Returns:
#         A list of strings, where each string represents g_i in the desired format.
#     """

#     Y = matrix_products(L, K)
    
#     g_k = []  # List to store the results in the desired format

#     N = L + K - 1
#     for k in range(N):
#         result_string = f"g_{k}: "

#          # Collect terms with e_j
#         collected_terms = {}
#         for i in range(L):
#             for j in range(K):
#                 if i + j == k:  # Check if element is on the diagonal
#                     term = Y[i][j]
#                     coeff, symbol = term.as_coeff_Mul()  # Direct extraction
#                     if symbol in collected_terms:
#                         collected_terms[symbol] += coeff
#                     else:
#                         collected_terms[symbol] = coeff
        
#         # Construct the string representation
#         for j, (symbol, coeff) in enumerate(collected_terms.items()):
#             result_string += f"({coeff})*{symbol}"
#             if j < len(collected_terms) - 1:
#                 result_string += " + "

#         g_k.append(result_string)

#     return g_k


# # Example usage
# L = 2
# K = 2

# result = matrix_products_with_diagonal_averaging(L, K)

# if result:
#     for string_rep in result:
#         print(string_rep)

# def matrix_products_with_diagonal_averaging(L, K):
#     """
#     Computes AE + EB - AEB and applies diagonal averaging to the result.

#     Args:
#         L: Size of square matrices A and B, and number of rows in E.
#         K: Number of columns in E and size of square matrix B.

#     Returns:
#         A list representing the diagonal-averaged values g_k as defined in formula (1).
#         Returns None if input validation fails.
#     """

#     # Generate symbolic matrices A, E, and B
#     A = [[sp.symbols(f'a{i+1}{j+1}') for j in range(L)] for i in range(L)]
#     E = [[sp.symbols(f'e{i+j}') for j in range(K)] for i in range(L)]
#     B = [[sp.symbols(f'b{i+1}{j+1}') for j in range(K)] for i in range(K)]

#     # Calculate Y = AE + EB - AEB
#     Y = matrix_products(L, K)  # Reuse the matrix_products function

#     # Diagonal Averaging
#     N = L + K - 1  # Total number of elements in the diagonal
#     g_k = []

#     # Case 1: 0 <= k < L - 1
#     for k in range(L - 1):
#         sum_term = 0
#         for m in range(1, k + 2):
#             sum_term += Y[m - 1][k - m + 1]
#         g_k.append((1/(k+1)) * sum_term) 

#     # Case 2: L - 1 <= k < K
#     for k in range(L - 1, K):
#         sum_term = 0
#         for m in range(1, L + 1):
#             sum_term += Y[m - 1][k - m + 1]
#         g_k.append((1/L) * sum_term)

#     # Case 3: K <= k < N
#     for k in range(K, N):
#         sum_term = 0
#         for m in range(k - K + 2, N - K + 2):
#             sum_term += Y[m - 1][k - m + 1]
#         g_k.append((1/(N-k)) * sum_term)

#     return g_k


# # Example usage
# L = 2  # Size of square matrices A and B
# K = 2  # Size of matrix E

# result = matrix_products_with_diagonal_averaging(L, K)


# if result:
#     for i, g_k in enumerate(result):
#         print(f"g_{i}: {g_k}")
        