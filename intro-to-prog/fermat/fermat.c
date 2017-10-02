#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MINNUM 1990000001
#define MAXNUM 2000000000
#define MAXTRIES 10

int modexp(long long base, long long exp, int mod){
	int result = 1;	
	while (exp > 0){
		if(exp % 2 == 1){
			result = result * base % mod;
		}
		base = (base * base) % mod;
		exp = exp/2;	
	}
	return result;
}

int deterministic(int min, int max){
	int count = 0;
	int p, root;
	int i, j;
	int isprime;

	for(p = (min % 2 == 0 ? min + 1 : min); p <= max; p += 2){ //No need to check if even numbers are prime
		if(p % 3 == 0){
			continue;
		}
		else if(p % 5 == 0){
			continue;
		}
		else{
			isprime = 1;
			root = (int) sqrt(p);
			j = 2;
			for(i = 7; i <= root; i += j){
				if(p % i == 0){
					isprime = 0;
					break;
				}
				j = 6 - j; //if j == 4 then j becomes 2 and the opposite
				//this way the program skips the factors of 3 and 2
			}
			if (isprime){
				count++;
			}
		}
	}

	return count;
}

int fermat(int min, int max, int tries){
	int p;
	long a;

	int try;
	int isprime;

	int count = 0;

	for(p = min; p <= max; p++){
		for(try = 1; try <= tries; try++){
			a = (rand() % (p - 1)) + 1;
			if(modexp(a, p-1, p) == 1){
				isprime = 1;
			}
			else{
				isprime = 0;
				break;
			}		
		}
		if(isprime){
			count++;
		}
	}

	return count;
}

int main(void){
	int count;
	int tries;
	double sttime,endtime;
	
	int seed = time(NULL);
	srand(seed);


	printf("Checking range [%d,%d] for primes.\n\n",MINNUM,MAXNUM);
	
	sttime = ((double) clock())/CLOCKS_PER_SEC;
	count = deterministic(MINNUM, MAXNUM);
	endtime = ((double) clock())/CLOCKS_PER_SEC;
	
	printf("Deterministic algorithm: Found %d primes in %.2f secs\n\n", count, endtime-sttime);
	

	printf("Trying Fermat test with seed = %d \n\n",seed);
	
	for(tries = 1; tries <= MAXTRIES; tries++){
		sttime = ((double) clock())/CLOCKS_PER_SEC;
		count = fermat(MINNUM, MAXNUM, tries);
		endtime = ((double) clock())/CLOCKS_PER_SEC;
		
		printf("Probabilistic algorithm: Found %d primes in %.2f secs (tries = %d)\n", count, endtime-sttime, tries);
	}
	
	return 0;
}
