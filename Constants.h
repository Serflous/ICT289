#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define ESCAPE_KEY 27

#define PIXELS_PER_CM 1
#define PIXELS_PER_METER (PIXELS_PER_CM * 100)

#define BALL_SIZE_CM (4.28/2.0)
#define BALL_SIZE_PX (BALL_SIZE_CM * PIXELS_PER_CM)

#define BALL_DETAIL_LEVEL 12

#define TARGET_FPS 120.0

#define FRICTION 5.0
#define SPEED_LOST_ON_WALL_IMPACT 0.67

#endif // CONSTANTS_H_INCLUDED