#include "msort.h"
#include "student.h"
#include <stdio.h>

#ifndef OMIT_MSORT
void msort(Student * base, int nel, int (*compar)(const void *, const void *)) {
	//clarification of inputs into msort function

	//Base case: if the array has one or fewer elements, it's already sorted
	//so just return.
	if((nel) <= 1){
	return;
	}
	int midpointval = (nel/2);

	//FILL IN 
	
	//Inductive case: split the array in two, sort the two pieces with msort,
	//merge the	sorted pieces
	
		
	//We're going to do this without explicitly creating the two separate arrays
	//We'll take advantage of the fact that to C, an array is just a pointer to
	//a region of memory. If we call msort on base, but pass in a smaller number
	//of elements, it will sort just that subarray. Similarly, if we call msort
	//but pass in the address of an element in the middle of the array, it will
	//sort the array *starting* from that element.
		
	//1. Find the midpoint of the array
	
	//FILL IN
	
	//2a. Sort the first half of the array (remember to adjust the # elements)
	
	//FILL IN
	msort(base, midpointval, compar);
	
	//2b. Sort the second half of the array. Pass in the address of the 
	//beginning of the second half of the array (remember to use the right # of 
	//elements)

	//FILL IN
	msort(&base[midpointval], nel-midpointval, compar);  
	//3a. Merge the two arrays (use merge)
	Student * merger = merge(base,midpointval, &base[midpointval], (nel-midpointval), compar);

	//FILL IN
	
	//3b. Copy the merged array over top of the original array (use copy)
	//Don't forget to free the array you no longer need!
	copy(base,merger,nel);
	//FILL IN
	free(merger);
	return;
}
#endif

#ifndef OMIT_MERGE
Student * merge(Student * base1, int nel1, Student * base2, int nel2, int (*compar)(const void *, const void *)) {
	
	//1. Allocate space for the returned merged array
	
	//FILL IN
	Student* mergedfirst = malloc(sizeof(Student)*(nel1+nel2));
	
	//2. Create indices to keep track of where you are in the three arrays

	//FILL IN
	int left1 = 0;
	int right1 = 0;
	int m1 = 0;
	
	//3. Go through base1 and base2, and merge them into the returned array
	while ((left1 < nel1) && (right1 < nel2))
	{
		if(compar(&base1[left1], &base2[right1]) < 1)//equal to 0 or negative one 
		{
			mergedfirst[m1] = base1[left1];
			left1++;
			m1++;
		}
		else if(compar(&base1[left1], &base2[right1]) >= 1)
		{
			mergedfirst[m1] = base2[right1];
			right1++;
			m1++;			
		}
	}
		if(right1 == nel2)
		{
			while(left1 < nel1)
			{
				mergedfirst[m1] = base1[left1];
				left1++;
				m1++;
			}
		}
		if(left1 == nel1)
		{
			while(right1 < nel2)
			{
				mergedfirst[m1] = base2[right1];
				right1++;
				m1++;
			}
		}
	
	//FILL IN
	
	//4. Return the merged array
	return(mergedfirst);
	//FILL IN

}


void copy(Student * to, Student * from, int nel) {
	/*
	An efficient implementation of this would use memcpy:
	memcpy(to, from, nel * width);

	We will do an element-by-element copy so you can see how it is done
	*/
	
	//loop over the from array and copy it byte by byte to the to array.
	for (int i = 0; i < nel; i++) {
		to[i] = from[i];
	}
	
	return;
}
#endif
