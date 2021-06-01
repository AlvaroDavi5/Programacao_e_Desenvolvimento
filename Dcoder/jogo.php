<?php
   //php 7.3.0
/**
 * genera un arreglo de palabras para jugar
 * @return array
 */
function cargarPalabras(){
  //array ScoleccionPalabras
  $coleccionPalabras = array();//Se inicializa el arreglo
  $coleccionPalabras[0] = array("palabra"=> "papa" , "pista" => "se cultiva bajo tierra ", "puntosPalabra"=>2);//precargar el arreglo
  $coleccionPalabras[1] = array("palabra"=> "hepatitis" , "pista" => "enfermedad que inflama el higado ", "puntosPalabra"=> 10);
  $coleccionPalabras[2] = array("palabra"=> "volkswagen" , "pista" => "marca de vehiculo ", "puntosPalabra"=> 5);
  $coleccionPalabras[3] = array("palabra"=> "pelicula" , "pista" => "resumen de una novela", "puntosPalabra"=> 8);
  $coleccionPalabras[4] = array("palabra"=> "clima" , "pista" => "condicion atmosferica", "puntosPalabra"=> 7);
  $coleccionPalabras[5] = array("palabra"=> "olimpiada" , "pista" => "fiesta deportiva", "puntosPalabra"=> 9);
  $coleccionPalabras[6] = array("palabra"=> "sonrisa" , "pista" => "traduccion de SMILE al espaniol", "puntosPalabra"=> 6);

  return $coleccionPalabras;//Retornamos el arreglo


}

/**
 * indice de palabra
 *@return array
 */


function cargarJuegos(){
  //array $coleccionJuegos
  $coleccionJuegos = array();
  $coleccionJuegos[0] = array("puntos"=> 2, "indicePalabra" => 0);
  $coleccionJuegos[1] = array("puntos"=>10 ,"indicePalabra" => 1);
  $coleccionJuegos[2] = array("puntos"=> 5, "indicePalabra" => 2);
  $coleccionJuegos[3] = array("puntos"=> 8, "indicePalabra" => 3);
  $coleccionJuegos[4] = array("puntos"=> 7, "indicePalabra" => 4);
  $coleccionJuegos[5] = array("puntos"=> 9, "indicePalabra" => 5);
  $coleccionJuegos[6] = array("puntos"=> 6, "indicePalabra" => 6);


  return $coleccionJuegos;
}

/**
 * a partir de la palabra genera un arreglo para determinar si sus letras fueron o no descubiertas
 * @param string $palabra
 * @return array
 */
function dividirPalabraEnLetras($palabra){
  //booleand $coleccionLetras
  //string $palabras
  //int $i
  $coleccionLetras= array();
  $palabras=strtolower($palabra);//STRTOLOWER obligamos a que las letras esten todas en minuscula
  
  for ($i = 0; $i<strlen($palabras); $i++){
    $coleccionLetras[$i] = array("letra" => $palabras[$i],"descubierta" => false);//Creamos un arreglo para guardar las letras de la palabra y determinamos si fueron descubierta

  }
  return $coleccionLetras;
}

/**
 * muestra y obtiene una opcion de menu valida
 * @return int
 */
function seleccionarOpcion(){
  echo "--------------------------------------------------------------\n";
  echo "\n ( 1 ) Jugar con una palabra aleatoria";
  echo "\n ( 2 ) Jugar con una palabra elegida";
  echo "\n ( 3 ) Agregar una palabra al listado";
  echo "\n ( 4 ) Mostrar la informacion completa de un numero del juego";
  echo "\n ( 5 ) Mostrar la informacion completa del primer juego con mas puntaje";
  echo "\n ( 6 ) Mostrar la informacion completa del primer juego que supere un puntaje indicado por el usuario";
  echo "\n ( 7 ) Mostrar la lista de palabra ordenada por puntaje ";
  echo "\n ( 8 ) salir";
  do {
    echo "\n Indique una opcion valida:";
    $opcion=trim(fgets(STDIN));
  }while ($opcion<0||$opcion>8) ;


  echo "--------------------------------------------------------------\n";
  return $opcion;
}

/**
 * Determina si una palabra existe en el arreglo de palabras
 * @param array $coleccionPalabras
 * @param string $palabra
 * @return boolean
 */
function existePalabra($coleccionPalabras,$palabra){
  //boolean $existe
  //int $i, $cantPal
  $i=0;
  $cantPal = count($coleccionPalabras);
  $existe = false;
  while($i<$cantPal && !$existe){
    $existe = $coleccionPalabras[$i]["palabra"] == $palabra;
    $i++;
  }

  return $existe;
}

