# Configuración básica
set title "Tiempos de Busqueda dentro del Arbol B-tree"
set xlabel "Ejecuciones"
set ylabel "Tiempo (s)"
set grid
set style data linespoints

# Ploteo de los tres archivos
plot "search_3.txt" using 0:1 title "MaxKeys 3" lt rgb "red" lw 2, \
     "search_4.txt" using 0:1 title "MaxKeys 4" lt rgb "blue" lw 2, \
     "search_5.txt" using 0:1 title "MaxKeys 5" lt rgb "green" lw 2
