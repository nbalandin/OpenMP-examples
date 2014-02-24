#  $Id: common.mk 10 2011-10-20 11:22:50Z goulas@gmail.com $
#  
#  Copyright 2011 George Goulas
#  Available from http://code.google.com/p/goulas-openmp-demos
#  
#  This file is part of goulas-openmp-demos.
#  
#  goulas-openmp-demos is free software: you can redistribute it and/or 
#  modify it under the terms of the GNU General Public License as 
#  published by the Free Software Foundation, either version 3 of the 
#  License, or (at your option) any later version.
#  
#  goulas-openmp-demos is distributed in the hope that it will be 
#  useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
#  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with goulas-openmp-demos.  
#  If not, see <http://www.gnu.org/licenses/>.
CC	:= gcc
override CFLAGS	+= -fopenmp -std=c99 -Wall
override LDFLAGS	+= -fopenmp

.PHONY: all clean

all:	${TARGET}

${TARGET}:	$(OBJ)

clean:
	$(RM) -f $(OBJ) $(TARGET)