/**
 * Determina si una letra existe en el arreglo de letras
 * @param array $coleccionLetras
 * @param string $letra
 * @return boolean
 */
function existeLetra($coleccionLetras,$letras){
  //boolean $existLetra
  // int $i,$cantLetra
 
  $i=0;
  $cantLetra = count($coleccionLetras);
  $existLetra = false;
  while($i<$cantLetra && !$existLetra){
    $existLetra = $coleccionLetras[$i]["letra"] == $letras;
    $i++;
  }

  return $existLetra;
}
/**
 * Solicita los datos correspondientes a un elemento de la coleccion de palabras: palabra, pista y puntaje.
 * Verifica que la palabra ingresada por el usuario no exista en la coleccion de palabras.
 * @param array $coleccionPalabras
 * @return array
 */
function palabraUsuario($coleccionPalabras) {
  //boolean $existPalabra
  //string $palabraUs,$pista
  //int $puntosPalabra,$i

  echo "ingrese la palabra:";
  $palabraUs=trim(fgets(STDIN));
  $palabraUs=strtolower($palabraUs);
  $existPalabra=existePalabra($coleccionPalabras, $palabraUs);//llamo a la funcion existePalabra para determinar si la palabra ingresada existe

  while ($existPalabra) {
    echo "la palabra ya existe \n";
    echo "ingrese otra palabra:";
    $palabraUs=trim(fgets(STDIN));
    $palabraUs=strtolower($palabraUs);
    $existPalabra=existePalabra($coleccionPalabras, $palabraUs);
  }
  echo "ingrese pista:" ;
  $pista=trim(fgets(STDIN));
  echo "ingrese puntos:";
  $puntosPalabra=trim(fgets(STDIN));

  $i=count($coleccionPalabras);
  $coleccionPalabras[$i]=array("palabra"=>$palabraUs,"pista"=>$pista,"puntosPalabra"=>$puntosPalabra);

  return $coleccionPalabras;
}


/**
 * Obtener indice aleatorio
 * @param int $min
 * @param int $max
 * @return int
 */
function indiceAleatorioEntre($min,$max){
  $i = rand($min,$max); // /*>>> RAND - Genera un numero entero aleatorio <<<*/
  return $i;
}

/**
 * solicitar un valor entre min y max
 * @param int $min
 * @param int $max
 * @return int
 */
function solicitarIndiceEntre($min,$max){
  do{
    echo "Seleccione un valor entre $min y $max: ";
    $i = trim(fgets(STDIN));
  }while(!($i>=$min && $i<=$max));

  return $i;
}



/**
 * Determinar si la palabra fue descubierta, es decir, todas las letras fueron descubiertas
 * @param array $coleccionLetras
 * @return boolean
 */
function palabraDescubierta($coleccionLetras){
  //boolean $palabraD
  //int $i,$i2

  $palabraD=false;
  $i=count($coleccionLetras);
  $i2=0;

  foreach($coleccionLetras as $indice => $des){

    if($des["descubierta"]==(!$palabraD)){//determino si la letra fue descubierta e incremento el contador
      $i2++;
    }
  }
  if ($i==$i2) {
    // se compara los contadores y si son iguales significa que se ha descubierto la palabra
    $palabraD=true;
  }

  return $palabraD;
}


/**
 * verifica si la letra ingresada es correcta
 * @return string
 */

function solicitarLetra(){
  $letraCorrecta = false;
  do{
    echo "Ingrese una letra: ";
    $letra = strtolower(trim(fgets(STDIN)));
    if(strlen($letra)!=1){
      echo "Debe ingresar 1 letra!\n";
    }else{
      $letraCorrecta = true;
    }

  }while(!$letraCorrecta);

  return $letra;
}

/**
 * Descubre todas las letras de la coleccion de letras iguales a la letra ingresada.
 * Devuelve la coleccionLetras modificada, con las letras descubiertas
 * @param array $coleccionLetras
 * @param string $letra
 * @return array
 */
function destaparLetra($coleccionLetras, $letra){
  //int $i, $sumaP

  $sumaP=count($coleccionLetras);
  for($i=0; $i < $sumaP;$i++){

    if($coleccionLetras[$i]["letra"] == $letra){
      $coleccionLetras[$i]=["letra"=>$letra,"descubierta"=>true];
    }
  }
  return $coleccionLetras;
}

/**
 * obtiene la palabra con las letras descubiertas y * en las letras no descubiertas. Ejemplo: he**t*t*s
 * @param array $coleccionLetras'
 * @return string
 */
function stringLetrasDescubiertas($coleccionLetras){
  //string $pal
  //boolean $descubiert
  $pal= "";
  $descubiert=false;
  foreach($coleccionLetras as $indice => $letraDes){
    if($letraDes["descubierta"] == (!$descubiert)){
      $pal=$pal.($letraDes["letra"]);
    }else{
      $pal= $pal.("*");
    }
  }
  return $pal;
}


