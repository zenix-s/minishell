
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


TODO

----> union de gran pipex con redirecciones

----> dejar las redirecciones bien del todo... 

		- ahora mismo en las redirecciones ls >a <b | grep >b <a e 
					-> lo hace bien pero no da los mensajes de errores bien


