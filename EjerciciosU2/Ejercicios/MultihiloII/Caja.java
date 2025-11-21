package MultihiloII;

public class Caja {
    private int id;
    private boolean ocupada = false;
    private Supermercado supermercado;

    public Caja(int id, Supermercado supermercado) {
        this.id = id;
        this.supermercado = supermercado;
    }

    // Método NO sincronizado, la sincronización se manejará internamente
    public void atenderCliente(int clienteId) {
        // Bloqueo solo en esta Caja para asegurar 1 cliente a la vez
        synchronized (this) {
            ocupada = true;
        }


        System.out.println("Caja " + id + " atendiendo al cliente " + clienteId);

        try {
            Thread.sleep(5000); // Simula el tiempo de atención (5 segundos)
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        System.out.println("Caja " + id + " terminó con el cliente " + clienteId);

        // Bloqueo solo para la notificación
        synchronized (this) {
            ocupada = false;
        }

        
        // Solo ahora que hay una caja libre, notificamos a todos los clientes esperando
        synchronized (supermercado) {
            supermercado.notifyAll();
        }
    }

    public synchronized boolean isLibre() {
        return !ocupada;
    }

    public int getId() {
        return id;
    }
}