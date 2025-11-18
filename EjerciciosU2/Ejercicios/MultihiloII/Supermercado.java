package MultihiloII;

public class Supermercado {
    private Caja[] cajas;

    public Supermercado(int numCajas) {
        cajas = new Caja[numCajas];
        for (int i = 0; i < numCajas; i++) {
            cajas[i] = new Caja(i + 1);
        }
    }

    // Método sincronizado para asignar un cliente a una caja libre
    public synchronized void atenderCliente(HiloCliente cliente) {
        Caja cajaLibre = null;

        // Esperar hasta que haya una caja libre
        while ((cajaLibre = getCajaLibre()) == null) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Atender al cliente en una caja libre (fuera del synchronized)
        Caja cajaAsignada = cajaLibre;
        notifyAll();

        // Atender en una caja específica
        cajaAsignada.atenderCliente(cliente.getClienteId());
    }

    // Método auxiliar para buscar una caja libre
    private Caja getCajaLibre() {
        for (Caja c : cajas) {
            if (c.isLibre()) {
                return c;
            }
        }
        return null;
    }
}
