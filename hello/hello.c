/* $Id: hello.c 6 2011-10-19 12:36:39Z goulas@gmail.com $
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

int main( int argc, char* argv[] )
{
	int id;
	#pragma omp parallel private(id)
	{
		int id = omp_get_thread_num();
		printf( "Hello from OpenMP thread %d\n", id );
	}
	return EXIT_SUCCESS;
}
