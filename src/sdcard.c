#include "sdcard.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define SD_CS_PIN 13

static void SD_Select(void)
{
    gpio_put(SD_CS_PIN, 0);
}

static void SD_Deselect(void)
{
    gpio_put(SD_CS_PIN, 1);
}

static uint8_t SD_SendCommand(uint8_t cmd,
                              uint32_t arg,
                              uint8_t crc)
{
    uint8_t packet[6];
    uint8_t response = 0xFF;

    packet[0] = 0x40 | cmd;
    packet[1] = (arg >> 24) & 0xFF;
    packet[2] = (arg >> 16) & 0xFF;
    packet[3] = (arg >> 8) & 0xFF;
    packet[4] = arg & 0xFF;
    packet[5] = crc;

    SPI_Write(packet, 6);

    for(int i = 0; i < 10; i++)
    {
        SPI_Read(&response, 1);

        if((response & 0x80) == 0)
        {
            break;
        }
    }

    return response;
}

bool SD_Init(void)
{
    gpio_init(SD_CS_PIN);
    gpio_set_dir(SD_CS_PIN, GPIO_OUT);

    SD_Deselect();

    uint8_t dummy = 0xFF;

    /* 80 startup clocks */
    for(int i = 0; i < 10; i++)
    {
        SPI_Write(&dummy, 1);
    }

    SD_Select();

    uint8_t response;

    /*---------------- CMD0 ----------------*/
    printf("\r\nCMD0...\r\n");

    response = SD_SendCommand(0, 0x00000000, 0x95);

    printf("CMD0 Response = 0x%02X\r\n", response);

    if(response != 0x01)
    {
        printf("CMD0 FAILED\r\n");
        return false;
    }

    printf("CMD0 SUCCESS\r\n");

    /*---------------- CMD8 ----------------*/
    printf("\r\nCMD8...\r\n");

    response = SD_SendCommand(8, 0x000001AA, 0x87);

    printf("CMD8 Response = 0x%02X\r\n", response);

    if(response != 0x01)
    {
        printf("CMD8 FAILED\r\n");
        return false;
    }

    printf("CMD8 SUCCESS\r\n");

    uint8_t r7[4];
    SPI_Read(r7, 4);

    printf("R7 = %02X %02X %02X %02X\r\n",
        r7[0], r7[1], r7[2], r7[3]);

    /*------------- CMD55 + ACMD41 -------------*/
    printf("\r\nStarting ACMD41 Loop...\r\n");

    for(int retry = 0; retry < 1000; retry++)
    {
        response = SD_SendCommand(55, 0x00000000, 0xFF);

        printf("CMD55 Response = 0x%02X\r\n", response);

        if(response > 0x01)
        {
            printf("CMD55 FAILED\r\n");
            return false;
        }

        response = SD_SendCommand(41, 0x40000000, 0xFF);

        printf("ACMD41 Response = 0x%02X\r\n", response);

        if(response == 0x00)
        {
            printf("ACMD41 SUCCESS\r\n");
            break;
        }
    }

    if(response != 0x00)
    {
        printf("ACMD41 TIMEOUT\r\n");
        return false;
    }

    /*---------------- CMD58 ----------------*/
    printf("\r\nCMD58...\r\n");

    response = SD_SendCommand(58, 0x00000000, 0xFF);

    printf("CMD58 Response = 0x%02X\r\n", response);

    if(response != 0x00)
    {
        printf("CMD58 FAILED\r\n");
        return false;
    }

    printf("CMD58 SUCCESS\r\n");

    uint8_t ocr[4];

    SPI_Read(ocr, 4);

    printf("OCR = %02X %02X %02X %02X\r\n",
           ocr[0], ocr[1], ocr[2], ocr[3]);

    SD_Deselect();
    SPI_Write(&dummy, 1);

    printf("\r\nSD CARD INITIALIZED SUCCESSFULLY\r\n");

    return true;
}

bool SD_ReadBlock(uint32_t block_address, uint8_t *buffer)
{
    uint8_t response;

    SD_Select();

    response = SD_SendCommand(17, block_address, 0xFF);

    if(response != 0x00)
    {
        SD_Deselect();

        uint8_t dummy = 0xFF;
        SPI_Write(&dummy, 1);

        return false;
    }

    uint8_t token = 0xFF;

    for(uint32_t i = 0; i < 10000; i++)
    {
        SPI_Read(&token, 1);

        if(token == 0xFE)
        {
            break;
        }
    }

    if(token != 0xFE)
    {
        SD_Deselect();

        uint8_t dummy = 0xFF;
        SPI_Write(&dummy, 1);

        return false;
    }

    SPI_Read(buffer, 512);

    uint8_t crc[2];
    SPI_Read(crc, 2);

    SD_Deselect();

    uint8_t dummy = 0xFF;
    SPI_Write(&dummy, 1);

    return true;
}

bool SD_WriteBlock(uint32_t block_address,const uint8_t *buffer)
{
    SD_Select();

    uint8_t response;

    response=SD_SendCommand(24,block_address,0xFF);

    if(response !=0x00)
    {
        SD_Deselect();

        uint8_t dummy =0xFF;
        SPI_Write(&dummy,1);

        return false;
    }

    uint8_t token =0xFE;
    
    SPI_Write(&token,1);

    SPI_Write(buffer,512);
    uint8_t crc[2] = {0xFF, 0xFF};

    SPI_Write(crc, 2);
    
    uint8_t data_response;

    SPI_Read(&data_response,1);

    if((data_response&0x1F)!=0x05)
    {
        printf("Write Failed\r\n");
        SD_Deselect();

        uint8_t dummy =0xFF;
        SPI_Write(&dummy,1);

        return false;
    }
    else
    {
        printf("Write Success\r\n");
    }

    uint8_t busy=0x00;
    for(uint32_t i=0;i<10000;i++)
    {
        SPI_Read(&busy,1);
        if(busy==0xFF)
        {
            break;
        }
    }
    if(busy!=0xFF)
    {
        printf("Busy Timeout\r\n");
        SD_Deselect();
        uint8_t dummy =0xFF;
        SPI_Write(&dummy,1);
        return false;
    }


    SD_Deselect();
    uint8_t dummy =0xFF;
    SPI_Write(&dummy,1);
    return true;

}