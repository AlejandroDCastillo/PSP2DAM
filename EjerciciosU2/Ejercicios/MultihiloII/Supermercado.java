package MultihiloII;

public class Supermercado {
    private Caja[] cajas;

    public Supermercado(int numCajas) {
        cajas = new Caja[numCajas];
        for (int i = 0; i < numCajas; i++) {
            cajas[i] = new Caja(i + 1, this);
        }
    }

    // Método sincronizado para asignar un cliente a una caja libre
    public void atenderCliente(HiloCliente cliente) {
        Caja cajaAsignada;

        synchronized (this) {
            // El cliente debe esperar *mientras* no haya una caja libre.
            while ((cajaAsignada = getCajaLibre()) == null) {
                try {
                    System.out.println("Cliente " + cliente.getClienteId() + " esperando por caja libre...");
                    wait(); // Libera el lock del Supermercado y espera la notificación
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }

        // Sale del bloque synchronized de Supermercado y llama al método de la Caja
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