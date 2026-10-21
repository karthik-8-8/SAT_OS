#ifndef TELEMETRY_LOGGER_H
#define TELEMETRY_LOGGER_H

#include "telemetry.h"
#include <stdbool.h>


void TelemetryLogger_Init(void);
bool TelemetryLogger_AddRecord(Telemetry_Record_t *record);


#endif