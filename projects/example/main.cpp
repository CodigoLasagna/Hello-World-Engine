//nr 1
#include "../../HelloWorldEngine.h"

int main(){
	//para iniciar un proyecto, se debe de crear un objeto de rénder antes que cualquier otro objeto.
	//el de abajo por ejemplo, está hecho para funcionar con uno de los 2 tipos disponibles
	//el renderizado de tipo 0, funciona en tiempo real, con la velocidad actual de tu equipo,
	//el renderizado de tipo 1, funciona con un delay en milisegundos para un loop de juego
	//mejor controlado.
	Renderer* main_env = new Renderer(1, 40, 40, 95); // aquí generaremos un objeto de tiempo controlado y 95ms de delay.
	
	//Después procedemos a definir una ventana, puedes tener el número de ventanas que quieras en tu juego.
	//aquí pediremos el tamaño actual con el que se comenzó la terminal, no es necesario hacer este paso, pero
	//puede ser útil.
	double term_w = main_env->get_term_size('w'), term_h = main_env->get_term_size('h');
	//Ahora originaremos las ventanas, hay dos formas de hacerlo, dependerá de ti como organizarlas
	//esta es la primera forma, declara una sola ventana o panel, es casi como declarar una variable,
	//si sabes declarar objetos con base a clases dentro de c++, no debería resultar ajeno
	//en este caso se crea una ventana/panel llamada terminal, que es justamente del ancho y alto de
	//la terminal, se dibuja desde el centro.
	Window terminal = Window(term_w, term_h, 0, 0, false, main_env);
	//y aquí está la manera complicada, pero muy útil si quieres crear varios menús o ventanas a utilizar
	//en tu juego.
	Window* win = new Window[2]{//aquí el número de ventanas a generar
		Window(14, 8, 1, 15, true, main_env),// aquí dibujamos la ventana desde la esquina superior izquierda
								   // con 14 unidades de ancho y 8 unidades de alto,
								   // y la movemos una unidad hacia la derecha, y otras 15 unidades
								   // hacia abajo, por eso el valor final está en true.
								   // porque permite esta clase de formato.
								   // por el contrario...
		Window(30, 20, 12, 0, false, main_env)//aquí dibujamos la ventana desde el centro, y la movemos 12 unidades a la derecha
									//, pero 0 unidades en el eje hacia abajo o arriba porque ya está centrada
									//esta ventana mide 30 unidades de ancho y 20 de alto.
	};
	
	//ahora generaremos objetos
	//hay tres formas de crearlos.
	Instance* player = instance_create(1, 10, '@');//aquí simplemente generamos un solo objeto
												   //en este caso será el jugador, no crearemos ningún otro
												   //objeto de este tipo, así que este formato es útil
												   //para objetos únicos dentro de nuestro juego.
												   //en este caso el jugador se genera una unidad a la derecha
												   //y 10 unidades hacia abajo, además de tener como icono
												   //o sprite el carácter de texto @.
	Instance* enemy = new Instance[2]{
		Instance(2, 2, 'O'),//aquí se generarán varios objetos, sí sabemos que queremos y podemos permitir
		Instance(5, 2, 'O')// el tiempo de definirlos, es bastante útil, creamos varios objetos
						   // y declaramos sus especificaciones al momento de hacerlo.
						   // el primer objeto se declara 2 unidades hacia la derecha y hacia abajo,
						   // con el carácter de texto O.
						   // mientras que el segundo se declara 5 unidades a la derecha y 2 unidades
						   // hacia abajo, también con el carácter de texto O.
	};
	Instance* wall = new Instance[10]{};//la última forma ya es un poco más técnica, pero permite crear
										//varios objetos del mismo tipo, y luego preocuparse de sus valores
										//independientes, básicamente es para crear objetos en masa.
										//los objetos ya tienen valores base, que puedes revisar dentro
										//del '.h' de esta librería.
	for (int i = 0; i < 10; i++){//aquí iniciaremos un loop para poder darles valores "específicos" a los objetos
		wall[i].m_coordx = i+2; // en este caso cada objeto se moverá una unidad más a la derecha que el anterior
		wall[i].m_coordy = 3;   // y todos estarán 3 unidades hacia abajo.
	}
	// como se observa en el paso anterior, podemos modificar valores independientes de los objetos
	// que generamos incluso después de su creación, podemos modificar
	// su posición, su sprite/icono, e incluso su color, así como un valor interno de estado
	// con el que podrán jugar y probar cosas.
	
	enemy[0].m_fgcolor = C_RED;//aquí cambié el color del enemigo 0 por el color rojo
	enemy[1].m_fgcolor = C_GREEN;//y aquí el del enemigo 1 por el color verde
	player->m_fgcolor = C_CYAN;//el color del jugador por el color cyan
	player->m_bcolor = true;//además de que podemos hacerlo bold o negritas para contrastar aún más
	for (int i = 0; i < 10; i++){
		wall[i].m_fgcolor = C_WHITE;
		wall[i].m_bgcolor = C_MAGENTA;//Además puedes cambiar el color del fondo
									  //, pero para tener cualquier tipo de fondo en un objeto
									  //debes de agregar un color de contexto para el
									  //objeto antes.
	}
	
	//Ahora trabajaremos creando un loop para nuestro juego
	char key{};//es recomendable tener un método de escape, para salir rápidamente del loop
			   //en este caso declararemos una variable de carácter
			   //para utilizar también en caso de que queramos crear inputs/controles
	while (key != 'q') {//iniciamos un ciclo while y de condición ponemos que se detenga si se presiona
						//la tecla Q de nuestro teclado.
		
		main_env->start_renderer(); //esta es nuestra función para comenzar nuestro
									//renderizado, es importante colocarla al inicio de
									//nuestro ciclo.
		terminal.clean();// de esta forma se limpian las ventanas/paneles
		win[0].clean(); //  para borrar cualquier cosa que pueda duplicarse
		win[1].clean(); //  de forma gráfica.
		
		instance_draw(win[0], &enemy[0]);// de esta manera dibujamos dentro de nuestros paneles
		instance_draw(win[0], &enemy[1]);// declaramos en que espacio/ventana y luego en el caso de objetos
											 // en un array, referenciamos el objeto que queremos con & antes
											 // de su nombre y número en el array.
		instance_draw(win[1], player);// cuando se trata de objetos únicos ignoramos el & y colocamos el nombre
										  // sin más.
		for (int i = 0; i < 10; i++){ //podemos aprovechar ciclos para dibujar objetos en un array
			instance_draw(terminal, &wall[i]);//de la misma forma, tenemos que referenciarlos con &
		}
		
		player->m_coordx += 1;// y como mencionamos previamente, podemos cambiar valores de nuestros
							  // objetos incluso después de declararlos, en este caso
							  // el objeto jugador se mueve a la derecha 1 unidad cada ciclo.
		
		key = getch();//aquí simplemente esperamos a que se introduzca el input esperado para cualquier
					  //acción deseada, si presionamos Q el ciclo lo declarara aquí y saldrá del juego.
		
		main_env->update_renderer();//para finalizar aquí está nuestra función para actualizar
									//todo el contexto general de nuestro rénder,
									//es importante ponerlo al final de nuestro ciclo,
									//, ya que indica el cierre de toda acción en nuestro juego
	}
	
	endwin();//Finalizamos el modo curses
	return 0;//retornamos 0 para acabar el programa correctamente.
}
