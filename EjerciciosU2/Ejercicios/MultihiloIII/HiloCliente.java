package MultihiloIII;

public class HiloCliente extends Thread{
    private int id;
    private Gimnasio gimnasio;
    public HiloCliente(int id, Gimnasio gimnasio) {
        this.id = id;
        this.gimnasio=gimnasio;
    }

    @Override
    public void run() {
        System.out.println("Cliente " + id + " entra en la cola de espera.");
        gimnasio.entrarSala(this);

    }

    public int getClienteId() {
        return id;
    }
}
