
media_triangular = []
valor_max = 255
frec = 1
cant_puntos = 100
ts_ms = int(1000/(frec*2*cant_puntos))
t_rise = 0.0001
t_fall = t_rise
for i in range(cant_puntos):
	media_triangular.append(int((valor_max/cant_puntos)*i))

for i in range(cant_puntos):
	media_triangular[i] = round(media_triangular[i] * 3.2/256,4)
pwl = "("
t = 0
for i in range(cant_puntos):
	t+=ts_ms
	pwl+=str(t)+"m "+str(media_triangular[i])+" "+str(t+ts_ms-t_rise)+"m "+str(media_triangular[i])+" "

for i in reversed(range(cant_puntos-1)):
	t+=ts_ms
	pwl+=str(t)+"m "+str(media_triangular[i])+" "+str(t+ts_ms-t_fall)+"m "+str(media_triangular[i])+" "
t+=ts_ms
pwl+=str(t)+"m "+str(media_triangular[0])+")"
print(pwl)