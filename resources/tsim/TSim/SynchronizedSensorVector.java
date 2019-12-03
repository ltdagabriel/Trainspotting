package TSim;

import java.util.Vector;

/** Every train has an FIFO of sensor events associated with it. This FIFO
 *  contains the sensor events of that specific train. Since we do not know
 *  how many trains a specific line/run might have we need to allocate those
 *  FIFOs dynamically. This is a synchronized helper class that does
 *  just that. If the requested train has never been seen before a new empty
 *  FIFO is allocated and returned. 
 *
 */

public class SynchronizedSensorVector 
{
    protected Vector vect;

    /** Creates a new SynchronizedSensorVector with the given initial size.
     *  
     *  @param initialSize   the initial size if the vector.
     *
     */

    public SynchronizedSensorVector(int initialSize)
    {
	vect = new Vector(initialSize);
    }

    /** Returns the FIFO associated with a specific train and allocates
     *  a new FIFO and expands the vector if it was the first request 
     *  for that train id.
     *
     *  @param index  the id of the train associated with the FIFO.
     *  @return  the FIFO associated with the train id.
     *
     */

    public synchronized SynchronizedFIFO get(int index) 
    {
	if (vect.size() <= index) {
	    vect.setSize(index + 1);
	}

	SynchronizedFIFO o = (SynchronizedFIFO) vect.get(index);
	
	if (o == null) {
	    o = new SynchronizedFIFO(10);
	    
	    put(index, o);
	}
			  

	return o;
    }

    /** Stores the given FIFO at the specified position in the vector.
     *  The vector is expanded if needed.
     *
     *  @param index   the position where the FIFO should be placed.
     *
     */

    public synchronized void put(int index, SynchronizedFIFO o) 
    {
	if (vect.size() <= index)
	    vect.setSize(index + 1);
	
	vect.set(index, o);
    }

}




