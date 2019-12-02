/*
 * File      : fal_flash_sfud_port.c
 * This file is part of FAL (Flash Abstraction Layer) package
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     armink       the first version
 */

#include <fal.h>

#ifdef FAL_FLASH_PORT_DRIVER_SFUD
#include <sfud.h>
#include <spi_flash_sfud.h>

sfud_flash sfud_norflash0;

static int fal_sfud_init(void)
{
    sfud_flash_t sfud_flash0 = NULL;
    sfud_flash0 = (sfud_flash_t)rt_sfud_flash_find("qspi10");
    if (NULL == sfud_flash0)
    {
        return -1;
    }

    sfud_norflash0 = *sfud_flash0;
    return 0;
}

static int read(long offset, uint8_t *buf, size_t size)
{
    sfud_read(&sfud_norflash0, nor_flash0.addr + offset, size, buf);

    return size;
}

static int write(long offset, const uint8_t *buf, size_t size)
{
    if (sfud_write(&sfud_norflash0, nor_flash0.addr + offset, size, buf) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}

static int erase(long offset, size_t size)
{
    if (sfud_erase(&sfud_norflash0, nor_flash0.addr + offset, size) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}
const struct fal_flash_dev nor_flash0 = { "nor_flash", 0, (16 * 1024 * 1024), 4096, {fal_sfud_init, read, write, erase} };
#endif /* FAL_FLASH_PORT_DRIVER_SFUD */
