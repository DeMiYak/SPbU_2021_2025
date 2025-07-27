import numpy as np



def iterative_matrix_vector_multiply_normalized(A, x, epsilon, max_iterations=1000):
    """
    Iteratively multiplies a vector x by a matrix A, normalizing x at each 
    iteration, until the difference between successive iterations is less than epsilon.

    Args:
        A: The NumPy array representing the matrix.
        x: The NumPy array representing the initial vector.
        epsilon: The convergence threshold.
        max_iterations: The maximum number of iterations to perform.

    Returns:
        The resulting normalized vector after convergence, or None if it doesn't converge.
    """
    x_prev = x
    x_curr = x.copy() / np.linalg.norm(x) # Normalize the initial vector

    for i in range(max_iterations):
        norm_prev = np.linalg.norm(x_prev)
        x_prev = x_curr.copy()
        x_curr = np.dot(A, x_prev)
        norm_curr = np.sum(x_curr)
        x_curr = x_curr / norm_curr # Normalize at each iteration
        lambd = norm_curr/norm_prev
        if np.linalg.norm(x_curr - x_prev) < epsilon:
            return [x_curr, lambd, i]

    return None  # Did not converge


# Example usage:
A = np.array([[0.8, 0.2], [0.3, 0.7]])
x = np.array([30, 2])
epsilon = 1e-9

# result = iterative_matrix_vector_multiply_normalized(A, x, epsilon)

# if result is not None:
#     print("Resulting normalized vector:", result)
# else:
#     print("Did not converge within the specified epsilon and maximum iterations.")

C = np.array([[1, 3, 5, 7, 2],
              [1/3, 1, 3, 3, 1/5],
              [1/5, 1/3, 1, 2, 1/4],
              [1/7, 1/3, 1/2, 1, 1/3],
              [1/2, 5, 4, 3, 1]])

A_1 = np.array([[1, 2, 3, 7, 4],
              [1/2, 1, 4, 1/4, 1/3],
              [1/5, 1/4, 1, 1/5, 1/2],
              [1/7, 1/4, 5, 1, 1/3],
              [1/4, 3, 2, 3, 1]])

A_2 = np.array([[1, 2, 3, 6, 4],
              [1/3, 1, 6, 6, 6],
              [1/5, 1/6, 1, 3, 4],
              [1/6, 1/6, 1/3, 1, 3],
              [1/4, 1/6, 1/4, 1/3, 1]])

