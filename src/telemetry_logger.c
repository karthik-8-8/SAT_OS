#include "telemetry_logger.h"
#include "sdcard.h"
#include <string.h>

static uint8_t block_buffer[512];

static uint32_t current_block=100;
static uint32_t record_count=0;

void TelemetryLogger_Init(void)
{
    memset(block_buffer,0,sizeof(block_buffer));
}

bool TelemetryLogger_AddRecord(Telemetry_Record_t *record)
{
    uint32_t offset;
    offset=record_count*sizeof(Telemetry_Record_t);
    if(offset + sizeof(Telemetry_Record_t) > 512)
        {
            if(!SD_WriteBlock(current_block, block_buffer))
            {
                return false;
            }

            current_block++;
            record_count = 0;

            memset(block_buffer, 0, sizeof(block_buffer));

            offset = 0;
        }
    memcpy(block_buffer + offset, record, sizeof(Telemetry_Record_t));
    record_count++;
    return true;
}