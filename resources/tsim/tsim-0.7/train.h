typedef enum {
  NoRail,
  HorizontalRail,
  VerticalRail, 
  UpLeftRail,
  UpRightRail,
  DownLeftRail,
  DownRightRail,
  UpStopRail,
  RightStopRail,
  DownStopRail,
  LeftStopRail,
  } tRailType;

typedef struct { 
  int x,y;
} tPos;

typedef tPos tRailPos;

typedef enum {
  NoDir,
  Up,
  Right,
  Down,
  Left 
  } tDirection;

typedef struct _tTrainLine *tTrainLine;
typedef int tTrainNo;

typedef enum {
  NoSensor,
  Sensor
  } tSensorState;

typedef enum {
  NoSemaphore,
  GoSemaphore,
  StopSemaphore
  } tSemaphoreState;

typedef enum {
  LeftSwitch,
  RightSwitch
  } tSwitchState;

typedef enum {
  SuccessStatus,	/* 0 */
  NoSwitchStatus,
  IllegalReverseStatus,
  IllegalTrainNoStatus,
  IllegalRailPosStatus,
  IllegalSwitchingStatus,
  } tStatus;

typedef enum {
  NoEvent,
  TrainCollisionEvent,
  StopCollisionEvent,
  DerailmentEvent
  } tEvent;

typedef int tTrainDisplacement;

tPos WidgetPos();
tPos Pos();
tRailPos RailPos();
tTrainLine CreateTrainLine();
void DeleteTrainLine();
tRailPos Space();
tStatus SetSpeed();
Boolean IsCustom();
Boolean CarPresent();
void SetRailType();
void SetRailBitmap();
tRailType RailType();
void SetSensorState();
tSensorState SensorState();
void SetSemaphore();
tSemaphoreState SemaphoreState();
tStatus SetSwitch();
tSwitchState SwitchState();
tStatus DeleteTrain();
tEvent CreateTrain();
tEvent MoveTrain();
