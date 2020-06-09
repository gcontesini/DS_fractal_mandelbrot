import numpy as np
import math

def format(value):
    return "%.16f" %value


def main():

	data_pnts_file = open("mandelbrot_data_points.txt","w")

	num_steps_int = 10000
	i_index_int= -1*num_steps_int-1

	real_part_dbl = -2.0

	for x_index_int in np.arange(1001):
		
		img_part_dbl = -2.0

		for y_index_int in np.arange(1001):

			const_cmplx = complex( real_part_dbl, img_part_dbl )

			z_cmplx = complex( 0.0, 0.0 )	

			key_bool = 1
			
			while( key_bool == 1 ):

				z_cmplx = z_cmplx*z_cmplx + const_cmplx 

				if( abs(z_cmplx) >= 2.0 ):
					key_bool = 0

				if( i_index_int == num_steps_int ):
					key_bool = 0

				i_index_int = i_index_int + 1 

			data_pnts_file.write( \
				format(const_cmplx.real) + "\t" +\
				format(const_cmplx.imag) + "\t" +\
				str(i_index_int)  + "\n" ) 

			i_index_int= -1*num_steps_int-1

			img_part_dbl = img_part_dbl + 0.01

		data_pnts_file.write(" \n")

		real_part_dbl = real_part_dbl + 0.01
		
	data_pnts_file.close()
		
if __name__ == '__main__':
	main()