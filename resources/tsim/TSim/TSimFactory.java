package TSim;

/** Class that creates a new TSimInterface and starts it.
 *
 */

public class TSimFactory
{
    
    /** Creates a new TSimInterface and starts a new thread that runs 
     *  the data collecting part of the inteface.
     *
     *  @return a new TSimInterface.
     *
     */

    public static TSimInterface getTSimInterface() 
    {
	TSimInterface tsim = new TSimInterface();
	
	Thread tsimT = new Thread(tsim);
	
	tsimT.start();
	
	return tsim;
    }
    
}
