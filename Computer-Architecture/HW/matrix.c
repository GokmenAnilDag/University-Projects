#include "matrix.h"

/**
 * This function initializes and returns a dense matrix 
 * as a dynamic two-dimensional array.
 */
DenseMatrix initDenseMatrix(int columnLength, int rowLength) {
	//allocate memory
	DenseMatrix denseMatrix = (DenseMatrix)malloc(sizeof(DenseMatrix_t));
	//assign the length inputs to it's corresponding pointers for the new matrix
	denseMatrix -> columnLength = columnLength;
	denseMatrix -> rowLength = rowLength;
	//allocating memory for the array (similar way as the example from lab)
	//each row will point to an array of integers, thus allowing us to make a matrix
	denseMatrix -> matrix = (int**)malloc(rowLength * sizeof(int*));
	//now allocating memory for the rows themselves
	for (int i = 0; i < rowLength; i++) {
		denseMatrix->matrix[i] = (int*)malloc(columnLength * sizeof(int*));
	}
	return denseMatrix;
}

/**
 * This function deallocates all the rows and 
 * columns of the given dense matrix.
 */
void freeDenseMatrix(DenseMatrix denseMatrix) {
	//basically free in reverse order to creating process
	//free each row, then free the row pointers, then the matrix itself
	for (int i = 0; i < denseMatrix -> rowLength; i++) {
		free(denseMatrix -> matrix[i]);
	}
	free(denseMatrix -> matrix);
	free(denseMatrix);
}

/**
 * This function creates a dense matrix and fills 
 * the elements in the given parse matrix as a set.
 */
DenseMatrix parseMatrixToDenseMatrix(Set parseMatrix, int columnLength, int rowLength) {
	//first we'll initialize the matrix
	DenseMatrix denseMatrix = initDenseMatrix(columnLength, rowLength);
	//now, we'll use a nested loop to fill each row and column
	//need an index to fill each point in the matrix with the corresponding element in the set
	int index = 0;
	for (int row = 0; row < rowLength; row++) {
		for (int column = 0; column < columnLength; column++) {
			//select the element at current index from the set
			Element element = parseMatrix -> elements[index];
			//void pointer to get data as int value
			int value = *(int*)element -> data;
			//assigning the value to the point
			denseMatrix -> matrix[row][column] = value;
			index++; //incrementing index to continue along the set
		}
	}
	return denseMatrix;
}

/**
 * This function creates and returns a parse matrix 
 * as a set depending on the given dense matrix's elements.
 */
Set denseMatrixToParseMatrix(DenseMatrix denseMatrix) {
	//initializing the set for return
	Set parseMatrix = initSet();
	//loop through each element of the matrix
	for (int row = 0; row < denseMatrix -> rowLength; row++) {
		for (int column = 0; column < denseMatrix -> columnLength; column++) {
			//select element at the current matrix point
			int value = denseMatrix -> matrix[row][column];
			//create an element for the value
			Element element = createIntegerElement(value);
			//add it to the set
			insertElement(parseMatrix, element);
		}
	}
	return parseMatrix;
}

/**
 * This matrix creates a new dense matrix, and the 
 * matrix is the addition of the given two matrices.
 */
DenseMatrix addDenseMatrices(DenseMatrix dm1, DenseMatrix dm2) {
	//initialize a new dense matrix for the result, size is the same, assuming both matrices are to be of same size
	DenseMatrix newMatrix = initDenseMatrix(dm -> columnLength, dm1 -> rowLength);
	//again, nested loop to get each element
	for (int row = 0; row < dm1 -> rowLength; row++) {
		for (int column = 0; column < dm1 -> columnLength; column++) {
			//add the elements in both matrices at current matrix point
			newMatrix->matrix[row][column] = dm1 -> matrix[row][column] + dm2 -> matrix[row][column];
		}
	}
	return newMatrix;
}

/**
 * This matrix creates a new sparse matrix as a set, 
 * and the matrix is the addition of the given 
 * two sparse matrices.
 */
Set addSparseMatrices(Set sm1, Set sm2, int columnLength, int rowLength) {
	//initialize a new set for then result
	Set newSet = initSet();
	
}
