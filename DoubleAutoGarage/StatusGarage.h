
#ifndef __STATUS_GARAGE_H__
#define __STATUS_GARAGE_H__

// Enumeration for Garage Status
enum Status_garage
{
	INITIAL = 0,
	UP = 1,
	DOWN = -1,
	MANUAL_UP = 2,
	MANUAL_DOWN = -2,
	PAUSE = 3,
	FINISH = 4,
	MANUAL_OVER_UP = 5,
	MANUAL_OVER_DOWN = -5,
	OVER_UP = 6,
	OVER_DOWN = -6
};
	
#endif

