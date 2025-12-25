/* 
 * File:   washin_machine_header.h
 * Author: Penta Seetaram
 *
 * Created on 11 June, 2025, 8:54 PM
 */

#ifndef WASHIN_MACHINE_HEADER_H
#define	WASHIN_MACHINE_HEADER_H

void power_on_screen(void);
void clear_screen(void);
void washing_program_display(unsigned char key);
void water_level_screen(unsigned char key);
void set_time(void);
void run_program(unsigned char key);
void door_status_check(void);

#endif	/* WASHIN_MACHINE_HEADER_H */
