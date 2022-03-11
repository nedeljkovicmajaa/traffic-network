#include "Line.h"

int Line::isInLine(int station_id)
{
	for (auto& station_id_ : train_stations) {
		if (station_id == station_id_) {
			return 1;
		}
	}

	return 0;
}