#define StringToEnum(s, type, tostring, lower, upper) \
  (type)StringToInt((s), tostring, lower, upper)
#define StringToSwitchState(s) \
  StringToEnum((s), tSwitchState, SwitchStateToString, LeftSwitch, RightSwitch)
#define StringToRailType(s) \
  StringToEnum((s), tRailType, RailTypeToString, NoRail, LeftStopRail)
#define StringToDirection(s) \
  StringToEnum((s), tDirection, DirectionToString, NoDir, Left)
#define StringToSensorState(s) \
  StringToEnum((s), tSensorState, SensorStateToString, NoSensor, \
	       Sensor)

extern String SwitchStateToString[];
extern String DirectionToString[];
extern String RailTypeToString[];
extern String SensorStateToString[];
extern String StatusToString[];
extern String EventToString[];

int StringToInt();
Boolean SaveTrainLine();
tTrainLine LoadTrainLine();
