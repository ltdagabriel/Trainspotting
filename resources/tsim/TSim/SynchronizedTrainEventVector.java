package TSim;

import java.util.Vector;

/** Associated with every train is a position in a vector consisting
 *  of the last error event of that particular train. This makes it
 *  possible to not only report the error on the standard error but
 *  also make future commands affecting the train result in an
 *  exception. Since the number of trains used in the line/run is not
 *  known such a vector need to expand dynamically.  This class is a
 *  helper class that does just that. 
 *
 */  

public class SynchronizedTrainEventVector
{
    protected Vector vect;

    /** Creates a new SynchronizedTrainEventVector with the specified 
     *  initial size.
     *
     *  @param initialSize   the initial size of the vecort.
     *
     */

    public SynchronizedTrainEventVector(int initialSize)
    {
	vect = new Vector(initialSize);
    }

    /** Get the last event for the train represented by the id. The
     *  vector is expanded if necessary.
     *
     *  @param  index   the id of the train.
     *  @return the last event of the train or null if no events were 
     *          stored.
     * */

    public synchronized TrainEvent get(int index) 
    {
	if (vect.size() <= index) {
	    vect.setSize(index + 1);
	}
	
	return (TrainEvent) vect.get(index);
    }

    /** Store the given train event for the specified train. The vector is
     *  expanded if necessary.
     *
     *  @param index the train id of the train associated with the event.
     *  @param e     the train event.
     *
     */
    
    public synchronized void put(int index, TrainEvent e) 
    {
	if (vect.size() <= index)
	    vect.setSize(index + 1);
	
	vect.set(index, e);
    }

}
