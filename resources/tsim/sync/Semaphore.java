package sync;

public class Semaphore {
    private int state;

    public Semaphore(int s) {
	state=s;
    }

    public Semaphore() {
	state=0;
    }

    public synchronized void acquire() {
	while(state<=0)
	    try {
		wait();
	    } catch(InterruptedException ie) {
		throw new RuntimeException("May not interrupt semaphore");
	    }
	state--;
    }

    public synchronized void release() {
	state++;
	notify();
    }

    public synchronized boolean tryAcquire() {
	if (state>0) {
	    state--;
	    return true;
	} else
	    return false;
    }
}
