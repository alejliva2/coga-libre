#ifndef TIMEDATA_H
#define TIMEDATA_H

// =========================
// TIEMPO
// =========================
struct TimeData
{
    double currentTime;
    double lastTime;
    double deltaTime;
};

void initTime(TimeData &td);
void updateTime(TimeData &td);

#endif