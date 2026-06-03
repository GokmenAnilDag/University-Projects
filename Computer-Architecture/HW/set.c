#include "set.h"

/**
 * This function initializes a set without an element and returns it.
 */
Set initSet() {
	//allocate memory for the set
	Set newSet = (Set)malloc(sizeof(Set_t));
	//no elements and cardinality for the empty set
	newSet -> elements = NULL;
	newSet -> cardinality = 0;
}

/**
 * This function creates an integer-typed element and returns it.
 * It allocates memory for both the element and the integer.
 */
Element createIntegerElement(int data) {
	//allocating memory for the new element and setting it's type to int
	Element newElement = (Element)malloc(sizeof(Element_t));
	newElement -> type = INTEGER;
	//allocating memory for the int value that'll be stored in the element
	int* intValue = (int*)malloc(sizeof(int));
	//assigning the recieved data to the int value
	*intValue = data;
	newElement -> data = intValue;
    return newElement;
}

/**
 * This function creates an float-typed element and returns it.
 * It allocates memory for both the element and the float.
 */
Element createFloatElement(float data) {
	//simply, changing the int parts of the createIntegerElement to float, and it should work
	//allocating memory for the new element and setting it's type to float
	Element newElement = (Element)malloc(sizeof(Element_t));
	newElement -> type = FLOAT;
	//allocating memory for the float value that'll be stored in the element
	float* floatValue = (float*)malloc(sizeof(float));
	//assigning the recieved data to the float value
	*floatValue = data;
	newElement -> data = floatValue;
	return newElement;
}

/**
 * This function creates an string-typed element and returns it.
 * It allocates memory for both the element and the string.
 * This function uses the `strlen` and the `strcpy` functions.
 */
Element createStringElement(char* data) {
	//allocating memory for the new element and setting it's type to string
	Element newElement = (Element)malloc(sizeof(Element_t));
	newElement -> type = STRING;
	//allocating memory for the string input that'll be stored in the element
	char* stringValue = (char*)malloc(strlen(data)+1); //+1 for the hidden \0 after every string (so I have learned)
	//assigning the recieved data to the string input
	strcpy(stringValue, data);//strcpy to copy a string from a memory location to another
	newElement -> data = stringValue;
	return newElement;
}

/**
 * This function creates an matrix-point-typed element and returns it.
 * It allocates memory for both the element and the matrix point.
 */
Element createMatrixPointElement(int x, int y, int data) {
	//allocating memory for the new element and setting it's type to matrix-point
	Element newElement = (Element)malloc(sizeof(Element_t));
	newElement->type = MATRIX_POINT;
	//allocating memory for an array of 3 integers for x,y and data
	int* matrixPointValues = (int*)malloc(3 * sizeof(int));
	//setting the values of the array to their corresponding value (in order)
	matrixPointValues[0] = x;
	matrixPointValues[1] = y;
	matrixPointValues[2] = data;
	//assign the array to the field
	newElement->data = matrixPointValues;
}

/**
 * This function compares two elements to see if they are identical.
 * First, it checks if the types are identical. If they are the same,
 * it checks if the data are the same. However, this function does not
 * compare addresses because the value from two different addresses
 * can be the same. It returns one if the elements are the same;
 * otherwise, it returns zero. This function uses the `strcmp` function.
 */
int isSame(Element e1, Element e2) {
	//first check their type and return 0 if different
	if (e1 -> type != e2->type) {
		return 0;
	}
	//if types are the same, now check the elements themselves for each type
	else if (e1 -> type == INTEGER) {
		//compare values inside the return statement for shortening the lines (? for if-else statements which I learned now :))
		return (*(int*)e1->data == *(int*)e2->data ? 1 : 0);
	}
	else if (e1 -> type == FLOAT) {
		//compare values for float
		return (*(float*)e1->data == *(float*)e2->data ? 1 : 0);
	}
	else if (e1 -> type == STRING) {
		//compare inputs for string
		return (strcmp((char*)e1->data, (char*)e2->data) == 0) ? 1 : 0;
	}
	else if (e1->type == MATRIX_POINT) {
		//assign data to arrays for checking
		int* mp1 = (int*)e1 -> data;
		int* mp2 = (int*)e2 -> data;
		//compare values for matrix-point, all three elements need to be equal, thus the triple AND
		return (mp1[0] == mp2[0] && mp1[1] == mp2[1] && mp1[2] == mp2[2]) ? 1 : 0;
	}
}

/**
 * This function checks if the given element is in the set or not.
 * It does not compare the addresses. It returns one if the given
 * element is in the set; otherwise, it returns zero.
 */
int in(Set set, Element element) {
	//we'd need a loop to check each element one-by-one
	for (int i = 0; i < set -> cardinality; i++) {
		//check if the element is the same as the element at index
		if (isSame(set -> elements[i], element)) {
			return 1; //element is in the set
		}
	}
	return 0; //element is not in the set
}

