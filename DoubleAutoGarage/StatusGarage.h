
#ifndef __STATUS_GARAGE_H__
#define __STATUS_GARAGE_H__

// Enumeration for Garage Status
enum Status_garage
{
	INITIAL = 0,
	UP = 1,
	DOWN = -1,
	PAUSE = 2,
	MANUAL = -2,
	FINISH = 3,
	OVER_UP = -3,
	OVER_DOWN = 4
};
	
#endif

