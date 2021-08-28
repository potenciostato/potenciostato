#tabla seno
import math
inicio = 0
final = 1023
cant_muestras_total = 1000
cantidad_muestras = round((cant_muestras_total/2))
for a in range(cant_muestras_total):
    b = round(511.5+511.5*math.sin(((math.pi*2)/cant_muestras_total)*a))
    print("{},".format(b))

#tabla sierra
inicio = 0
final = 1023
cant_muestras_total = 1000
cantidad_muestras = round((cant_muestras_total/2))
for a in range(1,cant_muestras_total+1):
    b = round(((final-inicio)/(cant_muestras_total))*a)
    print("{},".format(b))

#tabla tria
inicio = 0
final = 1023
cant_muestras_total = 1000
cantidad_muestras = round((cant_muestras_total/2))
for a in range(1,cantidad_muestras):
    b = round(((final-inicio)/(cantidad_muestras))*a)
    print("{},".format(b))

for a in reversed(range(cantidad_muestras)):
    b = round(((final-inicio)/(cantidad_muestras))*a)
    print("{},".format(b))