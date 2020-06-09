reset
set xrange[-2.0:0.5]
set yrange[-1.2:1.2]
unset ztics

# set dgrid3d
set cntrparam levels auto 50
# set key outside top right
unset surface
set contour
set isosamples 5000
set map cartesian
set view map
set palette rgbformulae 33,13,10


splot "mandelbrot_data_points.txt" u 1:2:3 w lines notitle
# splot "lab2.dat" u 1:2:3 w lines notitle palette



set terminal epslatex standalone color 12
set output "mandelbrot_fractal.tex"
replot




# reset

# set xrange[-2.0:0.5]
# set yrange[-1.2:1.2]

# set key outside top right
# set cntrparam levels auto 25
# unset ztics
# set key outside top right
# unset surface
# set isosamples 50
# set view map

# set contour
# set ticslevel 0.8
# unset colorbox


# splot 'lab2.dat' u 1:2:3 w lines notitle palette

# set terminal png
# set output "mandelbrot_fractal.png"
# replot

# pause -1