/**
 * Desarrolla el juego y retorna el puntaje obtenido
 * Si descubre la palabra se suma el puntaje de la palabra mas la cantidad de intentos que quedaron
 * Si no descubre la palabra el puntaje es 0.
 * @param array $coleccionPalabras
 * @param int $indicePalabra
 * @param int $cantDeIntentos
 * @return int
 */
function jugar($coleccionPalabras,$indicePalabra, $cantDeIntentos){
  // string $p, $letra, $letra2
  // array $coleccionLetras, $descubiertas
  // boolean $pal2, $palabraFueDescubierta, $existe
  // int $puntaje

  $p = $coleccionPalabras[$indicePalabra]["palabra"];
  $coleccionLetras = dividirPalabraEnLetras($p);
  $puntaje = 0;
  $palabraFueDescubierta=false;

  echo "pista : " .$coleccionPalabras[$indicePalabra]["pista"] ."\n"; //Mostrar pista:
  $descubiertas = array();

  do{
    $letra= solicitarLetra();
    $existe= existeLetra($coleccionLetras, $letra);
    
    if($existe){
      echo "La letra: ". $letra ." PERTENECE a la palabra \n";
      $descubiertas= destaparLetra($coleccionLetras,$letra);
      $letra2= stringLetrasDescubiertas($descubiertas);
      echo $letra2. "\n";
      $coleccionLetras=$descubiertas;

    }else{
      
      $cantDeIntentos--;
      
      echo "la letra: " . $letra ." NO PERTENECE a la palabra. QUEDAN " . $cantDeIntentos . " Intentos \n";
    }
    
    $palabraFueDescubierta = palabraDescubierta($descubiertas);
    
  }while(0<$cantDeIntentos && !$palabraFueDescubierta);

  if($palabraFueDescubierta){
    $puntaje=$coleccionPalabras[$indicePalabra]["puntosPalabra"]+$cantDeIntentos;
    echo "\n¡¡¡¡¡¡¡GANASTE ".$puntaje." puntos!!!!!!!\n";
  }else{
    echo "\n¡¡¡¡¡¡¡AHORCADO AHORCADO!!!!!!!\n";
  }

  return $puntaje;

}

/**
 * Agrega un nuevo juego al arreglo de juegos
 * @param array $coleccionJuegos
 * @param int $puntos
 * @param int $indicePalabra
 * @return array
 */
function agregarJuego($coleccionJuegos,$puntos,$indicePalabra){
  // array $coleccionJuegos
  //int $i
  $i=count($coleccionJuegos);
  $coleccionJuegos[$i] = array("puntos"=> $puntos, "indicePalabra" => $indicePalabra);
  return $coleccionJuegos;
}

/**
 * Muestra los datos completos de una palabra
 * @param array $coleccionPalabras
 * @param int $indicePalabra
 */
function mostrarPalabra($coleccionPalabras,$indicePalabra){
  //$coleccionPalabras[0]= array("palabra"=> "papa" , "pista" => "se cultiva bajo tierra", "puntosPalabra"=>7);

  echo"Palabra: ". $coleccionPalabras[$indicePalabra]["palabra"]."\n";
  echo"Pista: ". $coleccionPalabras[$indicePalabra]["pista"] ."\n";
  echo"Puntos: ". $coleccionPalabras[$indicePalabra]["puntosPalabra"] ."\n";
  echo "\n";

}

/**
 * Muestra los datos completos de un juego
 * @param array $coleccionJuegos
 * @param array $coleccionPalabras
 * @param int $indiceJuego
 */
function mostrarJuego($coleccionJuegos,$coleccionPalabras,$indiceJuego){
  //array("puntos"=> 8, "indicePalabra" => 1)
  echo "\n\n";
  echo "<-<-< Juego ".$indiceJuego." >->->\n";
  echo " Puntos ganados: ".$coleccionJuegos[$indiceJuego]["puntos"]."\n";
  echo " Informacion de la palabra:\n";
  mostrarPalabra($coleccionPalabras,$coleccionJuegos[$indiceJuego]["indicePalabra"]);
  echo "\n";
}


/**
 * Mostrar la informacion completa del primer juego con mas puntaje.
 * @param array $coleccionJuegos
 * @param array $coleccionPalabras
 * @param int $indiceJuego
 */
