
import time

start = time.time()

for i in range (6147480):
    print("hola", end="")

end = time.time()

print(f"El tiempo de ejecución ha sido de {end-start} segundos")
