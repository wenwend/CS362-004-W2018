/*
 * my_assert.c
 *
 *  Created on: Feb 3, 2018
 *      Author: wenwen
 */
int my_assert(int a, int b){
	if(a==b){
		printf("Success! it passed.\n");
		return 1;
	}
	else{
		printf("Something went wrong...%d != %d \n", a, b);
		return 0;
	}

}



