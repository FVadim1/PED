#Si tus ficheros de prueba no comienzan por "tad", cambia "tad*.cpp" por el prefijo de tus ficheros, por ejemplo "prueba*.cpp":
VAR=0;
VAR2=0;

for FILE in *pruebas/tad*.cpp ; do 
	echo "Evaluando $FILE"
	#Si tu Makefile espera que el fichero que contiene el programa principal se llame tad.cpp, cambia la siguiente línea por: cp $FILE src/tad.cpp
	cp $FILE src/tad.cpp 
        rm -f ./main
	make
	./main > $FILE.out
	diff -b -B -i $FILE.out $FILE.sal
	
	if [ "$?" == "0" ]; then
		echo "OK"
		VAR=`expr $VAR + 1`
	else
		echo "ERROR"
        VAR2=`expr $VAR2 + 1`
	fi
	
	echo
done

echo "###########################"
echo "PRUEBAS CORRECTAS: $VAR" 
echo "PRUEBAS INCORRECTAS: $VAR2"
echo "###########################"

if [ "$VAR2" -lt 1 ]; then
    echo
    echo "~ 100 % COMPLETADO ~"
    echo
    echo "Ha saltado Copia, A Paco Moreno que vas"
else
    echo 
    echo "=C"
fi

