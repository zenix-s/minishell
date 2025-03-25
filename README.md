
# minishell





## Redirecciones del proyecto

# >
	1: Redirección de salida estándar (stdout): >
	
		Descripción: Redirige la salida de un comando hacia un archivo. Si el archivo no existe, se crea. Si el archivo ya existe, se sobrescribe.

		Sintaxis:
			comando > archivo.txt

# >>
	2: Redirección de salida estándar (stdout) en modo de anexado: >>

		Descripción: Redirige la salida de un comando hacia un archivo, pero anexa la salida al final del archivo si ya existe (no sobrescribe).

		Sintaxis:
			comando >> archivo.txt

# <
	3: Redirección de entrada estándar (stdin): <

	Descripción: Toma la entrada desde un archivo en lugar de desde el teclado.

	Sintaxis:
		comando < archivo.txt

# <<
	4: Here dock: <<

	Descripcion: Permite redirigir múltiples líneas de texto directamente como entrada estándar a un comando, sin tener que escribirlas manualmente o desde un archivo.

	Sintaxis:
		comando >> archivo.txt

Hay mas redirecciones de las cuales no hay que hacer caso para este proyecto

Redirección de error estándar (stderr): 2>
Redirección de error estándar (stderr) en modo de anexado: 2>>
Redirección de salida estándar (stdout) y error estándar (stderr) a un mismo archivo: &>
Redirección de salida estándar (stdout) y error estándar (stderr) a un mismo archivo en modo de anexado: &>>
Descarte de salida: > /dev/null o 2> /dev/null

Como funcionan las redirecciones, da igual la cantidad de > o de < que le metas, solo tiene que ejecutar la ultima. Ademas da igual el orden, va a leer antes de escribir, tecnicamente ejecuta todas.... pero sobre escribe la ultima
con heredock tienes que escribir por orden los heredock por los que va a ir avanzando y sobreescribe a partir de que entre en el ultimo. 

## Referente a $? 

Según la salida, el echo $? tiene que devolver un numero distinto, aqui hay unos ejemplos.

0: El comando se ejecutó correctamente sin errores.

1: Generalmente indica un error general. Puede ser usado para muchas situaciones en las que no hay un código de error más específico.

127: Este valor significa que el comando no se encontró (generalmente cuando intentas ejecutar un comando que no existe o no está instalado en tu sistema).

126: Se usa cuando el comando no tiene permisos para ejecutarse. Es decir, la terminal no tiene permisos de ejecución para ese archivo.

2: Suele indicar un error de sintaxis en el comando, como una opción no válida.

128: Este valor se usa cuando un proceso se termina con una señal específica, como un kill o un comando similar. También se utiliza para indicar errores relacionados con señales, como una interrupción del proceso por una señal.

130: Se utiliza cuando un proceso es interrumpido por un Ctrl+C.

137: Este valor suele indicar que el proceso fue terminado por una señal de terminación, como kill -9.

255: Indica un error grave. A menudo se asocia con la salida de programas que terminan con errores de ejecución no esperados.

