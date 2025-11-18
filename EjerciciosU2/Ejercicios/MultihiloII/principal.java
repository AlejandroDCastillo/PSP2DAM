package MultihiloII;

public class principal {
     public static void main(String[] args) {
        Supermercado supermercado = new Supermercado(3); // 3 cajas
        int numClientes = 15;

        // Crear y lanzar los hilos de los clientes
        HiloCliente[] clientes = new HiloCliente[numClientes];
        for (int i = 0; i < numClientes; i++) {
            clientes[i] = new HiloCliente(i + 1, supermercado);
            clientes[i].start();
        }

        // Esperar a que todos los clientes terminen
        for (int i = 0; i < numClientes; i++) {
            try {
                clientes[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println(" Supermercado cerrado.");
    }
}
