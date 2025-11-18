package MultihiloI;
public class HiloSumasRestas implements Runnable {
    private int numero=1000;
    private int numveces;     
    private String operacion;
 //Constructor de la clase
 public HiloSumasRestas (int numveces, String operacion)
 {
    this.numveces=numveces;
    this.operacion=operacion;
}
 //Incrementará numero el numvece indicado
 public int incrementar (int numveces)
 {
    numero+=numveces;
    return numero;
 }
 //Decrementará numero el numvece indicado
 public int decrementar (int numveces)
 {
    numero-=numveces;
    return numero;

 }
 public void run() {
 //Si la operación es “+” se invocará al método incrementar
 //Si la operación es “-” se invocará al método decrementar
  if (this.operacion.equals("+")) {
        incrementar(this.numveces);
         System.out.println(Thread.currentThread().getName() + " incrementó: " + numero);

    }else{
        decrementar(this.numveces);
        System.out.println(Thread.currentThread().getName() + " decrementó: " + numero);

    }

}
public static void main(String[] args) {
        Thread HiloSuma1 = new Thread(new HiloSumasRestas(100,"+"),"HiloSuma1");
        Thread HiloResta2 = new Thread(new HiloSumasRestas(100,"-"),"HiloResta2");
        Thread HiloSuma3 =  new Thread(new HiloSumasRestas(1,"+"),"HiloSuma3");
        Thread HiloResta4  = new Thread(new HiloSumasRestas(1,"-"),"HiloResta4");


        HiloSuma1.start();
        HiloResta2.start();
        HiloSuma3.start();
        HiloResta4.start();
    }
}

    