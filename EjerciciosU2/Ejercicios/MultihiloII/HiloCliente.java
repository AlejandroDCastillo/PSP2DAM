package MultihiloII;

public class HiloCliente extends Thread{
    private int id;
    private Supermercado supermercado;

    public HiloCliente(int id, Supermercado supermercado) {
        this.id = id;
        this.supermercado = supermercado;
    }

    @Override
    public void run() {
        System.out.println("Cliente " + id + " entra en la cola de espera.");
        supermercado.atenderCliente(this);
    }

    public int getClienteId() {
        return id;
    }
}
