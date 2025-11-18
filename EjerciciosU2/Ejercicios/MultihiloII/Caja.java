package MultihiloII;

public class Caja {
    private int id;
    private boolean ocupada = false;

    public Caja(int id) {
        this.id = id;
    }

    // Método sincronizado para atender a un cliente
    public synchronized void atenderCliente(int clienteId) {
        while (ocupada) {
            try {
                wait(); // Espera hasta que la caja quede libre
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        ocupada = true;
        System.out.println("Caja " + id + " atendiendo al cliente " + clienteId);

        try {
            Thread.sleep(5000); // Simula el tiempo de atención (5 segundos)
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Caja " + id + " terminó con el cliente " + clienteId);
        ocupada = false;

        notifyAll(); // Notifica a los hilos que esperan que esta caja está libre
    }

    public boolean isLibre() {
        return !ocupada;
    }

    public int getId() {
        return id;
    }
}
