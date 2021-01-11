import java.util.*;

 // Compiler version JDK 11.0.2

 class Dcoder{
   public static void main(String args[]){ 
     
     Scanner leer=new Scanner(System.in);
     int a=0, b=0, i=0, r=0;
     
    do{
      
     System.out.println("Ingresa el numero de la tabla de multiplicar que deseas: ");
     a=leer.nextInt();
     
     System.out.println("¿Cuantos multiplos deseas?");
     b=leer.nextInt();
     
     for(i=1; i<=b; i++){
       
       System.out.println(a+" x "+i+" = "+a*i);
       
     }
     
     System.out.println("¿Deseas repetir el peoceso? (1-Si, 2-No)");
     r=leer.nextInt();
     
     }while(r==1);
     
     System.out.println("*** FIN DEL PROGRAMA ***");
     
   }
 }