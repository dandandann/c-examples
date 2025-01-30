
#include <stdio.h>


void display(int nums[], int n){
	for(int i = 0 ; i < n ; i++){
		printf("%d ", nums[i]);
	}
	printf("\n");
}

void merge(int nums[], int left,int mid, int right){
	// Create 2 sub array from main array
	// set size of 2 sub arrays
	int sizeLeft = mid - left + 1;
	int sizeRight = right - mid; // Nentuin size kiri
	// Contoh : 1 2 3 78 90 -> 1 2 3 || 78 90
	//          0 1 2  3  4
	// sizeLeft = 2 - 0 + 1 = 3 -->  3 angka di left
	// sizeright = right - mid = 4 - 2 = 2
	
	// Create 2 sub arrays;
	
	int arrLeft[sizeLeft];
	int arrRight[sizeRight];
	
	// Fill both 2 sub arrays
	// Value taken from main array
	for(int i = 0 ; i < sizeLeft ;i++){
		arrLeft[i] = nums[left + i];
//		printf("%d ", arrLeft[i]);
	}
//	printf("\n");
	for(int i = 0 ; i < sizeRight ; i++){
		arrRight[i] = nums[mid + 1 + i];
//		printf("%d ", arrRight[i]);
	}
	


//	printf("\n\n");
	
	int currLeft = 0, currRight = 0, currNums = left;
	while(currLeft < sizeLeft && currRight < sizeRight){
		// Compare
		if(arrLeft[currLeft] < arrRight[currRight]){
			nums[currNums] = arrLeft[currLeft];
			currLeft++;
		}
		else{
			nums[currNums] = arrRight[currRight];
			currRight++;
		}
		currNums++;
	}
	
	// Fill leftover from both sub arrays
	
	while(currLeft < sizeLeft){
		nums[currNums] = arrLeft[currLeft];
		currLeft++;
		currNums++;
	}
	
	while(currRight < sizeRight){
		nums[currNums] = arrRight[currRight];
		currRight++;
		currNums++;
	}
}

void mergeSort(int nums[], int left, int right){
//	int pivot =
//	printf("%d %d\n", left, right);
	
	// Setiap kali kita mau split, kita harus tau case2nya
	// Base one
	 if (left >= right){
	 	return;
	 }
	 
	int mid = (left + right)/2;
	mergeSort(nums, left, mid);
	mergeSort(nums, mid + 1 , right);
	merge(nums, left, mid, right);
}
//////////////////////////////////////

void binarySearch(int arr[], int n, int search){
	int left = 0;
	int right = n-1;
	
	while(left <= right){
		int mid = (left+right)/2;
	
		printf("%d", arr[mid]);
		if(arr[mid] == search){
			printf("You found %d", search);
			return;
		
		}else if(arr[mid] < search){
			right = mid - 1;
			
		}else{
			left = mid + 1;	
		}
		
	}
	
	printf("%d Not Found", search);
}


///////////////////////////////////////
int main(){
	int nums[] = {1, 5, 5, 5, 7, 7};
//	int nums[] = {24, 10, 5};
	
	int n = sizeof(nums) / sizeof(nums[0]); // 8 
//	printf("abc %d %d\n %d\n", sizeof(nums),  sizeof(nums[0]), sizeof(nums)/sizeof(nums[0]));
	display(nums, n);
	mergeSort(nums, 0, n-1);
	display(nums, n);
	int target;
	scanf("%d", &target);
	getchar();
	binarySearch(nums, n, target);
	
	return 0;
}