function mayorPuntaje($coleccionJuegos,$coleccionPalabras) {
  /*>>> Implementar las funciones necesarias para la opcion 5 del menu <<<*/
  //int $n, $cont, $mayorInd, $i

  $n=0;
  $cont=count($coleccionJuegos);
  for($i=0;$i<$cont;$i++){
    if($coleccionJuegos[$i]["puntos"]>$n){
      $n=$coleccionJuegos[$i]["puntos"];
      $mayorInd=$i;
    }
  }

  mostrarJuego($coleccionJuegos, $coleccionPalabras, $mayorInd);
}

/**
 * Mostrar la informacion completa del primer juego que supere un puntaje indicado por el usuario
 * @param array $coleccioJuegos
 * @param array $coleccionPalabras
 */
function primerPuntaje($coleccionJuegos,$coleccionPalabras) {
  /*>>> Implementar las funciones necesarias para la opcion 6 del menu <<<*/
  //boolean $primerP
  //int $i, $cont, $primerInd
  //string $punto


  $primerP=false;
  echo "Ingrese puntaje a comparar: \n";
  $punto=trim(fgets(STDIN));
  $cont=count($coleccionJuegos);
  $i=0;

  do{
    if($coleccionJuegos[$i]["puntos"]>$punto){
      $primerInd=$i;
      $primerP=true;
      
    }else{
      $i++;
    }
  }while(!$primerP && $i<$cont);

  mostrarJuego($coleccionJuegos,$coleccionPalabras,$primerInd);

}

/**
 *Mostrar la lista de palabras ordenada por orden alfabetico
 *@param array $coleccionPalabras
 */
function listaOrdenAlfabetica($coleccionPalabras) {
  /*>>> Implementar las funciones necesarias para la opcion 7 del menu <<<*/
  
  
  rsort($coleccionPalabras);//RSORT Esta función ordena un array en orden inverso (mayor a menor).
  print_r($coleccionPalabras);//PRINT_R muestra informacion sobre una variable en una forma que es legible

}


/******************************************/
/************** PROGRAMA PRINCIAL *********/
/******************************************/
//int $cantDeIntentos,$opcion,$numero,$n,$cont1,$cont2
$cantDeIntentos = 6; //cantidad de intentos que tendra el jugador para adivinar la palabra.
$coleccionJuegos = cargarJuegos();
$coleccionPalabras = cargarPalabras();
do{

  $n1=0;
  $n2=count($coleccionPalabras);
  $cont1=0;
  $cont2=count($coleccionJuegos);
  $opcion = seleccionarOpcion();
  switch ($opcion) {

    //SWITCH es similar al IF, es posible que se quiera comparar la misma expresion con valores diferentes y ejecutar una parte de codigo distinta

    case 1: //Jugar con una palabra aleatoria

      //int $puntos, $indiceAleatorioEntre, $indicePalabra
      //array $coleccionJuegos

      $indiceAleatorioEntre = indiceAleatorioEntre($n1,$n2);
      $indicePalabra = $indiceAleatorioEntre;
      $puntos = jugar($coleccionPalabras,$indicePalabra,$cantDeIntentos);
      $coleccionJuegos = agregarJuego($coleccionJuegos,$puntos,$indicePalabra);
      $cont2=count($coleccionJuegos);
      break;
    case 2: //Jugar con una palabra elegida
      // int $selec1, $puntos


      $selec1=solicitarIndiceEntre($n1,$n2-1);
      $puntos = jugar($coleccionPalabras,$selec1,$cantDeIntentos);
      $coleccionJuegos=agregarJuego($coleccionJuegos,$puntos,$selec1);
      $cont2=count($coleccionJuegos);

      break;
    case 3: //Agregar una palabra al listado

      $coleccionPalabras= palabraUsuario($coleccionPalabras);
      $n2=$n2+1;


      break;
    case 4: //Mostrar la informacion completa de un numero de juego
      //int $obteniendoIndice,$mostrandoJuego

      $obteniendoIndice=solicitarIndiceEntre($cont1,$cont2-1);
      $mostrandoJuego= mostrarJuego($coleccionJuegos,$coleccionPalabras,$obteniendoIndice);

      break;
    case 5: //Mostrar la informacion completa del primer juego con mas puntaje
      //int $mostrarElmasAltoPuntaje
      $mostrarElmasAltoPuntaje=MayorPuntaje($coleccionJuegos,$coleccionPalabras);

      break;
    case 6: //Mostrar la informacion completa del primer juego que supere un puntaje indicado por el usuario
      //int $mostrarPrimerDato
      $mostrarPrimerDato= PrimerPuntaje($coleccionJuegos,$coleccionPalabras);

      break;
    case 7: //Mostrar la lista de palabras ordenada por orden alfabetico
      //array $mostrarOrdenados
      $mostrarOrdenados=listaOrdenAlfabetica($coleccionPalabras);
      break;
  }
}while($opcion <> 8);