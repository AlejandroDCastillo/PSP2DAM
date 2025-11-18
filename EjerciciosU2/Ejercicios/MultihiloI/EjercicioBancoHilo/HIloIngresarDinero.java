package MultihiloI.EjercicioBancoHilo;
// Clase HiloIngresarDinero
class HiloIngresarDinero extends Thread {

  private CuentaBancaria cuenta;
    private String nombre;
    private int cantidad;

    HiloIngresarDinero(CuentaBancaria micuenta, String nombre, int cantidad) {
        this.cuenta = micuenta;
        this.nombre = nombre;
        this.cantidad = cantidad;
    }

    public void run() {
        cuenta.ingresarDinero(nombre, cantidad);
    }
}