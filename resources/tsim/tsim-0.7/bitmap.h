#define ReadCar(f,c,d,t) \
  ReadBitmap(parent, (f), &CarBitmap[c][d][t], &dummy, &dummy)
#define ReadRail(f,r,width,hot_y) \
  ReadBitmap(parent, (f), &RailBitmap[r], (width), hot_y)
#define ReadSemaphore(f,s,t) \
  ReadBitmap(parent, (f), &SemaphoreBitmap[s][t], &dummy, &dummy)
#define ReadSensor(f,r) \
  ReadBitmap(parent, (f), &SensorBitmap[r], &dummy, &dummy)
#define ReadSwitch(f,ce,d) \
  ReadBitmap(parent, (f), &SwitchBitmap[ce][d], &dummy, &dummy)

void ReadBitmap();
void WriteBitmap();
void ReadCustomBitmaps();
void CustomBitmaps();
