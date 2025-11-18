package MultihiloI.EjercicioBancoHilo;
// Clase CuentaBancaria
// Definición de la cuenta con un saldo inicial y de las operaciones para
//ingresar dinero (método ingresarDinero) y sacar dinero (método sacarDinero) de ç
// la cuenta
class CuentaBancaria {
 //Saldo inicial de la cuenta
private int saldo = 1000;

    // Método sincronizado para ingresar dinero
    synchronized void ingresarDinero(String nombre, int cantidad) {
        System.out.println(nombre + " ingresó en la cuenta " + cantidad + "€");
        saldo += cantidad;
        System.out.println("Saldo actual cuenta= " + saldo + "€");

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
     synchronized void sacarDinero(String nombre, int cantidad) {
        if (saldo >= cantidad) {
            System.out.println(nombre + " sacó de la cuenta " + cantidad + "€");
            saldo -= cantidad;
            System.out.println("Saldo actual cuenta= " + saldo + "€");
        } else {
            System.out.println(nombre + " no puede sacar " + cantidad + "€ -> NO HAY SALDO SUFICIENTE");
            System.out.println("Saldo actual cuenta= " + saldo + "€");
        }

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