A_3 = np.array([[1, 2, 3, 1/2, 1/5],
              [1/2, 1, 2, 1/4, 1/3],
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

x = np.array([1,1,1,1,1])
epsilon = 1e-9

def apply_to_multiple_matrices_numpy_corrected(matrices, x, epsilon, max_iterations=1000):
    """Applies the iterative function to multiple matrices using NumPy efficiently."""
    results = []
    for matrix in matrices:
        result = iterative_matrix_vector_multiply_normalized(matrix, x, epsilon, max_iterations)
        results.append(result)
    return results #Return as a NumPy array

matrices = [C, A_1, A_2, A_3, A_4, A_5]

# print(iterative_matrix_vector_multiply_normalized(C, x, epsilon))

results = apply_to_multiple_matrices_numpy_corrected(matrices, x, epsilon)
vectors=[]
for res in results:
    print(res)
    temp = res[0]
    print(temp/max(temp), temp/sum(temp))
    vectors.append(temp)

# print(results[0][0]*results[0][1], np.dot(C,results[0][0]))

Cvec = vectors.pop(0)

res = vectors*Cvec[:, np.newaxis]

print("\n", Cvec, "\n", vectors, "\n", res)
print(sum(res))
sumres = sum(res)
print(sumres/max(sumres))

C = np.array([[1,2],
             [1/2,1]])

A_1 = np.array([[1,3,1/2],
               [1/3,1,4],
               [2,1/4,1]])

A_2 = np.array([[1, 1/4, 2],
               [4, 1, 1/5],
               [1/2, 5, 1]])

epsilon = 1e-12
x_c = np.array([3,2])
x_a = np.array([1,1,1])

c_it = iterative_matrix_vector_multiply_normalized(C, x_c, epsilon)
print("\n",c_it)

x_1_it = iterative_matrix_vector_multiply_normalized(A_1, x_a, epsilon)
print("\n",x_1_it)

x_2_it = iterative_matrix_vector_multiply_normalized(A_2, x_a, epsilon)
print("\n",x_2_it)

results = [c_it, x_1_it, x_2_it]
vectors=[]
for res in results:
    print(res)
    temp = res[0]
    print(temp/max(temp), temp/sum(temp))
    vectors.append(temp)
    
Cvec = vectors.pop(0)

# w1*x1, w2*x2, ...
res = vectors*Cvec[:, np.newaxis]

print("\n", Cvec, "\n", vectors, "\nres:\n", res)
print(sum(res))
sumres = sum(res)
print(sumres/max(sumres))


# Geometric means

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

C = np.array([[1,2],
             [1/2,1]])

A_1 = np.array([[1,3,1/2],
               [1/3,1,4],
               [2,1/4,1]])

A_2 = np.array([[1, 1/4, 2],
               [4, 1, 1/5],
               [1/2, 5, 1]])

w = np.array([1, 1])
geometric_means = np.sum(np.prod(C, axis=1)**(1/C.shape[1]))
w_result = geometric_mean_method(C, w)
print("\n\n")
print("cumprod: ", w_result.cumprod()**(1/3))
print("w unnormalized: ", w_result)
print("w normalized: ", w_result/geometric_means)
w_result = w_result/geometric_means
print("geom_means: ", geometric_means)
print((3*5*7*2)**(1/5))

x = np.array([1,1,1])
geometric_means = np.sum(np.prod(A_1, axis=1)**(1/A_1.shape[1]))
x_1_result = geometric_mean_method(A_1, x)
print("\nA_1:\n")
print("cumprod: ", x_1_result.cumprod()**(1/3))
print("x unnormalized: ", x_1_result)
print("x normalized: ", x_1_result/geometric_means)
print("geom_means: ", geometric_means)


geometric_means = np.sum(np.prod(A_2, axis=1)**(1/A_2.shape[1]))
x_2_result = geometric_mean_method(A_2, x)
print("\nA_2:\n")
print("cumprod: ", x_2_result.cumprod()**(1/2))
print("x unnormalized: ", x_2_result)
print("x normalized: ", x_2_result/geometric_means)
print("geom_means: ", geometric_means)

res = np.array([x_1_result, x_2_result])

A = np.transpose(res)**w_result
print("res:", res, "\nw_result:", w_result)
print("A:", A)
print("results: ", np.prod(A, axis=1),"\nnormalized results:\n", np.prod(A,axis=1)/max(np.prod(A,axis=1)))
print(10**(1/2))
print(24**(1/3))

C = np.array([[1, 3, 5, 7, 2],
              [1/3, 1, 3, 3, 1/5],
              [1/5, 1/3, 1, 2, 1/4],
              [1/7, 1/3, 1/2, 1, 1/3],
              [1/2, 5, 4, 3, 1]])

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

x = np.array([1,1,1,1,1])
epsilon = 1e-9

geometric_means = np.sum(np.prod(C, axis=1)**(1/C.shape[1]))
w_result = geometric_mean_method(C, x)
print("\n\n")
print("cumprod: ", w_result.cumprod()**(1/3))
print("w unnormalized: ", w_result)
print("w normalized: ", w_result/geometric_means)
w_result = w_result/geometric_means
print("geom_means: ", geometric_means)

A = [A_1, A_2, A_3, A_4, A_5]

A_res = [geometric_mean_method(y, x) for y in A]
print("\nA_res:", A_res)