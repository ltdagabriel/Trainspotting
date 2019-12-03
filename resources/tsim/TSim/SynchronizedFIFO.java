package TSim;

import java.util.Vector;

/** The SynchronizedFIFO class implements a freely growable FIFO. 
 *  It is based on the java.util.Vecor class that has been wrapped
 *  with synchronized access methods.
 *
 */

public class SynchronizedFIFO 
{
    protected Vector data;
    
    /** Creates a new SynchronizedFIFO with given initial size.
     *
     *  @param size   the initial size of the SynchronizedFIFO.
     *
     */
    
    public SynchronizedFIFO(int size) 
    {
	data = new Vector(size);
    }
    
    /** Puts an object first in the FIFO. Since the FIFO automatically
     *  grows the method don't block.
     *
     *  @param o   the object to be insertet first in the FIFO.
     * 
     */
    
    public synchronized void put(Object o) 
    {
	data.add(o);
	notifyAll();
    }

    /** Removes and returns the first object in the FIFO if such
     *  exists. If not this method blocks until an object is inserted
     *  into the FIFO.
     *
     *  @return  the first object in the FIFO.
     *
     */

    public synchronized Object get() 
    {
	while (data.size() == 0)
	    try {
		wait();
	    }
	    catch (InterruptedException e) {
	    }
	
	return data.remove(0);
	
    }
}