/**
 * This function inserts an element into the given set.
 * The same element cannot be twice in the same set.
 * It returns one if the inserting element is successful;
 * otherwise, it returns zero. This function uses the
 * `realloc` function.
 */
int insertElement(Set set, Element element) {
	//call the in function to check if the element is already in the set
	if (in(set, element)) {
		return 0; //same element, unsuccessful
	}
	//using realloc to increase the size of the array
	//element pointer is to access an already allocated array
	Element* newElement = realloc(set -> elements, (set -> cardinality + 1) * sizeof(Element));
	//change pointer to the new element
	set -> elements = newElement;
	//inserting the new element to the end of the set
	set -> elements[set -> cardinality] = element;
	//increasing the cardinality
	set -> cardinality++;
	return 1;//successful
}

/**
 * This function removes the given element in the set.
 * It returns one if removal is successful; otherwise,
 * it returns zero. This function uses the `realloc` function.
 */
int removeElement(Set set, Element element) {
	//we first need a loop to find the index of the element given
	int indexToRemove = NULL; //initialize an int value as the index we'll remove
	for (int i = 0; i < set->cardinality; i++) {
		if (isSame(set->elements[i], element)) {
			indexToRemove = i;
			break; //element is found, no need to continue the loop
		}
	}
	if (indexToRemove == NULL) {
		return 0; //this way we're covered if the element is not in the set
	}
	//remove the element at indexToRemove
	freeElement(set->elements[indexToRemove]);
	//we need to shift the elements to avoid empty index, so, another loop
	for (int i = indexToRemove; i < set->cardinality - 1; i++) {
		set->elements[i] = set->elements[i + 1];
	}
	//reduce cardinality after shift
	set -> cardinality--;
	//we need to use realloc to fit the new size
	Element* newElement = realloc(set -> elements, (set -> cardinality - 1) * sizeof(Element));
	set -> elements = newElement;
	return 1;//successful
}

/**
 * This function creates and returns a new set, which is united of the given sets.
 */
Set unite(Set s1, Set s2) {
	//create a new set for the union
	Set s3 = initSet();
	//a loop for inserting s1 first
	for (int i = 0; i < s1 -> cardinality; i++) {
		insertElement(s3, s1 -> elements[i]);
	}
	//another loop for inserting s2
	for (int i = 0; i < s2 -> cardinality; i++) {
		//we need to check if the element is already in the set (if s1 already had the same element)
		if (!in(s3, s2 -> elements[i])) {
			insertElement(s3, s2 -> elements[i]);//insert if not already in s3
		}
	}
	return s3; //return union set for s1 and s2
}

/**
 * This function creates and returns a new set, which is intersected of the given sets.
 */
Set intersect(Set s1, Set s2) {
	//new set for intersection
	Set s3 = initSet();
	//kinda the same way as if we're inserting s2 in union, but this time we want the same elements
	for (int i = 0; i < s1 -> cardinality; i++) {
		if (in(s2, s1 -> elements[i])) {
			insertElement(s3, s1 -> elements[i]);
		}
	}
	return s3; //return intersection set for s1 and s2
}

/**
 * This function creates and returns a new set, which is
 * subtracted from the first given set by the second one.
 */
Set substract(Set s1, Set s2) {
	//we don't actually need to remove one by one
	//we can just add the different elements in s1 to a new set to get the result
	//so, again, new set for the subtraction
	Set s3 = initSet();
	for (int i = 0; i < s1->cardinality; i++) {
		//check if s2 does not have the current element as well, then add it to the new set if true
		if (!in(s2, s1 -> elements[i])) {
			insertElement(s3, s1 -> elements[i]);
		}
	}
	return s3; //return subtraction of s2 from s1
}

/**
 * This function prints the given element depending on its type.
 */
void printElement(Element element) {
	//each type needs to have print statement
	if (element -> type == INTEGER) {
		printf("Element is integer: %d\n", *(int*)element -> data);
	}
	else if (element -> type == FLOAT) {
		printf("Element is float: %f\n", *(float*)element -> data);
	}
	else if (element -> type == STRING) {
		printf("Element is string: %s\n", (char*)element -> data);
	}
	else if (element -> type == MATRIX_POINT) {
		int* matrixPoint = (int*)element -> data; //to use each index
		printf("Element is matrix point: (%d, %d, %d)\n", matrixPoint[0], matrixPoint[1], matrixPoint[2]);
	}
}

/**
 * This function prints the given set element by element depending on its type.
 */
void printSet(Set set) {
	//we just need a loop that uses printElement to print elements one-by-one
	printf("Set has elements: \n");
	for (int i = 0; i < set->cardinality; i++) {
		printElement(set -> elements[i]);
	}
}

/**
 * This element deallocates all data in the given set and the set itself.
 */
void freeSet(Set set) {
	//a loop to free each element one-by-one
	for (int i = 0; i < set -> cardinality; i++) {
		freeElement(set->elements[i]);
	}
	//freeing the elements array and set struct
	free(set -> elements);
	free(set);
}
