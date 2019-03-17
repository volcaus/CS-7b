#ifndef Sandpile_Included
#define Sandpile_Included

#include "grid.h"

/**
 * Drops a unit into the specific world at the specified position.
 *
 * If the position is out of bounds, then this function has no effect and the grid
 * is left unmodified.
 *
 * This may trigger a diffusion, which may propagate to other locations in the grid. A
 * cell diffuses when it reaches four units, and when it diffuses, it's emptied out
 * and a unit is dropped on each of the four neighbors.
 *
 * @param world The grid into which to drop the units.
 * @param row The row into which the unit is dropped.
 * @param col The column into which the unit is dropped.
 */
void dropUnit(Grid<int>& world, int x, int y);

#endif
