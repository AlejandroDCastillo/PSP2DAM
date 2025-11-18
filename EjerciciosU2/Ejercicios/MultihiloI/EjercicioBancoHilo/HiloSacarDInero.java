package MultihiloI.EjercicioBancoHilo;
// Clase HiloSacarDinero
class HiloSacarDinero extends Thread {
 private CuentaBancaria cuenta;
    private String nombre;
    private int cantidad;

    HiloSacarDinero(CuentaBancaria micuenta, String nombre, int cantidad) {
        this.cuenta = micuenta;
        this.nombre = nombre;
        this.cantidad = cantidad;
    }

    public void run() {
        cuenta.sacarDinero(nombre, cantidad);
    }
}