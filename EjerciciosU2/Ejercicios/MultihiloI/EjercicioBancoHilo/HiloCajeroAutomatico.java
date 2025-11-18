package MultihiloI.EjercicioBancoHilo;
// Clase Principal
public class HiloCajeroAutomatico {
 public static void main(String[] args) {
        CuentaBancaria cuenta = new CuentaBancaria();

        HiloIngresarDinero padre = new HiloIngresarDinero(cuenta, "Padre", 200);
        HiloSacarDinero abuelo = new HiloSacarDinero(cuenta, "Abuelo", 600);
        HiloSacarDinero hijo1 = new HiloSacarDinero(cuenta, "Hijo1", 900);
        HiloSacarDinero madre = new HiloSacarDinero(cuenta, "Madre", 800);
        HiloIngresarDinero hijo2 = new HiloIngresarDinero(cuenta, "Hijo2", 300);

        padre.start();
        abuelo.start();
        hijo1.start();
        madre.start();
        hijo2.start();

        try {
            padre.join();
            abuelo.join();
            hijo1.join();
            madre.join();
            hijo2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("\n Operaciones finalizadas. Saldo final: " + cuentaSaldoFinal(cuenta) + "€");
    }

    // Método auxiliar para obtener el saldo final
    static int cuentaSaldoFinal(CuentaBancaria cuenta) {
        try {
            java.lang.reflect.Field f = cuenta.getClass().getDeclaredField("saldo");
            f.setAccessible(true);
            return f.getInt(cuenta);
        } catch (Exception e) {
            return -1;
        }
    }
}