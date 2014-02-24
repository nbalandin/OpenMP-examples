/* $Id: tasks.c 10 2011-10-20 11:22:50Z goulas@gmail.com $
 *
 * Copyright 2011 George Goulas
 * Available from http://code.google.com/p/goulas-openmp-demos
 *
 * This file is part of goulas-openmp-demos.
 *
 * goulas-openmp-demos is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 3 of the 
 * License, or (at your option) any later version.
 *
 * goulas-openmp-demos is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with goulas-openmp-demos.  
 * If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define SIZE 1000000
#define MAXEL 100
#define SAFE_MALLOC(v,t,n) if((v=(t*)malloc( (n)*sizeof(t)))==NULL) return EXIT_FAILURE;
#define SAFE_EXEC( f ) if( f==EXIT_FAILURE) return EXIT_FAILURE;

int *a, *b, *c, *cv, *d, *dv;

int allocate_vectors( void )
{
	SAFE_MALLOC(a, int, SIZE);
	SAFE_MALLOC(b, int, SIZE);
	SAFE_MALLOC(c, int, SIZE);
	SAFE_MALLOC(cv, int, SIZE);
	SAFE_MALLOC(d, int, SIZE);
	SAFE_MALLOC(dv, int, SIZE);
	return EXIT_SUCCESS;
}

void random_init( void )
{
	srand( time(NULL) );
	for( int i=0; i<SIZE; i++ ) {
		a[i] = rand() % MAXEL;
		b[i] = rand() % MAXEL;
	}	
}

int main( int argc, char* argv[] )
{
	int i;
	double start_time, end_time;

	printf("\nParallel tasks\n\nSize %d\n", SIZE);

	SAFE_EXEC( allocate_vectors() );		
	random_init();

	// Serial alternative
	start_time = omp_get_wtime();
	for( i=0; i<SIZE; i++ ) {
		cv[i] = a[i] + b[i];
		dv[i] = a[i] - b[i];
	}
	end_time = omp_get_wtime();
	printf("Serial run time: %f msec\n", (end_time-start_time)*1000);

	// Parallel alternative
	#pragma omp parallel shared(a,b,c,d)
	{
		#pragma omp single nowait
		{
			start_time = omp_get_wtime();
			
			#pragma omp task shared(a,b,c) private(i)
			{
				for( i=0; i<SIZE; i++) {
					c[i] = a[i] + b[i];
				}
			}
			#pragma omp task shared(a,b,d) private(i)
			{
				for( i=0; i<SIZE; i++) {
					d[i] = a[i] - b[i];
				}
			}
		}
	}
	end_time = omp_get_wtime();
	printf("Parallel run time: %f msec\n", (end_time-start_time)*1000);

	printf("Comparing results for c: ");
	if(memcmp(c, cv, SIZE*sizeof(int)))
		printf("FAILURE\n");
	else
		printf("SUCCESS\n");
	printf("Comparing results for d: ");
	if(memcmp(d, dv, SIZE*sizeof(int)))
		printf("FAILURE\n");
	else
		printf("SUCCESS\n");

	free(a);
	free(b);
	free(c);
	free(cv);
	return EXIT_SUCCESS;
}
