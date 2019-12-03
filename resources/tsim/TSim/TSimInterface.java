package TSim;

/** The TSimInterface is the intended interface between TSim and the 
 *  laboration. It handles the extraction of information from TSim and
 *  provides methods for manipulating trains, sensors and switches.
 *
 */

public class TSimInterface implements Runnable
{

    public static final int SWITCH_LEFT  = 0x01;
    public static final int SWITCH_RIGHT = 0x02;
    
    protected SynchronizedFIFO commandFIFO     = new SynchronizedFIFO(10);

    protected SynchronizedTrainEventVector trainVec = 
	new SynchronizedTrainEventVector(0);

    protected SynchronizedSensorVector sensorVec = 
	new SynchronizedSensorVector(0);
    
    protected TSimStream sTSim;

    /** Create a new TSimInterface
     *
     */

    public TSimInterface()
    {
	sTSim = new TSimStream(System.in);
    }
    
    public void run() 
    {
	while (true) {
	    
	    try {
		TSimInformation dInfo = sTSim.read();
		
		if (dInfo instanceof CommandStatus)
		    commandFIFO.put(dInfo);
		
		/* if we got a train event something went wrong. 
		 */

		else if (dInfo instanceof TrainEvent) {
		    TrainEvent tE = (TrainEvent) dInfo;
		    
		    /* Store the error event to make future commands 
		       result in an exception.
		    */
		    
		    trainVec.put(tE.getTrainId(), tE);
		    
		    /* and report the error event on standard error
		     */
		    
		    reportTrainEvent((TrainEvent) dInfo);

		}

		/* As we do not know how many trains there are we start by
		   assuming there are 0 trains and add trains as they 
		   appear */

		else if (dInfo instanceof SensorEvent) {
		    SensorEvent sEvent = (SensorEvent) dInfo;
		    int trainId = sEvent.getTrainId();
		    
		    SynchronizedFIFO trainSensorFIFO = 
			sensorVec.get(trainId);
		    
		    trainSensorFIFO.put(sEvent);
		}
	    }
	    catch (UnparsableInputException e) {
		System.err.println(e.getMessage());
		System.exit(1);
	    }
	}
    }

    /** Helper method that reports an error event on standard error.
     *
     *  @param e   the error event.
     *
     */

    protected void reportTrainEvent(TrainEvent e) 
    {
	System.err.println(e);
    }


    /** Method that issues a command to a secific train to set its speed
     *  to the given value.
     *
     *  @param trainId  the id of the train to be affected by the command.
     *  @param speed    the new speed of the train.
     *  @throws CommandException  if the supplied id was false (NO_SUCH_TRAIN),
     *                            if the speed was illegal (ILLEGAL_SPEED)
     *                            or if the train had crashed.
     *
     */

    public synchronized void setSpeed(int trainId, int speed)
	throws CommandException
    {
	TrainEvent tE = trainVec.get(trainId);
	
	/* some event has happened for this train i.e. it has crashed */
	
	if (tE != null)
	    throw new CommandException(tE.toString());

	System.out.println("SetSpeed " + String.valueOf(trainId) + " " +
			   String.valueOf(speed));
	
	CommandStatus cStat = (CommandStatus) commandFIFO.get();

	if (cStat.getStatus() != CommandStatus.OK)
	    throw new CommandException(cStat.toString());

    }

    /** Set the position of the specified switch. Valid positions are
     *  SWITCH_LEFT and SWITCH_RIGHT.
     * 
     *  @param xPos   the x coordinate of the switch.
     *  @param yPos   the y coordinate of the switch.
     *  @param switchPos  the new position of the switch.
     *
     *  @thows CommandException if the coordinates of the switch were invalid
     *                          (NO_SUCH_SWITCH) or if there was a train on
     *                          the switch (TRAIN_ON_SWITCH)
     *
     */
     

    public synchronized void setSwitch(int xPos, int yPos, int switchPos)
	throws CommandException
    {
	
	System.out.println("SetSwitch " + String.valueOf(xPos) + " " +
			   String.valueOf(yPos) + 
			   (switchPos == SWITCH_LEFT ?
			    " LeftSwitch" : " RightSwitch"));
	
	CommandStatus cStat = (CommandStatus) commandFIFO.get();
	
	if (cStat.getStatus() != CommandStatus.OK)
	    throw new CommandException(cStat.toString());
    }

    
    /** Wait until the specified train passes a sensor.
     *
     *  @param trainId  the id of the train to wait for.
     *  @return a SensorEvent representing the information about the event
     *  @throw  CommandException if the train has crashed.
     *
     */


    public SensorEvent getSensor(int trainId) throws CommandException
    {
	TrainEvent tE = trainVec.get(trainId);
	
	/* some event has happened for this train i.e. it has crashed */
	
	if (tE != null)
	    throw new CommandException(tE.toString());

	return (SensorEvent) sensorVec.get(trainId).get();
    }

}











